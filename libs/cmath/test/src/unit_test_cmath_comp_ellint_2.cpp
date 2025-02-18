/**
 *	@file	unit_test_cmath_comp_ellint_2.cpp
 *
 *	@brief	comp_ellint_2 のテスト
 */

#include <hamon/cmath/comp_ellint_2.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/abs.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace comp_ellint_2_test
{

static_assert(hamon::is_same<float,       decltype(hamon::comp_ellint_2(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::comp_ellint_2(0.0))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::comp_ellint_2(0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::comp_ellint_2(0))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::comp_ellint_2f(0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::comp_ellint_2l(0.0l))>::value, "");

template <typename T>
void CompEllint2TestFloat(double error)
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto max = hamon::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto lowest = hamon::numeric_limits<T>::lowest();
	HAMON_CXX11_CONSTEXPR auto eps = hamon::numeric_limits<T>::epsilon();

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::comp_ellint_2(nan)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::comp_ellint_2(T( 1) + eps)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::comp_ellint_2(T(-1) - eps)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::comp_ellint_2(max)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::comp_ellint_2(lowest)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::comp_ellint_2(+inf)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::comp_ellint_2(-inf)));

	struct testcase
	{
		double expected;
		T k;
	};

	static testcase const testcases[] =
	{
		{1.0000000000000000, T(-1.0)},
		{1.1716970527816142, T(-0.9)},
		{1.2763499431699064, T(-0.8)},
		{1.3556611355719554, T(-0.7)},
		{1.4180833944487243, T(-0.6)},
		{1.4674622093394272, T(-0.5)},
		{1.5059416123600404, T(-0.4)},
		{1.5348334649232491, T(-0.3)},
		{1.5549685462425293, T(-0.2)},
		{1.5668619420216683, T(-0.1)},
		{1.5707963267948966, T( 0.0)},
		{1.5668619420216683, T( 0.1)},
		{1.5549685462425293, T( 0.2)},
		{1.5348334649232491, T( 0.3)},
		{1.5059416123600402, T( 0.4)},
		{1.4674622093394272, T( 0.5)},
		{1.4180833944487241, T( 0.6)},
		{1.3556611355719554, T( 0.7)},
		{1.2763499431699064, T( 0.8)},
		{1.1716970527816140, T( 0.9)},
		{1.0000000000000000, T( 1.0)},
	};

	for (auto const& data : testcases)
	{
		auto const r = hamon::comp_ellint_2(data.k);

		{
			double tole = hamon::abs(data.expected) * error;
			EXPECT_NEAR(data.expected, (double)r, tole);
		}
	}
}

template <typename T>
void CompEllint2TestInt()
{
	HAMON_CXX11_CONSTEXPR double error = 0.00000000000001;

	HAMON_CXX14_CONSTEXPR_EXPECT_EQ  (1.0000000000000000, hamon::comp_ellint_2(T(-1)));
	HAMON_CXX14_CONSTEXPR_EXPECT_NEAR(1.5707963267948966, hamon::comp_ellint_2(T( 0)), error);
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ  (1.0000000000000000, hamon::comp_ellint_2(T( 1)));
}

GTEST_TEST(CMathTest, CompEllint2Test)
{
	CompEllint2TestFloat<float>      (0.000001);
	CompEllint2TestFloat<double>     (0.00000000000001);
	CompEllint2TestFloat<long double>(0.00000000000001);

	CompEllint2TestInt<int>();
	CompEllint2TestInt<short>();

	HAMON_CXX11_CONSTEXPR auto nanf = hamon::numeric_limits<float>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto epsf = hamon::numeric_limits<float>::epsilon();
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::comp_ellint_2f(nanf)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::comp_ellint_2f( 1.0f + epsf)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::comp_ellint_2f(-1.0f - epsf)));

	HAMON_CXX11_CONSTEXPR auto nanl = hamon::numeric_limits<long double>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto epsl = hamon::numeric_limits<long double>::epsilon();
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::comp_ellint_2l(nanl)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::comp_ellint_2l( 1.0l + epsl)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::comp_ellint_2l(-1.0l - epsl)));
}

}	// namespace comp_ellint_2_test

}	// namespace hamon_cmath_test
