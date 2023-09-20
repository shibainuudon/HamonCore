/**
 *	@file	unit_test_cmath_asinh.cpp
 *
 *	@brief	asinh のテスト
 */

#include <hamon/cmath/asinh.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace asinh_test
{

static_assert(hamon::is_same<float,       decltype(hamon::asinh(0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::asinhf(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::asinh(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::asinh(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::asinh(0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::asinhl(0.0l))>::value, "");

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
	return 1e-12;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<long double>()
{
	return 1e-12;
}

template <typename T>
void AsinhTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.8184464592320, (double)hamon::asinh(T(-3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.6472311463710, (double)hamon::asinh(T(-2.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.4436354751788, (double)hamon::asinh(T(-2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.1947632172871, (double)hamon::asinh(T(-1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.8813735870195, (double)hamon::asinh(T(-1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.4812118250596, (double)hamon::asinh(T(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000, (double)hamon::asinh(T( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.4812118250596, (double)hamon::asinh(T( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.8813735870195, (double)hamon::asinh(T( 1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.1947632172871, (double)hamon::asinh(T( 1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.4436354751788, (double)hamon::asinh(T( 2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.6472311463710, (double)hamon::asinh(T( 2.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.8184464592320, (double)hamon::asinh(T( 3.0)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0, hamon::asinh(T(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0, hamon::asinh(T(-0.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::asinh(+inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::asinh(-inf));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::asinh(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::asinh(-nan)));
}

template <typename T>
void AsinhTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.000000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.8184464592320, (double)hamon::asinh(T(-3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.4436354751788, (double)hamon::asinh(T(-2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.8813735870195, (double)hamon::asinh(T(-1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000, (double)hamon::asinh(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.8813735870195, (double)hamon::asinh(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.4436354751788, (double)hamon::asinh(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.8184464592320, (double)hamon::asinh(T( 3)), error);
}

template <typename T>
void AsinhTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.000000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000, (double)hamon::asinh(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.8813735870195, (double)hamon::asinh(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.4436354751788, (double)hamon::asinh(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.8184464592320, (double)hamon::asinh(T( 3)), error);
}

GTEST_TEST(CMathTest, AsinhTest)
{
	AsinhTestFloat<float>();
	AsinhTestFloat<double>();
	AsinhTestFloat<long double>();

	AsinhTestSignedInt<int>();
	AsinhTestSignedInt<signed char>();
//	AsinhTestSignedInt<short>();
	AsinhTestSignedInt<long>();
//	AsinhTestSignedInt<long long>();

	AsinhTestUnsignedInt<unsigned int>();
//	AsinhTestUnsignedInt<unsigned char>();
	AsinhTestUnsignedInt<unsigned short>();
//	AsinhTestUnsignedInt<unsigned long>();
	AsinhTestUnsignedInt<unsigned long long>();
}

}	// namespace asinh_test

}	// namespace hamon_cmath_test
