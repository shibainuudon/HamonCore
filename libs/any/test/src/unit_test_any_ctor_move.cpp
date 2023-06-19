/**
 *	@file	unit_test_any_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 *
 *	any(any&& other) noexcept;
 */

#include <hamon/any.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include <string>

static_assert(hamon::is_move_constructible<hamon::any>::value, "");
static_assert(hamon::is_nothrow_move_constructible<hamon::any>::value, "");

GTEST_TEST(AnyTest, CtorMoveTest)
{
	{
		hamon::any a{};
		hamon::any b{hamon::move(a)};
		EXPECT_FALSE(b.has_value());
	}
	{
		hamon::any a{3};
		hamon::any b{hamon::move(a)};
		EXPECT_TRUE(b.has_value());
		EXPECT_EQ(3, hamon::any_cast<int>(b));
	}
	{
		hamon::any a{std::string("Hello")};
		hamon::any b{hamon::move(a)};
		EXPECT_TRUE(b.has_value());
		EXPECT_EQ("Hello", hamon::any_cast<std::string>(b));
	}
}
