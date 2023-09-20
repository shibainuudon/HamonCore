/**
 *	@file	unit_test_cmath_ceil.cpp
 *
 *	@brief	ceil のテスト
 */

#include <hamon/cmath/ceil.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/cmath/iszero.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace ceil_test
{

static_assert(hamon::is_same<float,       decltype(hamon::ceil(0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::ceilf(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::ceil(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::ceil(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::ceil(0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::ceill(0.0l))>::value, "");

template <typename T>
void CeilTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto eps = hamon::numeric_limits<T>::epsilon() * 2;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  0.0,  hamon::ceil(T(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  1.0,  hamon::ceil(T(0.0) + eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  0.0,  hamon::ceil(T(0.0) - eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::ceil(T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::ceil(T(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::ceil(T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::ceil(T(-0.0))));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  1.0,  hamon::ceil(T(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  2.0,  hamon::ceil(T(1.0) + eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  1.0,  hamon::ceil(T(1.0) - eps));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) -1.0,  hamon::ceil(T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  0.0,  hamon::ceil(T(-1.0) + eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) -1.0,  hamon::ceil(T(-1.0) - eps));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 10.0,  hamon::ceil(T(10.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 11.0,  hamon::ceil(T(10.0) + (eps*10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 10.0,  hamon::ceil(T(10.0) - (eps*10)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-10.0,  hamon::ceil(T(-10.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) -9.0,  hamon::ceil(T(-10.0) + (eps*10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-10.0,  hamon::ceil(T(-10.0) - (eps*10)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 1000.0,  hamon::ceil(T(1000.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 1001.0,  hamon::ceil(T(1000.0) + (eps*1000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 1000.0,  hamon::ceil(T(1000.0) - (eps*1000)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-1000.0,  hamon::ceil(T(-1000.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) -999.0,  hamon::ceil(T(-1000.0) + (eps*1000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-1000.0,  hamon::ceil(T(-1000.0) - (eps*1000)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf,  hamon::ceil(+inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf,  hamon::ceil(-inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::ceil(+inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::signbit(hamon::ceil(-inf)));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan  (hamon::ceil(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan  (hamon::ceil(-nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::ceil(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::ceil(-nan)));
}

template <typename T>
void CeilTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)   0, hamon::ceil((T)   0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)   1, hamon::ceil((T)   1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  -1, hamon::ceil((T)  -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)   3, hamon::ceil((T)   3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  -3, hamon::ceil((T)  -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 100, hamon::ceil((T) 100));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-100, hamon::ceil((T)-100));
}

template <typename T>
void CeilTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  0, hamon::ceil((T)  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  1, hamon::ceil((T)  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)100, hamon::ceil((T)100));
}

GTEST_TEST(CMathTest, CeilTest)
{
	CeilTestFloat<float>();
	CeilTestFloat<double>();
	CeilTestFloat<long double>();

	CeilTestSignedInt<int>();
//	CeilTestSignedInt<signed char>();
	CeilTestSignedInt<short>();
//	CeilTestSignedInt<long>();
	CeilTestSignedInt<long long>();

	CeilTestUnsignedInt<unsigned int>();
	CeilTestUnsignedInt<unsigned char>();
//	CeilTestUnsignedInt<unsigned short>();
	CeilTestUnsignedInt<unsigned long>();
//	CeilTestUnsignedInt<unsigned long long>();
}

}	// namespace ceil_test

}	// namespace hamon_cmath_test
