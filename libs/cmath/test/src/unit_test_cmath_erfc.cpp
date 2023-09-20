/**
 *	@file	unit_test_cmath_erfc.cpp
 *
 *	@brief	erfc のテスト
 */

#include <hamon/cmath/erfc.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace erfc_test
{

static_assert(hamon::is_same<float,       decltype(hamon::erfc(0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::erfcf(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::erfc(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::erfc(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::erfc(0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::erfcl(0.0l))>::value, "");

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
	return 1e-15;
}

template <>
inline HAMON_CXX11_CONSTEXPR double get_error<long double>()
{
	return 1e-15;
}

template <typename T>
void ErfcTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0.0), hamon::erfc(+inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(2.0), hamon::erfc(-inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::erfc(nan)));

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.995322265018952734162069256367, (double)hamon::erfc(T(-2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.992790429235257469948357539303, (double)hamon::erfc(T(-1.9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.989090501635730714183732810756, (double)hamon::erfc(T(-1.8)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.983790458590774563626242588122, (double)hamon::erfc(T(-1.7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.976348383344644007774283447142, (double)hamon::erfc(T(-1.6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.966105146475310727066976261646, (double)hamon::erfc(T(-1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.952285119762648810516482691533, (double)hamon::erfc(T(-1.4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.934007944940652436603893327504, (double)hamon::erfc(T(-1.3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.910313978229635380238405775715, (double)hamon::erfc(T(-1.2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.880205069574081699771867766322, (double)hamon::erfc(T(-1.1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.842700792949714869341220635083, (double)hamon::erfc(T(-1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.796908212422832128518724785142, (double)hamon::erfc(T(-0.9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.742100964707660486167110586503, (double)hamon::erfc(T(-0.8)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.677801193837418472975628809244, (double)hamon::erfc(T(-0.7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.603856090847925922562622436057, (double)hamon::erfc(T(-0.6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.520499877813046537682746653892, (double)hamon::erfc(T(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.428392355046668455103603845320, (double)hamon::erfc(T(-0.4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.328626759459127427638914047867, (double)hamon::erfc(T(-0.3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.222702589210478454140139006800, (double)hamon::erfc(T(-0.2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.112462916018284892203275071744, (double)hamon::erfc(T(-0.1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.000000000000000000000000000000, (double)hamon::erfc(T( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.887537083981715107796724928256, (double)hamon::erfc(T( 0.1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.777297410789521545859860993200, (double)hamon::erfc(T( 0.2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.671373240540872572361085952133, (double)hamon::erfc(T( 0.3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.571607644953331544896396154680, (double)hamon::erfc(T( 0.4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.479500122186953462317253346108, (double)hamon::erfc(T( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.396143909152074077437377563943, (double)hamon::erfc(T( 0.6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.322198806162581527024371190756, (double)hamon::erfc(T( 0.7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.257899035292339513832889413497, (double)hamon::erfc(T( 0.8)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.203091787577167871481275214858, (double)hamon::erfc(T( 0.9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.157299207050285130658779364917, (double)hamon::erfc(T( 1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.119794930425918300228132233678, (double)hamon::erfc(T( 1.1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0896860217703646197615942242846, (double)hamon::erfc(T( 1.2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0659920550593475633961066724963, (double)hamon::erfc(T( 1.3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0477148802373511894835173084666, (double)hamon::erfc(T( 1.4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0338948535246892729330237383541, (double)hamon::erfc(T( 1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0236516166553559922257165528580, (double)hamon::erfc(T( 1.6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0162095414092254363737574118781, (double)hamon::erfc(T( 1.7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0109094983642692858162671892442, (double)hamon::erfc(T( 1.8)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.00720957076474253005164246069665, (double)hamon::erfc(T( 1.9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.00467773498104726583793074363275, (double)hamon::erfc(T( 2.0)), error);
}

template <typename T>
void ErfcTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = get_error<double>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.995322265018952734162069256367,  hamon::erfc(T(-2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.842700792949714869341220635083,  hamon::erfc(T(-1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.000000000000000000000000000000,  hamon::erfc(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.157299207050285130658779364917,  hamon::erfc(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.00467773498104726583793074363275, hamon::erfc(T( 2)), error);
}

template <typename T>
void ErfcTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = get_error<double>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.000000000000000000000000000000,    hamon::erfc(T( 0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.157299207050285130658779364917,    hamon::erfc(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.00467773498104726583793074363275,  hamon::erfc(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.20904969985854413727761295823e-5,  hamon::erfc(T( 3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.54172579002800188521596734869e-8,  hamon::erfc(T( 4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.53745979442803485018834348538e-12, hamon::erfc(T( 5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.15197367124989131165933503992e-17, hamon::erfc(T( 6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(4.1838256077794143986140102239e-23,  hamon::erfc(T( 7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.12242971729829270799678884432e-29, hamon::erfc(T( 8)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.000000000000000000000000000000,    hamon::erfc(T( 9)), error);
}

GTEST_TEST(CMathTest, ErfcTest)
{
	ErfcTestFloat<float>();
	ErfcTestFloat<double>();
	ErfcTestFloat<long double>();

	ErfcTestSignedInt<signed int>();
//	ErfcTestSignedInt<signed char>();
	ErfcTestSignedInt<signed short>();
//	ErfcTestSignedInt<signed long>();
	ErfcTestSignedInt<signed long long>();

	ErfcTestUnsignedInt<unsigned int>();
	ErfcTestUnsignedInt<unsigned char>();
//	ErfcTestUnsignedInt<unsigned short>();
	ErfcTestUnsignedInt<unsigned long>();
//	ErfcTestUnsignedInt<unsigned long long>();
}

}	// namespace erfc_test

}	// namespace hamon_cmath_test
