/**
 *	@file	unit_test_forward_list_pmr.cpp
 *
 *	@brief	pmr::forward_list のテスト
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/algorithm/for_each.hpp>
#include <hamon/memory_resource/monotonic_buffer_resource.hpp>
#include <gtest/gtest.h>
#include <sstream>

GTEST_TEST(ForwardListTest, PmrTest)
{
	hamon::pmr::monotonic_buffer_resource mr;
	hamon::pmr::forward_list<int> ls(&mr);

	ls.push_front(3);               // 先頭に3を追加
	ls.insert_after(ls.begin(), 1); // 先頭の後ろに1を追加

	// イテレータを介して全要素に対して操作を行う
	std::stringstream ss;
	hamon::for_each(ls.cbegin(), ls.cend(), [&](int x) {
		ss << x << ", ";
	});
	EXPECT_EQ("3, 1, ", ss.str());
}
