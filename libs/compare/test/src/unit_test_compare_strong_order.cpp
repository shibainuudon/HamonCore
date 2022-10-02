/**
 *	@file	unit_test_compare_strong_order.cpp
 *
 *	@brief	strong_order のテスト
 */

#include <hamon/compare/strong_order.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/compare/is_eq.hpp>
#include <hamon/compare/concepts/three_way_comparable.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if defined(HAMON_HAS_STD_COMPARE) && defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

namespace hamon_compare_test
{

namespace strong_order_test
{

constexpr hamon::strong_ordering
different_cv_quals(int i, const int j)
{
	return hamon::strong_order(i, j);
}

struct X
{
	int i;

	friend constexpr hamon::strong_ordering
	operator<=>(X l, X r)
	{
		if (l.i < 0 && r.i < 0)
		{
			return hamon::strong_ordering::equivalent;
		}
		return r.i <=> l.i;
	}

	friend constexpr bool operator==(X l, X r)
	{
		return hamon::is_eq(l <=> r);
	}
};

struct Y
{
	int i;

	friend constexpr hamon::strong_ordering
	strong_order(Y lhs, Y rhs)
	{
		return lhs.i <=> rhs.i;
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	using hamon::strong_order;
	using hamon::strong_ordering;

	VERIFY(strong_order(1, 2) == strong_ordering::less);
	VERIFY(strong_order(1, 1) == strong_ordering::equal);
	VERIFY(strong_order(2, 1) == strong_ordering::greater);
	static_assert(noexcept(strong_order(1, 1)), "");

	VERIFY(different_cv_quals(  42,  999) == strong_ordering::less);
	VERIFY(different_cv_quals(-999, -999) == strong_ordering::equal);
	VERIFY(different_cv_quals( -99, -111) == strong_ordering::greater);

	static_assert(hamon::three_way_comparable<X>, "");

	X x1{ 1};
	X x2{-1};
	X x3{ 2};
	X x4{-2};
	VERIFY(strong_order(x1, x1) == strong_ordering::equal);
	VERIFY(strong_order(x2, x4) == strong_ordering::equivalent);
	VERIFY(strong_order(x1, x3) == strong_ordering::greater);
#if !defined(_MSC_VER)
	static_assert(!noexcept(strong_order(X{1}, X{2})), "");
#endif

	Y y1{ 1};
	Y y2{-1};
	Y y3{ 2};
	Y y4{-2};
	VERIFY(strong_order(y1, y1) == strong_ordering::equal);
	VERIFY(strong_order(y1, y2) == strong_ordering::greater);
	VERIFY(strong_order(y1, y3) == strong_ordering::less);
	VERIFY(strong_order(y1, y4) == strong_ordering::greater);

	return true;
}

#undef VERIFY

GTEST_TEST(CompareTest, StrongOrderTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace strong_order_test

}	// namespace hamon_compare_test

#endif
