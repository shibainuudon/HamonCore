/**
 *	@file	unit_test_numbers_egamma.cpp
 *
 *	@brief	numbers::egamma のテスト
 */

#include <hamon/numbers/egamma.hpp>
#include <hamon/preprocessor/cat.hpp>
#include <gtest/gtest.h>
#include <cmath>
#include "numbers_test.hpp"

namespace hamon_numbers_test
{

static_assert(hamon::numbers::egamma                != 0.0, "");
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
static_assert(hamon::numbers::egamma_v<float>       != 0.0, "");
static_assert(hamon::numbers::egamma_v<double>      != 0.0, "");
static_assert(hamon::numbers::egamma_v<long double> != 0.0, "");
#endif

template <typename T>
void EGammaTest(double error)
{
	// TODO オイラー定数を動的に計算する方法がわからない
	HAMON_NUMBERS_TEST(hamon::numbers::egamma, 0.5772156649015328606065120900824024310421593359399235988057672348848677267776646709369470632917467495, error);
}

GTEST_TEST(NumbersTest, EGammaTest)
{
	EGammaTest<float>(0.0000001);
	EGammaTest<double>(0.0);
	EGammaTest<long double>(0.0);
}

}	// namespace hamon_numbers_test
