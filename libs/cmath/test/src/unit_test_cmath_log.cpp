/**
 *	@file	unit_test_cmath_log.cpp
 *
 *	@brief	log のテスト
 */

#include <hamon/cmath/log.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/numbers.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace log_test
{

static_assert(std::is_same<float,       decltype(hamon::log(0.0f))>::value, "");
static_assert(std::is_same<float,       decltype(hamon::logf(0.0f))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::log(0.0 ))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::log(0   ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::log(0.0l))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::logl(0.0l))>::value, "");

template <typename T>
double log_error();

template <>
inline HAMON_CXX11_CONSTEXPR double log_error<float>()
{
	return 0.000001;
}

template <>
inline HAMON_CXX11_CONSTEXPR double log_error<double>()
{
	return 0.000000000001;
}

template <>
inline HAMON_CXX11_CONSTEXPR double log_error<long double>()
{
	return 0.000000000001;
}

template <typename T>
void LogTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto eps = std::numeric_limits<T>::epsilon();

	HAMON_CXX11_CONSTEXPR double error = log_error<T>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.38629436111989, (double)hamon::log(T(0.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.69314718055995, (double)hamon::log(T(0.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.28768207245178, (double)hamon::log(T(0.75)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.00000000000000, (double)hamon::log(T(1.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.22314355131421, (double)hamon::log(T(1.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.40546510810816, (double)hamon::log(T(1.50)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.69314718055994, (double)hamon::log(T(2.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.00000000000000, (double)hamon::log(hamon::numbers::e_fn<T>()),  error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.09861228866810, (double)hamon::log(T(3.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.38629436111989, (double)hamon::log(T(4.00)), error);

	//If the argument is ±0, -∞ is returned and FE_DIVBYZERO is raised.
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::log(T(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::log(T(-0.0)));

	//If the argument is 1, +0 is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::log(T(+1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::log(T(+1.0))));

	//If the argument is negative, NaN is returned and FE_INVALID is raised.
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log(T(-1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log(T(-2.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log(T( 0.0) - eps)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log(-inf)));

	//If the argument is +∞, +∞ is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::log(inf));

	//If the argument is NaN, NaN is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log( nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log(-nan)));
}

template <typename T>
void LogTestSignedInt(void)
{
	using R = hamon::float_promote_t<T>;
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<R>::infinity();

	HAMON_CXX11_CONSTEXPR double error = 0.000000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::log(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0,  hamon::log(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log(-T(1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log(-T(2))));
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.69314718055994506, hamon::log(T(2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0986122886681093, hamon::log(T(3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.3862943611198901, hamon::log(T(4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.6094379124341005, hamon::log(T(5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.7917594692280556, hamon::log(T(6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.9459101490553139, hamon::log(T(7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.0794415416798357, hamon::log(T(8)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.1972245773362187, hamon::log(T(9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.3025850929940455, hamon::log(T(10)), error);
}

template <typename T>
void LogTestUnsignedInt(void)
{
	using R = hamon::float_promote_t<T>;
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<R>::infinity();

	HAMON_CXX11_CONSTEXPR double error = 0.000000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::log(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0.0,  hamon::log(T(1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.69314718055994506, hamon::log(T(2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0986122886681093, hamon::log(T(3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.3862943611198901, hamon::log(T(4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.6094379124341005, hamon::log(T(5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.7917594692280556, hamon::log(T(6)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.9459101490553139, hamon::log(T(7)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.0794415416798357, hamon::log(T(8)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.1972245773362187, hamon::log(T(9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.3025850929940455, hamon::log(T(10)), error);
}

GTEST_TEST(CMathTest, LogTest)
{
	LogTestFloat<float>();
	LogTestFloat<double>();
	LogTestFloat<long double>();

//	LogTestSignedInt<int>();
	LogTestSignedInt<signed char>();
//	LogTestSignedInt<short>();
	LogTestSignedInt<long>();
//	LogTestSignedInt<long long>();

	LogTestUnsignedInt<unsigned int>();
//	LogTestUnsignedInt<unsigned char>();
	LogTestUnsignedInt<unsigned short>();
//	LogTestUnsignedInt<unsigned long>();
	LogTestUnsignedInt<unsigned long long>();
}

}	// namespace log_test

}	// namespace hamon_cmath_test
