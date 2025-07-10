/**
 *	@file	unit_test_deque_pmr.cpp
 *
 *	@brief	pmr::deque のテスト
 */

#include <hamon/deque.hpp>
#include <hamon/algorithm/for_each.hpp>
#include <hamon/memory_resource/monotonic_buffer_resource.hpp>
#include <gtest/gtest.h>
#include <sstream>

GTEST_TEST(DequeTest, PmrTest)
{
	hamon::pmr::monotonic_buffer_resource mr;
	hamon::pmr::deque<int> deq(&mr);

	deq.push_front(3);  // 先頭に要素を追加
	deq.push_back(1);   // 末尾に要素を追加

	// イテレータを介して全要素に対して操作を行う
	std::stringstream ss;
	hamon::for_each(deq.begin(), deq.end(), [&](int x) {
		ss << x << ", ";
	});
	EXPECT_EQ("3, 1, ", ss.str());
}
