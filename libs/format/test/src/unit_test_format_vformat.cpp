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
#include <hamon/format/format_context.hpp>
#include <hamon/format/wformat_context.hpp>
#include <hamon/format/make_format_args.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_format_test
{

namespace vformat_test
{

// A user-defined type used to test the handle formatter.
enum class status : std::uint16_t { foo = 0xAAAA, bar = 0x5555, foobar = 0xAA55 };

}	// namespace vformat_test

}	// namespace hamon_format_test

// The formatter for a user-defined type used to test the handle formatter.
template <class CharT>
struct hamon::formatter<hamon_format_test::vformat_test::status, CharT>
{
	// During the 2023 Issaquah meeting LEWG made it clear a formatter is
	// required to call its parse function. LWG3892 Adds the wording for that
	// requirement. Therefore this formatter is initialized in an invalid state.
	// A call to parse sets it in a valid state and a call to format validates
	// the state.
	int type = -1;

	constexpr auto parse(basic_format_parse_context<CharT>& parse_ctx)
		-> decltype(parse_ctx.begin())
	{
		auto begin = parse_ctx.begin();
		auto end   = parse_ctx.end();
		type       = 0;
		if (begin == end)
		{
			return begin;
		}

		switch (*begin)
		{
		case CharT('x'):
			break;
		case CharT('X'):
			type = 1;
			break;
		case CharT('s'):
			type = 2;
			break;
		case CharT('}'):
			return begin;
		default:
			hamon::detail::throw_format_error("The type option contains an invalid value for a status formatting argument");
		}

		++begin;
		if (begin != end && *begin != CharT('}'))
		{
			hamon::detail::throw_format_error("The format specifier should consume the input or end with a '}'");
		}

		return begin;
	}

	template <class Out>
	auto format(hamon_format_test::vformat_test::status s, basic_format_context<Out, CharT>& ctx) const
		-> decltype(ctx.out())
	{
		const char* names[] = {"foo", "bar", "foobar"};
		char buffer[7];
		const char* begin = names[0];
		const char* end = names[0];
		switch (type)
		{
		case -1:
			hamon::detail::throw_format_error("The formatter's parse function has not been called.");

		case 0:
			begin = buffer;
			buffer[0] = '0';
			buffer[1] = 'x';
			end = std::to_chars(&buffer[2], hamon::end(buffer), static_cast<std::uint16_t>(s), 16).ptr;
			buffer[6] = '\0';
			break;

		case 1:
			begin = buffer;
			buffer[0] = '0';
			buffer[1] = 'X';
			end = std::to_chars(&buffer[2], hamon::end(buffer), static_cast<std::uint16_t>(s), 16).ptr;
			hamon::transform(static_cast<const char*>(&buffer[2]), end, &buffer[2], [](char c) {
				return static_cast<char>(std::toupper(c)); });
			buffer[6] = '\0';
			break;

		case 2:
			switch (s)
			{
			case hamon_format_test::vformat_test::status::foo:
				begin = names[0];
				break;
			case hamon_format_test::vformat_test::status::bar:
				begin = names[1];
				break;
			case hamon_format_test::vformat_test::status::foobar:
				begin = names[2];
				break;
			}
			end = begin + strlen(begin);
			break;
		}

		return hamon::copy(begin, end, ctx.out());
	}
};

namespace hamon_format_test
{

namespace vformat_test
{

template <class T>
struct context {};

template <>
struct context<char>
{
	using type = hamon::format_context;
};

template <>
struct context<wchar_t>
{
	using type = hamon::wformat_context;
};

template <class T>
using context_t = typename context<T>::type;


#define SV(Str)		hamon::basic_string_view<CharT>(HAMON_STATICALLY_WIDEN(CharT, Str), sizeof(Str) - 1)
#define STR(Str)	hamon::basic_string<CharT>(HAMON_STATICALLY_WIDEN(CharT, Str), sizeof(Str) - 1)

struct VFormat
{
	template <typename CharT, typename... Args>
	hamon::basic_string<CharT> operator()(hamon::basic_string_view<CharT> fmt, Args&&... args)
	{
		// 左辺値しか受け取らないので、forward<Args>(args)... とはしない
		return hamon::vformat(fmt, hamon::make_format_args<context_t<CharT>>(args...));
	}
};

struct VFormatLoc
{
	template <typename CharT, typename... Args>
	hamon::basic_string<CharT> operator()(hamon::basic_string_view<CharT> fmt, Args&&... args)
	{
		// 左辺値しか受け取らないので、forward<Args>(args)... とはしない
		return hamon::vformat(std::locale(), fmt, hamon::make_format_args<context_t<CharT>>(args...));
	}
};

template <typename Fn, typename CharT>
void test_escape()
{
	Fn vformat;

	// *** Test escaping  ***
	EXPECT_EQ(SV("{"), vformat(SV("{{")));
	EXPECT_EQ(SV("}"), vformat(SV("}}")));
	EXPECT_EQ(SV("{:^}"), vformat(SV("{{:^}}")));
	EXPECT_EQ(SV("{: ^}"), vformat(SV("{{:{}^}}"), CharT(' ')));
	EXPECT_EQ(SV("{:{}^}"), vformat(SV("{{:{{}}^}}")));
	EXPECT_EQ(SV("{:{ }^}"), vformat(SV("{{:{{{}}}^}}"), CharT(' ')));
}

template <typename Fn, typename CharT>
void test_arg_id()
{
	Fn vformat;

	// *** Test argument ID ***
	EXPECT_EQ(SV("hello false true"), vformat(SV("hello {0:} {1:}"), false, true));
	EXPECT_EQ(SV("hello true false"), vformat(SV("hello {1:} {0:}"), false, true));
}

template <typename Fn, typename CharT>
void test_many_args()
{
	Fn vformat;

	// *** Test many arguments ***

	// [format.args]/1
	// An instance of basic_format_args provides access to formatting arguments.
	// Implementations should optimize the representation of basic_format_args
	// for a small number of formatting arguments.
	//
	// These's no guidances what "a small number of formatting arguments" is.
	// - fmtlib uses a 15 elements
	// - libc++ uses 12 elements
	// - MSVC STL uses a different approach regardless of the number of arguments
	// - libstdc++ has no implementation yet
	// fmtlib and libc++ use a similar approach, this approach can support 16
	// elements (based on design choices both support less elements). This test
	// makes sure "the large number of formatting arguments" code path is tested.
	EXPECT_EQ(
		SV("1234567890\t1234567890"),
		vformat(SV("{}{}{}{}{}{}{}{}{}{}\t{}{}{}{}{}{}{}{}{}{}"),
		1,
		2,
		3,
		4,
		5,
		6,
		7,
		8,
		9,
		0,
		1,
		2,
		3,
		4,
		5,
		6,
		7,
		8,
		9,
		0));
}

template <typename Fn, typename CharT>
void test_buffer_copy()
{
	Fn vformat;

	// *** copy ***
	EXPECT_EQ(
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"),
		vformat(SV("{}"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	EXPECT_EQ(
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"),
		vformat(SV("{}"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	EXPECT_EQ(
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"),
		vformat(SV("{}"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	EXPECT_EQ(
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"),
		vformat(SV("{}"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	EXPECT_EQ(
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"),
		vformat(SV("{}"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	// *** copy + push_back ***

	EXPECT_EQ(
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"X"),
		vformat(SV("{}X"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	EXPECT_EQ(
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"X"),
		vformat(SV("{}X"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	EXPECT_EQ(
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"X"),
		vformat(SV("{}X"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	EXPECT_EQ(
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"X"),
		vformat(SV("{}X"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	EXPECT_EQ(
		SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"X"),
		vformat(SV("{}X"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	// ***  push_back + copy ***

	EXPECT_EQ(
		SV("X"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"),
		vformat(SV("X{}"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	EXPECT_EQ(
		SV("X"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"),
		vformat(SV("X{}"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	EXPECT_EQ(
		SV("X"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"),
		vformat(SV("X{}"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	EXPECT_EQ(
		SV("X"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"),
		vformat(SV("X{}"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	EXPECT_EQ(
		SV("X"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"),
		vformat(SV("X{}"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));
}

template <typename Fn, typename CharT>
void test_buffer_fill()
{
	Fn vformat;

	// *** fill ***
	EXPECT_EQ(
		SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"),
		vformat(SV("{:|<64}"), SV("")));

	EXPECT_EQ(
		SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"),
		vformat(SV("{:|<128}"), SV("")));

	EXPECT_EQ(
		SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"),
		vformat(SV("{:|<256}"), SV("")));

	EXPECT_EQ(
		SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"),
		vformat(SV("{:|<512}"), SV("")));

	EXPECT_EQ(
		SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"),
		vformat(SV("{:|<1024}"), SV("")));

	// *** fill + push_back ***

	EXPECT_EQ(
		SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"X"),
		vformat(SV("{:|<64}X"), SV("")));

	EXPECT_EQ(
		SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"X"),
		vformat(SV("{:|<128}X"), SV("")));

	EXPECT_EQ(
		SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"X"),
		vformat(SV("{:|<256}X"), SV("")));

	EXPECT_EQ(
		SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"X"),
		vformat(SV("{:|<512}X"), SV("")));

	EXPECT_EQ(
		SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"X"),
		vformat(SV("{:|<1024}X"), SV("")));

	// *** push_back + fill ***

	EXPECT_EQ(
		SV("X"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"),
		vformat(SV("X{:|<64}"), SV("")));

	EXPECT_EQ(
		SV("X"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"),
		vformat(SV("X{:|<128}"), SV("")));

	EXPECT_EQ(
		SV("X"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"),
		vformat(SV("X{:|<256}"), SV("")));

	EXPECT_EQ(
		SV("X"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"),
		vformat(SV("X{:|<512}"), SV("")));

	EXPECT_EQ(
		SV("X"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"),
		vformat(SV("X{:|<1024}"), SV("")));
}

template <typename F, typename CharT>
void test_invalid_format_strings()
{
	F vformat;

	// *** Test invalid format strings ***
	EXPECT_THROW(vformat(SV("{")), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:")), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:"), 42), hamon::format_error);

	EXPECT_THROW(vformat(SV("{0")), hamon::format_error);
	EXPECT_THROW(vformat(SV("{0:")), hamon::format_error);
	EXPECT_THROW(vformat(SV("{0:"), 42), hamon::format_error);

	EXPECT_THROW(vformat(SV("}")), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:}-}"), 42), hamon::format_error);

	EXPECT_THROW(vformat(SV("} ")), hamon::format_error);
	EXPECT_THROW(vformat(SV("{-"), 42), hamon::format_error);
	EXPECT_THROW(vformat(SV("hello {}")), hamon::format_error);
	EXPECT_THROW(vformat(SV("hello {0}")), hamon::format_error);
	EXPECT_THROW(vformat(SV("hello {1}"), 42), hamon::format_error);
}

template <typename Fn, typename CharT>
void test_char()
{
	Fn vformat;

	// *** Test char format argument ***
	EXPECT_EQ(SV("hello 09azAZ!"),
		vformat(SV("hello {}{}{}{}{}{}{}"),
			CharT('0'),
			CharT('9'),
			CharT('a'),
			CharT('z'),
			CharT('A'),
			CharT('Z'),
			CharT('!')));

	// `char` to `wchar_t` 
	EXPECT_EQ(SV("hello 09azA"),
		vformat(SV("hello {}{}{}{}{}"), '0', '9', 'a', 'z', 'A'));

	// ***** Char type *****
	// *** align-fill & width ***
	EXPECT_EQ(SV("answer is '*     '"), vformat(SV("answer is '{:6}'"),  CharT('*')));
	EXPECT_EQ(SV("answer is '     *'"), vformat(SV("answer is '{:>6}'"), CharT('*')));
	EXPECT_EQ(SV("answer is '*     '"), vformat(SV("answer is '{:<6}'"), CharT('*')));
	EXPECT_EQ(SV("answer is '  *   '"), vformat(SV("answer is '{:^6}'"), CharT('*')));

	EXPECT_EQ(SV("answer is '*     '"), vformat(SV("answer is '{:6c}'"),  CharT('*')));
	EXPECT_EQ(SV("answer is '     *'"), vformat(SV("answer is '{:>6c}'"), CharT('*')));
	EXPECT_EQ(SV("answer is '*     '"), vformat(SV("answer is '{:<6c}'"), CharT('*')));
	EXPECT_EQ(SV("answer is '  *   '"), vformat(SV("answer is '{:^6c}'"), CharT('*')));

	// The fill character ':' is allowed here (P0645) but not in ranges (P2286).
	EXPECT_EQ(SV("answer is ':::::*'"), vformat(SV("answer is '{::>6}'"), CharT('*')));
	EXPECT_EQ(SV("answer is '*:::::'"), vformat(SV("answer is '{::<6}'"), CharT('*')));
	EXPECT_EQ(SV("answer is '::*:::'"), vformat(SV("answer is '{::^6}'"), CharT('*')));

	EXPECT_EQ(SV("answer is '-----*'"), vformat(SV("answer is '{:->6c}'"), CharT('*')));
	EXPECT_EQ(SV("answer is '*-----'"), vformat(SV("answer is '{:-<6c}'"), CharT('*')));
	EXPECT_EQ(SV("answer is '--*---'"), vformat(SV("answer is '{:-^6c}'"), CharT('*')));

	// *** Sign ***
	EXPECT_THROW(vformat(SV("{:-}"), CharT('*')), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:+}"), CharT('*')), hamon::format_error);
	EXPECT_THROW(vformat(SV("{: }"), CharT('*')), hamon::format_error);

	EXPECT_THROW(vformat(SV("{:-c}"), CharT('*')), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:+c}"), CharT('*')), hamon::format_error);
	EXPECT_THROW(vformat(SV("{: c}"), CharT('*')), hamon::format_error);

	// *** alternate form ***
	EXPECT_THROW(vformat(SV("{:#}"),  CharT('*')), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:#c}"), CharT('*')), hamon::format_error);

	// *** zero-padding ***
	EXPECT_THROW(vformat(SV("{:0}"),  CharT('*')), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:0c}"), CharT('*')), hamon::format_error);

	// *** precision ***
	EXPECT_THROW(vformat(SV("{:.}"),   CharT('*')), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:.0}"),  CharT('*')), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:.42}"), CharT('*')), hamon::format_error);

	EXPECT_THROW(vformat(SV("{:.c}"),   CharT('*')), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:.0c}"),  CharT('*')), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:.42c}"), CharT('*')), hamon::format_error);

	// *** locale-specific form ***
	// Note it has no effect but it's allowed.
	EXPECT_EQ(SV("answer is '*'"), vformat(SV("answer is '{:L}'"),  '*'));
	EXPECT_EQ(SV("answer is '*'"), vformat(SV("answer is '{:Lc}'"), '*'));

	// *** type ***
	EXPECT_THROW   (vformat(SV("{:a}"), CharT('*')), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:A}"), CharT('*')), hamon::format_error);
	EXPECT_NO_THROW(vformat(SV("{:b}"), CharT('*')));
	EXPECT_NO_THROW(vformat(SV("{:B}"), CharT('*')));
	EXPECT_NO_THROW(vformat(SV("{:c}"), CharT('*')));
	EXPECT_NO_THROW(vformat(SV("{:d}"), CharT('*')));
	EXPECT_THROW   (vformat(SV("{:e}"), CharT('*')), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:E}"), CharT('*')), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:f}"), CharT('*')), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:F}"), CharT('*')), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:g}"), CharT('*')), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:G}"), CharT('*')), hamon::format_error);
	EXPECT_NO_THROW(vformat(SV("{:o}"), CharT('*')));
	EXPECT_THROW   (vformat(SV("{:p}"), CharT('*')), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:P}"), CharT('*')), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:s}"), CharT('*')), hamon::format_error);
	EXPECT_NO_THROW(vformat(SV("{:x}"), CharT('*')));
	EXPECT_NO_THROW(vformat(SV("{:X}"), CharT('*')));
//	EXPECT_NO_THROW(vformat(SV("{:?}"), CharT('*')));	// C++23
}

template <typename Fn, typename CharT>
void test_char_as_integer()
{
	Fn vformat;

	// *** align-fill & width ***
	EXPECT_EQ(SV("answer is '42'"), vformat(SV("answer is '{:<1d}'"), CharT('*')));

	EXPECT_EQ(SV("answer is '42'"),  vformat(SV("answer is '{:<2d}'"), CharT('*')));
	EXPECT_EQ(SV("answer is '42 '"), vformat(SV("answer is '{:<3d}'"), CharT('*')));

	EXPECT_EQ(SV("answer is '     42'"), vformat(SV("answer is '{:7d}'"),  CharT('*')));
	EXPECT_EQ(SV("answer is '     42'"), vformat(SV("answer is '{:>7d}'"), CharT('*')));
	EXPECT_EQ(SV("answer is '42     '"), vformat(SV("answer is '{:<7d}'"), CharT('*')));
	EXPECT_EQ(SV("answer is '  42   '"), vformat(SV("answer is '{:^7d}'"), CharT('*')));

	// The fill character ':' is allowed here (P0645) but not in ranges (P2286).
	EXPECT_EQ(SV("answer is ':::::42'"), vformat(SV("answer is '{::>7d}'"), CharT('*')));
	EXPECT_EQ(SV("answer is '42:::::'"), vformat(SV("answer is '{::<7d}'"), CharT('*')));
	EXPECT_EQ(SV("answer is '::42:::'"), vformat(SV("answer is '{::^7d}'"), CharT('*')));

	// Test whether zero padding is ignored
	EXPECT_EQ(SV("answer is '     42'"), vformat(SV("answer is '{:>07d}'"), CharT('*')));
	EXPECT_EQ(SV("answer is '42     '"), vformat(SV("answer is '{:<07d}'"), CharT('*')));
	EXPECT_EQ(SV("answer is '  42   '"), vformat(SV("answer is '{:^07d}'"), CharT('*')));

	// *** Sign ***
	EXPECT_EQ(SV("answer is 42"),  vformat(SV("answer is {:d}"),  CharT('*')));
	EXPECT_EQ(SV("answer is 42"),  vformat(SV("answer is {:-d}"), CharT('*')));
	EXPECT_EQ(SV("answer is +42"), vformat(SV("answer is {:+d}"), CharT('*')));
	EXPECT_EQ(SV("answer is  42"), vformat(SV("answer is {: d}"), CharT('*')));

	// *** alternate form ***
	EXPECT_EQ(SV("answer is +42"),       vformat(SV("answer is {:+#d}"), CharT('*')));
	EXPECT_EQ(SV("answer is +101010"),   vformat(SV("answer is {:+b}"),  CharT('*')));
	EXPECT_EQ(SV("answer is +0b101010"), vformat(SV("answer is {:+#b}"), CharT('*')));
	EXPECT_EQ(SV("answer is +0B101010"), vformat(SV("answer is {:+#B}"), CharT('*')));
	EXPECT_EQ(SV("answer is +52"),       vformat(SV("answer is {:+o}"),  CharT('*')));
	EXPECT_EQ(SV("answer is +052"),      vformat(SV("answer is {:+#o}"), CharT('*')));
	EXPECT_EQ(SV("answer is +2a"),       vformat(SV("answer is {:+x}"),  CharT('*')));
	EXPECT_EQ(SV("answer is +0x2a"),     vformat(SV("answer is {:+#x}"), CharT('*')));
	EXPECT_EQ(SV("answer is +2A"),       vformat(SV("answer is {:+X}"),  CharT('*')));
	EXPECT_EQ(SV("answer is +0X2A"),     vformat(SV("answer is {:+#X}"), CharT('*')));

	// *** zero-padding & width ***
	EXPECT_EQ(SV("answer is +00000000042"), vformat(SV("answer is {:+#012d}"), CharT('*')));
	EXPECT_EQ(SV("answer is +00000101010"), vformat(SV("answer is {:+012b}"),  CharT('*')));
	EXPECT_EQ(SV("answer is +0b000101010"), vformat(SV("answer is {:+#012b}"), CharT('*')));
	EXPECT_EQ(SV("answer is +0B000101010"), vformat(SV("answer is {:+#012B}"), CharT('*')));
	EXPECT_EQ(SV("answer is +00000000052"), vformat(SV("answer is {:+012o}"),  CharT('*')));
	EXPECT_EQ(SV("answer is +00000000052"), vformat(SV("answer is {:+#012o}"), CharT('*')));
	EXPECT_EQ(SV("answer is +0000000002a"), vformat(SV("answer is {:+012x}"),  CharT('*')));
	EXPECT_EQ(SV("answer is +0x00000002a"), vformat(SV("answer is {:+#012x}"), CharT('*')));
	EXPECT_EQ(SV("answer is +0000000002A"), vformat(SV("answer is {:+012X}"),  CharT('*')));

	EXPECT_EQ(SV("answer is +0X00000002A"), vformat(SV("answer is {:+#012X}"), CharT('*')));

	// *** precision ***
	EXPECT_THROW(vformat(SV("{:.d}"),   CharT('*')), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:.0d}"),  CharT('*')), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:.42d}"), CharT('*')), hamon::format_error);

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp
}

template <typename Fn, typename CharT, typename W, typename U>
void test_string_impl(const W& world, const U& universe)
{
	Fn vformat;

	// *** Valid input tests ***
	// Unused argument is ignored. TODO FMT what does the Standard mandate?
	EXPECT_EQ(SV("hello world"),              vformat(SV("hello {}"), world, universe));
	EXPECT_EQ(SV("hello world and universe"), vformat(SV("hello {} and {}"), world, universe));
	EXPECT_EQ(SV("hello world"),              vformat(SV("hello {0}"), world, universe));
	EXPECT_EQ(SV("hello universe"),           vformat(SV("hello {1}"), world, universe));
	EXPECT_EQ(SV("hello universe and world"), vformat(SV("hello {1} and {0}"), world, universe));

	EXPECT_EQ(SV("hello world"),    vformat(SV("hello {:_>}"),  world));
	EXPECT_EQ(SV("hello world   "), vformat(SV("hello {:8}"),   world));
	EXPECT_EQ(SV("hello    world"), vformat(SV("hello {:>8}"),  world));
	EXPECT_EQ(SV("hello ___world"), vformat(SV("hello {:_>8}"), world));
	EXPECT_EQ(SV("hello _world__"), vformat(SV("hello {:_^8}"), world));
	EXPECT_EQ(SV("hello world___"), vformat(SV("hello {:_<8}"), world));

	// The fill character ':' is allowed here (P0645) but not in ranges (P2286).
	EXPECT_EQ(SV("hello :::world"), vformat(SV("hello {::>8}"), world));
	EXPECT_EQ(SV("hello <<<world"), vformat(SV("hello {:<>8}"), world));
	EXPECT_EQ(SV("hello ^^^world"), vformat(SV("hello {:^>8}"), world));

	EXPECT_EQ(SV("hello $world"), vformat(SV("hello {:$>{}}"),   world, 6));
	EXPECT_EQ(SV("hello $world"), vformat(SV("hello {0:$>{1}}"), world, 6));
	EXPECT_EQ(SV("hello $world"), vformat(SV("hello {1:$>{0}}"), 6, world));

	EXPECT_EQ(SV("hello world"), vformat(SV("hello {:.5}"), world));
	EXPECT_EQ(SV("hello unive"), vformat(SV("hello {:.5}"), universe));

	EXPECT_EQ(SV("hello univer"), vformat(SV("hello {:.{}}"),   universe, 6));
	EXPECT_EQ(SV("hello univer"), vformat(SV("hello {0:.{1}}"), universe, 6));
	EXPECT_EQ(SV("hello univer"), vformat(SV("hello {1:.{0}}"), 6, universe));

	EXPECT_EQ(SV("hello %world%"), vformat(SV("hello {:%^7.7}"), world));
	EXPECT_EQ(SV("hello univers"), vformat(SV("hello {:%^7.7}"), universe));
	EXPECT_EQ(SV("hello %world%"), vformat(SV("hello {:%^{}.{}}"), world, 7, 7));
	EXPECT_EQ(SV("hello %world%"), vformat(SV("hello {0:%^{1}.{2}}"), world, 7, 7));
	EXPECT_EQ(SV("hello %world%"), vformat(SV("hello {0:%^{2}.{1}}"), world, 7, 7));
	EXPECT_EQ(SV("hello %world%"), vformat(SV("hello {1:%^{0}.{2}}"), 7, world, 7));

	EXPECT_EQ(SV("hello world"),   vformat(SV("hello {:_>s}"), world));
	EXPECT_EQ(SV("hello $world"),  vformat(SV("hello {:$>{}s}"), world, 6));
	EXPECT_EQ(SV("hello world"),   vformat(SV("hello {:.5s}"), world));
	EXPECT_EQ(SV("hello univer"),  vformat(SV("hello {:.{}s}"), universe, 6));
	EXPECT_EQ(SV("hello %world%"), vformat(SV("hello {:%^7.7s}"), world));

	EXPECT_EQ(SV("hello #####uni"), vformat(SV("hello {:#>8.3s}"), universe));
	EXPECT_EQ(SV("hello ##uni###"), vformat(SV("hello {:#^8.3s}"), universe));
	EXPECT_EQ(SV("hello uni#####"), vformat(SV("hello {:#<8.3s}"), universe));

	// *** sign ***
	EXPECT_THROW(vformat(SV("hello {:-}"), world), hamon::format_error);

	// *** alternate form ***
	EXPECT_THROW(vformat(SV("hello {:#}"), world), hamon::format_error);

	// *** zero-padding ***
	EXPECT_THROW(vformat(SV("hello {:0}"), world), hamon::format_error);

	// *** width ***
	// Width 0 allowed, but not useful for string arguments.
	EXPECT_EQ(SV("hello world"), vformat(SV("hello {:{}}"), world, 0));

	EXPECT_THROW(vformat(SV("hello {:{}}"), world, -1), hamon::format_error);
	EXPECT_THROW(vformat(SV("hello {:{}}"), world, unsigned(-1)), hamon::format_error);
	EXPECT_THROW(vformat(SV("hello {:{}}"), world), hamon::format_error);
	EXPECT_THROW(vformat(SV("hello {:{}}"), world, universe), hamon::format_error);
	EXPECT_THROW(vformat(SV("hello {:{0}}"), world, 1), hamon::format_error);
	EXPECT_THROW(vformat(SV("hello {0:{}}"), world, 1), hamon::format_error);
	// Arg-id may not have leading zeros.
	EXPECT_THROW(vformat(SV("hello {0:{01}}"), world, 1), hamon::format_error);

	// *** precision ***

	// Precision 0 allowed, but not useful for string arguments.
	EXPECT_EQ(SV("hello "), vformat(SV("hello {:.{}}"), world, 0));
	// Precision may have leading zeros. Secondly tests the value is still base 10.
	EXPECT_EQ(SV("hello 0123456789"), vformat(SV("hello {:.000010}"), STR("0123456789abcdef")));
	EXPECT_THROW(vformat(SV("hello {:.{}}"), world, -1), hamon::format_error);
	EXPECT_THROW(vformat(SV("hello {:.{}}"), world, ~0u), hamon::format_error);
	EXPECT_THROW(vformat(SV("hello {:.{}}"), world), hamon::format_error);
	EXPECT_THROW(vformat(SV("hello {:.{}}"), world, universe), hamon::format_error);
	EXPECT_THROW(vformat(SV("hello {:.{0}}"), world, 1), hamon::format_error);
	EXPECT_THROW(vformat(SV("hello {0:.{}}"), world, 1), hamon::format_error);
	// Arg-id may not have leading zeros.
	EXPECT_THROW(vformat(SV("hello {0:.{01}}"), world, 1), hamon::format_error);

	// *** locale-specific form ***
	EXPECT_THROW(vformat(SV("hello {:L}"), world), hamon::format_error);

	// *** type ***
	EXPECT_THROW   (vformat(SV("{:a}"), world), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:A}"), world), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:b}"), world), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:B}"), world), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:c}"), world), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:d}"), world), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:e}"), world), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:E}"), world), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:f}"), world), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:F}"), world), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:g}"), world), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:G}"), world), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:o}"), world), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:p}"), world), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:P}"), world), hamon::format_error);
	EXPECT_NO_THROW(vformat(SV("{:s}"), world));
	EXPECT_THROW   (vformat(SV("{:x}"), world), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:X}"), world), hamon::format_error);
//	EXPECT_NO_THROW(vformat(SV("{:?}"), world));	// C++23
}

template <typename Fn, typename CharT>
void test_string_unicode()
{
	// unicode.pass.cpp and ascii.pass.cpp have additional tests.
#if _LIBCPP_HAS_UNICODE	// TODO
	Fn vformat;

	// Make sure all possible types are tested. For clarity don't use macros.
	if constexpr (hamon::same_as<CharT, char>)
	{
		const char* c_string = "aßc";
		EXPECT_EQ(SV("*aßc*"), vformat(SV("{:*^5}"),   c_string));
		EXPECT_EQ(SV("*aß*"),  vformat(SV("{:*^4.2}"), c_string));

		EXPECT_EQ(SV("*aßc*"), vformat(SV("{:*^5}"),   const_cast<char*>(c_string)));
		EXPECT_EQ(SV("*aß*"),  vformat(SV("{:*^4.2}"), const_cast<char*>(c_string)));

		EXPECT_EQ(SV("*aßc*"), vformat(SV("{:*^5}"),   "aßc"));
		EXPECT_EQ(SV("*aß*"),  vformat(SV("{:*^4.2}"), "aßc"));

		EXPECT_EQ(SV("*aßc*"), vformat(SV("{:*^5}"),   hamon::string("aßc")));
		EXPECT_EQ(SV("*aß*"),  vformat(SV("{:*^4.2}"), hamon::string("aßc")));

		EXPECT_EQ(SV("*aßc*"), vformat(SV("{:*^5}"),   hamon::string_view("aßc")));
		EXPECT_EQ(SV("*aß*"),  vformat(SV("{:*^4.2}"), hamon::string_view("aßc")));
	}
	else
	{
		const wchar_t* c_string = L"aßc";
		EXPECT_EQ(SV("*aßc*"), vformat(SV("{:*^5}"),   c_string));
		EXPECT_EQ(SV("*aß*"),  vformat(SV("{:*^4.2}"), c_string));

		EXPECT_EQ(SV("*aßc*"), vformat(SV("{:*^5}"),   const_cast<wchar_t*>(c_string)));
		EXPECT_EQ(SV("*aß*"),  vformat(SV("{:*^4.2}"), const_cast<wchar_t*>(c_string)));

		EXPECT_EQ(SV("*aßc*"), vformat(SV("{:*^5}"),   L"aßc"));
		EXPECT_EQ(SV("*aß*"),  vformat(SV("{:*^4.2}"), L"aßc"));

		EXPECT_EQ(SV("*aßc*"), vformat(SV("{:*^5}"),   hamon::wstring(L"aßc")));
		EXPECT_EQ(SV("*aß*"),  vformat(SV("{:*^4.2}"), hamon::wstring(L"aßc")));

		EXPECT_EQ(SV("*aßc*"), vformat(SV("{:*^5}"),   hamon::wstring_view(L"aßc")));
		EXPECT_EQ(SV("*aß*"),  vformat(SV("{:*^4.2}"), hamon::wstring_view(L"aßc")));
	}

	// ß requires one column
	EXPECT_EQ(SV("aßc"), vformat(SV("{}"), STR("aßc")));

	EXPECT_EQ(SV("aßc"), vformat(SV("{:.3}"), STR("aßc")));
	EXPECT_EQ(SV("aß"),  vformat(SV("{:.2}"), STR("aßc")));
	EXPECT_EQ(SV("a"),   vformat(SV("{:.1}"), STR("aßc")));

	EXPECT_EQ(SV("aßc"), vformat(SV("{:3.3}"), STR("aßc")));
	EXPECT_EQ(SV("aß"),  vformat(SV("{:2.2}"), STR("aßc")));
	EXPECT_EQ(SV("a"),   vformat(SV("{:1.1}"), STR("aßc")));

	EXPECT_EQ(SV("aßc---"), vformat(SV("{:-<6}"), STR("aßc")));
	EXPECT_EQ(SV("-aßc--"), vformat(SV("{:-^6}"), STR("aßc")));
	EXPECT_EQ(SV("---aßc"), vformat(SV("{:->6}"), STR("aßc")));

	// \u1000 requires two columns
	EXPECT_EQ(SV("a\u1110c"), vformat(SV("{}"), STR("a\u1110c")));

	EXPECT_EQ(SV("a\u1100c"), vformat(SV("{:.4}"), STR("a\u1100c")));
	EXPECT_EQ(SV("a\u1100"),  vformat(SV("{:.3}"), STR("a\u1100c")));
	EXPECT_EQ(SV("a"),        vformat(SV("{:.2}"), STR("a\u1100c")));
	EXPECT_EQ(SV("a"),        vformat(SV("{:.1}"), STR("a\u1100c")));

	EXPECT_EQ(SV("a\u1100c"), vformat(SV("{:-<4.4}"), STR("a\u1100c")));
	EXPECT_EQ(SV("a\u1100"),  vformat(SV("{:-<3.3}"), STR("a\u1100c")));
	EXPECT_EQ(SV("a-"),       vformat(SV("{:-<2.2}"), STR("a\u1100c")));
	EXPECT_EQ(SV("a"),        vformat(SV("{:-<1.1}"), STR("a\u1100c")));

	EXPECT_EQ(SV("a\u1110c---"), vformat(SV("{:-<7}"), STR("a\u1110c")));
	EXPECT_EQ(SV("-a\u1110c--"), vformat(SV("{:-^7}"), STR("a\u1110c")));
	EXPECT_EQ(SV("---a\u1110c"), vformat(SV("{:->7}"), STR("a\u1110c")));

	// Examples used in P1868R2
	EXPECT_EQ(SV("*\u0041*"),       vformat(SV("{:*^3}"), STR("\u0041"))); // { LATIN CAPITAL LETTER A }
	EXPECT_EQ(SV("*\u00c1*"),       vformat(SV("{:*^3}"), STR("\u00c1"))); // { LATIN CAPITAL LETTER A WITH ACUTE }
	EXPECT_EQ(SV("*\u0041\u0301*"), vformat(SV("{:*^3}"), STR("\u0041\u0301")));	// { LATIN CAPITAL LETTER A } { COMBINING ACUTE ACCENT }
	EXPECT_EQ(SV("*\u0132*"),       vformat(SV("{:*^3}"), STR("\u0132"))); // { LATIN CAPITAL LIGATURE IJ }
	EXPECT_EQ(SV("*\u0394*"),       vformat(SV("{:*^3}"), STR("\u0394"))); // { GREEK CAPITAL LETTER DELTA }

	EXPECT_EQ(SV("*\u0429*"), vformat(SV("{:*^3}"), STR("\u0429")));         // { CYRILLIC CAPITAL LETTER SHCHA }
	EXPECT_EQ(SV("*\u05d0*"), vformat(SV("{:*^3}"), STR("\u05d0")));         // { HEBREW LETTER ALEF }
	EXPECT_EQ(SV("*\u0634*"), vformat(SV("{:*^3}"), STR("\u0634")));         // { ARABIC LETTER SHEEN }
	EXPECT_EQ(SV("*\u3009*"), vformat(SV("{:*^4}"), STR("\u3009")));         // { RIGHT-POINTING ANGLE BRACKET }
	EXPECT_EQ(SV("*\u754c*"), vformat(SV("{:*^4}"), STR("\u754c")));         // { CJK Unified Ideograph-754C }
	EXPECT_EQ(SV("*\U0001f921*"), vformat(SV("{:*^4}"), STR("\U0001f921"))); // { UNICORN FACE }
	EXPECT_EQ(SV("*\U0001f468\u200d\U0001F469\u200d\U0001F467\u200d\U0001F466*"),
		vformat(SV("{:*^4}"), STR("\U0001f468\u200d\U0001F469\u200d\U0001F467\u200d\U0001F466"))); // { Family: Man, Woman, Girl, Boy }
#endif // TEST_HAS_NO_UNICODE
}

template <typename Fn, typename CharT>
void test_string()
{
	Fn vformat;

	// *** Test string format argument ***
	{
		CharT buffer[] = {CharT('0'), CharT('9'), CharT('a'), CharT('z'), CharT('A'), CharT('Z'), CharT('!'), 0};
		CharT* data = buffer;
		EXPECT_EQ(SV("hello 09azAZ!"), vformat(SV("hello {}"), data));
	}
	{
		CharT buffer[] = {CharT('0'), CharT('9'), CharT('a'), CharT('z'), CharT('A'), CharT('Z'), CharT('!'), 0};
		const CharT* data = buffer;
		EXPECT_EQ(SV("hello 09azAZ!"), vformat(SV("hello {}"), data));
	}
	{
		// https://github.com/llvm/llvm-project/issues/115935
		// Contents after the embedded null character are discarded.
		CharT buffer[] = {CharT('a'), CharT('b'), CharT('c'), 0, CharT('d'), CharT('e'), CharT('f'), 0};
		EXPECT_EQ(SV("hello abc"), vformat(SV("hello {}"), buffer));
		// Even when the last element of the array is not null character.
		CharT buffer2[] = {CharT('a'), CharT('b'), CharT('c'), 0, CharT('d'), CharT('e'), CharT('f')};
		EXPECT_EQ(SV("hello abc"), vformat(SV("hello {}"), buffer2));
	}
	{
		hamon::basic_string<CharT> data = STR("world");
		EXPECT_EQ(SV("hello world"), vformat(SV("hello {}"), data));
	}
	{
		hamon::basic_string<CharT> buffer = STR("world");
		hamon::basic_string_view<CharT> data = buffer;
		EXPECT_EQ(SV("hello world"), vformat(SV("hello {}"), data));
	}

	CharT world[] = {CharT('w'), CharT('o'), CharT('r'), CharT('l'), CharT('d'), 0};
	CharT universe[] = {CharT('u'), CharT('n'), CharT('i'), CharT('v'), CharT('e'), CharT('r'), CharT('s'), CharT('e'), 0};

	test_string_impl<Fn, CharT>(world, universe);
	test_string_impl<Fn, CharT>(static_cast<CharT*>(world), static_cast<CharT*>(universe));
	test_string_impl<Fn, CharT>(static_cast<CharT const*>(world), static_cast<CharT const*>(universe));
	test_string_impl<Fn, CharT>(hamon::basic_string<CharT>(world), hamon::basic_string<CharT>(universe));
	test_string_impl<Fn, CharT>(hamon::basic_string_view<CharT>(world), hamon::basic_string_view<CharT>(universe));

	test_string_unicode<Fn, CharT>();
}

template <typename Fn, typename CharT>
void test_bool()
{
	Fn vformat;

	// *** Test Boolean format argument ***
	EXPECT_EQ(SV("hello false true"), vformat(SV("hello {} {}"), false, true));

	// *** align-fill & width ***
	EXPECT_EQ(SV("answer is 'true   '"), vformat(SV("answer is '{:7}'"),  true));
	EXPECT_EQ(SV("answer is '   true'"), vformat(SV("answer is '{:>7}'"), true));
	EXPECT_EQ(SV("answer is 'true   '"), vformat(SV("answer is '{:<7}'"), true));
	EXPECT_EQ(SV("answer is ' true  '"), vformat(SV("answer is '{:^7}'"), true));

	EXPECT_EQ(SV("answer is 'false   '"), vformat(SV("answer is '{:8s}'"),  false));
	EXPECT_EQ(SV("answer is '   false'"), vformat(SV("answer is '{:>8s}'"), false));
	EXPECT_EQ(SV("answer is 'false   '"), vformat(SV("answer is '{:<8s}'"), false));
	EXPECT_EQ(SV("answer is ' false  '"), vformat(SV("answer is '{:^8s}'"), false));

	// The fill character ':' is allowed here (P0645) but not in ranges (P2286).
	EXPECT_EQ(SV("answer is ':::true'"), vformat(SV("answer is '{::>7}'"), true));
	EXPECT_EQ(SV("answer is 'true:::'"), vformat(SV("answer is '{::<7}'"), true));
	EXPECT_EQ(SV("answer is ':true::'"), vformat(SV("answer is '{::^7}'"), true));

	EXPECT_EQ(SV("answer is '---false'"), vformat(SV("answer is '{:->8s}'"), false));
	EXPECT_EQ(SV("answer is 'false---'"), vformat(SV("answer is '{:-<8s}'"), false));
	EXPECT_EQ(SV("answer is '-false--'"), vformat(SV("answer is '{:-^8s}'"), false));

	// *** Sign ***
	EXPECT_THROW(vformat(SV("{:-}"), true), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:+}"), true), hamon::format_error);
	EXPECT_THROW(vformat(SV("{: }"), true), hamon::format_error);

	EXPECT_THROW(vformat(SV("{:-s}"), true), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:+s}"), true), hamon::format_error);
	EXPECT_THROW(vformat(SV("{: s}"), true), hamon::format_error);

	// *** alternate form ***
	EXPECT_THROW(vformat(SV("{:#}"),  true), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:#s}"), true), hamon::format_error);

	// *** zero-padding ***
	EXPECT_THROW(vformat(SV("{:0}"),  true), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:0s}"), true), hamon::format_error);

	// *** precision ***
	EXPECT_THROW(vformat(SV("{:.}"),   true), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:.0}"),  true), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:.42}"), true), hamon::format_error);

	EXPECT_THROW(vformat(SV("{:.s}"),   true), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:.0s}"),  true), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:.42s}"), true), hamon::format_error);

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp

	// *** type ***
	EXPECT_THROW   (vformat(SV("{:a}"), true), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:A}"), true), hamon::format_error);
	EXPECT_NO_THROW(vformat(SV("{:b}"), true));
	EXPECT_NO_THROW(vformat(SV("{:B}"), true));
	EXPECT_THROW   (vformat(SV("{:c}"), true), hamon::format_error);
	EXPECT_NO_THROW(vformat(SV("{:d}"), true));
	EXPECT_THROW   (vformat(SV("{:e}"), true), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:E}"), true), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:f}"), true), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:F}"), true), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:g}"), true), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:G}"), true), hamon::format_error);
	EXPECT_NO_THROW(vformat(SV("{:o}"), true));
	EXPECT_THROW   (vformat(SV("{:p}"), true), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:P}"), true), hamon::format_error);
	EXPECT_NO_THROW(vformat(SV("{:s}"), true));
	EXPECT_NO_THROW(vformat(SV("{:x}"), true));
	EXPECT_NO_THROW(vformat(SV("{:X}"), true));
