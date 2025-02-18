/**
 *	@file	unit_test_cmath_beta.cpp
 *
 *	@brief	beta のテスト
 */

#include <hamon/cmath/beta.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/abs.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace beta_test
{

static_assert(hamon::is_same<float,       decltype(hamon::beta(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::beta(0.0f, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::beta(0.0f, 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::beta(0.0f, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::beta(0.0 , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::beta(0.0 , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::beta(0.0 , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::beta(0.0 , 0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::beta(0.0l, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::beta(0.0l, 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::beta(0.0l, 0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::beta(0.0l, 0   ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::beta(0   , 0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::beta(0   , 0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::beta(0   , 0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::beta(0   , 0   ))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::betaf(0.0f, 0.0f))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::betal(0.0l, 0.0l))>::value, "");

template <typename T1, typename T2>
void BetaTest(double error)
{
	using Promoted = hamon::float_promote_t<T1, T2>;
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<Promoted>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto min = hamon::numeric_limits<Promoted>::min();

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::beta(nan, nan)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::beta(nan, T2(1))));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::beta(T1(1), nan)));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::beta(T1(0), T2(0))));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::beta(T1(0), T2(1))));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::beta(T1(1), T2(0))));

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::beta(T1(-1), T2(-1))));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::beta(T1(-1), T2( 1))));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::beta(T1( 1), T2(-1))));

	struct testcase
	{
		double expected;
		T1 x;
		T2 y;
	};

	static testcase const testcases[] =
	{
		{1.0825088224469029e-06, 10, 10},
		{4.9925087406346778e-09, 10, 20},
		{1.5729567312509485e-10, 10, 30},
		{1.2168673582561288e-11, 10, 40},
		{1.5916380099863291e-12, 10, 50},
		{2.9408957938463963e-13, 10, 60},
		{6.9411637980691676e-14, 10, 70},
		{1.9665612972502651e-14, 10, 80},
		{6.4187824828154399e-15, 10, 90},
		{2.3455339739604842e-15, 10, 100},

		{4.9925087406346778e-09, 20, 10},
		{7.2544445519248436e-13, 20, 20},
		{1.7681885473062028e-15, 20, 30},
		{1.7891885039182335e-17, 20, 40},
		{4.3240677875623635e-19, 20, 50},
		{1.8857342309689053e-20, 20, 60},
		{1.2609804003539998e-21, 20, 70},
		{1.1660809542079041e-22, 20, 80},
		{1.3907944279729071e-23, 20, 90},
		{2.0365059099917614e-24, 20, 100},

		{1.5729567312509485e-10, 30, 10},
		{1.7681885473062028e-15, 30, 20},
		{5.6370779640482451e-19, 30, 30},
		{1.0539424603796547e-21, 30, 40},
		{6.0118197777273843e-24, 30, 50},
		{7.4279528553260153e-26, 30, 60},
		{1.6212207780604767e-27, 30, 70},
		{5.4783729715317616e-29, 30, 80},
		{2.6183005659681346e-30, 30, 90},
		{1.6587948222122229e-31, 30, 100},

		{1.2168673582561288e-11, 40, 10},
		{1.7891885039182335e-17, 40, 20},
		{1.0539424603796547e-21, 40, 30},
		{4.6508509140090659e-25, 40, 40},
		{7.5161712118557728e-28, 40, 50},
		{3.0311331979886071e-30, 40, 60},
		{2.4175035070466313e-32, 40, 70},
		{3.2734839142758369e-34, 40, 80},
		{6.7690629601315579e-36, 40, 90},
		{1.9797337118810115e-37, 40, 100},

		{1.5916380099863291e-12, 50, 10},
		{4.3240677875623635e-19, 50, 20},
		{6.0118197777273843e-24, 50, 30},
		{7.5161712118557728e-28, 50, 40},
		{3.9646612085674138e-31, 50, 50},
		{5.8425643906418403e-34, 50, 60},
		{1.8672362180783552e-36, 50, 70},
		{1.0939382296458963e-38, 50, 80},
		{1.0442781609879874e-40, 50, 90},
		{1.4904121110954370e-42, 50, 100},

		{2.9408957938463963e-13, 60, 10},
		{1.8857342309689053e-20, 60, 20},
		{7.4279528553260153e-26, 60, 30},
		{3.0311331979886071e-30, 60, 40},
		{5.8425643906418403e-34, 60, 50},
		{3.4501231469782229e-37, 60, 60},
		{4.7706855386086599e-40, 60, 70},
		{1.2902663809721126e-42, 60, 80},
		{6.0105571058570508e-45, 60, 90},
		{4.3922898898347209e-47, 60, 100},

		{6.9411637980691676e-14, 70, 10},
		{1.2609804003539998e-21, 70, 20},
		{1.6212207780604767e-27, 70, 30},
		{2.4175035070466313e-32, 70, 40},
		{1.8672362180783552e-36, 70, 50},
		{4.7706855386086599e-40, 70, 60},
		{3.0453137143482908e-43, 70, 70},
		{4.0192274082013779e-46, 70, 80},
		{9.5865870063501807e-49, 70, 90},
		{3.7409127305819802e-51, 70, 100},

		{1.9665612972502651e-14, 80, 10},
		{1.1660809542079041e-22, 80, 20},
		{5.4783729715317616e-29, 80, 30},
		{3.2734839142758369e-34, 80, 40},
		{1.0939382296458963e-38, 80, 50},
		{1.2902663809721126e-42, 80, 60},
		{4.0192274082013779e-46, 80, 70},
		{2.7160590828669411e-49, 80, 80},
		{3.4593773902125368e-52, 80, 90},
//		{7.4807039968503468e-55, 80, 100},

		{6.4187824828154399e-15, 90, 10},
		{1.3907944279729071e-23, 90, 20},
		{2.6183005659681346e-30, 90, 30},
		{6.7690629601315579e-36, 90, 40},
		{1.0442781609879874e-40, 90, 50},
		{6.0105571058570508e-45, 90, 60},
		{9.5865870063501807e-49, 90, 70},
		{3.4593773902125368e-52, 90, 80},
//		{2.4416737907558036e-55, 90, 90},
//		{3.0238531916564250e-58, 90, 100},

		{2.3455339739604842e-15, 100, 10},
		{2.0365059099917614e-24, 100, 20},
		{1.6587948222122229e-31, 100, 30},
		{1.9797337118810115e-37, 100, 40},
		{1.4904121110954370e-42, 100, 50},
		{4.3922898898347209e-47, 100, 60},
		{3.7409127305819802e-51, 100, 70},
//		{7.4807039968503468e-55, 100, 80},
//		{3.0238531916564250e-58, 100, 90},
//		{2.2087606931991849e-61, 100, 100},
	};

	for (auto const& data : testcases)
	{
		auto const x = data.x;
		auto const y = data.y;
		auto const r = hamon::beta(x, y);

		if (data.expected < min)
		{
			EXPECT_LT(r, min);
		}
		else
		{
			double tole = hamon::abs(data.expected) * error;
			EXPECT_NEAR(data.expected, (double)r, tole);
		}

		// B(x, y) = B(y, x)
		EXPECT_EQ(hamon::beta(x, y), hamon::beta(y, x));
	}
}

