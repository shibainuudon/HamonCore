/**
 *	@file	unit_test_cmath_asin.cpp
 *
 *	@brief	asin のテスト
 */

#include <hamon/cmath/asin.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace asin_test
{

static_assert(hamon::is_same<float,       decltype(hamon::asin(0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::asinf(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::asin(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::asin(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::asin(0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::asinl(0.0l))>::value, "");

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
void AsinTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto eps = std::numeric_limits<T>::epsilon();

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.5707963267949, (double)hamon::asin(T(-1.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.8480620789814, (double)hamon::asin(T(-0.75)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.5235987755983, (double)hamon::asin(T(-0.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.2526802551420, (double)hamon::asin(T(-0.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000, (double)hamon::asin(T( 0.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.2526802551420, (double)hamon::asin(T( 0.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.5235987755983, (double)hamon::asin(T( 0.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.8480620789814, (double)hamon::asin(T( 0.75)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.5707963267949, (double)hamon::asin(T( 1.00)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0, hamon::asin(T(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0.0, hamon::asin(T(-0.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::asin(T(+1.0) + eps)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::asin(T(-1.0) - eps)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::asin(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::asin(-nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::asin(+inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::asin(-inf)));
}

template <typename T>
void AsinTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.000000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000, hamon::asin(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.5707963267949, hamon::asin(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.5707963267949, hamon::asin(T(-1)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::asin(T( 2))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::asin(T(-2))));
}

template <typename T>
void AsinTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.000000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0000000000000, hamon::asin(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.5707963267949, hamon::asin(T( 1)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::asin(T( 2))));
}

GTEST_TEST(CMathTest, AsinTest)
{
	AsinTestFloat<float>();
	AsinTestFloat<double>();
	AsinTestFloat<long double>();

	AsinTestSignedInt<int>();
//	AsinTestSignedInt<signed char>();
	AsinTestSignedInt<short>();
//	AsinTestSignedInt<long>();
	AsinTestSignedInt<long long>();

	AsinTestUnsignedInt<unsigned int>();
	AsinTestUnsignedInt<unsigned char>();
//	AsinTestUnsignedInt<unsigned short>();
	AsinTestUnsignedInt<unsigned long>();
//	AsinTestUnsignedInt<unsigned long long>();
}

}	// namespace asin_test

}	// namespace hamon_cmath_test
