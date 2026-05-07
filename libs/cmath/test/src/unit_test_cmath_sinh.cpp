/**
 *	@file	unit_test_cmath_sinh.cpp
 *
 *	@brief	sinh のテスト
 */

#include <hamon/cmath/sinh.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace sinh_test
{

static_assert(hamon::is_same<float,       decltype(hamon::sinh(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::sinh(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::sinh(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::sinh(0.0l))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::sinhf(0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::sinhl(0.0l))>::value, "");

template <typename T>
void SinhTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();

	HAMON_CXX11_CONSTEXPR double error = hamon::is_same<T, float>::value ? 1e-6 : 1e-11;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-10.017874927409901898974593619465828060178104123183, (double)hamon::sinh(T(-3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -6.050204481039787321450323638350403187672481834523, (double)hamon::sinh(T(-2.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -3.626860407847018767668213982801261704886342012321, (double)hamon::sinh(T(-2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -2.129279455094817496834387494677631648831789119504, (double)hamon::sinh(T(-1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -1.175201193643801456882381850595600815155717981334, (double)hamon::sinh(T(-1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -0.521095305493747361622425626411491559105928982611, (double)hamon::sinh(T(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.000000000000000000000000000000000000000000000000, (double)hamon::sinh(T( 0.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.521095305493747361622425626411491559105928982611, (double)hamon::sinh(T( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  1.175201193643801456882381850595600815155717981334, (double)hamon::sinh(T( 1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  2.129279455094817496834387494677631648831789119504, (double)hamon::sinh(T( 1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  3.626860407847018767668213982801261704886342012321, (double)hamon::sinh(T( 2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  6.050204481039787321450323638350403187672481834523, (double)hamon::sinh(T( 2.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 10.017874927409901898974593619465828060178104123183, (double)hamon::sinh(T( 3.0)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(+0.0), hamon::sinh(T(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-0.0), hamon::sinh(T(-0.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::sinh(+inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::sinh(-inf));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::sinh(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::sinh(-nan)));
}

template <typename T>
void SinhTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-10.017874927409901898974593619465828060178104123183, (double)hamon::sinh(T(-3)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -3.626860407847018767668213982801261704886342012321, (double)hamon::sinh(T(-2)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( -1.175201193643801456882381850595600815155717981334, (double)hamon::sinh(T(-1)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  0.000000000000000000000000000000000000000000000000, (double)hamon::sinh(T( 0)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  1.175201193643801456882381850595600815155717981334, (double)hamon::sinh(T( 1)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(  3.626860407847018767668213982801261704886342012321, (double)hamon::sinh(T( 2)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 10.017874927409901898974593619465828060178104123183, (double)hamon::sinh(T( 3)), 1e-11);
}

template <typename T>
void SinhTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.000000000000000000000000000000000000000000000000, (double)hamon::sinh(T( 0)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.175201193643801456882381850595600815155717981334, (double)hamon::sinh(T( 1)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.626860407847018767668213982801261704886342012321, (double)hamon::sinh(T( 2)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(10.017874927409901898974593619465828060178104123183, (double)hamon::sinh(T( 3)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(27.28991719712775244890827159079381858028941248553,  (double)hamon::sinh(T( 4)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(74.203210577788758977009471996064565599619409004426, (double)hamon::sinh(T( 5)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(201.71315737027922812498206768797873146900419543877, (double)hamon::sinh(T( 6)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(548.31612327324652237375611757601851157979633055454, (double)hamon::sinh(T( 7)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1490.4788257895501861158766390318814464474743141164, (double)hamon::sinh(T( 8)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(4051.5419020827899605152235958980346174888250078394, (double)hamon::sinh(T( 9)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(11013.232874703393377236524554846364402901451190319, (double)hamon::sinh(T(10)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(242582597.70489513795397660405149136535934930439451, (double)hamon::sinh(T(20)), 1e-11);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(5343237290762.2310734952342785825859808113744781574, (double)hamon::sinh(T(30)), 1e-3);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(117692633418509992.70394995537451740013025868098148, (double)hamon::sinh(T(40)), 1e+8);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2592352764293536232043.7266614667426924137344538544, (double)hamon::sinh(T(50)), 1e+16);
}

GTEST_TEST(CMathTest, SinhTest)
{
	SinhTestFloat<float>();
	SinhTestFloat<double>();
	SinhTestFloat<long double>();

	SinhTestSignedInt<int>();
//	SinhTestSignedInt<signed char>();
	SinhTestSignedInt<short>();
//	SinhTestSignedInt<long>();
	SinhTestSignedInt<long long>();

//	SinhTestUnsignedInt<unsigned int>();
	SinhTestUnsignedInt<unsigned char>();
//	SinhTestUnsignedInt<unsigned short>();
	SinhTestUnsignedInt<unsigned long>();
//	SinhTestUnsignedInt<unsigned long long>();
}

}	// namespace sinh_test

}	// namespace hamon_cmath_test
