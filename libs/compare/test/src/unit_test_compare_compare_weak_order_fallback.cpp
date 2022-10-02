﻿/**
 *	@file	unit_test_compare_compare_weak_order_fallback.cpp
 *
 *	@brief	compare_weak_order_fallback のテスト
 */

#include <hamon/compare/compare_weak_order_fallback.hpp>
#include <hamon/compare/weak_ordering.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_compare_test
{

namespace compare_weak_order_fallback_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

struct X
{
	double v = 0.0;

	constexpr X(double x) : v(x) {}

	friend constexpr bool operator==(const X& lhs, const X& rhs)
	{
		return lhs.v == rhs.v;
	}

	friend constexpr bool operator<(const X& lhs, const X& rhs)
	{
		return !hamon::isnan(lhs.v) && !hamon::isnan(rhs.v) && lhs.v < rhs.v;
	}
};

inline HAMON_CXX17_CONSTEXPR bool test01()
{
	using hamon::compare_weak_order_fallback;
	using hamon::weak_ordering;

	int n1 = 1;
	int n2 = 2;
	VERIFY(compare_weak_order_fallback(n1, n1) == weak_ordering::equivalent);
	VERIFY(compare_weak_order_fallback(n1, n2) == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(n2, n1) == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(n2, n2) == weak_ordering::equivalent);
	static_assert(noexcept(compare_weak_order_fallback(1, 1)), "");

	X x1  {+0.0};
	X x2  {-0.0};
	X x3  {+1.0};
	X x4  {-1.0};
	X x5  { std::numeric_limits<double>::quiet_NaN()};
	X x6  {-std::numeric_limits<double>::quiet_NaN()};
	X x7  { std::numeric_limits<double>::max()};
	X x8  { std::numeric_limits<double>::lowest()};
	X x9  { std::numeric_limits<double>::infinity()};
	X x10 {-std::numeric_limits<double>::infinity()};

	VERIFY(compare_weak_order_fallback(x1, x1)  == weak_ordering::equivalent);
	VERIFY(compare_weak_order_fallback(x1, x2)  == weak_ordering::equivalent);
	VERIFY(compare_weak_order_fallback(x1, x3)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x1, x4)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x1, x5)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x1, x6)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x1, x7)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x1, x8)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x1, x9)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x1, x10) == weak_ordering::greater);

	VERIFY(compare_weak_order_fallback(x2, x1)  == weak_ordering::equivalent);
	VERIFY(compare_weak_order_fallback(x2, x2)  == weak_ordering::equivalent);
	VERIFY(compare_weak_order_fallback(x2, x3)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x2, x4)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x2, x5)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x2, x6)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x2, x7)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x2, x8)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x2, x9)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x2, x10) == weak_ordering::greater);

	VERIFY(compare_weak_order_fallback(x3, x1)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x3, x2)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x3, x3)  == weak_ordering::equivalent);
	VERIFY(compare_weak_order_fallback(x3, x4)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x3, x5)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x3, x6)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x3, x7)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x3, x8)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x3, x9)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x3, x10) == weak_ordering::greater);

	VERIFY(compare_weak_order_fallback(x4, x1)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x4, x2)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x4, x3)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x4, x4)  == weak_ordering::equivalent);
	VERIFY(compare_weak_order_fallback(x4, x5)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x4, x6)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x4, x7)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x4, x8)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x4, x9)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x4, x10) == weak_ordering::greater);

	VERIFY(compare_weak_order_fallback(x5, x1)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x5, x2)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x5, x3)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x5, x4)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x5, x5)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x5, x6)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x5, x7)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x5, x8)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x5, x9)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x5, x10) == weak_ordering::greater);

	VERIFY(compare_weak_order_fallback(x6, x1)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x6, x2)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x6, x3)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x6, x4)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x6, x5)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x6, x6)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x6, x7)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x6, x8)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x6, x9)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x6, x10) == weak_ordering::greater);

	VERIFY(compare_weak_order_fallback(x7, x1)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x7, x2)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x7, x3)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x7, x4)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x7, x5)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x7, x6)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x7, x7)  == weak_ordering::equivalent);
	VERIFY(compare_weak_order_fallback(x7, x8)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x7, x9)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x7, x10) == weak_ordering::greater);

	VERIFY(compare_weak_order_fallback(x8, x1)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x8, x2)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x8, x3)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x8, x4)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x8, x5)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x8, x6)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x8, x7)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x8, x8)  == weak_ordering::equivalent);
	VERIFY(compare_weak_order_fallback(x8, x9)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x8, x10) == weak_ordering::greater);

	VERIFY(compare_weak_order_fallback(x9, x1)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x9, x2)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x9, x3)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x9, x4)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x9, x5)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x9, x6)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x9, x7)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x9, x8)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x9, x9)  == weak_ordering::equivalent);
	VERIFY(compare_weak_order_fallback(x9, x10) == weak_ordering::greater);

	VERIFY(compare_weak_order_fallback(x10, x1)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x10, x2)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x10, x3)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x10, x4)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x10, x5)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x10, x6)  == weak_ordering::greater);
	VERIFY(compare_weak_order_fallback(x10, x7)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x10, x8)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x10, x9)  == weak_ordering::less);
	VERIFY(compare_weak_order_fallback(x10, x10) == weak_ordering::equivalent);

	return true;
}

#undef VERIFY

GTEST_TEST(CompareTest, CompareWeakOrderFallbackTest)
{
#if defined(HAMON_COMPARE_USE_INLINE_VARIABLES)
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(test01());
#else
	EXPECT_TRUE(test01());
#endif
}

}	// namespace compare_weak_order_fallback_test

}	// namespace hamon_compare_test
