/**
 *	@file	unit_test_cmath_nan.cpp
 *
 *	@brief	nan のテスト
 */

#include <hamon/cmath/nan.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace nan_test
{

static_assert(hamon::is_same<float,       decltype(hamon::nanf(nullptr))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::nan (nullptr))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::nanl(nullptr))>::value, "");

GTEST_TEST(CMathTest, NanTest)
{
	EXPECT_TRUE(hamon::isnan(hamon::nanf("")));
	EXPECT_TRUE(hamon::isnan(hamon::nanf("1")));
	EXPECT_TRUE(hamon::isnan(hamon::nanf("2")));

	EXPECT_TRUE(hamon::isnan(hamon::nan("")));
	EXPECT_TRUE(hamon::isnan(hamon::nan("1")));
	EXPECT_TRUE(hamon::isnan(hamon::nan("2")));

	EXPECT_TRUE(hamon::isnan(hamon::nanl("")));
	EXPECT_TRUE(hamon::isnan(hamon::nanl("1")));
	EXPECT_TRUE(hamon::isnan(hamon::nanl("2")));
}

}	// namespace nan_test

}	// namespace hamon_cmath_test
