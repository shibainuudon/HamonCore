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
#include <hamon/memory/allocator.hpp>
#include <hamon/vector.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>

GTEST_TEST(AnyTest, MakeAnyTest)
{
	{
		hamon::any a = hamon::make_any<int>(41);
		EXPECT_EQ(41, hamon::any_cast<int>(a));
	}
	{
		hamon::any a = hamon::make_any<hamon::string>(3u, 'z');
		EXPECT_EQ("zzz", hamon::any_cast<hamon::string>(a));
	}
	{
		hamon::allocator<int> alloc;
		hamon::any a = hamon::make_any<hamon::vector<int>>({3, 1, 4}, alloc);
		auto const& vec = hamon::any_cast<hamon::vector<int> const&>(a);
		EXPECT_EQ(3, vec[0]);
		EXPECT_EQ(1, vec[1]);
		EXPECT_EQ(4, vec[2]);
	}
}
