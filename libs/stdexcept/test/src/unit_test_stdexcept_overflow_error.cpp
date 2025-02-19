/**
 *	@file	unit_test_stdexcept_overflow_error.cpp
 *
 *	@brief	overflow_error のテスト
 */

#include <hamon/stdexcept/overflow_error.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(StdExceptTest, OverflowErrorTest)
{
#if !defined(HAMON_NO_EXCEPTIONS)
	EXPECT_THROW(hamon::detail::throw_overflow_error("test"), hamon::overflow_error);
#endif
}
