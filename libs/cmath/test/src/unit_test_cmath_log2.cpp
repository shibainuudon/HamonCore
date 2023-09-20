/**
 *	@file	unit_test_cmath_log2.cpp
 *
 *	@brief	log2 のテスト
 */

#include <hamon/cmath/log2.hpp>
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

namespace log2_test
{

static_assert(hamon::is_same<float,       decltype(hamon::log2(0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::log2f(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::log2(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::log2(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::log2(0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::log2l(0.0l))>::value, "");

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
void Log2TestFloat()
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto eps = hamon::numeric_limits<T>::epsilon();

	HAMON_CXX11_CONSTEXPR double error = get_error<T>();

	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-3.0, (double)hamon::log2(T(0.125)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-2.0, (double)hamon::log2(T(0.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(-1.0, (double)hamon::log2(T(0.5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.0, (double)hamon::log2(T(1.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0, (double)hamon::log2(T(2.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.0, (double)hamon::log2(T(4.0)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 3.0, (double)hamon::log2(T(8.0)), error);

	//If the argument is ±0, -∞ is returned and FE_DIVBYZERO is raised.
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::log2(T(+0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::log2(T(-0.0)));

	//If the argument is 1, +0 is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::log2(T(+1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::log2(T(+1.0))));

	//If the argument is negative, NaN is returned and FE_INVALID is raised.
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log2(T(-1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log2(T(-2.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log2(T( 0.0) - eps)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log2(-inf)));

	//If the argument is +∞, +∞ is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::log2(inf));

	//If the argument is NaN, NaN is returned
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log2( nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log2(-nan)));
}

template <typename T>
void Log2TestSignedInt(void)
{
	using R = hamon::float_promote_t<T>;
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<R>::infinity();

	HAMON_CXX11_CONSTEXPR double error = 0.000000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::log2(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0,                (double)hamon::log2(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0,                (double)hamon::log2(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.5849625007211561, (double)hamon::log2(T( 3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.0,                (double)hamon::log2(T( 4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.3219280948873622, (double)hamon::log2(T( 5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(3.0,                (double)hamon::log2(T( 8)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log2(T(-1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::log2(T(-2))));
}

template <typename T>
void Log2TestUnsignedInt(void)
{
	using R = hamon::float_promote_t<T>;
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<R>::infinity();

	HAMON_CXX11_CONSTEXPR double error = 0.000000000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf, hamon::log2(T(0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(0.0,                (double)hamon::log2(T( 1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.0,                (double)hamon::log2(T( 2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(1.5849625007211561, (double)hamon::log2(T( 3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.0,                (double)hamon::log2(T( 4)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(2.3219280948873622, (double)hamon::log2(T( 5)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR(3.0,                (double)hamon::log2(T( 8)), error);
}

GTEST_TEST(CMathTest, Log2Test)
{
	Log2TestFloat<float>();
	Log2TestFloat<double>();
	Log2TestFloat<long double>();

//	Log2TestSignedInt<int>();
	Log2TestSignedInt<signed char>();
//	Log2TestSignedInt<short>();
	Log2TestSignedInt<long>();
//	Log2TestSignedInt<long long>();

	Log2TestUnsignedInt<unsigned int>();
//	Log2TestUnsignedInt<unsigned char>();
	Log2TestUnsignedInt<unsigned short>();
//	Log2TestUnsignedInt<unsigned long>();
	Log2TestUnsignedInt<unsigned long long>();
}

}	// namespace log2_test

}	// namespace hamon_cmath_test
