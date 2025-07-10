/**
 *	@file	unit_test_string_pmr.cpp
 *
 *	@brief	pmr::string のテスト
 */

#include <hamon/string.hpp>
#include <hamon/memory_resource/monotonic_buffer_resource.hpp>
#include <gtest/gtest.h>
#include <sstream>

GTEST_TEST(StringTest, PmrTest)
{
	{
		// C文字列からstringオブジェクトを構築
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::string s("hello", &mr);

		// 末尾に文字列を追加
		s += " world";

		EXPECT_EQ("hello world", s);

		// 部分文字列を取得(始点:0、始点からの文字数:5)
		hamon::pmr::string hello = s.substr(0, 5);

		// ostreamへの出力
		std::stringstream ss;
		ss << hello;
		EXPECT_EQ("hello", ss.str());

		hello = hamon::move(s);
		EXPECT_EQ("hello world", hello);

		s = hello;
		EXPECT_EQ("hello world", s);
	}
	{
		// C文字列からstringオブジェクトを構築
		hamon::pmr::monotonic_buffer_resource mr;
		hamon::pmr::wstring s(L"hello", &mr);

		// 末尾に文字列を追加
		s += L" world";

		EXPECT_EQ(L"hello world", s);

		// 部分文字列を取得(始点:0、始点からの文字数:5)
		hamon::pmr::wstring hello = s.substr(0, 5);

		// ostreamへの出力
		std::wstringstream ss;
		ss << hello;
		EXPECT_EQ(L"hello", ss.str());

		hello = hamon::move(s);
		EXPECT_EQ(L"hello world", hello);

		s = hello;
		EXPECT_EQ(L"hello world", s);
	}
}
