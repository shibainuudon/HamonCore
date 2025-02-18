/**
 *	@file	unit_test_cmath_comp_ellint_1.cpp
 *
 *	@brief	comp_ellint_1 のテスト
 */

#include <hamon/cmath/comp_ellint_1.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/abs.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace comp_ellint_1_test
{

static_assert(hamon::is_same<float,       decltype(hamon::comp_ellint_1(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::comp_ellint_1(0.0))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::comp_ellint_1(0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::comp_ellint_1(0))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::comp_ellint_1f(0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::comp_ellint_1l(0.0l))>::value, "");

template <typename T>
void CompEllint1TestFloat(double error)
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto max = hamon::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto lowest = hamon::numeric_limits<T>::lowest();
	HAMON_CXX11_CONSTEXPR auto eps = hamon::numeric_limits<T>::epsilon();

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::comp_ellint_1(nan)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::comp_ellint_1(T( 1) + eps)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::comp_ellint_1(T(-1) - eps)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::comp_ellint_1(max)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::comp_ellint_1(lowest)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::comp_ellint_1(+inf)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::comp_ellint_1(-inf)));

	struct testcase
	{
		double expected;
		T k;
	};
	HAMON_CXX11_CONSTEXPR auto infd = hamon::numeric_limits<double>::infinity();

	static testcase const testcases[] =
	{
		{infd,               T(-1.0)},
		{2.2805491384227703, T(-0.9)},
		{1.9953027776647294, T(-0.8)},
		{1.8456939983747234, T(-0.7)},
		{1.7507538029157526, T(-0.6)},
		{1.6857503548125961, T(-0.5)},
		{1.6399998658645112, T(-0.4)},
		{1.6080486199305128, T(-0.3)},
		{1.5868678474541662, T(-0.2)},
		{1.5747455615173560, T(-0.1)},
		{1.5707963267948966, T( 0.0)},
		{1.5747455615173560, T( 0.1)},
		{1.5868678474541662, T( 0.2)},
		{1.6080486199305128, T( 0.3)},
		{1.6399998658645112, T( 0.4)},
		{1.6857503548125961, T( 0.5)},
		{1.7507538029157526, T( 0.6)},
		{1.8456939983747238, T( 0.7)},
		{1.9953027776647294, T( 0.8)},
		{2.2805491384227707, T( 0.9)},
		{infd,               T( 1.0)},
	};

	for (auto const& data : testcases)
	{
		auto const r = hamon::comp_ellint_1(data.k);

		if (hamon::isinf(data.expected))
		{
			EXPECT_EQ(data.expected, r);
		}
		else
		{
			double tole = hamon::abs(data.expected) * error;
			EXPECT_NEAR(data.expected, (double)r, tole);
		}
	}
}

template <typename T>
void CompEllint1TestInt()
{
	HAMON_CXX11_CONSTEXPR double error = 0.000000000000001;

	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<double>::infinity();

	HAMON_CXX14_CONSTEXPR_EXPECT_EQ  (inf,                hamon::comp_ellint_1(T(-1)));
	HAMON_CXX14_CONSTEXPR_EXPECT_NEAR(1.5707963267948966, hamon::comp_ellint_1(T( 0)), error);
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ  (inf,                hamon::comp_ellint_1(T( 1)));
}

GTEST_TEST(CMathTest, CompEllint1Test)
{
	CompEllint1TestFloat<float>      (0.000001);
	CompEllint1TestFloat<double>     (0.000000000000001);
	CompEllint1TestFloat<long double>(0.000000000000001);

	CompEllint1TestInt<int>();
	CompEllint1TestInt<short>();

	HAMON_CXX11_CONSTEXPR auto nanf = hamon::numeric_limits<float>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto epsf = hamon::numeric_limits<float>::epsilon();
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::comp_ellint_1f(nanf)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::comp_ellint_1f( 1.0f + epsf)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::comp_ellint_1f(-1.0f - epsf)));

	HAMON_CXX11_CONSTEXPR auto nanl = hamon::numeric_limits<long double>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto epsl = hamon::numeric_limits<long double>::epsilon();
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::comp_ellint_1l(nanl)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::comp_ellint_1l( 1.0l + epsl)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::comp_ellint_1l(-1.0l - epsl)));
}

}	// namespace comp_ellint_1_test

}	// namespace hamon_cmath_test
