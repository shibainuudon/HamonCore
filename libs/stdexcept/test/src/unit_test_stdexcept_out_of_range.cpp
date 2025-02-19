/**
 *	@file	unit_test_stdexcept_out_of_range.cpp
 *
 *	@brief	out_of_range のテスト
 */

#include <hamon/stdexcept/out_of_range.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>

GTEST_TEST(StdExceptTest, OutOfRangeTest)
{
#if !defined(HAMON_NO_EXCEPTIONS)
	EXPECT_THROW(hamon::detail::throw_out_of_range("test"), hamon::out_of_range);
#endif
}