//	EXPECT_THROW   (vformat(SV("{:?}"), true), hamon::format_error);	// C++23
}

template <typename Fn, typename CharT>
void test_bool_as_integer()
{
	Fn vformat;

	// *** align-fill & width ***
	EXPECT_EQ(SV("answer is '1'"),  vformat(SV("answer is '{:<1d}'"), true));
	EXPECT_EQ(SV("answer is '1 '"), vformat(SV("answer is '{:<2d}'"), true));
	EXPECT_EQ(SV("answer is '0 '"), vformat(SV("answer is '{:<2d}'"), false));

	EXPECT_EQ(SV("answer is '     1'"), vformat(SV("answer is '{:6d}'"),  true));
	EXPECT_EQ(SV("answer is '     1'"), vformat(SV("answer is '{:>6d}'"), true));
	EXPECT_EQ(SV("answer is '1     '"), vformat(SV("answer is '{:<6d}'"), true));
	EXPECT_EQ(SV("answer is '  1   '"), vformat(SV("answer is '{:^6d}'"), true));

	// The fill character ':' is allowed here (P0645) but not in ranges (P2286).
	EXPECT_EQ(SV("answer is ':::::0'"), vformat(SV("answer is '{::>6d}'"), false));
	EXPECT_EQ(SV("answer is '0:::::'"), vformat(SV("answer is '{::<6d}'"), false));
	EXPECT_EQ(SV("answer is '::0:::'"), vformat(SV("answer is '{::^6d}'"), false));

	// Test whether zero padding is ignored
	EXPECT_EQ(SV("answer is '     1'"), vformat(SV("answer is '{:>06d}'"), true));
	EXPECT_EQ(SV("answer is '1     '"), vformat(SV("answer is '{:<06d}'"), true));
	EXPECT_EQ(SV("answer is '  1   '"), vformat(SV("answer is '{:^06d}'"), true));

	// *** Sign ***
	EXPECT_EQ(SV("answer is 1"),  vformat(SV("answer is {:d}"),  true));
	EXPECT_EQ(SV("answer is 0"),  vformat(SV("answer is {:-d}"), false));
	EXPECT_EQ(SV("answer is +1"), vformat(SV("answer is {:+d}"), true));
	EXPECT_EQ(SV("answer is  0"), vformat(SV("answer is {: d}"), false));

	// *** alternate form ***
	EXPECT_EQ(SV("answer is +1"),   vformat(SV("answer is {:+#d}"), true));
	EXPECT_EQ(SV("answer is +1"),   vformat(SV("answer is {:+b}"),  true));
	EXPECT_EQ(SV("answer is +0b1"), vformat(SV("answer is {:+#b}"), true));
	EXPECT_EQ(SV("answer is +0B1"), vformat(SV("answer is {:+#B}"), true));
	EXPECT_EQ(SV("answer is +1"),   vformat(SV("answer is {:+o}"),  true));
	EXPECT_EQ(SV("answer is +01"),  vformat(SV("answer is {:+#o}"), true));
	EXPECT_EQ(SV("answer is +1"),   vformat(SV("answer is {:+x}"),  true));
	EXPECT_EQ(SV("answer is +0x1"), vformat(SV("answer is {:+#x}"), true));
	EXPECT_EQ(SV("answer is +1"),   vformat(SV("answer is {:+X}"),  true));
	EXPECT_EQ(SV("answer is +0X1"), vformat(SV("answer is {:+#X}"), true));

	EXPECT_EQ(SV("answer is 0"),   vformat(SV("answer is {:#d}"), false));
	EXPECT_EQ(SV("answer is 0"),   vformat(SV("answer is {:b}"),  false));
	EXPECT_EQ(SV("answer is 0b0"), vformat(SV("answer is {:#b}"), false));
	EXPECT_EQ(SV("answer is 0B0"), vformat(SV("answer is {:#B}"), false));
	EXPECT_EQ(SV("answer is 0"),   vformat(SV("answer is {:o}"),  false));
	EXPECT_EQ(SV("answer is 0"),   vformat(SV("answer is {:#o}"), false));
	EXPECT_EQ(SV("answer is 0"),   vformat(SV("answer is {:x}"),  false));
	EXPECT_EQ(SV("answer is 0x0"), vformat(SV("answer is {:#x}"), false));
	EXPECT_EQ(SV("answer is 0"),   vformat(SV("answer is {:X}"),  false));
	EXPECT_EQ(SV("answer is 0X0"), vformat(SV("answer is {:#X}"), false));

	// *** zero-padding & width ***
	EXPECT_EQ(SV("answer is +00000000001"), vformat(SV("answer is {:+#012d}"), true));
	EXPECT_EQ(SV("answer is +00000000001"), vformat(SV("answer is {:+012b}"),  true));
	EXPECT_EQ(SV("answer is +0b000000001"), vformat(SV("answer is {:+#012b}"), true));
	EXPECT_EQ(SV("answer is +0B000000001"), vformat(SV("answer is {:+#012B}"), true));
	EXPECT_EQ(SV("answer is +00000000001"), vformat(SV("answer is {:+012o}"),  true));
	EXPECT_EQ(SV("answer is +00000000001"), vformat(SV("answer is {:+#012o}"), true));
	EXPECT_EQ(SV("answer is +00000000001"), vformat(SV("answer is {:+012x}"),  true));
	EXPECT_EQ(SV("answer is +0x000000001"), vformat(SV("answer is {:+#012x}"), true));
	EXPECT_EQ(SV("answer is +00000000001"), vformat(SV("answer is {:+012X}"),  true));
	EXPECT_EQ(SV("answer is +0X000000001"), vformat(SV("answer is {:+#012X}"), true));

	EXPECT_EQ(SV("answer is 000000000000"), vformat(SV("answer is {:#012d}"), false));
	EXPECT_EQ(SV("answer is 000000000000"), vformat(SV("answer is {:012b}"),  false));
	EXPECT_EQ(SV("answer is 0b0000000000"), vformat(SV("answer is {:#012b}"), false));
	EXPECT_EQ(SV("answer is 0B0000000000"), vformat(SV("answer is {:#012B}"), false));
	EXPECT_EQ(SV("answer is 000000000000"), vformat(SV("answer is {:012o}"),  false));
	EXPECT_EQ(SV("answer is 000000000000"), vformat(SV("answer is {:#012o}"), false));
	EXPECT_EQ(SV("answer is 000000000000"), vformat(SV("answer is {:012x}"),  false));
	EXPECT_EQ(SV("answer is 0x0000000000"), vformat(SV("answer is {:#012x}"), false));
	EXPECT_EQ(SV("answer is 000000000000"), vformat(SV("answer is {:012X}"),  false));
	EXPECT_EQ(SV("answer is 0X0000000000"), vformat(SV("answer is {:#012X}"), false));

	// *** precision ***
	EXPECT_THROW(vformat(SV("{:.}"),   true), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:.0}"),  true), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:.42}"), true), hamon::format_error);

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp
}

