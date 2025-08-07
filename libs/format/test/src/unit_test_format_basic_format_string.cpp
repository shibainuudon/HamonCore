/**
 *	@file	unit_test_format_basic_format_string.cpp
 *
 *	@brief	basic_format_string のテスト
 *
 *	template<class charT, class... Args>
 *	struct basic_format_string;
 */

#include <hamon/format/basic_format_string.hpp>
#include <hamon/format/format_string.hpp>
#include <hamon/format/wformat_string.hpp>
#include <hamon/format/runtime_format.hpp>
#include <hamon/string_view.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_format_test
{

namespace basic_format_string_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

#define CSTR(Str)	HAMON_STATICALLY_WIDEN(CharT, Str)
#define SV(Str)		hamon::basic_string_view<CharT>(HAMON_STATICALLY_WIDEN(CharT, Str), sizeof(Str) - 1)

template <typename CharT>
HAMON_CXX20_CONSTEXPR bool test()
{
	VERIFY((hamon::basic_format_string<CharT>{CSTR("foo")}.get() == SV("foo")));
	VERIFY((hamon::basic_format_string<CharT, int>{CSTR("{}")}.get() == SV("{}")));
	VERIFY((hamon::basic_format_string<CharT, int, char>{CSTR("{} {:*>6}")}.get() == SV("{} {:*>6}")));

	// Embedded NUL character
	VERIFY((hamon::basic_format_string<CharT, void*, bool>{SV("{}\0{}")}.get() == SV("{}\0{}")));

	return true;
}

template <typename CharT>
bool test_runtime_format_string()
{
	static_assert(noexcept(hamon::format_string<>{hamon::runtime_format(hamon::string_view{})}));
	static_assert(noexcept(hamon::wformat_string<>{hamon::runtime_format(hamon::wstring_view{})}));
	{
		hamon::basic_format_string<CharT> s = hamon::runtime_format(CSTR("}{invalid format string}{"));
		VERIFY(s.get() == SV("}{invalid format string}{"));
	}
	return true;
}

#undef CSTR
#undef SV

#undef VERIFY

GTEST_TEST(FormatTest, BasicFormatStringTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<wchar_t>());

	EXPECT_TRUE(test_runtime_format_string<char>());
	EXPECT_TRUE(test_runtime_format_string<wchar_t>());
}

}	// namespace basic_format_string_test

}	// namespace hamon_format_test
