/**
 *	@file	unit_test_stdexcept_length_error.cpp
 *
 *	@brief	length_error のテスト
 */

#include <hamon/stdexcept/length_error.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(StdExceptTest, LengthErrorTest)
{
#if !defined(HAMON_NO_EXCEPTIONS)
	EXPECT_THROW(hamon::detail::throw_length_error("test"), hamon::length_error);
#endif
}
