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
static_assert(hamon::is_same<float,       decltype(hamon::acosf(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::acos(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::acos(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::acos(0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::acosl(0.0l))>::value, "");

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
void AcosTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto eps = hamon::numeric_limits<T>::epsilon();

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(3.141592653590, (double)hamon::acos(T(-1.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.418858405776, (double)hamon::acos(T(-0.75)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.094395102393, (double)hamon::acos(T(-0.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.823476581937, (double)hamon::acos(T(-0.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.570796326795, (double)hamon::acos(T( 0.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.318116071653, (double)hamon::acos(T( 0.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.047197551197, (double)hamon::acos(T( 0.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.722734247813, (double)hamon::acos(T( 0.75)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.000000000000, (double)hamon::acos(T( 1.00)), error);

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
	HAMON_CXX11_CONSTEXPR double error = 0.000000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(3.141592653590, hamon::acos(T(-1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.570796326795, hamon::acos(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.000000000000, hamon::acos(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::acos(T( 2))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::acos(T(-2))));
}

template <typename T>
void AcosTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.000000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.570796326795, hamon::acos(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.000000000000, hamon::acos(T( 1)), error);
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