GTEST_TEST(CMathTest, BetaTest)
{
	BetaTest<float,       float>      (0.0001);
	BetaTest<float,       double>     (0.000000000001);
	BetaTest<float,       long double>(0.000000000001);
	BetaTest<float,       int>        (0.000000000001);
	BetaTest<double,      float>      (0.000000000001);
	BetaTest<double,      double>     (0.000000000001);
	BetaTest<double,      long double>(0.000000000001);
	BetaTest<double,      int>        (0.000000000001);
	BetaTest<long double, float>      (0.000000000001);
	BetaTest<long double, double>     (0.000000000001);
	BetaTest<long double, long double>(0.000000000001);
	BetaTest<long double, int>        (0.000000000001);
	BetaTest<int,         float>      (0.000000000001);
	BetaTest<int,         double>     (0.000000000001);
	BetaTest<int,         long double>(0.000000000001);
	BetaTest<int,         int>        (0.000000000001);

	HAMON_CXX11_CONSTEXPR auto nanf = hamon::numeric_limits<float>::quiet_NaN();
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::betaf(nanf, nanf)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::betaf(nanf, 1.0f)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::betaf(1.0f, nanf)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::betaf(0.0f, 0.0f)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::betaf(0.0f, 1.0f)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::betaf(1.0f, 0.0f)));

	HAMON_CXX11_CONSTEXPR auto nanl = hamon::numeric_limits<long double>::quiet_NaN();
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::betal(nanl, nanl)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::betal(nanl, 1.0l)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::betal(1.0l, nanl)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::betal(0.0l, 0.0l)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::betal(0.0l, 1.0l)));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::betal(1.0l, 0.0l)));
}

}	// namespace beta_test

}	// namespace hamon_cmath_test
