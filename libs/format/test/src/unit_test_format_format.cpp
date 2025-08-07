/**
 *	@file	unit_test_format_format.cpp
 *
 *	@brief	format のテスト
 *
 *	template<class... Args>
 *	string format(format_string<Args...> fmt, Args&&... args);
 *
 *	template<class... Args>
 *	wstring format(wformat_string<Args...> fmt, Args&&... args);
 *
 *	template<class... Args>
 *	string format(const locale& loc, format_string<Args...> fmt, Args&&... args);
 *
 *	template<class... Args>
 *	wstring format(const locale& loc, wformat_string<Args...> fmt, Args&&... args);
 */

#include <hamon/format/format.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
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

namespace format_test
{

struct TestFunction
{
	template <typename CharT, typename... Args>
	void operator()(hamon::basic_string_view<CharT> expected, test_format_string_t<CharT, Args...> fmt, Args&&... args) const
	{
		hamon::basic_string<CharT> out = hamon::format(fmt, hamon::forward<Args>(args)...);
		EXPECT_EQ(expected, out);

		// locale
		(*this)(expected, std::locale(), fmt, hamon::forward<Args>(args)...);
	}

	template <typename CharT, typename... Args>
	void operator()(hamon::basic_string_view<CharT> expected, std::locale const& loc, test_format_string_t<CharT, Args...> fmt, Args&&... args) const
	{
		hamon::basic_string<CharT> out = hamon::format(loc, fmt, hamon::forward<Args>(args)...);
		EXPECT_EQ(expected, out);
	}
};

GTEST_TEST(FormatTest, FormatTest)
{
	test_full<char>(TestFunction{});
	test_full<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormatTupleTest)
{
	test_tuple<char>(TestFunction{});
	test_tuple<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormatMapTest)
{
	test_map<char>(TestFunction{});
	test_map<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormatSetTest)
{
	test_set<char>(TestFunction{});
	test_set<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormatSequenceTest)
{
	test_sequence<char>(TestFunction{});
	test_sequence<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormatStringTest)
{
	test_string<char>(TestFunction{});
	test_string<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormatUnicodeTest)
{
#if !defined(HAMON_MSVC)
	// MSVCでCharTがcharのとき、テストに失敗してしまう TODO
	test_unicode<char>(TestFunction{});
#endif
	test_unicode<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormatLocaleTest)
{
	test_locale<char>(TestFunction{});
	test_locale<wchar_t>(TestFunction{});
}

}	// namespace format_test

}	// namespace hamon_format_test
