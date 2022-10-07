/**
 *	@file	unit_test_numbers_ln10.cpp
 *
 *	@brief	numbers::ln10 のテスト
 */

#include <hamon/numbers/ln10.hpp>
#include <hamon/preprocessor/cat.hpp>
#include <gtest/gtest.h>
#include <cmath>
#include "numbers_test.hpp"

namespace hamon_numbers_test
{

static_assert(hamon::numbers::ln10                != 0.0, "");
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
static_assert(hamon::numbers::ln10_v<float>       != 0.0, "");
static_assert(hamon::numbers::ln10_v<double>      != 0.0, "");
static_assert(hamon::numbers::ln10_v<long double> != 0.0, "");
#endif

template <typename T>
void Ln10Test(double error)
{
	HAMON_NUMBERS_TEST(hamon::numbers::ln10, std::log(T(10)), error);
}

GTEST_TEST(NumbersTest, Ln10Test)
{
	Ln10Test<float>(0.0);
	Ln10Test<double>(0.0);
	Ln10Test<long double>(0.0);
}

}	// namespace hamon_numbers_test
