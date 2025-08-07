/**
 *	@file	unit_test_format_runtime_format_string.cpp
 *
 *	@brief	runtime-format-string のテスト
 *
 *	template<class charT> struct runtime-format-string {                  // exposition only
 *	private:
 *		basic_string_view<charT> str;                                       // exposition only
 *	public:
 *		runtime-format-string(basic_string_view<charT> s) noexcept : str(s) {}
 *		runtime-format-string(const runtime-format-string&) = delete;
 *		runtime-format-string& operator=(const runtime-format-string&) = delete;
 *	};
 *	runtime-format-string<char> runtime_format(string_view fmt) noexcept { return fmt; }
 *	runtime-format-string<wchar_t> runtime_format(wstring_view fmt) noexcept { return fmt; }
 */

#include <hamon/format/runtime_format.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>

namespace hamon_format_test
{

namespace runtime_format_string_test
{

template <class CharT>
static void test()
{
	using StringView = hamon::basic_string_view<CharT>;

	static_assert(noexcept(hamon::runtime_format(StringView{})));
	auto format_string = hamon::runtime_format(StringView{});

	using FormatString = decltype(format_string);
	static_assert(hamon::is_same<FormatString, hamon::detail::runtime_format_string<CharT>>::value, "");

	static_assert(hamon::is_nothrow_convertible<StringView, FormatString>::value, "");
	static_assert(hamon::is_nothrow_constructible<FormatString, StringView>::value, "");

	static_assert(!hamon::is_copy_constructible<FormatString>::value, "");
	static_assert(!hamon::is_copy_assignable<FormatString>::value, "");

	static_assert(!hamon::is_move_constructible<FormatString>::value, "");
	static_assert(!hamon::is_move_assignable<FormatString>::value, "");
}

GTEST_TEST(FormatTest, RuntimeFormatStringTest)
{
	test<char>();
	test<wchar_t>();
}

}	// namespace runtime_format_string_test

}	// namespace hamon_format_test
