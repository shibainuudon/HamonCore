/**
 *	@file	unit_test_numbers_log2e.cpp
 *
 *	@brief	numbers::log2e のテスト
 */

#include <hamon/numbers/log2e.hpp>
#include <hamon/numbers/e.hpp>
#include <hamon/preprocessor/cat.hpp>
#include <gtest/gtest.h>
#include <cmath>
#include "numbers_test.hpp"

namespace hamon_numbers_test
{

static_assert(hamon::numbers::log2e                != 0.0, "");
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
static_assert(hamon::numbers::log2e_v<float>       != 0.0, "");
static_assert(hamon::numbers::log2e_v<double>      != 0.0, "");
static_assert(hamon::numbers::log2e_v<long double> != 0.0, "");
#endif

template <typename T>
void Log2eTest(double error)
{
	HAMON_NUMBERS_TEST(hamon::numbers::log2e, std::log2(hamon::numbers::e_fn<T>()), error);
}

GTEST_TEST(NumbersTest, Log2eTest)
{
	Log2eTest<float>(0.0);
	Log2eTest<double>(0.0);
	Log2eTest<long double>(0.0);
}

}	// namespace hamon_numbers_test