template <typename Fn, typename CharT, typename I>
void test_integer_as_integer()
{
	Fn vformat;

	// *** align-fill & width ***
	EXPECT_EQ(SV("answer is '42'"),  vformat(SV("answer is '{:<1}'"), I(42)));
	EXPECT_EQ(SV("answer is '42'"),  vformat(SV("answer is '{:<2}'"), I(42)));
	EXPECT_EQ(SV("answer is '42 '"), vformat(SV("answer is '{:<3}'"), I(42)));

	EXPECT_EQ(SV("answer is '     42'"), vformat(SV("answer is '{:7}'"),  I(42)));
	EXPECT_EQ(SV("answer is '     42'"), vformat(SV("answer is '{:>7}'"), I(42)));
	EXPECT_EQ(SV("answer is '42     '"), vformat(SV("answer is '{:<7}'"), I(42)));
	EXPECT_EQ(SV("answer is '  42   '"), vformat(SV("answer is '{:^7}'"), I(42)));

	// The fill character ':' is allowed here (P0645) but not in ranges (P2286).
	EXPECT_EQ(SV("answer is ':::::42'"), vformat(SV("answer is '{::>7}'"), I(42)));
	EXPECT_EQ(SV("answer is '42:::::'"), vformat(SV("answer is '{::<7}'"), I(42)));
	EXPECT_EQ(SV("answer is '::42:::'"), vformat(SV("answer is '{::^7}'"), I(42)));

	// Test whether zero padding is ignored
	EXPECT_EQ(SV("answer is '     42'"), vformat(SV("answer is '{:>07}'"), I(42)));
	EXPECT_EQ(SV("answer is '42     '"), vformat(SV("answer is '{:<07}'"), I(42)));
	EXPECT_EQ(SV("answer is '  42   '"), vformat(SV("answer is '{:^07}'"), I(42)));

	// *** Sign ***
	if constexpr (hamon::signed_integral<I>)
	{
		EXPECT_EQ(SV("answer is -42"), vformat(SV("answer is {}"), I(-42)));
	}
	EXPECT_EQ(SV("answer is 0"),  vformat(SV("answer is {}"), I(0)));
	EXPECT_EQ(SV("answer is 42"), vformat(SV("answer is {}"), I(42)));

	if constexpr (hamon::signed_integral<I>)
	{
		EXPECT_EQ(SV("answer is -42"), vformat(SV("answer is {:-}"), I(-42)));
	}
	EXPECT_EQ(SV("answer is 0"),  vformat(SV("answer is {:-}"), I(0)));
	EXPECT_EQ(SV("answer is 42"), vformat(SV("answer is {:-}"), I(42)));

	if constexpr (hamon::signed_integral<I>)
	{
		EXPECT_EQ(SV("answer is -42"), vformat(SV("answer is {:+}"), I(-42)));
	}
	EXPECT_EQ(SV("answer is +0"),  vformat(SV("answer is {:+}"), I(0)));
	EXPECT_EQ(SV("answer is +42"), vformat(SV("answer is {:+}"), I(42)));

	if constexpr (hamon::signed_integral<I>)
	{
		EXPECT_EQ(SV("answer is -42"), vformat(SV("answer is {: }"), I(-42)));
	}
	EXPECT_EQ(SV("answer is  0"),  vformat(SV("answer is {: }"), I(0)));
	EXPECT_EQ(SV("answer is  42"), vformat(SV("answer is {: }"), I(42)));

	// *** alternate form ***
	if constexpr (hamon::signed_integral<I>)
	{
		EXPECT_EQ(SV("answer is -42"),       vformat(SV("answer is {:#}"),  I(-42)));
		EXPECT_EQ(SV("answer is -42"),       vformat(SV("answer is {:#d}"), I(-42)));
		EXPECT_EQ(SV("answer is -101010"),   vformat(SV("answer is {:b}"),  I(-42)));
		EXPECT_EQ(SV("answer is -0b101010"), vformat(SV("answer is {:#b}"), I(-42)));
		EXPECT_EQ(SV("answer is -0B101010"), vformat(SV("answer is {:#B}"), I(-42)));
		EXPECT_EQ(SV("answer is -52"),       vformat(SV("answer is {:o}"),  I(-42)));
		EXPECT_EQ(SV("answer is -052"),      vformat(SV("answer is {:#o}"), I(-42)));
		EXPECT_EQ(SV("answer is -2a"),       vformat(SV("answer is {:x}"),  I(-42)));
		EXPECT_EQ(SV("answer is -0x2a"),     vformat(SV("answer is {:#x}"), I(-42)));
		EXPECT_EQ(SV("answer is -2A"),       vformat(SV("answer is {:X}"),  I(-42)));
		EXPECT_EQ(SV("answer is -0X2A"),     vformat(SV("answer is {:#X}"), I(-42)));
	}
	EXPECT_EQ(SV("answer is 0"),   vformat(SV("answer is {:#}"),  I(0)));
	EXPECT_EQ(SV("answer is 0"),   vformat(SV("answer is {:#d}"), I(0)));
	EXPECT_EQ(SV("answer is 0"),   vformat(SV("answer is {:b}"),  I(0)));
	EXPECT_EQ(SV("answer is 0b0"), vformat(SV("answer is {:#b}"), I(0)));
	EXPECT_EQ(SV("answer is 0B0"), vformat(SV("answer is {:#B}"), I(0)));
	EXPECT_EQ(SV("answer is 0"),   vformat(SV("answer is {:o}"),  I(0)));
	EXPECT_EQ(SV("answer is 0"),   vformat(SV("answer is {:#o}"), I(0)));
	EXPECT_EQ(SV("answer is 0"),   vformat(SV("answer is {:x}"),  I(0)));
	EXPECT_EQ(SV("answer is 0x0"), vformat(SV("answer is {:#x}"), I(0)));
	EXPECT_EQ(SV("answer is 0"),   vformat(SV("answer is {:X}"),  I(0)));
	EXPECT_EQ(SV("answer is 0X0"), vformat(SV("answer is {:#X}"), I(0)));

	EXPECT_EQ(SV("answer is +42"),       vformat(SV("answer is {:+#}"),  I(42)));
	EXPECT_EQ(SV("answer is +42"),       vformat(SV("answer is {:+#d}"), I(42)));
	EXPECT_EQ(SV("answer is +101010"),   vformat(SV("answer is {:+b}"),  I(42)));
	EXPECT_EQ(SV("answer is +0b101010"), vformat(SV("answer is {:+#b}"), I(42)));
	EXPECT_EQ(SV("answer is +0B101010"), vformat(SV("answer is {:+#B}"), I(42)));
	EXPECT_EQ(SV("answer is +52"),       vformat(SV("answer is {:+o}"),  I(42)));
	EXPECT_EQ(SV("answer is +052"),      vformat(SV("answer is {:+#o}"), I(42)));
	EXPECT_EQ(SV("answer is +2a"),       vformat(SV("answer is {:+x}"),  I(42)));
	EXPECT_EQ(SV("answer is +0x2a"),     vformat(SV("answer is {:+#x}"), I(42)));
	EXPECT_EQ(SV("answer is +2A"),       vformat(SV("answer is {:+X}"),  I(42)));
	EXPECT_EQ(SV("answer is +0X2A"),     vformat(SV("answer is {:+#X}"), I(42)));

	// *** zero-padding & width ***
	if constexpr (hamon::signed_integral<I>)
	{
		EXPECT_EQ(SV("answer is -00000000042"), vformat(SV("answer is {:#012}"),  I(-42)));
		EXPECT_EQ(SV("answer is -00000000042"), vformat(SV("answer is {:#012d}"), I(-42)));
		EXPECT_EQ(SV("answer is -00000101010"), vformat(SV("answer is {:012b}"),  I(-42)));
		EXPECT_EQ(SV("answer is -0b000101010"), vformat(SV("answer is {:#012b}"), I(-42)));
		EXPECT_EQ(SV("answer is -0B000101010"), vformat(SV("answer is {:#012B}"), I(-42)));
		EXPECT_EQ(SV("answer is -00000000052"), vformat(SV("answer is {:012o}"),  I(-42)));
		EXPECT_EQ(SV("answer is -00000000052"), vformat(SV("answer is {:#012o}"), I(-42)));
		EXPECT_EQ(SV("answer is -0000000002a"), vformat(SV("answer is {:012x}"),  I(-42)));
		EXPECT_EQ(SV("answer is -0x00000002a"), vformat(SV("answer is {:#012x}"), I(-42)));
		EXPECT_EQ(SV("answer is -0000000002A"), vformat(SV("answer is {:012X}"),  I(-42)));
		EXPECT_EQ(SV("answer is -0X00000002A"), vformat(SV("answer is {:#012X}"), I(-42)));
	}

	EXPECT_EQ(SV("answer is 000000000000"), vformat(SV("answer is {:#012}"),  I(0)));
	EXPECT_EQ(SV("answer is 000000000000"), vformat(SV("answer is {:#012d}"), I(0)));
	EXPECT_EQ(SV("answer is 000000000000"), vformat(SV("answer is {:012b}"),  I(0)));
	EXPECT_EQ(SV("answer is 0b0000000000"), vformat(SV("answer is {:#012b}"), I(0)));
	EXPECT_EQ(SV("answer is 0B0000000000"), vformat(SV("answer is {:#012B}"), I(0)));
	EXPECT_EQ(SV("answer is 000000000000"), vformat(SV("answer is {:012o}"),  I(0)));
	EXPECT_EQ(SV("answer is 000000000000"), vformat(SV("answer is {:#012o}"), I(0)));
	EXPECT_EQ(SV("answer is 000000000000"), vformat(SV("answer is {:012x}"),  I(0)));
	EXPECT_EQ(SV("answer is 0x0000000000"), vformat(SV("answer is {:#012x}"), I(0)));
	EXPECT_EQ(SV("answer is 000000000000"), vformat(SV("answer is {:012X}"),  I(0)));
	EXPECT_EQ(SV("answer is 0X0000000000"), vformat(SV("answer is {:#012X}"), I(0)));

	EXPECT_EQ(SV("answer is +00000000042"), vformat(SV("answer is {:+#012}"),  I(42)));
	EXPECT_EQ(SV("answer is +00000000042"), vformat(SV("answer is {:+#012d}"), I(42)));
	EXPECT_EQ(SV("answer is +00000101010"), vformat(SV("answer is {:+012b}"),  I(42)));
	EXPECT_EQ(SV("answer is +0b000101010"), vformat(SV("answer is {:+#012b}"), I(42)));
	EXPECT_EQ(SV("answer is +0B000101010"), vformat(SV("answer is {:+#012B}"), I(42)));
	EXPECT_EQ(SV("answer is +00000000052"), vformat(SV("answer is {:+012o}"),  I(42)));
	EXPECT_EQ(SV("answer is +00000000052"), vformat(SV("answer is {:+#012o}"), I(42)));
	EXPECT_EQ(SV("answer is +0000000002a"), vformat(SV("answer is {:+012x}"),  I(42)));
	EXPECT_EQ(SV("answer is +0x00000002a"), vformat(SV("answer is {:+#012x}"), I(42)));
	EXPECT_EQ(SV("answer is +0000000002A"), vformat(SV("answer is {:+012X}"),  I(42)));
	EXPECT_EQ(SV("answer is +0X00000002A"), vformat(SV("answer is {:+#012X}"), I(42)));

	// *** precision ***
	EXPECT_THROW(vformat(SV("{:.}"),   I(0)), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:.0}"),  I(0)), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:.42}"), I(0)), hamon::format_error);

	EXPECT_THROW(vformat(SV("{:.{}}"), I(0)), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:.{}}"), I(0), true), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:.{}}"), I(0), 1.0), hamon::format_error);

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp

	// *** type ***
	EXPECT_THROW   (vformat(SV("{:a}"), I(0)), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:A}"), I(0)), hamon::format_error);
	EXPECT_NO_THROW(vformat(SV("{:b}"), I(0)));
	EXPECT_NO_THROW(vformat(SV("{:B}"), I(0)));
	EXPECT_NO_THROW(vformat(SV("{:c}"), I(0)));
	EXPECT_NO_THROW(vformat(SV("{:d}"), I(0)));
	EXPECT_THROW   (vformat(SV("{:e}"), I(0)), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:E}"), I(0)), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:f}"), I(0)), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:F}"), I(0)), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:g}"), I(0)), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:G}"), I(0)), hamon::format_error);
	EXPECT_NO_THROW(vformat(SV("{:o}"), I(0)));
	EXPECT_THROW   (vformat(SV("{:p}"), I(0)), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:P}"), I(0)), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:s}"), I(0)), hamon::format_error);
	EXPECT_NO_THROW(vformat(SV("{:x}"), I(0)));
	EXPECT_NO_THROW(vformat(SV("{:X}"), I(0)));
//	EXPECT_THROW   (vformat(SV("{:?}"), I(0)), hamon::format_error);	// C++23
}

template <typename Fn, typename CharT, typename I>
void test_integer_as_char()
{
	Fn vformat;

	// *** align-fill & width ***
	EXPECT_EQ(SV("answer is '*     '"), vformat(SV("answer is '{:6c}'"),  I(42)));
	EXPECT_EQ(SV("answer is '     *'"), vformat(SV("answer is '{:>6c}'"), I(42)));
	EXPECT_EQ(SV("answer is '*     '"), vformat(SV("answer is '{:<6c}'"), I(42)));
	EXPECT_EQ(SV("answer is '  *   '"), vformat(SV("answer is '{:^6c}'"), I(42)));

	// The fill character ':' is allowed here (P0645) but not in ranges (P2286).
	EXPECT_EQ(SV("answer is ':::::*'"), vformat(SV("answer is '{::>6c}'"), I(42)));
	EXPECT_EQ(SV("answer is '*:::::'"), vformat(SV("answer is '{::<6c}'"), I(42)));
	EXPECT_EQ(SV("answer is '::*:::'"), vformat(SV("answer is '{::^6c}'"), I(42)));

	// *** Sign ***
	EXPECT_EQ(SV("answer is *"), vformat(SV("answer is {:c}"), I(42)));
	EXPECT_THROW(vformat(SV("answer is {:-c}"), I(42)), hamon::format_error);
	EXPECT_THROW(vformat(SV("answer is {:+c}"), I(42)), hamon::format_error);
	EXPECT_THROW(vformat(SV("answer is {: c}"), I(42)), hamon::format_error);

	// *** alternate form ***
	EXPECT_THROW(vformat(SV("answer is {:#c}"), I(42)), hamon::format_error);

	// *** zero-padding & width ***
	EXPECT_THROW(vformat(SV("answer is {:01c}"), I(42)), hamon::format_error);

	// *** precision ***
	EXPECT_THROW(vformat(SV("{:.c}"),   I(0)), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:.0c}"),  I(0)), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:.42c}"), I(0)), hamon::format_error);

	EXPECT_THROW(vformat(SV("{:.{}c}"), I(0)), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:.{}c}"), I(0), true), hamon::format_error);
	EXPECT_THROW(vformat(SV("{:.{}c}"), I(0), 1.0), hamon::format_error);

	// *** locale-specific form ***
	// Note it has no effect but it's allowed.
	EXPECT_EQ(SV("answer is '*'"), vformat(SV("answer is '{:Lc}'"), I(42)));

	// *** type ***
	EXPECT_THROW   (vformat(SV("{:a}"), I(42)), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:A}"), I(42)), hamon::format_error);
	EXPECT_NO_THROW(vformat(SV("{:b}"), I(42)));
	EXPECT_NO_THROW(vformat(SV("{:B}"), I(42)));
	EXPECT_NO_THROW(vformat(SV("{:c}"), I(42)));
	EXPECT_NO_THROW(vformat(SV("{:d}"), I(42)));
	EXPECT_THROW   (vformat(SV("{:e}"), I(42)), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:E}"), I(42)), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:f}"), I(42)), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:F}"), I(42)), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:g}"), I(42)), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:G}"), I(42)), hamon::format_error);
	EXPECT_NO_THROW(vformat(SV("{:o}"), I(42)));
	EXPECT_THROW   (vformat(SV("{:p}"), I(42)), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:P}"), I(42)), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:s}"), I(42)), hamon::format_error);
	EXPECT_NO_THROW(vformat(SV("{:x}"), I(42)));
	EXPECT_NO_THROW(vformat(SV("{:X}"), I(42)));
//	EXPECT_THROW   (vformat(SV("{:?}"), I(42)), hamon::format_error);	// C++23

	// *** Validate range ***
	// The code has some duplications to keep the if statement readable.
	if constexpr (hamon::signed_integral<CharT>)
	{
		if constexpr (hamon::signed_integral<I> && sizeof(I) > sizeof(CharT))
		{
			EXPECT_THROW(vformat(SV("{:c}"), hamon::numeric_limits<I>::min()), hamon::format_error);
			EXPECT_THROW(vformat(SV("{:c}"), hamon::numeric_limits<I>::max()), hamon::format_error);
		}
		else if constexpr (hamon::unsigned_integral<I> && sizeof(I) >= sizeof(CharT))
		{
			EXPECT_THROW(vformat(SV("{:c}"), hamon::numeric_limits<I>::max()), hamon::format_error);
		}
	}
	else if constexpr (sizeof(I) > sizeof(CharT))
	{
		EXPECT_THROW(vformat(SV("{:c}"), hamon::numeric_limits<I>::max()), hamon::format_error);
	}
}

template <typename Fn, typename CharT, typename I>
void test_integer()
{
	test_integer_as_integer<Fn, CharT, I>();
	test_integer_as_char<Fn, CharT, I>();
}

template <typename Fn, typename CharT>
void test_signed_integer()
{
	Fn vformat;

	// *** Test signed integral format argument ***
	EXPECT_EQ(SV("hello 42"), vformat(SV("hello {}"), static_cast<signed char>(42)));
	EXPECT_EQ(SV("hello 42"), vformat(SV("hello {}"), static_cast<short>(42)));
	EXPECT_EQ(SV("hello 42"), vformat(SV("hello {}"), static_cast<int>(42)));
	EXPECT_EQ(SV("hello 42"), vformat(SV("hello {}"), static_cast<long>(42)));
	EXPECT_EQ(SV("hello 42"), vformat(SV("hello {}"), static_cast<long long>(42)));

	test_integer<Fn, CharT, signed char>();
	test_integer<Fn, CharT, short>();
	test_integer<Fn, CharT, int>();
	test_integer<Fn, CharT, long>();
	test_integer<Fn, CharT, long long>();

	// *** EXPECT_EQ the minima and maxima ***
	EXPECT_EQ(SV("-0b10000000"), vformat(SV("{:#b}"), hamon::numeric_limits<std::int8_t>::min()));
	EXPECT_EQ(SV("-0200"),       vformat(SV("{:#o}"), hamon::numeric_limits<std::int8_t>::min()));
	EXPECT_EQ(SV("-128"),        vformat(SV("{:#}"),  hamon::numeric_limits<std::int8_t>::min()));
	EXPECT_EQ(SV("-0x80"),       vformat(SV("{:#x}"), hamon::numeric_limits<std::int8_t>::min()));

	EXPECT_EQ(SV("-0b1000000000000000"), vformat(SV("{:#b}"), hamon::numeric_limits<std::int16_t>::min()));
	EXPECT_EQ(SV("-0100000"), vformat(SV("{:#o}"), hamon::numeric_limits<std::int16_t>::min()));
	EXPECT_EQ(SV("-32768"),   vformat(SV("{:#}"),  hamon::numeric_limits<std::int16_t>::min()));
	EXPECT_EQ(SV("-0x8000"),  vformat(SV("{:#x}"), hamon::numeric_limits<std::int16_t>::min()));

	EXPECT_EQ(SV("-0b10000000000000000000000000000000"), vformat(SV("{:#b}"), hamon::numeric_limits<std::int32_t>::min()));
	EXPECT_EQ(SV("-020000000000"), vformat(SV("{:#o}"), hamon::numeric_limits<std::int32_t>::min()));
	EXPECT_EQ(SV("-2147483648"),   vformat(SV("{:#}"),  hamon::numeric_limits<std::int32_t>::min()));
	EXPECT_EQ(SV("-0x80000000"),   vformat(SV("{:#x}"), hamon::numeric_limits<std::int32_t>::min()));

	EXPECT_EQ(SV("-0b1000000000000000000000000000000000000000000000000000000000000000"),
		vformat(SV("{:#b}"), hamon::numeric_limits<std::int64_t>::min()));
	EXPECT_EQ(SV("-01000000000000000000000"), vformat(SV("{:#o}"), hamon::numeric_limits<std::int64_t>::min()));
	EXPECT_EQ(SV("-9223372036854775808"),     vformat(SV("{:#}"),  hamon::numeric_limits<std::int64_t>::min()));
	EXPECT_EQ(SV("-0x8000000000000000"),      vformat(SV("{:#x}"), hamon::numeric_limits<std::int64_t>::min()));

	EXPECT_EQ(SV("0b1111111"), vformat(SV("{:#b}"), hamon::numeric_limits<std::int8_t>::max()));
	EXPECT_EQ(SV("0177"),      vformat(SV("{:#o}"), hamon::numeric_limits<std::int8_t>::max()));
	EXPECT_EQ(SV("127"),       vformat(SV("{:#}"),  hamon::numeric_limits<std::int8_t>::max()));
	EXPECT_EQ(SV("0x7f"),      vformat(SV("{:#x}"), hamon::numeric_limits<std::int8_t>::max()));

	EXPECT_EQ(SV("0b111111111111111"), vformat(SV("{:#b}"), hamon::numeric_limits<std::int16_t>::max()));
	EXPECT_EQ(SV("077777"),            vformat(SV("{:#o}"), hamon::numeric_limits<std::int16_t>::max()));
	EXPECT_EQ(SV("32767"),             vformat(SV("{:#}"),  hamon::numeric_limits<std::int16_t>::max()));
	EXPECT_EQ(SV("0x7fff"),            vformat(SV("{:#x}"), hamon::numeric_limits<std::int16_t>::max()));

	EXPECT_EQ(SV("0b1111111111111111111111111111111"), vformat(SV("{:#b}"), hamon::numeric_limits<std::int32_t>::max()));
	EXPECT_EQ(SV("017777777777"), vformat(SV("{:#o}"), hamon::numeric_limits<std::int32_t>::max()));
	EXPECT_EQ(SV("2147483647"),   vformat(SV("{:#}"),  hamon::numeric_limits<std::int32_t>::max()));
	EXPECT_EQ(SV("0x7fffffff"),   vformat(SV("{:#x}"), hamon::numeric_limits<std::int32_t>::max()));

	EXPECT_EQ(SV("0b111111111111111111111111111111111111111111111111111111111111111"),
		vformat(SV("{:#b}"), hamon::numeric_limits<std::int64_t>::max()));
	EXPECT_EQ(SV("0777777777777777777777"), vformat(SV("{:#o}"), hamon::numeric_limits<std::int64_t>::max()));
	EXPECT_EQ(SV("9223372036854775807"),    vformat(SV("{:#}"),  hamon::numeric_limits<std::int64_t>::max()));
	EXPECT_EQ(SV("0x7fffffffffffffff"),     vformat(SV("{:#x}"), hamon::numeric_limits<std::int64_t>::max()));
}

