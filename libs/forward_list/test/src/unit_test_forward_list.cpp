/**
 *	@file	unit_test_forward_list.cpp
 *
 *	@brief	forward_list のテスト
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/algorithm/for_each.hpp>
#include <hamon/sstream/stringstream.hpp>
#include <gtest/gtest.h>

GTEST_TEST(ForwardListTest, ForwardListTest)
{
	hamon::forward_list<int> ls;

	ls.push_front(3);               // 先頭に3を追加
	ls.insert_after(ls.begin(), 1); // 先頭の後ろに1を追加

	// イテレータを介して全要素に対して操作を行う
	hamon::stringstream ss;
	hamon::for_each(ls.cbegin(), ls.cend(), [&](int x) {
		ss << x << ", ";
	});
	EXPECT_EQ("3, 1, ", ss.str());
}
