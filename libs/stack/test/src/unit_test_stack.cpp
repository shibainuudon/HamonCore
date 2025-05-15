/**
 *	@file	unit_test_stack.cpp
 *
 *	@brief	stack のテスト
 */

#include <hamon/stack.hpp>
#include <gtest/gtest.h>
#include <sstream>

GTEST_TEST(StackTest, StackTest)
{
	hamon::stack<int> st;

	// 要素を追加
	st.push(1);
	st.push(2);
	st.push(3);

	std::stringstream ss;
	while (!st.empty())
	{
		ss << st.top() << " "; // 末尾要素を参照する
		st.pop(); // 末尾要素を削除
	}

	EXPECT_EQ("3 2 1 ", ss.str());
}
