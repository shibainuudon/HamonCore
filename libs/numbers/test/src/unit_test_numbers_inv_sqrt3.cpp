/**
 *	@file	unit_test_numbers_inv_sqrt3.cpp
 *
 *	@brief	numbers::inv_sqrt3 のテスト
 */

#include <hamon/numbers/inv_sqrt3.hpp>
#include <hamon/preprocessor/cat.hpp>
#include <gtest/gtest.h>
#include <cmath>
#include "numbers_test.hpp"

namespace hamon_numbers_test
{

static_assert(hamon::numbers::inv_sqrt3                != 0.0, "");
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
static_assert(hamon::numbers::inv_sqrt3_v<float>       != 0.0, "");
static_assert(hamon::numbers::inv_sqrt3_v<double>      != 0.0, "");
static_assert(hamon::numbers::inv_sqrt3_v<long double> != 0.0, "");
#endif

template <typename T>
void InvSqrt3Test(double error)
{
	HAMON_NUMBERS_TEST(hamon::numbers::inv_sqrt3, T(1) / std::sqrt(T(3)), error);
}

GTEST_TEST(NumbersTest, InvSqrt3Test)
{
	InvSqrt3Test<float>(0.0000001);
	InvSqrt3Test<double>(0.0000001);
	InvSqrt3Test<long double>(0.0000001);
}

}	// namespace hamon_numbers_test
