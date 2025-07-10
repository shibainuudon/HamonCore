/**
 *	@file	unit_test_multiset_overview.cpp
 *
 *	@brief	multiset のテスト
 */

#include <hamon/set/multiset.hpp>
#include <gtest/gtest.h>
#include <sstream>

GTEST_TEST(MultisetTest, OverviewTest)
{
	// intをキーとして扱う集合
	hamon::multiset<int> s;

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
