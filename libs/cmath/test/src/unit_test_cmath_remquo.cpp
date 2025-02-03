/**
 *	@file	unit_test_cmath_remquo.cpp
 *
 *	@brief	remquo のテスト
 */

#include <hamon/cmath/remquo.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace remquo_test
{

static_assert(hamon::is_same<float,       decltype(hamon::remquo(0.0f, 0.0f, nullptr))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::remquof(0.0f, 0.0f, nullptr))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::remquo(0.0f, 0.0, nullptr))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::remquo(0.0f, 0.0l, nullptr))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::remquo(0.0f, 0, nullptr))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::remquo(0.0 , 0.0f, nullptr))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::remquo(0.0 , 0.0, nullptr))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::remquo(0.0 , 0.0l, nullptr))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::remquo(0.0 , 0, nullptr))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::remquo(0.0l, 0.0f, nullptr))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::remquo(0.0l, 0.0, nullptr))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::remquo(0.0l, 0.0l, nullptr))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::remquol(0.0l, 0.0l, nullptr))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::remquo(0.0l, 0, nullptr))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::remquo(0   , 0.0f, nullptr))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::remquo(0   , 0.0, nullptr))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::remquo(0   , 0.0l, nullptr))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::remquo(0   , 0, nullptr))>::value, "");

template <typename T1, typename T2, typename R>
HAMON_CXX14_CONSTEXPR bool RemquoTestImpl(R re_expect, int quo_expect, T1 x, T2 y)
{
	int quo = 0;
	auto re = hamon::remquo(x, y, &quo);
	return re == re_expect && quo == quo_expect;
}

template <typename T1, typename T2>
void RemquoTestFloat(void)
{
	using R = hamon::float_promote_t<T1, T2>;

	HAMON_CXX11_CONSTEXPR auto nan1 = hamon::numeric_limits<T1>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto nan2 = hamon::numeric_limits<T2>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf1 = hamon::numeric_limits<T1>::infinity();
	HAMON_CXX11_CONSTEXPR auto inf2 = hamon::numeric_limits<T2>::infinity();

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 1.0), 2, T1( 7.0), T2(3)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 1.5), 2, T1( 7.5), T2(3)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R(-1.0), 3, T1( 8.0), T2(3)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R(-0.5), 3, T1( 8.5), T2(3)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 0.0), 3, T1( 9.0), T2(3)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 0.5), 3, T1( 9.5), T2(3)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 1.0), 3, T1(10.0), T2(3)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R(-1.5), 4, T1(10.5), T2(3)));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 1.0), -2, T1( 7.0), T2(-3)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 1.5), -2, T1( 7.5), T2(-3)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R(-1.0), -3, T1( 8.0), T2(-3)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R(-0.5), -3, T1( 8.5), T2(-3)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 0.0), -3, T1( 9.0), T2(-3)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 0.5), -3, T1( 9.5), T2(-3)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 1.0), -3, T1(10.0), T2(-3)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R(-1.5), -4, T1(10.5), T2(-3)));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 0.5), -3, T1(- 7.0), T2(2.5)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 0.0), -3, T1(- 7.5), T2(2.5)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R(-0.5), -3, T1(- 8.0), T2(2.5)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R(-1.0), -3, T1(- 8.5), T2(2.5)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 1.0), -4, T1(- 9.0), T2(2.5)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 0.5), -4, T1(- 9.5), T2(2.5)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 0.0), -4, T1(-10.0), T2(2.5)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R(-0.5), -4, T1(-10.5), T2(2.5)));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 0.5), 3, T1(- 7.0), T2(-2.5)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 0.0), 3, T1(- 7.5), T2(-2.5)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R(-0.5), 3, T1(- 8.0), T2(-2.5)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R(-1.0), 3, T1(- 8.5), T2(-2.5)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 1.0), 4, T1(- 9.0), T2(-2.5)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 0.5), 4, T1(- 9.5), T2(-2.5)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 0.0), 4, T1(-10.0), T2(-2.5)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R(-0.5), 4, T1(-10.5), T2(-2.5)));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 1.0), 0, T1( 1.0), T2(5.0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 1.5), 0, T1( 1.5), T2(5.0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 2.0), 0, T1( 2.0), T2(5.0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 2.5), 0, T1( 2.5), T2(5.0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R(-2.0), 1, T1( 3.0), T2(5.0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R(-1.5), 1, T1( 3.5), T2(5.0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R(-1.0), 1, T1( 4.0), T2(5.0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R(-0.5), 1, T1( 4.5), T2(5.0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 0.0), 1, T1( 5.0), T2(5.0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 0.5), 1, T1( 5.5), T2(5.0)));

	int quo;

	//If x is ±∞ and y is not NaN, NaN is returned and FE_INVALID is raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remquo( inf1, T2( 1.0), &quo)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remquo(-inf1, T2( 1.0), &quo)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remquo( inf1, T2(-2.0), &quo)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remquo(-inf1, T2(-2.0), &quo)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remquo( inf1, T2( 0.0), &quo)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remquo(-inf1, T2( 0.0), &quo)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remquo( inf1, inf2, &quo)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remquo(-inf1, inf2, &quo)));

	//If y is ±0 and x is not NaN, NaN is returned and FE_INVALID is raised
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remquo(T1( 1.0), T2(+0.0), &quo)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remquo(T1( 1.0), T2(-0.0), &quo)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remquo(T1(-2.0), T2(+0.0), &quo)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remquo(T1(-2.0), T2(-0.0), &quo)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remquo(T1( 0.0), T2(+0.0), &quo)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remquo(T1( 0.0), T2(-0.0), &quo)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remquo(inf1,     T2(+0.0), &quo)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remquo(inf1,     T2(-0.0), &quo)));

	//If either argument is NaN, NaN is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remquo(nan1, T2(1.0), &quo)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remquo(nan1, T2(0.0), &quo)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remquo(T1(1.0), nan2, &quo)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remquo(inf1, nan2, &quo)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::remquo(nan1, nan2, &quo)));
}

template <typename T1, typename T2>
void RemquoTestInteger(void)
{
	using R = hamon::float_promote_t<T1, T2>;

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R(-1), 2, T1( 5), T2( 3)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 1),-2, T1(-5), T2( 3)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R(-1),-2, T1( 5), T2(-3)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 1), 2, T1(-5), T2(-3)));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 1), 2, T1( 5), T2( 2)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R(-1),-2, T1(-5), T2( 2)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 1),-2, T1( 5), T2(-2)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R(-1), 2, T1(-5), T2(-2)));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 0), 1, T1( 5), T2( 5)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R(-0),-1, T1(-5), T2( 5)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 0),-1, T1( 5), T2(-5)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R(-0), 1, T1(-5), T2(-5)));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 2), 0, T1( 2), T2( 5)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R(-2), 0, T1(-2), T2( 5)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R( 2), 0, T1( 2), T2(-5)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(RemquoTestImpl(R(-2), 0, T1(-2), T2(-5)));
}

GTEST_TEST(CMathTest, RemquoTest)
{
	RemquoTestFloat<float, float>();
	RemquoTestFloat<float, double>();
	RemquoTestFloat<double, double>();
	RemquoTestFloat<double, long double>();
	RemquoTestFloat<long double, long double>();
	RemquoTestFloat<long double, float>();

	RemquoTestInteger<int, int>();
	RemquoTestInteger<int, float>();
	RemquoTestInteger<int, double>();
	RemquoTestInteger<int, long long>();
	RemquoTestInteger<double, long long>();
	RemquoTestInteger<long double, long long>();
}

}	// namespace remquo_test

}	// namespace hamon_cmath_test
