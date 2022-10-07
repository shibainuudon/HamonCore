/**
 *	@file	unit_test_numbers_ln2.cpp
 *
 *	@brief	numbers::ln2 のテスト
 */

#include <hamon/numbers/ln2.hpp>
#include <hamon/preprocessor/cat.hpp>
#include <gtest/gtest.h>
#include <cmath>
#include "numbers_test.hpp"

namespace hamon_numbers_test
{

static_assert(hamon::numbers::ln2                != 0.0, "");
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
static_assert(hamon::numbers::ln2_v<float>       != 0.0, "");
static_assert(hamon::numbers::ln2_v<double>      != 0.0, "");
static_assert(hamon::numbers::ln2_v<long double> != 0.0, "");
#endif

template <typename T>
void Ln2Test(double error)
{
	HAMON_NUMBERS_TEST(hamon::numbers::ln2, std::log(T(2)), error);
}

GTEST_TEST(NumbersTest, Ln2Test)
{
	Ln2Test<float>(0.0);
	Ln2Test<double>(0.0);
	Ln2Test<long double>(0.0);
}

}	// namespace hamon_numbers_test
