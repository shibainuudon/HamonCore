/**
 *	@file	unit_test_cmath_expm1.cpp
 *
 *	@brief	expm1 のテスト
 */

#include <hamon/cmath/expm1.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace expm1_test
{

static_assert(hamon::is_same<float,       decltype(hamon::expm1(0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::expm1f(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::expm1(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::expm1(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::expm1(0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::expm1l(0.0l))>::value, "");

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
void Expm1TestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000, (double)hamon::expm1(T(+0.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000, (double)hamon::expm1(T(-0.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.2840254166877, (double)hamon::expm1(T( 0.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.6487212707001, (double)hamon::expm1(T( 0.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.1170000166127, (double)hamon::expm1(T( 0.75)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.7182818284590, (double)hamon::expm1(T( 1.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 6.3890560989306, (double)hamon::expm1(T( 2.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(19.0855369231876, (double)hamon::expm1(T( 3.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.2211992169285, (double)hamon::expm1(T(-0.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.3934693402873, (double)hamon::expm1(T(-0.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.5276334472589, (double)hamon::expm1(T(-0.75)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.6321205588285, (double)hamon::expm1(T(-1.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.8646647167633, (double)hamon::expm1(T(-2.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.9502129316321, (double)hamon::expm1(T(-3.00)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ   (-1.0,          hamon::expm1(-inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isinf  (hamon::expm1(+inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::expm1(+inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan  (hamon::expm1(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan  (hamon::expm1(-nan)));
}

template <typename T>
void Expm1TestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.000000000001;
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.8646647167633, hamon::expm1(T(-2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.6321205588285, hamon::expm1(T(-1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000, hamon::expm1(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.7182818284590, hamon::expm1(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 6.3890560989306, hamon::expm1(T( 2)), error);
}

template <typename T>
void Expm1TestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.000000000001;
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000, hamon::expm1(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.7182818284590, hamon::expm1(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 6.3890560989306, hamon::expm1(T( 2)), error);
}

GTEST_TEST(CMathTest, Expm1Test)
{
	Expm1TestFloat<float>();
	Expm1TestFloat<double>();
	Expm1TestFloat<long double>();

	Expm1TestSignedInt<int>();
//	Expm1TestSignedInt<signed char>();
	Expm1TestSignedInt<short>();
//	Expm1TestSignedInt<long>();
	Expm1TestSignedInt<long long>();

	Expm1TestUnsignedInt<unsigned int>();
	Expm1TestUnsignedInt<unsigned char>();
//	Expm1TestUnsignedInt<unsigned short>();
	Expm1TestUnsignedInt<unsigned long>();
//	Expm1TestUnsignedInt<unsigned long long>();
}

}	// namespace expm1_test

}	// namespace hamon_cmath_test
