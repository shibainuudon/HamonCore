/**
 *	@file	unit_test_string_getline.cpp
 *
 *	@brief	getline のテスト
 *
 *	template<class charT, class traits, class Allocator>
 *	basic_istream<charT, traits>&
 *	getline(basic_istream<charT, traits>& is,
 *		basic_string<charT, traits, Allocator>& str,
 *		charT delim);
 *	
 *	template<class charT, class traits, class Allocator>
 *	basic_istream<charT, traits>&
 *	getline(basic_istream<charT, traits>&& is,
 *		basic_string<charT, traits, Allocator>& str,
 *		charT delim);
 *	
 *	template<class charT, class traits, class Allocator>
 *	basic_istream<charT, traits>&
 *	getline(basic_istream<charT, traits>& is,
 *		basic_string<charT, traits, Allocator>& str);
 *	
 *	template<class charT, class traits, class Allocator>
 *	basic_istream<charT, traits>&
 *	getline(basic_istream<charT, traits>&& is,
 *		basic_string<charT, traits, Allocator>& str);
 */

#include <hamon/string/getline.hpp>
#include <hamon/string/basic_string.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <sstream>
#include "constexpr_test.hpp"
#include "string_test_helper.hpp"

namespace hamon_test
{
namespace string_test
{
namespace getline_test
{

template <typename CharT>
void GetLineTest()
{
	using string = hamon::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		std::basic_stringstream<CharT> ss;
		ss << Helper::abcde() << std::endl;
		ss << Helper::ABCDE() << std::endl;
		ss << Helper::aababc() << std::endl;
		string s;
		auto& r = hamon::getline(ss, s);
		EXPECT_TRUE(&r == &ss);
		EXPECT_EQ(s, Helper::abcde());
		hamon::getline(ss, s);
		EXPECT_EQ(s, Helper::ABCDE());
		hamon::getline(ss, s);
		EXPECT_EQ(s, Helper::aababc());
	}
	{
		std::basic_stringstream<CharT> ss;
		ss << Helper::long_str() << std::endl;
		string s;
		auto& r = hamon::getline(ss, s);
		EXPECT_TRUE(&r == &ss);
		EXPECT_EQ(s, Helper::long_str());
	}
	{
		std::basic_stringstream<CharT> ss;
		ss << Helper::abcde() << std::endl;
		ss << Helper::ABCDE() << std::endl;
		ss << Helper::aababc() << std::endl;
		string s;
		auto& r = hamon::getline(hamon::move(ss), s);
		EXPECT_TRUE(&r == &ss);
		EXPECT_EQ(s, Helper::abcde());
		hamon::getline(hamon::move(ss), s);
		EXPECT_EQ(s, Helper::ABCDE());
		hamon::getline(hamon::move(ss), s);
		EXPECT_EQ(s, Helper::aababc());
	}
	{
		std::basic_stringstream<CharT> ss;
		ss << Helper::long_str() << std::endl;
		string s;
		auto& r = hamon::getline(hamon::move(ss), s);
		EXPECT_TRUE(&r == &ss);
		EXPECT_EQ(s, Helper::long_str());
	}
	{
		std::basic_stringstream<CharT> ss;
		ss << Helper::abcde();
		string s;
		auto const delim = Helper::abcde()[2];
		auto& r = hamon::getline(ss, s, delim);
		EXPECT_TRUE(&r == &ss);
		EXPECT_EQ(s, string(Helper::abcde(), 0, 2));	// "ab"
		hamon::getline(ss, s, delim);
		EXPECT_EQ(s, string(Helper::abcde(), 3, 2));	// "de"
	}
	{
		std::basic_stringstream<CharT> ss;
		ss << Helper::long_str() << std::endl;
		string s;
		auto& r = hamon::getline(ss, s, ss.widen(' '));
		EXPECT_TRUE(&r == &ss);
		EXPECT_EQ(s, string(Helper::long_str(), 0, 3));	// "The"
		hamon::getline(ss, s, ss.widen(' '));
		EXPECT_EQ(s, string(Helper::long_str(), 4, 5));	// "quick"
		hamon::getline(ss, s, ss.widen(' '));
		EXPECT_EQ(s, string(Helper::long_str(), 10, 5));// "brown"
	}
	{
		std::basic_stringstream<CharT> ss;
		ss << Helper::abcde();
		string s;
		auto const delim = Helper::abcde()[3];
		auto& r = hamon::getline(hamon::move(ss), s, delim);
		EXPECT_TRUE(&r == &ss);
		EXPECT_EQ(s, string(Helper::abcde(), 0, 3));	// "abc"
		hamon::getline(hamon::move(ss), s, delim);
		EXPECT_EQ(s, string(Helper::abcde(), 4, 1));	// "e"
	}
	{
		std::basic_stringstream<CharT> ss;
		ss << Helper::long_str() << std::endl;
		string s;
		auto& r = hamon::getline(hamon::move(ss), s, ss.widen(' '));
		EXPECT_TRUE(&r == &ss);
		EXPECT_EQ(s, string(Helper::long_str(), 0, 3));	// "The"
		hamon::getline(hamon::move(ss), s, ss.widen(' '));
		EXPECT_EQ(s, string(Helper::long_str(), 4, 5));	// "quick"
		hamon::getline(hamon::move(ss), s, ss.widen(' '));
		EXPECT_EQ(s, string(Helper::long_str(), 10, 5));// "brown"
	}
}

GTEST_TEST(StringTest, GetLineTest)
{
	GetLineTest<char>();
	GetLineTest<wchar_t>();
#if 0	// stringstream が char と wchar_t 以外に対応していない	TODO
#if defined(HAMON_HAS_CXX20_CHAR8_T) && !defined(HAMON_PLATFORM_MACOS)
	GetLineTest<char8_t>();
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	GetLineTest<char16_t>();
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	GetLineTest<char32_t>();
#endif
#endif
}

}	// namespace getline_test
}	// namespace string_test
}	// namespace hamon_test
