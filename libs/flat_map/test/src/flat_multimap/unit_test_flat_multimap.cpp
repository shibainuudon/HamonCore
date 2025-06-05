/**
 *	@file	unit_test_flat_multimap.cpp
 *
 *	@brief	flat_multimap のテスト
 */

#include <hamon/flat_map.hpp>
#include <gtest/gtest.h>
#include <sstream>

GTEST_TEST(FlatMultimapTest, FlatMultimapTest)
{
	// intをキー、charを値、として扱う連想配列
	// flat_mapとは異なり、キーが重複してもよい
	hamon::flat_multimap<int, char> fm =
	{
		{10, 'A'}, {11, 'B'}, {12, 'C'},
		{10, 'a'}, {11, 'b'}, {12, 'c'},
	};

	// 全体を出力する
	std::stringstream ss;
	for (const auto& p : fm)
	{
		ss << p.first << ":" << p.second << ", ";
	}
	EXPECT_EQ("10:A, 10:a, 11:B, 11:b, 12:C, 12:c, ", ss.str());
}
