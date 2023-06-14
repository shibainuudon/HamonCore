/**
 *	@file	unit_test_cmath_atan.cpp
 *
 *	@brief	atan のテスト
 */

#include <hamon/cmath/atan.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/numbers.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace atan_test
{

static_assert(hamon::is_same<float,       decltype(hamon::atan(0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::atanf(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::atan(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::atan(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::atan(0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::atanl(0.0l))>::value, "");

template <typename T>
double get_error();

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<float>()
{
	return 0.000001;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<double>()
{
	return 0.000000000001;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<long double>()
{
	return 0.000000000001;
}

template <typename T>
void AtanTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.5507989928217, (double)hamon::atan(T(-50.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.1902899496825, (double)hamon::atan(T( -2.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.7853981633974, (double)hamon::atan(T( -1.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.6435011087932, (double)hamon::atan(T( -0.75)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.4636476090008, (double)hamon::atan(T( -0.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.2449786631268, (double)hamon::atan(T( -0.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000, (double)hamon::atan(T(  0.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.2449786631268, (double)hamon::atan(T(  0.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.4636476090008, (double)hamon::atan(T(  0.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.6435011087932, (double)hamon::atan(T(  0.75)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.7853981633974, (double)hamon::atan(T(  1.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.1902899496825, (double)hamon::atan(T(  2.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.5507989928217, (double)hamon::atan(T( 50.00)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::atan(T(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::atan(T(-0.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( hamon::numbers::pi_fn<double>() / 2, (double)hamon::atan(+inf), 0.000001);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-hamon::numbers::pi_fn<double>() / 2, (double)hamon::atan(-inf), 0.000001);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::atan(-nan)));
}

template <typename T>
void AtanTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.000000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000, hamon::atan(T(   0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.7853981633974, hamon::atan(T(   1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.1071487177941, hamon::atan(T(   2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.4711276743037, hamon::atan(T(  10)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.5607966601082, hamon::atan(T( 100)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.7853981633974, hamon::atan(T(  -1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.1071487177941, hamon::atan(T(  -2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.4711276743037, hamon::atan(T( -10)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.5607966601082, hamon::atan(T(-100)), error);
}

template <typename T>
void AtanTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.000000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0000000000000, hamon::atan(T(  0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.7853981633974, hamon::atan(T(  1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.1071487177941, hamon::atan(T(  2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.4711276743037, hamon::atan(T( 10)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.5607966601082, hamon::atan(T(100)), error);
}

GTEST_TEST(CMathTest, AtanTest)
{
	AtanTestFloat<float>();
	AtanTestFloat<double>();
	AtanTestFloat<long double>();

	AtanTestSignedInt<int>();
//	AtanTestSignedInt<signed char>();
	AtanTestSignedInt<short>();
//	AtanTestSignedInt<long>();
	AtanTestSignedInt<long long>();

	AtanTestUnsignedInt<unsigned int>();
	AtanTestUnsignedInt<unsigned char>();
//	AtanTestUnsignedInt<unsigned short>();
	AtanTestUnsignedInt<unsigned long>();
//	AtanTestUnsignedInt<unsigned long long>();
}

}	// namespace atan_test

}	// namespace hamon_cmath_test
