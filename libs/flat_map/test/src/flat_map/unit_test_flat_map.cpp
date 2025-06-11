/**
 *	@file	unit_test_flat_map.cpp
 *
 *	@brief	flat_map のテスト
 */

#include <hamon/flat_map.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include <sstream>

GTEST_TEST(FlatMapTest, FlatMapTest)
{
	// stringをキー、intを値として扱う連想配列
	hamon::flat_map<hamon::string, int> fm =
	{
		{"Carol", 4},
		{"Alice", 3},
		{"Bob",   1},
	};

	// 検索 : キー(string)を指定し、値(int)を得る
	int r = fm.at("Alice");
	EXPECT_EQ(3, r);

	// 全体を出力する
	std::stringstream ss;
	for (const auto& p : fm)
	{
		ss << p.first << ":" << p.second << ", ";
	}
	EXPECT_EQ("Alice:3, Bob:1, Carol:4, ", ss.str());
}
