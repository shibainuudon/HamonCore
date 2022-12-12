/**
 *	@file	unit_test_cmath_rsqrt.cpp
 *
 *	@brief	rsqrt のテスト
 */

#include <hamon/cmath/rsqrt.hpp>
#include <hamon/cmath/isinf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/fabs.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace rsqrt_test
{

static_assert(std::is_same<float,       decltype(hamon::rsqrt(0.0f))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::rsqrt(0.0 ))>::value, "");
static_assert(std::is_same<double,      decltype(hamon::rsqrt(0   ))>::value, "");
static_assert(std::is_same<long double, decltype(hamon::rsqrt(0.0l))>::value, "");

template <typename T>
void RsqrtTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto eps = std::numeric_limits<T>::epsilon();

	HAMON_CXX11_CONSTEXPR double error = 0.0000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::rsqrt(T(0.00)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 2.0,           (double)hamon::rsqrt(T(  0.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0,           (double)hamon::rsqrt(T(  1.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.66666666666, (double)hamon::rsqrt(T(  2.25)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.70710678118, (double)hamon::rsqrt(T(  2.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.57735026918, (double)hamon::rsqrt(T(  3.00)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.1,           (double)hamon::rsqrt(T(100.00)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isinf  (hamon::rsqrt(T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isinf  (hamon::rsqrt(T(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::rsqrt(T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::rsqrt(T(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::rsqrt(+inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::rsqrt(+inf)));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::rsqrt(-eps)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::rsqrt(T(-1.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::rsqrt(-inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::rsqrt(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::rsqrt(-nan)));
}

template <typename T>
void RsqrtTestSignedInt(void)
{
	using R = hamon::float_promote_t<T>;
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<R>::infinity();

	HAMON_CXX11_CONSTEXPR double error = 0.0000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::rsqrt(T(  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0,           (double)hamon::rsqrt(T(  1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.70710678118, (double)hamon::rsqrt(T(  2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.57735026918, (double)hamon::rsqrt(T(  3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.1,           (double)hamon::rsqrt(T(100)), error);

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::rsqrt(T(-1))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::rsqrt(T(-2))));
}

template <typename T>
void RsqrtTestUnsignedInt(void)
{
	using R = hamon::float_promote_t<T>;
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<R>::infinity();

	HAMON_CXX11_CONSTEXPR double error = 0.0000001;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(inf, hamon::rsqrt(T(  0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 1.0,           (double)hamon::rsqrt(T(  1)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.70710678118, (double)hamon::rsqrt(T(  2)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.57735026918, (double)hamon::rsqrt(T(  3)), error);
	HAMON_CXX11_CONSTEXPR_EXPECT_NEAR( 0.1,           (double)hamon::rsqrt(T(100)), error);
}

GTEST_TEST(CMathTest, RsqrtTest)
{
	RsqrtTestFloat<float>();
	RsqrtTestFloat<double>();
	RsqrtTestFloat<long double>();

//	RsqrtTestSignedInt<int>();
	RsqrtTestSignedInt<signed char>();
//	RsqrtTestSignedInt<short>();
	RsqrtTestSignedInt<long>();
//	RsqrtTestSignedInt<long long>();

	RsqrtTestUnsignedInt<unsigned int>();
//	RsqrtTestUnsignedInt<unsigned char>();
	RsqrtTestUnsignedInt<unsigned short>();
//	RsqrtTestUnsignedInt<unsigned long>();
	RsqrtTestUnsignedInt<unsigned long long>();
}

}	// namespace rsqrt_test

}	// namespace hamon_cmath_test
