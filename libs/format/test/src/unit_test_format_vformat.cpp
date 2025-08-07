/**
 *	@file	unit_test_format_vformat.cpp
 *
 *	@brief	vformat のテスト
 *
 *	string vformat(string_view fmt, format_args args);
 *	wstring vformat(wstring_view fmt, wformat_args args);
 *	string vformat(const locale& loc, string_view fmt, format_args args);
 *	wstring vformat(const locale& loc, wstring_view fmt, wformat_args args);
 */

#include <hamon/format/vformat.hpp>
#include <hamon/format/make_format_args.hpp>
#include <hamon/format/format_error.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <gtest/gtest.h>
#include <locale>
#include "constexpr_test.hpp"
#include "format_test_helper.hpp"
#include "format_test.hpp"
#include "format_test_exceptions.hpp"
#include "format_test_tuple.hpp"
#include "format_test_tuple_exceptions.hpp"
#include "format_test_map.hpp"
#include "format_test_map_exceptions.hpp"
#include "format_test_set.hpp"
#include "format_test_set_exceptions.hpp"
#include "format_test_sequence.hpp"
#include "format_test_sequence_exceptions.hpp"
#include "format_test_string.hpp"
#include "format_test_string_exceptions.hpp"
#include "format_test_locale.hpp"

namespace hamon_format_test
{

namespace vformat_test
{

struct TestFunction
{
	template <typename CharT, typename... Args>
	void operator()(hamon::basic_string_view<CharT> expected, hamon::basic_string_view<CharT> fmt, Args&&... args) const
	{
		hamon::basic_string<CharT> out = hamon::vformat(fmt, hamon::make_format_args<test_format_context_t<CharT>>(args...));
		EXPECT_EQ(expected, out);

		// locale
		(*this)(expected, std::locale(), fmt, hamon::forward<Args>(args)...);
	}

	template <typename CharT, typename... Args>
	void operator()(hamon::basic_string_view<CharT> expected, std::locale const& loc, hamon::basic_string_view<CharT> fmt, Args&&... args) const
	{
		hamon::basic_string<CharT> out = hamon::vformat(loc, fmt, hamon::make_format_args<test_format_context_t<CharT>>(args...));
		EXPECT_EQ(expected, out);
	}
};

struct TestExceptionsFunction
{
	template <typename CharT, typename... Args>
	void operator()(hamon::basic_string_view<CharT> fmt, Args&&... args) const
	{
		EXPECT_THROW(hamon::vformat(fmt, hamon::make_format_args<test_format_context_t<CharT>>(args...)),
			hamon::format_error);
	}

	template <typename CharT, typename... Args>
	void operator()(bool is_throw, hamon::basic_string_view<CharT> fmt, Args&&... args) const
	{
		if (is_throw)
		{
			EXPECT_THROW(hamon::vformat(fmt, hamon::make_format_args<test_format_context_t<CharT>>(args...)),
				hamon::format_error);
		}
		else
		{
			EXPECT_NO_THROW(hamon::vformat(fmt, hamon::make_format_args<test_format_context_t<CharT>>(args...)));
		}
	}
};

GTEST_TEST(FormatTest, VFormatTest)
{
	test_full<char>(TestFunction{});
	test_full<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, VFormatExceptionsTest)
{
	test_exceptions<char>(TestExceptionsFunction{});
	test_exceptions<wchar_t>(TestExceptionsFunction{});
}

GTEST_TEST(FormatTest, VFormatTupleTest)
{
	test_tuple<char>(TestFunction{});
	test_tuple<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, VFormatTupleExceptionsTest)
{
	test_tuple_exceptions<char>(TestExceptionsFunction{});
	test_tuple_exceptions<wchar_t>(TestExceptionsFunction{});
}

GTEST_TEST(FormatTest, VFormatMapTest)
{
	test_map<char>(TestFunction{});
	test_map<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, VFormatMapExceptionsTest)
{
	test_map_exceptions<char>(TestExceptionsFunction{});
	test_map_exceptions<wchar_t>(TestExceptionsFunction{});
}

GTEST_TEST(FormatTest, VFormatSetTest)
{
	test_set<char>(TestFunction{});
	test_set<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, VFormatSetExceptionsTest)
{
	test_set_exceptions<char>(TestExceptionsFunction{});
	test_set_exceptions<wchar_t>(TestExceptionsFunction{});
}

GTEST_TEST(FormatTest, VFormatSequenceTest)
{
	test_sequence<char>(TestFunction{});
	test_sequence<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, VFormatSequenceExceptionsTest)
{
	test_sequence_exceptions<char>(TestExceptionsFunction{});
	test_sequence_exceptions<wchar_t>(TestExceptionsFunction{});
}

GTEST_TEST(FormatTest, VFormatStringTest)
{
	test_string<char>(TestFunction{});
	test_string<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, VFormatStringExceptionsTest)
{
	test_string_exceptions<char>(TestExceptionsFunction{});
	test_string_exceptions<wchar_t>(TestExceptionsFunction{});
}

GTEST_TEST(FormatTest, VFormatLocaleTest)
{
	test_locale<char>(TestFunction{});
	test_locale<wchar_t>(TestFunction{});
}

}	// namespace vformat_test

}	// namespace hamon_format_test
