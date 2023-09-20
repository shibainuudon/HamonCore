/**
 *	@file	unit_test_cmath_erf.cpp
 *
 *	@brief	erf のテスト
 */

#include <hamon/cmath/erf.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace erf_test
{

static_assert(hamon::is_same<float,       decltype(hamon::erf(0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::erff(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::erf(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::erf(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::erf(0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::erfl(0.0l))>::value, "");

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
	return 1e-14;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<long double>()
{
	return 1e-14;
}

template <typename T>
void ErfTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1.0), hamon::erf(+inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-1.0), hamon::erf(-inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::erf(nan)));

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.995322265018952734162069256367, (double)hamon::erf(T(-2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.992790429235257469948357539303, (double)hamon::erf(T(-1.9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.989090501635730714183732810756, (double)hamon::erf(T(-1.8)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.983790458590774563626242588122, (double)hamon::erf(T(-1.7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.976348383344644007774283447142, (double)hamon::erf(T(-1.6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.966105146475310727066976261646, (double)hamon::erf(T(-1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.952285119762648810516482691533, (double)hamon::erf(T(-1.4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.934007944940652436603893327504, (double)hamon::erf(T(-1.3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.910313978229635380238405775715, (double)hamon::erf(T(-1.2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.880205069574081699771867766322, (double)hamon::erf(T(-1.1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.842700792949714869341220635083, (double)hamon::erf(T(-1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.796908212422832128518724785142, (double)hamon::erf(T(-0.9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.742100964707660486167110586503, (double)hamon::erf(T(-0.8)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.677801193837418472975628809244, (double)hamon::erf(T(-0.7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.603856090847925922562622436057, (double)hamon::erf(T(-0.6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.520499877813046537682746653892, (double)hamon::erf(T(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.428392355046668455103603845320, (double)hamon::erf(T(-0.4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.328626759459127427638914047867, (double)hamon::erf(T(-0.3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.222702589210478454140139006800, (double)hamon::erf(T(-0.2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.112462916018284892203275071744, (double)hamon::erf(T(-0.1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.000000000000000000000000000000, (double)hamon::erf(T( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.112462916018284892203275071744, (double)hamon::erf(T( 0.1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.222702589210478454140139006800, (double)hamon::erf(T( 0.2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.328626759459127427638914047867, (double)hamon::erf(T( 0.3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.428392355046668455103603845320, (double)hamon::erf(T( 0.4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.520499877813046537682746653892, (double)hamon::erf(T( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.603856090847925922562622436057, (double)hamon::erf(T( 0.6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.677801193837418472975628809244, (double)hamon::erf(T( 0.7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.742100964707660486167110586503, (double)hamon::erf(T( 0.8)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.796908212422832128518724785142, (double)hamon::erf(T( 0.9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.842700792949714869341220635083, (double)hamon::erf(T( 1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.880205069574081699771867766322, (double)hamon::erf(T( 1.1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.910313978229635380238405775715, (double)hamon::erf(T( 1.2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.934007944940652436603893327504, (double)hamon::erf(T( 1.3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.952285119762648810516482691533, (double)hamon::erf(T( 1.4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.966105146475310727066976261646, (double)hamon::erf(T( 1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.976348383344644007774283447142, (double)hamon::erf(T( 1.6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.983790458590774563626242588122, (double)hamon::erf(T( 1.7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.989090501635730714183732810756, (double)hamon::erf(T( 1.8)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.992790429235257469948357539303, (double)hamon::erf(T( 1.9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.995322265018952734162069256367, (double)hamon::erf(T( 2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.997020533343667014496114983359, (double)hamon::erf(T( 2.1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.998137153702018108556548243971, (double)hamon::erf(T( 2.2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.998856823402643348534652540619, (double)hamon::erf(T( 2.3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.999311486103354921430255067829, (double)hamon::erf(T( 2.4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.999593047982555041060435784260, (double)hamon::erf(T( 2.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.999763965583470650796008996793, (double)hamon::erf(T( 2.6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.999865667260059475670859881280, (double)hamon::erf(T( 2.7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.999924986805334540975776754752, (double)hamon::erf(T( 2.8)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.999958902121900541164316132511, (double)hamon::erf(T( 2.9)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.999999999999998945267336534277, (double)hamon::erf(T( 5.67122)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0, (double)hamon::erf(T( 5.67123)), error);
}

template <typename T>
void ErfTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = get_error<double>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.000000000000000000000000000000, hamon::erf(T(-9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.999999999999999999999999999989, hamon::erf(T(-8)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.999999999999999999999958161744, hamon::erf(T(-7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.999999999999999978480263287501, hamon::erf(T(-6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.999999999998462540205571965150, hamon::erf(T(-5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.999999984582742099719981147840, hamon::erf(T(-4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.999977909503001414558627223870, hamon::erf(T(-3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.995322265018952734162069256367, hamon::erf(T(-2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.842700792949714869341220635083, hamon::erf(T(-1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.000000000000000000000000000000, hamon::erf(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.842700792949714869341220635083, hamon::erf(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.995322265018952734162069256367, hamon::erf(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.999977909503001414558627223870, hamon::erf(T( 3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.999999984582742099719981147840, hamon::erf(T( 4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.999999999998462540205571965150, hamon::erf(T( 5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.999999999999999978480263287501, hamon::erf(T( 6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.999999999999999999999958161744, hamon::erf(T( 7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.999999999999999999999999999989, hamon::erf(T( 8)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.000000000000000000000000000000, hamon::erf(T( 9)), error);
}

template <typename T>
void ErfTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = get_error<double>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.000000000000000000000000000000, hamon::erf(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.842700792949714869341220635083, hamon::erf(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.995322265018952734162069256367, hamon::erf(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.999977909503001414558627223870, hamon::erf(T( 3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.999999984582742099719981147840, hamon::erf(T( 4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.999999999998462540205571965150, hamon::erf(T( 5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.999999999999999978480263287501, hamon::erf(T( 6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.999999999999999999999958161744, hamon::erf(T( 7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.999999999999999999999999999989, hamon::erf(T( 8)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.000000000000000000000000000000, hamon::erf(T( 9)), error);
}

GTEST_TEST(CMathTest, ErfTest)
{
	ErfTestFloat<float>();
	ErfTestFloat<double>();
	ErfTestFloat<long double>();

	ErfTestSignedInt<signed int>();
//	ErfTestSignedInt<signed char>();
	ErfTestSignedInt<signed short>();
//	ErfTestSignedInt<signed long>();
	ErfTestSignedInt<signed long long>();

	ErfTestUnsignedInt<unsigned int>();
	ErfTestUnsignedInt<unsigned char>();
//	ErfTestUnsignedInt<unsigned short>();
	ErfTestUnsignedInt<unsigned long>();
//	ErfTestUnsignedInt<unsigned long long>();
}

}	// namespace erf_test

}	// namespace hamon_cmath_test
