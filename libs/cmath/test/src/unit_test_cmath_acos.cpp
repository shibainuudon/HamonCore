/**
 *	@file	unit_test_cmath_acos.cpp
 *
 *	@brief	acos のテスト
 */

#include <hamon/cmath/acos.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace acos_test
{

static_assert(hamon::is_same<float,       decltype(hamon::acos(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::acos(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::acos(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::acos(0.0l))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::acosf(0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::acosl(0.0l))>::value, "");

template <typename T>
void AcosTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto eps = hamon::numeric_limits<T>::epsilon();

	HAMON_CXX11_CONSTEXPR double error = hamon::is_same<T, float>::value ? 1e-6 : 1e-15;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(3.1415926535897932384626433832795028841971693993751, (double)hamon::acos(T(-1.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.4188584057763776272842660306381695221719509129507, (double)hamon::acos(T(-0.75)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.0943951023931954923084289221863352561314462662501, (double)hamon::acos(T(-0.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.8234765819369752727169791286334624143507784327844, (double)hamon::acos(T(-0.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.5707963267948966192313216916397514420985846996876, (double)hamon::acos(T( 0.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.3181160716528179657456642546460404698463909665907, (double)hamon::acos(T( 0.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.047197551196597746154214461093167628065723133125,  (double)hamon::acos(T( 0.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.7227342478134156111783773526413333620252184864244, (double)hamon::acos(T( 0.75)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0000000000000000000000000000000000000000000000000, (double)hamon::acos(T( 1.00)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0, hamon::acos(T(+1.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::acos(T(+1.0) + eps)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::acos(T(-1.0) - eps)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::acos(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::acos(-nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::acos(+inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::acos(-inf)));
}

template <typename T>
void AcosTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 1e-30;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(3.1415926535897932384626433832795028841971693993751, hamon::acos(T(-1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.5707963267948966192313216916397514420985846996876, hamon::acos(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0000000000000000000000000000000000000000000000000, hamon::acos(T( 1)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::acos(T( 2))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::acos(T(-2))));
}

template <typename T>
void AcosTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 1e-30;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.5707963267948966192313216916397514420985846996876, hamon::acos(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0000000000000000000000000000000000000000000000000, hamon::acos(T( 1)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::acos(T( 2))));
}

GTEST_TEST(CMathTest, AcosTest)
{
	AcosTestFloat<float>();
	AcosTestFloat<double>();
	AcosTestFloat<long double>();

	AcosTestSignedInt<int>();
	AcosTestSignedInt<signed char>();
//	AcosTestSignedInt<short>();
	AcosTestSignedInt<long>();
//	AcosTestSignedInt<long long>();

	AcosTestUnsignedInt<unsigned int>();
//	AcosTestUnsignedInt<unsigned char>();
	AcosTestUnsignedInt<unsigned short>();
//	AcosTestUnsignedInt<unsigned long>();
	AcosTestUnsignedInt<unsigned long long>();
}

}	// namespace acos_test

}	// namespace hamon_cmath_test
