/**
 *	@file	unit_test_cmath_is_negative.cpp
 *
 *	@brief	is_negative のテスト
 */

#include <hamon/cmath/is_negative.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace is_negative_test
{

static_assert(hamon::is_same<bool, decltype(hamon::is_negative(0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::is_negative(0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::is_negative(0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::is_negative(0   ))>::value, "");

template <typename T>
void IsNegativeTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan    = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf    = std::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_negative(T( 1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_negative(T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_negative(T( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_negative(T(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_negative( inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_negative(-inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_negative(max));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_negative(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_negative(lowest));

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_negative(T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_negative(T(-0.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_negative( nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_negative(-nan));
}

template <typename T>
void IsNegativeTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_negative(T( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_negative(T( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_negative(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_negative(T( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_negative(T(-2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_negative(max));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_negative(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_negative(lowest));
}

template <typename T>
void IsNegativeTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_negative(T( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_negative(T( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_negative(T( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_negative(max));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_negative(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_negative(lowest));
}

GTEST_TEST(CMathTest, IsNegativeTest)
{
	IsNegativeTestFloat<float>();
	IsNegativeTestFloat<double>();
	IsNegativeTestFloat<long double>();

//	IsNegativeTestSignedInt<int>();
	IsNegativeTestSignedInt<signed char>();
//	IsNegativeTestSignedInt<short>();
	IsNegativeTestSignedInt<long>();
//	IsNegativeTestSignedInt<long long>();

	IsNegativeTestUnsignedInt<unsigned int>();
//	IsNegativeTestUnsignedInt<unsigned char>();
	IsNegativeTestUnsignedInt<unsigned short>();
//	IsNegativeTestUnsignedInt<unsigned long>();
	IsNegativeTestUnsignedInt<unsigned long long>();
}

}	// namespace is_negative_test

}	// namespace hamon_cmath_test
