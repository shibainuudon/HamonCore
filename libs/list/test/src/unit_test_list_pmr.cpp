/**
 *	@file	unit_test_list_pmr.cpp
 *
 *	@brief	pmr::list のテスト
 */

#include <hamon/list.hpp>
#include <hamon/algorithm/for_each.hpp>
#include <hamon/memory_resource/monotonic_buffer_resource.hpp>
#include <gtest/gtest.h>
#include <sstream>

GTEST_TEST(ListTest, PmrTest)
{
	hamon::pmr::monotonic_buffer_resource mr;
	hamon::pmr::list<int> ls(&mr);

	// 先頭から要素を追加
	ls.push_front(1);
	ls.push_front(2);

	// 末尾から要素を追加
	ls.push_back(3);
	ls.push_back(4);

	// 要素を先頭から順番に表示
	std::stringstream ss;
	hamon::for_each(ls.cbegin(), ls.cend(), [&](int x){
		ss << x << ", ";
	});
	EXPECT_EQ("2, 1, 3, 4, ", ss.str());
}
