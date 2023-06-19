/**
 *	@file	unit_test_any_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 *
 *	any(const any& other);
 */

#include <hamon/any.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <gtest/gtest.h>
#include <string>

static_assert(hamon::is_copy_constructible<hamon::any>::value, "");

GTEST_TEST(AnyTest, CtorCopyTest)
{
	{
		hamon::any a{};
		hamon::any b{a};
		EXPECT_FALSE(a.has_value());
		EXPECT_FALSE(b.has_value());
	}
	{
		hamon::any a{3};
		hamon::any b{a};
		EXPECT_TRUE(a.has_value());
		EXPECT_TRUE(b.has_value());
		EXPECT_EQ(3, hamon::any_cast<int>(a));
		EXPECT_EQ(3, hamon::any_cast<int>(b));

		a = 4;
		EXPECT_TRUE(a.has_value());
		EXPECT_TRUE(b.has_value());
		EXPECT_EQ(4, hamon::any_cast<int>(a));
		EXPECT_EQ(3, hamon::any_cast<int>(b));
	}
	{
		hamon::any a{std::string("Hello")};
		hamon::any b{a};
		EXPECT_TRUE(a.has_value());
		EXPECT_TRUE(b.has_value());
		EXPECT_EQ("Hello", hamon::any_cast<std::string>(a));
		EXPECT_EQ("Hello", hamon::any_cast<std::string>(b));

		a = 42;
		EXPECT_TRUE(a.has_value());
		EXPECT_TRUE(b.has_value());
		EXPECT_EQ(42, hamon::any_cast<int>(a));
		EXPECT_EQ("Hello", hamon::any_cast<std::string>(b));
	}
}
