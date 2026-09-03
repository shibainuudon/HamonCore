/**
 *	@file	unit_test_cmath_asinh.cpp
 *
 *	@brief	asinh のテスト
 */

#include <hamon/cmath/asinh.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/fabs.hpp>	// HAMON_CXX11_CONSTEXPR_EXPECT_NEAR
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace asinh_test
{

static_assert(hamon::is_same<float,       decltype(hamon::asinh(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::asinh(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::asinh(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::asinh(0.0l))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::asinhf(0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::asinhl(0.0l))>::value, "");

template <typename T>
void AsinhTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR double error = hamon::is_same<T, float>::value ? 1e-6 : 1e-12;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.818446459232066823483698963560708993786253942768, (double)hamon::asinh(T(-3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.647231146371095710624858610443619663504414430193, (double)hamon::asinh(T(-2.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.443635475178810342493276740273105269405553003157, (double)hamon::asinh(T(-2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.194763217287109304111930828519090523536162075153, (double)hamon::asinh(T(-1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.881373587019543025232609324979792309028160328261, (double)hamon::asinh(T(-1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.481211825059603447497758913424368423135184334385, (double)hamon::asinh(T(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.000000000000000000000000000000000000000000000000, (double)hamon::asinh(T( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.481211825059603447497758913424368423135184334385, (double)hamon::asinh(T( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.881373587019543025232609324979792309028160328261, (double)hamon::asinh(T( 1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.194763217287109304111930828519090523536162075153, (double)hamon::asinh(T( 1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.443635475178810342493276740273105269405553003157, (double)hamon::asinh(T( 2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.647231146371095710624858610443619663504414430193, (double)hamon::asinh(T( 2.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.818446459232066823483698963560708993786253942768, (double)hamon::asinh(T( 3.0)), error);

	// if the argument is ±0 or ±∞, it is returned unmodified.
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::asinh(T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::asinh(T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::asinh(T(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::signbit(hamon::asinh(T(-0.0))));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::asinh(+inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::asinh(-inf));

	// if the argument is NaN, NaN is returned.
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::asinh(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::asinh(-nan)));
}

template <typename T>
void AsinhTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 1e-12;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.818446459232066823483698963560708993786253942768, (double)hamon::asinh(T(-3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.443635475178810342493276740273105269405553003157, (double)hamon::asinh(T(-2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.881373587019543025232609324979792309028160328261, (double)hamon::asinh(T(-1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.000000000000000000000000000000000000000000000000, (double)hamon::asinh(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.881373587019543025232609324979792309028160328261, (double)hamon::asinh(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.443635475178810342493276740273105269405553003157, (double)hamon::asinh(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.818446459232066823483698963560708993786253942768, (double)hamon::asinh(T( 3)), error);
}

template <typename T>
void AsinhTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 1e-12;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.000000000000000000000000000000000000000000000000, (double)hamon::asinh(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.881373587019543025232609324979792309028160328261, (double)hamon::asinh(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.443635475178810342493276740273105269405553003157, (double)hamon::asinh(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.818446459232066823483698963560708993786253942768, (double)hamon::asinh(T( 3)), error);
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
