/**
 *	@file	unit_test_numbers_log10e.cpp
 *
 *	@brief	numbers::log10e のテスト
 */

#include <hamon/numbers/log10e.hpp>
#include <hamon/numbers/e.hpp>
#include <hamon/preprocessor/cat.hpp>
#include <gtest/gtest.h>
#include <cmath>
#include "numbers_test.hpp"

namespace hamon_numbers_test
{

static_assert(hamon::numbers::log10e                != 0.0, "");
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
static_assert(hamon::numbers::log10e_v<float>       != 0.0, "");
static_assert(hamon::numbers::log10e_v<double>      != 0.0, "");
static_assert(hamon::numbers::log10e_v<long double> != 0.0, "");
#endif

template <typename T>
void Log10eTest(double error)
{
	HAMON_NUMBERS_TEST(hamon::numbers::log10e, std::log10(hamon::numbers::e_fn<T>()), error);
}

GTEST_TEST(NumbersTest, Log10eTest)
{
	Log10eTest<float>(0.0000001);
	Log10eTest<double>(0.0);
	Log10eTest<long double>(0.0);
}

}	// namespace hamon_numbers_test
