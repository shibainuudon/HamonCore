/**
 *	@file	unit_test_cmath_cosh.cpp
 *
 *	@brief	cosh のテスト
 */

#include <hamon/cmath/cosh.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace cosh_test
{

static_assert(hamon::is_same<float,       decltype(hamon::cosh(0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::coshf(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::cosh(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::cosh(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::cosh(0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::coshl(0.0l))>::value, "");

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
void CoshTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(10.06766199577, (double)hamon::cosh(T(-3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 6.13228947966, (double)hamon::cosh(T(-2.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.76219569108, (double)hamon::cosh(T(-2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.35240961524, (double)hamon::cosh(T(-1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.54308063482, (double)hamon::cosh(T(-1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.12762596521, (double)hamon::cosh(T(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, (double)hamon::cosh(T(-0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, (double)hamon::cosh(T( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.12762596521, (double)hamon::cosh(T( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.54308063482, (double)hamon::cosh(T( 1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.35240961524, (double)hamon::cosh(T( 1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.76219569108, (double)hamon::cosh(T( 2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 6.13228947966, (double)hamon::cosh(T( 2.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(10.06766199577, (double)hamon::cosh(T( 3.0)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.0, hamon::cosh(T(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 1.0, hamon::cosh(T(-0.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::cosh(+inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::cosh(-inf));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::cosh(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::cosh(-nan)));
}

template <typename T>
void CoshTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.00000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(10.06766199577, (double)hamon::cosh(T(-3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.76219569108, (double)hamon::cosh(T(-2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.54308063482, (double)hamon::cosh(T(-1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, (double)hamon::cosh(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.54308063482, (double)hamon::cosh(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.76219569108, (double)hamon::cosh(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(10.06766199577, (double)hamon::cosh(T( 3)), error);
}

template <typename T>
void CoshTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.00000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000, (double)hamon::cosh(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.54308063482, (double)hamon::cosh(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.76219569108, (double)hamon::cosh(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(10.06766199577, (double)hamon::cosh(T( 3)), error);
}

GTEST_TEST(CMathTest, CoshTest)
{
	CoshTestFloat<float>();
	CoshTestFloat<double>();
	CoshTestFloat<long double>();

	CoshTestSignedInt<int>();
//	CoshTestSignedInt<signed char>();
	CoshTestSignedInt<short>();
//	CoshTestSignedInt<long>();
	CoshTestSignedInt<long long>();

	CoshTestUnsignedInt<unsigned int>();
	CoshTestUnsignedInt<unsigned char>();
//	CoshTestUnsignedInt<unsigned short>();
	CoshTestUnsignedInt<unsigned long>();
//	CoshTestUnsignedInt<unsigned long long>();
}

}	// namespace cosh_test

}	// namespace hamon_cmath_test
