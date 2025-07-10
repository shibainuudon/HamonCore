/**
 *	@file	unit_test_multimap_pmr.cpp
 *
 *	@brief	pmr::multimap のテスト
 */

#include <hamon/map/multimap.hpp>
#include <hamon/memory_resource/monotonic_buffer_resource.hpp>
#include <gtest/gtest.h>
#include <sstream>

GTEST_TEST(MultimapTest, PmrTest)
{
	// charをキー、intを値として扱う連想配列
	hamon::pmr::monotonic_buffer_resource mr;
	hamon::pmr::multimap<char, int> m(&mr);

	// 挿入
	m.emplace('c', 30);
	m.emplace('a', 10);
	m.emplace('b', 20);
	m.emplace('a', 40); // キー'a'に対応する値が2つ

	// 同じキーを持つ値の数を取得する
	auto count = m.count('a'); // count == 2
	EXPECT_TRUE(count == 2);

	// キー`a`を持つ値を列挙する
	auto p = m.equal_range('a');
	std::stringstream ss;
	for (auto it = p.first; it != p.second; ++it)
	{
		ss << it->second << ", ";
	}
	EXPECT_EQ("10, 40, ", ss.str());
}
