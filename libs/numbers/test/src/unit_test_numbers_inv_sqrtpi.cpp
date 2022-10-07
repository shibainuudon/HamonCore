/**
 *	@file	unit_test_numbers_inv_sqrtpi.cpp
 *
 *	@brief	numbers::inv_sqrtpi のテスト
 */

#include <hamon/numbers/inv_sqrtpi.hpp>
#include <hamon/numbers/pi.hpp>
#include <hamon/preprocessor/cat.hpp>
#include <gtest/gtest.h>
#include <cmath>
#include "numbers_test.hpp"

namespace hamon_numbers_test
{

static_assert(hamon::numbers::inv_sqrtpi                != 0.0, "");
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
static_assert(hamon::numbers::inv_sqrtpi_v<float>       != 0.0, "");
static_assert(hamon::numbers::inv_sqrtpi_v<double>      != 0.0, "");
static_assert(hamon::numbers::inv_sqrtpi_v<long double> != 0.0, "");
#endif

template <typename T>
void InvSqrtPiTest(double error)
{
	HAMON_NUMBERS_TEST(hamon::numbers::inv_sqrtpi, T(1) / std::sqrt(hamon::numbers::pi_fn<T>()), error);
}

GTEST_TEST(NumbersTest, InvSqrtPiTest)
{
	InvSqrtPiTest<float>(0.0000001);
	InvSqrtPiTest<double>(0.0);
	InvSqrtPiTest<long double>(0.0);
}

}	// namespace hamon_numbers_test
