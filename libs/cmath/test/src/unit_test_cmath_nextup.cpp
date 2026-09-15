/**
 *	@file	unit_test_cmath_nextup.cpp
 *
 *	@brief	nextup のテスト
 */

#include <hamon/cmath/nextup.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace nextup_test
{

static_assert(hamon::is_same<float,       decltype(hamon::nextup(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::nextup(0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::nextup(0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::nextup(0   ))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::nextupf(0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::nextupl(0.0l))>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX14_CONSTEXPR bool test(T x, int count)
{
	for (int i = 0; i < count; ++i)
	{
		T y = hamon::nextup(x);
		VERIFY(x < y);
		x = y;
	}

	return true;
}

template <typename T>
void NextupTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto max = hamon::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto min = hamon::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto lowest = hamon::numeric_limits<T>::lowest();
	HAMON_CXX11_CONSTEXPR auto denorm_min = hamon::numeric_limits<T>::denorm_min();

	// x が正の有限の最大値の場合、正の無限大を返す
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::nextup(max) == +inf);

	// x が正の無限大の場合、 x を返す
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::nextup(+inf) == +inf);

	// x が負の無限大の場合、 有限の最小値を返す
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::nextup(-inf) == lowest);

	// x が ±0 の場合、正の最小の表現可能な値 (正の最小の非正規化数) を返す
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::nextup(T(-0.0)) == denorm_min);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::nextup(T(+0.0)) == denorm_min);

	// x が負の最小の表現可能な値 (絶対値が最小の負数) の場合、 -0 を返す
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::iszero (hamon::nextup(-denorm_min)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::signbit(hamon::nextup(-denorm_min)));

	// x が NaN の場合、 NaN を返す
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::nextup(+nan)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::nextup(-nan)));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(denorm_min, 100));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(-denorm_min, 100));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(max, 1));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(min, 100));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(-min, 100));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(lowest, 100));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(T(+0.0), 100));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(T(-0.0), 100));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(T(+0.1), 100));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(T(-0.1), 100));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(T(+0.5), 100));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(T(-0.5), 100));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(T(+1.0), 100));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(T(-1.0), 100));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(T(+2.0), 100));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(T(-2.0), 100));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(T(+10.1), 100));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(T(-10.1), 100));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(+inf == hamon::nextup(+inf));
}

GTEST_TEST(CMathTest, NextupTest)
{
	NextupTestFloat<float>();
	NextupTestFloat<double>();
//	NextupTestFloat<long double>();
}

}	// namespace nextup_test

}	// namespace hamon_cmath_test
