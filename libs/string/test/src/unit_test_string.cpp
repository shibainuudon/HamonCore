/**
 *	@file	unit_test_string.cpp
 *
 *	@brief	string のテスト
 */

#include <hamon/string.hpp>
#include <hamon/sstream/stringstream.hpp>
#include <hamon/sstream/wstringstream.hpp>
#include <gtest/gtest.h>

GTEST_TEST(StringTest, StringTest)
{
	{
		// C文字列からstringオブジェクトを構築
		hamon::string s = "hello";

		// 末尾に文字列を追加
		s += " world";

		EXPECT_EQ("hello world", s);

		// 部分文字列を取得(始点:0、始点からの文字数:5)
		hamon::string hello = s.substr(0, 5);

		// ostreamへの出力
		hamon::stringstream ss;
		ss << hello;
		EXPECT_EQ("hello", ss.str());
	}
	{
		// C文字列からstringオブジェクトを構築
		hamon::wstring s = L"hello";

		// 末尾に文字列を追加
		s += L" world";

		EXPECT_EQ(L"hello world", s);

		// 部分文字列を取得(始点:0、始点からの文字数:5)
		hamon::wstring hello = s.substr(0, 5);

		// ostreamへの出力
		hamon::wstringstream ss;
		ss << hello;
		EXPECT_EQ(L"hello", ss.str());
	}
}
