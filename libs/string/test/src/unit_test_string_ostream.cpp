/**
 *	@file	unit_test_string_ostream.cpp
 *
 *	@brief	ストリームへの出力のテスト
 *
 *	template<class charT, class traits, class Allocator>
 *	basic_ostream<charT, traits>&
 *	operator<<(basic_ostream<charT, traits>& os,
 *		const basic_string<charT, traits, Allocator>& str);
 */

#include <hamon/string/basic_string.hpp>
#include <hamon/iomanip/setfill.hpp>
#include <hamon/iomanip/setw.hpp>
#include <hamon/ios.hpp>
#include <hamon/sstream/basic_stringstream.hpp>
#include <hamon/config.hpp>
#include "constexpr_test.hpp"
#include "string_test_helper.hpp"

namespace hamon_test
{
namespace string_test
{
namespace ostream_test
{

template <typename CharT>
void OStreamTest()
{
	using string = hamon::basic_string<CharT>;
	using Helper = StringTestHelper<CharT>;

	{
		string const s = Helper::abcde();
		hamon::basic_stringstream<CharT> ss;
		auto& r = (ss << s);
		EXPECT_TRUE(&r == &ss);
		EXPECT_EQ(ss.str(), s.c_str());
	}
	{
		hamon::basic_stringstream<CharT> ss;
		CharT const c = ss.widen('-');
		string const s = Helper::abcde();
		ss << hamon::setfill(c);
		ss << hamon::left;
		ss << hamon::setw(7);
		ss << s;
		EXPECT_EQ(ss.str(), (s + c + c).c_str());	// "abcde--"

		// width is reset after each call
		ss << s;
		EXPECT_EQ(ss.str(), (s + c + c + s).c_str());	// "abcde--abcde"
	}
	{
		hamon::basic_stringstream<CharT> ss;
		CharT const c = ss.widen('+');
		string const s = Helper::abcde();
		ss << hamon::setfill(c);
		ss << hamon::right;
		ss << hamon::setw(6);
		ss << s;
		EXPECT_EQ(ss.str(), (c + s).c_str());	// "+abcde"

		// width is reset after each call
		ss << s;
		EXPECT_EQ(ss.str(), (c + s + s).c_str());	// "+abcdeabcde"
	}
}

GTEST_TEST(StringTest, OStreamTest)
{
	OStreamTest<char>();
	OStreamTest<wchar_t>();
#if 0	// stringstream が char と wchar_t 以外に対応していない	TODO
#if defined(HAMON_HAS_CXX20_CHAR8_T) && !defined(HAMON_PLATFORM_MACOS)
	OStreamTest<char8_t>();
#endif
#if defined(HAMON_HAS_CXX11_CHAR16_T)
	OStreamTest<char16_t>();
#endif
#if defined(HAMON_HAS_CXX11_CHAR32_T)
	OStreamTest<char32_t>();
#endif
#endif
}

}	// namespace ostream_test
}	// namespace string_test
}	// namespace hamon_test
