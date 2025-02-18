/**
 *	@file	unit_test_cmath_legendre.cpp
 *
 *	@brief	legendre のテスト
 */

#include <hamon/cmath/legendre.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace legendre_test
{

static_assert(hamon::is_same<float,       decltype(hamon::legendre(0u, 0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::legendref(0u, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::legendre(0u, 0.0))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::legendre(0u, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::legendrel(0u, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::legendre(0u, 0))>::value, "");

template <typename T>
void LegendreTest(double error)
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto min = hamon::numeric_limits<T>::lowest();
	HAMON_CXX11_CONSTEXPR auto max = hamon::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto eps = hamon::numeric_limits<T>::epsilon();

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::legendre(0, nan)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::legendre(1, nan)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::legendre(2, T( 1) + eps)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::legendre(3, T(-1) - eps)));

	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(T( 1.0), hamon::legendre( 0, T(-1)));
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(T( 1.0), hamon::legendre( 0, T( 0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(T( 1.0), hamon::legendre( 0, T( 1)));
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(T(-1.0), hamon::legendre( 1, T(-1)));
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(T( 0.0), hamon::legendre( 1, T( 0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(T( 1.0), hamon::legendre( 1, T( 1)));
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(T( 1.0), hamon::legendre( 2, T(-1)));
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(T(-0.5), hamon::legendre( 2, T( 0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(T( 1.0), hamon::legendre( 2, T( 1)));
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(T(-1.0), hamon::legendre( 5, T(-1)));
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(T( 0.0), hamon::legendre( 5, T( 0)));
	HAMON_CXX14_CONSTEXPR_EXPECT_EQ(T( 1.0), hamon::legendre( 5, T( 1)));

	struct testcase
	{
		double expected;
		unsigned int n;
		T x;
	};

	static testcase const testcases[] =
	{
		{ 1.0000000000000000, 0, T(-1.0)},
		{ 1.0000000000000000, 0, T(-0.9)},
		{ 1.0000000000000000, 0, T(-0.8)},
		{ 1.0000000000000000, 0, T(-0.7)},
		{ 1.0000000000000000, 0, T(-0.6)},
		{ 1.0000000000000000, 0, T(-0.5)},
		{ 1.0000000000000000, 0, T(-0.4)},
		{ 1.0000000000000000, 0, T(-0.3)},
		{ 1.0000000000000000, 0, T(-0.2)},
		{ 1.0000000000000000, 0, T(-0.1)},
		{ 1.0000000000000000, 0, T( 0.0)},
		{ 1.0000000000000000, 0, T( 0.1)},
		{ 1.0000000000000000, 0, T( 0.2)},
		{ 1.0000000000000000, 0, T( 0.3)},
		{ 1.0000000000000000, 0, T( 0.4)},
		{ 1.0000000000000000, 0, T( 0.5)},
		{ 1.0000000000000000, 0, T( 0.6)},
		{ 1.0000000000000000, 0, T( 0.7)},
		{ 1.0000000000000000, 0, T( 0.8)},
		{ 1.0000000000000000, 0, T( 0.9)},
		{ 1.0000000000000000, 0, T( 1.0)},

		{-1.0000000000000000, 1, T(-1.0)},
		{-0.9000000000000000, 1, T(-0.9)},
		{-0.8000000000000000, 1, T(-0.8)},
		{-0.7000000000000000, 1, T(-0.7)},
		{-0.6000000000000000, 1, T(-0.6)},
		{-0.5000000000000000, 1, T(-0.5)},
		{-0.4000000000000000, 1, T(-0.4)},
		{-0.3000000000000000, 1, T(-0.3)},
		{-0.2000000000000000, 1, T(-0.2)},
		{-0.1000000000000000, 1, T(-0.1)},
		{ 0.0000000000000000, 1, T( 0.0)},
		{ 0.1000000000000000, 1, T( 0.1)},
		{ 0.2000000000000000, 1, T( 0.2)},
		{ 0.3000000000000000, 1, T( 0.3)},
		{ 0.4000000000000000, 1, T( 0.4)},
		{ 0.5000000000000000, 1, T( 0.5)},
		{ 0.6000000000000000, 1, T( 0.6)},
		{ 0.7000000000000000, 1, T( 0.7)},
		{ 0.8000000000000000, 1, T( 0.8)},
		{ 0.9000000000000000, 1, T( 0.9)},
		{ 1.0000000000000000, 1, T( 1.0)},

		{ 1.0000000000000000, 2, T(-1.0)},
		{ 0.7150000000000000, 2, T(-0.9)},
		{ 0.4600000000000001, 2, T(-0.8)},
		{ 0.2349999999999998, 2, T(-0.7)},
		{ 0.0399999999999999, 2, T(-0.6)},
		{-0.1250000000000000, 2, T(-0.5)},
		{-0.2600000000000001, 2, T(-0.4)},
		{-0.3650000000000000, 2, T(-0.3)},
		{-0.4400000000000000, 2, T(-0.2)},
		{-0.4849999999999999, 2, T(-0.1)},
		{-0.5000000000000000, 2, T( 0.0)},
		{-0.4849999999999999, 2, T( 0.1)},
		{-0.4399999999999998, 2, T( 0.2)},
		{-0.3649999999999999, 2, T( 0.3)},
		{-0.2599999999999998, 2, T( 0.4)},
		{-0.1250000000000000, 2, T( 0.5)},
		{ 0.0400000000000001, 2, T( 0.6)},
		{ 0.2350000000000003, 2, T( 0.7)},
		{ 0.4600000000000001, 2, T( 0.8)},
		{ 0.7150000000000003, 2, T( 0.9)},
		{ 1.0000000000000000, 2, T( 1.0)},

		{-1.0000000000000000, 5, T(-1.0)},
		{ 0.0411412500000000, 5, T(-0.9)},
		{ 0.3995199999999999, 5, T(-0.8)},
		{ 0.3651987499999999, 5, T(-0.7)},
		{ 0.1526399999999999, 5, T(-0.6)},
		{-0.0898437500000000, 5, T(-0.5)},
		{-0.2706400000000001, 5, T(-0.4)},
		{-0.3453862499999999, 5, T(-0.3)},
		{-0.3075199999999999, 5, T(-0.2)},
		{-0.1788287499999999, 5, T(-0.1)},
		{ 0.0000000000000000, 5, T( 0.0)},
		{ 0.1788287500000001, 5, T( 0.1)},
		{ 0.3075200000000001, 5, T( 0.2)},
		{ 0.3453862500000000, 5, T( 0.3)},
		{ 0.2706399999999998, 5, T( 0.4)},
		{ 0.0898437500000000, 5, T( 0.5)},
		{-0.1526400000000001, 5, T( 0.6)},
		{-0.3651987500000002, 5, T( 0.7)},
		{-0.3995199999999999, 5, T( 0.8)},
		{-0.0411412499999991, 5, T( 0.9)},
		{ 1.0000000000000000, 5, T( 1.0)},

		{ 1.0000000000000000, 10, T(-1.0)},
		{-0.2631456178558596, 10, T(-0.9)},
		{ 0.3005297956000000, 10, T(-0.8)},
		{ 0.0858057955316403, 10, T(-0.7)},
		{-0.2436627456000000, 10, T(-0.6)},
		{-0.1882286071777343, 10, T(-0.5)},
		{ 0.0968390644000002, 10, T(-0.4)},
		{ 0.2514763495160156, 10, T(-0.3)},
		{ 0.1290720255999998, 10, T(-0.2)},
		{-0.1221249973871094, 10, T(-0.1)},
		{-0.2460937500000000, 10, T( 0.0)},
		{-0.1221249973871092, 10, T( 0.1)},
		{ 0.1290720256000004, 10, T( 0.2)},
		{ 0.2514763495160156, 10, T( 0.3)},
		{ 0.0968390643999996, 10, T( 0.4)},
		{-0.1882286071777343, 10, T( 0.5)},
		{-0.2436627455999998, 10, T( 0.6)},
		{ 0.0858057955316412, 10, T( 0.7)},
		{ 0.3005297956000000, 10, T( 0.8)},
		{-0.2631456178558601, 10, T( 0.9)},
		{ 1.0000000000000000, 10, T( 1.0)},

		{ 1.0000000000000000, 20, T(-1.0)},
		{-0.1493082353098483, 20, T(-0.9)},
		{ 0.2242046054174134, 20, T(-0.8)},
		{-0.2045739446383417, 20, T(-0.7)},
		{ 0.1591675291009810, 20, T(-0.6)},
		{-0.0483583810673735, 20, T(-0.5)},
		{-0.1015926155862811, 20, T(-0.4)},
		{ 0.1802871594799804, 20, T(-0.3)},
		{-0.0980421943445947, 20, T(-0.2)},
		{-0.0820771309445276, 20, T(-0.1)},
		{ 0.1761970520019531, 20, T( 0.0)},
		{-0.0820771309445280, 20, T( 0.1)},
		{-0.0980421943445940, 20, T( 0.2)},
		{ 0.1802871594799804, 20, T( 0.3)},
		{-0.1015926155862819, 20, T( 0.4)},
		{-0.0483583810673735, 20, T( 0.5)},
		{ 0.1591675291009807, 20, T( 0.6)},
		{-0.2045739446383413, 20, T( 0.7)},
		{ 0.2242046054174134, 20, T( 0.8)},
		{-0.1493082353098475, 20, T( 0.9)},
		{ 1.0000000000000000, 20, T( 1.0)},

		{ 1.0000000000000000, 50, T(-1.0)},
		{-0.1700376599438367, 50, T(-0.9)},
		{ 0.1387973734509311, 50, T(-0.8)},
		{-0.0145727316458928, 50, T(-0.7)},
		{-0.0588607988440020, 50, T(-0.6)},
		{-0.0310590992396098, 50, T(-0.5)},
		{ 0.0415690333818246, 50, T(-0.4)},
		{ 0.1091105157471479, 50, T(-0.3)},
		{ 0.0834322722041974, 50, T(-0.2)},
		{-0.0382058126613136, 50, T(-0.1)},
		{-0.1122751726592170, 50, T( 0.0)},
		{-0.0382058126613141, 50, T( 0.1)},
		{ 0.0834322722041965, 50, T( 0.2)},
		{ 0.1091105157471479, 50, T( 0.3)},
		{ 0.0415690333818260, 50, T( 0.4)},
		{-0.0310590992396098, 50, T( 0.5)},
		{-0.0588607988440014, 50, T( 0.6)},
		{-0.0145727316458907, 50, T( 0.7)},
		{ 0.1387973734509311, 50, T( 0.8)},
		{-0.1700376599438367, 50, T( 0.9)},
		{ 1.0000000000000000, 50, T( 1.0)},

		{ 1.0000000000000000, 100, T(-1.0)},
		{ 0.1022658205587189, 100, T(-0.9)},
		{ 0.0508611679135842, 100, T(-0.8)},
		{-0.0771325071997786, 100, T(-0.7)},
		{-0.0237470239051331, 100, T(-0.6)},
		{-0.0605180259618611, 100, T(-0.5)},
		{-0.0722582021256850, 100, T(-0.4)},
		{ 0.0571273922028010, 100, T(-0.3)},
		{ 0.0146818353556597, 100, T(-0.2)},
		{-0.0638950984347502, 100, T(-0.1)},
		{ 0.0795892373871787, 100, T( 0.0)},
		{-0.0638950984347497, 100, T( 0.1)},
		{ 0.0146818353556578, 100, T( 0.2)},
		{ 0.0571273922028015, 100, T( 0.3)},
		{-0.0722582021256840, 100, T( 0.4)},
		{-0.0605180259618611, 100, T( 0.5)},
		{-0.0237470239051342, 100, T( 0.6)},
		{-0.0771325071997805, 100, T( 0.7)},
		{ 0.0508611679135842, 100, T( 0.8)},
		{ 0.1022658205587206, 100, T( 0.9)},
		{ 1.0000000000000000, 100, T( 1.0)},
	};

	for (auto const& data : testcases)
	{
		auto const r = hamon::legendre(data.n, data.x);

		if (data.expected > max)
		{
			EXPECT_EQ(+inf, r);
		}
		else if (data.expected < min)
		{
			EXPECT_EQ(-inf, r);
		}
		else
		{
			double tole = hamon::abs(data.expected) * error;
			EXPECT_NEAR(data.expected, (double)r, tole);
		}
	}
}

template <typename T>
void LegendreTestInt(double error)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::legendre(0, T( 2))));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::legendre(1, T(-2))));

	struct testcase
	{
		double expected;
		unsigned int n;
		T x;
	};

	static testcase const testcases[] =
	{
		{ 1.0000000000000000, 0, -1},
		{ 1.0000000000000000, 0,  0},
		{ 1.0000000000000000, 0,  1},

		{-1.0000000000000000, 1, -1},
		{ 0.0000000000000000, 1,  0},
		{ 1.0000000000000000, 1,  1},

		{ 1.0000000000000000, 2, -1},
		{-0.5000000000000000, 2,  0},
		{ 1.0000000000000000, 2,  1},

		{-1.0000000000000000, 5, -1},
		{ 0.0000000000000000, 5,  0},
		{ 1.0000000000000000, 5,  1},

		{ 1.0000000000000000, 10, -1},
		{-0.2460937500000000, 10,  0},
		{ 1.0000000000000000, 10,  1},

		{ 1.0000000000000000, 20, -1},
		{ 0.1761970520019531, 20,  0},
		{ 1.0000000000000000, 20,  1},

		{ 1.0000000000000000, 50, -1},
		{-0.1122751726592170, 50,  0},
		{ 1.0000000000000000, 50,  1},

		{ 1.0000000000000000, 100, -1},
		{ 0.0795892373871787, 100,  0},
		{ 1.0000000000000000, 100,  1},
	};

	for (auto const& data : testcases)
	{
		auto const r = hamon::legendre(data.n, data.x);

		{
			double tole = hamon::abs(data.expected) * error;
			EXPECT_NEAR(data.expected, (double)r, tole);
		}
	}
}

GTEST_TEST(CMathTest, LegendreTest)
{
	LegendreTest<float>      (0.001);
	LegendreTest<double>     (0.00000000001);
	LegendreTest<long double>(0.00000000001);

	LegendreTestInt<int>(0.00000000001);

	HAMON_CXX11_CONSTEXPR auto nanf = hamon::numeric_limits<float>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto epsf = hamon::numeric_limits<float>::epsilon();
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::legendref(0, nanf)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::legendref(1, nanf)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::legendref(2,  1.0f + epsf)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::legendref(3, -1.0f - epsf)));

	HAMON_CXX11_CONSTEXPR auto nanl = hamon::numeric_limits<long double>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto epsl = hamon::numeric_limits<long double>::epsilon();
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::legendrel(0, nanl)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::legendrel(1, nanl)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::legendrel(2,  1.0l + epsl)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::legendrel(3, -1.0l - epsl)));
}

}	// namespace legendre_test

}	// namespace hamon_cmath_test
