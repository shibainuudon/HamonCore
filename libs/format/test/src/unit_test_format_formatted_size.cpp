/**
 *	@file	unit_test_format_formatted_size.cpp
 *
 *	@brief	formatted_size のテスト
 *
 *	template<class... Args>
 *	size_t formatted_size(format_string<Args...> fmt, Args&&... args);
 *
 *	template<class... Args>
 *	size_t formatted_size(wformat_string<Args...> fmt, Args&&... args);
 *
 *	template<class... Args>
 *	size_t formatted_size(const locale& loc, format_string<Args...> fmt, Args&&... args);
 *	
 *	template<class... Args>
 *	size_t formatted_size(const locale& loc, wformat_string<Args...> fmt, Args&&... args);
 */

#include <hamon/format/formatted_size.hpp>
#include <hamon/utility/forward.hpp>
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

namespace formatted_size_test
{

struct TestFunction
{
	template <typename CharT, typename... Args>
	void operator()(hamon::basic_string_view<CharT> expected, test_format_string_t<CharT, Args...> fmt, Args&&... args) const
	{
		hamon::size_t size = hamon::formatted_size(fmt, hamon::forward<Args>(args)...);
		EXPECT_EQ(expected.size(), size);

		// locale
		(*this)(expected, std::locale(), fmt, hamon::forward<Args>(args)...);
	}

	template <typename CharT, typename... Args>
	void operator()(hamon::basic_string_view<CharT> expected, std::locale const& loc, test_format_string_t<CharT, Args...> fmt, Args&&... args) const
	{
		hamon::size_t size = hamon::formatted_size(loc, fmt, hamon::forward<Args>(args)...);
		EXPECT_EQ(expected.size(), size);
	}
};

GTEST_TEST(FormatTest, FormattedSizeTest)
{
	test_partial<char>(TestFunction{});
	test_partial<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormattedSizeTupleTest)
{
	test_tuple<char>(TestFunction{});
	test_tuple<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormattedSizeMapTest)
{
	test_map<char>(TestFunction{});
	test_map<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormattedSizeSetTest)
{
	test_set<char>(TestFunction{});
	test_set<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormattedSizeSequenceTest)
{
	test_sequence<char>(TestFunction{});
	test_sequence<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormattedSizeStringTest)
{
	test_string<char>(TestFunction{});
	test_string<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormattedSizeUnicodeTest)
{
#if !defined(HAMON_MSVC)
	// MSVCでCharTがcharのとき、テストに失敗してしまう TODO
	test_unicode<char>(TestFunction{});
#endif
	test_unicode<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormattedSizeLocaleTest)
{
	test_locale<char>(TestFunction{});
	test_locale<wchar_t>(TestFunction{});
}

}	// namespace formatted_size_test

}	// namespace hamon_format_test
