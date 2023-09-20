/**
 *	@file	unit_test_cmath_log10.cpp
 *
 *	@brief	log10 のテスト
 */

#include <hamon/cmath/log10.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/fabs.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace log10_test
{

static_assert(hamon::is_same<float,       decltype(hamon::log10(0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::log10f(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::log10(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::log10(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::log10(0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::log10l(0.0l))>::value, "");

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
void Log10TestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto eps = hamon::numeric_limits<T>::epsilon();

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-3.0,                  (double)hamon::log10(T(   0.001)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-2.0,                  (double)hamon::log10(T(   0.01)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.0,                  (double)hamon::log10(T(   0.1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-0.301029995663981195, (double)hamon::log10(T(   0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0,                  (double)hamon::log10(T(   1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.301029995663981195, (double)hamon::log10(T(   2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.477121254719662437, (double)hamon::log10(T(   3.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.954242509439324875, (double)hamon::log10(T(   9.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0,                  (double)hamon::log10(T(  10.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.0,                  (double)hamon::log10(T( 100.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.0,                  (double)hamon::log10(T(1000.0)), error);

	//If the argument is ±0, -∞ is returned and FE_DIVBYZERO is raised.
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::log10(T(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::log10(T(-0.0)));

	//If the argument is 1, +0 is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::log10(T(+1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::log10(T(+1.0))));

	//If the argument is negative, NaN is returned and FE_INVALID is raised.
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log10(T(-1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log10(T(-2.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log10(T( 0.0) - eps)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log10(-inf)));

	//If the argument is +∞, +∞ is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::log10(inf));

	//If the argument is NaN, NaN is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log10( nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log10(-nan)));
}

template <typename T>
void Log10TestSignedInt(void)
{
	using R = hamon::float_promote_t<T>;
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<R>::infinity();

	HAMON_CXX11_CONSTEXPR double error = 0.000000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::log10(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0,                  (double)hamon::log10(T(   1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.301029995663981195, (double)hamon::log10(T(   2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.477121254719662437, (double)hamon::log10(T(   3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.954242509439324875, (double)hamon::log10(T(   9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0,                  (double)hamon::log10(T(  10)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.0,                  (double)hamon::log10(T( 100)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log10(T(-1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log10(T(-2))));
}

template <typename T>
void Log10TestUnsignedInt(void)
{
	using R = hamon::float_promote_t<T>;
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<R>::infinity();

	HAMON_CXX11_CONSTEXPR double error = 0.000000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::log10(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0,                  (double)hamon::log10(T(   1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.301029995663981195, (double)hamon::log10(T(   2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.477121254719662437, (double)hamon::log10(T(   3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.954242509439324875, (double)hamon::log10(T(   9)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0,                  (double)hamon::log10(T(  10)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.0,                  (double)hamon::log10(T( 100)), error);
}

GTEST_TEST(CMathTest, Log10Test)
{
	Log10TestFloat<float>();
	Log10TestFloat<double>();
	Log10TestFloat<long double>();

	Log10TestSignedInt<int>();
//	Log10TestSignedInt<signed char>();
	Log10TestSignedInt<short>();
//	Log10TestSignedInt<long>();
	Log10TestSignedInt<long long>();

//	Log10TestUnsignedInt<unsigned int>();
	Log10TestUnsignedInt<unsigned char>();
//	Log10TestUnsignedInt<unsigned short>();
	Log10TestUnsignedInt<unsigned long>();
//	Log10TestUnsignedInt<unsigned long long>();
}

}	// namespace log10_test

}	// namespace hamon_cmath_test
