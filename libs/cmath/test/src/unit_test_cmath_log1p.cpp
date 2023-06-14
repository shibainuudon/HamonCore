/**
 *	@file	unit_test_cmath_log1p.cpp
 *
 *	@brief	log1p のテスト
 */

#include <hamon/cmath/log1p.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace log1p_test
{

static_assert(hamon::is_same<float,       decltype(hamon::log1p(0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::log1pf(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::log1p(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::log1p(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::log1p(0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::log1pl(0.0l))>::value, "");

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
void Log1pTestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto eps = std::numeric_limits<T>::epsilon();
	HAMON_CXX11_CONSTEXPR auto min = std::numeric_limits<T>::lowest();

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-2.30258509299404568, (double)hamon::log1p(T(-0.9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.69314718055994530, (double)hamon::log1p(T(-0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.40546510810816438, (double)hamon::log1p(T( 0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.69314718055994530, (double)hamon::log1p(T( 1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.91629073187415506, (double)hamon::log1p(T( 1.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.09861228866810969, (double)hamon::log1p(T( 2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.60943791243410037, (double)hamon::log1p(T( 4.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.19722457733621938, (double)hamon::log1p(T( 8.0)), error);

	//If the argument is ±0, it is returned unmodified
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(+0.0), hamon::log1p(T(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-0.0), hamon::log1p(T(-0.0)));

	//If the argument is -1, -∞ is returned.
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::log1p(T(-1.0)));

	//If the argument is less than -1, NaN is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log1p(T(-1.0) - eps)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log1p(T(-1.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log1p(T(-2.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log1p(T(-2.5))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log1p(T(-3.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log1p(min)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log1p(-inf)));

	//If the argument is +∞, +∞ is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(+inf, hamon::log1p(+inf));

	//If the argument is NaN, NaN is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log1p(-nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log1p(+nan)));
}

template <typename T>
void Log1pTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.000000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.69314718055994530, hamon::log1p(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.09861228866810969, hamon::log1p(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.60943791243410037, hamon::log1p(T( 4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.19722457733621938, hamon::log1p(T( 8)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0), hamon::log1p(T(0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isinf  (hamon::log1p(T(-1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::signbit(hamon::log1p(T(-1))));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log1p(T(-2))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log1p(T(-3))));
}

template <typename T>
void Log1pTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR double error = 0.000000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.69314718055994530, hamon::log1p(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.09861228866810969, hamon::log1p(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.60943791243410037, hamon::log1p(T( 4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.19722457733621938, hamon::log1p(T( 8)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(0), hamon::log1p(T(0)));
}

GTEST_TEST(CMathTest, Log1pTest)
{
	Log1pTestFloat<float>();
	Log1pTestFloat<double>();
	Log1pTestFloat<long double>();

	Log1pTestSignedInt<int>();
//	Log1pTestSignedInt<signed char>();
	Log1pTestSignedInt<short>();
//	Log1pTestSignedInt<long>();
	Log1pTestSignedInt<long long>();

//	Log1pTestUnsignedInt<unsigned int>();
	Log1pTestUnsignedInt<unsigned char>();
//	Log1pTestUnsignedInt<unsigned short>();
	Log1pTestUnsignedInt<unsigned long>();
//	Log1pTestUnsignedInt<unsigned long long>();
}

}	// namespace log1p_test

}	// namespace hamon_cmath_test
