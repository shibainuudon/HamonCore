/**
 *	@file	unit_test_numbers_sqrt3.cpp
 *
 *	@brief	numbers::sqrt3 のテスト
 */

#include <hamon/numbers/sqrt3.hpp>
#include <hamon/preprocessor/cat.hpp>
#include <gtest/gtest.h>
#include <cmath>
#include "numbers_test.hpp"

namespace hamon_numbers_test
{

static_assert(hamon::numbers::sqrt3                != 0.0, "");
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
static_assert(hamon::numbers::sqrt3_v<float>       != 0.0, "");
static_assert(hamon::numbers::sqrt3_v<double>      != 0.0, "");
static_assert(hamon::numbers::sqrt3_v<long double> != 0.0, "");
#endif

template <typename T>
void Sqrt3Test(double error)
{
	HAMON_NUMBERS_TEST(hamon::numbers::sqrt3, std::sqrt(T(3)), error);
}

GTEST_TEST(NumbersTest, Sqrt3Test)
{
	Sqrt3Test<float>(0.0);
	Sqrt3Test<double>(0.0);
	Sqrt3Test<long double>(0.0);
}

}	// namespace hamon_numbers_test
