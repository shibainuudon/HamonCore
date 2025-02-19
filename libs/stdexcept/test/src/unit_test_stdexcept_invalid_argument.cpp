/**
 *	@file	unit_test_stdexcept_invalid_argument.cpp
 *
 *	@brief	invalid_argument のテスト
 */

#include <hamon/stdexcept/invalid_argument.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(StdExceptTest, InvalidArgumentTest)
{
#if !defined(HAMON_NO_EXCEPTIONS)
	EXPECT_THROW(hamon::detail::throw_invalid_argument("test"), hamon::invalid_argument);
#endif
}
