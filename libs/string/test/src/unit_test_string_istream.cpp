/**
 *	@file	unit_test_string_istream.cpp
 *
 *	@brief	ストリームからの入力のテスト
 *
 *	template<class charT, class traits, class Allocator>
 *	basic_istream<charT, traits>&
 *	operator>>(basic_istream<charT, traits>& is,
 *		basic_string<charT, traits, Allocator>& str);
 */

#include <hamon/string/basic_string.hpp>
#include <hamon/config.hpp>
#include <sstream>
#include <iomanip>
#include "constexpr_test.hpp"
#include "string_test_helper.hpp"

namespace hamon_test
{
namespace string_test
{
namespace istream_test
{

template <typename CharT>
void IStreamTest()
{
	using string = hamon::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		std::basic_stringstream<CharT> ss;
		ss << Helper::long_str() << std::endl;
		string s;
		auto& r = (ss >> s);
		EXPECT_TRUE(&r == &ss);
		EXPECT_EQ(s, string(Helper::long_str(), 0, 3));	// "The"
		ss >> s;
		EXPECT_EQ(s, string(Helper::long_str(), 4, 5));	// "quick"
		ss >> s;
		EXPECT_EQ(s, string(Helper::long_str(), 10, 5));// "brown"
	}
	{
		std::basic_stringstream<CharT> ss;
		ss << Helper::abcde();
		string s;
		ss >> s;
		EXPECT_EQ(s, Helper::abcde());
	}
	{
		std::basic_stringstream<CharT> ss;
		ss << Helper::abcde();
		string s;
		ss << std::setw(3);
		ss >> s;
		EXPECT_EQ(s, string(Helper::abcde(), 0, 3));	// "abc"
	}
	{
		std::basic_stringstream<CharT> ss;
		ss << Helper::abcde();
		string s;
		ss << std::setw(7);
		ss >> s;
		EXPECT_EQ(s, Helper::abcde());
	}
}

GTEST_TEST(StringTest, IStreamTest)
{
	IStreamTest<char>();
	IStreamTest<wchar_t>();
#if 0	// stringstream が char と wchar_t 以外に対応していない	TODO
#if defined(HAMON_HAS_CXX20_CHAR8_T) && !defined(HAMON_PLATFORM_MACOS)
	IStreamTest<char8_t>();
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	IStreamTest<char16_t>();
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	IStreamTest<char32_t>();
#endif
#endif
}

}	// namespace istream_test
}	// namespace string_test
}	// namespace hamon_test
