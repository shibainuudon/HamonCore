/**
 *	@file	unit_test_format_format_to.cpp
 *
 *	@brief	format_to のテスト
 *
 *	template<class Out, class... Args>
 *	Out format_to(Out out, format_string<Args...> fmt, Args&&... args);
 *
 *	template<class Out, class... Args>
 *	Out format_to(Out out, wformat_string<Args...> fmt, Args&&... args);
 *
 *	template<class Out, class... Args>
 *	Out format_to(Out out, const locale& loc, format_string<Args...> fmt, Args&&... args);
 *
 *	template<class Out, class... Args>
 *	Out format_to(Out out, const locale& loc, wformat_string<Args...> fmt, Args&&... args);
 */

#include <hamon/format/format_to.hpp>
#include <hamon/algorithm/equal.hpp>
#include <hamon/iterator/back_inserter.hpp>
#include <hamon/list.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include <locale>
#include "constexpr_test.hpp"
#include "format_test_helper.hpp"
#include "format_test.hpp"
#include "format_test_tuple.hpp"
#include "format_test_map.hpp"
#include "format_test_set.hpp"
#include "format_test_sequence.hpp"
#include "format_test_string.hpp"
#include "format_test_unicode.hpp"
#include "format_test_locale.hpp"

namespace hamon_format_test
{

namespace format_to_test
{

struct TestFunction
{
	template <typename CharT, typename... Args>
	void operator()(hamon::basic_string_view<CharT> expected, test_format_string_t<CharT, Args...> fmt, Args&&... args) const
	{
		{
			hamon::basic_string<CharT> out(expected.size(), CharT(' '));
			auto it = hamon::format_to(out.begin(), fmt, hamon::forward<Args>(args)...);
			EXPECT_TRUE(it == out.end());
			EXPECT_EQ(expected, out);
		}
		{
			hamon::list<CharT> out;
			hamon::format_to(hamon::back_inserter(out), fmt, hamon::forward<Args>(args)...);
			EXPECT_TRUE(hamon::equal(out.begin(), out.end(), expected.begin(), expected.end()));
		}
		{
			hamon::vector<CharT> out;
			hamon::format_to(hamon::back_inserter(out), fmt, hamon::forward<Args>(args)...);
			EXPECT_TRUE(hamon::equal(out.begin(), out.end(), expected.begin(), expected.end()));
		}
		{
			assert(expected.size() < 4096 && "Update the size of the buffer.");
			CharT out[4096];
			auto it = hamon::format_to(out, fmt, hamon::forward<Args>(args)...);
			EXPECT_TRUE(hamon::distance(out, it) == int(expected.size()));
			// Convert to std::string since output contains '\0' for boolean tests.
			EXPECT_EQ(expected, hamon::basic_string<CharT>(out, it));
		}

		// locale
		(*this)(expected, std::locale(), fmt, hamon::forward<Args>(args)...);
	}

	template <typename CharT, typename... Args>
	void operator()(hamon::basic_string_view<CharT> expected, std::locale const& loc, test_format_string_t<CharT, Args...> fmt, Args&&... args) const
	{
		{
			hamon::basic_string<CharT> out(expected.size(), CharT(' '));
			auto it = hamon::format_to(out.begin(), loc, fmt, hamon::forward<Args>(args)...);
			EXPECT_TRUE(it == out.end());
			EXPECT_EQ(expected, out);
		}
		{
			hamon::list<CharT> out;
			hamon::format_to(hamon::back_inserter(out), loc, fmt, hamon::forward<Args>(args)...);
			EXPECT_TRUE(hamon::equal(out.begin(), out.end(), expected.begin(), expected.end()));
		}
		{
			hamon::vector<CharT> out;
			hamon::format_to(hamon::back_inserter(out), loc, fmt, hamon::forward<Args>(args)...);
			EXPECT_TRUE(hamon::equal(out.begin(), out.end(), expected.begin(), expected.end()));
		}
		{
			assert(expected.size() < 4096 && "Update the size of the buffer.");
			CharT out[4096];
			auto it = hamon::format_to(out, loc, fmt, hamon::forward<Args>(args)...);
			EXPECT_TRUE(hamon::distance(out, it) == int(expected.size()));
			// Convert to std::string since output contains '\0' for boolean tests.
			EXPECT_EQ(expected, hamon::basic_string<CharT>(out, it));
		}
	}
};

GTEST_TEST(FormatTest, FormatToTest)
{
	test_partial<char>(TestFunction{});
	test_partial<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormatToTupleTest)
{
	test_tuple<char>(TestFunction{});
	test_tuple<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormatToMapTest)
{
	test_map<char>(TestFunction{});
	test_map<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormatToSetTest)
{
	test_set<char>(TestFunction{});
	test_set<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormatToSequenceTest)
{
	test_sequence<char>(TestFunction{});
	test_sequence<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormatToStringTest)
{
	test_string<char>(TestFunction{});
	test_string<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormatToUnicodeTest)
{
#if !defined(HAMON_MSVC)
	// MSVCでCharTがcharのとき、テストに失敗してしまう TODO
	test_unicode<char>(TestFunction{});
#endif
	test_unicode<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormatToLocaleTest)
{
	test_locale<char>(TestFunction{});
	test_locale<wchar_t>(TestFunction{});
}

}	// namespace format_to_test

}	// namespace hamon_format_test
