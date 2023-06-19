/**
 *	@file	unit_test_any_make_any.cpp
 *
 *	@brief	make_any関数のテスト
 *
 *	template<class T, class... Args>
 *	any make_any(Args&&... args);
 *
 *	template<class T, class U, class... Args>
 *	any make_any(initializer_list<U> il, Args&&... args);
 */

#include <hamon/any.hpp>
#include <gtest/gtest.h>
#include <string>
#include <vector>

GTEST_TEST(AnyTest, MakeAnyTest)
{
	{
		hamon::any a = hamon::make_any<int>(41);
		EXPECT_EQ(41, hamon::any_cast<int>(a));
	}
	{
		hamon::any a = hamon::make_any<std::string>(3u, 'z');
		EXPECT_EQ("zzz", hamon::any_cast<std::string>(a));
	}
	{
		std::allocator<int> alloc;
		hamon::any a = hamon::make_any<std::vector<int>>({3, 1, 4}, alloc);
		auto const& vec = hamon::any_cast<std::vector<int> const&>(a);
		EXPECT_EQ(3, vec[0]);
		EXPECT_EQ(1, vec[1]);
		EXPECT_EQ(4, vec[2]);
	}
}
