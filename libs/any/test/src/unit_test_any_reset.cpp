/**
 *	@file	unit_test_any_reset.cpp
 *
 *	@brief	reset関数のテスト
 *
 *	void reset() noexcept;
 */

#include <hamon/any.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>

GTEST_TEST(AnyTest, AssignResetTest)
{
	{
		hamon::any a{3};
		EXPECT_TRUE(a.has_value());

		a.reset();
		EXPECT_FALSE(a.has_value());

		a = hamon::string("XXX");
		EXPECT_TRUE(a.has_value());

		a.reset();
		EXPECT_FALSE(a.has_value());
	}
}
