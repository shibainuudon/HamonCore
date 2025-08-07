/**
 *	@file	unit_test_format_format_to_n.cpp
 *
 *	@brief	format_to_n のテスト
 *
 *	template<class Out, class... Args>
 *	format_to_n_result<Out> format_to_n(Out out, iter_difference_t<Out> n, format_string<Args...> fmt, Args&&... args);
 *
 *	template<class Out, class... Args>
 *	format_to_n_result<Out> format_to_n(Out out, iter_difference_t<Out> n, wformat_string<Args...> fmt, Args&&... args);
 *
 *	template<class Out, class... Args>
 *	format_to_n_result<Out> format_to_n(Out out, iter_difference_t<Out> n, const locale& loc, format_string<Args...> fmt, Args&&... args);
 *
 *	template<class Out, class... Args>
 *	format_to_n_result<Out> format_to_n(Out out, iter_difference_t<Out> n, const locale& loc, wformat_string<Args...> fmt, Args&&... args);
 */

#include <hamon/format/format_to_n.hpp>
#include <hamon/format/format_to_n_result.hpp>
#include <hamon/format/formatted_size.hpp>
#include <hamon/algorithm/equal.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/iterator/back_inserter.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/list.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits/is_signed.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
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

namespace format_to_n_test
{

struct TestFunction
{
	template <typename CharT, typename... Args>
	void operator()(hamon::basic_string_view<CharT> expected, test_format_string_t<CharT, Args...> fmt, Args&&... args) const
	{
		{
			hamon::list<CharT> out;
			hamon::format_to_n_result result = hamon::format_to_n(hamon::back_inserter(out), 0, fmt, hamon::forward<Args>(args)...);
			// To avoid signedness warnings make sure formatted_size uses the same type
			// as result.size.
			using diff_type = decltype(result.size);
			auto formatted_size = hamon::formatted_size(fmt, hamon::forward<Args>(args)...);

			EXPECT_TRUE(result.size == static_cast<diff_type>(formatted_size));
			EXPECT_TRUE(out.empty());
		}
		{
			hamon::vector<CharT> out;
			hamon::format_to_n_result result = hamon::format_to_n(hamon::back_inserter(out), 5, fmt, hamon::forward<Args>(args)...);
			using diff_type = decltype(result.size);
			auto formatted_size = hamon::formatted_size(fmt, hamon::forward<Args>(args)...);
			auto size = hamon::min<hamon::size_t>(5, formatted_size);

			EXPECT_TRUE(result.size == static_cast<diff_type>(formatted_size));
			EXPECT_TRUE(hamon::equal(out.begin(), out.end(), expected.begin(), expected.begin() + size));
		}
		{
			hamon::basic_string<CharT> out;
			hamon::format_to_n_result result = hamon::format_to_n(hamon::back_inserter(out), 1000, fmt, hamon::forward<Args>(args)...);
			using diff_type = decltype(result.size);
			auto formatted_size = hamon::formatted_size(fmt, hamon::forward<Args>(args)...);
			auto size = hamon::min<hamon::size_t>(1000, formatted_size);

			EXPECT_TRUE(result.size == static_cast<diff_type>(formatted_size));
			EXPECT_TRUE(out == expected.substr(0, size));
		}
		{
			// Test the returned iterator.
			hamon::basic_string<CharT> out(10, CharT(' '));
			hamon::format_to_n_result result = hamon::format_to_n(out.begin(), 10, fmt, hamon::forward<Args>(args)...);
			using diff_type = decltype(result.size);
			auto formatted_size = hamon::formatted_size(fmt, hamon::forward<Args>(args)...);
			auto size = hamon::min<hamon::size_t>(10, formatted_size);

			EXPECT_TRUE(result.size == static_cast<diff_type>(formatted_size));
			EXPECT_TRUE(result.out == out.begin() + size);
			EXPECT_TRUE(out.substr(0, size) == expected.substr(0, size));
		}
		{
			static_assert(hamon::is_signed_v<hamon::iter_difference_t<CharT*>>,
				"If the difference type isn't negative the test will fail "
				"due to using a large positive value.");
			CharT buffer[1] = { CharT(0) };
			hamon::format_to_n_result result = hamon::format_to_n(buffer, -1, fmt, hamon::forward<Args>(args)...);
			using diff_type = decltype(result.size);
			auto formatted_size = hamon::formatted_size(fmt, hamon::forward<Args>(args)...);

			EXPECT_TRUE(result.size == static_cast<diff_type>(formatted_size));
			EXPECT_TRUE(result.out == buffer);
			EXPECT_TRUE(buffer[0] == CharT(0));
		}

		// locale
		(*this)(expected, std::locale(), fmt, hamon::forward<Args>(args)...);
	}

