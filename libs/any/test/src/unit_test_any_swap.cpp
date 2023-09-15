/**
 *	@file	unit_test_any_swap.cpp
 *
 *	@brief	swap関数のテスト
 *
 *	void any::swap(any& rhs) noexcept;
 *	void swap(any& x, any& y) noexcept;
 */

#include <hamon/any.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>

GTEST_TEST(AnyTest, SwapTest)
{
	{
		hamon::any a{3};
		hamon::any b{hamon::string("Hello")};
		EXPECT_EQ(3, hamon::any_cast<int>(a));
		EXPECT_EQ("Hello", hamon::any_cast<hamon::string>(b));

		a.swap(b);
		EXPECT_EQ("Hello", hamon::any_cast<hamon::string>(a));
		EXPECT_EQ(3, hamon::any_cast<int>(b));

		swap(a, b);
		EXPECT_EQ(3, hamon::any_cast<int>(a));
		EXPECT_EQ("Hello", hamon::any_cast<hamon::string>(b));
	}
}
