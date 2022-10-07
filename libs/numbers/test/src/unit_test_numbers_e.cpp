/**
 *	@file	unit_test_numbers_e.cpp
 *
 *	@brief	numbers::e のテスト
 */

#include <hamon/numbers/e.hpp>
#include <hamon/preprocessor/cat.hpp>
#include <gtest/gtest.h>
#include <cmath>
#include "numbers_test.hpp"

namespace hamon_numbers_test
{

static_assert(hamon::numbers::e                != 0.0, "");
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
static_assert(hamon::numbers::e_v<float>       != 0.0, "");
static_assert(hamon::numbers::e_v<double>      != 0.0, "");
static_assert(hamon::numbers::e_v<long double> != 0.0, "");
#endif

template <typename T>
void ETest(double error)
{
	HAMON_NUMBERS_TEST(hamon::numbers::e, std::exp(T(1)), error);
}

GTEST_TEST(NumbersTest, ETest)
{
	ETest<float>(0.0);
	ETest<double>(0.0);
	ETest<long double>(0.0);
}

}	// namespace hamon_numbers_test
