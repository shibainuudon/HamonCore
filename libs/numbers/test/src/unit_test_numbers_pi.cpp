/**
 *	@file	unit_test_numbers_pi.cpp
 *
 *	@brief	numbers::pi のテスト
 */

#include <hamon/numbers/pi.hpp>
#include <hamon/preprocessor/cat.hpp>
#include <gtest/gtest.h>
#include <cmath>
#include "numbers_test.hpp"

namespace hamon_numbers_test
{

static_assert(hamon::numbers::pi                != 0.0, "");
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
static_assert(hamon::numbers::pi_v<float>       != 0.0, "");
static_assert(hamon::numbers::pi_v<double>      != 0.0, "");
static_assert(hamon::numbers::pi_v<long double> != 0.0, "");
#endif

template <typename T>
void PiTest(double error)
{
	HAMON_NUMBERS_TEST(hamon::numbers::pi, acos(T(-1)), error);
}

GTEST_TEST(NumbersTest, PiTest)
{
	PiTest<float>(0.000001);
	PiTest<double>(0.0);
	PiTest<long double>(0.0);
}

}	// namespace hamon_numbers_test
