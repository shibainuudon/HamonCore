/**
 *	@file	unit_test_config_noreturn.cpp
 *
 *	@brief	HAMON_NORETURN のテスト
 */

#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include <stdexcept>

namespace hamon_config_noreturn_test
{

#if !defined(HAMON_NO_EXCEPTIONS)

HAMON_NORETURN void report_error()
{
	throw std::runtime_error("");
}

int func(int x)
{
	if (x > 0)
	{
		return x;
	}

	report_error();
}

GTEST_TEST(ConfigTest, NoReturnTest)
{
	func(1);
}

#endif

}	// namespace hamon_config_noreturn_test
