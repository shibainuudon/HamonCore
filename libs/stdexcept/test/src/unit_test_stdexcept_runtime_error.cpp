/**
 *	@file	unit_test_stdexcept_runtime_error.cpp
 *
 *	@brief	runtime_error のテスト
 */

#include <hamon/stdexcept/runtime_error.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(StdExceptTest, RuntimeErrorTest)
{
#if !defined(HAMON_NO_EXCEPTIONS)
	EXPECT_THROW(hamon::detail::throw_runtime_error("test"), hamon::runtime_error);
#endif
}
