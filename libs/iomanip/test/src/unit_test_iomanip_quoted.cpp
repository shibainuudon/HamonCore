/**
 *	@file	unit_test_iomanip_quoted.cpp
 *
 *	@brief	quoted のテスト
 *
 *	template<typename charT>
 *	unspecified quoted(const charT* s, charT delim = charT('"'), charT escape = charT('\\'));
 *
 *	template<typename charT, typename traits, typename Allocator>
 *	unspecified quoted(const basic_string<charT, traits, Allocator>& s, charT delim = charT('"'), charT escape = charT('\\'));
 *
 *	template<typename charT, typename traits>
 *	unspecified quoted(basic_string_view<charT, traits> s, charT delim = charT('"'), charT escape = charT('\\'));
 *
 *	template<typename charT, typename traits, typename Allocator>
 *	unspecified quoted(basic_string<charT, traits, Allocator>& s, charT delim = charT('"'), charT escape = charT('\\'));
 */

#include <hamon/iomanip/quoted.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#if (HAMON_CXX_STANDARD >= 17) && HAMON_HAS_INCLUDE(<string_view>)
#include <string_view>
#endif

namespace iomanip_test
{

namespace quoted_test
{

template <typename CharT, typename Traits>
bool is_skipws(std::basic_istream<CharT, Traits> const& is)
{
	return (is.flags() & std::ios_base::skipws) != 0;
}

template <typename Str, typename OutStr, typename CharT>
void test2(Str in, CharT delim, CharT escape, Str unquoted_str, Str quoted_str, bool noskip_ws)
{
	// round trip
	{
		std::basic_stringstream<CharT> ss;
		if (noskip_ws)
		{
			std::noskipws(ss);
		}
		auto const skipws = is_skipws(ss);
		ss << hamon::quoted(in, delim, escape);
		OutStr out;
		ss >> hamon::quoted(out, delim, escape);
		EXPECT_EQ(in, out);
		EXPECT_EQ(skipws, is_skipws(ss));
	}

	// unquoted
	{
		std::basic_stringstream<CharT> ss;
		if (noskip_ws)
		{
			std::noskipws(ss);
		}
		auto const skipws = is_skipws(ss);
		ss << in;
		OutStr out;
		ss >> hamon::quoted(out, delim, escape);
		EXPECT_EQ(unquoted_str, out);
		EXPECT_EQ(skipws, is_skipws(ss));
	}

	// quoted
	{
		std::basic_stringstream<CharT> ss;
		if (noskip_ws)
		{
			std::noskipws(ss);
		}
		auto const skipws = is_skipws(ss);
		ss << hamon::quoted(in, delim, escape);
		OutStr out;
		ss >> out;
		EXPECT_EQ(quoted_str, out);
		EXPECT_EQ(skipws, is_skipws(ss));
	}
}

template <typename CharT>
void test(CharT const* str, CharT delim, CharT escape, CharT const* unquoted_str, CharT const* quoted_str)
{
	test2<CharT const*, std::basic_string<CharT>>(str, delim, escape, unquoted_str, quoted_str, true);
	test2<CharT const*, std::basic_string<CharT>>(str, delim, escape, unquoted_str, quoted_str, false);
	test2<CharT const*, hamon::basic_string<CharT>>(str, delim, escape, unquoted_str, quoted_str, true);
	test2<CharT const*, hamon::basic_string<CharT>>(str, delim, escape, unquoted_str, quoted_str, false);
	test2<hamon::basic_string<CharT>, hamon::basic_string<CharT>>(str, delim, escape, unquoted_str, quoted_str, true);
	test2<hamon::basic_string<CharT>, hamon::basic_string<CharT>>(str, delim, escape, unquoted_str, quoted_str, false);
	test2<hamon::basic_string<CharT> const&, hamon::basic_string<CharT>>(str, delim, escape, unquoted_str, quoted_str, true);
	test2<hamon::basic_string<CharT> const&, hamon::basic_string<CharT>>(str, delim, escape, unquoted_str, quoted_str, false);
	test2<std::basic_string<CharT>, std::basic_string<CharT>>(str, delim, escape, unquoted_str, quoted_str, true);
	test2<std::basic_string<CharT>, std::basic_string<CharT>>(str, delim, escape, unquoted_str, quoted_str, false);
	test2<std::basic_string<CharT> const&, std::basic_string<CharT>>(str, delim, escape, unquoted_str, quoted_str, true);
	test2<std::basic_string<CharT> const&, std::basic_string<CharT>>(str, delim, escape, unquoted_str, quoted_str, false);
	test2<hamon::basic_string_view<CharT>, hamon::basic_string<CharT>>(str, delim, escape, unquoted_str, quoted_str, true);
	test2<hamon::basic_string_view<CharT>, hamon::basic_string<CharT>>(str, delim, escape, unquoted_str, quoted_str, false);
#if defined(HAMON_HAS_STD_STRING_VIEW)
	test2<std::basic_string_view<CharT>, std::basic_string<CharT>>(str, delim, escape, unquoted_str, quoted_str, true);
	test2<std::basic_string_view<CharT>, std::basic_string<CharT>>(str, delim, escape, unquoted_str, quoted_str, false);
#endif
}

GTEST_TEST(IOManipTest, QuotedTest)
{
	test("abc",       '\"', '\\', "abc",     "\"abc\"");
	test("a\"b\"c",   '\"', '\\', "a\"b\"c", "\"a\\\"b\\\"c\"");
	test("a b c",     '\"', '\\', "a",       "\"a");
	test("\"abc\"",   '\"', '\\', "abc",     "\"\\\"abc\\\"\"");
	test("\"a b c\"", '\"', '\\', "a b c",   "\"\\\"a");
	test("abc",       '!',  '\\', "abc",     "!abc!");
	test("a$b$c",     '$',  '%',  "a$b$c",   "$a%$b%$c$");
}

}	// namespace quoted_test

}	// namespace iomanip_test