template <typename Fn, typename CharT>
void test_unsigned_integer()
{
	Fn vformat;

	// ** Test unsigned integral format argument ***
	EXPECT_EQ(SV("hello 42"), vformat(SV("hello {}"), static_cast<unsigned char>(42)));
	EXPECT_EQ(SV("hello 42"), vformat(SV("hello {}"), static_cast<unsigned short>(42)));
	EXPECT_EQ(SV("hello 42"), vformat(SV("hello {}"), static_cast<unsigned>(42)));
	EXPECT_EQ(SV("hello 42"), vformat(SV("hello {}"), static_cast<unsigned long>(42)));
	EXPECT_EQ(SV("hello 42"), vformat(SV("hello {}"), static_cast<unsigned long long>(42)));

	test_integer<Fn, CharT, unsigned char>();
	test_integer<Fn, CharT, unsigned short>();
	test_integer<Fn, CharT, unsigned>();
	test_integer<Fn, CharT, unsigned long>();
	test_integer<Fn, CharT, unsigned long long>();

	// *** test the maxima ***
	EXPECT_EQ(SV("0b11111111"), vformat(SV("{:#b}"), hamon::numeric_limits<std::uint8_t>::max()));
	EXPECT_EQ(SV("0377"),       vformat(SV("{:#o}"), hamon::numeric_limits<std::uint8_t>::max()));
	EXPECT_EQ(SV("255"),        vformat(SV("{:#}"),  hamon::numeric_limits<std::uint8_t>::max()));
	EXPECT_EQ(SV("0xff"),       vformat(SV("{:#x}"), hamon::numeric_limits<std::uint8_t>::max()));

	EXPECT_EQ(SV("0b1111111111111111"), vformat(SV("{:#b}"), hamon::numeric_limits<std::uint16_t>::max()));
	EXPECT_EQ(SV("0177777"), vformat(SV("{:#o}"), hamon::numeric_limits<std::uint16_t>::max()));
	EXPECT_EQ(SV("65535"),   vformat(SV("{:#}"),  hamon::numeric_limits<std::uint16_t>::max()));
	EXPECT_EQ(SV("0xffff"),  vformat(SV("{:#x}"), hamon::numeric_limits<std::uint16_t>::max()));

	EXPECT_EQ(SV("0b11111111111111111111111111111111"), vformat(SV("{:#b}"), hamon::numeric_limits<std::uint32_t>::max()));
	EXPECT_EQ(SV("037777777777"), vformat(SV("{:#o}"), hamon::numeric_limits<std::uint32_t>::max()));
	EXPECT_EQ(SV("4294967295"),   vformat(SV("{:#}"),  hamon::numeric_limits<std::uint32_t>::max()));
	EXPECT_EQ(SV("0xffffffff"),   vformat(SV("{:#x}"), hamon::numeric_limits<std::uint32_t>::max()));

	EXPECT_EQ(SV("0b1111111111111111111111111111111111111111111111111111111111111111"),
		vformat(SV("{:#b}"), hamon::numeric_limits<std::uint64_t>::max()));
	EXPECT_EQ(SV("01777777777777777777777"), vformat(SV("{:#o}"), hamon::numeric_limits<std::uint64_t>::max()));
	EXPECT_EQ(SV("18446744073709551615"),    vformat(SV("{:#}"),  hamon::numeric_limits<std::uint64_t>::max()));
	EXPECT_EQ(SV("0xffffffffffffffff"),      vformat(SV("{:#x}"), hamon::numeric_limits<std::uint64_t>::max()));
}

