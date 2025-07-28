/**
 *	@file	unit_test_flat_set_erase.cpp
 *
 *	@brief	erase のテスト
 */

#include <hamon/flat_set/flat_set.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace hamon_flat_set_test
{

namespace erase_test
{

GTEST_TEST(FlatSetTest, EraseTest)
{
	{
		hamon::flat_set<int> fs = {3, 1, 4};

		EXPECT_EQ(3u, fs.size());

		fs.erase(1);
		EXPECT_EQ(2u, fs.size());

		fs.erase(fs.begin(), fs.end());
		EXPECT_EQ(0u, fs.size());
	}
	{
		hamon::flat_set<int> fs = {3, 1, 4};

		// イテレート中に要素削除をするような場合には、
		// 範囲for文は使用できない
		for (auto it = fs.begin(); it != fs.end();)
		{
			// 条件一致した要素を削除する
			if (*it == 1)
			{
				// 削除された要素の次を指すイテレータが返される。
				it = fs.erase(it);
			}
			// 要素削除をしない場合に、イテレータを進める
			else
			{
				++it;
			}
		}

		std::stringstream ss;
		for (int i : fs)
		{
			ss << i << ", ";
		}
		EXPECT_EQ("3, 4, ", ss.str());
	}
}

}	// namespace erase_test

}	// namespace hamon_flat_set_test
