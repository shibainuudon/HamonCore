/**
 *	@file	unit_test_cmath_signbit.cpp
 *
 *	@brief	signbit のテスト
 */

#include <hamon/cmath/signbit.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <limits>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace signbit_test
{

static_assert(std::is_same<bool, decltype(hamon::signbit(0.0f))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::signbit(0.0 ))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::signbit(0.0l))>::value, "");
static_assert(std::is_same<bool, decltype(hamon::signbit(0   ))>::value, "");

template <typename T>
void SignbitTestFloat(void)
{
	HAMON_CONSTEXPR auto nan    = std::numeric_limits<T>::quiet_NaN();
	HAMON_CONSTEXPR auto inf    = std::numeric_limits<T>::infinity();
	HAMON_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	HAMON_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	HAMON_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(T( 1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::signbit(T(-1.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(T( 0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::signbit(T(-0.5)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit( inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::signbit(-inf));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(max));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::signbit(lowest));

	// HAMONでは、+0と-0は区別されない
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(T( 0.0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(T(-0.0)));

	// HAMONでは、+NaNと-NaNは区別されない
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit( nan));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(-nan));
}

template <typename T>
void SignbitTestSignedInt(void)
{
	HAMON_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	HAMON_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	HAMON_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(T( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(T( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::signbit(T(-1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(T( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::signbit(T(-2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(max));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::signbit(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (hamon::signbit(lowest));
}

template <typename T>
void SignbitTestUnsignedInt(void)
{
	HAMON_CONSTEXPR auto max    = std::numeric_limits<T>::max();
	HAMON_CONSTEXPR auto min    = std::numeric_limits<T>::min();
	HAMON_CONSTEXPR auto lowest = std::numeric_limits<T>::lowest();

	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(T( 0)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(T( 1)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(T( 2)));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(max));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(min));
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(hamon::signbit(lowest));
}

GTEST_TEST(CMathTest, SignBitTest)
{
	SignbitTestFloat<float>();
	SignbitTestFloat<double>();
	SignbitTestFloat<long double>();

//	SignbitTestSignedInt<int>();
	SignbitTestSignedInt<signed char>();
//	SignbitTestSignedInt<short>();
	SignbitTestSignedInt<long>();
//	SignbitTestSignedInt<long long>();

	SignbitTestUnsignedInt<unsigned int>();
//	SignbitTestUnsignedInt<unsigned char>();
	SignbitTestUnsignedInt<unsigned short>();
//	SignbitTestUnsignedInt<unsigned long>();
	SignbitTestUnsignedInt<unsigned long long>();
}

}	// namespace signbit_test

}	// namespace hamon_cmath_test
