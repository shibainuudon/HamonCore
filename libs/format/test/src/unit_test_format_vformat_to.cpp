/**
 *	@file	unit_test_format_vformat_to.cpp
 *
 *	@brief	vformat_to のテスト
 *
 *	template<class Out>
 *	Out vformat_to(Out out, string_view fmt, format_args args);
 *
 *	template<class Out>
 *	Out vformat_to(Out out, wstring_view fmt, wformat_args args);
 *
 *	template<class Out>
 *	Out vformat_to(Out out, const locale& loc, string_view fmt, format_args args);
 *
 *	template<class Out>
 *	Out vformat_to(Out out, const locale& loc, wstring_view fmt, wformat_args args);
 */

#include <hamon/format/vformat_to.hpp>
#include <hamon/format/make_format_args.hpp>
#include <hamon/format/format_error.hpp>
#include <hamon/algorithm/equal.hpp>
#include <hamon/iterator/back_inserter.hpp>
#include <hamon/list.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/vector.hpp>
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

namespace vformat_to_test
{

struct TestFunction
{
	template <typename CharT, typename... Args>
	void operator()(hamon::basic_string_view<CharT> expected, hamon::basic_string_view<CharT> fmt, Args&&... args) const
	{
		{
			hamon::basic_string<CharT> out(expected.size(), CharT(' '));
			auto it = hamon::vformat_to(out.begin(), fmt, hamon::make_format_args<test_format_context_t<CharT>>(args...));
			EXPECT_TRUE(it == out.end());
			EXPECT_EQ(expected, out);
		}
		{
			hamon::list<CharT> out;
			hamon::vformat_to(hamon::back_inserter(out), fmt, hamon::make_format_args<test_format_context_t<CharT>>(args...));
			EXPECT_TRUE(hamon::equal(out.begin(), out.end(), expected.begin(), expected.end()));
		}
		{
			hamon::vector<CharT> out;
			hamon::vformat_to(hamon::back_inserter(out), fmt, hamon::make_format_args<test_format_context_t<CharT>>(args...));
			EXPECT_TRUE(hamon::equal(out.begin(), out.end(), expected.begin(), expected.end()));
		}
		{
			assert(expected.size() < 4096 && "Update the size of the buffer.");
			CharT out[4096];
			auto it = hamon::vformat_to(out, fmt, hamon::make_format_args<test_format_context_t<CharT>>(args...));
			EXPECT_TRUE(hamon::distance(out, it) == int(expected.size()));
			// Convert to std::string since output contains '\0' for boolean tests.
			EXPECT_EQ(expected, hamon::basic_string<CharT>(out, it));
		}

		// locale
		(*this)(expected, std::locale(), fmt, hamon::forward<Args>(args)...);
	}

	template <typename CharT, typename... Args>
	void operator()(hamon::basic_string_view<CharT> expected, std::locale const& loc, hamon::basic_string_view<CharT> fmt, Args&&... args) const
	{
		{
			hamon::basic_string<CharT> out(expected.size(), CharT(' '));
			auto it = hamon::vformat_to(out.begin(), loc, fmt, hamon::make_format_args<test_format_context_t<CharT>>(args...));
			EXPECT_TRUE(it == out.end());
			EXPECT_EQ(expected, out);
		}
		{
			hamon::list<CharT> out;
			hamon::vformat_to(hamon::back_inserter(out), loc, fmt, hamon::make_format_args<test_format_context_t<CharT>>(args...));
			EXPECT_TRUE(hamon::equal(out.begin(), out.end(), expected.begin(), expected.end()));
		}
		{
			hamon::vector<CharT> out;
			hamon::vformat_to(hamon::back_inserter(out), loc, fmt, hamon::make_format_args<test_format_context_t<CharT>>(args...));
			EXPECT_TRUE(hamon::equal(out.begin(), out.end(), expected.begin(), expected.end()));
		}
		{
			assert(expected.size() < 4096 && "Update the size of the buffer.");
			CharT out[4096];
			auto it = hamon::vformat_to(out, loc, fmt, hamon::make_format_args<test_format_context_t<CharT>>(args...));
			EXPECT_TRUE(hamon::distance(out, it) == int(expected.size()));
			// Convert to std::string since output contains '\0' for boolean tests.
			EXPECT_EQ(expected, hamon::basic_string<CharT>(out, it));
		}
	}
};

struct TestExceptionsFunction
{
	template <typename CharT, typename... Args>
	void operator()(hamon::basic_string_view<CharT> fmt, Args&&... args) const
	{
		hamon::basic_string<CharT> out;
		EXPECT_THROW(hamon::vformat_to(hamon::back_inserter(out), fmt, hamon::make_format_args<test_format_context_t<CharT>>(args...)),
			hamon::format_error);
	}

	template <typename CharT, typename... Args>
	void operator()(bool is_throw, hamon::basic_string_view<CharT> fmt, Args&&... args) const
	{
		hamon::basic_string<CharT> out;
		if (is_throw)
		{
			EXPECT_THROW(hamon::vformat_to(hamon::back_inserter(out), fmt, hamon::make_format_args<test_format_context_t<CharT>>(args...)),
				hamon::format_error);
		}
		else
		{
			EXPECT_NO_THROW(hamon::vformat_to(hamon::back_inserter(out), fmt, hamon::make_format_args<test_format_context_t<CharT>>(args...)));
		}
	}
};

GTEST_TEST(FormatTest, VFormatToTest)
{
	test_partial<char>(TestFunction{});
	test_partial<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, VFormatToExceptionsTest)
{
	test_exceptions<char>(TestExceptionsFunction{});
	test_exceptions<wchar_t>(TestExceptionsFunction{});
}

GTEST_TEST(FormatTest, VFormatToTupleTest)
{
	test_tuple<char>(TestFunction{});
	test_tuple<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, VFormatToTupleExceptionsTest)
{
	test_tuple_exceptions<char>(TestExceptionsFunction{});
	test_tuple_exceptions<wchar_t>(TestExceptionsFunction{});
}

GTEST_TEST(FormatTest, VFormatToMapTest)
{
	test_map<char>(TestFunction{});
	test_map<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, VFormatToMapExceptionsTest)
{
	test_map_exceptions<char>(TestExceptionsFunction{});
	test_map_exceptions<wchar_t>(TestExceptionsFunction{});
}

GTEST_TEST(FormatTest, VFormatToSetTest)
{
	test_set<char>(TestFunction{});
	test_set<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, VFormatToSetExceptionsTest)
{
	test_set_exceptions<char>(TestExceptionsFunction{});
	test_set_exceptions<wchar_t>(TestExceptionsFunction{});
}

GTEST_TEST(FormatTest, VFormatToSequenceTest)
{
	test_sequence<char>(TestFunction{});
	test_sequence<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, VFormatToSequenceExceptionsTest)
{
	test_sequence_exceptions<char>(TestExceptionsFunction{});
	test_sequence_exceptions<wchar_t>(TestExceptionsFunction{});
}

GTEST_TEST(FormatTest, VFormatToStringTest)
{
	test_string<char>(TestFunction{});
	test_string<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, VFormatToStringExceptionsTest)
{
	test_string_exceptions<char>(TestExceptionsFunction{});
	test_string_exceptions<wchar_t>(TestExceptionsFunction{});
}

GTEST_TEST(FormatTest, VFormatToLocaleTest)
{
	test_locale<char>(TestFunction{});
	test_locale<wchar_t>(TestFunction{});
}

}	// namespace vformat_to_test

}	// namespace hamon_format_test
