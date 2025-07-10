/**
 *	@file	unit_test_multiset_pmr.cpp
 *
 *	@brief	pmr::multiset のテスト
 */

#include <hamon/set/multiset.hpp>
#include <hamon/memory_resource/monotonic_buffer_resource.hpp>
#include <gtest/gtest.h>
#include <sstream>

GTEST_TEST(MultisetTest, PmrTest)
{
	// intをキーとして扱う集合
	hamon::pmr::monotonic_buffer_resource mr;
	hamon::pmr::multiset<int> s(&mr);

	// 挿入
	s.insert(3);
	s.insert(1);
	s.insert(4);
	s.insert(1); // キーを重複させることが可能

	// キー1に該当する要素数を取得する
	hamon::size_t count = s.count(1);
	EXPECT_TRUE(count == 2);

	// 検索 : キー(int)を指定し、対応する値を得る
	decltype(s)::iterator it = s.find(1);
	EXPECT_TRUE(it != s.end());

	// 発見した
	// 同じキーの要素を全て列挙する
	std::stringstream ss;
	for (hamon::size_t i = 0; i < count; ++i)
	{
		int value = *it;
		ss << value << ", ";
		++it;
	}
	EXPECT_EQ("1, 1, ", ss.str());
}
