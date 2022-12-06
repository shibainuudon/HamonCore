/**
 *	@file	unit_test_cmath_exp.cpp
 *
 *	@brief	exp のテスト
 */

#include <hamon/cmath/exp.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace exp_test
{

static_assert(std::is_same<float,       decltype(hamon::exp(0.0f))>::value, "");
static_assert(std::is_same<float,       decltype(hamon::expf(0.0f))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::exp(0.0 ))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::exp(0   ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::exp(0.0l))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::expl(0.0l))>::value, "");

template <typename T>
void ExpTestFloat(double error)
{
	HAMON_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();

	EXPECT_NEAR( 1.0000000000000, (double)hamon::exp(T(+0.00)), error);
	EXPECT_NEAR( 1.0000000000000, (double)hamon::exp(T(-0.00)), error);
	EXPECT_NEAR( 1.2840254166877, (double)hamon::exp(T( 0.25)), error);
	EXPECT_NEAR( 1.6487212707001, (double)hamon::exp(T( 0.50)), error);
	EXPECT_NEAR( 2.1170000166127, (double)hamon::exp(T( 0.75)), error);
	EXPECT_NEAR( 2.7182818284590, (double)hamon::exp(T( 1.00)), error);
	EXPECT_NEAR( 7.3890560989306, (double)hamon::exp(T( 2.00)), error);
	EXPECT_NEAR(20.0855369231876, (double)hamon::exp(T( 3.00)), error);
	EXPECT_NEAR( 0.7788007830714, (double)hamon::exp(T(-0.25)), error);
	EXPECT_NEAR( 0.6065306597126, (double)hamon::exp(T(-0.50)), error);
	EXPECT_NEAR( 0.4723665527410, (double)hamon::exp(T(-0.75)), error);
	EXPECT_NEAR( 0.3678794411714, (double)hamon::exp(T(-1.00)), error);
	EXPECT_NEAR( 0.1353352832366, (double)hamon::exp(T(-2.00)), error);
	EXPECT_NEAR( 0.0497870683678, (double)hamon::exp(T(-3.00)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::exp(-inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::exp(-inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isinf  (hamon::exp(+inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::exp(+inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan  (hamon::exp(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan  (hamon::exp(-nan)));
}

template <typename T>
void ExpTestSignedInt(void)
{
	HAMON_CONSTEXPR double error = 0.000000000001;
	EXPECT_NEAR(0.1353352832366, hamon::exp(T(-2)), error);
	EXPECT_NEAR(0.3678794411714, hamon::exp(T(-1)), error);
	EXPECT_NEAR(1.0000000000000, hamon::exp(T( 0)), error);
	EXPECT_NEAR(2.7182818284590, hamon::exp(T( 1)), error);
	EXPECT_NEAR(7.3890560989306, hamon::exp(T( 2)), error);
}

template <typename T>
void ExpTestUnsignedInt(void)
{
	HAMON_CONSTEXPR double error = 0.000000000001;
	EXPECT_NEAR(1.0000000000000, hamon::exp(T( 0)), error);
	EXPECT_NEAR(2.7182818284590, hamon::exp(T( 1)), error);
	EXPECT_NEAR(7.3890560989306, hamon::exp(T( 2)), error);
}

GTEST_TEST(CMathTest, ExpTest)
{
	ExpTestFloat<float>(0.000001);
	ExpTestFloat<double>(0.000000000001);
	ExpTestFloat<long double>(0.000000000001);

	ExpTestSignedInt<int>();
//	ExpTestSignedInt<signed char>();
	ExpTestSignedInt<short>();
//	ExpTestSignedInt<long>();
	ExpTestSignedInt<long long>();

	ExpTestUnsignedInt<unsigned int>();
	ExpTestUnsignedInt<unsigned char>();
//	ExpTestUnsignedInt<unsigned short>();
	ExpTestUnsignedInt<unsigned long>();
//	ExpTestUnsignedInt<unsigned long long>();
}

}	// namespace exp_test

}	// namespace hamon_cmath_test
