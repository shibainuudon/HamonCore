/**
 *	@file	unit_test_flat_multiset.cpp
 *
 *	@brief	flat_multiset のテスト
 */

#include <hamon/flat_set.hpp>
#include <hamon/string.hpp>
#include <hamon/deque.hpp>
#include <hamon/functional.hpp>
#include <gtest/gtest.h>
#include <sstream>

GTEST_TEST(FlatMultisetTest, FlatMultisetTest)
{
	{
		// stringをキーとして扱う連想配列
		hamon::flat_multiset<hamon::string> fs = {"Carol", "Alice", "Bob", "Carol"};

		// 検索 : キーを指定し、イテレータを得る
		auto it = fs.find("Alice");
		EXPECT_EQ("Alice", *it);

		// 全体を出力する
		std::stringstream ss;
		for (const auto& str : fs)
		{
			ss << str << ", ";
		}
		EXPECT_EQ("Alice, Bob, Carol, Carol, ", ss.str());
	}
	{
		hamon::deque<int> keys = {1, 4, 2, 7, 8, 1, 5, 7};

		// intをキーとして扱う連想配列
		// キーの順序はgreater、キーのコンテナはdequeで保持
		hamon::flat_multiset<int, hamon::greater<int>, hamon::deque<int>> fs(keys);

		// 全体を出力する
		std::stringstream ss;
		for (int i : fs)
		{
			ss << i << " ";
		}
		EXPECT_EQ("8 7 7 5 4 2 1 1 ", ss.str());
	}
}
