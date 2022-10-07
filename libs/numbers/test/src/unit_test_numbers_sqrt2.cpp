/**
 *	@file	unit_test_numbers_sqrt2.cpp
 *
 *	@brief	numbers::sqrt2 のテスト
 */

#include <hamon/numbers/sqrt2.hpp>
#include <hamon/preprocessor/cat.hpp>
#include <gtest/gtest.h>
#include <cmath>
#include "numbers_test.hpp"

namespace hamon_numbers_test
{

static_assert(hamon::numbers::sqrt2                != 0.0, "");
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
static_assert(hamon::numbers::sqrt2_v<float>       != 0.0, "");
static_assert(hamon::numbers::sqrt2_v<double>      != 0.0, "");
static_assert(hamon::numbers::sqrt2_v<long double> != 0.0, "");
#endif

template <typename T>
void Sqrt2Test(double error)
{
	HAMON_NUMBERS_TEST(hamon::numbers::sqrt2, std::sqrt(T(2)), error);
}

GTEST_TEST(NumbersTest, Sqrt2Test)
{
	Sqrt2Test<float>(0.0);
	Sqrt2Test<double>(0.0);
	Sqrt2Test<long double>(0.0);
}

}	// namespace hamon_numbers_test
