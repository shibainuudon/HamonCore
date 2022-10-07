/**
 *	@file	unit_test_numbers_inv_pi.cpp
 *
 *	@brief	numbers::inv_pi のテスト
 */

#include <hamon/numbers/inv_pi.hpp>
#include <hamon/numbers/pi.hpp>
#include <hamon/preprocessor/cat.hpp>
#include <gtest/gtest.h>
#include <cmath>
#include "numbers_test.hpp"

namespace hamon_numbers_test
{

static_assert(hamon::numbers::inv_pi                != 0.0, "");
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
static_assert(hamon::numbers::inv_pi_v<float>       != 0.0, "");
static_assert(hamon::numbers::inv_pi_v<double>      != 0.0, "");
static_assert(hamon::numbers::inv_pi_v<long double> != 0.0, "");
#endif

template <typename T>
void InvPiTest(double error)
{
	HAMON_NUMBERS_TEST(hamon::numbers::inv_pi, T(1) / hamon::numbers::pi_fn<T>(), error);
}

GTEST_TEST(NumbersTest, InvPiTest)
{
	InvPiTest<float>(0.0);
	InvPiTest<double>(0.0);
	InvPiTest<long double>(0.0);
}

}	// namespace hamon_numbers_test
