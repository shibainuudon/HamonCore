/**
 *	@file	unit_test_list.cpp
 *
 *	@brief	list のテスト
 */

#include <hamon/list.hpp>
#include <hamon/algorithm/for_each.hpp>
#include <hamon/sstream/stringstream.hpp>
#include <gtest/gtest.h>

GTEST_TEST(ListTest, ListTest)
{
	hamon::list<int> ls;

	// 先頭から要素を追加
	ls.push_front(1);
	ls.push_front(2);

	// 末尾から要素を追加
	ls.push_back(3);
	ls.push_back(4);

	// 要素を先頭から順番に表示
	hamon::stringstream ss;
	hamon::for_each(ls.cbegin(), ls.cend(), [&](int x){
		ss << x << ", ";
	});
	EXPECT_EQ("2, 1, 3, 4, ", ss.str());
}
