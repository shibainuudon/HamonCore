/**
 *	@file	unit_test_cmath_sin.cpp
 *
 *	@brief	sin のテスト
 */

#include <hamon/cmath/sin.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/numbers.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace sin_test
{

static_assert(hamon::is_same<float,       decltype(hamon::sin(0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::sinf(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::sin(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::sin(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::sin(0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::sinl(0.0l))>::value, "");

template <typename T>
double get_error();

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<float>()
{
	return 0.00001;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<double>()
{
	return 0.00000000001;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<long double>()
{
	return 0.00000000001;
}

template <typename T>
void SinTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.35078322768961985, (double)hamon::sin(T(-3.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.14112000805986722, (double)hamon::sin(T(-3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.59847214410395649, (double)hamon::sin(T(-2.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.90929742682568169, (double)hamon::sin(T(-2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.99749498660405443, (double)hamon::sin(T(-1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.84147098480789650, (double)hamon::sin(T(-1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.47942553860420300, (double)hamon::sin(T(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000000000, (double)hamon::sin(T( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.47942553860420300, (double)hamon::sin(T( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.84147098480789650, (double)hamon::sin(T( 1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.99749498660405443, (double)hamon::sin(T( 1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.90929742682568169, (double)hamon::sin(T( 2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.59847214410395649, (double)hamon::sin(T( 2.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.14112000805986722, (double)hamon::sin(T( 3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.35078322768961985, (double)hamon::sin(T( 3.5)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0, (double)hamon::sin( hamon::numbers::pi_fn<T>()), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0, (double)hamon::sin(-hamon::numbers::pi_fn<T>()), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::sin(T(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::sin(T(-0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::sin(+inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::sin(-inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::sin(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::sin(-nan)));
}

template <typename T>
void SinTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.00000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000000000, hamon::sin(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.84147098480789650, hamon::sin(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.84147098480789650, hamon::sin(T(-1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.90929742682568169, hamon::sin(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.90929742682568169, hamon::sin(T(-2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.14112000805986722, hamon::sin(T( 3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.14112000805986722, hamon::sin(T(-3)), error);
}

template <typename T>
void SinTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.00000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.00000000000000000, hamon::sin(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.84147098480789650, hamon::sin(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.90929742682568169, hamon::sin(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.14112000805986722, hamon::sin(T( 3)), error);
}

GTEST_TEST(CMathTest, SinTest)
{
	SinTestFloat<float>();
	SinTestFloat<double>();
	SinTestFloat<long double>();

	SinTestSignedInt<int>();
//	SinTestSignedInt<signed char>();
	SinTestSignedInt<short>();
//	SinTestSignedInt<long>();
	SinTestSignedInt<long long>();

//	SinTestUnsignedInt<unsigned int>();
	SinTestUnsignedInt<unsigned char>();
//	SinTestUnsignedInt<unsigned short>();
	SinTestUnsignedInt<unsigned long>();
//	SinTestUnsignedInt<unsigned long long>();
}

}	// namespace sin_test

}	// namespace hamon_cmath_test
