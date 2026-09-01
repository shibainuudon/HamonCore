/**
 *	@file	unit_test_deque.cpp
 *
 *	@brief	deque のテスト
 */

#include <hamon/deque.hpp>
#include <hamon/algorithm/for_each.hpp>
#include <hamon/sstream/stringstream.hpp>
#include <gtest/gtest.h>

GTEST_TEST(DequeTest, DequeTest)
{
	hamon::deque<int> deq;

	deq.push_front(3);  // 先頭に要素を追加
	deq.push_back(1);   // 末尾に要素を追加

	// イテレータを介して全要素に対して操作を行う
	hamon::stringstream ss;
	hamon::for_each(deq.begin(), deq.end(), [&](int x) {
		ss << x << ", ";
	});
	EXPECT_EQ("3, 1, ", ss.str());
}
