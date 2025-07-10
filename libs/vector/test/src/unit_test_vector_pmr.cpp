/**
 *	@file	unit_test_vector_pmr.cpp
 *
 *	@brief	pmr::vector のテスト
 */

#include <hamon/vector.hpp>
#include <hamon/memory_resource/monotonic_buffer_resource.hpp>
#include <gtest/gtest.h>
#include <sstream>

GTEST_TEST(VectorTest, PmrTest)
{
	// int型を要素とする可変長配列の変数を定義し、
	// 初期状態の要素を設定
    hamon::pmr::monotonic_buffer_resource mr;
	hamon::pmr::vector<int> v({1, 99, 4}, &mr);

	v[1] = 3;                    // 1番目の要素を参照し、書き換える
	v.push_back(5);              // 末尾に値5を追加
	v.insert(v.begin() + 1, 2);  // 1番目に値2を挿入

	int* p = v.data();           // 内部表現のポインタを取得
	hamon::size_t size = v.size(); // 要素数を取得
	EXPECT_TRUE(p[0] == 1);
	EXPECT_TRUE(size == 5u);

	// 各要素に対して操作を行う
	std::stringstream ss;
	for (int x : v)
	{
		ss << x << ", ";
	}
	EXPECT_EQ("1, 2, 3, 4, 5, ", ss.str());
}
