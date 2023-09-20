/**
 *	@file	unit_test_cmath_sinh.cpp
 *
 *	@brief	sinh のテスト
 */

#include <hamon/cmath/sinh.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace sinh_test
{

static_assert(hamon::is_same<float,       decltype(hamon::sinh(0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::sinhf(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::sinh(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::sinh(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::sinh(0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::sinhl(0.0l))>::value, "");

template <typename T>
double get_error();

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<float>()
{
	return 1e-6;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<double>()
{
	return 1e-11;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<long double>()
{
	return 1e-11;
}

template <typename T>
void SinhTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-10.01787492740, (double)hamon::sinh(T(-3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -3.62686040785, (double)hamon::sinh(T(-2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -1.17520119364, (double)hamon::sinh(T(-1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.52109530549, (double)hamon::sinh(T(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.52109530549, (double)hamon::sinh(T( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  1.17520119364, (double)hamon::sinh(T( 1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  2.12927945509, (double)hamon::sinh(T( 1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  3.62686040785, (double)hamon::sinh(T( 2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 10.01787492740, (double)hamon::sinh(T( 3.0)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(+0.0), hamon::sinh(T(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-0.0), hamon::sinh(T(-0.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::sinh(+inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::sinh(-inf));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::sinh(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::sinh(-nan)));
}

template <typename T>
void SinhTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.00000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-10.01787492740, (double)hamon::sinh(T(-3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -3.62686040785, (double)hamon::sinh(T(-2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -1.17520119364, (double)hamon::sinh(T(-1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.00000000000, (double)hamon::sinh(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  1.17520119364, (double)hamon::sinh(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  3.62686040785, (double)hamon::sinh(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 10.01787492740, (double)hamon::sinh(T( 3)), error);
}

template <typename T>
void SinhTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.00000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.00000000000, (double)hamon::sinh(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  1.17520119364, (double)hamon::sinh(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  3.62686040785, (double)hamon::sinh(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 10.01787492740, (double)hamon::sinh(T( 3)), error);
}

GTEST_TEST(CMathTest, SinhTest)
{
	SinhTestFloat<float>();
	SinhTestFloat<double>();
	SinhTestFloat<long double>();

	SinhTestSignedInt<int>();
//	SinhTestSignedInt<signed char>();
	SinhTestSignedInt<short>();
//	SinhTestSignedInt<long>();
	SinhTestSignedInt<long long>();

//	SinhTestUnsignedInt<unsigned int>();
	SinhTestUnsignedInt<unsigned char>();
//	SinhTestUnsignedInt<unsigned short>();
	SinhTestUnsignedInt<unsigned long>();
//	SinhTestUnsignedInt<unsigned long long>();
}

}	// namespace sinh_test

}	// namespace hamon_cmath_test
