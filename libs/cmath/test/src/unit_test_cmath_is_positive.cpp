/**
 *	@file	unit_test_cmath_is_positive.cpp
 *
 *	@brief	is_positive のテスト
 */

#include <hamon/cmath/is_positive.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace is_positive_test
{

static_assert(hamon::is_same<bool, decltype(hamon::is_positive(0.0f))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::is_positive(0.0 ))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::is_positive(0.0l))>::value, "");
static_assert(hamon::is_same<bool, decltype(hamon::is_positive(0   ))>::value, "");

template <typename T>
void IsPositiveTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan    = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf    = hamon::numeric_limits<T>::infinity();
	HAMON_CXX11_CONSTEXPR auto max    = hamon::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto min    = hamon::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto lowest = hamon::numeric_limits<T>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_positive(T( 1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_positive(T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_positive(T( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_positive(T(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_positive( inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_positive(-inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_positive(max));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_positive(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_positive(lowest));

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_positive(T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_positive(T(-0.0)));

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_positive( nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_positive(-nan));
}

template <typename T>
void IsPositiveTestSignedInt(void)
{
	HAMON_CXX11_CONSTEXPR auto max    = hamon::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto min    = hamon::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto lowest = hamon::numeric_limits<T>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_positive(T( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_positive(T( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_positive(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_positive(T( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_positive(T(-2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_positive(max));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_positive(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_positive(lowest));
}

template <typename T>
void IsPositiveTestUnsignedInt(void)
{
	HAMON_CXX11_CONSTEXPR auto max    = hamon::numeric_limits<T>::max();
	HAMON_CXX11_CONSTEXPR auto min    = hamon::numeric_limits<T>::min();
	HAMON_CXX11_CONSTEXPR auto lowest = hamon::numeric_limits<T>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_positive(T( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_positive(T( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_positive(T( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::is_positive(max));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_positive(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::is_positive(lowest));
}

GTEST_TEST(CMathTest, IsPositiveTest)
{
	IsPositiveTestFloat<float>();
	IsPositiveTestFloat<double>();
	IsPositiveTestFloat<long double>();

//	IsPositiveTestSignedInt<int>();
	IsPositiveTestSignedInt<signed char>();
//	IsPositiveTestSignedInt<short>();
	IsPositiveTestSignedInt<long>();
//	IsPositiveTestSignedInt<long long>();

	IsPositiveTestUnsignedInt<unsigned int>();
//	IsPositiveTestUnsignedInt<unsigned char>();
	IsPositiveTestUnsignedInt<unsigned short>();
//	IsPositiveTestUnsignedInt<unsigned long>();
	IsPositiveTestUnsignedInt<unsigned long long>();
}

}	// namespace is_positive_test

}	// namespace hamon_cmath_test