	template <typename CharT, typename... Args>
	void operator()(hamon::basic_string_view<CharT> expected, std::locale const& loc, test_format_string_t<CharT, Args...> fmt, Args&&... args) const
	{
		{
			hamon::list<CharT> out;
			hamon::format_to_n_result result = hamon::format_to_n(hamon::back_inserter(out), 0, loc, fmt, hamon::forward<Args>(args)...);
			// To avoid signedness warnings make sure formatted_size uses the same type
			// as result.size.
			using diff_type = decltype(result.size);
			auto formatted_size = hamon::formatted_size(loc, fmt, hamon::forward<Args>(args)...);

			EXPECT_TRUE(result.size == static_cast<diff_type>(formatted_size));
			EXPECT_TRUE(out.empty());
		}
		{
			hamon::vector<CharT> out;
			hamon::format_to_n_result result = hamon::format_to_n(hamon::back_inserter(out), 5, loc, fmt, hamon::forward<Args>(args)...);
			using diff_type = decltype(result.size);
			auto formatted_size = hamon::formatted_size(loc, fmt, hamon::forward<Args>(args)...);
			auto size = hamon::min<hamon::size_t>(5, formatted_size);

			EXPECT_TRUE(result.size == static_cast<diff_type>(formatted_size));
			EXPECT_TRUE(hamon::equal(out.begin(), out.end(), expected.begin(), expected.begin() + size));
		}
		{
			hamon::basic_string<CharT> out;
			hamon::format_to_n_result result = hamon::format_to_n(hamon::back_inserter(out), 1000, loc, fmt, hamon::forward<Args>(args)...);
			using diff_type = decltype(result.size);
			auto formatted_size = hamon::formatted_size(loc, fmt, hamon::forward<Args>(args)...);
			auto size = hamon::min<hamon::size_t>(1000, formatted_size);

			EXPECT_TRUE(result.size == static_cast<diff_type>(formatted_size));
			EXPECT_TRUE(out == expected.substr(0, size));
		}
		{
			// Test the returned iterator.
			hamon::basic_string<CharT> out(10, CharT(' '));
			hamon::format_to_n_result result = hamon::format_to_n(out.begin(), 10, loc, fmt, hamon::forward<Args>(args)...);
			using diff_type = decltype(result.size);
			auto formatted_size = hamon::formatted_size(loc, fmt, hamon::forward<Args>(args)...);
			auto size = hamon::min<hamon::size_t>(10, formatted_size);

			EXPECT_TRUE(result.size == static_cast<diff_type>(formatted_size));
			EXPECT_TRUE(result.out == out.begin() + size);
			EXPECT_TRUE(out.substr(0, size) == expected.substr(0, size));
		}
		{
			static_assert(hamon::is_signed_v<hamon::iter_difference_t<CharT*>>,
				"If the difference type isn't negative the test will fail "
				"due to using a large positive value.");
			CharT buffer[1] = { CharT(0) };
			hamon::format_to_n_result result = hamon::format_to_n(buffer, -1, loc, fmt, hamon::forward<Args>(args)...);
			using diff_type = decltype(result.size);
			auto formatted_size = hamon::formatted_size(loc, fmt, hamon::forward<Args>(args)...);

			EXPECT_TRUE(result.size == static_cast<diff_type>(formatted_size));
			EXPECT_TRUE(result.out == buffer);
			EXPECT_TRUE(buffer[0] == CharT(0));
		}
	}
};

GTEST_TEST(FormatTest, FormatToNTest)
{
	test_partial<char>(TestFunction{});
	test_partial<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormatToNTupleTest)
{
	test_tuple<char>(TestFunction{});
	test_tuple<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormatToNMapTest)
{
	test_map<char>(TestFunction{});
	test_map<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormatToNSetTest)
{
	test_set<char>(TestFunction{});
	test_set<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormatToNSequenceTest)
{
	test_sequence<char>(TestFunction{});
	test_sequence<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormatToNStringTest)
{
	test_string<char>(TestFunction{});
	test_string<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormatToNUnicodeTest)
{
#if !defined(HAMON_MSVC)
	// MSVCでCharTがcharのとき、テストに失敗してしまう TODO
	test_unicode<char>(TestFunction{});
#endif
	test_unicode<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, FormatToNLocaleTest)
{
	test_locale<char>(TestFunction{});
	test_locale<wchar_t>(TestFunction{});
}

}	// namespace format_to_n_test

}	// namespace hamon_format_test