template <typename Fn, typename CharT, typename F>
void format_test_floating_point_hex_lower_case()
{
	Fn vformat;

	auto nan_pos = std::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// Test whether the hexadecimal letters are the proper case.
	// The precision is too large for float, so two tests are used.
	EXPECT_EQ(SV("answer is '1.abcp+0'"), vformat(SV("answer is '{:a}'"), F(0x1.abcp+0)));
	EXPECT_EQ(SV("answer is '1.defp+0'"), vformat(SV("answer is '{:a}'"), F(0x1.defp+0)));

	// *** align-fill & width ***
	EXPECT_EQ(SV("answer is '   1p-2'"), vformat(SV("answer is '{:7a}'"),  F(0.25)));
	EXPECT_EQ(SV("answer is '   1p-2'"), vformat(SV("answer is '{:>7a}'"), F(0.25)));
	EXPECT_EQ(SV("answer is '1p-2   '"), vformat(SV("answer is '{:<7a}'"), F(0.25)));
	EXPECT_EQ(SV("answer is ' 1p-2  '"), vformat(SV("answer is '{:^7a}'"), F(0.25)));

	// The fill character ':' is allowed here (P0645) but not in ranges (P2286).
	EXPECT_EQ(SV("answer is ':::1p-3'"), vformat(SV("answer is '{::>7a}'"), F(125e-3)));
	EXPECT_EQ(SV("answer is '1p-3:::'"), vformat(SV("answer is '{::<7a}'"), F(125e-3)));
	EXPECT_EQ(SV("answer is ':1p-3::'"), vformat(SV("answer is '{::^7a}'"), F(125e-3)));

	EXPECT_EQ(SV("answer is '***inf'"), vformat(SV("answer is '{:*>6a}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is 'inf***'"), vformat(SV("answer is '{:*<6a}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '*inf**'"), vformat(SV("answer is '{:*^6a}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '###-inf'"), vformat(SV("answer is '{:#>7a}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf###'"), vformat(SV("answer is '{:#<7a}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '#-inf##'"), vformat(SV("answer is '{:#^7a}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '^^^nan'"), vformat(SV("answer is '{:^>6a}'"), nan_pos));
	EXPECT_EQ(SV("answer is 'nan^^^'"), vformat(SV("answer is '{:^<6a}'"), nan_pos));
	EXPECT_EQ(SV("answer is '^nan^^'"), vformat(SV("answer is '{:^^6a}'"), nan_pos));

	EXPECT_EQ(SV("answer is '000-nan'"), vformat(SV("answer is '{:0>7a}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-nan000'"), vformat(SV("answer is '{:0<7a}'"), nan_neg));
	EXPECT_EQ(SV("answer is '0-nan00'"), vformat(SV("answer is '{:0^7a}'"), nan_neg));

	// Test whether zero padding is ignored
	EXPECT_EQ(SV("answer is '   1p-2'"), vformat(SV("answer is '{:>07a}'"), F(0.25)));
	EXPECT_EQ(SV("answer is '1p-2   '"), vformat(SV("answer is '{:<07a}'"), F(0.25)));
	EXPECT_EQ(SV("answer is ' 1p-2  '"), vformat(SV("answer is '{:^07a}'"), F(0.25)));

	// *** Sign ***
	EXPECT_EQ(SV("answer is '0p+0'"),  vformat(SV("answer is '{:a}'"),  F(0)));
	EXPECT_EQ(SV("answer is '0p+0'"),  vformat(SV("answer is '{:-a}'"), F(0)));
	EXPECT_EQ(SV("answer is '+0p+0'"), vformat(SV("answer is '{:+a}'"), F(0)));
	EXPECT_EQ(SV("answer is ' 0p+0'"), vformat(SV("answer is '{: a}'"), F(0)));

	EXPECT_EQ(SV("answer is '-0p+0'"), vformat(SV("answer is '{:a}'"),  F(-0.)));
	EXPECT_EQ(SV("answer is '-0p+0'"), vformat(SV("answer is '{:-a}'"), F(-0.)));
	EXPECT_EQ(SV("answer is '-0p+0'"), vformat(SV("answer is '{:+a}'"), F(-0.)));
	EXPECT_EQ(SV("answer is '-0p+0'"), vformat(SV("answer is '{: a}'"), F(-0.)));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	EXPECT_EQ(SV("answer is 'inf'"),  vformat(SV("answer is '{:a}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is 'inf'"),  vformat(SV("answer is '{:-a}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '+inf'"), vformat(SV("answer is '{:+a}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is ' inf'"), vformat(SV("answer is '{: a}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:a}'"),  -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:-a}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:+a}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{: a}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is 'nan'"),  vformat(SV("answer is '{:a}'"),  nan_pos));
	EXPECT_EQ(SV("answer is 'nan'"),  vformat(SV("answer is '{:-a}'"), nan_pos));
	EXPECT_EQ(SV("answer is '+nan'"), vformat(SV("answer is '{:+a}'"), nan_pos));
	EXPECT_EQ(SV("answer is ' nan'"), vformat(SV("answer is '{: a}'"), nan_pos));

	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:a}'"),  nan_neg));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:-a}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:+a}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{: a}'"), nan_neg));

	// *** alternate form ***
	// When precision is zero there's no decimal point except when the alternate form is specified.
	EXPECT_EQ(SV("answer is '0p+0'"),  vformat(SV("answer is '{:a}'"),  F(0)));
	EXPECT_EQ(SV("answer is '0.p+0'"), vformat(SV("answer is '{:#a}'"), F(0)));

	EXPECT_EQ(SV("answer is '1p+1'"),   vformat(SV("answer is '{:.0a}'"),  F(2.5)));
	EXPECT_EQ(SV("answer is '1.p+1'"),  vformat(SV("answer is '{:#.0a}'"), F(2.5)));
	EXPECT_EQ(SV("answer is '1.4p+1'"), vformat(SV("answer is '{:#a}'"),   F(2.5)));

	EXPECT_EQ(SV("answer is 'inf'"),  vformat(SV("answer is '{:#a}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:#a}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is 'nan'"),  vformat(SV("answer is '{:#a}'"), nan_pos));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:#a}'"), nan_neg));

	// *** zero-padding & width ***
	EXPECT_EQ(SV("answer is '1p-5'"),   vformat(SV("answer is '{:04a}'"),  0.03125));
	EXPECT_EQ(SV("answer is '+1p-5'"),  vformat(SV("answer is '{:+05a}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+01p-5'"), vformat(SV("answer is '{:+06a}'"), 0.03125));

	EXPECT_EQ(SV("answer is '0001p-5'"), vformat(SV("answer is '{:07a}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0001p-5'"), vformat(SV("answer is '{:-07a}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+001p-5'"), vformat(SV("answer is '{:+07a}'"), 0.03125));
	EXPECT_EQ(SV("answer is ' 001p-5'"), vformat(SV("answer is '{: 07a}'"), 0.03125));

	EXPECT_EQ(SV("answer is '       inf'"), vformat(SV("answer is '{:010a}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '       inf'"), vformat(SV("answer is '{:-010a}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      +inf'"), vformat(SV("answer is '{:+010a}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '       inf'"), vformat(SV("answer is '{: 010a}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{:010a}'"),  -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{:-010a}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{:+010a}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{: 010a}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '       nan'"), vformat(SV("answer is '{:010a}'"),  nan_pos));
	EXPECT_EQ(SV("answer is '       nan'"), vformat(SV("answer is '{:-010a}'"), nan_pos));
	EXPECT_EQ(SV("answer is '      +nan'"), vformat(SV("answer is '{:+010a}'"), nan_pos));
	EXPECT_EQ(SV("answer is '       nan'"), vformat(SV("answer is '{: 010a}'"), nan_pos));

	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{:010a}'"),  nan_neg));
	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{:-010a}'"), nan_neg));
	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{:+010a}'"), nan_neg));
	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{: 010a}'"), nan_neg));

	// *** precision ***
	// See format_test_floating_point_hex_lower_case_precision

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp
}

template <typename Fn, typename CharT, typename F>
void format_test_floating_point_hex_upper_case()
{
	Fn vformat;

	auto nan_pos = std::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// Test whether the hexadecimal letters are the proper case.
	// The precision is too large for float, so two tests are used.
	EXPECT_EQ(SV("answer is '1.ABCP+0'"), vformat(SV("answer is '{:A}'"), F(0x1.abcp+0)));
	EXPECT_EQ(SV("answer is '1.DEFP+0'"), vformat(SV("answer is '{:A}'"), F(0x1.defp+0)));

	// *** align-fill & width ***
	EXPECT_EQ(SV("answer is '   1P-2'"), vformat(SV("answer is '{:7A}'"),  F(0.25)));
	EXPECT_EQ(SV("answer is '   1P-2'"), vformat(SV("answer is '{:>7A}'"), F(0.25)));
	EXPECT_EQ(SV("answer is '1P-2   '"), vformat(SV("answer is '{:<7A}'"), F(0.25)));
	EXPECT_EQ(SV("answer is ' 1P-2  '"), vformat(SV("answer is '{:^7A}'"), F(0.25)));

	EXPECT_EQ(SV("answer is '---1P-3'"), vformat(SV("answer is '{:->7A}'"), F(125e-3)));
	EXPECT_EQ(SV("answer is '1P-3---'"), vformat(SV("answer is '{:-<7A}'"), F(125e-3)));
	EXPECT_EQ(SV("answer is '-1P-3--'"), vformat(SV("answer is '{:-^7A}'"), F(125e-3)));

	EXPECT_EQ(SV("answer is '***INF'"), vformat(SV("answer is '{:*>6A}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is 'INF***'"), vformat(SV("answer is '{:*<6A}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '*INF**'"), vformat(SV("answer is '{:*^6A}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '###-INF'"), vformat(SV("answer is '{:#>7A}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-INF###'"), vformat(SV("answer is '{:#<7A}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '#-INF##'"), vformat(SV("answer is '{:#^7A}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '^^^NAN'"), vformat(SV("answer is '{:^>6A}'"), nan_pos));
	EXPECT_EQ(SV("answer is 'NAN^^^'"), vformat(SV("answer is '{:^<6A}'"), nan_pos));
	EXPECT_EQ(SV("answer is '^NAN^^'"), vformat(SV("answer is '{:^^6A}'"), nan_pos));

	EXPECT_EQ(SV("answer is '000-NAN'"), vformat(SV("answer is '{:0>7A}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-NAN000'"), vformat(SV("answer is '{:0<7A}'"), nan_neg));
	EXPECT_EQ(SV("answer is '0-NAN00'"), vformat(SV("answer is '{:0^7A}'"), nan_neg));

	// Test whether zero padding is ignored
	EXPECT_EQ(SV("answer is '   1P-2'"), vformat(SV("answer is '{:>07A}'"), F(0.25)));
	EXPECT_EQ(SV("answer is '1P-2   '"), vformat(SV("answer is '{:<07A}'"), F(0.25)));
	EXPECT_EQ(SV("answer is ' 1P-2  '"), vformat(SV("answer is '{:^07A}'"), F(0.25)));

	// *** Sign ***
	EXPECT_EQ(SV("answer is '0P+0'"),  vformat(SV("answer is '{:A}'"),  F(0)));
	EXPECT_EQ(SV("answer is '0P+0'"),  vformat(SV("answer is '{:-A}'"), F(0)));
	EXPECT_EQ(SV("answer is '+0P+0'"), vformat(SV("answer is '{:+A}'"), F(0)));
	EXPECT_EQ(SV("answer is ' 0P+0'"), vformat(SV("answer is '{: A}'"), F(0)));

	EXPECT_EQ(SV("answer is '-0P+0'"), vformat(SV("answer is '{:A}'"),  F(-0.)));
	EXPECT_EQ(SV("answer is '-0P+0'"), vformat(SV("answer is '{:-A}'"), F(-0.)));
	EXPECT_EQ(SV("answer is '-0P+0'"), vformat(SV("answer is '{:+A}'"), F(-0.)));
	EXPECT_EQ(SV("answer is '-0P+0'"), vformat(SV("answer is '{: A}'"), F(-0.)));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	EXPECT_EQ(SV("answer is 'INF'"),  vformat(SV("answer is '{:A}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is 'INF'"),  vformat(SV("answer is '{:-A}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '+INF'"), vformat(SV("answer is '{:+A}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is ' INF'"), vformat(SV("answer is '{: A}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '-INF'"), vformat(SV("answer is '{:A}'"),  -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-INF'"), vformat(SV("answer is '{:-A}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-INF'"), vformat(SV("answer is '{:+A}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-INF'"), vformat(SV("answer is '{: A}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is 'NAN'"),  vformat(SV("answer is '{:A}'"),  nan_pos));
	EXPECT_EQ(SV("answer is 'NAN'"),  vformat(SV("answer is '{:-A}'"), nan_pos));
	EXPECT_EQ(SV("answer is '+NAN'"), vformat(SV("answer is '{:+A}'"), nan_pos));
	EXPECT_EQ(SV("answer is ' NAN'"), vformat(SV("answer is '{: A}'"), nan_pos));

	EXPECT_EQ(SV("answer is '-NAN'"), vformat(SV("answer is '{:A}'"),  nan_neg));
	EXPECT_EQ(SV("answer is '-NAN'"), vformat(SV("answer is '{:-A}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-NAN'"), vformat(SV("answer is '{:+A}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-NAN'"), vformat(SV("answer is '{: A}'"), nan_neg));

	// *** alternate form ***
	// When precision is zero there's no decimal point except when the alternate form is specified.
	EXPECT_EQ(SV("answer is '0P+0'"),  vformat(SV("answer is '{:A}'"),  F(0)));
	EXPECT_EQ(SV("answer is '0.P+0'"), vformat(SV("answer is '{:#A}'"), F(0)));

	EXPECT_EQ(SV("answer is '1P+1'"),   vformat(SV("answer is '{:.0A}'"),  F(2.5)));
	EXPECT_EQ(SV("answer is '1.P+1'"),  vformat(SV("answer is '{:#.0A}'"), F(2.5)));
	EXPECT_EQ(SV("answer is '1.4P+1'"), vformat(SV("answer is '{:#A}'"),   F(2.5)));

	EXPECT_EQ(SV("answer is 'INF'"),  vformat(SV("answer is '{:#A}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-INF'"), vformat(SV("answer is '{:#A}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is 'NAN'"),  vformat(SV("answer is '{:#A}'"), nan_pos));
	EXPECT_EQ(SV("answer is '-NAN'"), vformat(SV("answer is '{:#A}'"), nan_neg));

	// *** zero-padding & width ***
	EXPECT_EQ(SV("answer is '1P-5'"),   vformat(SV("answer is '{:04A}'"),  0.03125));
	EXPECT_EQ(SV("answer is '+1P-5'"),  vformat(SV("answer is '{:+05A}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+01P-5'"), vformat(SV("answer is '{:+06A}'"), 0.03125));

	EXPECT_EQ(SV("answer is '0001P-5'"), vformat(SV("answer is '{:07A}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0001P-5'"), vformat(SV("answer is '{:-07A}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+001P-5'"), vformat(SV("answer is '{:+07A}'"), 0.03125));
	EXPECT_EQ(SV("answer is ' 001P-5'"), vformat(SV("answer is '{: 07A}'"), 0.03125));

	EXPECT_EQ(SV("answer is '       INF'"), vformat(SV("answer is '{:010A}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '       INF'"), vformat(SV("answer is '{:-010A}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      +INF'"), vformat(SV("answer is '{:+010A}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '       INF'"), vformat(SV("answer is '{: 010A}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '      -INF'"), vformat(SV("answer is '{:010A}'"),  -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -INF'"), vformat(SV("answer is '{:-010A}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -INF'"), vformat(SV("answer is '{:+010A}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -INF'"), vformat(SV("answer is '{: 010A}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '       NAN'"), vformat(SV("answer is '{:010A}'"),  nan_pos));
	EXPECT_EQ(SV("answer is '       NAN'"), vformat(SV("answer is '{:-010A}'"), nan_pos));
	EXPECT_EQ(SV("answer is '      +NAN'"), vformat(SV("answer is '{:+010A}'"), nan_pos));
	EXPECT_EQ(SV("answer is '       NAN'"), vformat(SV("answer is '{: 010A}'"), nan_pos));

	EXPECT_EQ(SV("answer is '      -NAN'"), vformat(SV("answer is '{:010A}'"),  nan_neg));
	EXPECT_EQ(SV("answer is '      -NAN'"), vformat(SV("answer is '{:-010A}'"), nan_neg));
	EXPECT_EQ(SV("answer is '      -NAN'"), vformat(SV("answer is '{:+010A}'"), nan_neg));
	EXPECT_EQ(SV("answer is '      -NAN'"), vformat(SV("answer is '{: 010A}'"), nan_neg));

	// *** precision ***
	// See format_test_floating_point_hex_upper_case_precision

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp
}

template <typename Fn, typename CharT, typename F>
void format_test_floating_point_hex_lower_case_precision()
{
	Fn vformat;

	auto nan_pos = std::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	EXPECT_EQ(SV("answer is '   1.000000p-2'"), vformat(SV("answer is '{:14.6a}'"),  F(0.25)));
	EXPECT_EQ(SV("answer is '   1.000000p-2'"), vformat(SV("answer is '{:>14.6a}'"), F(0.25)));
	EXPECT_EQ(SV("answer is '1.000000p-2   '"), vformat(SV("answer is '{:<14.6a}'"), F(0.25)));
	EXPECT_EQ(SV("answer is ' 1.000000p-2  '"), vformat(SV("answer is '{:^14.6a}'"), F(0.25)));

	EXPECT_EQ(SV("answer is '---1.000000p-3'"), vformat(SV("answer is '{:->14.6a}'"), F(125e-3)));
	EXPECT_EQ(SV("answer is '1.000000p-3---'"), vformat(SV("answer is '{:-<14.6a}'"), F(125e-3)));
	EXPECT_EQ(SV("answer is '-1.000000p-3--'"), vformat(SV("answer is '{:-^14.6a}'"), F(125e-3)));

	EXPECT_EQ(SV("answer is '***inf'"), vformat(SV("answer is '{:*>6.6a}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is 'inf***'"), vformat(SV("answer is '{:*<6.6a}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '*inf**'"), vformat(SV("answer is '{:*^6.6a}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '###-inf'"), vformat(SV("answer is '{:#>7.6a}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf###'"), vformat(SV("answer is '{:#<7.6a}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '#-inf##'"), vformat(SV("answer is '{:#^7.6a}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '^^^nan'"), vformat(SV("answer is '{:^>6.6a}'"), nan_pos));
	EXPECT_EQ(SV("answer is 'nan^^^'"), vformat(SV("answer is '{:^<6.6a}'"), nan_pos));
	EXPECT_EQ(SV("answer is '^nan^^'"), vformat(SV("answer is '{:^^6.6a}'"), nan_pos));

	EXPECT_EQ(SV("answer is '000-nan'"), vformat(SV("answer is '{:0>7.6a}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-nan000'"), vformat(SV("answer is '{:0<7.6a}'"), nan_neg));
	EXPECT_EQ(SV("answer is '0-nan00'"), vformat(SV("answer is '{:0^7.6a}'"), nan_neg));

	// Test whether zero padding is ignored
	EXPECT_EQ(SV("answer is '   1.000000p-2'"), vformat(SV("answer is '{:>014.6a}'"), F(0.25)));
	EXPECT_EQ(SV("answer is '1.000000p-2   '"), vformat(SV("answer is '{:<014.6a}'"), F(0.25)));
	EXPECT_EQ(SV("answer is ' 1.000000p-2  '"), vformat(SV("answer is '{:^014.6a}'"), F(0.25)));

	// *** Sign ***
	EXPECT_EQ(SV("answer is '0.000000p+0'"),  vformat(SV("answer is '{:.6a}'"),  F(0)));
	EXPECT_EQ(SV("answer is '0.000000p+0'"),  vformat(SV("answer is '{:-.6a}'"), F(0)));
	EXPECT_EQ(SV("answer is '+0.000000p+0'"), vformat(SV("answer is '{:+.6a}'"), F(0)));
	EXPECT_EQ(SV("answer is ' 0.000000p+0'"), vformat(SV("answer is '{: .6a}'"), F(0)));

	EXPECT_EQ(SV("answer is '-0.000000p+0'"), vformat(SV("answer is '{:.6a}'"),  F(-0.)));
	EXPECT_EQ(SV("answer is '-0.000000p+0'"), vformat(SV("answer is '{:-.6a}'"), F(-0.)));
	EXPECT_EQ(SV("answer is '-0.000000p+0'"), vformat(SV("answer is '{:+.6a}'"), F(-0.)));
	EXPECT_EQ(SV("answer is '-0.000000p+0'"), vformat(SV("answer is '{: .6a}'"), F(-0.)));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	EXPECT_EQ(SV("answer is 'inf'"),  vformat(SV("answer is '{:.6a}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is 'inf'"),  vformat(SV("answer is '{:-.6a}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '+inf'"), vformat(SV("answer is '{:+.6a}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is ' inf'"), vformat(SV("answer is '{: .6a}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:.6a}'"),  -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:-.6a}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:+.6a}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{: .6a}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is 'nan'"),  vformat(SV("answer is '{:.6a}'"),  nan_pos));
	EXPECT_EQ(SV("answer is 'nan'"),  vformat(SV("answer is '{:-.6a}'"), nan_pos));
	EXPECT_EQ(SV("answer is '+nan'"), vformat(SV("answer is '{:+.6a}'"), nan_pos));
	EXPECT_EQ(SV("answer is ' nan'"), vformat(SV("answer is '{: .6a}'"), nan_pos));

	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:.6a}'"),  nan_neg));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:-.6a}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:+.6a}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{: .6a}'"), nan_neg));

	// *** alternate form ***
	EXPECT_EQ(SV("answer is '1.400000p+1'"), vformat(SV("answer is '{:#.6a}'"), F(2.5)));

	EXPECT_EQ(SV("answer is 'inf'"),  vformat(SV("answer is '{:#.6a}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:#.6a}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is 'nan'"),  vformat(SV("answer is '{:#.6a}'"), nan_pos));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:#.6a}'"), nan_neg));

	// *** zero-padding & width ***
	EXPECT_EQ(SV("answer is '1.000000p-5'"),   vformat(SV("answer is '{:011.6a}'"),  0.03125));
	EXPECT_EQ(SV("answer is '+1.000000p-5'"),  vformat(SV("answer is '{:+012.6a}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+01.000000p-5'"), vformat(SV("answer is '{:+013.6a}'"), 0.03125));

	EXPECT_EQ(SV("answer is '0001.000000p-5'"), vformat(SV("answer is '{:014.6a}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0001.000000p-5'"), vformat(SV("answer is '{:-014.6a}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+001.000000p-5'"), vformat(SV("answer is '{:+014.6a}'"), 0.03125));
	EXPECT_EQ(SV("answer is ' 001.000000p-5'"), vformat(SV("answer is '{: 014.6a}'"), 0.03125));

	EXPECT_EQ(SV("answer is '       inf'"), vformat(SV("answer is '{:010.6a}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '       inf'"), vformat(SV("answer is '{:-010.6a}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      +inf'"), vformat(SV("answer is '{:+010.6a}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '       inf'"), vformat(SV("answer is '{: 010.6a}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{:010.6a}'"),  -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{:-010.6a}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{:+010.6a}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{: 010.6a}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '       nan'"), vformat(SV("answer is '{:010.6a}'"),  nan_pos));
	EXPECT_EQ(SV("answer is '       nan'"), vformat(SV("answer is '{:-010.6a}'"), nan_pos));
	EXPECT_EQ(SV("answer is '      +nan'"), vformat(SV("answer is '{:+010.6a}'"), nan_pos));
	EXPECT_EQ(SV("answer is '       nan'"), vformat(SV("answer is '{: 010.6a}'"), nan_pos));

	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{:010.6a}'"),  nan_neg));
	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{:-010.6a}'"), nan_neg));
	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{:+010.6a}'"), nan_neg));
	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{: 010.6a}'"), nan_neg));

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp
}

template <typename Fn, typename CharT, typename F>
void format_test_floating_point_hex_upper_case_precision()
{
	Fn vformat;

	auto nan_pos = std::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	EXPECT_EQ(SV("answer is '   1.000000P-2'"), vformat(SV("answer is '{:14.6A}'"),  F(0.25)));
	EXPECT_EQ(SV("answer is '   1.000000P-2'"), vformat(SV("answer is '{:>14.6A}'"), F(0.25)));
	EXPECT_EQ(SV("answer is '1.000000P-2   '"), vformat(SV("answer is '{:<14.6A}'"), F(0.25)));
	EXPECT_EQ(SV("answer is ' 1.000000P-2  '"), vformat(SV("answer is '{:^14.6A}'"), F(0.25)));

	EXPECT_EQ(SV("answer is '---1.000000P-3'"), vformat(SV("answer is '{:->14.6A}'"), F(125e-3)));
	EXPECT_EQ(SV("answer is '1.000000P-3---'"), vformat(SV("answer is '{:-<14.6A}'"), F(125e-3)));
	EXPECT_EQ(SV("answer is '-1.000000P-3--'"), vformat(SV("answer is '{:-^14.6A}'"), F(125e-3)));

	EXPECT_EQ(SV("answer is '***INF'"), vformat(SV("answer is '{:*>6.6A}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is 'INF***'"), vformat(SV("answer is '{:*<6.6A}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '*INF**'"), vformat(SV("answer is '{:*^6.6A}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '###-INF'"), vformat(SV("answer is '{:#>7.6A}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-INF###'"), vformat(SV("answer is '{:#<7.6A}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '#-INF##'"), vformat(SV("answer is '{:#^7.6A}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '^^^NAN'"), vformat(SV("answer is '{:^>6.6A}'"), nan_pos));
	EXPECT_EQ(SV("answer is 'NAN^^^'"), vformat(SV("answer is '{:^<6.6A}'"), nan_pos));
	EXPECT_EQ(SV("answer is '^NAN^^'"), vformat(SV("answer is '{:^^6.6A}'"), nan_pos));

	EXPECT_EQ(SV("answer is '000-NAN'"), vformat(SV("answer is '{:0>7.6A}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-NAN000'"), vformat(SV("answer is '{:0<7.6A}'"), nan_neg));
	EXPECT_EQ(SV("answer is '0-NAN00'"), vformat(SV("answer is '{:0^7.6A}'"), nan_neg));

	// Test whether zero padding is ignored
	EXPECT_EQ(SV("answer is '   1.000000P-2'"), vformat(SV("answer is '{:>014.6A}'"), F(0.25)));
	EXPECT_EQ(SV("answer is '1.000000P-2   '"), vformat(SV("answer is '{:<014.6A}'"), F(0.25)));
	EXPECT_EQ(SV("answer is ' 1.000000P-2  '"), vformat(SV("answer is '{:^014.6A}'"), F(0.25)));

	// *** Sign ***
	EXPECT_EQ(SV("answer is '0.000000P+0'"),  vformat(SV("answer is '{:.6A}'"),  F(0)));
	EXPECT_EQ(SV("answer is '0.000000P+0'"),  vformat(SV("answer is '{:-.6A}'"), F(0)));
	EXPECT_EQ(SV("answer is '+0.000000P+0'"), vformat(SV("answer is '{:+.6A}'"), F(0)));
	EXPECT_EQ(SV("answer is ' 0.000000P+0'"), vformat(SV("answer is '{: .6A}'"), F(0)));

	EXPECT_EQ(SV("answer is '-0.000000P+0'"), vformat(SV("answer is '{:.6A}'"),  F(-0.)));
	EXPECT_EQ(SV("answer is '-0.000000P+0'"), vformat(SV("answer is '{:-.6A}'"), F(-0.)));
	EXPECT_EQ(SV("answer is '-0.000000P+0'"), vformat(SV("answer is '{:+.6A}'"), F(-0.)));
	EXPECT_EQ(SV("answer is '-0.000000P+0'"), vformat(SV("answer is '{: .6A}'"), F(-0.)));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	EXPECT_EQ(SV("answer is 'INF'"),  vformat(SV("answer is '{:.6A}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is 'INF'"),  vformat(SV("answer is '{:-.6A}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '+INF'"), vformat(SV("answer is '{:+.6A}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is ' INF'"), vformat(SV("answer is '{: .6A}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '-INF'"), vformat(SV("answer is '{:.6A}'"),  -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-INF'"), vformat(SV("answer is '{:-.6A}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-INF'"), vformat(SV("answer is '{:+.6A}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-INF'"), vformat(SV("answer is '{: .6A}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is 'NAN'"),  vformat(SV("answer is '{:.6A}'"),  nan_pos));
	EXPECT_EQ(SV("answer is 'NAN'"),  vformat(SV("answer is '{:-.6A}'"), nan_pos));
	EXPECT_EQ(SV("answer is '+NAN'"), vformat(SV("answer is '{:+.6A}'"), nan_pos));
	EXPECT_EQ(SV("answer is ' NAN'"), vformat(SV("answer is '{: .6A}'"), nan_pos));

	EXPECT_EQ(SV("answer is '-NAN'"), vformat(SV("answer is '{:.6A}'"),  nan_neg));
	EXPECT_EQ(SV("answer is '-NAN'"), vformat(SV("answer is '{:-.6A}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-NAN'"), vformat(SV("answer is '{:+.6A}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-NAN'"), vformat(SV("answer is '{: .6A}'"), nan_neg));

	// *** alternate form ***
	EXPECT_EQ(SV("answer is '1.400000P+1'"), vformat(SV("answer is '{:#.6A}'"), F(2.5)));

	EXPECT_EQ(SV("answer is 'INF'"),  vformat(SV("answer is '{:#.6A}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-INF'"), vformat(SV("answer is '{:#.6A}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is 'NAN'"),  vformat(SV("answer is '{:#.6A}'"), nan_pos));
	EXPECT_EQ(SV("answer is '-NAN'"), vformat(SV("answer is '{:#.6A}'"), nan_neg));

	// *** zero-padding & width ***
	EXPECT_EQ(SV("answer is '1.000000P-5'"),   vformat(SV("answer is '{:011.6A}'"),  0.03125));
	EXPECT_EQ(SV("answer is '+1.000000P-5'"),  vformat(SV("answer is '{:+012.6A}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+01.000000P-5'"), vformat(SV("answer is '{:+013.6A}'"), 0.03125));

	EXPECT_EQ(SV("answer is '0001.000000P-5'"), vformat(SV("answer is '{:014.6A}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0001.000000P-5'"), vformat(SV("answer is '{:-014.6A}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+001.000000P-5'"), vformat(SV("answer is '{:+014.6A}'"), 0.03125));
	EXPECT_EQ(SV("answer is ' 001.000000P-5'"), vformat(SV("answer is '{: 014.6A}'"), 0.03125));

	EXPECT_EQ(SV("answer is '       INF'"), vformat(SV("answer is '{:010.6A}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '       INF'"), vformat(SV("answer is '{:-010.6A}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      +INF'"), vformat(SV("answer is '{:+010.6A}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '       INF'"), vformat(SV("answer is '{: 010.6A}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '      -INF'"), vformat(SV("answer is '{:010.6A}'"),  -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -INF'"), vformat(SV("answer is '{:-010.6A}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -INF'"), vformat(SV("answer is '{:+010.6A}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -INF'"), vformat(SV("answer is '{: 010.6A}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '       NAN'"), vformat(SV("answer is '{:010.6A}'"),  nan_pos));
	EXPECT_EQ(SV("answer is '       NAN'"), vformat(SV("answer is '{:-010.6A}'"), nan_pos));
	EXPECT_EQ(SV("answer is '      +NAN'"), vformat(SV("answer is '{:+010.6A}'"), nan_pos));
	EXPECT_EQ(SV("answer is '       NAN'"), vformat(SV("answer is '{: 010.6A}'"), nan_pos));

	EXPECT_EQ(SV("answer is '      -NAN'"), vformat(SV("answer is '{:010.6A}'"),  nan_neg));
	EXPECT_EQ(SV("answer is '      -NAN'"), vformat(SV("answer is '{:-010.6A}'"), nan_neg));
	EXPECT_EQ(SV("answer is '      -NAN'"), vformat(SV("answer is '{:+010.6A}'"), nan_neg));
	EXPECT_EQ(SV("answer is '      -NAN'"), vformat(SV("answer is '{: 010.6A}'"), nan_neg));

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp
}

template <typename Fn, typename CharT, typename F>
void format_test_floating_point_scientific_lower_case()
{
	Fn vformat;

	auto nan_pos = std::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	EXPECT_EQ(SV("answer is '   2.500000e-01'"), vformat(SV("answer is '{:15e}'"),  F(0.25)));
	EXPECT_EQ(SV("answer is '   2.500000e-01'"), vformat(SV("answer is '{:>15e}'"), F(0.25)));
	EXPECT_EQ(SV("answer is '2.500000e-01   '"), vformat(SV("answer is '{:<15e}'"), F(0.25)));
	EXPECT_EQ(SV("answer is ' 2.500000e-01  '"), vformat(SV("answer is '{:^15e}'"), F(0.25)));

	EXPECT_EQ(SV("answer is '---1.250000e-01'"), vformat(SV("answer is '{:->15e}'"), F(125e-3)));
	EXPECT_EQ(SV("answer is '1.250000e-01---'"), vformat(SV("answer is '{:-<15e}'"), F(125e-3)));
	EXPECT_EQ(SV("answer is '-1.250000e-01--'"), vformat(SV("answer is '{:-^15e}'"), F(125e-3)));

	EXPECT_EQ(SV("answer is '***inf'"), vformat(SV("answer is '{:*>6e}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is 'inf***'"), vformat(SV("answer is '{:*<6e}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '*inf**'"), vformat(SV("answer is '{:*^6e}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '###-inf'"), vformat(SV("answer is '{:#>7e}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf###'"), vformat(SV("answer is '{:#<7e}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '#-inf##'"), vformat(SV("answer is '{:#^7e}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '^^^nan'"), vformat(SV("answer is '{:^>6e}'"), nan_pos));
	EXPECT_EQ(SV("answer is 'nan^^^'"), vformat(SV("answer is '{:^<6e}'"), nan_pos));
	EXPECT_EQ(SV("answer is '^nan^^'"), vformat(SV("answer is '{:^^6e}'"), nan_pos));

	EXPECT_EQ(SV("answer is '000-nan'"), vformat(SV("answer is '{:0>7e}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-nan000'"), vformat(SV("answer is '{:0<7e}'"), nan_neg));
	EXPECT_EQ(SV("answer is '0-nan00'"), vformat(SV("answer is '{:0^7e}'"), nan_neg));

	// Test whether zero padding is ignored
	EXPECT_EQ(SV("answer is '   2.500000e-01'"), vformat(SV("answer is '{:>015e}'"), F(0.25)));
	EXPECT_EQ(SV("answer is '2.500000e-01   '"), vformat(SV("answer is '{:<015e}'"), F(0.25)));
	EXPECT_EQ(SV("answer is ' 2.500000e-01  '"), vformat(SV("answer is '{:^015e}'"), F(0.25)));

	// *** Sign ***
	EXPECT_EQ(SV("answer is '0.000000e+00'"),  vformat(SV("answer is '{:e}'"),  F(0)));
	EXPECT_EQ(SV("answer is '0.000000e+00'"),  vformat(SV("answer is '{:-e}'"), F(0)));
	EXPECT_EQ(SV("answer is '+0.000000e+00'"), vformat(SV("answer is '{:+e}'"), F(0)));
	EXPECT_EQ(SV("answer is ' 0.000000e+00'"), vformat(SV("answer is '{: e}'"), F(0)));

	EXPECT_EQ(SV("answer is '-0.000000e+00'"), vformat(SV("answer is '{:e}'"),  F(-0.)));
	EXPECT_EQ(SV("answer is '-0.000000e+00'"), vformat(SV("answer is '{:-e}'"), F(-0.)));
	EXPECT_EQ(SV("answer is '-0.000000e+00'"), vformat(SV("answer is '{:+e}'"), F(-0.)));
	EXPECT_EQ(SV("answer is '-0.000000e+00'"), vformat(SV("answer is '{: e}'"), F(-0.)));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	EXPECT_EQ(SV("answer is 'inf'"),  vformat(SV("answer is '{:e}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is 'inf'"),  vformat(SV("answer is '{:-e}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '+inf'"), vformat(SV("answer is '{:+e}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is ' inf'"), vformat(SV("answer is '{: e}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:e}'"),  -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:-e}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:+e}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{: e}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is 'nan'"),  vformat(SV("answer is '{:e}'"),  nan_pos));
	EXPECT_EQ(SV("answer is 'nan'"),  vformat(SV("answer is '{:-e}'"), nan_pos));
	EXPECT_EQ(SV("answer is '+nan'"), vformat(SV("answer is '{:+e}'"), nan_pos));
	EXPECT_EQ(SV("answer is ' nan'"), vformat(SV("answer is '{: e}'"), nan_pos));

	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:e}'"),  nan_neg));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:-e}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:+e}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{: e}'"), nan_neg));

	// *** alternate form **
	// When precision is zero there's no decimal point except when the alternate form is specified.
	EXPECT_EQ(SV("answer is '0e+00'"),  vformat(SV("answer is '{:.0e}'"),  F(0)));
	EXPECT_EQ(SV("answer is '0.e+00'"), vformat(SV("answer is '{:#.0e}'"), F(0)));

	EXPECT_EQ(SV("answer is '0.000000e+00'"), vformat(SV("answer is '{:#e}'"), F(0)));
	EXPECT_EQ(SV("answer is '2.500000e+00'"), vformat(SV("answer is '{:#e}'"), F(2.5)));

	EXPECT_EQ(SV("answer is 'inf'"),  vformat(SV("answer is '{:#e}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:#e}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is 'nan'"),  vformat(SV("answer is '{:#e}'"), nan_pos));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:#e}'"), nan_neg));

	// *** zero-padding & width ***
	EXPECT_EQ(SV("answer is '3.125000e-02'"),  vformat(SV("answer is '{:07e}'"),  0.03125));
	EXPECT_EQ(SV("answer is '+3.125000e-02'"), vformat(SV("answer is '{:+07e}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+3.125000e-02'"), vformat(SV("answer is '{:+08e}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+3.125000e-02'"), vformat(SV("answer is '{:+09e}'"), 0.03125));

	EXPECT_EQ(SV("answer is '003.125000e-02'"), vformat(SV("answer is '{:014e}'"),  0.03125));
	EXPECT_EQ(SV("answer is '003.125000e-02'"), vformat(SV("answer is '{:-014e}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+03.125000e-02'"), vformat(SV("answer is '{:+014e}'"), 0.03125));
	EXPECT_EQ(SV("answer is ' 03.125000e-02'"), vformat(SV("answer is '{: 014e}'"), 0.03125));

	EXPECT_EQ(SV("answer is '       inf'"), vformat(SV("answer is '{:010e}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '       inf'"), vformat(SV("answer is '{:-010e}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      +inf'"), vformat(SV("answer is '{:+010e}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '       inf'"), vformat(SV("answer is '{: 010e}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{:010e}'"),  -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{:-010e}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{:+010e}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{: 010e}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '       nan'"), vformat(SV("answer is '{:010e}'"),  nan_pos));
	EXPECT_EQ(SV("answer is '       nan'"), vformat(SV("answer is '{:-010e}'"), nan_pos));
	EXPECT_EQ(SV("answer is '      +nan'"), vformat(SV("answer is '{:+010e}'"), nan_pos));
	EXPECT_EQ(SV("answer is '       nan'"), vformat(SV("answer is '{: 010e}'"), nan_pos));

	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{:010e}'"),  nan_neg));
	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{:-010e}'"), nan_neg));
	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{:+010e}'"), nan_neg));
	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{: 010e}'"), nan_neg));

	// *** precision ***
	EXPECT_EQ(SV("answer is '3e-02'"),            vformat(SV("answer is '{:.0e}'"),  0.03125));
	EXPECT_EQ(SV("answer is '3.1e-02'"),          vformat(SV("answer is '{:.1e}'"),  0.03125));
	EXPECT_EQ(SV("answer is '3.125e-02'"),        vformat(SV("answer is '{:.3e}'"),  0.03125));
	EXPECT_EQ(SV("answer is '3.1250000000e-02'"), vformat(SV("answer is '{:.10e}'"), 0.03125));

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp
}

template <typename Fn, typename CharT, typename F>
void format_test_floating_point_scientific_upper_case()
{
	Fn vformat;

	auto nan_pos = std::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	EXPECT_EQ(SV("answer is '   2.500000E-01'"), vformat(SV("answer is '{:15E}'"),  F(0.25)));
	EXPECT_EQ(SV("answer is '   2.500000E-01'"), vformat(SV("answer is '{:>15E}'"), F(0.25)));
	EXPECT_EQ(SV("answer is '2.500000E-01   '"), vformat(SV("answer is '{:<15E}'"), F(0.25)));
	EXPECT_EQ(SV("answer is ' 2.500000E-01  '"), vformat(SV("answer is '{:^15E}'"), F(0.25)));

	EXPECT_EQ(SV("answer is '---1.250000E-01'"), vformat(SV("answer is '{:->15E}'"), F(125e-3)));
	EXPECT_EQ(SV("answer is '1.250000E-01---'"), vformat(SV("answer is '{:-<15E}'"), F(125e-3)));
	EXPECT_EQ(SV("answer is '-1.250000E-01--'"), vformat(SV("answer is '{:-^15E}'"), F(125e-3)));

	EXPECT_EQ(SV("answer is '***INF'"), vformat(SV("answer is '{:*>6E}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is 'INF***'"), vformat(SV("answer is '{:*<6E}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '*INF**'"), vformat(SV("answer is '{:*^6E}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '###-INF'"), vformat(SV("answer is '{:#>7E}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-INF###'"), vformat(SV("answer is '{:#<7E}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '#-INF##'"), vformat(SV("answer is '{:#^7E}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '^^^NAN'"), vformat(SV("answer is '{:^>6E}'"), nan_pos));
	EXPECT_EQ(SV("answer is 'NAN^^^'"), vformat(SV("answer is '{:^<6E}'"), nan_pos));
	EXPECT_EQ(SV("answer is '^NAN^^'"), vformat(SV("answer is '{:^^6E}'"), nan_pos));

	EXPECT_EQ(SV("answer is '000-NAN'"), vformat(SV("answer is '{:0>7E}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-NAN000'"), vformat(SV("answer is '{:0<7E}'"), nan_neg));
	EXPECT_EQ(SV("answer is '0-NAN00'"), vformat(SV("answer is '{:0^7E}'"), nan_neg));

	// Test whether zero padding is ignored
	EXPECT_EQ(SV("answer is '   2.500000E-01'"), vformat(SV("answer is '{:>015E}'"), F(0.25)));
	EXPECT_EQ(SV("answer is '2.500000E-01   '"), vformat(SV("answer is '{:<015E}'"), F(0.25)));
	EXPECT_EQ(SV("answer is ' 2.500000E-01  '"), vformat(SV("answer is '{:^015E}'"), F(0.25)));

	// *** Sign ***
	EXPECT_EQ(SV("answer is '0.000000E+00'"),  vformat(SV("answer is '{:E}'"),  F(0)));
	EXPECT_EQ(SV("answer is '0.000000E+00'"),  vformat(SV("answer is '{:-E}'"), F(0)));
	EXPECT_EQ(SV("answer is '+0.000000E+00'"), vformat(SV("answer is '{:+E}'"), F(0)));
	EXPECT_EQ(SV("answer is ' 0.000000E+00'"), vformat(SV("answer is '{: E}'"), F(0)));

	EXPECT_EQ(SV("answer is '-0.000000E+00'"), vformat(SV("answer is '{:E}'"),  F(-0.)));
	EXPECT_EQ(SV("answer is '-0.000000E+00'"), vformat(SV("answer is '{:-E}'"), F(-0.)));
	EXPECT_EQ(SV("answer is '-0.000000E+00'"), vformat(SV("answer is '{:+E}'"), F(-0.)));
	EXPECT_EQ(SV("answer is '-0.000000E+00'"), vformat(SV("answer is '{: E}'"), F(-0.)));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	EXPECT_EQ(SV("answer is 'INF'"),  vformat(SV("answer is '{:E}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is 'INF'"),  vformat(SV("answer is '{:-E}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '+INF'"), vformat(SV("answer is '{:+E}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is ' INF'"), vformat(SV("answer is '{: E}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '-INF'"), vformat(SV("answer is '{:E}'"),  -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-INF'"), vformat(SV("answer is '{:-E}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-INF'"), vformat(SV("answer is '{:+E}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-INF'"), vformat(SV("answer is '{: E}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is 'NAN'"),  vformat(SV("answer is '{:E}'"),  nan_pos));
	EXPECT_EQ(SV("answer is 'NAN'"),  vformat(SV("answer is '{:-E}'"), nan_pos));
	EXPECT_EQ(SV("answer is '+NAN'"), vformat(SV("answer is '{:+E}'"), nan_pos));
	EXPECT_EQ(SV("answer is ' NAN'"), vformat(SV("answer is '{: E}'"), nan_pos));

	EXPECT_EQ(SV("answer is '-NAN'"), vformat(SV("answer is '{:E}'"),  nan_neg));
	EXPECT_EQ(SV("answer is '-NAN'"), vformat(SV("answer is '{:-E}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-NAN'"), vformat(SV("answer is '{:+E}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-NAN'"), vformat(SV("answer is '{: E}'"), nan_neg));

	// *** alternate form **
	// When precision is zero there's no decimal point except when the alternate form is specified.
	EXPECT_EQ(SV("answer is '0E+00'"),  vformat(SV("answer is '{:.0E}'"),  F(0)));
	EXPECT_EQ(SV("answer is '0.E+00'"), vformat(SV("answer is '{:#.0E}'"), F(0)));

	EXPECT_EQ(SV("answer is '0.000000E+00'"), vformat(SV("answer is '{:#E}'"), F(0)));
	EXPECT_EQ(SV("answer is '2.500000E+00'"), vformat(SV("answer is '{:#E}'"), F(2.5)));

	EXPECT_EQ(SV("answer is 'INF'"),  vformat(SV("answer is '{:#E}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-INF'"), vformat(SV("answer is '{:#E}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is 'NAN'"),  vformat(SV("answer is '{:#E}'"), nan_pos));
	EXPECT_EQ(SV("answer is '-NAN'"), vformat(SV("answer is '{:#E}'"), nan_neg));

	// *** zero-padding & width ***
	EXPECT_EQ(SV("answer is '3.125000E-02'"),  vformat(SV("answer is '{:07E}'"),  0.03125));
	EXPECT_EQ(SV("answer is '+3.125000E-02'"), vformat(SV("answer is '{:+07E}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+3.125000E-02'"), vformat(SV("answer is '{:+08E}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+3.125000E-02'"), vformat(SV("answer is '{:+09E}'"), 0.03125));

	EXPECT_EQ(SV("answer is '003.125000E-02'"), vformat(SV("answer is '{:014E}'"),  0.03125));
	EXPECT_EQ(SV("answer is '003.125000E-02'"), vformat(SV("answer is '{:-014E}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+03.125000E-02'"), vformat(SV("answer is '{:+014E}'"), 0.03125));
	EXPECT_EQ(SV("answer is ' 03.125000E-02'"), vformat(SV("answer is '{: 014E}'"), 0.03125));

	EXPECT_EQ(SV("answer is '       INF'"), vformat(SV("answer is '{:010E}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '       INF'"), vformat(SV("answer is '{:-010E}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      +INF'"), vformat(SV("answer is '{:+010E}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '       INF'"), vformat(SV("answer is '{: 010E}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '      -INF'"), vformat(SV("answer is '{:010E}'"),  -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -INF'"), vformat(SV("answer is '{:-010E}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -INF'"), vformat(SV("answer is '{:+010E}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -INF'"), vformat(SV("answer is '{: 010E}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '       NAN'"), vformat(SV("answer is '{:010E}'"),  nan_pos));
	EXPECT_EQ(SV("answer is '       NAN'"), vformat(SV("answer is '{:-010E}'"), nan_pos));
	EXPECT_EQ(SV("answer is '      +NAN'"), vformat(SV("answer is '{:+010E}'"), nan_pos));
	EXPECT_EQ(SV("answer is '       NAN'"), vformat(SV("answer is '{: 010E}'"), nan_pos));

	EXPECT_EQ(SV("answer is '      -NAN'"), vformat(SV("answer is '{:010E}'"),  nan_neg));
	EXPECT_EQ(SV("answer is '      -NAN'"), vformat(SV("answer is '{:-010E}'"), nan_neg));
	EXPECT_EQ(SV("answer is '      -NAN'"), vformat(SV("answer is '{:+010E}'"), nan_neg));
	EXPECT_EQ(SV("answer is '      -NAN'"), vformat(SV("answer is '{: 010E}'"), nan_neg));

	// *** precision ***
	EXPECT_EQ(SV("answer is '3E-02'"),            vformat(SV("answer is '{:.0E}'"),  0.03125));
	EXPECT_EQ(SV("answer is '3.1E-02'"),          vformat(SV("answer is '{:.1E}'"),  0.03125));
	EXPECT_EQ(SV("answer is '3.125E-02'"),        vformat(SV("answer is '{:.3E}'"),  0.03125));
	EXPECT_EQ(SV("answer is '3.1250000000E-02'"), vformat(SV("answer is '{:.10E}'"), 0.03125));

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp
}

template <typename Fn, typename CharT, typename F>
void format_test_floating_point_fixed_lower_case()
{
	Fn vformat;

	auto nan_pos = std::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	EXPECT_EQ(SV("answer is '   0.250000'"), vformat(SV("answer is '{:11f}'"),  F(0.25)));
	EXPECT_EQ(SV("answer is '   0.250000'"), vformat(SV("answer is '{:>11f}'"), F(0.25)));
	EXPECT_EQ(SV("answer is '0.250000   '"), vformat(SV("answer is '{:<11f}'"), F(0.25)));
	EXPECT_EQ(SV("answer is ' 0.250000  '"), vformat(SV("answer is '{:^11f}'"), F(0.25)));

	EXPECT_EQ(SV("answer is '---0.125000'"), vformat(SV("answer is '{:->11f}'"), F(125e-3)));
	EXPECT_EQ(SV("answer is '0.125000---'"), vformat(SV("answer is '{:-<11f}'"), F(125e-3)));
	EXPECT_EQ(SV("answer is '-0.125000--'"), vformat(SV("answer is '{:-^11f}'"), F(125e-3)));

	EXPECT_EQ(SV("answer is '***inf'"), vformat(SV("answer is '{:*>6f}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is 'inf***'"), vformat(SV("answer is '{:*<6f}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '*inf**'"), vformat(SV("answer is '{:*^6f}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '###-inf'"), vformat(SV("answer is '{:#>7f}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf###'"), vformat(SV("answer is '{:#<7f}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '#-inf##'"), vformat(SV("answer is '{:#^7f}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '^^^nan'"), vformat(SV("answer is '{:^>6f}'"), nan_pos));
	EXPECT_EQ(SV("answer is 'nan^^^'"), vformat(SV("answer is '{:^<6f}'"), nan_pos));
	EXPECT_EQ(SV("answer is '^nan^^'"), vformat(SV("answer is '{:^^6f}'"), nan_pos));

	EXPECT_EQ(SV("answer is '000-nan'"), vformat(SV("answer is '{:0>7f}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-nan000'"), vformat(SV("answer is '{:0<7f}'"), nan_neg));
	EXPECT_EQ(SV("answer is '0-nan00'"), vformat(SV("answer is '{:0^7f}'"), nan_neg));

	// Test whether zero padding is ignored
	EXPECT_EQ(SV("answer is '   0.250000'"), vformat(SV("answer is '{:>011f}'"), F(0.25)));
	EXPECT_EQ(SV("answer is '0.250000   '"), vformat(SV("answer is '{:<011f}'"), F(0.25)));
	EXPECT_EQ(SV("answer is ' 0.250000  '"), vformat(SV("answer is '{:^011f}'"), F(0.25)));

	// *** Sign ***
	EXPECT_EQ(SV("answer is '0.000000'"),  vformat(SV("answer is '{:f}'"),  F(0)));
	EXPECT_EQ(SV("answer is '0.000000'"),  vformat(SV("answer is '{:-f}'"), F(0)));
	EXPECT_EQ(SV("answer is '+0.000000'"), vformat(SV("answer is '{:+f}'"), F(0)));
	EXPECT_EQ(SV("answer is ' 0.000000'"), vformat(SV("answer is '{: f}'"), F(0)));

	EXPECT_EQ(SV("answer is '-0.000000'"), vformat(SV("answer is '{:f}'"),  F(-0.)));
	EXPECT_EQ(SV("answer is '-0.000000'"), vformat(SV("answer is '{:-f}'"), F(-0.)));
	EXPECT_EQ(SV("answer is '-0.000000'"), vformat(SV("answer is '{:+f}'"), F(-0.)));
	EXPECT_EQ(SV("answer is '-0.000000'"), vformat(SV("answer is '{: f}'"), F(-0.)));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	EXPECT_EQ(SV("answer is 'inf'"),  vformat(SV("answer is '{:f}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is 'inf'"),  vformat(SV("answer is '{:-f}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '+inf'"), vformat(SV("answer is '{:+f}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is ' inf'"), vformat(SV("answer is '{: f}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:f}'"),  -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:-f}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:+f}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{: f}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is 'nan'"),  vformat(SV("answer is '{:f}'"),  nan_pos));
	EXPECT_EQ(SV("answer is 'nan'"),  vformat(SV("answer is '{:-f}'"), nan_pos));
	EXPECT_EQ(SV("answer is '+nan'"), vformat(SV("answer is '{:+f}'"), nan_pos));
	EXPECT_EQ(SV("answer is ' nan'"), vformat(SV("answer is '{: f}'"), nan_pos));

	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:f}'"),  nan_neg));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:-f}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:+f}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{: f}'"), nan_neg));

	// *** alternate form **
	// When precision is zero there's no decimal point except when the alternate form is specified.
	EXPECT_EQ(SV("answer is '0'"),  vformat(SV("answer is '{:.0f}'"),  F(0)));
	EXPECT_EQ(SV("answer is '0.'"), vformat(SV("answer is '{:#.0f}'"), F(0)));

	EXPECT_EQ(SV("answer is '0.000000'"), vformat(SV("answer is '{:#f}'"), F(0)));
	EXPECT_EQ(SV("answer is '2.500000'"), vformat(SV("answer is '{:#f}'"), F(2.5)));

	EXPECT_EQ(SV("answer is 'inf'"),  vformat(SV("answer is '{:#f}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:#f}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is 'nan'"),  vformat(SV("answer is '{:#f}'"), nan_pos));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:#f}'"), nan_neg));

	// *** zero-padding & width ***
	EXPECT_EQ(SV("answer is '0.031250'"),  vformat(SV("answer is '{:07f}'"),  0.03125));
	EXPECT_EQ(SV("answer is '+0.031250'"), vformat(SV("answer is '{:+07f}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+0.031250'"), vformat(SV("answer is '{:+08f}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+0.031250'"), vformat(SV("answer is '{:+09f}'"), 0.03125));

	EXPECT_EQ(SV("answer is '000.031250'"), vformat(SV("answer is '{:010f}'"),  0.03125));
	EXPECT_EQ(SV("answer is '000.031250'"), vformat(SV("answer is '{:-010f}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+00.031250'"), vformat(SV("answer is '{:+010f}'"), 0.03125));
	EXPECT_EQ(SV("answer is ' 00.031250'"), vformat(SV("answer is '{: 010f}'"), 0.03125));

	EXPECT_EQ(SV("answer is '       inf'"), vformat(SV("answer is '{:010f}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '       inf'"), vformat(SV("answer is '{:-010f}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      +inf'"), vformat(SV("answer is '{:+010f}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '       inf'"), vformat(SV("answer is '{: 010f}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{:010f}'"),  -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{:-010f}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{:+010f}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{: 010f}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '       nan'"), vformat(SV("answer is '{:010f}'"),  nan_pos));
	EXPECT_EQ(SV("answer is '       nan'"), vformat(SV("answer is '{:-010f}'"), nan_pos));
	EXPECT_EQ(SV("answer is '      +nan'"), vformat(SV("answer is '{:+010f}'"), nan_pos));
	EXPECT_EQ(SV("answer is '       nan'"), vformat(SV("answer is '{: 010f}'"), nan_pos));

	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{:010f}'"),  nan_neg));
	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{:-010f}'"), nan_neg));
	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{:+010f}'"), nan_neg));
	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{: 010f}'"), nan_neg));

	// *** precision ***
	EXPECT_EQ(SV("answer is '0'"),            vformat(SV("answer is '{:.0f}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0.0'"),          vformat(SV("answer is '{:.1f}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0.03125'"),      vformat(SV("answer is '{:.5f}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0.0312500000'"), vformat(SV("answer is '{:.10f}'"), 0.03125));

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp
}

template <typename Fn, typename CharT, typename F>
void format_test_floating_point_fixed_upper_case()
{
	Fn vformat;

	auto nan_pos = std::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	EXPECT_EQ(SV("answer is '   0.250000'"), vformat(SV("answer is '{:11F}'"),  F(0.25)));
	EXPECT_EQ(SV("answer is '   0.250000'"), vformat(SV("answer is '{:>11F}'"), F(0.25)));
	EXPECT_EQ(SV("answer is '0.250000   '"), vformat(SV("answer is '{:<11F}'"), F(0.25)));
	EXPECT_EQ(SV("answer is ' 0.250000  '"), vformat(SV("answer is '{:^11F}'"), F(0.25)));

	EXPECT_EQ(SV("answer is '---0.125000'"), vformat(SV("answer is '{:->11F}'"), F(125e-3)));
	EXPECT_EQ(SV("answer is '0.125000---'"), vformat(SV("answer is '{:-<11F}'"), F(125e-3)));
	EXPECT_EQ(SV("answer is '-0.125000--'"), vformat(SV("answer is '{:-^11F}'"), F(125e-3)));

	EXPECT_EQ(SV("answer is '***INF'"), vformat(SV("answer is '{:*>6F}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is 'INF***'"), vformat(SV("answer is '{:*<6F}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '*INF**'"), vformat(SV("answer is '{:*^6F}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '###-INF'"), vformat(SV("answer is '{:#>7F}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-INF###'"), vformat(SV("answer is '{:#<7F}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '#-INF##'"), vformat(SV("answer is '{:#^7F}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '^^^NAN'"), vformat(SV("answer is '{:^>6F}'"), nan_pos));
	EXPECT_EQ(SV("answer is 'NAN^^^'"), vformat(SV("answer is '{:^<6F}'"), nan_pos));
	EXPECT_EQ(SV("answer is '^NAN^^'"), vformat(SV("answer is '{:^^6F}'"), nan_pos));

	EXPECT_EQ(SV("answer is '000-NAN'"), vformat(SV("answer is '{:0>7F}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-NAN000'"), vformat(SV("answer is '{:0<7F}'"), nan_neg));
	EXPECT_EQ(SV("answer is '0-NAN00'"), vformat(SV("answer is '{:0^7F}'"), nan_neg));

	// Test whether zero padding is ignored
	EXPECT_EQ(SV("answer is '   0.250000'"), vformat(SV("answer is '{:>011F}'"), F(0.25)));
	EXPECT_EQ(SV("answer is '0.250000   '"), vformat(SV("answer is '{:<011F}'"), F(0.25)));
	EXPECT_EQ(SV("answer is ' 0.250000  '"), vformat(SV("answer is '{:^011F}'"), F(0.25)));

	// *** Sign ***
	EXPECT_EQ(SV("answer is '0.000000'"),  vformat(SV("answer is '{:F}'"),  F(0)));
	EXPECT_EQ(SV("answer is '0.000000'"),  vformat(SV("answer is '{:-F}'"), F(0)));
	EXPECT_EQ(SV("answer is '+0.000000'"), vformat(SV("answer is '{:+F}'"), F(0)));
	EXPECT_EQ(SV("answer is ' 0.000000'"), vformat(SV("answer is '{: F}'"), F(0)));

	EXPECT_EQ(SV("answer is '-0.000000'"), vformat(SV("answer is '{:F}'"),  F(-0.)));
	EXPECT_EQ(SV("answer is '-0.000000'"), vformat(SV("answer is '{:-F}'"), F(-0.)));
	EXPECT_EQ(SV("answer is '-0.000000'"), vformat(SV("answer is '{:+F}'"), F(-0.)));
	EXPECT_EQ(SV("answer is '-0.000000'"), vformat(SV("answer is '{: F}'"), F(-0.)));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	EXPECT_EQ(SV("answer is 'INF'"),  vformat(SV("answer is '{:F}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is 'INF'"),  vformat(SV("answer is '{:-F}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '+INF'"), vformat(SV("answer is '{:+F}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is ' INF'"), vformat(SV("answer is '{: F}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '-INF'"), vformat(SV("answer is '{:F}'"),  -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-INF'"), vformat(SV("answer is '{:-F}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-INF'"), vformat(SV("answer is '{:+F}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-INF'"), vformat(SV("answer is '{: F}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is 'NAN'"),  vformat(SV("answer is '{:F}'"),  nan_pos));
	EXPECT_EQ(SV("answer is 'NAN'"),  vformat(SV("answer is '{:-F}'"), nan_pos));
	EXPECT_EQ(SV("answer is '+NAN'"), vformat(SV("answer is '{:+F}'"), nan_pos));
	EXPECT_EQ(SV("answer is ' NAN'"), vformat(SV("answer is '{: F}'"), nan_pos));

	EXPECT_EQ(SV("answer is '-NAN'"), vformat(SV("answer is '{:F}'"),  nan_neg));
	EXPECT_EQ(SV("answer is '-NAN'"), vformat(SV("answer is '{:-F}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-NAN'"), vformat(SV("answer is '{:+F}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-NAN'"), vformat(SV("answer is '{: F}'"), nan_neg));

	// *** alternate form **
	// When precision is zero there's no decimal point except when the alternate form is specified.
	EXPECT_EQ(SV("answer is '0'"),  vformat(SV("answer is '{:.0F}'"),  F(0)));
	EXPECT_EQ(SV("answer is '0.'"), vformat(SV("answer is '{:#.0F}'"), F(0)));

	EXPECT_EQ(SV("answer is '0.000000'"), vformat(SV("answer is '{:#F}'"), F(0)));
	EXPECT_EQ(SV("answer is '2.500000'"), vformat(SV("answer is '{:#F}'"), F(2.5)));

	EXPECT_EQ(SV("answer is 'INF'"),  vformat(SV("answer is '{:#F}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-INF'"), vformat(SV("answer is '{:#F}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is 'NAN'"),  vformat(SV("answer is '{:#F}'"), nan_pos));
	EXPECT_EQ(SV("answer is '-NAN'"), vformat(SV("answer is '{:#F}'"), nan_neg));

	// *** zero-padding & width ***
	EXPECT_EQ(SV("answer is '0.031250'"),  vformat(SV("answer is '{:07F}'"),  0.03125));
	EXPECT_EQ(SV("answer is '+0.031250'"), vformat(SV("answer is '{:+07F}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+0.031250'"), vformat(SV("answer is '{:+08F}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+0.031250'"), vformat(SV("answer is '{:+09F}'"), 0.03125));

	EXPECT_EQ(SV("answer is '000.031250'"), vformat(SV("answer is '{:010F}'"),  0.03125));
	EXPECT_EQ(SV("answer is '000.031250'"), vformat(SV("answer is '{:-010F}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+00.031250'"), vformat(SV("answer is '{:+010F}'"), 0.03125));
	EXPECT_EQ(SV("answer is ' 00.031250'"), vformat(SV("answer is '{: 010F}'"), 0.03125));

	EXPECT_EQ(SV("answer is '       INF'"), vformat(SV("answer is '{:010F}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '       INF'"), vformat(SV("answer is '{:-010F}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      +INF'"), vformat(SV("answer is '{:+010F}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '       INF'"), vformat(SV("answer is '{: 010F}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '      -INF'"), vformat(SV("answer is '{:010F}'"),  -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -INF'"), vformat(SV("answer is '{:-010F}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -INF'"), vformat(SV("answer is '{:+010F}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -INF'"), vformat(SV("answer is '{: 010F}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '       NAN'"), vformat(SV("answer is '{:010F}'"),  nan_pos));
	EXPECT_EQ(SV("answer is '       NAN'"), vformat(SV("answer is '{:-010F}'"), nan_pos));
	EXPECT_EQ(SV("answer is '      +NAN'"), vformat(SV("answer is '{:+010F}'"), nan_pos));
	EXPECT_EQ(SV("answer is '       NAN'"), vformat(SV("answer is '{: 010F}'"), nan_pos));

	EXPECT_EQ(SV("answer is '      -NAN'"), vformat(SV("answer is '{:010F}'"),  nan_neg));
	EXPECT_EQ(SV("answer is '      -NAN'"), vformat(SV("answer is '{:-010F}'"), nan_neg));
	EXPECT_EQ(SV("answer is '      -NAN'"), vformat(SV("answer is '{:+010F}'"), nan_neg));
	EXPECT_EQ(SV("answer is '      -NAN'"), vformat(SV("answer is '{: 010F}'"), nan_neg));

	// *** precision ***
	EXPECT_EQ(SV("answer is '0'"),            vformat(SV("answer is '{:.0F}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0.0'"),          vformat(SV("answer is '{:.1F}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0.03125'"),      vformat(SV("answer is '{:.5F}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0.0312500000'"), vformat(SV("answer is '{:.10F}'"), 0.03125));

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp
}

template <typename Fn, typename CharT, typename F>
void format_test_floating_point_general_lower_case()
{
	Fn vformat;

	auto nan_pos = std::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	EXPECT_EQ(SV("answer is '   0.25'"), vformat(SV("answer is '{:7g}'"),  F(0.25)));
	EXPECT_EQ(SV("answer is '   0.25'"), vformat(SV("answer is '{:>7g}'"), F(0.25)));
	EXPECT_EQ(SV("answer is '0.25   '"), vformat(SV("answer is '{:<7g}'"), F(0.25)));
	EXPECT_EQ(SV("answer is ' 0.25  '"), vformat(SV("answer is '{:^7g}'"), F(0.25)));

	EXPECT_EQ(SV("answer is '---0.125'"), vformat(SV("answer is '{:->8g}'"), F(125e-3)));
	EXPECT_EQ(SV("answer is '0.125---'"), vformat(SV("answer is '{:-<8g}'"), F(125e-3)));
	EXPECT_EQ(SV("answer is '-0.125--'"), vformat(SV("answer is '{:-^8g}'"), F(125e-3)));

	EXPECT_EQ(SV("answer is '***inf'"), vformat(SV("answer is '{:*>6g}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is 'inf***'"), vformat(SV("answer is '{:*<6g}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '*inf**'"), vformat(SV("answer is '{:*^6g}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '###-inf'"), vformat(SV("answer is '{:#>7g}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf###'"), vformat(SV("answer is '{:#<7g}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '#-inf##'"), vformat(SV("answer is '{:#^7g}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '^^^nan'"), vformat(SV("answer is '{:^>6g}'"), nan_pos));
	EXPECT_EQ(SV("answer is 'nan^^^'"), vformat(SV("answer is '{:^<6g}'"), nan_pos));
	EXPECT_EQ(SV("answer is '^nan^^'"), vformat(SV("answer is '{:^^6g}'"), nan_pos));

	EXPECT_EQ(SV("answer is '000-nan'"), vformat(SV("answer is '{:0>7g}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-nan000'"), vformat(SV("answer is '{:0<7g}'"), nan_neg));
	EXPECT_EQ(SV("answer is '0-nan00'"), vformat(SV("answer is '{:0^7g}'"), nan_neg));

	// Test whether zero padding is ignored
	EXPECT_EQ(SV("answer is '   0.25'"), vformat(SV("answer is '{:>07g}'"), F(0.25)));
	EXPECT_EQ(SV("answer is '0.25   '"), vformat(SV("answer is '{:<07g}'"), F(0.25)));
	EXPECT_EQ(SV("answer is ' 0.25  '"), vformat(SV("answer is '{:^07g}'"), F(0.25)));

	// *** Sign ***
	EXPECT_EQ(SV("answer is '0'"),  vformat(SV("answer is '{:g}'"),  F(0)));
	EXPECT_EQ(SV("answer is '0'"),  vformat(SV("answer is '{:-g}'"), F(0)));
	EXPECT_EQ(SV("answer is '+0'"), vformat(SV("answer is '{:+g}'"), F(0)));
	EXPECT_EQ(SV("answer is ' 0'"), vformat(SV("answer is '{: g}'"), F(0)));

	EXPECT_EQ(SV("answer is '-0'"), vformat(SV("answer is '{:g}'"),  F(-0.)));
	EXPECT_EQ(SV("answer is '-0'"), vformat(SV("answer is '{:-g}'"), F(-0.)));
	EXPECT_EQ(SV("answer is '-0'"), vformat(SV("answer is '{:+g}'"), F(-0.)));
	EXPECT_EQ(SV("answer is '-0'"), vformat(SV("answer is '{: g}'"), F(-0.)));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	EXPECT_EQ(SV("answer is 'inf'"),  vformat(SV("answer is '{:g}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is 'inf'"),  vformat(SV("answer is '{:-g}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '+inf'"), vformat(SV("answer is '{:+g}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is ' inf'"), vformat(SV("answer is '{: g}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:g}'"),  -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:-g}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:+g}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{: g}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is 'nan'"),  vformat(SV("answer is '{:g}'"),  nan_pos));
	EXPECT_EQ(SV("answer is 'nan'"),  vformat(SV("answer is '{:-g}'"), nan_pos));
	EXPECT_EQ(SV("answer is '+nan'"), vformat(SV("answer is '{:+g}'"), nan_pos));
	EXPECT_EQ(SV("answer is ' nan'"), vformat(SV("answer is '{: g}'"), nan_pos));

	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:g}'"),  nan_neg));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:-g}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:+g}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{: g}'"), nan_neg));

	// *** alternate form **
	// When precision is zero there's no decimal point except when the alternate form is specified.
	EXPECT_EQ(SV("answer is '0'"),  vformat(SV("answer is '{:.0g}'"),  F(0)));
	EXPECT_EQ(SV("answer is '0.'"), vformat(SV("answer is '{:#.0g}'"), F(0)));

	EXPECT_EQ(SV("answer is '0.00000'"), vformat(SV("answer is '{:#g}'"), F(0)));
	EXPECT_EQ(SV("answer is '2.50000'"), vformat(SV("answer is '{:#g}'"), F(2.5)));

	EXPECT_EQ(SV("answer is 'inf'"),  vformat(SV("answer is '{:#g}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:#g}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is 'nan'"),  vformat(SV("answer is '{:#g}'"), nan_pos));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:#g}'"), nan_neg));

	// *** zero-padding & width ***
	EXPECT_EQ(SV("answer is '0.03125'"),  vformat(SV("answer is '{:06g}'"),  0.03125));
	EXPECT_EQ(SV("answer is '+0.03125'"), vformat(SV("answer is '{:+06g}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+0.03125'"), vformat(SV("answer is '{:+07g}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+0.03125'"), vformat(SV("answer is '{:+08g}'"), 0.03125));

	EXPECT_EQ(SV("answer is '000.03125'"), vformat(SV("answer is '{:09g}'"),  0.03125));
	EXPECT_EQ(SV("answer is '000.03125'"), vformat(SV("answer is '{:-09g}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+00.03125'"), vformat(SV("answer is '{:+09g}'"), 0.03125));
	EXPECT_EQ(SV("answer is ' 00.03125'"), vformat(SV("answer is '{: 09g}'"), 0.03125));

	EXPECT_EQ(SV("answer is '       inf'"), vformat(SV("answer is '{:010g}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '       inf'"), vformat(SV("answer is '{:-010g}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      +inf'"), vformat(SV("answer is '{:+010g}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '       inf'"), vformat(SV("answer is '{: 010g}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{:010g}'"),  -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{:-010g}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{:+010g}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{: 010g}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '       nan'"), vformat(SV("answer is '{:010g}'"),  nan_pos));
	EXPECT_EQ(SV("answer is '       nan'"), vformat(SV("answer is '{:-010g}'"), nan_pos));
	EXPECT_EQ(SV("answer is '      +nan'"), vformat(SV("answer is '{:+010g}'"), nan_pos));
	EXPECT_EQ(SV("answer is '       nan'"), vformat(SV("answer is '{: 010g}'"), nan_pos));

	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{:010g}'"),  nan_neg));
	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{:-010g}'"), nan_neg));
	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{:+010g}'"), nan_neg));
	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{: 010g}'"), nan_neg));

	// *** precision ***
	EXPECT_EQ(SV("answer is '0.03'"),    vformat(SV("answer is '{:.0g}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0.03'"),    vformat(SV("answer is '{:.1g}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0.031'"),   vformat(SV("answer is '{:.2g}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0.0312'"),  vformat(SV("answer is '{:.3g}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0.03125'"), vformat(SV("answer is '{:.4g}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0.03125'"), vformat(SV("answer is '{:.5g}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0.03125'"), vformat(SV("answer is '{:.10g}'"), 0.03125));

	// *** precision & alternate form ***

	// Output validated with  printf("%#xg")
	EXPECT_EQ(SV("answer is '1.'"),      vformat(SV("answer is '{:#.{}g}'"), 1.2, 0));
	EXPECT_EQ(SV("answer is '1.'"),      vformat(SV("answer is '{:#.{}g}'"), 1.2, 1));
	EXPECT_EQ(SV("answer is '1.2'"),     vformat(SV("answer is '{:#.{}g}'"), 1.2, 2));
	EXPECT_EQ(SV("answer is '1.20'"),    vformat(SV("answer is '{:#.{}g}'"), 1.2, 3));
	EXPECT_EQ(SV("answer is '1.200'"),   vformat(SV("answer is '{:#.{}g}'"), 1.2, 4));
	EXPECT_EQ(SV("answer is '1.2000'"),  vformat(SV("answer is '{:#.{}g}'"), 1.2, 5));
	EXPECT_EQ(SV("answer is '1.20000'"), vformat(SV("answer is '{:#.{}g}'"), 1.2, 6));

	EXPECT_EQ(SV("answer is '1.e+03'"),   vformat(SV("answer is '{:#.{}g}'"), 1200.0, 0));
	EXPECT_EQ(SV("answer is '1.e+03'"),   vformat(SV("answer is '{:#.{}g}'"), 1200.0, 1));
	EXPECT_EQ(SV("answer is '1.2e+03'"),  vformat(SV("answer is '{:#.{}g}'"), 1200.0, 2));
	EXPECT_EQ(SV("answer is '1.20e+03'"), vformat(SV("answer is '{:#.{}g}'"), 1200.0, 3));
	EXPECT_EQ(SV("answer is '1200.'"),    vformat(SV("answer is '{:#.{}g}'"), 1200.0, 4));
	EXPECT_EQ(SV("answer is '1200.0'"),   vformat(SV("answer is '{:#.{}g}'"), 1200.0, 5));
	EXPECT_EQ(SV("answer is '1200.00'"),  vformat(SV("answer is '{:#.{}g}'"), 1200.0, 6));

	EXPECT_EQ(SV("answer is '1.e+06'"),      vformat(SV("answer is '{:#.{}g}'"), 1200000.0, 0));
	EXPECT_EQ(SV("answer is '1.e+06'"),      vformat(SV("answer is '{:#.{}g}'"), 1200000.0, 1));
	EXPECT_EQ(SV("answer is '1.2e+06'"),     vformat(SV("answer is '{:#.{}g}'"), 1200000.0, 2));
	EXPECT_EQ(SV("answer is '1.20e+06'"),    vformat(SV("answer is '{:#.{}g}'"), 1200000.0, 3));
	EXPECT_EQ(SV("answer is '1.200e+06'"),   vformat(SV("answer is '{:#.{}g}'"), 1200000.0, 4));
	EXPECT_EQ(SV("answer is '1.2000e+06'"),  vformat(SV("answer is '{:#.{}g}'"), 1200000.0, 5));
	EXPECT_EQ(SV("answer is '1.20000e+06'"), vformat(SV("answer is '{:#.{}g}'"), 1200000.0, 6));

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp
}

template <typename Fn, typename CharT, typename F>
void format_test_floating_point_general_upper_case()
{
	Fn vformat;

	auto nan_pos = std::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	EXPECT_EQ(SV("answer is '   0.25'"), vformat(SV("answer is '{:7G}'"),  F(0.25)));
	EXPECT_EQ(SV("answer is '   0.25'"), vformat(SV("answer is '{:>7G}'"), F(0.25)));
	EXPECT_EQ(SV("answer is '0.25   '"), vformat(SV("answer is '{:<7G}'"), F(0.25)));
	EXPECT_EQ(SV("answer is ' 0.25  '"), vformat(SV("answer is '{:^7G}'"), F(0.25)));

	EXPECT_EQ(SV("answer is '---0.125'"), vformat(SV("answer is '{:->8G}'"), F(125e-3)));
	EXPECT_EQ(SV("answer is '0.125---'"), vformat(SV("answer is '{:-<8G}'"), F(125e-3)));
	EXPECT_EQ(SV("answer is '-0.125--'"), vformat(SV("answer is '{:-^8G}'"), F(125e-3)));

	EXPECT_EQ(SV("answer is '***INF'"), vformat(SV("answer is '{:*>6G}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is 'INF***'"), vformat(SV("answer is '{:*<6G}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '*INF**'"), vformat(SV("answer is '{:*^6G}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '###-INF'"), vformat(SV("answer is '{:#>7G}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-INF###'"), vformat(SV("answer is '{:#<7G}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '#-INF##'"), vformat(SV("answer is '{:#^7G}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '^^^NAN'"), vformat(SV("answer is '{:^>6G}'"), nan_pos));
	EXPECT_EQ(SV("answer is 'NAN^^^'"), vformat(SV("answer is '{:^<6G}'"), nan_pos));
	EXPECT_EQ(SV("answer is '^NAN^^'"), vformat(SV("answer is '{:^^6G}'"), nan_pos));

	EXPECT_EQ(SV("answer is '000-NAN'"), vformat(SV("answer is '{:0>7G}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-NAN000'"), vformat(SV("answer is '{:0<7G}'"), nan_neg));
	EXPECT_EQ(SV("answer is '0-NAN00'"), vformat(SV("answer is '{:0^7G}'"), nan_neg));

	// Test whether zero padding is ignored
	EXPECT_EQ(SV("answer is '   0.25'"), vformat(SV("answer is '{:>07G}'"), F(0.25)));
	EXPECT_EQ(SV("answer is '0.25   '"), vformat(SV("answer is '{:<07G}'"), F(0.25)));
	EXPECT_EQ(SV("answer is ' 0.25  '"), vformat(SV("answer is '{:^07G}'"), F(0.25)));

	// *** Sign ***
	EXPECT_EQ(SV("answer is '0'"),  vformat(SV("answer is '{:G}'"),  F(0)));
	EXPECT_EQ(SV("answer is '0'"),  vformat(SV("answer is '{:-G}'"), F(0)));
	EXPECT_EQ(SV("answer is '+0'"), vformat(SV("answer is '{:+G}'"), F(0)));
	EXPECT_EQ(SV("answer is ' 0'"), vformat(SV("answer is '{: G}'"), F(0)));

	EXPECT_EQ(SV("answer is '-0'"), vformat(SV("answer is '{:G}'"),  F(-0.)));
	EXPECT_EQ(SV("answer is '-0'"), vformat(SV("answer is '{:-G}'"), F(-0.)));
	EXPECT_EQ(SV("answer is '-0'"), vformat(SV("answer is '{:+G}'"), F(-0.)));
	EXPECT_EQ(SV("answer is '-0'"), vformat(SV("answer is '{: G}'"), F(-0.)));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	EXPECT_EQ(SV("answer is 'INF'"),  vformat(SV("answer is '{:G}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is 'INF'"),  vformat(SV("answer is '{:-G}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '+INF'"), vformat(SV("answer is '{:+G}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is ' INF'"), vformat(SV("answer is '{: G}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '-INF'"), vformat(SV("answer is '{:G}'"),  -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-INF'"), vformat(SV("answer is '{:-G}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-INF'"), vformat(SV("answer is '{:+G}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-INF'"), vformat(SV("answer is '{: G}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is 'NAN'"),  vformat(SV("answer is '{:G}'"),  nan_pos));
	EXPECT_EQ(SV("answer is 'NAN'"),  vformat(SV("answer is '{:-G}'"), nan_pos));
	EXPECT_EQ(SV("answer is '+NAN'"), vformat(SV("answer is '{:+G}'"), nan_pos));
	EXPECT_EQ(SV("answer is ' NAN'"), vformat(SV("answer is '{: G}'"), nan_pos));

	EXPECT_EQ(SV("answer is '-NAN'"), vformat(SV("answer is '{:G}'"),  nan_neg));
	EXPECT_EQ(SV("answer is '-NAN'"), vformat(SV("answer is '{:-G}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-NAN'"), vformat(SV("answer is '{:+G}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-NAN'"), vformat(SV("answer is '{: G}'"), nan_neg));

	// *** alternate form **
	// When precision is zero there's no decimal point except when the alternate form is specified.
	EXPECT_EQ(SV("answer is '0'"),  vformat(SV("answer is '{:.0G}'"),  F(0)));
	EXPECT_EQ(SV("answer is '0.'"), vformat(SV("answer is '{:#.0G}'"), F(0)));

	EXPECT_EQ(SV("answer is '0.00000'"), vformat(SV("answer is '{:#G}'"), F(0)));
	EXPECT_EQ(SV("answer is '2.50000'"), vformat(SV("answer is '{:#G}'"), F(2.5)));

	EXPECT_EQ(SV("answer is 'INF'"),  vformat(SV("answer is '{:#G}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-INF'"), vformat(SV("answer is '{:#G}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is 'NAN'"),  vformat(SV("answer is '{:#G}'"), nan_pos));
	EXPECT_EQ(SV("answer is '-NAN'"), vformat(SV("answer is '{:#G}'"), nan_neg));

	// *** zero-padding & width ***
	EXPECT_EQ(SV("answer is '0.03125'"),  vformat(SV("answer is '{:06G}'"),  0.03125));
	EXPECT_EQ(SV("answer is '+0.03125'"), vformat(SV("answer is '{:+06G}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+0.03125'"), vformat(SV("answer is '{:+07G}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+0.03125'"), vformat(SV("answer is '{:+08G}'"), 0.03125));

	EXPECT_EQ(SV("answer is '000.03125'"), vformat(SV("answer is '{:09G}'"),  0.03125));
	EXPECT_EQ(SV("answer is '000.03125'"), vformat(SV("answer is '{:-09G}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+00.03125'"), vformat(SV("answer is '{:+09G}'"), 0.03125));
	EXPECT_EQ(SV("answer is ' 00.03125'"), vformat(SV("answer is '{: 09G}'"), 0.03125));

	EXPECT_EQ(SV("answer is '       INF'"), vformat(SV("answer is '{:010G}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '       INF'"), vformat(SV("answer is '{:-010G}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      +INF'"), vformat(SV("answer is '{:+010G}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '       INF'"), vformat(SV("answer is '{: 010G}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '      -INF'"), vformat(SV("answer is '{:010G}'"),  -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -INF'"), vformat(SV("answer is '{:-010G}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -INF'"), vformat(SV("answer is '{:+010G}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -INF'"), vformat(SV("answer is '{: 010G}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '       NAN'"), vformat(SV("answer is '{:010G}'"),  nan_pos));
	EXPECT_EQ(SV("answer is '       NAN'"), vformat(SV("answer is '{:-010G}'"), nan_pos));
	EXPECT_EQ(SV("answer is '      +NAN'"), vformat(SV("answer is '{:+010G}'"), nan_pos));
	EXPECT_EQ(SV("answer is '       NAN'"), vformat(SV("answer is '{: 010G}'"), nan_pos));

	EXPECT_EQ(SV("answer is '      -NAN'"), vformat(SV("answer is '{:010G}'"),  nan_neg));
	EXPECT_EQ(SV("answer is '      -NAN'"), vformat(SV("answer is '{:-010G}'"), nan_neg));
	EXPECT_EQ(SV("answer is '      -NAN'"), vformat(SV("answer is '{:+010G}'"), nan_neg));
	EXPECT_EQ(SV("answer is '      -NAN'"), vformat(SV("answer is '{: 010G}'"), nan_neg));

	// *** precision ***
	EXPECT_EQ(SV("answer is '0.03'"),    vformat(SV("answer is '{:.0G}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0.03'"),    vformat(SV("answer is '{:.1G}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0.031'"),   vformat(SV("answer is '{:.2G}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0.0312'"),  vformat(SV("answer is '{:.3G}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0.03125'"), vformat(SV("answer is '{:.4G}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0.03125'"), vformat(SV("answer is '{:.5G}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0.03125'"), vformat(SV("answer is '{:.10G}'"), 0.03125));

	// *** precision & alternate form ***

	// Output validated with  printf("%#xg")
	EXPECT_EQ(SV("answer is '1.'"),      vformat(SV("answer is '{:#.{}G}'"), 1.2, 0));
	EXPECT_EQ(SV("answer is '1.'"),      vformat(SV("answer is '{:#.{}G}'"), 1.2, 1));
	EXPECT_EQ(SV("answer is '1.2'"),     vformat(SV("answer is '{:#.{}G}'"), 1.2, 2));
	EXPECT_EQ(SV("answer is '1.20'"),    vformat(SV("answer is '{:#.{}G}'"), 1.2, 3));
	EXPECT_EQ(SV("answer is '1.200'"),   vformat(SV("answer is '{:#.{}G}'"), 1.2, 4));
	EXPECT_EQ(SV("answer is '1.2000'"),  vformat(SV("answer is '{:#.{}G}'"), 1.2, 5));
	EXPECT_EQ(SV("answer is '1.20000'"), vformat(SV("answer is '{:#.{}G}'"), 1.2, 6));

	EXPECT_EQ(SV("answer is '1.E+03'"),   vformat(SV("answer is '{:#.{}G}'"), 1200.0, 0));
	EXPECT_EQ(SV("answer is '1.E+03'"),   vformat(SV("answer is '{:#.{}G}'"), 1200.0, 1));
	EXPECT_EQ(SV("answer is '1.2E+03'"),  vformat(SV("answer is '{:#.{}G}'"), 1200.0, 2));
	EXPECT_EQ(SV("answer is '1.20E+03'"), vformat(SV("answer is '{:#.{}G}'"), 1200.0, 3));
	EXPECT_EQ(SV("answer is '1200.'"),    vformat(SV("answer is '{:#.{}G}'"), 1200.0, 4));
	EXPECT_EQ(SV("answer is '1200.0'"),   vformat(SV("answer is '{:#.{}G}'"), 1200.0, 5));
	EXPECT_EQ(SV("answer is '1200.00'"),  vformat(SV("answer is '{:#.{}G}'"), 1200.0, 6));

	EXPECT_EQ(SV("answer is '1.E+06'"),      vformat(SV("answer is '{:#.{}G}'"), 1200000.0, 0));
	EXPECT_EQ(SV("answer is '1.E+06'"),      vformat(SV("answer is '{:#.{}G}'"), 1200000.0, 1));
	EXPECT_EQ(SV("answer is '1.2E+06'"),     vformat(SV("answer is '{:#.{}G}'"), 1200000.0, 2));
	EXPECT_EQ(SV("answer is '1.20E+06'"),    vformat(SV("answer is '{:#.{}G}'"), 1200000.0, 3));
	EXPECT_EQ(SV("answer is '1.200E+06'"),   vformat(SV("answer is '{:#.{}G}'"), 1200000.0, 4));
	EXPECT_EQ(SV("answer is '1.2000E+06'"),  vformat(SV("answer is '{:#.{}G}'"), 1200000.0, 5));
	EXPECT_EQ(SV("answer is '1.20000E+06'"), vformat(SV("answer is '{:#.{}G}'"), 1200000.0, 6));

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp
}

template <typename Fn, typename CharT, typename F>
void format_test_floating_point_default()
{
	Fn vformat;

	auto nan_pos = std::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	EXPECT_EQ(SV("answer is '   0.25'"), vformat(SV("answer is '{:7}'"),  F(0.25)));
	EXPECT_EQ(SV("answer is '   0.25'"), vformat(SV("answer is '{:>7}'"), F(0.25)));
	EXPECT_EQ(SV("answer is '0.25   '"), vformat(SV("answer is '{:<7}'"), F(0.25)));
	EXPECT_EQ(SV("answer is ' 0.25  '"), vformat(SV("answer is '{:^7}'"), F(0.25)));

	EXPECT_EQ(SV("answer is '---0.125'"), vformat(SV("answer is '{:->8}'"), F(125e-3)));
	EXPECT_EQ(SV("answer is '0.125---'"), vformat(SV("answer is '{:-<8}'"), F(125e-3)));
	EXPECT_EQ(SV("answer is '-0.125--'"), vformat(SV("answer is '{:-^8}'"), F(125e-3)));

	EXPECT_EQ(SV("answer is '***inf'"), vformat(SV("answer is '{:*>6}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is 'inf***'"), vformat(SV("answer is '{:*<6}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '*inf**'"), vformat(SV("answer is '{:*^6}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '###-inf'"), vformat(SV("answer is '{:#>7}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf###'"), vformat(SV("answer is '{:#<7}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '#-inf##'"), vformat(SV("answer is '{:#^7}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '^^^nan'"), vformat(SV("answer is '{:^>6}'"), nan_pos));
	EXPECT_EQ(SV("answer is 'nan^^^'"), vformat(SV("answer is '{:^<6}'"), nan_pos));
	EXPECT_EQ(SV("answer is '^nan^^'"), vformat(SV("answer is '{:^^6}'"), nan_pos));

	EXPECT_EQ(SV("answer is '000-nan'"), vformat(SV("answer is '{:0>7}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-nan000'"), vformat(SV("answer is '{:0<7}'"), nan_neg));
	EXPECT_EQ(SV("answer is '0-nan00'"), vformat(SV("answer is '{:0^7}'"), nan_neg));

	// Test whether zero padding is ignored
	EXPECT_EQ(SV("answer is '   0.25'"), vformat(SV("answer is '{:>07}'"), F(0.25)));
	EXPECT_EQ(SV("answer is '0.25   '"), vformat(SV("answer is '{:<07}'"), F(0.25)));
	EXPECT_EQ(SV("answer is ' 0.25  '"), vformat(SV("answer is '{:^07}'"), F(0.25)));

	// *** Sign ***
	EXPECT_EQ(SV("answer is '0'"),  vformat(SV("answer is '{:}'"),  F(0)));
	EXPECT_EQ(SV("answer is '0'"),  vformat(SV("answer is '{:-}'"), F(0)));
	EXPECT_EQ(SV("answer is '+0'"), vformat(SV("answer is '{:+}'"), F(0)));
	EXPECT_EQ(SV("answer is ' 0'"), vformat(SV("answer is '{: }'"), F(0)));

	EXPECT_EQ(SV("answer is '-0'"), vformat(SV("answer is '{:}'"),  F(-0.)));
	EXPECT_EQ(SV("answer is '-0'"), vformat(SV("answer is '{:-}'"), F(-0.)));
	EXPECT_EQ(SV("answer is '-0'"), vformat(SV("answer is '{:+}'"), F(-0.)));
	EXPECT_EQ(SV("answer is '-0'"), vformat(SV("answer is '{: }'"), F(-0.)));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	EXPECT_EQ(SV("answer is 'inf'"),  vformat(SV("answer is '{:}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is 'inf'"),  vformat(SV("answer is '{:-}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '+inf'"), vformat(SV("answer is '{:+}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is ' inf'"), vformat(SV("answer is '{: }'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:}'"),  -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:-}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:+}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{: }'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is 'nan'"),  vformat(SV("answer is '{:}'"),  nan_pos));
	EXPECT_EQ(SV("answer is 'nan'"),  vformat(SV("answer is '{:-}'"), nan_pos));
	EXPECT_EQ(SV("answer is '+nan'"), vformat(SV("answer is '{:+}'"), nan_pos));
	EXPECT_EQ(SV("answer is ' nan'"), vformat(SV("answer is '{: }'"), nan_pos));

	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:}'"),  nan_neg));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:-}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:+}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{: }'"), nan_neg));

	// *** alternate form ***
	EXPECT_EQ(SV("answer is '0.'"),  vformat(SV("answer is '{:#}'"), F(0)));
	EXPECT_EQ(SV("answer is '2.5'"), vformat(SV("answer is '{:#}'"), F(2.5)));

	EXPECT_EQ(SV("answer is 'inf'"),  vformat(SV("answer is '{:#}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:#}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is 'nan'"),  vformat(SV("answer is '{:#}'"), nan_pos));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:#}'"), nan_neg));

	// *** zero-padding & width ***
	EXPECT_EQ(SV("answer is '0.03125'"),   vformat(SV("answer is '{:07}'"),  0.03125));
	EXPECT_EQ(SV("answer is '+0.03125'"),  vformat(SV("answer is '{:+07}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+0.03125'"),  vformat(SV("answer is '{:+08}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+00.03125'"), vformat(SV("answer is '{:+09}'"), 0.03125));

	EXPECT_EQ(SV("answer is '0000.03125'"), vformat(SV("answer is '{:010}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0000.03125'"), vformat(SV("answer is '{:-010}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+000.03125'"), vformat(SV("answer is '{:+010}'"), 0.03125));
	EXPECT_EQ(SV("answer is ' 000.03125'"), vformat(SV("answer is '{: 010}'"), 0.03125));

	EXPECT_EQ(SV("answer is '       inf'"), vformat(SV("answer is '{:010}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '       inf'"), vformat(SV("answer is '{:-010}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      +inf'"), vformat(SV("answer is '{:+010}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '       inf'"), vformat(SV("answer is '{: 010}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{:010}'"),  -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{:-010}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{:+010}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{: 010}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '       nan'"), vformat(SV("answer is '{:010}'"),  nan_pos));
	EXPECT_EQ(SV("answer is '       nan'"), vformat(SV("answer is '{:-010}'"), nan_pos));
	EXPECT_EQ(SV("answer is '      +nan'"), vformat(SV("answer is '{:+010}'"), nan_pos));
	EXPECT_EQ(SV("answer is '       nan'"), vformat(SV("answer is '{: 010}'"), nan_pos));

	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{:010}'"),  nan_neg));
	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{:-010}'"), nan_neg));
	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{:+010}'"), nan_neg));
	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{: 010}'"), nan_neg));

	// *** precision ***
	// See format_test_floating_point_default_precision

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp
}

template <typename Fn, typename CharT, typename F>
void format_test_floating_point_default_precision()
{
	Fn vformat;

	auto nan_pos = std::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	EXPECT_EQ(SV("answer is '   0.25'"), vformat(SV("answer is '{:7.6}'"),  F(0.25)));
	EXPECT_EQ(SV("answer is '   0.25'"), vformat(SV("answer is '{:>7.6}'"), F(0.25)));
	EXPECT_EQ(SV("answer is '0.25   '"), vformat(SV("answer is '{:<7.6}'"), F(0.25)));
	EXPECT_EQ(SV("answer is ' 0.25  '"), vformat(SV("answer is '{:^7.6}'"), F(0.25)));

	EXPECT_EQ(SV("answer is '---0.125'"), vformat(SV("answer is '{:->8.6}'"), F(125e-3)));
	EXPECT_EQ(SV("answer is '0.125---'"), vformat(SV("answer is '{:-<8.6}'"), F(125e-3)));
	EXPECT_EQ(SV("answer is '-0.125--'"), vformat(SV("answer is '{:-^8.6}'"), F(125e-3)));

	EXPECT_EQ(SV("answer is '***inf'"), vformat(SV("answer is '{:*>6.6}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is 'inf***'"), vformat(SV("answer is '{:*<6.6}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '*inf**'"), vformat(SV("answer is '{:*^6.6}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '###-inf'"), vformat(SV("answer is '{:#>7.6}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf###'"), vformat(SV("answer is '{:#<7.6}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '#-inf##'"), vformat(SV("answer is '{:#^7.6}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '^^^nan'"), vformat(SV("answer is '{:^>6.6}'"), nan_pos));
	EXPECT_EQ(SV("answer is 'nan^^^'"), vformat(SV("answer is '{:^<6.6}'"), nan_pos));
	EXPECT_EQ(SV("answer is '^nan^^'"), vformat(SV("answer is '{:^^6.6}'"), nan_pos));

	EXPECT_EQ(SV("answer is '000-nan'"), vformat(SV("answer is '{:0>7.6}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-nan000'"), vformat(SV("answer is '{:0<7.6}'"), nan_neg));
	EXPECT_EQ(SV("answer is '0-nan00'"), vformat(SV("answer is '{:0^7.6}'"), nan_neg));

	// Test whether zero padding is ignored
	EXPECT_EQ(SV("answer is '   0.25'"), vformat(SV("answer is '{:>07.6}'"), F(0.25)));
	EXPECT_EQ(SV("answer is '0.25   '"), vformat(SV("answer is '{:<07.6}'"), F(0.25)));
	EXPECT_EQ(SV("answer is ' 0.25  '"), vformat(SV("answer is '{:^07.6}'"), F(0.25)));

	// *** Sign ***
	EXPECT_EQ(SV("answer is '0'"),  vformat(SV("answer is '{:.6}'"),  F(0)));
	EXPECT_EQ(SV("answer is '0'"),  vformat(SV("answer is '{:-.6}'"), F(0)));
	EXPECT_EQ(SV("answer is '+0'"), vformat(SV("answer is '{:+.6}'"), F(0)));
	EXPECT_EQ(SV("answer is ' 0'"), vformat(SV("answer is '{: .6}'"), F(0)));

	EXPECT_EQ(SV("answer is '-0'"), vformat(SV("answer is '{:.6}'"),  F(-0.)));
	EXPECT_EQ(SV("answer is '-0'"), vformat(SV("answer is '{:-.6}'"), F(-0.)));
	EXPECT_EQ(SV("answer is '-0'"), vformat(SV("answer is '{:+.6}'"), F(-0.)));
	EXPECT_EQ(SV("answer is '-0'"), vformat(SV("answer is '{: .6}'"), F(-0.)));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	EXPECT_EQ(SV("answer is 'inf'"),  vformat(SV("answer is '{:.6}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is 'inf'"),  vformat(SV("answer is '{:-.6}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '+inf'"), vformat(SV("answer is '{:+.6}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is ' inf'"), vformat(SV("answer is '{: .6}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:.6}'"),  -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:-.6}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:+.6}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{: .6}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is 'nan'"),  vformat(SV("answer is '{:.6}'"),  nan_pos));
	EXPECT_EQ(SV("answer is 'nan'"),  vformat(SV("answer is '{:-.6}'"), nan_pos));
	EXPECT_EQ(SV("answer is '+nan'"), vformat(SV("answer is '{:+.6}'"), nan_pos));
	EXPECT_EQ(SV("answer is ' nan'"), vformat(SV("answer is '{: .6}'"), nan_pos));

	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:.6}'"),  nan_neg));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:-.6}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:+.6}'"), nan_neg));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{: .6}'"), nan_neg));

	// *** alternate form **
	// When precision is zero there's no decimal point except when the alternate form is specified.
	// Note unlike the g and G option the trailing zeros are still removed.
	EXPECT_EQ(SV("answer is '0'"),  vformat(SV("answer is '{:.0}'"),  F(0)));
	EXPECT_EQ(SV("answer is '0.'"), vformat(SV("answer is '{:#.0}'"), F(0)));

	EXPECT_EQ(SV("answer is '0.'"),  vformat(SV("answer is '{:#.6}'"), F(0)));
	EXPECT_EQ(SV("answer is '2.5'"), vformat(SV("answer is '{:#.6}'"), F(2.5)));

	EXPECT_EQ(SV("answer is 'inf'"),  vformat(SV("answer is '{:#.6}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '-inf'"), vformat(SV("answer is '{:#.6}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is 'nan'"),  vformat(SV("answer is '{:#.6}'"), nan_pos));
	EXPECT_EQ(SV("answer is '-nan'"), vformat(SV("answer is '{:#.6}'"), nan_neg));

	// *** zero-padding & width ***
	EXPECT_EQ(SV("answer is '0.03125'"),  vformat(SV("answer is '{:06.6}'"),  0.03125));
	EXPECT_EQ(SV("answer is '+0.03125'"), vformat(SV("answer is '{:+06.6}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+0.03125'"), vformat(SV("answer is '{:+07.6}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+0.03125'"), vformat(SV("answer is '{:+08.6}'"), 0.03125));

	EXPECT_EQ(SV("answer is '000.03125'"), vformat(SV("answer is '{:09.6}'"),  0.03125));
	EXPECT_EQ(SV("answer is '000.03125'"), vformat(SV("answer is '{:-09.6}'"), 0.03125));
	EXPECT_EQ(SV("answer is '+00.03125'"), vformat(SV("answer is '{:+09.6}'"), 0.03125));
	EXPECT_EQ(SV("answer is ' 00.03125'"), vformat(SV("answer is '{: 09.6}'"), 0.03125));

	EXPECT_EQ(SV("answer is '       inf'"), vformat(SV("answer is '{:010.6}'"),  std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '       inf'"), vformat(SV("answer is '{:-010.6}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      +inf'"), vformat(SV("answer is '{:+010.6}'"), std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '       inf'"), vformat(SV("answer is '{: 010.6}'"), std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{:010.6}'"),  -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{:-010.6}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{:+010.6}'"), -std::numeric_limits<F>::infinity()));
	EXPECT_EQ(SV("answer is '      -inf'"), vformat(SV("answer is '{: 010.6}'"), -std::numeric_limits<F>::infinity()));

	EXPECT_EQ(SV("answer is '       nan'"), vformat(SV("answer is '{:010.6}'"),  nan_pos));
	EXPECT_EQ(SV("answer is '       nan'"), vformat(SV("answer is '{:-010.6}'"), nan_pos));
	EXPECT_EQ(SV("answer is '      +nan'"), vformat(SV("answer is '{:+010.6}'"), nan_pos));
	EXPECT_EQ(SV("answer is '       nan'"), vformat(SV("answer is '{: 010.6}'"), nan_pos));

	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{:010.6}'"),  nan_neg));
	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{:-010.6}'"), nan_neg));
	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{:+010.6}'"), nan_neg));
	EXPECT_EQ(SV("answer is '      -nan'"), vformat(SV("answer is '{: 010.6}'"), nan_neg));

	// *** precision ***
	EXPECT_EQ(SV("answer is '0.03'"),    vformat(SV("answer is '{:.0}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0.03'"),    vformat(SV("answer is '{:.1}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0.031'"),   vformat(SV("answer is '{:.2}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0.0312'"),  vformat(SV("answer is '{:.3}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0.03125'"), vformat(SV("answer is '{:.4}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0.03125'"), vformat(SV("answer is '{:.5}'"),  0.03125));
	EXPECT_EQ(SV("answer is '0.03125'"), vformat(SV("answer is '{:.10}'"), 0.03125));

	// *** precision & alternate form ***

	EXPECT_EQ(SV("answer is '1.'"),  vformat(SV("answer is '{:#.{}}'"), 1.2, 0));
	EXPECT_EQ(SV("answer is '1.'"),  vformat(SV("answer is '{:#.{}}'"), 1.2, 1));
	EXPECT_EQ(SV("answer is '1.2'"), vformat(SV("answer is '{:#.{}}'"), 1.2, 2));
	EXPECT_EQ(SV("answer is '1.2'"), vformat(SV("answer is '{:#.{}}'"), 1.2, 3));
	EXPECT_EQ(SV("answer is '1.2'"), vformat(SV("answer is '{:#.{}}'"), 1.2, 4));
	EXPECT_EQ(SV("answer is '1.2'"), vformat(SV("answer is '{:#.{}}'"), 1.2, 5));
	EXPECT_EQ(SV("answer is '1.2'"), vformat(SV("answer is '{:#.{}}'"), 1.2, 6));

	EXPECT_EQ(SV("answer is '1.e+03'"),  vformat(SV("answer is '{:#.{}}'"), 1200.0, 0));
	EXPECT_EQ(SV("answer is '1.e+03'"),  vformat(SV("answer is '{:#.{}}'"), 1200.0, 1));
	EXPECT_EQ(SV("answer is '1.2e+03'"), vformat(SV("answer is '{:#.{}}'"), 1200.0, 2));
	EXPECT_EQ(SV("answer is '1.2e+03'"), vformat(SV("answer is '{:#.{}}'"), 1200.0, 3));
	EXPECT_EQ(SV("answer is '1200.'"),   vformat(SV("answer is '{:#.{}}'"), 1200.0, 4));
	EXPECT_EQ(SV("answer is '1200.'"),   vformat(SV("answer is '{:#.{}}'"), 1200.0, 5));
	EXPECT_EQ(SV("answer is '1200.'"),   vformat(SV("answer is '{:#.{}}'"), 1200.0, 6));

	EXPECT_EQ(SV("answer is '1.e+06'"),  vformat(SV("answer is '{:#.{}}'"), 1200000.0, 0));
	EXPECT_EQ(SV("answer is '1.e+06'"),  vformat(SV("answer is '{:#.{}}'"), 1200000.0, 1));
	EXPECT_EQ(SV("answer is '1.2e+06'"), vformat(SV("answer is '{:#.{}}'"), 1200000.0, 2));
	EXPECT_EQ(SV("answer is '1.2e+06'"), vformat(SV("answer is '{:#.{}}'"), 1200000.0, 3));
	EXPECT_EQ(SV("answer is '1.2e+06'"), vformat(SV("answer is '{:#.{}}'"), 1200000.0, 4));
	EXPECT_EQ(SV("answer is '1.2e+06'"), vformat(SV("answer is '{:#.{}}'"), 1200000.0, 5));
	EXPECT_EQ(SV("answer is '1.2e+06'"), vformat(SV("answer is '{:#.{}}'"), 1200000.0, 6));

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp
}

template <typename Fn, typename CharT, typename F>
void format_test_floating_point_PR58714()
{
	Fn vformat;

	EXPECT_EQ(SV("+1234"),         vformat(SV("{:+}"),  F(1234.0)));
	EXPECT_EQ(SV("+1.348p+10"),    vformat(SV("{:+a}"), F(1234.0)));
	EXPECT_EQ(SV("+1.234000e+03"), vformat(SV("{:+e}"), F(1234.0)));
	EXPECT_EQ(SV("+1234.000000"),  vformat(SV("{:+f}"), F(1234.0)));
	EXPECT_EQ(SV("+1234"),         vformat(SV("{:+g}"), F(1234.0)));

	EXPECT_EQ(SV("1234."),        vformat(SV("{:#}"),  F(1234.0)));
	EXPECT_EQ(SV("1.348p+10"),    vformat(SV("{:#a}"), F(1234.0)));
	EXPECT_EQ(SV("1.234000e+03"), vformat(SV("{:#e}"), F(1234.0)));
	EXPECT_EQ(SV("1234.000000"),  vformat(SV("{:#f}"), F(1234.0)));
	EXPECT_EQ(SV("1234.00"),      vformat(SV("{:#g}"), F(1234.0)));

	EXPECT_EQ(SV("4.e+30"),       vformat(SV("{:#}"),  F(4.0e+30)));
	EXPECT_EQ(SV("1.p+102"),      vformat(SV("{:#a}"), F(0x4.0p+100)));
	EXPECT_EQ(SV("4.000000e+30"), vformat(SV("{:#e}"), F(4.0e+30)));
	EXPECT_EQ(SV("5070602400912917605986812821504.000000"), vformat(SV("{:#f}"), F(0x4.0p+100)));
	EXPECT_EQ(SV("4.00000e+30"),  vformat(SV("{:#g}"), F(4.0e+30)));

	EXPECT_EQ(SV("1234."),        vformat(SV("{:#.6}"),  F(1234.0))); // # does not restore zeros
	EXPECT_EQ(SV("1.348000p+10"), vformat(SV("{:#.6a}"), F(1234.0)));
	EXPECT_EQ(SV("1.234000e+03"), vformat(SV("{:#.6e}"), F(1234.0)));
	EXPECT_EQ(SV("1234.000000"),  vformat(SV("{:#.6f}"), F(1234.0)));
	EXPECT_EQ(SV("1234.00"),      vformat(SV("{:#.6g}"), F(1234.0)));

	EXPECT_EQ(SV("-1234."),        vformat(SV("{:#}"),  F(-1234.0)));
	EXPECT_EQ(SV("-1.348p+10"),    vformat(SV("{:#a}"), F(-1234.0)));
	EXPECT_EQ(SV("-1.234000e+03"), vformat(SV("{:#e}"), F(-1234.0)));
	EXPECT_EQ(SV("-1234.000000"),  vformat(SV("{:#f}"), F(-1234.0)));
	EXPECT_EQ(SV("-1234.00"),      vformat(SV("{:#g}"), F(-1234.0)));

	EXPECT_EQ(SV("-1234."),        vformat(SV("{:#.6}"),  F(-1234.0))); // # does not restore zeros
	EXPECT_EQ(SV("-1.348000p+10"), vformat(SV("{:#.6a}"), F(-1234.0)));
	EXPECT_EQ(SV("-1.234000e+03"), vformat(SV("{:#.6e}"), F(-1234.0)));
	EXPECT_EQ(SV("-1234.000000"),  vformat(SV("{:#.6f}"), F(-1234.0)));
	EXPECT_EQ(SV("-1234.00"),      vformat(SV("{:#.6g}"), F(-1234.0)));

	EXPECT_EQ(SV("+1234."),        vformat(SV("{:+#}"),  F(1234.0)));
	EXPECT_EQ(SV("+1.348p+10"),    vformat(SV("{:+#a}"), F(1234.0)));
	EXPECT_EQ(SV("+1.234000e+03"), vformat(SV("{:+#e}"), F(1234.0)));
	EXPECT_EQ(SV("+1234.000000"),  vformat(SV("{:+#f}"), F(1234.0)));
	EXPECT_EQ(SV("+1234.00"),      vformat(SV("{:+#g}"), F(1234.0)));

	EXPECT_EQ(SV("+1234."),        vformat(SV("{:+#.6}"),  F(1234.0))); // # does not restore zeros
	EXPECT_EQ(SV("+1.348000p+10"), vformat(SV("{:+#.6a}"), F(1234.0)));
	EXPECT_EQ(SV("+1.234000e+03"), vformat(SV("{:+#.6e}"), F(1234.0)));
	EXPECT_EQ(SV("+1234.000000"),  vformat(SV("{:+#.6f}"), F(1234.0)));
	EXPECT_EQ(SV("+1234.00"),      vformat(SV("{:+#.6g}"), F(1234.0)));
}

template <typename Fn, typename CharT, typename F>
void test_floating_point_impl()
{
	Fn vformat;

	format_test_floating_point_hex_lower_case<Fn, CharT, F>();
	format_test_floating_point_hex_upper_case<Fn, CharT, F>();
	format_test_floating_point_hex_lower_case_precision<Fn, CharT, F>();
	format_test_floating_point_hex_upper_case_precision<Fn, CharT, F>();

	format_test_floating_point_scientific_lower_case<Fn, CharT, F>();
	format_test_floating_point_scientific_upper_case<Fn, CharT, F>();

	format_test_floating_point_fixed_lower_case<Fn, CharT, F>();
	format_test_floating_point_fixed_upper_case<Fn, CharT, F>();

	format_test_floating_point_general_lower_case<Fn, CharT, F>();
	format_test_floating_point_general_upper_case<Fn, CharT, F>();

	format_test_floating_point_default<Fn, CharT, F>();
	format_test_floating_point_default_precision<Fn, CharT, F>();

	format_test_floating_point_PR58714<Fn, CharT, F>();

	// *** type ***
	EXPECT_NO_THROW(vformat(SV("{:a}"), F(1)));
	EXPECT_NO_THROW(vformat(SV("{:A}"), F(1)));
	EXPECT_THROW   (vformat(SV("{:b}"), F(1)), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:B}"), F(1)), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:c}"), F(1)), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:d}"), F(1)), hamon::format_error);
	EXPECT_NO_THROW(vformat(SV("{:e}"), F(1)));
	EXPECT_NO_THROW(vformat(SV("{:E}"), F(1)));
	EXPECT_NO_THROW(vformat(SV("{:f}"), F(1)));
	EXPECT_NO_THROW(vformat(SV("{:F}"), F(1)));
	EXPECT_NO_THROW(vformat(SV("{:g}"), F(1)));
	EXPECT_NO_THROW(vformat(SV("{:G}"), F(1)));
	EXPECT_THROW   (vformat(SV("{:o}"), F(1)), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:p}"), F(1)), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:P}"), F(1)), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:s}"), F(1)), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:x}"), F(1)), hamon::format_error);
	EXPECT_THROW   (vformat(SV("{:X}"), F(1)), hamon::format_error);
//	EXPECT_THROW   (vformat(SV("{:?}"), F(1)), hamon::format_error);	// C++23
}

template <typename Fn, typename CharT>
void test_floating_point()
{
	Fn vformat;

	// *** Test floating point format argument ***
	EXPECT_EQ(SV("hello 42"), vformat(SV("hello {}"), static_cast<float>(42)));
	EXPECT_EQ(SV("hello 42"), vformat(SV("hello {}"), static_cast<double>(42)));
	EXPECT_EQ(SV("hello 42"), vformat(SV("hello {}"), static_cast<long double>(42)));

	test_floating_point_impl<Fn, CharT, float>();
	test_floating_point_impl<Fn, CharT, double>();
//	test_floating_point_impl<Fn, CharT, long double>();		// TODO
}

template <typename Fn, typename CharT>
void test()
{
	test_escape<Fn, CharT>();
	test_arg_id<Fn, CharT>();
	test_many_args<Fn, CharT>();
	test_buffer_copy<Fn, CharT>();
	test_buffer_fill<Fn, CharT>();
	test_invalid_format_strings<Fn, CharT>();
	test_char<Fn, CharT>();
	test_char_as_integer<Fn, CharT>();
	test_string<Fn, CharT>();
	test_bool<Fn, CharT>();
	test_bool_as_integer<Fn, CharT>();
	test_signed_integer<Fn, CharT>();
	test_unsigned_integer<Fn, CharT>();
	test_floating_point<Fn, CharT>();
	test_pointer<Fn, CharT>();
	test_handle<Fn, CharT>();
	test_buffer_optimizations<Fn, CharT>();
}

#undef SV
#undef STR

GTEST_TEST(FormatTest, VFormatTest)
{
	test<VFormat, char>();
	test<VFormat, wchar_t>();
	test<VFormatLoc, char>();
	test<VFormatLoc, wchar_t>();
}

}	// namespace vformat_test

}	// namespace hamon_format_test
