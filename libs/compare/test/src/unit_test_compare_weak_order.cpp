/**
 *	@file	unit_test_compare_weak_order.cpp
 *
 *	@brief	weak_order のテスト
 */

#include <hamon/compare/weak_order.hpp>
#include <hamon/compare/weak_ordering.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/compare/is_eq.hpp>
#include <hamon/compare/concepts/three_way_comparable.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

#if defined(HAMON_HAS_STD_COMPARE) && defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

namespace hamon_compare_test
{

namespace weak_order_test
{

constexpr hamon::weak_ordering
different_cv_quals(int i, const int j)
{
	return hamon::weak_order(i, j);
}

struct X
{
	int i;

	friend constexpr hamon::weak_ordering
	operator<=>(X l, X r)
	{
		if (l.i < 0 && r.i < 0)
		{
			return hamon::weak_ordering::equivalent;
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

	friend constexpr hamon::weak_ordering
	weak_order(Y lhs, Y rhs)
	{
		return lhs.i <=> rhs.i;
	}
};

struct Z
{
	int i;

	friend constexpr hamon::strong_ordering
	strong_order(Z lhs, Z rhs)
	{
		return lhs.i <=> rhs.i;
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	using hamon::weak_order;
	using hamon::weak_ordering;

	VERIFY(weak_order(1, 2) == weak_ordering::less);
	VERIFY(weak_order(1, 1) == weak_ordering::equivalent);
	VERIFY(weak_order(2, 1) == weak_ordering::greater);
	static_assert(noexcept(weak_order(1, 1)), "");

	VERIFY(different_cv_quals(  42,   999) == weak_ordering::less);
	VERIFY(different_cv_quals(-999,  -999) == weak_ordering::equivalent);
	VERIFY(different_cv_quals(-999, -1000) == weak_ordering::greater);

	static_assert(hamon::three_way_comparable<X>, "");

	X x1{ 1};
	X x2{-1};
	X x3{ 2};
	X x4{-2};
	VERIFY(weak_order(x1, x1) == weak_ordering::equivalent);
	VERIFY(weak_order(x2, x4) == weak_ordering::equivalent);
	VERIFY(weak_order(x1, x3) == weak_ordering::greater);
#if !defined(_MSC_VER)
	static_assert(!noexcept(weak_order(X{1}, X{2})), "");
#endif

	Y y1{ 1};
	Y y2{-1};
	Y y3{ 2};
	Y y4{-2};
	VERIFY(weak_order(y1, y1) == weak_ordering::equivalent);
	VERIFY(weak_order(y1, y2) == weak_ordering::greater);
	VERIFY(weak_order(y1, y3) == weak_ordering::less);
	VERIFY(weak_order(y1, y4) == weak_ordering::greater);

	Z z1{ 1};
	Z z2{-1};
	Z z3{ 2};
	Z z4{-2};
	VERIFY(weak_order(z1, z1) == weak_ordering::equivalent);
	VERIFY(weak_order(z1, z2) == weak_ordering::greater);
	VERIFY(weak_order(z1, z3) == weak_ordering::less);
	VERIFY(weak_order(z1, z4) == weak_ordering::greater);

	VERIFY(weak_order( 0.0,  0.0) == weak_ordering::equivalent);
	VERIFY(weak_order(-0.0, -0.0) == weak_ordering::equivalent);
	VERIFY(weak_order(-0.0,  0.0) == weak_ordering::equivalent);
	VERIFY(weak_order( 0.0, -0.0) == weak_ordering::equivalent);

	double min = std::numeric_limits<double>::lowest();
	double max = std::numeric_limits<double>::max();
	double nan = std::numeric_limits<double>::quiet_NaN();
	double inf = std::numeric_limits<double>::infinity();
	double denorm = std::numeric_limits<double>::denorm_min();
	double smallest = std::numeric_limits<double>::min();
	double epsilon = std::numeric_limits<double>::epsilon();

	VERIFY(weak_order(denorm, smallest) == weak_ordering::less);
	VERIFY(weak_order(denorm, 0.0) == weak_ordering::greater);
	//VERIFY(weak_order(0.0, nan) == weak_ordering::less);
	VERIFY(weak_order( nan,  nan) == weak_ordering::equivalent);
	//VERIFY(weak_order( nan, -nan) == weak_ordering::greater);
	//VERIFY(weak_order(-nan,  nan) == weak_ordering::less);
	//VERIFY(weak_order(nan, 0.0) == weak_ordering::greater);
	//VERIFY(weak_order(-nan, 0.0) == weak_ordering::less);
	//VERIFY(weak_order(-nan, min) == weak_ordering::less);
	VERIFY(weak_order(-inf, min) == weak_ordering::less);
	//VERIFY(weak_order(-nan, -inf) == weak_ordering::less);
	//VERIFY(weak_order(-inf, -nan) == weak_ordering::greater);
	VERIFY(weak_order(max, inf) == weak_ordering::less);
	VERIFY(weak_order(inf, max) == weak_ordering::greater);
	//VERIFY(weak_order(inf, nan) == weak_ordering::less);
	VERIFY(weak_order(1.0, 1.0+epsilon) == weak_ordering::less);

	return true;
}

#undef VERIFY

GTEST_TEST(CompareTest, WeakOrderTest)
{
//	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	EXPECT_TRUE(test01());
}

}	// namespace weak_order_test

}	// namespace hamon_compare_test

#endif
