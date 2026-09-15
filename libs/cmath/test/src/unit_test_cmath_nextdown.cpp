/**
 *	@file	unit_test_cmath_nextdown.cpp
 *
 *	@brief	nextdown のテスト
 */

#include <hamon/cmath/nextdown.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "get_random_value.hpp"

#include <cmath>	// std::nextafter

namespace hamon_cmath_test
{

namespace nextdown_test
{

static_assert(hamon::is_same<float,       decltype(hamon::nextdown(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::nextdown(0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::nextdown(0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::nextdown(0   ))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::nextdownf(0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::nextdownl(0.0l))>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX14_CONSTEXPR bool test(T x)
{
	if (!hamon::is_constant_evaluated())
	{
		VERIFY(hamon::nextdown(x) == std::nextafter(x, -hamon::numeric_limits<T>::infinity()));
	}

	VERIFY(x > hamon::nextdown(x));

	return true;
}

#undef VERIFY

template <typename T>
void NextdownTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto max = hamon::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto min = hamon::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto lowest = hamon::numeric_limits<T>::lowest();
	HAMON_CXX11_CONSTEXPR auto denorm_min = hamon::numeric_limits<T>::denorm_min();

	// x が負の有限の最小値の場合、負の無限大を返す
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::nextdown(lowest) == -inf);

	// x が負の無限大の場合、 x を返す
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::nextdown(-inf) == -inf);

	// x が正の無限大の場合、 有限の最大値を返す
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::nextdown(+inf) == max);

	// x が ±0 の場合、負の絶対値が最小の表現可能な値 (絶対値が最小の負の非正規化数) を返す
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::nextdown(T(-0.0)) == -denorm_min);
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::nextdown(T(+0.0)) == -denorm_min);

	// x が正の最小の表現可能な値 (絶対値が最小の正数) の場合、 +0 を返す
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::iszero (hamon::nextdown(denorm_min)));
	HAMON_CXX14_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::nextdown(denorm_min)));

	// x が NaN の場合、 NaN を返す
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::nextdown(+nan)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::nextdown(-nan)));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(denorm_min));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(-denorm_min));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(max));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(min));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(-min));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(lowest));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(T(+0.0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(T(-0.0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(+inf));

	for (int i = 0; i < 100; ++i)
	{
		EXPECT_TRUE(test(get_random_value<T>()));
	}
	for (int i = 0; i < 100; ++i)
	{
		EXPECT_TRUE(test(get_random_value<T>(T(-1), T(1))));
	}
}

GTEST_TEST(CMathTest, NextdownTest)
{
	NextdownTestFloat<float>();
	NextdownTestFloat<double>();
	NextdownTestFloat<long double>();
}

}	// namespace nextdown_test

}	// namespace hamon_cmath_test
