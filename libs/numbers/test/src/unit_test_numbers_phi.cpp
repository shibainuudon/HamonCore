/**
 *	@file	unit_test_numbers_phi.cpp
 *
 *	@brief	numbers::phi のテスト
 */

#include <hamon/numbers/phi.hpp>
#include <hamon/preprocessor/cat.hpp>
#include <gtest/gtest.h>
#include <cmath>
#include "numbers_test.hpp"

namespace hamon_numbers_test
{

static_assert(hamon::numbers::phi                != 0.0, "");
#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
static_assert(hamon::numbers::phi_v<float>       != 0.0, "");
static_assert(hamon::numbers::phi_v<double>      != 0.0, "");
static_assert(hamon::numbers::phi_v<long double> != 0.0, "");
#endif

template <typename T>
void PhiTest(double error)
{
	HAMON_NUMBERS_TEST(hamon::numbers::phi, (T(1) + std::sqrt(T(5))) / T(2), error);
}

GTEST_TEST(NumbersTest, PhiTest)
{
	PhiTest<float>(0.0);
	PhiTest<double>(0.0);
	PhiTest<long double>(0.0);
}

}	// namespace hamon_numbers_test
