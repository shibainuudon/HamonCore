/**
 *	@file	unit_test_any_assign_move.cpp
 *
 *	@brief	ムーブ代入演算子のテスト
 *
 *	any& operator=(any&& rhs) noexcept;
 */

#include <hamon/any.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <hamon/type_traits/is_nothrow_move_assignable.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include <string>

static_assert(hamon::is_move_assignable<hamon::any>::value, "");
static_assert(hamon::is_nothrow_move_assignable<hamon::any>::value, "");

GTEST_TEST(AnyTest, AssignMoveTest)
{
	{
		hamon::any a{3};
		hamon::any b{};
		EXPECT_FALSE(b.has_value());
		b = hamon::move(a);
		EXPECT_TRUE(b.has_value());
		EXPECT_EQ(3, hamon::any_cast<int>(b));
	}
	{
		hamon::any a{};
		hamon::any b{3};
		EXPECT_TRUE(b.has_value());
		EXPECT_EQ(3, hamon::any_cast<int>(b));
		b = hamon::move(a);
		EXPECT_FALSE(b.has_value());
	}
	{
		hamon::any a{std::string("Hello")};
		hamon::any b{};
		EXPECT_FALSE(b.has_value());
		b = hamon::move(a);
		EXPECT_TRUE(b.has_value());
		EXPECT_EQ("Hello", hamon::any_cast<std::string>(b));
	}
}
