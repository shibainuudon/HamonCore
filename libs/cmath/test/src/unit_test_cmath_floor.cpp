/**
 *	@file	unit_test_cmath_floor.cpp
 *
 *	@brief	floor のテスト
 */

#include <hamon/cmath/floor.hpp>
#include <hamon/cmath/signbit.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace floor_test
{

static_assert(hamon::is_same<float,       decltype(hamon::floor(0.0f))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::floorf(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::floor(0.0 ))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::floor(0   ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::floor(0.0l))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::floorl(0.0l))>::value, "");

template <typename T>
void FloorTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto eps = hamon::numeric_limits<T>::epsilon() * 2;

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  0.0,  hamon::floor(T(0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  0.0,  hamon::floor(T(0.0) + eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) -1.0,  hamon::floor(T(0.0) - eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::floor(T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::iszero (hamon::floor(T(-0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::floor(T(+0.0))));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::floor(T(-0.0))));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  1.0,  hamon::floor(T(1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  1.0,  hamon::floor(T(1.0) + eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  0.0,  hamon::floor(T(1.0) - eps));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) -1.0,  hamon::floor(T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) -1.0,  hamon::floor(T(-1.0) + eps));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) -2.0,  hamon::floor(T(-1.0) - eps));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 10.0,  hamon::floor(T(10.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 10.0,  hamon::floor(T(10.0) + (eps*10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  9.0,  hamon::floor(T(10.0) - (eps*10)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-10.0,  hamon::floor(T(-10.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-10.0,  hamon::floor(T(-10.0) + (eps*10)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-11.0,  hamon::floor(T(-10.0) - (eps*10)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 1000.0,  hamon::floor(T(1000.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 1000.0,  hamon::floor(T(1000.0) + (eps*1000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  999.0,  hamon::floor(T(1000.0) - (eps*1000)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-1000.0,  hamon::floor(T(-1000.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-1000.0,  hamon::floor(T(-1000.0) + (eps*1000)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-1001.0,  hamon::floor(T(-1000.0) - (eps*1000)));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ( inf,  hamon::floor(+inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(-inf,  hamon::floor(-inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::floor(+inf)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::signbit(hamon::floor(-inf)));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan  (hamon::floor(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::isnan  (hamon::floor(-nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::floor(+nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(hamon::floor(-nan)));
}

template <typename T>
void FloorTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)   0, hamon::floor((T)   0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)   1, hamon::floor((T)   1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  -1, hamon::floor((T)  -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)   3, hamon::floor((T)   3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  -3, hamon::floor((T)  -3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 100, hamon::floor((T) 100));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-100, hamon::floor((T)-100));
}

template <typename T>
void FloorTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  0, hamon::floor((T)  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  1, hamon::floor((T)  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)100, hamon::floor((T)100));
}

GTEST_TEST(CMathTest, FloorTest)
{
	FloorTestFloat<float>();
	FloorTestFloat<double>();
	FloorTestFloat<long double>();

	FloorTestSignedInt<int>();
//	FloorTestSignedInt<signed char>();
	FloorTestSignedInt<short>();
//	FloorTestSignedInt<long>();
	FloorTestSignedInt<long long>();

	FloorTestUnsignedInt<unsigned int>();
	FloorTestUnsignedInt<unsigned char>();
//	FloorTestUnsignedInt<unsigned short>();
	FloorTestUnsignedInt<unsigned long>();
//	FloorTestUnsignedInt<unsigned long long>();
}

}	// namespace floor_test

}	// namespace hamon_cmath_test
