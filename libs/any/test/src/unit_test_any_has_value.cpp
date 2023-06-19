/**
 *	@file	unit_test_any_has_value.cpp
 *
 *	@brief	has_value関数のテスト
 *
 *	bool has_value() const noexcept;
 */

#include <hamon/any.hpp>
#include <gtest/gtest.h>
#include <string>

GTEST_TEST(AnyTest, HasValueTest)
{
	{
		hamon::any a{3};
		hamon::any b;
		EXPECT_TRUE(a.has_value());
		EXPECT_FALSE(b.has_value());
	}
}
