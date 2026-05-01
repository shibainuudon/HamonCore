/**
 *	@file	unit_test_cmath_sqrt.cpp
 *
 *	@brief	sqrt のテスト
 */

#include <hamon/cmath/sqrt.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace sqrt_test
{

static_assert(hamon::is_same<float,       decltype(hamon::sqrt(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::sqrt(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::sqrt(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::sqrt(0.0l))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::sqrtf(0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::sqrtl(0.0l))>::value, "");

template <typename T>
void SqrtTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto eps = hamon::numeric_limits<T>::epsilon();

	HAMON_CXX11_CONSTEXPR double error = hamon::is_same<T, float>::value ? 1e-6 : 1e-14;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000000000000000000000000000000000000000000, (double)hamon::sqrt(T(  0.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.50000000000000000000000000000000000000000000000000, (double)hamon::sqrt(T(  0.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.70710678118654752440084436210484903928483593768847, (double)hamon::sqrt(T(  0.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.86602540378443864676372317075293618347140262690519, (double)hamon::sqrt(T(  0.75)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000000000000000000000000000000000000000000, (double)hamon::sqrt(T(  1.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.1180339887498948482045868343656381177203091798058,  (double)hamon::sqrt(T(  1.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.2247448713915890490986420373529456959829737403283,  (double)hamon::sqrt(T(  1.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.3228756555322952952508078768196302128551295915412,  (double)hamon::sqrt(T(  1.75)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.4142135623730950488016887242096980785696718753770,  (double)hamon::sqrt(T(  2.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.5000000000000000000000000000000000000000000000000,  (double)hamon::sqrt(T(  2.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.5811388300841896659994467722163592668597775696626,  (double)hamon::sqrt(T(  2.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.6583123951776999245574663683353433419635442727947,  (double)hamon::sqrt(T(  2.75)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.7320508075688772935274463415058723669428052538104,  (double)hamon::sqrt(T(  3.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(10.000000000000000000000000000000000000000000000000,   (double)hamon::sqrt(T(100.000)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(11.111075555498666484621494041182192341186325190118,   (double)hamon::sqrt(T(123.456)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1000.00000000000, (double)hamon::sqrt(T(1000000.00)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::sqrt(T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::sqrt(T(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::sqrt(T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::sqrt(T(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::sqrt(+inf));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::sqrt(-eps)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::sqrt(T(-1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::sqrt(-inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::sqrt(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::sqrt(-nan)));
}

template <typename T>
void SqrtTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 1e-15;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000000000000000000000000000000000000000, hamon::sqrt(T(  0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0000000000000000000000000000000000000000000000000, hamon::sqrt(T(  1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.4142135623730950488016887242096980785696718753770, hamon::sqrt(T(  2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.7320508075688772935274463415058723669428052538104, hamon::sqrt(T(  3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.0000000000000000000000000000000000000000000000000, hamon::sqrt(T(  4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.2360679774997896964091736687312762354406183596115, hamon::sqrt(T(  5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.4494897427831780981972840747058913919659474806567, hamon::sqrt(T(  6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.6457513110645905905016157536392604257102591830825, hamon::sqrt(T(  7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.8284271247461900976033774484193961571393437507539, hamon::sqrt(T(  8)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.0000000000000000000000000000000000000000000000000, hamon::sqrt(T(  9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.1622776601683793319988935444327185337195551393252, hamon::sqrt(T( 10)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(10.0000000000000000000000000000000000000000000000000, hamon::sqrt(T(100)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::sqrt(T(-1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::sqrt(T(-2))));
}

template <typename T>
void SqrtTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 1e-15;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0000000000000000000000000000000000000000000000000, hamon::sqrt(T(  0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0000000000000000000000000000000000000000000000000, hamon::sqrt(T(  1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.4142135623730950488016887242096980785696718753770, hamon::sqrt(T(  2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.7320508075688772935274463415058723669428052538104, hamon::sqrt(T(  3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.0000000000000000000000000000000000000000000000000, hamon::sqrt(T(  4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.2360679774997896964091736687312762354406183596115, hamon::sqrt(T(  5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.4494897427831780981972840747058913919659474806567, hamon::sqrt(T(  6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.6457513110645905905016157536392604257102591830825, hamon::sqrt(T(  7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.8284271247461900976033774484193961571393437507539, hamon::sqrt(T(  8)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.0000000000000000000000000000000000000000000000000, hamon::sqrt(T(  9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.1622776601683793319988935444327185337195551393252, hamon::sqrt(T( 10)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(10.0000000000000000000000000000000000000000000000000, hamon::sqrt(T(100)), error);
}

GTEST_TEST(CMathTest, SqrtTest)
{
	SqrtTestFloat<float>();
	SqrtTestFloat<double>();
	SqrtTestFloat<long double>();

//	SqrtTestSignedInt<int>();
	SqrtTestSignedInt<signed char>();
//	SqrtTestSignedInt<short>();
	SqrtTestSignedInt<long>();
//	SqrtTestSignedInt<long long>();

	SqrtTestUnsignedInt<unsigned int>();
//	SqrtTestUnsignedInt<unsigned char>();
	SqrtTestUnsignedInt<unsigned short>();
//	SqrtTestUnsignedInt<unsigned long>();
	SqrtTestUnsignedInt<unsigned long long>();
}

}	// namespace sqrt_test

}	// namespace hamon_cmath_test
