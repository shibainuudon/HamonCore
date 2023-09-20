/**
 *	@file	unit_test_cmath_sign.cpp
 *
 *	@brief	sign のテスト
 */

#include <hamon/cmath/sign.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/type_traits/float_promote.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace sign_test
{

static_assert(hamon::is_same<float,       decltype(hamon::sign(0.0f))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::sign(0.0 ))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::sign(0.0l))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::sign(0   ))>::value, "");

template <typename T>
void SignTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan    = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf    = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto max    = hamon::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto min    = hamon::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto lowest = hamon::numeric_limits<T>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::sign(T( 1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-1), hamon::sign(T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::sign(T( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-1), hamon::sign(T(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::sign( inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-1), hamon::sign(-inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::sign(max));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 1), hamon::sign(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T(-1), hamon::sign(lowest));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0), hamon::sign(T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(T( 0), hamon::sign(T(-0.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::sign( nan)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(hamon::isnan(hamon::sign(-nan)));
}

template <typename T>
void SignTestSignedInt(void)
{
	using R = hamon::float_promote_t<T>;

	HAMON_CXX11_CONSTEXPR auto max    = hamon::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto min    = hamon::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto lowest = hamon::numeric_limits<T>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 0), hamon::sign(T( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 1), hamon::sign(T( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-1), hamon::sign(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 1), hamon::sign(T( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-1), hamon::sign(T(-2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 1), hamon::sign(max));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-1), hamon::sign(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R(-1), hamon::sign(lowest));
}

template <typename T>
void SignTestUnsignedInt(void)
{
	using R = hamon::float_promote_t<T>;

	HAMON_CXX11_CONSTEXPR auto max    = hamon::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto min    = hamon::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto lowest = hamon::numeric_limits<T>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 0), hamon::sign(T( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 1), hamon::sign(T( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 1), hamon::sign(T( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 1), hamon::sign(max));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 0), hamon::sign(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(R( 0), hamon::sign(lowest));
}

GTEST_TEST(CMathTest, SignTest)
{
	SignTestFloat<float>();
	SignTestFloat<double>();
	SignTestFloat<long double>();

//	SignTestSignedInt<int>();
	SignTestSignedInt<signed char>();
//	SignTestSignedInt<short>();
	SignTestSignedInt<long>();
//	SignTestSignedInt<long long>();

	SignTestUnsignedInt<unsigned int>();
//	SignTestUnsignedInt<unsigned char>();
	SignTestUnsignedInt<unsigned short>();
//	SignTestUnsignedInt<unsigned long>();
	SignTestUnsignedInt<unsigned long long>();
}

}	// namespace sign_test

}	// namespace hamon_cmath_test
