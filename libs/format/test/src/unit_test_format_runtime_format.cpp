/**
 *	@file	unit_test_format_runtime_format.cpp
 *
 *	@brief	runtime_format のテスト
 *
 *	runtime-format-string<char> runtime_format(string_view fmt) noexcept { return fmt; }
 *	runtime-format-string<wchar_t> runtime_format(wstring_view fmt) noexcept { return fmt; }
 */

#include <hamon/format/format.hpp>
#include <hamon/format/runtime_format.hpp>
#include <hamon/format/format_error.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "format_test_helper.hpp"
#include "format_test.hpp"
#include "format_test_exceptions.hpp"

namespace hamon_format_test
{

namespace runtime_format_test
{

struct TestFunction
{
	template <typename CharT, typename... Args>
	void operator()(hamon::basic_string_view<CharT> expected, hamon::basic_string_view<CharT> fmt, Args&&... args) const
	{
		hamon::basic_string<CharT> out = hamon::format(hamon::runtime_format(fmt), hamon::forward<Args>(args)...);
		EXPECT_EQ(expected, out);
	}
};

struct TestExceptionsFunction
{
	template <typename CharT, typename... Args>
	void operator()(hamon::basic_string_view<CharT> fmt, Args&&... args) const
	{
		EXPECT_THROW(hamon::format(hamon::runtime_format(fmt), hamon::forward<Args>(args)...),
			hamon::format_error);
	}

	template <typename CharT, typename... Args>
	void operator()(bool is_throw, hamon::basic_string_view<CharT> fmt, Args&&... args) const
	{
		if (is_throw)
		{
			EXPECT_THROW(hamon::format(hamon::runtime_format(fmt), hamon::forward<Args>(args)...),
				hamon::format_error);
		}
		else
		{
			EXPECT_NO_THROW(hamon::format(hamon::runtime_format(fmt), hamon::forward<Args>(args)...));
		}
	}
};

GTEST_TEST(FormatTest, RuntimeFormatTest)
{
	test_full<char>(TestFunction{});
	test_full<wchar_t>(TestFunction{});
}

GTEST_TEST(FormatTest, RuntimeFormatExceptionsTest)
{
	test_exceptions<char>(TestExceptionsFunction{});
	test_exceptions<wchar_t>(TestExceptionsFunction{});
}

}	// namespace runtime_format_test

}	// namespace hamon_format_test
