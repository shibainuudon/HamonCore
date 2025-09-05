/**
 *	@file	unit_test_format_format.cpp
 *
 *	@brief	format のテスト
 *
 *	template<class... Args>
 *	string format(format_string<Args...> fmt, Args&&... args);
 *	template<class... Args>
 *	wstring format(wformat_string<Args...> fmt, Args&&... args);
 *	template<class... Args>
 *	string format(const locale& loc, format_string<Args...> fmt, Args&&... args);
 *	template<class... Args>
 *	wstring format(const locale& loc, wformat_string<Args...> fmt, Args&&... args);
 */

#include <hamon/format/format.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_format_test
{

namespace format_test
{

// A user-defined type used to test the handle formatter.
enum class status : std::uint16_t { foo = 0xAAAA, bar = 0x5555, foobar = 0xAA55 };

}	// namespace format_test

}	// namespace hamon_format_test

// The formatter for a user-defined type used to test the handle formatter.
template <class CharT>
struct hamon::formatter<hamon_format_test::format_test::status, CharT>
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
	auto format(hamon_format_test::format_test::status s, basic_format_context<Out, CharT>& ctx) const
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
			case hamon_format_test::format_test::status::foo:
				begin = names[0];
				break;
			case hamon_format_test::format_test::status::bar:
				begin = names[1];
				break;
			case hamon_format_test::format_test::status::foobar:
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

namespace format_test
{


#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

#define SV(Str)		hamon::basic_string_view<CharT>(HAMON_STATICALLY_WIDEN(CharT, Str), sizeof(Str) - 1)
#define STR(Str)	hamon::basic_string<CharT>(HAMON_STATICALLY_WIDEN(CharT, Str), sizeof(Str) - 1)

template <typename CharT>
/*HAMON_CXX20_CONSTEXPR*/ bool test_escape()
{
	VERIFY(SV("{") == hamon::format(SV("{{")));
	VERIFY(SV("}") == hamon::format(SV("}}")));
	VERIFY(SV("{:^}") == hamon::format(SV("{{:^}}")));
	VERIFY(SV("{: ^}") == hamon::format(SV("{{:{}^}}"), CharT(' ')));
	VERIFY(SV("{:{}^}") == hamon::format(SV("{{:{{}}^}}")));
	VERIFY(SV("{:{ }^}") == hamon::format(SV("{{:{{{}}}^}}"), CharT(' ')));

	VERIFY(SV("{") == hamon::format(std::locale(), SV("{{")));
	VERIFY(SV("}") == hamon::format(std::locale(), SV("}}")));
	VERIFY(SV("{:^}") == hamon::format(std::locale(), SV("{{:^}}")));
	VERIFY(SV("{: ^}") == hamon::format(std::locale(), SV("{{:{}^}}"), CharT(' ')));
	VERIFY(SV("{:{}^}") == hamon::format(std::locale(), SV("{{:{{}}^}}")));
	VERIFY(SV("{:{ }^}") == hamon::format(std::locale(), SV("{{:{{{}}}^}}"), CharT(' ')));

	return true;
}

template <typename CharT>
/*HAMON_CXX20_CONSTEXPR*/ bool test_arg_id()
{
	VERIFY(SV("hello false true") == hamon::format(SV("hello {0:} {1:}"), false, true));
	VERIFY(SV("hello true false") == hamon::format(SV("hello {1:} {0:}"), false, true));

	VERIFY(SV("hello false true") == hamon::format(std::locale(), SV("hello {0:} {1:}"), false, true));
	VERIFY(SV("hello true false") == hamon::format(std::locale(), SV("hello {1:} {0:}"), false, true));

	return true;
}

template <typename CharT>
/*HAMON_CXX20_CONSTEXPR*/ bool test_many_args()
{
	VERIFY(SV("1234567890\t1234567890") ==
		hamon::format(SV("{}{}{}{}{}{}{}{}{}{}\t{}{}{}{}{}{}{}{}{}{}"),
			1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0));

	VERIFY(SV("1234567890\t1234567890") ==
		hamon::format(std::locale(), SV("{}{}{}{}{}{}{}{}{}{}\t{}{}{}{}{}{}{}{}{}{}"),
			1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0));

	return true;
}

template <typename CharT>
/*HAMON_CXX20_CONSTEXPR*/ bool test_buffer_copy()
{
	// *** copy ***
	VERIFY(SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef") ==
		  hamon::format(SV("{}"), SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	VERIFY(SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef") ==
		  hamon::format(std::locale(), SV("{}"), SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	VERIFY(SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef") ==
		hamon::format(SV("{}"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	VERIFY(SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef") ==
		hamon::format(SV("{}"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	VERIFY(SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef") ==
		hamon::format(SV("{}"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	VERIFY(SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
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
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef") ==
		hamon::format(SV("{}"),
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

	VERIFY(SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"X") ==
		hamon::format(SV("{}X"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	VERIFY(SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"X") ==
		hamon::format(std::locale(), SV("{}X"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	VERIFY(SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"X") ==
		hamon::format(SV("{}X"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	VERIFY(SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"X") ==
		hamon::format(SV("{}X"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	VERIFY(SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"X") ==
		hamon::format(SV("{}X"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	VERIFY(SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
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
		"X") ==
		hamon::format(SV("{}X"),
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

	VERIFY(SV("X"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef") ==
		hamon::format(SV("X{}"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	VERIFY(SV("X"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef") ==
		hamon::format(std::locale(), SV("X{}"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	VERIFY(SV("X"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef") ==
		hamon::format(SV("X{}"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	VERIFY(SV("X"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef") ==
		hamon::format(SV("X{}"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	VERIFY(SV("X"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef") ==
		hamon::format(SV("X{}"),
			SV("0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef"
			   "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef")));

	VERIFY(SV("X"
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
		"0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef") ==
		hamon::format(SV("X{}"),
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

	return true;
}

template <typename CharT>
/*HAMON_CXX20_CONSTEXPR*/ bool test_buffer_fill()
{
	// *** fill ***
	VERIFY(SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||") ==
		hamon::format(SV("{:|<64}"), SV("")));

	VERIFY(SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||") ==
		hamon::format(std::locale(), SV("{:|<64}"), SV("")));

	VERIFY(SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||") ==
		hamon::format(SV("{:|<128}"), SV("")));

	VERIFY(SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||") ==
		hamon::format(SV("{:|<256}"), SV("")));

	VERIFY(SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||") ==
		hamon::format(SV("{:|<512}"), SV("")));

	VERIFY(SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
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
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||") ==
		hamon::format(SV("{:|<1024}"), SV("")));

	// *** fill + push_back ***

	VERIFY(SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"X") ==
		hamon::format(SV("{:|<64}X"), SV("")));

	VERIFY(SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"X") ==
		hamon::format(std::locale(), SV("{:|<64}X"), SV("")));

	VERIFY(SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"X") ==
		hamon::format(SV("{:|<128}X"), SV("")));

	VERIFY(SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"X") ==
		hamon::format(SV("{:|<256}X"), SV("")));

	VERIFY(SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"X") ==
		hamon::format(SV("{:|<512}X"), SV("")));

	VERIFY(SV("||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
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
		"X") ==
		hamon::format(SV("{:|<1024}X"), SV("")));

	// *** push_back + fill ***

	VERIFY(SV("X"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||") ==
		hamon::format(SV("X{:|<64}"), SV("")));

	VERIFY(SV("X"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||") ==
		hamon::format(std::locale(), SV("X{:|<64}"), SV("")));

	VERIFY(SV("X"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||") ==
		hamon::format(SV("X{:|<128}"), SV("")));

	VERIFY(SV("X"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||") ==
		hamon::format(SV("X{:|<256}"), SV("")));

	VERIFY(SV("X"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||") ==
		hamon::format(SV("X{:|<512}"), SV("")));

	VERIFY(SV("X"
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
		"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||") ==
		hamon::format(SV("X{:|<1024}"), SV("")));

	return true;
}

template <typename CharT>
/*HAMON_CXX20_CONSTEXPR*/ bool test_char()
{
	VERIFY(SV("hello 09azAZ!") ==
		  hamon::format(SV("hello {}{}{}{}{}{}{}"),
		  CharT('0'),
		  CharT('9'),
		  CharT('a'),
		  CharT('z'),
		  CharT('A'),
		  CharT('Z'),
		  CharT('!')));

	VERIFY(SV("hello 09azAZ!") ==
		  hamon::format(std::locale(), SV("hello {}{}{}{}{}{}{}"),
		  CharT('0'),
		  CharT('9'),
		  CharT('a'),
		  CharT('z'),
		  CharT('A'),
		  CharT('Z'),
		  CharT('!')));

	// ***** Char type *****
	// *** align-fill & width ***
	VERIFY(SV("answer is '*     '") == hamon::format(SV("answer is '{:6}'"), CharT('*')));
	VERIFY(SV("answer is '     *'") == hamon::format(SV("answer is '{:>6}'"), CharT('*')));
	VERIFY(SV("answer is '*     '") == hamon::format(SV("answer is '{:<6}'"), CharT('*')));
	VERIFY(SV("answer is '  *   '") == hamon::format(SV("answer is '{:^6}'"), CharT('*')));

	VERIFY(SV("answer is '*     '") == hamon::format(SV("answer is '{:6c}'"), CharT('*')));
	VERIFY(SV("answer is '     *'") == hamon::format(SV("answer is '{:>6c}'"), CharT('*')));
	VERIFY(SV("answer is '*     '") == hamon::format(SV("answer is '{:<6c}'"), CharT('*')));
	VERIFY(SV("answer is '  *   '") == hamon::format(SV("answer is '{:^6c}'"), CharT('*')));

	// The fill character ':' is allowed here (P0645) but not in ranges (P2286).
	VERIFY(SV("answer is ':::::*'") == hamon::format(SV("answer is '{::>6}'"), CharT('*')));
	VERIFY(SV("answer is '*:::::'") == hamon::format(SV("answer is '{::<6}'"), CharT('*')));
	VERIFY(SV("answer is '::*:::'") == hamon::format(SV("answer is '{::^6}'"), CharT('*')));

	VERIFY(SV("answer is '-----*'") == hamon::format(SV("answer is '{:->6c}'"), CharT('*')));
	VERIFY(SV("answer is '*-----'") == hamon::format(SV("answer is '{:-<6c}'"), CharT('*')));
	VERIFY(SV("answer is '--*---'") == hamon::format(SV("answer is '{:-^6c}'"), CharT('*')));

	//// *** Sign ***
	//check_exception("The format specifier for a character does not allow the sign option", SV("{:-}"), CharT('*'));
	//check_exception("The format specifier for a character does not allow the sign option", SV("{:+}"), CharT('*'));
	//check_exception("The format specifier for a character does not allow the sign option", SV("{: }"), CharT('*'));

	//check_exception("The format specifier for a character does not allow the sign option", SV("{:-c}"), CharT('*'));
	//check_exception("The format specifier for a character does not allow the sign option", SV("{:+c}"), CharT('*'));
	//check_exception("The format specifier for a character does not allow the sign option", SV("{: c}"), CharT('*'));

	//// *** alternate form ***
	//check_exception(
	//	"The format specifier for a character does not allow the alternate form option", SV("{:#}"), CharT('*'));
	//check_exception(
	//	"The format specifier for a character does not allow the alternate form option", SV("{:#c}"), CharT('*'));

	//// *** zero-padding ***
	//check_exception(
	//	"The format specifier for a character does not allow the zero-padding option", SV("{:0}"), CharT('*'));
	//check_exception(
	//	"The format specifier for a character does not allow the zero-padding option", SV("{:0c}"), CharT('*'));

	//// *** precision ***
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.}"), CharT('*'));
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.0}"), CharT('*'));
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.42}"), CharT('*'));

	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.c}"), CharT('*'));
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.0c}"), CharT('*'));
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.42c}"), CharT('*'));

	// *** locale-specific form ***
	// Note it has no effect but it's allowed.
	VERIFY(SV("answer is '*'") == hamon::format(SV("answer is '{:L}'"), '*'));
	VERIFY(SV("answer is '*'") == hamon::format(SV("answer is '{:Lc}'"), '*'));

//	// *** type ***
//#if TEST_STD_VER > 20
//	const char* valid_types = "bBcdoxX?";
//#else
//	const char* valid_types = "bBcdoxX";
//#endif
//	for (const auto& fmt : invalid_types<CharT>(valid_types))
//	{
//		check_exception("The type option contains an invalid value for a character formatting argument", fmt, CharT('*'));
//	}

	return true;
}

template <typename CharT>
/*HAMON_CXX20_CONSTEXPR*/ bool test_char_as_integer()
{
	// *** align-fill & width ***
	VERIFY(SV("answer is '42'") == hamon::format(SV("answer is '{:<1d}'"), CharT('*')));

	VERIFY(SV("answer is '42'")  == hamon::format(SV("answer is '{:<2d}'"), CharT('*')));
	VERIFY(SV("answer is '42 '") == hamon::format(SV("answer is '{:<3d}'"), CharT('*')));

	VERIFY(SV("answer is '     42'") == hamon::format(SV("answer is '{:7d}'"),  CharT('*')));
	VERIFY(SV("answer is '     42'") == hamon::format(SV("answer is '{:>7d}'"), CharT('*')));
	VERIFY(SV("answer is '42     '") == hamon::format(SV("answer is '{:<7d}'"), CharT('*')));
	VERIFY(SV("answer is '  42   '") == hamon::format(SV("answer is '{:^7d}'"), CharT('*')));

	// The fill character ':' is allowed here (P0645) but not in ranges (P2286).
	VERIFY(SV("answer is ':::::42'") == hamon::format(SV("answer is '{::>7d}'"), CharT('*')));
	VERIFY(SV("answer is '42:::::'") == hamon::format(SV("answer is '{::<7d}'"), CharT('*')));
	VERIFY(SV("answer is '::42:::'") == hamon::format(SV("answer is '{::^7d}'"), CharT('*')));

	// Test whether zero padding is ignored
	VERIFY(SV("answer is '     42'") == hamon::format(SV("answer is '{:>07d}'"), CharT('*')));
	VERIFY(SV("answer is '42     '") == hamon::format(SV("answer is '{:<07d}'"), CharT('*')));
	VERIFY(SV("answer is '  42   '") == hamon::format(SV("answer is '{:^07d}'"), CharT('*')));

	// *** Sign ***
	VERIFY(SV("answer is 42")  == hamon::format(SV("answer is {:d}"),  CharT('*')));
	VERIFY(SV("answer is 42")  == hamon::format(SV("answer is {:-d}"), CharT('*')));
	VERIFY(SV("answer is +42") == hamon::format(SV("answer is {:+d}"), CharT('*')));
	VERIFY(SV("answer is  42") == hamon::format(SV("answer is {: d}"), CharT('*')));

	// *** alternate form ***
	VERIFY(SV("answer is +42")       == hamon::format(SV("answer is {:+#d}"), CharT('*')));
	VERIFY(SV("answer is +101010")   == hamon::format(SV("answer is {:+b}"),  CharT('*')));
	VERIFY(SV("answer is +0b101010") == hamon::format(SV("answer is {:+#b}"), CharT('*')));
	VERIFY(SV("answer is +0B101010") == hamon::format(SV("answer is {:+#B}"), CharT('*')));
	VERIFY(SV("answer is +52")       == hamon::format(SV("answer is {:+o}"),  CharT('*')));
	VERIFY(SV("answer is +052")      == hamon::format(SV("answer is {:+#o}"), CharT('*')));
	VERIFY(SV("answer is +2a")       == hamon::format(SV("answer is {:+x}"),  CharT('*')));
	VERIFY(SV("answer is +0x2a")     == hamon::format(SV("answer is {:+#x}"), CharT('*')));
	VERIFY(SV("answer is +2A")       == hamon::format(SV("answer is {:+X}"),  CharT('*')));
	VERIFY(SV("answer is +0X2A")     == hamon::format(SV("answer is {:+#X}"), CharT('*')));

	// *** zero-padding & width ***
	VERIFY(SV("answer is +00000000042") == hamon::format(SV("answer is {:+#012d}"), CharT('*')));
	VERIFY(SV("answer is +00000101010") == hamon::format(SV("answer is {:+012b}"),  CharT('*')));
	VERIFY(SV("answer is +0b000101010") == hamon::format(SV("answer is {:+#012b}"), CharT('*')));
	VERIFY(SV("answer is +0B000101010") == hamon::format(SV("answer is {:+#012B}"), CharT('*')));
	VERIFY(SV("answer is +00000000052") == hamon::format(SV("answer is {:+012o}"),  CharT('*')));
	VERIFY(SV("answer is +00000000052") == hamon::format(SV("answer is {:+#012o}"), CharT('*')));
	VERIFY(SV("answer is +0000000002a") == hamon::format(SV("answer is {:+012x}"),  CharT('*')));
	VERIFY(SV("answer is +0x00000002a") == hamon::format(SV("answer is {:+#012x}"), CharT('*')));
	VERIFY(SV("answer is +0000000002A") == hamon::format(SV("answer is {:+012X}"),  CharT('*')));

	VERIFY(SV("answer is +0X00000002A") == hamon::format(SV("answer is {:+#012X}"), CharT('*')));

	//// *** precision ***
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.d}"), CharT('*'));
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.0d}"), CharT('*'));
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.42d}"), CharT('*'));

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp

//	// *** type ***
//#if TEST_STD_VER > 20
//	const char* valid_types = "bBcdoxX?";
//#else
//	const char* valid_types = "bBcdoxX";
//#endif
//	for (const auto& fmt : invalid_types<CharT>(valid_types))
//	{
//		check_exception("The type option contains an invalid value for a character formatting argument", fmt, CharT('*'));
//	}
	return true;
}

inline /*HAMON_CXX20_CONSTEXPR*/ bool test_char_to_wchar_t()
{
	using CharT = wchar_t;
	VERIFY(SV("hello 09azA") == hamon::format(SV("hello {}{}{}{}{}"), '0', '9', 'a', 'z', 'A'));
	VERIFY(SV("hello 09azA") == hamon::format(std::locale(), SV("hello {}{}{}{}{}"), '0', '9', 'a', 'z', 'A'));
	return true;
}

template <typename CharT, typename W, typename U>
/*HAMON_CXX20_CONSTEXPR*/ bool test_string_impl(const W& world, const U& universe)
{
	// *** Valid input tests ***
	// Unused argument is ignored. TODO FMT what does the Standard mandate?
	VERIFY(SV("hello world")              == hamon::format(SV("hello {}"),          world, universe));
	VERIFY(SV("hello world and universe") == hamon::format(SV("hello {} and {}"),   world, universe));
	VERIFY(SV("hello world")              == hamon::format(SV("hello {0}"),         world, universe));
	VERIFY(SV("hello universe")           == hamon::format(SV("hello {1}"),         world, universe));
	VERIFY(SV("hello universe and world") == hamon::format(SV("hello {1} and {0}"), world, universe));

	VERIFY(SV("hello world")    == hamon::format(SV("hello {:_>}"),  world));
	VERIFY(SV("hello world   ") == hamon::format(SV("hello {:8}"),   world));
	VERIFY(SV("hello    world") == hamon::format(SV("hello {:>8}"),  world));
	VERIFY(SV("hello ___world") == hamon::format(SV("hello {:_>8}"), world));
	VERIFY(SV("hello _world__") == hamon::format(SV("hello {:_^8}"), world));
	VERIFY(SV("hello world___") == hamon::format(SV("hello {:_<8}"), world));

	// The fill character ':' is allowed here (P0645) but not in ranges (P2286).
	VERIFY(SV("hello :::world") == hamon::format(SV("hello {::>8}"), world));
	VERIFY(SV("hello <<<world") == hamon::format(SV("hello {:<>8}"), world));
	VERIFY(SV("hello ^^^world") == hamon::format(SV("hello {:^>8}"), world));

	VERIFY(SV("hello $world") == hamon::format(SV("hello {:$>{}}"),   world, 6));
	VERIFY(SV("hello $world") == hamon::format(SV("hello {0:$>{1}}"), world, 6));
	VERIFY(SV("hello $world") == hamon::format(SV("hello {1:$>{0}}"), 6, world));

	VERIFY(SV("hello world") == hamon::format(SV("hello {:.5}"), world));
	VERIFY(SV("hello unive") == hamon::format(SV("hello {:.5}"), universe));

	VERIFY(SV("hello univer") == hamon::format(SV("hello {:.{}}"),   universe, 6));
	VERIFY(SV("hello univer") == hamon::format(SV("hello {0:.{1}}"), universe, 6));
	VERIFY(SV("hello univer") == hamon::format(SV("hello {1:.{0}}"), 6, universe));

	VERIFY(SV("hello %world%") == hamon::format(SV("hello {:%^7.7}"), world));
	VERIFY(SV("hello univers") == hamon::format(SV("hello {:%^7.7}"), universe));
	VERIFY(SV("hello %world%") == hamon::format(SV("hello {:%^{}.{}}"), world, 7, 7));
	VERIFY(SV("hello %world%") == hamon::format(SV("hello {0:%^{1}.{2}}"), world, 7, 7));
	VERIFY(SV("hello %world%") == hamon::format(SV("hello {0:%^{2}.{1}}"), world, 7, 7));
	VERIFY(SV("hello %world%") == hamon::format(SV("hello {1:%^{0}.{2}}"), 7, world, 7));

	VERIFY(SV("hello world")   == hamon::format(SV("hello {:_>s}"),   world));
	VERIFY(SV("hello $world")  == hamon::format(SV("hello {:$>{}s}"), world, 6));
	VERIFY(SV("hello world")   == hamon::format(SV("hello {:.5s}"),   world));
	VERIFY(SV("hello univer")  == hamon::format(SV("hello {:.{}s}"),  universe, 6));
	VERIFY(SV("hello %world%") == hamon::format(SV("hello {:%^7.7s}"), world));

	VERIFY(SV("hello #####uni") == hamon::format(SV("hello {:#>8.3s}"), universe));
	VERIFY(SV("hello ##uni###") == hamon::format(SV("hello {:#^8.3s}"), universe));
	VERIFY(SV("hello uni#####") == hamon::format(SV("hello {:#<8.3s}"), universe));

	//// *** sign ***
	//check_exception("The format specifier should consume the input or end with a '}'", SV("hello {:-}"), world);

	//// *** alternate form ***
	//check_exception("The format specifier should consume the input or end with a '}'", SV("hello {:#}"), world);

	//// *** zero-padding ***
	//check_exception("The width option should not have a leading zero", SV("hello {:0}"), world);

	// *** width ***
	// Width 0 allowed, but not useful for string arguments.
	VERIFY(SV("hello world") == hamon::format(SV("hello {:{}}"), world, 0));

//#ifdef _LIBCPP_VERSION
//	// This limit isn't specified in the Standard.
//	static_assert(std::__format::__number_max == 2'147'483'647, "Update the assert and the test.");
//	check_exception("The numeric value of the format specifier is too large", SV("{:2147483648}"), world);
//	check_exception("The numeric value of the format specifier is too large", SV("{:5000000000}"), world);
//	check_exception("The numeric value of the format specifier is too large", SV("{:10000000000}"), world);
//#endif
//
//	check_exception("An argument index may not have a negative value", SV("hello {:{}}"), world, -1);
//	check_exception("The value of the argument index exceeds its maximum value", SV("hello {:{}}"), world, unsigned(-1));
//	check_exception(
//		"The argument index value is too large for the number of arguments supplied", SV("hello {:{}}"), world);
//	check_exception(
//		"Replacement argument isn't a standard signed or unsigned integer type", SV("hello {:{}}"), world, universe);
//	check_exception("Using manual argument numbering in automatic argument numbering mode", SV("hello {:{0}}"), world, 1);
//	check_exception("Using automatic argument numbering in manual argument numbering mode", SV("hello {0:{}}"), world, 1);
//	// Arg-id may not have leading zeros.
//	check_exception("The argument index is invalid", SV("hello {0:{01}}"), world, 1);
//
//	// *** precision ***
//#ifdef _LIBCPP_VERSION
//  // This limit isn't specified in the Standard.
//	static_assert(std::__format::__number_max == 2'147'483'647, "Update the assert and the test.");
//	check_exception("The numeric value of the format specifier is too large", SV("{:.2147483648}"), world);
//	check_exception("The numeric value of the format specifier is too large", SV("{:.5000000000}"), world);
//	check_exception("The numeric value of the format specifier is too large", SV("{:.10000000000}"), world);
//#endif

	// Precision 0 allowed, but not useful for string arguments.
	VERIFY(SV("hello ") == hamon::format(SV("hello {:.{}}"), world, 0));
	// Precision may have leading zeros. Secondly tests the value is still base 10.
	VERIFY(SV("hello 0123456789") == hamon::format(SV("hello {:.000010}"), STR("0123456789abcdef")));
	//check_exception("An argument index may not have a negative value", SV("hello {:.{}}"), world, -1);
	//check_exception("The value of the argument index exceeds its maximum value", SV("hello {:.{}}"), world, ~0u);
	//check_exception(
	//	"The argument index value is too large for the number of arguments supplied", SV("hello {:.{}}"), world);
	//check_exception(
	//	"Replacement argument isn't a standard signed or unsigned integer type", SV("hello {:.{}}"), world, universe);
	//check_exception("Using manual argument numbering in automatic argument numbering mode", SV("hello {:.{0}}"), world,
	//				1);
	//check_exception("Using automatic argument numbering in manual argument numbering mode", SV("hello {0:.{}}"), world,
	//				1);
	//// Arg-id may not have leading zeros.
	//check_exception("The argument index is invalid", SV("hello {0:.{01}}"), world, 1);

	//// *** locale-specific form ***
	//check_exception("The format specifier should consume the input or end with a '}'", SV("hello {:L}"), world);

//	// *** type ***
//#if TEST_STD_VER > 20
//	const char* valid_types = "s?";
//#else
//	const char* valid_types = "s";
//#endif
//	for (const auto& fmt : invalid_types<CharT>(valid_types))
//	{
//		check_exception("The type option contains an invalid value for a string formatting argument", fmt, world);
//	}

	return true;
}

template <typename CharT>
/*HAMON_CXX20_CONSTEXPR*/ bool test_string_unicode()
{
#if _LIBCPP_HAS_UNICODE
	if constexpr (std::same_as<CharT, char>)
	{
		const char* c_string = "aßc";
		VERIFY(SV("*aßc*") == hamon::format(SV("{:*^5}"), c_string));
		VERIFY(SV("*aß*") == hamon::format(SV("{:*^4.2}"), c_string));

		VERIFY(SV("*aßc*") == hamon::format(SV("{:*^5}"), const_cast<char*>(c_string)));
		VERIFY(SV("*aß*") == hamon::format(SV("{:*^4.2}"), const_cast<char*>(c_string)));

		VERIFY(SV("*aßc*") == hamon::format(SV("{:*^5}"), "aßc"));
		VERIFY(SV("*aß*") == hamon::format(SV("{:*^4.2}"), "aßc"));

		VERIFY(SV("*aßc*") == hamon::format(SV("{:*^5}"), std::string("aßc")));
		VERIFY(SV("*aß*") == hamon::format(SV("{:*^4.2}"), std::string("aßc")));

		VERIFY(SV("*aßc*") == hamon::format(SV("{:*^5}"), std::string_view("aßc")));
		VERIFY(SV("*aß*") == hamon::format(SV("{:*^4.2}"), std::string_view("aßc")));
	}
	else
	{
		const wchar_t* c_string = L"aßc";
		VERIFY(SV("*aßc*") == hamon::format(SV("{:*^5}"), c_string));
		VERIFY(SV("*aß*") == hamon::format(SV("{:*^4.2}"), c_string));

		VERIFY(SV("*aßc*") == hamon::format(SV("{:*^5}"), const_cast<wchar_t*>(c_string)));
		VERIFY(SV("*aß*") == hamon::format(SV("{:*^4.2}"), const_cast<wchar_t*>(c_string)));

		VERIFY(SV("*aßc*") == hamon::format(SV("{:*^5}"), L"aßc"));
		VERIFY(SV("*aß*") == hamon::format(SV("{:*^4.2}"), L"aßc"));

		VERIFY(SV("*aßc*") == hamon::format(SV("{:*^5}"), std::wstring(L"aßc")));
		VERIFY(SV("*aß*") == hamon::format(SV("{:*^4.2}"), std::wstring(L"aßc")));

		VERIFY(SV("*aßc*") == hamon::format(SV("{:*^5}"), std::wstring_view(L"aßc")));
		VERIFY(SV("*aß*") == hamon::format(SV("{:*^4.2}"), std::wstring_view(L"aßc")));
	}

	// ß requires one column
	VERIFY(SV("aßc") == hamon::format(SV("{}"), STR("aßc")));

	VERIFY(SV("aßc") == hamon::format(SV("{:.3}"), STR("aßc")));
	VERIFY(SV("aß") == hamon::format(SV("{:.2}"), STR("aßc")));
	VERIFY(SV("a") == hamon::format(SV("{:.1}"), STR("aßc")));

	VERIFY(SV("aßc") == hamon::format(SV("{:3.3}"), STR("aßc")));
	VERIFY(SV("aß") == hamon::format(SV("{:2.2}"), STR("aßc")));
	VERIFY(SV("a") == hamon::format(SV("{:1.1}"), STR("aßc")));

	VERIFY(SV("aßc---") == hamon::format(SV("{:-<6}"), STR("aßc")));
	VERIFY(SV("-aßc--") == hamon::format(SV("{:-^6}"), STR("aßc")));
	VERIFY(SV("---aßc") == hamon::format(SV("{:->6}"), STR("aßc")));

	// \u1000 requires two columns
	VERIFY(SV("a\u1110c") == hamon::format(SV("{}"), STR("a\u1110c")));

	VERIFY(SV("a\u1100c") == hamon::format(SV("{:.4}"), STR("a\u1100c")));
	VERIFY(SV("a\u1100") == hamon::format(SV("{:.3}"), STR("a\u1100c")));
	VERIFY(SV("a") == hamon::format(SV("{:.2}"), STR("a\u1100c")));
	VERIFY(SV("a") == hamon::format(SV("{:.1}"), STR("a\u1100c")));

	VERIFY(SV("a\u1100c") == hamon::format(SV("{:-<4.4}"), STR("a\u1100c")));
	VERIFY(SV("a\u1100") == hamon::format(SV("{:-<3.3}"), STR("a\u1100c")));
	VERIFY(SV("a-") == hamon::format(SV("{:-<2.2}"), STR("a\u1100c")));
	VERIFY(SV("a") == hamon::format(SV("{:-<1.1}"), STR("a\u1100c")));

	VERIFY(SV("a\u1110c---") == hamon::format(SV("{:-<7}"), STR("a\u1110c")));
	VERIFY(SV("-a\u1110c--") == hamon::format(SV("{:-^7}"), STR("a\u1110c")));
	VERIFY(SV("---a\u1110c") == hamon::format(SV("{:->7}"), STR("a\u1110c")));

	// Examples used in P1868R2
	VERIFY(SV("*\u0041*") == hamon::format(SV("{:*^3}"), STR("\u0041"))); // { LATIN CAPITAL LETTER A }
	VERIFY(SV("*\u00c1*") == hamon::format(SV("{:*^3}"), STR("\u00c1"))); // { LATIN CAPITAL LETTER A WITH ACUTE }
	VERIFY(SV("*\u0041\u0301*") == hamon::format(SV("{:*^3}"), STR("\u0041\u0301")));	// { LATIN CAPITAL LETTER A } { COMBINING ACUTE ACCENT }
	VERIFY(SV("*\u0132*") == hamon::format(SV("{:*^3}"), STR("\u0132"))); // { LATIN CAPITAL LIGATURE IJ }
	VERIFY(SV("*\u0394*") == hamon::format(SV("{:*^3}"), STR("\u0394"))); // { GREEK CAPITAL LETTER DELTA }

	VERIFY(SV("*\u0429*") == hamon::format(SV("{:*^3}"), STR("\u0429"))); // { CYRILLIC CAPITAL LETTER SHCHA }
	VERIFY(SV("*\u05d0*") == hamon::format(SV("{:*^3}"), STR("\u05d0"))); // { HEBREW LETTER ALEF }
	VERIFY(SV("*\u0634*") == hamon::format(SV("{:*^3}"), STR("\u0634"))); // { ARABIC LETTER SHEEN }
	VERIFY(SV("*\u3009*") == hamon::format(SV("{:*^4}"), STR("\u3009"))); // { RIGHT-POINTING ANGLE BRACKET }
	VERIFY(SV("*\u754c*") == hamon::format(SV("{:*^4}"), STR("\u754c"))); // { CJK Unified Ideograph-754C }
	VERIFY(SV("*\U0001f921*") == hamon::format(SV("{:*^4}"), STR("\U0001f921"))); // { UNICORN FACE }
	VERIFY(SV("*\U0001f468\u200d\U0001F469\u200d\U0001F467\u200d\U0001F466*") == hamon::format(SV("{:*^4}"),
		STR("\U0001f468\u200d\U0001F469\u200d\U0001F467\u200d\U0001F466"))); // { Family: Man, Woman, Girl, Boy }
#endif
	return true;
}

template <typename CharT>
/*HAMON_CXX20_CONSTEXPR*/ bool test_string()
{
	// *** Test string format argument ***
	{
		CharT buffer[] = {CharT('0'), CharT('9'), CharT('a'), CharT('z'), CharT('A'), CharT('Z'), CharT('!'), 0};
		CharT* data = buffer;
		VERIFY(SV("hello 09azAZ!") == hamon::format(SV("hello {}"), data));
		VERIFY(SV("hello 09azAZ!") == hamon::format(std::locale(), SV("hello {}"), data));
	}
	{
		CharT buffer[] = {CharT('0'), CharT('9'), CharT('a'), CharT('z'), CharT('A'), CharT('Z'), CharT('!'), 0};
		const CharT* data = buffer;
		VERIFY(SV("hello 09azAZ!") == hamon::format(SV("hello {}"), data));
		VERIFY(SV("hello 09azAZ!") == hamon::format(std::locale(), SV("hello {}"), data));
	}
	{
		// https://github.com/llvm/llvm-project/issues/115935
		// Contents after the embedded null character are discarded.
		CharT buffer[] = {CharT('a'), CharT('b'), CharT('c'), 0, CharT('d'), CharT('e'), CharT('f'), 0};
		VERIFY(SV("hello abc") == hamon::format(SV("hello {}"), buffer));
		VERIFY(SV("hello abc") == hamon::format(std::locale(), SV("hello {}"), buffer));
		// Even when the last element of the array is not null character.
		CharT buffer2[] = {CharT('a'), CharT('b'), CharT('c'), 0, CharT('d'), CharT('e'), CharT('f')};
		VERIFY(SV("hello abc") == hamon::format(SV("hello {}"), buffer2));
		VERIFY(SV("hello abc") == hamon::format(std::locale(), SV("hello {}"), buffer2));
	}
	{
		hamon::basic_string<CharT> data = STR("world");
		VERIFY(SV("hello world") == hamon::format(SV("hello {}"), data));
		VERIFY(SV("hello world") == hamon::format(std::locale(), SV("hello {}"), data));
	}
	{
		hamon::basic_string<CharT> buffer = STR("world");
		hamon::basic_string_view<CharT> data = buffer;
		VERIFY(SV("hello world") == hamon::format(SV("hello {}"), data));
		VERIFY(SV("hello world") == hamon::format(std::locale(), SV("hello {}"), data));
	}

	CharT world[] = {CharT('w'), CharT('o'), CharT('r'), CharT('l'), CharT('d'), 0};
	CharT universe[] = {CharT('u'), CharT('n'), CharT('i'), CharT('v'), CharT('e'), CharT('r'), CharT('s'), CharT('e'), 0};

	VERIFY(test_string_impl<CharT>(world, universe));
	VERIFY(test_string_impl<CharT>(static_cast<CharT*>(world), static_cast<CharT*>(universe)));
	VERIFY(test_string_impl<CharT>(static_cast<CharT const*>(world), static_cast<CharT const*>(universe)));
	VERIFY(test_string_impl<CharT>(hamon::basic_string<CharT>(world), hamon::basic_string<CharT>(universe)));
	VERIFY(test_string_impl<CharT>(hamon::basic_string_view<CharT>(world), hamon::basic_string_view<CharT>(universe)));

	VERIFY(test_string_unicode<CharT>());

	return true;
}

template <typename CharT>
/*HAMON_CXX20_CONSTEXPR*/ bool test_bool()
{
	// *** Test Boolean format argument ***
	VERIFY(SV("hello false true") == hamon::format(SV("hello {} {}"), false, true));
	VERIFY(SV("hello false true") == hamon::format(std::locale(), SV("hello {} {}"), false, true));

	// *** align-fill & width ***
	VERIFY(SV("answer is 'true   '") == hamon::format(SV("answer is '{:7}'"), true));
	VERIFY(SV("answer is '   true'") == hamon::format(SV("answer is '{:>7}'"), true));
	VERIFY(SV("answer is 'true   '") == hamon::format(SV("answer is '{:<7}'"), true));
	VERIFY(SV("answer is ' true  '") == hamon::format(SV("answer is '{:^7}'"), true));

	VERIFY(SV("answer is 'false   '") == hamon::format(SV("answer is '{:8s}'"), false));
	VERIFY(SV("answer is '   false'") == hamon::format(SV("answer is '{:>8s}'"), false));
	VERIFY(SV("answer is 'false   '") == hamon::format(SV("answer is '{:<8s}'"), false));
	VERIFY(SV("answer is ' false  '") == hamon::format(SV("answer is '{:^8s}'"), false));

	// The fill character ':' is allowed here (P0645) but not in ranges (P2286).
	VERIFY(SV("answer is ':::true'") == hamon::format(SV("answer is '{::>7}'"), true));
	VERIFY(SV("answer is 'true:::'") == hamon::format(SV("answer is '{::<7}'"), true));
	VERIFY(SV("answer is ':true::'") == hamon::format(SV("answer is '{::^7}'"), true));

	VERIFY(SV("answer is '---false'") == hamon::format(SV("answer is '{:->8s}'"), false));
	VERIFY(SV("answer is 'false---'") == hamon::format(SV("answer is '{:-<8s}'"), false));
	VERIFY(SV("answer is '-false--'") == hamon::format(SV("answer is '{:-^8s}'"), false));

	//// *** Sign ***
	//check_exception("The format specifier for a bool does not allow the sign option", SV("{:-}"), true);
	//check_exception("The format specifier for a bool does not allow the sign option", SV("{:+}"), true);
	//check_exception("The format specifier for a bool does not allow the sign option", SV("{: }"), true);

	//check_exception("The format specifier for a bool does not allow the sign option", SV("{:-s}"), true);
	//check_exception("The format specifier for a bool does not allow the sign option", SV("{:+s}"), true);
	//check_exception("The format specifier for a bool does not allow the sign option", SV("{: s}"), true);

	//// *** alternate form ***
	//check_exception("The format specifier for a bool does not allow the alternate form option", SV("{:#}"), true);
	//check_exception("The format specifier for a bool does not allow the alternate form option", SV("{:#s}"), true);

	//// *** zero-padding ***
	//check_exception("The format specifier for a bool does not allow the zero-padding option", SV("{:0}"), true);
	//check_exception("The format specifier for a bool does not allow the zero-padding option", SV("{:0s}"), true);

	//// *** precision ***
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.}"), true);
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.0}"), true);
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.42}"), true);

	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.s}"), true);
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.0s}"), true);
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.42s}"), true);

	//// *** locale-specific form ***
	//// See locale-specific_form.pass.cpp

	//// *** type ***
	//for (const auto& fmt : invalid_types<CharT>("bBdosxX"))
	//{
	//	check_exception("The type option contains an invalid value for a bool formatting argument", fmt, true);
	//}

	return true;
}

template <typename CharT>
/*HAMON_CXX20_CONSTEXPR*/ bool test_bool_as_integer()
{
	// *** align-fill & width ***
	VERIFY(SV("answer is '1'")  == hamon::format(SV("answer is '{:<1d}'"), true));
	VERIFY(SV("answer is '1 '") == hamon::format(SV("answer is '{:<2d}'"), true));
	VERIFY(SV("answer is '0 '") == hamon::format(SV("answer is '{:<2d}'"), false));

	VERIFY(SV("answer is '     1'") == hamon::format(SV("answer is '{:6d}'"),  true));
	VERIFY(SV("answer is '     1'") == hamon::format(SV("answer is '{:>6d}'"), true));
	VERIFY(SV("answer is '1     '") == hamon::format(SV("answer is '{:<6d}'"), true));
	VERIFY(SV("answer is '  1   '") == hamon::format(SV("answer is '{:^6d}'"), true));

	// The fill character ':' is allowed here (P0645) but not in ranges (P2286).
	VERIFY(SV("answer is ':::::0'") == hamon::format(SV("answer is '{::>6d}'"), false));
	VERIFY(SV("answer is '0:::::'") == hamon::format(SV("answer is '{::<6d}'"), false));
	VERIFY(SV("answer is '::0:::'") == hamon::format(SV("answer is '{::^6d}'"), false));

	// Test whether zero padding is ignored
	VERIFY(SV("answer is '     1'") == hamon::format(SV("answer is '{:>06d}'"), true));
	VERIFY(SV("answer is '1     '") == hamon::format(SV("answer is '{:<06d}'"), true));
	VERIFY(SV("answer is '  1   '") == hamon::format(SV("answer is '{:^06d}'"), true));

	// *** Sign ***
	VERIFY(SV("answer is 1")  == hamon::format(SV("answer is {:d}"),  true));
	VERIFY(SV("answer is 0")  == hamon::format(SV("answer is {:-d}"), false));
	VERIFY(SV("answer is +1") == hamon::format(SV("answer is {:+d}"), true));
	VERIFY(SV("answer is  0") == hamon::format(SV("answer is {: d}"), false));

	// *** alternate form ***
	VERIFY(SV("answer is +1")   == hamon::format(SV("answer is {:+#d}"), true));
	VERIFY(SV("answer is +1")   == hamon::format(SV("answer is {:+b}"),  true));
	VERIFY(SV("answer is +0b1") == hamon::format(SV("answer is {:+#b}"), true));
	VERIFY(SV("answer is +0B1") == hamon::format(SV("answer is {:+#B}"), true));
	VERIFY(SV("answer is +1")   == hamon::format(SV("answer is {:+o}"),  true));
	VERIFY(SV("answer is +01")  == hamon::format(SV("answer is {:+#o}"), true));
	VERIFY(SV("answer is +1")   == hamon::format(SV("answer is {:+x}"),  true));
	VERIFY(SV("answer is +0x1") == hamon::format(SV("answer is {:+#x}"), true));
	VERIFY(SV("answer is +1")   == hamon::format(SV("answer is {:+X}"),  true));
	VERIFY(SV("answer is +0X1") == hamon::format(SV("answer is {:+#X}"), true));

	VERIFY(SV("answer is 0")   == hamon::format(SV("answer is {:#d}"), false));
	VERIFY(SV("answer is 0")   == hamon::format(SV("answer is {:b}"),  false));
	VERIFY(SV("answer is 0b0") == hamon::format(SV("answer is {:#b}"), false));
	VERIFY(SV("answer is 0B0") == hamon::format(SV("answer is {:#B}"), false));
	VERIFY(SV("answer is 0")   == hamon::format(SV("answer is {:o}"),  false));
	VERIFY(SV("answer is 0")   == hamon::format(SV("answer is {:#o}"), false));
	VERIFY(SV("answer is 0")   == hamon::format(SV("answer is {:x}"),  false));
	VERIFY(SV("answer is 0x0") == hamon::format(SV("answer is {:#x}"), false));
	VERIFY(SV("answer is 0")   == hamon::format(SV("answer is {:X}"),  false));
	VERIFY(SV("answer is 0X0") == hamon::format(SV("answer is {:#X}"), false));

	// *** zero-padding & width ***
	VERIFY(SV("answer is +00000000001") == hamon::format(SV("answer is {:+#012d}"), true));
	VERIFY(SV("answer is +00000000001") == hamon::format(SV("answer is {:+012b}"),  true));
	VERIFY(SV("answer is +0b000000001") == hamon::format(SV("answer is {:+#012b}"), true));
	VERIFY(SV("answer is +0B000000001") == hamon::format(SV("answer is {:+#012B}"), true));
	VERIFY(SV("answer is +00000000001") == hamon::format(SV("answer is {:+012o}"),  true));
	VERIFY(SV("answer is +00000000001") == hamon::format(SV("answer is {:+#012o}"), true));
	VERIFY(SV("answer is +00000000001") == hamon::format(SV("answer is {:+012x}"),  true));
	VERIFY(SV("answer is +0x000000001") == hamon::format(SV("answer is {:+#012x}"), true));
	VERIFY(SV("answer is +00000000001") == hamon::format(SV("answer is {:+012X}"),  true));
	VERIFY(SV("answer is +0X000000001") == hamon::format(SV("answer is {:+#012X}"), true));

	VERIFY(SV("answer is 000000000000") == hamon::format(SV("answer is {:#012d}"), false));
	VERIFY(SV("answer is 000000000000") == hamon::format(SV("answer is {:012b}"),  false));
	VERIFY(SV("answer is 0b0000000000") == hamon::format(SV("answer is {:#012b}"), false));
	VERIFY(SV("answer is 0B0000000000") == hamon::format(SV("answer is {:#012B}"), false));
	VERIFY(SV("answer is 000000000000") == hamon::format(SV("answer is {:012o}"),  false));
	VERIFY(SV("answer is 000000000000") == hamon::format(SV("answer is {:#012o}"), false));
	VERIFY(SV("answer is 000000000000") == hamon::format(SV("answer is {:012x}"),  false));
	VERIFY(SV("answer is 0x0000000000") == hamon::format(SV("answer is {:#012x}"), false));
	VERIFY(SV("answer is 000000000000") == hamon::format(SV("answer is {:012X}"),  false));
	VERIFY(SV("answer is 0X0000000000") == hamon::format(SV("answer is {:#012X}"), false));

	//// *** precision ***
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.}"), true);
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.0}"), true);
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.42}"), true);

	//// *** locale-specific form ***
	//// See locale-specific_form.pass.cpp

	//// *** type ***
	//for (const auto& fmt : invalid_types<CharT>("bBcdosxX"))
	//{
	//	check_exception("The type option contains an invalid value for a bool formatting argument", fmt, true);
	//}

	return true;
}

template <typename CharT, typename I>
/*HAMON_CXX20_CONSTEXPR*/ bool test_integer_as_integer()
{
	// *** align-fill & width ***
	VERIFY(SV("answer is '42'")  == hamon::format(SV("answer is '{:<1}'"), I(42)));
	VERIFY(SV("answer is '42'")  == hamon::format(SV("answer is '{:<2}'"), I(42)));
	VERIFY(SV("answer is '42 '") == hamon::format(SV("answer is '{:<3}'"), I(42)));

	VERIFY(SV("answer is '     42'") == hamon::format(SV("answer is '{:7}'"),  I(42)));
	VERIFY(SV("answer is '     42'") == hamon::format(SV("answer is '{:>7}'"), I(42)));
	VERIFY(SV("answer is '42     '") == hamon::format(SV("answer is '{:<7}'"), I(42)));
	VERIFY(SV("answer is '  42   '") == hamon::format(SV("answer is '{:^7}'"), I(42)));

	// The fill character ':' is allowed here (P0645) but not in ranges (P2286).
	VERIFY(SV("answer is ':::::42'") == hamon::format(SV("answer is '{::>7}'"), I(42)));
	VERIFY(SV("answer is '42:::::'") == hamon::format(SV("answer is '{::<7}'"), I(42)));
	VERIFY(SV("answer is '::42:::'") == hamon::format(SV("answer is '{::^7}'"), I(42)));

	// Test whether zero padding is ignored
	VERIFY(SV("answer is '     42'") == hamon::format(SV("answer is '{:>07}'"), I(42)));
	VERIFY(SV("answer is '42     '") == hamon::format(SV("answer is '{:<07}'"), I(42)));
	VERIFY(SV("answer is '  42   '") == hamon::format(SV("answer is '{:^07}'"), I(42)));

	// *** Sign ***
	if constexpr (std::signed_integral<I>)
	{
		VERIFY(SV("answer is -42") == hamon::format(SV("answer is {}"), I(-42)));
	}
	VERIFY(SV("answer is 0")  == hamon::format(SV("answer is {}"), I(0)));
	VERIFY(SV("answer is 42") == hamon::format(SV("answer is {}"), I(42)));

	if constexpr (std::signed_integral<I>)
	{
		VERIFY(SV("answer is -42") == hamon::format(SV("answer is {:-}"), I(-42)));
	}
	VERIFY(SV("answer is 0")  == hamon::format(SV("answer is {:-}"), I(0)));
	VERIFY(SV("answer is 42") == hamon::format(SV("answer is {:-}"), I(42)));

	if constexpr (std::signed_integral<I>)
	{
		VERIFY(SV("answer is -42") == hamon::format(SV("answer is {:+}"), I(-42)));
	}
	VERIFY(SV("answer is +0")  == hamon::format(SV("answer is {:+}"), I(0)));
	VERIFY(SV("answer is +42") == hamon::format(SV("answer is {:+}"), I(42)));

	if constexpr (std::signed_integral<I>)
	{
		VERIFY(SV("answer is -42") == hamon::format(SV("answer is {: }"), I(-42)));
	}

	VERIFY(SV("answer is  0")  == hamon::format(SV("answer is {: }"), I(0)));
	VERIFY(SV("answer is  42") == hamon::format(SV("answer is {: }"), I(42)));

	// *** alternate form ***
	if constexpr (std::signed_integral<I>)
	{
		VERIFY(SV("answer is -42")       == hamon::format(SV("answer is {:#}"),  I(-42)));
		VERIFY(SV("answer is -42")       == hamon::format(SV("answer is {:#d}"), I(-42)));
		VERIFY(SV("answer is -101010")   == hamon::format(SV("answer is {:b}"),  I(-42)));
		VERIFY(SV("answer is -0b101010") == hamon::format(SV("answer is {:#b}"), I(-42)));
		VERIFY(SV("answer is -0B101010") == hamon::format(SV("answer is {:#B}"), I(-42)));
		VERIFY(SV("answer is -52")       == hamon::format(SV("answer is {:o}"),  I(-42)));
		VERIFY(SV("answer is -052")      == hamon::format(SV("answer is {:#o}"), I(-42)));
		VERIFY(SV("answer is -2a")       == hamon::format(SV("answer is {:x}"),  I(-42)));
		VERIFY(SV("answer is -0x2a")     == hamon::format(SV("answer is {:#x}"), I(-42)));
		VERIFY(SV("answer is -2A")       == hamon::format(SV("answer is {:X}"),  I(-42)));
		VERIFY(SV("answer is -0X2A")     == hamon::format(SV("answer is {:#X}"), I(-42)));
	}
	VERIFY(SV("answer is 0")   == hamon::format(SV("answer is {:#}"),  I(0)));
	VERIFY(SV("answer is 0")   == hamon::format(SV("answer is {:#d}"), I(0)));
	VERIFY(SV("answer is 0")   == hamon::format(SV("answer is {:b}"),  I(0)));
	VERIFY(SV("answer is 0b0") == hamon::format(SV("answer is {:#b}"), I(0)));
	VERIFY(SV("answer is 0B0") == hamon::format(SV("answer is {:#B}"), I(0)));
	VERIFY(SV("answer is 0")   == hamon::format(SV("answer is {:o}"),  I(0)));
	VERIFY(SV("answer is 0")   == hamon::format(SV("answer is {:#o}"), I(0)));
	VERIFY(SV("answer is 0")   == hamon::format(SV("answer is {:x}"),  I(0)));
	VERIFY(SV("answer is 0x0") == hamon::format(SV("answer is {:#x}"), I(0)));
	VERIFY(SV("answer is 0")   == hamon::format(SV("answer is {:X}"),  I(0)));
	VERIFY(SV("answer is 0X0") == hamon::format(SV("answer is {:#X}"), I(0)));

	VERIFY(SV("answer is +42")       == hamon::format(SV("answer is {:+#}"),  I(42)));
	VERIFY(SV("answer is +42")       == hamon::format(SV("answer is {:+#d}"), I(42)));
	VERIFY(SV("answer is +101010")   == hamon::format(SV("answer is {:+b}"),  I(42)));
	VERIFY(SV("answer is +0b101010") == hamon::format(SV("answer is {:+#b}"), I(42)));
	VERIFY(SV("answer is +0B101010") == hamon::format(SV("answer is {:+#B}"), I(42)));
	VERIFY(SV("answer is +52")       == hamon::format(SV("answer is {:+o}"),  I(42)));
	VERIFY(SV("answer is +052")      == hamon::format(SV("answer is {:+#o}"), I(42)));
	VERIFY(SV("answer is +2a")       == hamon::format(SV("answer is {:+x}"),  I(42)));
	VERIFY(SV("answer is +0x2a")     == hamon::format(SV("answer is {:+#x}"), I(42)));
	VERIFY(SV("answer is +2A")       == hamon::format(SV("answer is {:+X}"),  I(42)));
	VERIFY(SV("answer is +0X2A")     == hamon::format(SV("answer is {:+#X}"), I(42)));

	// *** zero-padding & width ***
	if constexpr (std::signed_integral<I>)
	{
		VERIFY(SV("answer is -00000000042") == hamon::format(SV("answer is {:#012}"),  I(-42)));
		VERIFY(SV("answer is -00000000042") == hamon::format(SV("answer is {:#012d}"), I(-42)));
		VERIFY(SV("answer is -00000101010") == hamon::format(SV("answer is {:012b}"),  I(-42)));
		VERIFY(SV("answer is -0b000101010") == hamon::format(SV("answer is {:#012b}"), I(-42)));
		VERIFY(SV("answer is -0B000101010") == hamon::format(SV("answer is {:#012B}"), I(-42)));
		VERIFY(SV("answer is -00000000052") == hamon::format(SV("answer is {:012o}"),  I(-42)));
		VERIFY(SV("answer is -00000000052") == hamon::format(SV("answer is {:#012o}"), I(-42)));
		VERIFY(SV("answer is -0000000002a") == hamon::format(SV("answer is {:012x}"),  I(-42)));
		VERIFY(SV("answer is -0x00000002a") == hamon::format(SV("answer is {:#012x}"), I(-42)));
		VERIFY(SV("answer is -0000000002A") == hamon::format(SV("answer is {:012X}"),  I(-42)));
		VERIFY(SV("answer is -0X00000002A") == hamon::format(SV("answer is {:#012X}"), I(-42)));
	}

	VERIFY(SV("answer is 000000000000") == hamon::format(SV("answer is {:#012}"),  I(0)));
	VERIFY(SV("answer is 000000000000") == hamon::format(SV("answer is {:#012d}"), I(0)));
	VERIFY(SV("answer is 000000000000") == hamon::format(SV("answer is {:012b}"),  I(0)));
	VERIFY(SV("answer is 0b0000000000") == hamon::format(SV("answer is {:#012b}"), I(0)));
	VERIFY(SV("answer is 0B0000000000") == hamon::format(SV("answer is {:#012B}"), I(0)));
	VERIFY(SV("answer is 000000000000") == hamon::format(SV("answer is {:012o}"),  I(0)));
	VERIFY(SV("answer is 000000000000") == hamon::format(SV("answer is {:#012o}"), I(0)));
	VERIFY(SV("answer is 000000000000") == hamon::format(SV("answer is {:012x}"),  I(0)));
	VERIFY(SV("answer is 0x0000000000") == hamon::format(SV("answer is {:#012x}"), I(0)));
	VERIFY(SV("answer is 000000000000") == hamon::format(SV("answer is {:012X}"),  I(0)));
	VERIFY(SV("answer is 0X0000000000") == hamon::format(SV("answer is {:#012X}"), I(0)));

	VERIFY(SV("answer is +00000000042") == hamon::format(SV("answer is {:+#012}"),  I(42)));
	VERIFY(SV("answer is +00000000042") == hamon::format(SV("answer is {:+#012d}"), I(42)));
	VERIFY(SV("answer is +00000101010") == hamon::format(SV("answer is {:+012b}"),  I(42)));
	VERIFY(SV("answer is +0b000101010") == hamon::format(SV("answer is {:+#012b}"), I(42)));
	VERIFY(SV("answer is +0B000101010") == hamon::format(SV("answer is {:+#012B}"), I(42)));
	VERIFY(SV("answer is +00000000052") == hamon::format(SV("answer is {:+012o}"),  I(42)));
	VERIFY(SV("answer is +00000000052") == hamon::format(SV("answer is {:+#012o}"), I(42)));
	VERIFY(SV("answer is +0000000002a") == hamon::format(SV("answer is {:+012x}"),  I(42)));
	VERIFY(SV("answer is +0x00000002a") == hamon::format(SV("answer is {:+#012x}"), I(42)));
	VERIFY(SV("answer is +0000000002A") == hamon::format(SV("answer is {:+012X}"),  I(42)));
	VERIFY(SV("answer is +0X00000002A") == hamon::format(SV("answer is {:+#012X}"), I(42)));

	//// *** precision ***
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.}"), I(0));
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.0}"), I(0));
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.42}"), I(0));

	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.{}}"), I(0));
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.{}}"), I(0), true);
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.{}}"), I(0), 1.0);

	//// *** locale-specific form ***
	//// See locale-specific_form.pass.cpp

	//// *** type ***
	//for (const auto& fmt : invalid_types<CharT>("bBcdoxX"))
	//{
	//	check_exception("The type option contains an invalid value for an integer formatting argument", fmt, I(0));
	//}

	return true;
}

template <typename CharT, typename I>
/*HAMON_CXX20_CONSTEXPR*/ bool test_integer_as_char()
{
	// *** align-fill & width ***
	VERIFY(SV("answer is '*     '") == hamon::format(SV("answer is '{:6c}'"),  I(42)));
	VERIFY(SV("answer is '     *'") == hamon::format(SV("answer is '{:>6c}'"), I(42)));
	VERIFY(SV("answer is '*     '") == hamon::format(SV("answer is '{:<6c}'"), I(42)));
	VERIFY(SV("answer is '  *   '") == hamon::format(SV("answer is '{:^6c}'"), I(42)));

	// The fill character ':' is allowed here (P0645) but not in ranges (P2286).
	VERIFY(SV("answer is ':::::*'") == hamon::format(SV("answer is '{::>6c}'"), I(42)));
	VERIFY(SV("answer is '*:::::'") == hamon::format(SV("answer is '{::<6c}'"), I(42)));
	VERIFY(SV("answer is '::*:::'") == hamon::format(SV("answer is '{::^6c}'"), I(42)));

	// *** Sign ***
	VERIFY(SV("answer is *") == hamon::format(SV("answer is {:c}"), I(42)));
	//check_exception("The format specifier for an integer does not allow the sign option", SV("answer is {:-c}"), I(42));
	//check_exception("The format specifier for an integer does not allow the sign option", SV("answer is {:+c}"), I(42));
	//check_exception("The format specifier for an integer does not allow the sign option", SV("answer is {: c}"), I(42));

	//// *** alternate form ***
	//check_exception(
	//	"The format specifier for an integer does not allow the alternate form option", SV("answer is {:#c}"), I(42));

	//// *** zero-padding & width ***
	//check_exception(
	//	"The format specifier for an integer does not allow the zero-padding option", SV("answer is {:01c}"), I(42));

	//// *** precision ***
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.c}"), I(0));
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.0c}"), I(0));
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.42c}"), I(0));

	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.{}c}"), I(0));
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.{}c}"), I(0), true);
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.{}c}"), I(0), 1.0);

	// *** locale-specific form ***
	// Note it has no effect but it's allowed.
	VERIFY(SV("answer is '*'") == hamon::format(SV("answer is '{:Lc}'"), I(42)));

	//// *** type ***
	//for (const auto& fmt : invalid_types<CharT>("bBcdoxX"))
	//{
	//	check_exception("The type option contains an invalid value for an integer formatting argument", fmt, I(42));
	//}

	//// *** Validate range ***
	//// The code has some duplications to keep the if statement readable.
	//if constexpr (std::signed_integral<CharT>)
	//{
	//	if constexpr (std::signed_integral<I> && sizeof(I) > sizeof(CharT))
	//	{
	//		check_exception("Integral value outside the range of the char type", SV("{:c}"), hamon::numeric_limits<I>::min());
	//		check_exception("Integral value outside the range of the char type", SV("{:c}"), hamon::numeric_limits<I>::max());
	//	}
	//	else if constexpr (std::unsigned_integral<I> && sizeof(I) >= sizeof(CharT))
	//	{
	//		check_exception("Integral value outside the range of the char type", SV("{:c}"), hamon::numeric_limits<I>::max());
	//	}
	//}
	//else if constexpr (sizeof(I) > sizeof(CharT))
	//{
	//	check_exception("Integral value outside the range of the char type", SV("{:c}"), hamon::numeric_limits<I>::max());
	//}

	return true;
}

template <typename CharT, typename I>
/*HAMON_CXX20_CONSTEXPR*/ bool test_integer()
{
	VERIFY(test_integer_as_integer<CharT, I>());
	VERIFY(test_integer_as_char<CharT, I>());
	return true;
}

template <typename CharT>
/*HAMON_CXX20_CONSTEXPR*/ bool test_signed_integer()
{
	// *** Test signed integral format argument ***
	VERIFY(SV("hello 42") == hamon::format(SV("hello {}"), static_cast<signed char>(42)));
	VERIFY(SV("hello 42") == hamon::format(SV("hello {}"), static_cast<short>(42)));
	VERIFY(SV("hello 42") == hamon::format(SV("hello {}"), static_cast<int>(42)));
	VERIFY(SV("hello 42") == hamon::format(SV("hello {}"), static_cast<long>(42)));
	VERIFY(SV("hello 42") == hamon::format(SV("hello {}"), static_cast<long long>(42)));

	VERIFY(SV("hello 42") == hamon::format(std::locale(), SV("hello {}"), static_cast<signed char>(42)));
	VERIFY(SV("hello 42") == hamon::format(std::locale(), SV("hello {}"), static_cast<short>(42)));
	VERIFY(SV("hello 42") == hamon::format(std::locale(), SV("hello {}"), static_cast<int>(42)));
	VERIFY(SV("hello 42") == hamon::format(std::locale(), SV("hello {}"), static_cast<long>(42)));
	VERIFY(SV("hello 42") == hamon::format(std::locale(), SV("hello {}"), static_cast<long long>(42)));

	VERIFY(test_integer<CharT, signed char>());
	VERIFY(test_integer<CharT, short>());
	VERIFY(test_integer<CharT, int>());
	VERIFY(test_integer<CharT, long>());
	VERIFY(test_integer<CharT, long long>());

	// *** test the minima and maxima ***
	VERIFY(SV("-0b10000000") == hamon::format(SV("{:#b}"), hamon::numeric_limits<std::int8_t>::min()));
	VERIFY(SV("-0200") == hamon::format(SV("{:#o}"), hamon::numeric_limits<std::int8_t>::min()));
	VERIFY(SV("-128")  == hamon::format(SV("{:#}"),  hamon::numeric_limits<std::int8_t>::min()));
	VERIFY(SV("-0x80") == hamon::format(SV("{:#x}"), hamon::numeric_limits<std::int8_t>::min()));

	VERIFY(SV("-0b1000000000000000") == hamon::format(SV("{:#b}"), hamon::numeric_limits<std::int16_t>::min()));
	VERIFY(SV("-0100000") == hamon::format(SV("{:#o}"), hamon::numeric_limits<std::int16_t>::min()));
	VERIFY(SV("-32768")   == hamon::format(SV("{:#}"),  hamon::numeric_limits<std::int16_t>::min()));
	VERIFY(SV("-0x8000")  == hamon::format(SV("{:#x}"), hamon::numeric_limits<std::int16_t>::min()));

	VERIFY(SV("-0b10000000000000000000000000000000") == hamon::format(SV("{:#b}"), hamon::numeric_limits<std::int32_t>::min()));
	VERIFY(SV("-020000000000") == hamon::format(SV("{:#o}"), hamon::numeric_limits<std::int32_t>::min()));
	VERIFY(SV("-2147483648")   == hamon::format(SV("{:#}"),  hamon::numeric_limits<std::int32_t>::min()));
	VERIFY(SV("-0x80000000")   == hamon::format(SV("{:#x}"), hamon::numeric_limits<std::int32_t>::min()));

	VERIFY(SV("-0b1000000000000000000000000000000000000000000000000000000000000000") ==
		hamon::format(SV("{:#b}"), hamon::numeric_limits<std::int64_t>::min()));
	VERIFY(SV("-01000000000000000000000") == hamon::format(SV("{:#o}"), hamon::numeric_limits<std::int64_t>::min()));
	VERIFY(SV("-9223372036854775808")     == hamon::format(SV("{:#}"),  hamon::numeric_limits<std::int64_t>::min()));
	VERIFY(SV("-0x8000000000000000")      == hamon::format(SV("{:#x}"), hamon::numeric_limits<std::int64_t>::min()));

	VERIFY(SV("0b1111111") == hamon::format(SV("{:#b}"), hamon::numeric_limits<std::int8_t>::max()));
	VERIFY(SV("0177") == hamon::format(SV("{:#o}"), hamon::numeric_limits<std::int8_t>::max()));
	VERIFY(SV("127")  == hamon::format(SV("{:#}"),  hamon::numeric_limits<std::int8_t>::max()));
	VERIFY(SV("0x7f") == hamon::format(SV("{:#x}"), hamon::numeric_limits<std::int8_t>::max()));

	VERIFY(SV("0b111111111111111") == hamon::format(SV("{:#b}"), hamon::numeric_limits<std::int16_t>::max()));
	VERIFY(SV("077777") == hamon::format(SV("{:#o}"), hamon::numeric_limits<std::int16_t>::max()));
	VERIFY(SV("32767")  == hamon::format(SV("{:#}"),  hamon::numeric_limits<std::int16_t>::max()));
	VERIFY(SV("0x7fff") == hamon::format(SV("{:#x}"), hamon::numeric_limits<std::int16_t>::max()));

	VERIFY(SV("0b1111111111111111111111111111111") == hamon::format(SV("{:#b}"), hamon::numeric_limits<std::int32_t>::max()));
	VERIFY(SV("017777777777") == hamon::format(SV("{:#o}"), hamon::numeric_limits<std::int32_t>::max()));
	VERIFY(SV("2147483647")   == hamon::format(SV("{:#}"),  hamon::numeric_limits<std::int32_t>::max()));
	VERIFY(SV("0x7fffffff")   == hamon::format(SV("{:#x}"), hamon::numeric_limits<std::int32_t>::max()));

	VERIFY(SV("0b111111111111111111111111111111111111111111111111111111111111111") ==
		hamon::format(SV("{:#b}"), hamon::numeric_limits<std::int64_t>::max()));
	VERIFY(SV("0777777777777777777777") == hamon::format(SV("{:#o}"), hamon::numeric_limits<std::int64_t>::max()));
	VERIFY(SV("9223372036854775807")    == hamon::format(SV("{:#}"),  hamon::numeric_limits<std::int64_t>::max()));
	VERIFY(SV("0x7fffffffffffffff")     == hamon::format(SV("{:#x}"), hamon::numeric_limits<std::int64_t>::max()));

	return true;
}

template <typename CharT>
/*HAMON_CXX20_CONSTEXPR*/ bool test_unsigned_integer()
{
	// ** Test unsigned integral format argument ***
	VERIFY(SV("hello 42") == hamon::format(SV("hello {}"), static_cast<unsigned char>(42)));
	VERIFY(SV("hello 42") == hamon::format(SV("hello {}"), static_cast<unsigned short>(42)));
	VERIFY(SV("hello 42") == hamon::format(SV("hello {}"), static_cast<unsigned>(42)));
	VERIFY(SV("hello 42") == hamon::format(SV("hello {}"), static_cast<unsigned long>(42)));
	VERIFY(SV("hello 42") == hamon::format(SV("hello {}"), static_cast<unsigned long long>(42)));

	VERIFY(SV("hello 42") == hamon::format(std::locale(), SV("hello {}"), static_cast<unsigned char>(42)));
	VERIFY(SV("hello 42") == hamon::format(std::locale(), SV("hello {}"), static_cast<unsigned short>(42)));
	VERIFY(SV("hello 42") == hamon::format(std::locale(), SV("hello {}"), static_cast<unsigned>(42)));
	VERIFY(SV("hello 42") == hamon::format(std::locale(), SV("hello {}"), static_cast<unsigned long>(42)));
	VERIFY(SV("hello 42") == hamon::format(std::locale(), SV("hello {}"), static_cast<unsigned long long>(42)));

	VERIFY(test_integer<CharT, unsigned char>());
	VERIFY(test_integer<CharT, unsigned short>());
	VERIFY(test_integer<CharT, unsigned>());
	VERIFY(test_integer<CharT, unsigned long>());
	VERIFY(test_integer<CharT, unsigned long long>());

	// *** test the maxima ***
	VERIFY(SV("0b11111111") == hamon::format(SV("{:#b}"), hamon::numeric_limits<std::uint8_t>::max()));
	VERIFY(SV("0377") == hamon::format(SV("{:#o}"), hamon::numeric_limits<std::uint8_t>::max()));
	VERIFY(SV("255")  == hamon::format(SV("{:#}"),  hamon::numeric_limits<std::uint8_t>::max()));
	VERIFY(SV("0xff") == hamon::format(SV("{:#x}"), hamon::numeric_limits<std::uint8_t>::max()));

	VERIFY(SV("0b1111111111111111") == hamon::format(SV("{:#b}"), hamon::numeric_limits<std::uint16_t>::max()));
	VERIFY(SV("0177777") == hamon::format(SV("{:#o}"), hamon::numeric_limits<std::uint16_t>::max()));
	VERIFY(SV("65535")   == hamon::format(SV("{:#}"),  hamon::numeric_limits<std::uint16_t>::max()));
	VERIFY(SV("0xffff")  == hamon::format(SV("{:#x}"), hamon::numeric_limits<std::uint16_t>::max()));

	VERIFY(SV("0b11111111111111111111111111111111") == hamon::format(SV("{:#b}"), hamon::numeric_limits<std::uint32_t>::max()));
	VERIFY(SV("037777777777") == hamon::format(SV("{:#o}"), hamon::numeric_limits<std::uint32_t>::max()));
	VERIFY(SV("4294967295")   == hamon::format(SV("{:#}"),  hamon::numeric_limits<std::uint32_t>::max()));
	VERIFY(SV("0xffffffff")   == hamon::format(SV("{:#x}"), hamon::numeric_limits<std::uint32_t>::max()));

	VERIFY(SV("0b1111111111111111111111111111111111111111111111111111111111111111") ==
		hamon::format(SV("{:#b}"), hamon::numeric_limits<std::uint64_t>::max()));
	VERIFY(SV("01777777777777777777777") == hamon::format(SV("{:#o}"), hamon::numeric_limits<std::uint64_t>::max()));
	VERIFY(SV("18446744073709551615")    == hamon::format(SV("{:#}"),  hamon::numeric_limits<std::uint64_t>::max()));
	VERIFY(SV("0xffffffffffffffff")      == hamon::format(SV("{:#x}"), hamon::numeric_limits<std::uint64_t>::max()));

	return true;
}

template <typename CharT, typename F>
/*HAMON_CXX20_CONSTEXPR*/ bool test_floating_point_hex_lower_case()
{
	auto nan_pos = hamon::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// Test whether the hexadecimal letters are the proper case.
	// The precision is too large for float, so two tests are used.
	VERIFY(SV("answer is '1.abcp+0'") == hamon::format(SV("answer is '{:a}'"), F(0x1.abcp+0)));
	VERIFY(SV("answer is '1.defp+0'") == hamon::format(SV("answer is '{:a}'"), F(0x1.defp+0)));

	// *** align-fill & width ***
	VERIFY(SV("answer is '   1p-2'") == hamon::format(SV("answer is '{:7a}'"),  F(0.25)));
	VERIFY(SV("answer is '   1p-2'") == hamon::format(SV("answer is '{:>7a}'"), F(0.25)));
	VERIFY(SV("answer is '1p-2   '") == hamon::format(SV("answer is '{:<7a}'"), F(0.25)));
	VERIFY(SV("answer is ' 1p-2  '") == hamon::format(SV("answer is '{:^7a}'"), F(0.25)));

	// The fill character ':' is allowed here (P0645) but not in ranges (P2286).
	VERIFY(SV("answer is ':::1p-3'") == hamon::format(SV("answer is '{::>7a}'"), F(125e-3)));
	VERIFY(SV("answer is '1p-3:::'") == hamon::format(SV("answer is '{::<7a}'"), F(125e-3)));
	VERIFY(SV("answer is ':1p-3::'") == hamon::format(SV("answer is '{::^7a}'"), F(125e-3)));

	VERIFY(SV("answer is '***inf'") == hamon::format(SV("answer is '{:*>6a}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is 'inf***'") == hamon::format(SV("answer is '{:*<6a}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '*inf**'") == hamon::format(SV("answer is '{:*^6a}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '###-inf'") == hamon::format(SV("answer is '{:#>7a}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf###'") == hamon::format(SV("answer is '{:#<7a}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '#-inf##'") == hamon::format(SV("answer is '{:#^7a}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '^^^nan'") == hamon::format(SV("answer is '{:^>6a}'"), nan_pos));
	VERIFY(SV("answer is 'nan^^^'") == hamon::format(SV("answer is '{:^<6a}'"), nan_pos));
	VERIFY(SV("answer is '^nan^^'") == hamon::format(SV("answer is '{:^^6a}'"), nan_pos));

	VERIFY(SV("answer is '000-nan'") == hamon::format(SV("answer is '{:0>7a}'"), nan_neg));
	VERIFY(SV("answer is '-nan000'") == hamon::format(SV("answer is '{:0<7a}'"), nan_neg));
	VERIFY(SV("answer is '0-nan00'") == hamon::format(SV("answer is '{:0^7a}'"), nan_neg));

	// Test whether zero padding is ignored
	VERIFY(SV("answer is '   1p-2'") == hamon::format(SV("answer is '{:>07a}'"), F(0.25)));
	VERIFY(SV("answer is '1p-2   '") == hamon::format(SV("answer is '{:<07a}'"), F(0.25)));
	VERIFY(SV("answer is ' 1p-2  '") == hamon::format(SV("answer is '{:^07a}'"), F(0.25)));

	// *** Sign ***
	VERIFY(SV("answer is '0p+0'")  == hamon::format(SV("answer is '{:a}'"),  F(0)));
	VERIFY(SV("answer is '0p+0'")  == hamon::format(SV("answer is '{:-a}'"), F(0)));
	VERIFY(SV("answer is '+0p+0'") == hamon::format(SV("answer is '{:+a}'"), F(0)));
	VERIFY(SV("answer is ' 0p+0'") == hamon::format(SV("answer is '{: a}'"), F(0)));

	VERIFY(SV("answer is '-0p+0'") == hamon::format(SV("answer is '{:a}'"),  F(-0.)));
	VERIFY(SV("answer is '-0p+0'") == hamon::format(SV("answer is '{:-a}'"), F(-0.)));
	VERIFY(SV("answer is '-0p+0'") == hamon::format(SV("answer is '{:+a}'"), F(-0.)));
	VERIFY(SV("answer is '-0p+0'") == hamon::format(SV("answer is '{: a}'"), F(-0.)));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	VERIFY(SV("answer is 'inf'")  == hamon::format(SV("answer is '{:a}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is 'inf'")  == hamon::format(SV("answer is '{:-a}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '+inf'") == hamon::format(SV("answer is '{:+a}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is ' inf'") == hamon::format(SV("answer is '{: a}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:a}'"),  -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:-a}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:+a}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{: a}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is 'nan'")  == hamon::format(SV("answer is '{:a}'"),  nan_pos));
	VERIFY(SV("answer is 'nan'")  == hamon::format(SV("answer is '{:-a}'"), nan_pos));
	VERIFY(SV("answer is '+nan'") == hamon::format(SV("answer is '{:+a}'"), nan_pos));
	VERIFY(SV("answer is ' nan'") == hamon::format(SV("answer is '{: a}'"), nan_pos));

	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:a}'"),  nan_neg));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:-a}'"), nan_neg));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:+a}'"), nan_neg));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{: a}'"), nan_neg));

	// *** alternate form ***
	// When precision is zero there's no decimal point except when the alternate form is specified.
	VERIFY(SV("answer is '0p+0'")  == hamon::format(SV("answer is '{:a}'"),  F(0)));
	VERIFY(SV("answer is '0.p+0'") == hamon::format(SV("answer is '{:#a}'"), F(0)));

	VERIFY(SV("answer is '1p+1'")   == hamon::format(SV("answer is '{:.0a}'"),  F(2.5)));
	VERIFY(SV("answer is '1.p+1'")  == hamon::format(SV("answer is '{:#.0a}'"), F(2.5)));
	VERIFY(SV("answer is '1.4p+1'") == hamon::format(SV("answer is '{:#a}'"),   F(2.5)));

	VERIFY(SV("answer is 'inf'")  == hamon::format(SV("answer is '{:#a}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:#a}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is 'nan'")  == hamon::format(SV("answer is '{:#a}'"), nan_pos));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:#a}'"), nan_neg));

	// *** zero-padding & width ***
	VERIFY(SV("answer is '1p-5'")   == hamon::format(SV("answer is '{:04a}'"),  0.03125));
	VERIFY(SV("answer is '+1p-5'")  == hamon::format(SV("answer is '{:+05a}'"), 0.03125));
	VERIFY(SV("answer is '+01p-5'") == hamon::format(SV("answer is '{:+06a}'"), 0.03125));

	VERIFY(SV("answer is '0001p-5'") == hamon::format(SV("answer is '{:07a}'"),  0.03125));
	VERIFY(SV("answer is '0001p-5'") == hamon::format(SV("answer is '{:-07a}'"), 0.03125));
	VERIFY(SV("answer is '+001p-5'") == hamon::format(SV("answer is '{:+07a}'"), 0.03125));
	VERIFY(SV("answer is ' 001p-5'") == hamon::format(SV("answer is '{: 07a}'"), 0.03125));

	VERIFY(SV("answer is '       inf'") == hamon::format(SV("answer is '{:010a}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '       inf'") == hamon::format(SV("answer is '{:-010a}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      +inf'") == hamon::format(SV("answer is '{:+010a}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '       inf'") == hamon::format(SV("answer is '{: 010a}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{:010a}'"),  -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{:-010a}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{:+010a}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{: 010a}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '       nan'") == hamon::format(SV("answer is '{:010a}'"),  nan_pos));
	VERIFY(SV("answer is '       nan'") == hamon::format(SV("answer is '{:-010a}'"), nan_pos));
	VERIFY(SV("answer is '      +nan'") == hamon::format(SV("answer is '{:+010a}'"), nan_pos));
	VERIFY(SV("answer is '       nan'") == hamon::format(SV("answer is '{: 010a}'"), nan_pos));

	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{:010a}'"),  nan_neg));
	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{:-010a}'"), nan_neg));
	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{:+010a}'"), nan_neg));
	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{: 010a}'"), nan_neg));

	// *** precision ***
	// See format_test_floating_point_hex_lower_case_precision

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp
	return true;
}

template <typename CharT, typename F>
/*HAMON_CXX20_CONSTEXPR*/ bool test_floating_point_hex_upper_case()
{
	auto nan_pos = hamon::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// Test whether the hexadecimal letters are the proper case.
	// The precision is too large for float, so two tests are used.
	VERIFY(SV("answer is '1.ABCP+0'") == hamon::format(SV("answer is '{:A}'"), F(0x1.abcp+0)));
	VERIFY(SV("answer is '1.DEFP+0'") == hamon::format(SV("answer is '{:A}'"), F(0x1.defp+0)));

	// *** align-fill & width ***
	VERIFY(SV("answer is '   1P-2'") == hamon::format(SV("answer is '{:7A}'"),  F(0.25)));
	VERIFY(SV("answer is '   1P-2'") == hamon::format(SV("answer is '{:>7A}'"), F(0.25)));
	VERIFY(SV("answer is '1P-2   '") == hamon::format(SV("answer is '{:<7A}'"), F(0.25)));
	VERIFY(SV("answer is ' 1P-2  '") == hamon::format(SV("answer is '{:^7A}'"), F(0.25)));

	VERIFY(SV("answer is '---1P-3'") == hamon::format(SV("answer is '{:->7A}'"), F(125e-3)));
	VERIFY(SV("answer is '1P-3---'") == hamon::format(SV("answer is '{:-<7A}'"), F(125e-3)));
	VERIFY(SV("answer is '-1P-3--'") == hamon::format(SV("answer is '{:-^7A}'"), F(125e-3)));

	VERIFY(SV("answer is '***INF'") == hamon::format(SV("answer is '{:*>6A}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is 'INF***'") == hamon::format(SV("answer is '{:*<6A}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '*INF**'") == hamon::format(SV("answer is '{:*^6A}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '###-INF'") == hamon::format(SV("answer is '{:#>7A}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-INF###'") == hamon::format(SV("answer is '{:#<7A}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '#-INF##'") == hamon::format(SV("answer is '{:#^7A}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '^^^NAN'") == hamon::format(SV("answer is '{:^>6A}'"), nan_pos));
	VERIFY(SV("answer is 'NAN^^^'") == hamon::format(SV("answer is '{:^<6A}'"), nan_pos));
	VERIFY(SV("answer is '^NAN^^'") == hamon::format(SV("answer is '{:^^6A}'"), nan_pos));

	VERIFY(SV("answer is '000-NAN'") == hamon::format(SV("answer is '{:0>7A}'"), nan_neg));
	VERIFY(SV("answer is '-NAN000'") == hamon::format(SV("answer is '{:0<7A}'"), nan_neg));
	VERIFY(SV("answer is '0-NAN00'") == hamon::format(SV("answer is '{:0^7A}'"), nan_neg));

	// Test whether zero padding is ignored
	VERIFY(SV("answer is '   1P-2'") == hamon::format(SV("answer is '{:>07A}'"), F(0.25)));
	VERIFY(SV("answer is '1P-2   '") == hamon::format(SV("answer is '{:<07A}'"), F(0.25)));
	VERIFY(SV("answer is ' 1P-2  '") == hamon::format(SV("answer is '{:^07A}'"), F(0.25)));

	// *** Sign ***
	VERIFY(SV("answer is '0P+0'")  == hamon::format(SV("answer is '{:A}'"),  F(0)));
	VERIFY(SV("answer is '0P+0'")  == hamon::format(SV("answer is '{:-A}'"), F(0)));
	VERIFY(SV("answer is '+0P+0'") == hamon::format(SV("answer is '{:+A}'"), F(0)));
	VERIFY(SV("answer is ' 0P+0'") == hamon::format(SV("answer is '{: A}'"), F(0)));

	VERIFY(SV("answer is '-0P+0'") == hamon::format(SV("answer is '{:A}'"),  F(-0.)));
	VERIFY(SV("answer is '-0P+0'") == hamon::format(SV("answer is '{:-A}'"), F(-0.)));
	VERIFY(SV("answer is '-0P+0'") == hamon::format(SV("answer is '{:+A}'"), F(-0.)));
	VERIFY(SV("answer is '-0P+0'") == hamon::format(SV("answer is '{: A}'"), F(-0.)));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	VERIFY(SV("answer is 'INF'")  == hamon::format(SV("answer is '{:A}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is 'INF'")  == hamon::format(SV("answer is '{:-A}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '+INF'") == hamon::format(SV("answer is '{:+A}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is ' INF'") == hamon::format(SV("answer is '{: A}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '-INF'") == hamon::format(SV("answer is '{:A}'"),  -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-INF'") == hamon::format(SV("answer is '{:-A}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-INF'") == hamon::format(SV("answer is '{:+A}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-INF'") == hamon::format(SV("answer is '{: A}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is 'NAN'")  == hamon::format(SV("answer is '{:A}'"),  nan_pos));
	VERIFY(SV("answer is 'NAN'")  == hamon::format(SV("answer is '{:-A}'"), nan_pos));
	VERIFY(SV("answer is '+NAN'") == hamon::format(SV("answer is '{:+A}'"), nan_pos));
	VERIFY(SV("answer is ' NAN'") == hamon::format(SV("answer is '{: A}'"), nan_pos));

	VERIFY(SV("answer is '-NAN'") == hamon::format(SV("answer is '{:A}'"),  nan_neg));
	VERIFY(SV("answer is '-NAN'") == hamon::format(SV("answer is '{:-A}'"), nan_neg));
	VERIFY(SV("answer is '-NAN'") == hamon::format(SV("answer is '{:+A}'"), nan_neg));
	VERIFY(SV("answer is '-NAN'") == hamon::format(SV("answer is '{: A}'"), nan_neg));

	// *** alternate form ***
	// When precision is zero there's no decimal point except when the alternate form is specified.
	VERIFY(SV("answer is '0P+0'")  == hamon::format(SV("answer is '{:A}'"),  F(0)));
	VERIFY(SV("answer is '0.P+0'") == hamon::format(SV("answer is '{:#A}'"), F(0)));

	VERIFY(SV("answer is '1P+1'")   == hamon::format(SV("answer is '{:.0A}'"),  F(2.5)));
	VERIFY(SV("answer is '1.P+1'")  == hamon::format(SV("answer is '{:#.0A}'"), F(2.5)));
	VERIFY(SV("answer is '1.4P+1'") == hamon::format(SV("answer is '{:#A}'"),   F(2.5)));

	VERIFY(SV("answer is 'INF'")  == hamon::format(SV("answer is '{:#A}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-INF'") == hamon::format(SV("answer is '{:#A}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is 'NAN'")  == hamon::format(SV("answer is '{:#A}'"), nan_pos));
	VERIFY(SV("answer is '-NAN'") == hamon::format(SV("answer is '{:#A}'"), nan_neg));

	// *** zero-padding & width ***
	VERIFY(SV("answer is '1P-5'")   == hamon::format(SV("answer is '{:04A}'"),  0.03125));
	VERIFY(SV("answer is '+1P-5'")  == hamon::format(SV("answer is '{:+05A}'"), 0.03125));
	VERIFY(SV("answer is '+01P-5'") == hamon::format(SV("answer is '{:+06A}'"), 0.03125));

	VERIFY(SV("answer is '0001P-5'") == hamon::format(SV("answer is '{:07A}'"),  0.03125));
	VERIFY(SV("answer is '0001P-5'") == hamon::format(SV("answer is '{:-07A}'"), 0.03125));
	VERIFY(SV("answer is '+001P-5'") == hamon::format(SV("answer is '{:+07A}'"), 0.03125));
	VERIFY(SV("answer is ' 001P-5'") == hamon::format(SV("answer is '{: 07A}'"), 0.03125));

	VERIFY(SV("answer is '       INF'") == hamon::format(SV("answer is '{:010A}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '       INF'") == hamon::format(SV("answer is '{:-010A}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      +INF'") == hamon::format(SV("answer is '{:+010A}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '       INF'") == hamon::format(SV("answer is '{: 010A}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '      -INF'") == hamon::format(SV("answer is '{:010A}'"),  -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -INF'") == hamon::format(SV("answer is '{:-010A}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -INF'") == hamon::format(SV("answer is '{:+010A}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -INF'") == hamon::format(SV("answer is '{: 010A}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '       NAN'") == hamon::format(SV("answer is '{:010A}'"),  nan_pos));
	VERIFY(SV("answer is '       NAN'") == hamon::format(SV("answer is '{:-010A}'"), nan_pos));
	VERIFY(SV("answer is '      +NAN'") == hamon::format(SV("answer is '{:+010A}'"), nan_pos));
	VERIFY(SV("answer is '       NAN'") == hamon::format(SV("answer is '{: 010A}'"), nan_pos));

	VERIFY(SV("answer is '      -NAN'") == hamon::format(SV("answer is '{:010A}'"),  nan_neg));
	VERIFY(SV("answer is '      -NAN'") == hamon::format(SV("answer is '{:-010A}'"), nan_neg));
	VERIFY(SV("answer is '      -NAN'") == hamon::format(SV("answer is '{:+010A}'"), nan_neg));
	VERIFY(SV("answer is '      -NAN'") == hamon::format(SV("answer is '{: 010A}'"), nan_neg));

	// *** precision ***
	// See format_test_floating_point_hex_upper_case_precision

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp
	return true;
}

template <typename CharT, typename F>
/*HAMON_CXX20_CONSTEXPR*/ bool test_floating_point_hex_lower_case_precision()
{
	auto nan_pos = hamon::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	VERIFY(SV("answer is '   1.000000p-2'") == hamon::format(SV("answer is '{:14.6a}'"),  F(0.25)));
	VERIFY(SV("answer is '   1.000000p-2'") == hamon::format(SV("answer is '{:>14.6a}'"), F(0.25)));
	VERIFY(SV("answer is '1.000000p-2   '") == hamon::format(SV("answer is '{:<14.6a}'"), F(0.25)));
	VERIFY(SV("answer is ' 1.000000p-2  '") == hamon::format(SV("answer is '{:^14.6a}'"), F(0.25)));

	VERIFY(SV("answer is '---1.000000p-3'") == hamon::format(SV("answer is '{:->14.6a}'"), F(125e-3)));
	VERIFY(SV("answer is '1.000000p-3---'") == hamon::format(SV("answer is '{:-<14.6a}'"), F(125e-3)));
	VERIFY(SV("answer is '-1.000000p-3--'") == hamon::format(SV("answer is '{:-^14.6a}'"), F(125e-3)));

	VERIFY(SV("answer is '***inf'") == hamon::format(SV("answer is '{:*>6.6a}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is 'inf***'") == hamon::format(SV("answer is '{:*<6.6a}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '*inf**'") == hamon::format(SV("answer is '{:*^6.6a}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '###-inf'") == hamon::format(SV("answer is '{:#>7.6a}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf###'") == hamon::format(SV("answer is '{:#<7.6a}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '#-inf##'") == hamon::format(SV("answer is '{:#^7.6a}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '^^^nan'") == hamon::format(SV("answer is '{:^>6.6a}'"), nan_pos));
	VERIFY(SV("answer is 'nan^^^'") == hamon::format(SV("answer is '{:^<6.6a}'"), nan_pos));
	VERIFY(SV("answer is '^nan^^'") == hamon::format(SV("answer is '{:^^6.6a}'"), nan_pos));

	VERIFY(SV("answer is '000-nan'") == hamon::format(SV("answer is '{:0>7.6a}'"), nan_neg));
	VERIFY(SV("answer is '-nan000'") == hamon::format(SV("answer is '{:0<7.6a}'"), nan_neg));
	VERIFY(SV("answer is '0-nan00'") == hamon::format(SV("answer is '{:0^7.6a}'"), nan_neg));

	// Test whether zero padding is ignored
	VERIFY(SV("answer is '   1.000000p-2'") == hamon::format(SV("answer is '{:>014.6a}'"), F(0.25)));
	VERIFY(SV("answer is '1.000000p-2   '") == hamon::format(SV("answer is '{:<014.6a}'"), F(0.25)));
	VERIFY(SV("answer is ' 1.000000p-2  '") == hamon::format(SV("answer is '{:^014.6a}'"), F(0.25)));

	// *** Sign ***
	VERIFY(SV("answer is '0.000000p+0'")  == hamon::format(SV("answer is '{:.6a}'"),  F(0)));
	VERIFY(SV("answer is '0.000000p+0'")  == hamon::format(SV("answer is '{:-.6a}'"), F(0)));
	VERIFY(SV("answer is '+0.000000p+0'") == hamon::format(SV("answer is '{:+.6a}'"), F(0)));
	VERIFY(SV("answer is ' 0.000000p+0'") == hamon::format(SV("answer is '{: .6a}'"), F(0)));

	VERIFY(SV("answer is '-0.000000p+0'") == hamon::format(SV("answer is '{:.6a}'"),  F(-0.)));
	VERIFY(SV("answer is '-0.000000p+0'") == hamon::format(SV("answer is '{:-.6a}'"), F(-0.)));
	VERIFY(SV("answer is '-0.000000p+0'") == hamon::format(SV("answer is '{:+.6a}'"), F(-0.)));
	VERIFY(SV("answer is '-0.000000p+0'") == hamon::format(SV("answer is '{: .6a}'"), F(-0.)));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	VERIFY(SV("answer is 'inf'")  == hamon::format(SV("answer is '{:.6a}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is 'inf'")  == hamon::format(SV("answer is '{:-.6a}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '+inf'") == hamon::format(SV("answer is '{:+.6a}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is ' inf'") == hamon::format(SV("answer is '{: .6a}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:.6a}'"),  -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:-.6a}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:+.6a}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{: .6a}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is 'nan'")  == hamon::format(SV("answer is '{:.6a}'"),  nan_pos));
	VERIFY(SV("answer is 'nan'")  == hamon::format(SV("answer is '{:-.6a}'"), nan_pos));
	VERIFY(SV("answer is '+nan'") == hamon::format(SV("answer is '{:+.6a}'"), nan_pos));
	VERIFY(SV("answer is ' nan'") == hamon::format(SV("answer is '{: .6a}'"), nan_pos));

	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:.6a}'"),  nan_neg));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:-.6a}'"), nan_neg));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:+.6a}'"), nan_neg));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{: .6a}'"), nan_neg));

	// *** alternate form ***
	VERIFY(SV("answer is '1.400000p+1'") == hamon::format(SV("answer is '{:#.6a}'"), F(2.5)));

	VERIFY(SV("answer is 'inf'")  == hamon::format(SV("answer is '{:#.6a}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:#.6a}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is 'nan'")  == hamon::format(SV("answer is '{:#.6a}'"), nan_pos));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:#.6a}'"), nan_neg));

	// *** zero-padding & width ***
	VERIFY(SV("answer is '1.000000p-5'")   == hamon::format(SV("answer is '{:011.6a}'"),  0.03125));
	VERIFY(SV("answer is '+1.000000p-5'")  == hamon::format(SV("answer is '{:+012.6a}'"), 0.03125));
	VERIFY(SV("answer is '+01.000000p-5'") == hamon::format(SV("answer is '{:+013.6a}'"), 0.03125));

	VERIFY(SV("answer is '0001.000000p-5'") == hamon::format(SV("answer is '{:014.6a}'"),  0.03125));
	VERIFY(SV("answer is '0001.000000p-5'") == hamon::format(SV("answer is '{:-014.6a}'"), 0.03125));
	VERIFY(SV("answer is '+001.000000p-5'") == hamon::format(SV("answer is '{:+014.6a}'"), 0.03125));
	VERIFY(SV("answer is ' 001.000000p-5'") == hamon::format(SV("answer is '{: 014.6a}'"), 0.03125));

	VERIFY(SV("answer is '       inf'") == hamon::format(SV("answer is '{:010.6a}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '       inf'") == hamon::format(SV("answer is '{:-010.6a}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      +inf'") == hamon::format(SV("answer is '{:+010.6a}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '       inf'") == hamon::format(SV("answer is '{: 010.6a}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{:010.6a}'"),  -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{:-010.6a}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{:+010.6a}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{: 010.6a}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '       nan'") == hamon::format(SV("answer is '{:010.6a}'"),  nan_pos));
	VERIFY(SV("answer is '       nan'") == hamon::format(SV("answer is '{:-010.6a}'"), nan_pos));
	VERIFY(SV("answer is '      +nan'") == hamon::format(SV("answer is '{:+010.6a}'"), nan_pos));
	VERIFY(SV("answer is '       nan'") == hamon::format(SV("answer is '{: 010.6a}'"), nan_pos));

	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{:010.6a}'"),  nan_neg));
	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{:-010.6a}'"), nan_neg));
	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{:+010.6a}'"), nan_neg));
	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{: 010.6a}'"), nan_neg));

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp
	return true;
}

template <typename CharT, typename F>
/*HAMON_CXX20_CONSTEXPR*/ bool test_floating_point_hex_upper_case_precision()
{
	auto nan_pos = hamon::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	VERIFY(SV("answer is '   1.000000P-2'") == hamon::format(SV("answer is '{:14.6A}'"),  F(0.25)));
	VERIFY(SV("answer is '   1.000000P-2'") == hamon::format(SV("answer is '{:>14.6A}'"), F(0.25)));
	VERIFY(SV("answer is '1.000000P-2   '") == hamon::format(SV("answer is '{:<14.6A}'"), F(0.25)));
	VERIFY(SV("answer is ' 1.000000P-2  '") == hamon::format(SV("answer is '{:^14.6A}'"), F(0.25)));

	VERIFY(SV("answer is '---1.000000P-3'") == hamon::format(SV("answer is '{:->14.6A}'"), F(125e-3)));
	VERIFY(SV("answer is '1.000000P-3---'") == hamon::format(SV("answer is '{:-<14.6A}'"), F(125e-3)));
	VERIFY(SV("answer is '-1.000000P-3--'") == hamon::format(SV("answer is '{:-^14.6A}'"), F(125e-3)));

	VERIFY(SV("answer is '***INF'") == hamon::format(SV("answer is '{:*>6.6A}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is 'INF***'") == hamon::format(SV("answer is '{:*<6.6A}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '*INF**'") == hamon::format(SV("answer is '{:*^6.6A}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '###-INF'") == hamon::format(SV("answer is '{:#>7.6A}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-INF###'") == hamon::format(SV("answer is '{:#<7.6A}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '#-INF##'") == hamon::format(SV("answer is '{:#^7.6A}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '^^^NAN'") == hamon::format(SV("answer is '{:^>6.6A}'"), nan_pos));
	VERIFY(SV("answer is 'NAN^^^'") == hamon::format(SV("answer is '{:^<6.6A}'"), nan_pos));
	VERIFY(SV("answer is '^NAN^^'") == hamon::format(SV("answer is '{:^^6.6A}'"), nan_pos));

	VERIFY(SV("answer is '000-NAN'") == hamon::format(SV("answer is '{:0>7.6A}'"), nan_neg));
	VERIFY(SV("answer is '-NAN000'") == hamon::format(SV("answer is '{:0<7.6A}'"), nan_neg));
	VERIFY(SV("answer is '0-NAN00'") == hamon::format(SV("answer is '{:0^7.6A}'"), nan_neg));

	// Test whether zero padding is ignored
	VERIFY(SV("answer is '   1.000000P-2'") == hamon::format(SV("answer is '{:>014.6A}'"), F(0.25)));
	VERIFY(SV("answer is '1.000000P-2   '") == hamon::format(SV("answer is '{:<014.6A}'"), F(0.25)));
	VERIFY(SV("answer is ' 1.000000P-2  '") == hamon::format(SV("answer is '{:^014.6A}'"), F(0.25)));

	// *** Sign ***
	VERIFY(SV("answer is '0.000000P+0'")  == hamon::format(SV("answer is '{:.6A}'"),  F(0)));
	VERIFY(SV("answer is '0.000000P+0'")  == hamon::format(SV("answer is '{:-.6A}'"), F(0)));
	VERIFY(SV("answer is '+0.000000P+0'") == hamon::format(SV("answer is '{:+.6A}'"), F(0)));
	VERIFY(SV("answer is ' 0.000000P+0'") == hamon::format(SV("answer is '{: .6A}'"), F(0)));

	VERIFY(SV("answer is '-0.000000P+0'") == hamon::format(SV("answer is '{:.6A}'"),  F(-0.)));
	VERIFY(SV("answer is '-0.000000P+0'") == hamon::format(SV("answer is '{:-.6A}'"), F(-0.)));
	VERIFY(SV("answer is '-0.000000P+0'") == hamon::format(SV("answer is '{:+.6A}'"), F(-0.)));
	VERIFY(SV("answer is '-0.000000P+0'") == hamon::format(SV("answer is '{: .6A}'"), F(-0.)));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	VERIFY(SV("answer is 'INF'")  == hamon::format(SV("answer is '{:.6A}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is 'INF'")  == hamon::format(SV("answer is '{:-.6A}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '+INF'") == hamon::format(SV("answer is '{:+.6A}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is ' INF'") == hamon::format(SV("answer is '{: .6A}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '-INF'") == hamon::format(SV("answer is '{:.6A}'"),  -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-INF'") == hamon::format(SV("answer is '{:-.6A}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-INF'") == hamon::format(SV("answer is '{:+.6A}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-INF'") == hamon::format(SV("answer is '{: .6A}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is 'NAN'")  == hamon::format(SV("answer is '{:.6A}'"),  nan_pos));
	VERIFY(SV("answer is 'NAN'")  == hamon::format(SV("answer is '{:-.6A}'"), nan_pos));
	VERIFY(SV("answer is '+NAN'") == hamon::format(SV("answer is '{:+.6A}'"), nan_pos));
	VERIFY(SV("answer is ' NAN'") == hamon::format(SV("answer is '{: .6A}'"), nan_pos));

	VERIFY(SV("answer is '-NAN'") == hamon::format(SV("answer is '{:.6A}'"),  nan_neg));
	VERIFY(SV("answer is '-NAN'") == hamon::format(SV("answer is '{:-.6A}'"), nan_neg));
	VERIFY(SV("answer is '-NAN'") == hamon::format(SV("answer is '{:+.6A}'"), nan_neg));
	VERIFY(SV("answer is '-NAN'") == hamon::format(SV("answer is '{: .6A}'"), nan_neg));

	// *** alternate form ***
	VERIFY(SV("answer is '1.400000P+1'") == hamon::format(SV("answer is '{:#.6A}'"), F(2.5)));

	VERIFY(SV("answer is 'INF'")  == hamon::format(SV("answer is '{:#.6A}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-INF'") == hamon::format(SV("answer is '{:#.6A}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is 'NAN'")  == hamon::format(SV("answer is '{:#.6A}'"), nan_pos));
	VERIFY(SV("answer is '-NAN'") == hamon::format(SV("answer is '{:#.6A}'"), nan_neg));

	// *** zero-padding & width ***
	VERIFY(SV("answer is '1.000000P-5'")   == hamon::format(SV("answer is '{:011.6A}'"),  0.03125));
	VERIFY(SV("answer is '+1.000000P-5'")  == hamon::format(SV("answer is '{:+012.6A}'"), 0.03125));
	VERIFY(SV("answer is '+01.000000P-5'") == hamon::format(SV("answer is '{:+013.6A}'"), 0.03125));

	VERIFY(SV("answer is '0001.000000P-5'") == hamon::format(SV("answer is '{:014.6A}'"),  0.03125));
	VERIFY(SV("answer is '0001.000000P-5'") == hamon::format(SV("answer is '{:-014.6A}'"), 0.03125));
	VERIFY(SV("answer is '+001.000000P-5'") == hamon::format(SV("answer is '{:+014.6A}'"), 0.03125));
	VERIFY(SV("answer is ' 001.000000P-5'") == hamon::format(SV("answer is '{: 014.6A}'"), 0.03125));

	VERIFY(SV("answer is '       INF'") == hamon::format(SV("answer is '{:010.6A}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '       INF'") == hamon::format(SV("answer is '{:-010.6A}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      +INF'") == hamon::format(SV("answer is '{:+010.6A}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '       INF'") == hamon::format(SV("answer is '{: 010.6A}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '      -INF'") == hamon::format(SV("answer is '{:010.6A}'"),  -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -INF'") == hamon::format(SV("answer is '{:-010.6A}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -INF'") == hamon::format(SV("answer is '{:+010.6A}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -INF'") == hamon::format(SV("answer is '{: 010.6A}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '       NAN'") == hamon::format(SV("answer is '{:010.6A}'"),  nan_pos));
	VERIFY(SV("answer is '       NAN'") == hamon::format(SV("answer is '{:-010.6A}'"), nan_pos));
	VERIFY(SV("answer is '      +NAN'") == hamon::format(SV("answer is '{:+010.6A}'"), nan_pos));
	VERIFY(SV("answer is '       NAN'") == hamon::format(SV("answer is '{: 010.6A}'"), nan_pos));

	VERIFY(SV("answer is '      -NAN'") == hamon::format(SV("answer is '{:010.6A}'"),  nan_neg));
	VERIFY(SV("answer is '      -NAN'") == hamon::format(SV("answer is '{:-010.6A}'"), nan_neg));
	VERIFY(SV("answer is '      -NAN'") == hamon::format(SV("answer is '{:+010.6A}'"), nan_neg));
	VERIFY(SV("answer is '      -NAN'") == hamon::format(SV("answer is '{: 010.6A}'"), nan_neg));

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp
	return true;
}

template <typename CharT, typename F>
/*HAMON_CXX20_CONSTEXPR*/ bool test_floating_point_scientific_lower_case()
{
	auto nan_pos = hamon::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	VERIFY(SV("answer is '   2.500000e-01'") == hamon::format(SV("answer is '{:15e}'"),  F(0.25)));
	VERIFY(SV("answer is '   2.500000e-01'") == hamon::format(SV("answer is '{:>15e}'"), F(0.25)));
	VERIFY(SV("answer is '2.500000e-01   '") == hamon::format(SV("answer is '{:<15e}'"), F(0.25)));
	VERIFY(SV("answer is ' 2.500000e-01  '") == hamon::format(SV("answer is '{:^15e}'"), F(0.25)));

	VERIFY(SV("answer is '---1.250000e-01'") == hamon::format(SV("answer is '{:->15e}'"), F(125e-3)));
	VERIFY(SV("answer is '1.250000e-01---'") == hamon::format(SV("answer is '{:-<15e}'"), F(125e-3)));
	VERIFY(SV("answer is '-1.250000e-01--'") == hamon::format(SV("answer is '{:-^15e}'"), F(125e-3)));

	VERIFY(SV("answer is '***inf'") == hamon::format(SV("answer is '{:*>6e}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is 'inf***'") == hamon::format(SV("answer is '{:*<6e}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '*inf**'") == hamon::format(SV("answer is '{:*^6e}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '###-inf'") == hamon::format(SV("answer is '{:#>7e}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf###'") == hamon::format(SV("answer is '{:#<7e}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '#-inf##'") == hamon::format(SV("answer is '{:#^7e}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '^^^nan'") == hamon::format(SV("answer is '{:^>6e}'"), nan_pos));
	VERIFY(SV("answer is 'nan^^^'") == hamon::format(SV("answer is '{:^<6e}'"), nan_pos));
	VERIFY(SV("answer is '^nan^^'") == hamon::format(SV("answer is '{:^^6e}'"), nan_pos));

	VERIFY(SV("answer is '000-nan'") == hamon::format(SV("answer is '{:0>7e}'"), nan_neg));
	VERIFY(SV("answer is '-nan000'") == hamon::format(SV("answer is '{:0<7e}'"), nan_neg));
	VERIFY(SV("answer is '0-nan00'") == hamon::format(SV("answer is '{:0^7e}'"), nan_neg));

	// Test whether zero padding is ignored
	VERIFY(SV("answer is '   2.500000e-01'") == hamon::format(SV("answer is '{:>015e}'"), F(0.25)));
	VERIFY(SV("answer is '2.500000e-01   '") == hamon::format(SV("answer is '{:<015e}'"), F(0.25)));
	VERIFY(SV("answer is ' 2.500000e-01  '") == hamon::format(SV("answer is '{:^015e}'"), F(0.25)));

	// *** Sign ***
	VERIFY(SV("answer is '0.000000e+00'")  == hamon::format(SV("answer is '{:e}'"),  F(0)));
	VERIFY(SV("answer is '0.000000e+00'")  == hamon::format(SV("answer is '{:-e}'"), F(0)));
	VERIFY(SV("answer is '+0.000000e+00'") == hamon::format(SV("answer is '{:+e}'"), F(0)));
	VERIFY(SV("answer is ' 0.000000e+00'") == hamon::format(SV("answer is '{: e}'"), F(0)));

	VERIFY(SV("answer is '-0.000000e+00'") == hamon::format(SV("answer is '{:e}'"),  F(-0.)));
	VERIFY(SV("answer is '-0.000000e+00'") == hamon::format(SV("answer is '{:-e}'"), F(-0.)));
	VERIFY(SV("answer is '-0.000000e+00'") == hamon::format(SV("answer is '{:+e}'"), F(-0.)));
	VERIFY(SV("answer is '-0.000000e+00'") == hamon::format(SV("answer is '{: e}'"), F(-0.)));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	VERIFY(SV("answer is 'inf'")  == hamon::format(SV("answer is '{:e}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is 'inf'")  == hamon::format(SV("answer is '{:-e}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '+inf'") == hamon::format(SV("answer is '{:+e}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is ' inf'") == hamon::format(SV("answer is '{: e}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:e}'"),  -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:-e}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:+e}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{: e}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is 'nan'")  == hamon::format(SV("answer is '{:e}'"),  nan_pos));
	VERIFY(SV("answer is 'nan'")  == hamon::format(SV("answer is '{:-e}'"), nan_pos));
	VERIFY(SV("answer is '+nan'") == hamon::format(SV("answer is '{:+e}'"), nan_pos));
	VERIFY(SV("answer is ' nan'") == hamon::format(SV("answer is '{: e}'"), nan_pos));

	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:e}'"),  nan_neg));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:-e}'"), nan_neg));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:+e}'"), nan_neg));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{: e}'"), nan_neg));

	// *** alternate form **
	// When precision is zero there's no decimal point except when the alternate form is specified.
	VERIFY(SV("answer is '0e+00'")  == hamon::format(SV("answer is '{:.0e}'"),  F(0)));
	VERIFY(SV("answer is '0.e+00'") == hamon::format(SV("answer is '{:#.0e}'"), F(0)));

	VERIFY(SV("answer is '0.000000e+00'") == hamon::format(SV("answer is '{:#e}'"), F(0)));
	VERIFY(SV("answer is '2.500000e+00'") == hamon::format(SV("answer is '{:#e}'"), F(2.5)));

	VERIFY(SV("answer is 'inf'")  == hamon::format(SV("answer is '{:#e}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:#e}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is 'nan'")  == hamon::format(SV("answer is '{:#e}'"), nan_pos));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:#e}'"), nan_neg));

	// *** zero-padding & width ***
	VERIFY(SV("answer is '3.125000e-02'")  == hamon::format(SV("answer is '{:07e}'"),  0.03125));
	VERIFY(SV("answer is '+3.125000e-02'") == hamon::format(SV("answer is '{:+07e}'"), 0.03125));
	VERIFY(SV("answer is '+3.125000e-02'") == hamon::format(SV("answer is '{:+08e}'"), 0.03125));
	VERIFY(SV("answer is '+3.125000e-02'") == hamon::format(SV("answer is '{:+09e}'"), 0.03125));

	VERIFY(SV("answer is '003.125000e-02'") == hamon::format(SV("answer is '{:014e}'"),  0.03125));
	VERIFY(SV("answer is '003.125000e-02'") == hamon::format(SV("answer is '{:-014e}'"), 0.03125));
	VERIFY(SV("answer is '+03.125000e-02'") == hamon::format(SV("answer is '{:+014e}'"), 0.03125));
	VERIFY(SV("answer is ' 03.125000e-02'") == hamon::format(SV("answer is '{: 014e}'"), 0.03125));

	VERIFY(SV("answer is '       inf'") == hamon::format(SV("answer is '{:010e}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '       inf'") == hamon::format(SV("answer is '{:-010e}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      +inf'") == hamon::format(SV("answer is '{:+010e}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '       inf'") == hamon::format(SV("answer is '{: 010e}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{:010e}'"),  -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{:-010e}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{:+010e}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{: 010e}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '       nan'") == hamon::format(SV("answer is '{:010e}'"),  nan_pos));
	VERIFY(SV("answer is '       nan'") == hamon::format(SV("answer is '{:-010e}'"), nan_pos));
	VERIFY(SV("answer is '      +nan'") == hamon::format(SV("answer is '{:+010e}'"), nan_pos));
	VERIFY(SV("answer is '       nan'") == hamon::format(SV("answer is '{: 010e}'"), nan_pos));

	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{:010e}'"),  nan_neg));
	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{:-010e}'"), nan_neg));
	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{:+010e}'"), nan_neg));
	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{: 010e}'"), nan_neg));

	// *** precision ***
	VERIFY(SV("answer is '3e-02'")            == hamon::format(SV("answer is '{:.0e}'"),  0.03125));
	VERIFY(SV("answer is '3.1e-02'")          == hamon::format(SV("answer is '{:.1e}'"),  0.03125));
	VERIFY(SV("answer is '3.125e-02'")        == hamon::format(SV("answer is '{:.3e}'"),  0.03125));
	VERIFY(SV("answer is '3.1250000000e-02'") == hamon::format(SV("answer is '{:.10e}'"), 0.03125));

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp
	return true;
}

template <typename CharT, typename F>
/*HAMON_CXX20_CONSTEXPR*/ bool test_floating_point_scientific_upper_case()
{
	auto nan_pos = hamon::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	VERIFY(SV("answer is '   2.500000E-01'") == hamon::format(SV("answer is '{:15E}'"),  F(0.25)));
	VERIFY(SV("answer is '   2.500000E-01'") == hamon::format(SV("answer is '{:>15E}'"), F(0.25)));
	VERIFY(SV("answer is '2.500000E-01   '") == hamon::format(SV("answer is '{:<15E}'"), F(0.25)));
	VERIFY(SV("answer is ' 2.500000E-01  '") == hamon::format(SV("answer is '{:^15E}'"), F(0.25)));

	VERIFY(SV("answer is '---1.250000E-01'") == hamon::format(SV("answer is '{:->15E}'"), F(125e-3)));
	VERIFY(SV("answer is '1.250000E-01---'") == hamon::format(SV("answer is '{:-<15E}'"), F(125e-3)));
	VERIFY(SV("answer is '-1.250000E-01--'") == hamon::format(SV("answer is '{:-^15E}'"), F(125e-3)));

	VERIFY(SV("answer is '***INF'") == hamon::format(SV("answer is '{:*>6E}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is 'INF***'") == hamon::format(SV("answer is '{:*<6E}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '*INF**'") == hamon::format(SV("answer is '{:*^6E}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '###-INF'") == hamon::format(SV("answer is '{:#>7E}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-INF###'") == hamon::format(SV("answer is '{:#<7E}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '#-INF##'") == hamon::format(SV("answer is '{:#^7E}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '^^^NAN'") == hamon::format(SV("answer is '{:^>6E}'"), nan_pos));
	VERIFY(SV("answer is 'NAN^^^'") == hamon::format(SV("answer is '{:^<6E}'"), nan_pos));
	VERIFY(SV("answer is '^NAN^^'") == hamon::format(SV("answer is '{:^^6E}'"), nan_pos));

	VERIFY(SV("answer is '000-NAN'") == hamon::format(SV("answer is '{:0>7E}'"), nan_neg));
	VERIFY(SV("answer is '-NAN000'") == hamon::format(SV("answer is '{:0<7E}'"), nan_neg));
	VERIFY(SV("answer is '0-NAN00'") == hamon::format(SV("answer is '{:0^7E}'"), nan_neg));

	// Test whether zero padding is ignored
	VERIFY(SV("answer is '   2.500000E-01'") == hamon::format(SV("answer is '{:>015E}'"), F(0.25)));
	VERIFY(SV("answer is '2.500000E-01   '") == hamon::format(SV("answer is '{:<015E}'"), F(0.25)));
	VERIFY(SV("answer is ' 2.500000E-01  '") == hamon::format(SV("answer is '{:^015E}'"), F(0.25)));

	// *** Sign ***
	VERIFY(SV("answer is '0.000000E+00'")  == hamon::format(SV("answer is '{:E}'"),  F(0)));
	VERIFY(SV("answer is '0.000000E+00'")  == hamon::format(SV("answer is '{:-E}'"), F(0)));
	VERIFY(SV("answer is '+0.000000E+00'") == hamon::format(SV("answer is '{:+E}'"), F(0)));
	VERIFY(SV("answer is ' 0.000000E+00'") == hamon::format(SV("answer is '{: E}'"), F(0)));

	VERIFY(SV("answer is '-0.000000E+00'") == hamon::format(SV("answer is '{:E}'"),  F(-0.)));
	VERIFY(SV("answer is '-0.000000E+00'") == hamon::format(SV("answer is '{:-E}'"), F(-0.)));
	VERIFY(SV("answer is '-0.000000E+00'") == hamon::format(SV("answer is '{:+E}'"), F(-0.)));
	VERIFY(SV("answer is '-0.000000E+00'") == hamon::format(SV("answer is '{: E}'"), F(-0.)));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	VERIFY(SV("answer is 'INF'")  == hamon::format(SV("answer is '{:E}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is 'INF'")  == hamon::format(SV("answer is '{:-E}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '+INF'") == hamon::format(SV("answer is '{:+E}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is ' INF'") == hamon::format(SV("answer is '{: E}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '-INF'") == hamon::format(SV("answer is '{:E}'"),  -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-INF'") == hamon::format(SV("answer is '{:-E}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-INF'") == hamon::format(SV("answer is '{:+E}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-INF'") == hamon::format(SV("answer is '{: E}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is 'NAN'")  == hamon::format(SV("answer is '{:E}'"),  nan_pos));
	VERIFY(SV("answer is 'NAN'")  == hamon::format(SV("answer is '{:-E}'"), nan_pos));
	VERIFY(SV("answer is '+NAN'") == hamon::format(SV("answer is '{:+E}'"), nan_pos));
	VERIFY(SV("answer is ' NAN'") == hamon::format(SV("answer is '{: E}'"), nan_pos));

	VERIFY(SV("answer is '-NAN'") == hamon::format(SV("answer is '{:E}'"),  nan_neg));
	VERIFY(SV("answer is '-NAN'") == hamon::format(SV("answer is '{:-E}'"), nan_neg));
	VERIFY(SV("answer is '-NAN'") == hamon::format(SV("answer is '{:+E}'"), nan_neg));
	VERIFY(SV("answer is '-NAN'") == hamon::format(SV("answer is '{: E}'"), nan_neg));

	// *** alternate form **
	// When precision is zero there's no decimal point except when the alternate form is specified.
	VERIFY(SV("answer is '0E+00'")  == hamon::format(SV("answer is '{:.0E}'"),  F(0)));
	VERIFY(SV("answer is '0.E+00'") == hamon::format(SV("answer is '{:#.0E}'"), F(0)));

	VERIFY(SV("answer is '0.000000E+00'") == hamon::format(SV("answer is '{:#E}'"), F(0)));
	VERIFY(SV("answer is '2.500000E+00'") == hamon::format(SV("answer is '{:#E}'"), F(2.5)));

	VERIFY(SV("answer is 'INF'")  == hamon::format(SV("answer is '{:#E}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-INF'") == hamon::format(SV("answer is '{:#E}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is 'NAN'")  == hamon::format(SV("answer is '{:#E}'"), nan_pos));
	VERIFY(SV("answer is '-NAN'") == hamon::format(SV("answer is '{:#E}'"), nan_neg));

	// *** zero-padding & width ***
	VERIFY(SV("answer is '3.125000E-02'")  == hamon::format(SV("answer is '{:07E}'"),  0.03125));
	VERIFY(SV("answer is '+3.125000E-02'") == hamon::format(SV("answer is '{:+07E}'"), 0.03125));
	VERIFY(SV("answer is '+3.125000E-02'") == hamon::format(SV("answer is '{:+08E}'"), 0.03125));
	VERIFY(SV("answer is '+3.125000E-02'") == hamon::format(SV("answer is '{:+09E}'"), 0.03125));

	VERIFY(SV("answer is '003.125000E-02'") == hamon::format(SV("answer is '{:014E}'"),  0.03125));
	VERIFY(SV("answer is '003.125000E-02'") == hamon::format(SV("answer is '{:-014E}'"), 0.03125));
	VERIFY(SV("answer is '+03.125000E-02'") == hamon::format(SV("answer is '{:+014E}'"), 0.03125));
	VERIFY(SV("answer is ' 03.125000E-02'") == hamon::format(SV("answer is '{: 014E}'"), 0.03125));

	VERIFY(SV("answer is '       INF'") == hamon::format(SV("answer is '{:010E}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '       INF'") == hamon::format(SV("answer is '{:-010E}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      +INF'") == hamon::format(SV("answer is '{:+010E}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '       INF'") == hamon::format(SV("answer is '{: 010E}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '      -INF'") == hamon::format(SV("answer is '{:010E}'"),  -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -INF'") == hamon::format(SV("answer is '{:-010E}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -INF'") == hamon::format(SV("answer is '{:+010E}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -INF'") == hamon::format(SV("answer is '{: 010E}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '       NAN'") == hamon::format(SV("answer is '{:010E}'"),  nan_pos));
	VERIFY(SV("answer is '       NAN'") == hamon::format(SV("answer is '{:-010E}'"), nan_pos));
	VERIFY(SV("answer is '      +NAN'") == hamon::format(SV("answer is '{:+010E}'"), nan_pos));
	VERIFY(SV("answer is '       NAN'") == hamon::format(SV("answer is '{: 010E}'"), nan_pos));

	VERIFY(SV("answer is '      -NAN'") == hamon::format(SV("answer is '{:010E}'"),  nan_neg));
	VERIFY(SV("answer is '      -NAN'") == hamon::format(SV("answer is '{:-010E}'"), nan_neg));
	VERIFY(SV("answer is '      -NAN'") == hamon::format(SV("answer is '{:+010E}'"), nan_neg));
	VERIFY(SV("answer is '      -NAN'") == hamon::format(SV("answer is '{: 010E}'"), nan_neg));

	// *** precision ***
	VERIFY(SV("answer is '3E-02'")            == hamon::format(SV("answer is '{:.0E}'"),  0.03125));
	VERIFY(SV("answer is '3.1E-02'")          == hamon::format(SV("answer is '{:.1E}'"),  0.03125));
	VERIFY(SV("answer is '3.125E-02'")        == hamon::format(SV("answer is '{:.3E}'"),  0.03125));
	VERIFY(SV("answer is '3.1250000000E-02'") == hamon::format(SV("answer is '{:.10E}'"), 0.03125));

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp
	return true;
}

template <typename CharT, typename F>
/*HAMON_CXX20_CONSTEXPR*/ bool test_floating_point_fixed_lower_case()
{
	auto nan_pos = hamon::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	VERIFY(SV("answer is '   0.250000'") == hamon::format(SV("answer is '{:11f}'"),  F(0.25)));
	VERIFY(SV("answer is '   0.250000'") == hamon::format(SV("answer is '{:>11f}'"), F(0.25)));
	VERIFY(SV("answer is '0.250000   '") == hamon::format(SV("answer is '{:<11f}'"), F(0.25)));
	VERIFY(SV("answer is ' 0.250000  '") == hamon::format(SV("answer is '{:^11f}'"), F(0.25)));

	VERIFY(SV("answer is '---0.125000'") == hamon::format(SV("answer is '{:->11f}'"), F(125e-3)));
	VERIFY(SV("answer is '0.125000---'") == hamon::format(SV("answer is '{:-<11f}'"), F(125e-3)));
	VERIFY(SV("answer is '-0.125000--'") == hamon::format(SV("answer is '{:-^11f}'"), F(125e-3)));

	VERIFY(SV("answer is '***inf'") == hamon::format(SV("answer is '{:*>6f}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is 'inf***'") == hamon::format(SV("answer is '{:*<6f}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '*inf**'") == hamon::format(SV("answer is '{:*^6f}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '###-inf'") == hamon::format(SV("answer is '{:#>7f}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf###'") == hamon::format(SV("answer is '{:#<7f}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '#-inf##'") == hamon::format(SV("answer is '{:#^7f}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '^^^nan'") == hamon::format(SV("answer is '{:^>6f}'"), nan_pos));
	VERIFY(SV("answer is 'nan^^^'") == hamon::format(SV("answer is '{:^<6f}'"), nan_pos));
	VERIFY(SV("answer is '^nan^^'") == hamon::format(SV("answer is '{:^^6f}'"), nan_pos));

	VERIFY(SV("answer is '000-nan'") == hamon::format(SV("answer is '{:0>7f}'"), nan_neg));
	VERIFY(SV("answer is '-nan000'") == hamon::format(SV("answer is '{:0<7f}'"), nan_neg));
	VERIFY(SV("answer is '0-nan00'") == hamon::format(SV("answer is '{:0^7f}'"), nan_neg));

	// Test whether zero padding is ignored
	VERIFY(SV("answer is '   0.250000'") == hamon::format(SV("answer is '{:>011f}'"), F(0.25)));
	VERIFY(SV("answer is '0.250000   '") == hamon::format(SV("answer is '{:<011f}'"), F(0.25)));
	VERIFY(SV("answer is ' 0.250000  '") == hamon::format(SV("answer is '{:^011f}'"), F(0.25)));

	// *** Sign ***
	VERIFY(SV("answer is '0.000000'")  == hamon::format(SV("answer is '{:f}'"),  F(0)));
	VERIFY(SV("answer is '0.000000'")  == hamon::format(SV("answer is '{:-f}'"), F(0)));
	VERIFY(SV("answer is '+0.000000'") == hamon::format(SV("answer is '{:+f}'"), F(0)));
	VERIFY(SV("answer is ' 0.000000'") == hamon::format(SV("answer is '{: f}'"), F(0)));

	VERIFY(SV("answer is '-0.000000'") == hamon::format(SV("answer is '{:f}'"),  F(-0.)));
	VERIFY(SV("answer is '-0.000000'") == hamon::format(SV("answer is '{:-f}'"), F(-0.)));
	VERIFY(SV("answer is '-0.000000'") == hamon::format(SV("answer is '{:+f}'"), F(-0.)));
	VERIFY(SV("answer is '-0.000000'") == hamon::format(SV("answer is '{: f}'"), F(-0.)));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	VERIFY(SV("answer is 'inf'")  == hamon::format(SV("answer is '{:f}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is 'inf'")  == hamon::format(SV("answer is '{:-f}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '+inf'") == hamon::format(SV("answer is '{:+f}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is ' inf'") == hamon::format(SV("answer is '{: f}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:f}'"),  -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:-f}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:+f}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{: f}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is 'nan'")  == hamon::format(SV("answer is '{:f}'"),  nan_pos));
	VERIFY(SV("answer is 'nan'")  == hamon::format(SV("answer is '{:-f}'"), nan_pos));
	VERIFY(SV("answer is '+nan'") == hamon::format(SV("answer is '{:+f}'"), nan_pos));
	VERIFY(SV("answer is ' nan'") == hamon::format(SV("answer is '{: f}'"), nan_pos));

	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:f}'"),  nan_neg));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:-f}'"), nan_neg));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:+f}'"), nan_neg));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{: f}'"), nan_neg));

	// *** alternate form **
	// When precision is zero there's no decimal point except when the alternate form is specified.
	VERIFY(SV("answer is '0'")  == hamon::format(SV("answer is '{:.0f}'"),  F(0)));
	VERIFY(SV("answer is '0.'") == hamon::format(SV("answer is '{:#.0f}'"), F(0)));

	VERIFY(SV("answer is '0.000000'") == hamon::format(SV("answer is '{:#f}'"), F(0)));
	VERIFY(SV("answer is '2.500000'") == hamon::format(SV("answer is '{:#f}'"), F(2.5)));

	VERIFY(SV("answer is 'inf'")  == hamon::format(SV("answer is '{:#f}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:#f}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is 'nan'")  == hamon::format(SV("answer is '{:#f}'"), nan_pos));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:#f}'"), nan_neg));

	// *** zero-padding & width ***
	VERIFY(SV("answer is '0.031250'")  == hamon::format(SV("answer is '{:07f}'"),  0.03125));
	VERIFY(SV("answer is '+0.031250'") == hamon::format(SV("answer is '{:+07f}'"), 0.03125));
	VERIFY(SV("answer is '+0.031250'") == hamon::format(SV("answer is '{:+08f}'"), 0.03125));
	VERIFY(SV("answer is '+0.031250'") == hamon::format(SV("answer is '{:+09f}'"), 0.03125));

	VERIFY(SV("answer is '000.031250'") == hamon::format(SV("answer is '{:010f}'"),  0.03125));
	VERIFY(SV("answer is '000.031250'") == hamon::format(SV("answer is '{:-010f}'"), 0.03125));
	VERIFY(SV("answer is '+00.031250'") == hamon::format(SV("answer is '{:+010f}'"), 0.03125));
	VERIFY(SV("answer is ' 00.031250'") == hamon::format(SV("answer is '{: 010f}'"), 0.03125));

	VERIFY(SV("answer is '       inf'") == hamon::format(SV("answer is '{:010f}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '       inf'") == hamon::format(SV("answer is '{:-010f}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      +inf'") == hamon::format(SV("answer is '{:+010f}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '       inf'") == hamon::format(SV("answer is '{: 010f}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{:010f}'"),  -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{:-010f}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{:+010f}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{: 010f}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '       nan'") == hamon::format(SV("answer is '{:010f}'"),  nan_pos));
	VERIFY(SV("answer is '       nan'") == hamon::format(SV("answer is '{:-010f}'"), nan_pos));
	VERIFY(SV("answer is '      +nan'") == hamon::format(SV("answer is '{:+010f}'"), nan_pos));
	VERIFY(SV("answer is '       nan'") == hamon::format(SV("answer is '{: 010f}'"), nan_pos));

	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{:010f}'"),  nan_neg));
	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{:-010f}'"), nan_neg));
	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{:+010f}'"), nan_neg));
	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{: 010f}'"), nan_neg));

	// *** precision ***
	VERIFY(SV("answer is '0'")            == hamon::format(SV("answer is '{:.0f}'"),  0.03125));
	VERIFY(SV("answer is '0.0'")          == hamon::format(SV("answer is '{:.1f}'"),  0.03125));
	VERIFY(SV("answer is '0.03125'")      == hamon::format(SV("answer is '{:.5f}'"),  0.03125));
	VERIFY(SV("answer is '0.0312500000'") == hamon::format(SV("answer is '{:.10f}'"), 0.03125));

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp
	return true;
}

template <typename CharT, typename F>
/*HAMON_CXX20_CONSTEXPR*/ bool test_floating_point_fixed_upper_case()
{
	auto nan_pos = hamon::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	VERIFY(SV("answer is '   0.250000'") == hamon::format(SV("answer is '{:11F}'"),  F(0.25)));
	VERIFY(SV("answer is '   0.250000'") == hamon::format(SV("answer is '{:>11F}'"), F(0.25)));
	VERIFY(SV("answer is '0.250000   '") == hamon::format(SV("answer is '{:<11F}'"), F(0.25)));
	VERIFY(SV("answer is ' 0.250000  '") == hamon::format(SV("answer is '{:^11F}'"), F(0.25)));

	VERIFY(SV("answer is '---0.125000'") == hamon::format(SV("answer is '{:->11F}'"), F(125e-3)));
	VERIFY(SV("answer is '0.125000---'") == hamon::format(SV("answer is '{:-<11F}'"), F(125e-3)));
	VERIFY(SV("answer is '-0.125000--'") == hamon::format(SV("answer is '{:-^11F}'"), F(125e-3)));

	VERIFY(SV("answer is '***INF'") == hamon::format(SV("answer is '{:*>6F}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is 'INF***'") == hamon::format(SV("answer is '{:*<6F}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '*INF**'") == hamon::format(SV("answer is '{:*^6F}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '###-INF'") == hamon::format(SV("answer is '{:#>7F}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-INF###'") == hamon::format(SV("answer is '{:#<7F}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '#-INF##'") == hamon::format(SV("answer is '{:#^7F}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '^^^NAN'") == hamon::format(SV("answer is '{:^>6F}'"), nan_pos));
	VERIFY(SV("answer is 'NAN^^^'") == hamon::format(SV("answer is '{:^<6F}'"), nan_pos));
	VERIFY(SV("answer is '^NAN^^'") == hamon::format(SV("answer is '{:^^6F}'"), nan_pos));

	VERIFY(SV("answer is '000-NAN'") == hamon::format(SV("answer is '{:0>7F}'"), nan_neg));
	VERIFY(SV("answer is '-NAN000'") == hamon::format(SV("answer is '{:0<7F}'"), nan_neg));
	VERIFY(SV("answer is '0-NAN00'") == hamon::format(SV("answer is '{:0^7F}'"), nan_neg));

	// Test whether zero padding is ignored
	VERIFY(SV("answer is '   0.250000'") == hamon::format(SV("answer is '{:>011F}'"), F(0.25)));
	VERIFY(SV("answer is '0.250000   '") == hamon::format(SV("answer is '{:<011F}'"), F(0.25)));
	VERIFY(SV("answer is ' 0.250000  '") == hamon::format(SV("answer is '{:^011F}'"), F(0.25)));

	// *** Sign ***
	VERIFY(SV("answer is '0.000000'")  == hamon::format(SV("answer is '{:F}'"),  F(0)));
	VERIFY(SV("answer is '0.000000'")  == hamon::format(SV("answer is '{:-F}'"), F(0)));
	VERIFY(SV("answer is '+0.000000'") == hamon::format(SV("answer is '{:+F}'"), F(0)));
	VERIFY(SV("answer is ' 0.000000'") == hamon::format(SV("answer is '{: F}'"), F(0)));

	VERIFY(SV("answer is '-0.000000'") == hamon::format(SV("answer is '{:F}'"),  F(-0.)));
	VERIFY(SV("answer is '-0.000000'") == hamon::format(SV("answer is '{:-F}'"), F(-0.)));
	VERIFY(SV("answer is '-0.000000'") == hamon::format(SV("answer is '{:+F}'"), F(-0.)));
	VERIFY(SV("answer is '-0.000000'") == hamon::format(SV("answer is '{: F}'"), F(-0.)));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	VERIFY(SV("answer is 'INF'")  == hamon::format(SV("answer is '{:F}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is 'INF'")  == hamon::format(SV("answer is '{:-F}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '+INF'") == hamon::format(SV("answer is '{:+F}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is ' INF'") == hamon::format(SV("answer is '{: F}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '-INF'") == hamon::format(SV("answer is '{:F}'"),  -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-INF'") == hamon::format(SV("answer is '{:-F}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-INF'") == hamon::format(SV("answer is '{:+F}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-INF'") == hamon::format(SV("answer is '{: F}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is 'NAN'")  == hamon::format(SV("answer is '{:F}'"),  nan_pos));
	VERIFY(SV("answer is 'NAN'")  == hamon::format(SV("answer is '{:-F}'"), nan_pos));
	VERIFY(SV("answer is '+NAN'") == hamon::format(SV("answer is '{:+F}'"), nan_pos));
	VERIFY(SV("answer is ' NAN'") == hamon::format(SV("answer is '{: F}'"), nan_pos));

	VERIFY(SV("answer is '-NAN'") == hamon::format(SV("answer is '{:F}'"),  nan_neg));
	VERIFY(SV("answer is '-NAN'") == hamon::format(SV("answer is '{:-F}'"), nan_neg));
	VERIFY(SV("answer is '-NAN'") == hamon::format(SV("answer is '{:+F}'"), nan_neg));
	VERIFY(SV("answer is '-NAN'") == hamon::format(SV("answer is '{: F}'"), nan_neg));

	// *** alternate form **
	// When precision is zero there's no decimal point except when the alternate form is specified.
	VERIFY(SV("answer is '0'")  == hamon::format(SV("answer is '{:.0F}'"),  F(0)));
	VERIFY(SV("answer is '0.'") == hamon::format(SV("answer is '{:#.0F}'"), F(0)));

	VERIFY(SV("answer is '0.000000'") == hamon::format(SV("answer is '{:#F}'"), F(0)));
	VERIFY(SV("answer is '2.500000'") == hamon::format(SV("answer is '{:#F}'"), F(2.5)));

	VERIFY(SV("answer is 'INF'")  == hamon::format(SV("answer is '{:#F}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-INF'") == hamon::format(SV("answer is '{:#F}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is 'NAN'")  == hamon::format(SV("answer is '{:#F}'"), nan_pos));
	VERIFY(SV("answer is '-NAN'") == hamon::format(SV("answer is '{:#F}'"), nan_neg));

	// *** zero-padding & width ***
	VERIFY(SV("answer is '0.031250'")  == hamon::format(SV("answer is '{:07F}'"),  0.03125));
	VERIFY(SV("answer is '+0.031250'") == hamon::format(SV("answer is '{:+07F}'"), 0.03125));
	VERIFY(SV("answer is '+0.031250'") == hamon::format(SV("answer is '{:+08F}'"), 0.03125));
	VERIFY(SV("answer is '+0.031250'") == hamon::format(SV("answer is '{:+09F}'"), 0.03125));

	VERIFY(SV("answer is '000.031250'") == hamon::format(SV("answer is '{:010F}'"),  0.03125));
	VERIFY(SV("answer is '000.031250'") == hamon::format(SV("answer is '{:-010F}'"), 0.03125));
	VERIFY(SV("answer is '+00.031250'") == hamon::format(SV("answer is '{:+010F}'"), 0.03125));
	VERIFY(SV("answer is ' 00.031250'") == hamon::format(SV("answer is '{: 010F}'"), 0.03125));

	VERIFY(SV("answer is '       INF'") == hamon::format(SV("answer is '{:010F}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '       INF'") == hamon::format(SV("answer is '{:-010F}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      +INF'") == hamon::format(SV("answer is '{:+010F}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '       INF'") == hamon::format(SV("answer is '{: 010F}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '      -INF'") == hamon::format(SV("answer is '{:010F}'"),  -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -INF'") == hamon::format(SV("answer is '{:-010F}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -INF'") == hamon::format(SV("answer is '{:+010F}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -INF'") == hamon::format(SV("answer is '{: 010F}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '       NAN'") == hamon::format(SV("answer is '{:010F}'"),  nan_pos));
	VERIFY(SV("answer is '       NAN'") == hamon::format(SV("answer is '{:-010F}'"), nan_pos));
	VERIFY(SV("answer is '      +NAN'") == hamon::format(SV("answer is '{:+010F}'"), nan_pos));
	VERIFY(SV("answer is '       NAN'") == hamon::format(SV("answer is '{: 010F}'"), nan_pos));

	VERIFY(SV("answer is '      -NAN'") == hamon::format(SV("answer is '{:010F}'"),  nan_neg));
	VERIFY(SV("answer is '      -NAN'") == hamon::format(SV("answer is '{:-010F}'"), nan_neg));
	VERIFY(SV("answer is '      -NAN'") == hamon::format(SV("answer is '{:+010F}'"), nan_neg));
	VERIFY(SV("answer is '      -NAN'") == hamon::format(SV("answer is '{: 010F}'"), nan_neg));

	// *** precision ***
	VERIFY(SV("answer is '0'")            == hamon::format(SV("answer is '{:.0F}'"),  0.03125));
	VERIFY(SV("answer is '0.0'")          == hamon::format(SV("answer is '{:.1F}'"),  0.03125));
	VERIFY(SV("answer is '0.03125'")      == hamon::format(SV("answer is '{:.5F}'"),  0.03125));
	VERIFY(SV("answer is '0.0312500000'") == hamon::format(SV("answer is '{:.10F}'"), 0.03125));

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp
	return true;
}

template <typename CharT, typename F>
/*HAMON_CXX20_CONSTEXPR*/ bool test_floating_point_general_lower_case()
{
	auto nan_pos = hamon::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	VERIFY(SV("answer is '   0.25'") == hamon::format(SV("answer is '{:7g}'"),  F(0.25)));
	VERIFY(SV("answer is '   0.25'") == hamon::format(SV("answer is '{:>7g}'"), F(0.25)));
	VERIFY(SV("answer is '0.25   '") == hamon::format(SV("answer is '{:<7g}'"), F(0.25)));
	VERIFY(SV("answer is ' 0.25  '") == hamon::format(SV("answer is '{:^7g}'"), F(0.25)));

	VERIFY(SV("answer is '---0.125'") == hamon::format(SV("answer is '{:->8g}'"), F(125e-3)));
	VERIFY(SV("answer is '0.125---'") == hamon::format(SV("answer is '{:-<8g}'"), F(125e-3)));
	VERIFY(SV("answer is '-0.125--'") == hamon::format(SV("answer is '{:-^8g}'"), F(125e-3)));

	VERIFY(SV("answer is '***inf'") == hamon::format(SV("answer is '{:*>6g}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is 'inf***'") == hamon::format(SV("answer is '{:*<6g}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '*inf**'") == hamon::format(SV("answer is '{:*^6g}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '###-inf'") == hamon::format(SV("answer is '{:#>7g}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf###'") == hamon::format(SV("answer is '{:#<7g}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '#-inf##'") == hamon::format(SV("answer is '{:#^7g}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '^^^nan'") == hamon::format(SV("answer is '{:^>6g}'"), nan_pos));
	VERIFY(SV("answer is 'nan^^^'") == hamon::format(SV("answer is '{:^<6g}'"), nan_pos));
	VERIFY(SV("answer is '^nan^^'") == hamon::format(SV("answer is '{:^^6g}'"), nan_pos));

	VERIFY(SV("answer is '000-nan'") == hamon::format(SV("answer is '{:0>7g}'"), nan_neg));
	VERIFY(SV("answer is '-nan000'") == hamon::format(SV("answer is '{:0<7g}'"), nan_neg));
	VERIFY(SV("answer is '0-nan00'") == hamon::format(SV("answer is '{:0^7g}'"), nan_neg));

	// Test whether zero padding is ignored
	VERIFY(SV("answer is '   0.25'") == hamon::format(SV("answer is '{:>07g}'"), F(0.25)));
	VERIFY(SV("answer is '0.25   '") == hamon::format(SV("answer is '{:<07g}'"), F(0.25)));
	VERIFY(SV("answer is ' 0.25  '") == hamon::format(SV("answer is '{:^07g}'"), F(0.25)));

	// *** Sign ***
	VERIFY(SV("answer is '0'")  == hamon::format(SV("answer is '{:g}'"),  F(0)));
	VERIFY(SV("answer is '0'")  == hamon::format(SV("answer is '{:-g}'"), F(0)));
	VERIFY(SV("answer is '+0'") == hamon::format(SV("answer is '{:+g}'"), F(0)));
	VERIFY(SV("answer is ' 0'") == hamon::format(SV("answer is '{: g}'"), F(0)));

	VERIFY(SV("answer is '-0'") == hamon::format(SV("answer is '{:g}'"),  F(-0.)));
	VERIFY(SV("answer is '-0'") == hamon::format(SV("answer is '{:-g}'"), F(-0.)));
	VERIFY(SV("answer is '-0'") == hamon::format(SV("answer is '{:+g}'"), F(-0.)));
	VERIFY(SV("answer is '-0'") == hamon::format(SV("answer is '{: g}'"), F(-0.)));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	VERIFY(SV("answer is 'inf'")  == hamon::format(SV("answer is '{:g}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is 'inf'")  == hamon::format(SV("answer is '{:-g}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '+inf'") == hamon::format(SV("answer is '{:+g}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is ' inf'") == hamon::format(SV("answer is '{: g}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:g}'"),  -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:-g}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:+g}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{: g}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is 'nan'")  == hamon::format(SV("answer is '{:g}'"),  nan_pos));
	VERIFY(SV("answer is 'nan'")  == hamon::format(SV("answer is '{:-g}'"), nan_pos));
	VERIFY(SV("answer is '+nan'") == hamon::format(SV("answer is '{:+g}'"), nan_pos));
	VERIFY(SV("answer is ' nan'") == hamon::format(SV("answer is '{: g}'"), nan_pos));

	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:g}'"),  nan_neg));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:-g}'"), nan_neg));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:+g}'"), nan_neg));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{: g}'"), nan_neg));

	// *** alternate form **
	// When precision is zero there's no decimal point except when the alternate form is specified.
	VERIFY(SV("answer is '0'")  == hamon::format(SV("answer is '{:.0g}'"),  F(0)));
	VERIFY(SV("answer is '0.'") == hamon::format(SV("answer is '{:#.0g}'"), F(0)));

	VERIFY(SV("answer is '0.00000'") == hamon::format(SV("answer is '{:#g}'"), F(0)));
	VERIFY(SV("answer is '2.50000'") == hamon::format(SV("answer is '{:#g}'"), F(2.5)));

	VERIFY(SV("answer is 'inf'")  == hamon::format(SV("answer is '{:#g}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:#g}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is 'nan'")  == hamon::format(SV("answer is '{:#g}'"), nan_pos));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:#g}'"), nan_neg));

	// *** zero-padding & width ***
	VERIFY(SV("answer is '0.03125'")  == hamon::format(SV("answer is '{:06g}'"),  0.03125));
	VERIFY(SV("answer is '+0.03125'") == hamon::format(SV("answer is '{:+06g}'"), 0.03125));
	VERIFY(SV("answer is '+0.03125'") == hamon::format(SV("answer is '{:+07g}'"), 0.03125));
	VERIFY(SV("answer is '+0.03125'") == hamon::format(SV("answer is '{:+08g}'"), 0.03125));

	VERIFY(SV("answer is '000.03125'") == hamon::format(SV("answer is '{:09g}'"),  0.03125));
	VERIFY(SV("answer is '000.03125'") == hamon::format(SV("answer is '{:-09g}'"), 0.03125));
	VERIFY(SV("answer is '+00.03125'") == hamon::format(SV("answer is '{:+09g}'"), 0.03125));
	VERIFY(SV("answer is ' 00.03125'") == hamon::format(SV("answer is '{: 09g}'"), 0.03125));

	VERIFY(SV("answer is '       inf'") == hamon::format(SV("answer is '{:010g}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '       inf'") == hamon::format(SV("answer is '{:-010g}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      +inf'") == hamon::format(SV("answer is '{:+010g}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '       inf'") == hamon::format(SV("answer is '{: 010g}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{:010g}'"),  -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{:-010g}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{:+010g}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{: 010g}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '       nan'") == hamon::format(SV("answer is '{:010g}'"),  nan_pos));
	VERIFY(SV("answer is '       nan'") == hamon::format(SV("answer is '{:-010g}'"), nan_pos));
	VERIFY(SV("answer is '      +nan'") == hamon::format(SV("answer is '{:+010g}'"), nan_pos));
	VERIFY(SV("answer is '       nan'") == hamon::format(SV("answer is '{: 010g}'"), nan_pos));

	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{:010g}'"),  nan_neg));
	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{:-010g}'"), nan_neg));
	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{:+010g}'"), nan_neg));
	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{: 010g}'"), nan_neg));

	// *** precision ***
	VERIFY(SV("answer is '0.03'")    == hamon::format(SV("answer is '{:.0g}'"),  0.03125));
	VERIFY(SV("answer is '0.03'")    == hamon::format(SV("answer is '{:.1g}'"),  0.03125));
	VERIFY(SV("answer is '0.031'")   == hamon::format(SV("answer is '{:.2g}'"),  0.03125));
	VERIFY(SV("answer is '0.0312'")  == hamon::format(SV("answer is '{:.3g}'"),  0.03125));
	VERIFY(SV("answer is '0.03125'") == hamon::format(SV("answer is '{:.4g}'"),  0.03125));
	VERIFY(SV("answer is '0.03125'") == hamon::format(SV("answer is '{:.5g}'"),  0.03125));
	VERIFY(SV("answer is '0.03125'") == hamon::format(SV("answer is '{:.10g}'"), 0.03125));

	// *** precision & alternate form ***

	// Output validated with  printf("%#xg")
	VERIFY(SV("answer is '1.'")      == hamon::format(SV("answer is '{:#.{}g}'"), 1.2, 0));
	VERIFY(SV("answer is '1.'")      == hamon::format(SV("answer is '{:#.{}g}'"), 1.2, 1));
	VERIFY(SV("answer is '1.2'")     == hamon::format(SV("answer is '{:#.{}g}'"), 1.2, 2));
	VERIFY(SV("answer is '1.20'")    == hamon::format(SV("answer is '{:#.{}g}'"), 1.2, 3));
	VERIFY(SV("answer is '1.200'")   == hamon::format(SV("answer is '{:#.{}g}'"), 1.2, 4));
	VERIFY(SV("answer is '1.2000'")  == hamon::format(SV("answer is '{:#.{}g}'"), 1.2, 5));
	VERIFY(SV("answer is '1.20000'") == hamon::format(SV("answer is '{:#.{}g}'"), 1.2, 6));

	VERIFY(SV("answer is '1.e+03'")   == hamon::format(SV("answer is '{:#.{}g}'"), 1200.0, 0));
	VERIFY(SV("answer is '1.e+03'")   == hamon::format(SV("answer is '{:#.{}g}'"), 1200.0, 1));
	VERIFY(SV("answer is '1.2e+03'")  == hamon::format(SV("answer is '{:#.{}g}'"), 1200.0, 2));
	VERIFY(SV("answer is '1.20e+03'") == hamon::format(SV("answer is '{:#.{}g}'"), 1200.0, 3));
	VERIFY(SV("answer is '1200.'")    == hamon::format(SV("answer is '{:#.{}g}'"), 1200.0, 4));
	VERIFY(SV("answer is '1200.0'")   == hamon::format(SV("answer is '{:#.{}g}'"), 1200.0, 5));
	VERIFY(SV("answer is '1200.00'")  == hamon::format(SV("answer is '{:#.{}g}'"), 1200.0, 6));

	VERIFY(SV("answer is '1.e+06'")      == hamon::format(SV("answer is '{:#.{}g}'"), 1200000.0, 0));
	VERIFY(SV("answer is '1.e+06'")      == hamon::format(SV("answer is '{:#.{}g}'"), 1200000.0, 1));
	VERIFY(SV("answer is '1.2e+06'")     == hamon::format(SV("answer is '{:#.{}g}'"), 1200000.0, 2));
	VERIFY(SV("answer is '1.20e+06'")    == hamon::format(SV("answer is '{:#.{}g}'"), 1200000.0, 3));
	VERIFY(SV("answer is '1.200e+06'")   == hamon::format(SV("answer is '{:#.{}g}'"), 1200000.0, 4));
	VERIFY(SV("answer is '1.2000e+06'")  == hamon::format(SV("answer is '{:#.{}g}'"), 1200000.0, 5));
	VERIFY(SV("answer is '1.20000e+06'") == hamon::format(SV("answer is '{:#.{}g}'"), 1200000.0, 6));

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp
	return true;
}

template <typename CharT, typename F>
/*HAMON_CXX20_CONSTEXPR*/ bool test_floating_point_general_upper_case()
{
	auto nan_pos = hamon::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	VERIFY(SV("answer is '   0.25'") == hamon::format(SV("answer is '{:7G}'"),  F(0.25)));
	VERIFY(SV("answer is '   0.25'") == hamon::format(SV("answer is '{:>7G}'"), F(0.25)));
	VERIFY(SV("answer is '0.25   '") == hamon::format(SV("answer is '{:<7G}'"), F(0.25)));
	VERIFY(SV("answer is ' 0.25  '") == hamon::format(SV("answer is '{:^7G}'"), F(0.25)));

	VERIFY(SV("answer is '---0.125'") == hamon::format(SV("answer is '{:->8G}'"), F(125e-3)));
	VERIFY(SV("answer is '0.125---'") == hamon::format(SV("answer is '{:-<8G}'"), F(125e-3)));
	VERIFY(SV("answer is '-0.125--'") == hamon::format(SV("answer is '{:-^8G}'"), F(125e-3)));

	VERIFY(SV("answer is '***INF'") == hamon::format(SV("answer is '{:*>6G}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is 'INF***'") == hamon::format(SV("answer is '{:*<6G}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '*INF**'") == hamon::format(SV("answer is '{:*^6G}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '###-INF'") == hamon::format(SV("answer is '{:#>7G}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-INF###'") == hamon::format(SV("answer is '{:#<7G}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '#-INF##'") == hamon::format(SV("answer is '{:#^7G}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '^^^NAN'") == hamon::format(SV("answer is '{:^>6G}'"), nan_pos));
	VERIFY(SV("answer is 'NAN^^^'") == hamon::format(SV("answer is '{:^<6G}'"), nan_pos));
	VERIFY(SV("answer is '^NAN^^'") == hamon::format(SV("answer is '{:^^6G}'"), nan_pos));

	VERIFY(SV("answer is '000-NAN'") == hamon::format(SV("answer is '{:0>7G}'"), nan_neg));
	VERIFY(SV("answer is '-NAN000'") == hamon::format(SV("answer is '{:0<7G}'"), nan_neg));
	VERIFY(SV("answer is '0-NAN00'") == hamon::format(SV("answer is '{:0^7G}'"), nan_neg));

	// Test whether zero padding is ignored
	VERIFY(SV("answer is '   0.25'") == hamon::format(SV("answer is '{:>07G}'"), F(0.25)));
	VERIFY(SV("answer is '0.25   '") == hamon::format(SV("answer is '{:<07G}'"), F(0.25)));
	VERIFY(SV("answer is ' 0.25  '") == hamon::format(SV("answer is '{:^07G}'"), F(0.25)));

	// *** Sign ***
	VERIFY(SV("answer is '0'")  == hamon::format(SV("answer is '{:G}'"),  F(0)));
	VERIFY(SV("answer is '0'")  == hamon::format(SV("answer is '{:-G}'"), F(0)));
	VERIFY(SV("answer is '+0'") == hamon::format(SV("answer is '{:+G}'"), F(0)));
	VERIFY(SV("answer is ' 0'") == hamon::format(SV("answer is '{: G}'"), F(0)));

	VERIFY(SV("answer is '-0'") == hamon::format(SV("answer is '{:G}'"),  F(-0.)));
	VERIFY(SV("answer is '-0'") == hamon::format(SV("answer is '{:-G}'"), F(-0.)));
	VERIFY(SV("answer is '-0'") == hamon::format(SV("answer is '{:+G}'"), F(-0.)));
	VERIFY(SV("answer is '-0'") == hamon::format(SV("answer is '{: G}'"), F(-0.)));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	VERIFY(SV("answer is 'INF'")  == hamon::format(SV("answer is '{:G}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is 'INF'")  == hamon::format(SV("answer is '{:-G}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '+INF'") == hamon::format(SV("answer is '{:+G}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is ' INF'") == hamon::format(SV("answer is '{: G}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '-INF'") == hamon::format(SV("answer is '{:G}'"),  -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-INF'") == hamon::format(SV("answer is '{:-G}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-INF'") == hamon::format(SV("answer is '{:+G}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-INF'") == hamon::format(SV("answer is '{: G}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is 'NAN'")  == hamon::format(SV("answer is '{:G}'"),  nan_pos));
	VERIFY(SV("answer is 'NAN'")  == hamon::format(SV("answer is '{:-G}'"), nan_pos));
	VERIFY(SV("answer is '+NAN'") == hamon::format(SV("answer is '{:+G}'"), nan_pos));
	VERIFY(SV("answer is ' NAN'") == hamon::format(SV("answer is '{: G}'"), nan_pos));

	VERIFY(SV("answer is '-NAN'") == hamon::format(SV("answer is '{:G}'"),  nan_neg));
	VERIFY(SV("answer is '-NAN'") == hamon::format(SV("answer is '{:-G}'"), nan_neg));
	VERIFY(SV("answer is '-NAN'") == hamon::format(SV("answer is '{:+G}'"), nan_neg));
	VERIFY(SV("answer is '-NAN'") == hamon::format(SV("answer is '{: G}'"), nan_neg));

	// *** alternate form **
	// When precision is zero there's no decimal point except when the alternate form is specified.
	VERIFY(SV("answer is '0'")  == hamon::format(SV("answer is '{:.0G}'"),  F(0)));
	VERIFY(SV("answer is '0.'") == hamon::format(SV("answer is '{:#.0G}'"), F(0)));

	VERIFY(SV("answer is '0.00000'") == hamon::format(SV("answer is '{:#G}'"), F(0)));
	VERIFY(SV("answer is '2.50000'") == hamon::format(SV("answer is '{:#G}'"), F(2.5)));

	VERIFY(SV("answer is 'INF'")  == hamon::format(SV("answer is '{:#G}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-INF'") == hamon::format(SV("answer is '{:#G}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is 'NAN'")  == hamon::format(SV("answer is '{:#G}'"), nan_pos));
	VERIFY(SV("answer is '-NAN'") == hamon::format(SV("answer is '{:#G}'"), nan_neg));

	// *** zero-padding & width ***
	VERIFY(SV("answer is '0.03125'")  == hamon::format(SV("answer is '{:06G}'"),  0.03125));
	VERIFY(SV("answer is '+0.03125'") == hamon::format(SV("answer is '{:+06G}'"), 0.03125));
	VERIFY(SV("answer is '+0.03125'") == hamon::format(SV("answer is '{:+07G}'"), 0.03125));
	VERIFY(SV("answer is '+0.03125'") == hamon::format(SV("answer is '{:+08G}'"), 0.03125));

	VERIFY(SV("answer is '000.03125'") == hamon::format(SV("answer is '{:09G}'"),  0.03125));
	VERIFY(SV("answer is '000.03125'") == hamon::format(SV("answer is '{:-09G}'"), 0.03125));
	VERIFY(SV("answer is '+00.03125'") == hamon::format(SV("answer is '{:+09G}'"), 0.03125));
	VERIFY(SV("answer is ' 00.03125'") == hamon::format(SV("answer is '{: 09G}'"), 0.03125));

	VERIFY(SV("answer is '       INF'") == hamon::format(SV("answer is '{:010G}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '       INF'") == hamon::format(SV("answer is '{:-010G}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      +INF'") == hamon::format(SV("answer is '{:+010G}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '       INF'") == hamon::format(SV("answer is '{: 010G}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '      -INF'") == hamon::format(SV("answer is '{:010G}'"),  -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -INF'") == hamon::format(SV("answer is '{:-010G}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -INF'") == hamon::format(SV("answer is '{:+010G}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -INF'") == hamon::format(SV("answer is '{: 010G}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '       NAN'") == hamon::format(SV("answer is '{:010G}'"),  nan_pos));
	VERIFY(SV("answer is '       NAN'") == hamon::format(SV("answer is '{:-010G}'"), nan_pos));
	VERIFY(SV("answer is '      +NAN'") == hamon::format(SV("answer is '{:+010G}'"), nan_pos));
	VERIFY(SV("answer is '       NAN'") == hamon::format(SV("answer is '{: 010G}'"), nan_pos));

	VERIFY(SV("answer is '      -NAN'") == hamon::format(SV("answer is '{:010G}'"),  nan_neg));
	VERIFY(SV("answer is '      -NAN'") == hamon::format(SV("answer is '{:-010G}'"), nan_neg));
	VERIFY(SV("answer is '      -NAN'") == hamon::format(SV("answer is '{:+010G}'"), nan_neg));
	VERIFY(SV("answer is '      -NAN'") == hamon::format(SV("answer is '{: 010G}'"), nan_neg));

	// *** precision ***
	VERIFY(SV("answer is '0.03'")    == hamon::format(SV("answer is '{:.0G}'"),  0.03125));
	VERIFY(SV("answer is '0.03'")    == hamon::format(SV("answer is '{:.1G}'"),  0.03125));
	VERIFY(SV("answer is '0.031'")   == hamon::format(SV("answer is '{:.2G}'"),  0.03125));
	VERIFY(SV("answer is '0.0312'")  == hamon::format(SV("answer is '{:.3G}'"),  0.03125));
	VERIFY(SV("answer is '0.03125'") == hamon::format(SV("answer is '{:.4G}'"),  0.03125));
	VERIFY(SV("answer is '0.03125'") == hamon::format(SV("answer is '{:.5G}'"),  0.03125));
	VERIFY(SV("answer is '0.03125'") == hamon::format(SV("answer is '{:.10G}'"), 0.03125));

	// *** precision & alternate form ***

	// Output validated with  printf("%#xg")
	VERIFY(SV("answer is '1.'")      == hamon::format(SV("answer is '{:#.{}G}'"), 1.2, 0));
	VERIFY(SV("answer is '1.'")      == hamon::format(SV("answer is '{:#.{}G}'"), 1.2, 1));
	VERIFY(SV("answer is '1.2'")     == hamon::format(SV("answer is '{:#.{}G}'"), 1.2, 2));
	VERIFY(SV("answer is '1.20'")    == hamon::format(SV("answer is '{:#.{}G}'"), 1.2, 3));
	VERIFY(SV("answer is '1.200'")   == hamon::format(SV("answer is '{:#.{}G}'"), 1.2, 4));
	VERIFY(SV("answer is '1.2000'")  == hamon::format(SV("answer is '{:#.{}G}'"), 1.2, 5));
	VERIFY(SV("answer is '1.20000'") == hamon::format(SV("answer is '{:#.{}G}'"), 1.2, 6));

	VERIFY(SV("answer is '1.E+03'")   == hamon::format(SV("answer is '{:#.{}G}'"), 1200.0, 0));
	VERIFY(SV("answer is '1.E+03'")   == hamon::format(SV("answer is '{:#.{}G}'"), 1200.0, 1));
	VERIFY(SV("answer is '1.2E+03'")  == hamon::format(SV("answer is '{:#.{}G}'"), 1200.0, 2));
	VERIFY(SV("answer is '1.20E+03'") == hamon::format(SV("answer is '{:#.{}G}'"), 1200.0, 3));
	VERIFY(SV("answer is '1200.'")    == hamon::format(SV("answer is '{:#.{}G}'"), 1200.0, 4));
	VERIFY(SV("answer is '1200.0'")   == hamon::format(SV("answer is '{:#.{}G}'"), 1200.0, 5));
	VERIFY(SV("answer is '1200.00'")  == hamon::format(SV("answer is '{:#.{}G}'"), 1200.0, 6));

	VERIFY(SV("answer is '1.E+06'")      == hamon::format(SV("answer is '{:#.{}G}'"), 1200000.0, 0));
	VERIFY(SV("answer is '1.E+06'")      == hamon::format(SV("answer is '{:#.{}G}'"), 1200000.0, 1));
	VERIFY(SV("answer is '1.2E+06'")     == hamon::format(SV("answer is '{:#.{}G}'"), 1200000.0, 2));
	VERIFY(SV("answer is '1.20E+06'")    == hamon::format(SV("answer is '{:#.{}G}'"), 1200000.0, 3));
	VERIFY(SV("answer is '1.200E+06'")   == hamon::format(SV("answer is '{:#.{}G}'"), 1200000.0, 4));
	VERIFY(SV("answer is '1.2000E+06'")  == hamon::format(SV("answer is '{:#.{}G}'"), 1200000.0, 5));
	VERIFY(SV("answer is '1.20000E+06'") == hamon::format(SV("answer is '{:#.{}G}'"), 1200000.0, 6));

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp
	return true;
}

template <typename CharT, typename F>
/*HAMON_CXX20_CONSTEXPR*/ bool test_floating_point_default()
{
	auto nan_pos = hamon::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	VERIFY(SV("answer is '   0.25'") == hamon::format(SV("answer is '{:7}'"),  F(0.25)));
	VERIFY(SV("answer is '   0.25'") == hamon::format(SV("answer is '{:>7}'"), F(0.25)));
	VERIFY(SV("answer is '0.25   '") == hamon::format(SV("answer is '{:<7}'"), F(0.25)));
	VERIFY(SV("answer is ' 0.25  '") == hamon::format(SV("answer is '{:^7}'"), F(0.25)));

	VERIFY(SV("answer is '---0.125'") == hamon::format(SV("answer is '{:->8}'"), F(125e-3)));
	VERIFY(SV("answer is '0.125---'") == hamon::format(SV("answer is '{:-<8}'"), F(125e-3)));
	VERIFY(SV("answer is '-0.125--'") == hamon::format(SV("answer is '{:-^8}'"), F(125e-3)));

	VERIFY(SV("answer is '***inf'") == hamon::format(SV("answer is '{:*>6}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is 'inf***'") == hamon::format(SV("answer is '{:*<6}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '*inf**'") == hamon::format(SV("answer is '{:*^6}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '###-inf'") == hamon::format(SV("answer is '{:#>7}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf###'") == hamon::format(SV("answer is '{:#<7}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '#-inf##'") == hamon::format(SV("answer is '{:#^7}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '^^^nan'") == hamon::format(SV("answer is '{:^>6}'"), nan_pos));
	VERIFY(SV("answer is 'nan^^^'") == hamon::format(SV("answer is '{:^<6}'"), nan_pos));
	VERIFY(SV("answer is '^nan^^'") == hamon::format(SV("answer is '{:^^6}'"), nan_pos));

	VERIFY(SV("answer is '000-nan'") == hamon::format(SV("answer is '{:0>7}'"), nan_neg));
	VERIFY(SV("answer is '-nan000'") == hamon::format(SV("answer is '{:0<7}'"), nan_neg));
	VERIFY(SV("answer is '0-nan00'") == hamon::format(SV("answer is '{:0^7}'"), nan_neg));

	// Test whether zero padding is ignored
	VERIFY(SV("answer is '   0.25'") == hamon::format(SV("answer is '{:>07}'"), F(0.25)));
	VERIFY(SV("answer is '0.25   '") == hamon::format(SV("answer is '{:<07}'"), F(0.25)));
	VERIFY(SV("answer is ' 0.25  '") == hamon::format(SV("answer is '{:^07}'"), F(0.25)));

	// *** Sign ***
	VERIFY(SV("answer is '0'")  == hamon::format(SV("answer is '{:}'"),  F(0)));
	VERIFY(SV("answer is '0'")  == hamon::format(SV("answer is '{:-}'"), F(0)));
	VERIFY(SV("answer is '+0'") == hamon::format(SV("answer is '{:+}'"), F(0)));
	VERIFY(SV("answer is ' 0'") == hamon::format(SV("answer is '{: }'"), F(0)));

	VERIFY(SV("answer is '-0'") == hamon::format(SV("answer is '{:}'"),  F(-0.)));
	VERIFY(SV("answer is '-0'") == hamon::format(SV("answer is '{:-}'"), F(-0.)));
	VERIFY(SV("answer is '-0'") == hamon::format(SV("answer is '{:+}'"), F(-0.)));
	VERIFY(SV("answer is '-0'") == hamon::format(SV("answer is '{: }'"), F(-0.)));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	VERIFY(SV("answer is 'inf'")  == hamon::format(SV("answer is '{:}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is 'inf'")  == hamon::format(SV("answer is '{:-}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '+inf'") == hamon::format(SV("answer is '{:+}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is ' inf'") == hamon::format(SV("answer is '{: }'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:}'"),  -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:-}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:+}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{: }'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is 'nan'")  == hamon::format(SV("answer is '{:}'"),  nan_pos));
	VERIFY(SV("answer is 'nan'")  == hamon::format(SV("answer is '{:-}'"), nan_pos));
	VERIFY(SV("answer is '+nan'") == hamon::format(SV("answer is '{:+}'"), nan_pos));
	VERIFY(SV("answer is ' nan'") == hamon::format(SV("answer is '{: }'"), nan_pos));

	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:}'"),  nan_neg));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:-}'"), nan_neg));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:+}'"), nan_neg));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{: }'"), nan_neg));

	// *** alternate form ***
	VERIFY(SV("answer is '0.'")  == hamon::format(SV("answer is '{:#}'"), F(0)));
	VERIFY(SV("answer is '2.5'") == hamon::format(SV("answer is '{:#}'"), F(2.5)));

	VERIFY(SV("answer is 'inf'")  == hamon::format(SV("answer is '{:#}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:#}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is 'nan'")  == hamon::format(SV("answer is '{:#}'"), nan_pos));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:#}'"), nan_neg));

	// *** zero-padding & width ***
	VERIFY(SV("answer is '0.03125'")   == hamon::format(SV("answer is '{:07}'"),  0.03125));
	VERIFY(SV("answer is '+0.03125'")  == hamon::format(SV("answer is '{:+07}'"), 0.03125));
	VERIFY(SV("answer is '+0.03125'")  == hamon::format(SV("answer is '{:+08}'"), 0.03125));
	VERIFY(SV("answer is '+00.03125'") == hamon::format(SV("answer is '{:+09}'"), 0.03125));

	VERIFY(SV("answer is '0000.03125'") == hamon::format(SV("answer is '{:010}'"),  0.03125));
	VERIFY(SV("answer is '0000.03125'") == hamon::format(SV("answer is '{:-010}'"), 0.03125));
	VERIFY(SV("answer is '+000.03125'") == hamon::format(SV("answer is '{:+010}'"), 0.03125));
	VERIFY(SV("answer is ' 000.03125'") == hamon::format(SV("answer is '{: 010}'"), 0.03125));

	VERIFY(SV("answer is '       inf'") == hamon::format(SV("answer is '{:010}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '       inf'") == hamon::format(SV("answer is '{:-010}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      +inf'") == hamon::format(SV("answer is '{:+010}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '       inf'") == hamon::format(SV("answer is '{: 010}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{:010}'"),  -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{:-010}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{:+010}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{: 010}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '       nan'") == hamon::format(SV("answer is '{:010}'"),  nan_pos));
	VERIFY(SV("answer is '       nan'") == hamon::format(SV("answer is '{:-010}'"), nan_pos));
	VERIFY(SV("answer is '      +nan'") == hamon::format(SV("answer is '{:+010}'"), nan_pos));
	VERIFY(SV("answer is '       nan'") == hamon::format(SV("answer is '{: 010}'"), nan_pos));

	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{:010}'"),  nan_neg));
	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{:-010}'"), nan_neg));
	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{:+010}'"), nan_neg));
	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{: 010}'"), nan_neg));

	// *** precision ***
	// See format_test_floating_point_default_precision

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp
	return true;
}

template <typename CharT, typename F>
/*HAMON_CXX20_CONSTEXPR*/ bool test_floating_point_default_precision()
{
	auto nan_pos = hamon::numeric_limits<F>::quiet_NaN();                          // "nan"
	auto nan_neg = std::copysign(nan_pos, static_cast<decltype(nan_pos)>(-1.0)); // "-nan"

	// *** align-fill & width ***
	VERIFY(SV("answer is '   0.25'") == hamon::format(SV("answer is '{:7.6}'"),  F(0.25)));
	VERIFY(SV("answer is '   0.25'") == hamon::format(SV("answer is '{:>7.6}'"), F(0.25)));
	VERIFY(SV("answer is '0.25   '") == hamon::format(SV("answer is '{:<7.6}'"), F(0.25)));
	VERIFY(SV("answer is ' 0.25  '") == hamon::format(SV("answer is '{:^7.6}'"), F(0.25)));

	VERIFY(SV("answer is '---0.125'") == hamon::format(SV("answer is '{:->8.6}'"), F(125e-3)));
	VERIFY(SV("answer is '0.125---'") == hamon::format(SV("answer is '{:-<8.6}'"), F(125e-3)));
	VERIFY(SV("answer is '-0.125--'") == hamon::format(SV("answer is '{:-^8.6}'"), F(125e-3)));

	VERIFY(SV("answer is '***inf'") == hamon::format(SV("answer is '{:*>6.6}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is 'inf***'") == hamon::format(SV("answer is '{:*<6.6}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '*inf**'") == hamon::format(SV("answer is '{:*^6.6}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '###-inf'") == hamon::format(SV("answer is '{:#>7.6}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf###'") == hamon::format(SV("answer is '{:#<7.6}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '#-inf##'") == hamon::format(SV("answer is '{:#^7.6}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '^^^nan'") == hamon::format(SV("answer is '{:^>6.6}'"), nan_pos));
	VERIFY(SV("answer is 'nan^^^'") == hamon::format(SV("answer is '{:^<6.6}'"), nan_pos));
	VERIFY(SV("answer is '^nan^^'") == hamon::format(SV("answer is '{:^^6.6}'"), nan_pos));

	VERIFY(SV("answer is '000-nan'") == hamon::format(SV("answer is '{:0>7.6}'"), nan_neg));
	VERIFY(SV("answer is '-nan000'") == hamon::format(SV("answer is '{:0<7.6}'"), nan_neg));
	VERIFY(SV("answer is '0-nan00'") == hamon::format(SV("answer is '{:0^7.6}'"), nan_neg));

	// Test whether zero padding is ignored
	VERIFY(SV("answer is '   0.25'") == hamon::format(SV("answer is '{:>07.6}'"), F(0.25)));
	VERIFY(SV("answer is '0.25   '") == hamon::format(SV("answer is '{:<07.6}'"), F(0.25)));
	VERIFY(SV("answer is ' 0.25  '") == hamon::format(SV("answer is '{:^07.6}'"), F(0.25)));

	// *** Sign ***
	VERIFY(SV("answer is '0'")  == hamon::format(SV("answer is '{:.6}'"),  F(0)));
	VERIFY(SV("answer is '0'")  == hamon::format(SV("answer is '{:-.6}'"), F(0)));
	VERIFY(SV("answer is '+0'") == hamon::format(SV("answer is '{:+.6}'"), F(0)));
	VERIFY(SV("answer is ' 0'") == hamon::format(SV("answer is '{: .6}'"), F(0)));

	VERIFY(SV("answer is '-0'") == hamon::format(SV("answer is '{:.6}'"),  F(-0.)));
	VERIFY(SV("answer is '-0'") == hamon::format(SV("answer is '{:-.6}'"), F(-0.)));
	VERIFY(SV("answer is '-0'") == hamon::format(SV("answer is '{:+.6}'"), F(-0.)));
	VERIFY(SV("answer is '-0'") == hamon::format(SV("answer is '{: .6}'"), F(-0.)));

	// [format.string.std]/5 The sign option applies to floating-point infinity and NaN.
	VERIFY(SV("answer is 'inf'")  == hamon::format(SV("answer is '{:.6}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is 'inf'")  == hamon::format(SV("answer is '{:-.6}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '+inf'") == hamon::format(SV("answer is '{:+.6}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is ' inf'") == hamon::format(SV("answer is '{: .6}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:.6}'"),  -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:-.6}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:+.6}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{: .6}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is 'nan'")  == hamon::format(SV("answer is '{:.6}'"),  nan_pos));
	VERIFY(SV("answer is 'nan'")  == hamon::format(SV("answer is '{:-.6}'"), nan_pos));
	VERIFY(SV("answer is '+nan'") == hamon::format(SV("answer is '{:+.6}'"), nan_pos));
	VERIFY(SV("answer is ' nan'") == hamon::format(SV("answer is '{: .6}'"), nan_pos));

	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:.6}'"),  nan_neg));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:-.6}'"), nan_neg));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:+.6}'"), nan_neg));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{: .6}'"), nan_neg));

	// *** alternate form **
	// When precision is zero there's no decimal point except when the alternate form is specified.
	// Note unlike the g and G option the trailing zeros are still removed.
	VERIFY(SV("answer is '0'")  == hamon::format(SV("answer is '{:.0}'"),  F(0)));
	VERIFY(SV("answer is '0.'") == hamon::format(SV("answer is '{:#.0}'"), F(0)));

	VERIFY(SV("answer is '0.'")  == hamon::format(SV("answer is '{:#.6}'"), F(0)));
	VERIFY(SV("answer is '2.5'") == hamon::format(SV("answer is '{:#.6}'"), F(2.5)));

	VERIFY(SV("answer is 'inf'")  == hamon::format(SV("answer is '{:#.6}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '-inf'") == hamon::format(SV("answer is '{:#.6}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is 'nan'")  == hamon::format(SV("answer is '{:#.6}'"), nan_pos));
	VERIFY(SV("answer is '-nan'") == hamon::format(SV("answer is '{:#.6}'"), nan_neg));

	// *** zero-padding & width ***
	VERIFY(SV("answer is '0.03125'")  == hamon::format(SV("answer is '{:06.6}'"),  0.03125));
	VERIFY(SV("answer is '+0.03125'") == hamon::format(SV("answer is '{:+06.6}'"), 0.03125));
	VERIFY(SV("answer is '+0.03125'") == hamon::format(SV("answer is '{:+07.6}'"), 0.03125));
	VERIFY(SV("answer is '+0.03125'") == hamon::format(SV("answer is '{:+08.6}'"), 0.03125));

	VERIFY(SV("answer is '000.03125'") == hamon::format(SV("answer is '{:09.6}'"),  0.03125));
	VERIFY(SV("answer is '000.03125'") == hamon::format(SV("answer is '{:-09.6}'"), 0.03125));
	VERIFY(SV("answer is '+00.03125'") == hamon::format(SV("answer is '{:+09.6}'"), 0.03125));
	VERIFY(SV("answer is ' 00.03125'") == hamon::format(SV("answer is '{: 09.6}'"), 0.03125));

	VERIFY(SV("answer is '       inf'") == hamon::format(SV("answer is '{:010.6}'"),  hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '       inf'") == hamon::format(SV("answer is '{:-010.6}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      +inf'") == hamon::format(SV("answer is '{:+010.6}'"), hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '       inf'") == hamon::format(SV("answer is '{: 010.6}'"), hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{:010.6}'"),  -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{:-010.6}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{:+010.6}'"), -hamon::numeric_limits<F>::infinity()));
	VERIFY(SV("answer is '      -inf'") == hamon::format(SV("answer is '{: 010.6}'"), -hamon::numeric_limits<F>::infinity()));

	VERIFY(SV("answer is '       nan'") == hamon::format(SV("answer is '{:010.6}'"),  nan_pos));
	VERIFY(SV("answer is '       nan'") == hamon::format(SV("answer is '{:-010.6}'"), nan_pos));
	VERIFY(SV("answer is '      +nan'") == hamon::format(SV("answer is '{:+010.6}'"), nan_pos));
	VERIFY(SV("answer is '       nan'") == hamon::format(SV("answer is '{: 010.6}'"), nan_pos));

	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{:010.6}'"),  nan_neg));
	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{:-010.6}'"), nan_neg));
	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{:+010.6}'"), nan_neg));
	VERIFY(SV("answer is '      -nan'") == hamon::format(SV("answer is '{: 010.6}'"), nan_neg));

	// *** precision ***
	VERIFY(SV("answer is '0.03'")    == hamon::format(SV("answer is '{:.0}'"),  0.03125));
	VERIFY(SV("answer is '0.03'")    == hamon::format(SV("answer is '{:.1}'"),  0.03125));
	VERIFY(SV("answer is '0.031'")   == hamon::format(SV("answer is '{:.2}'"),  0.03125));
	VERIFY(SV("answer is '0.0312'")  == hamon::format(SV("answer is '{:.3}'"),  0.03125));
	VERIFY(SV("answer is '0.03125'") == hamon::format(SV("answer is '{:.4}'"),  0.03125));
	VERIFY(SV("answer is '0.03125'") == hamon::format(SV("answer is '{:.5}'"),  0.03125));
	VERIFY(SV("answer is '0.03125'") == hamon::format(SV("answer is '{:.10}'"), 0.03125));

	// *** precision & alternate form ***

	VERIFY(SV("answer is '1.'")  == hamon::format(SV("answer is '{:#.{}}'"), 1.2, 0));
	VERIFY(SV("answer is '1.'")  == hamon::format(SV("answer is '{:#.{}}'"), 1.2, 1));
	VERIFY(SV("answer is '1.2'") == hamon::format(SV("answer is '{:#.{}}'"), 1.2, 2));
	VERIFY(SV("answer is '1.2'") == hamon::format(SV("answer is '{:#.{}}'"), 1.2, 3));
	VERIFY(SV("answer is '1.2'") == hamon::format(SV("answer is '{:#.{}}'"), 1.2, 4));
	VERIFY(SV("answer is '1.2'") == hamon::format(SV("answer is '{:#.{}}'"), 1.2, 5));
	VERIFY(SV("answer is '1.2'") == hamon::format(SV("answer is '{:#.{}}'"), 1.2, 6));

	VERIFY(SV("answer is '1.e+03'")  == hamon::format(SV("answer is '{:#.{}}'"), 1200.0, 0));
	VERIFY(SV("answer is '1.e+03'")  == hamon::format(SV("answer is '{:#.{}}'"), 1200.0, 1));
	VERIFY(SV("answer is '1.2e+03'") == hamon::format(SV("answer is '{:#.{}}'"), 1200.0, 2));
	VERIFY(SV("answer is '1.2e+03'") == hamon::format(SV("answer is '{:#.{}}'"), 1200.0, 3));
	VERIFY(SV("answer is '1200.'")   == hamon::format(SV("answer is '{:#.{}}'"), 1200.0, 4));
	VERIFY(SV("answer is '1200.'")   == hamon::format(SV("answer is '{:#.{}}'"), 1200.0, 5));
	VERIFY(SV("answer is '1200.'")   == hamon::format(SV("answer is '{:#.{}}'"), 1200.0, 6));

	VERIFY(SV("answer is '1.e+06'")  == hamon::format(SV("answer is '{:#.{}}'"), 1200000.0, 0));
	VERIFY(SV("answer is '1.e+06'")  == hamon::format(SV("answer is '{:#.{}}'"), 1200000.0, 1));
	VERIFY(SV("answer is '1.2e+06'") == hamon::format(SV("answer is '{:#.{}}'"), 1200000.0, 2));
	VERIFY(SV("answer is '1.2e+06'") == hamon::format(SV("answer is '{:#.{}}'"), 1200000.0, 3));
	VERIFY(SV("answer is '1.2e+06'") == hamon::format(SV("answer is '{:#.{}}'"), 1200000.0, 4));
	VERIFY(SV("answer is '1.2e+06'") == hamon::format(SV("answer is '{:#.{}}'"), 1200000.0, 5));
	VERIFY(SV("answer is '1.2e+06'") == hamon::format(SV("answer is '{:#.{}}'"), 1200000.0, 6));

	// *** locale-specific form ***
	// See locale-specific_form.pass.cpp
	return true;
}

template <typename CharT, typename F>
/*HAMON_CXX20_CONSTEXPR*/ bool test_floating_point_PR58714()
{
	VERIFY(SV("+1234")         == hamon::format(SV("{:+}"),  F(1234.0)));
	VERIFY(SV("+1.348p+10")    == hamon::format(SV("{:+a}"), F(1234.0)));
	VERIFY(SV("+1.234000e+03") == hamon::format(SV("{:+e}"), F(1234.0)));
	VERIFY(SV("+1234.000000")  == hamon::format(SV("{:+f}"), F(1234.0)));
	VERIFY(SV("+1234")         == hamon::format(SV("{:+g}"), F(1234.0)));

	VERIFY(SV("1234.")        == hamon::format(SV("{:#}"),  F(1234.0)));
	VERIFY(SV("1.348p+10")    == hamon::format(SV("{:#a}"), F(1234.0)));
	VERIFY(SV("1.234000e+03") == hamon::format(SV("{:#e}"), F(1234.0)));
	VERIFY(SV("1234.000000")  == hamon::format(SV("{:#f}"), F(1234.0)));
	VERIFY(SV("1234.00")      == hamon::format(SV("{:#g}"), F(1234.0)));

	VERIFY(SV("4.e+30")       == hamon::format(SV("{:#}"),  F(4.0e+30)));
	VERIFY(SV("1.p+102")      == hamon::format(SV("{:#a}"), F(0x4.0p+100)));
	VERIFY(SV("4.000000e+30") == hamon::format(SV("{:#e}"), F(4.0e+30)));
	VERIFY(SV("5070602400912917605986812821504.000000") == hamon::format(SV("{:#f}"), F(0x4.0p+100)));
	VERIFY(SV("4.00000e+30")  == hamon::format(SV("{:#g}"), F(4.0e+30)));

	VERIFY(SV("1234.")        == hamon::format(SV("{:#.6}"),  F(1234.0))); // # does not restore zeros
	VERIFY(SV("1.348000p+10") == hamon::format(SV("{:#.6a}"), F(1234.0)));
	VERIFY(SV("1.234000e+03") == hamon::format(SV("{:#.6e}"), F(1234.0)));
	VERIFY(SV("1234.000000")  == hamon::format(SV("{:#.6f}"), F(1234.0)));
	VERIFY(SV("1234.00")      == hamon::format(SV("{:#.6g}"), F(1234.0)));

	VERIFY(SV("-1234.")        == hamon::format(SV("{:#}"),  F(-1234.0)));
	VERIFY(SV("-1.348p+10")    == hamon::format(SV("{:#a}"), F(-1234.0)));
	VERIFY(SV("-1.234000e+03") == hamon::format(SV("{:#e}"), F(-1234.0)));
	VERIFY(SV("-1234.000000")  == hamon::format(SV("{:#f}"), F(-1234.0)));
	VERIFY(SV("-1234.00")      == hamon::format(SV("{:#g}"), F(-1234.0)));

	VERIFY(SV("-1234.")        == hamon::format(SV("{:#.6}"),  F(-1234.0))); // # does not restore zeros
	VERIFY(SV("-1.348000p+10") == hamon::format(SV("{:#.6a}"), F(-1234.0)));
	VERIFY(SV("-1.234000e+03") == hamon::format(SV("{:#.6e}"), F(-1234.0)));
	VERIFY(SV("-1234.000000")  == hamon::format(SV("{:#.6f}"), F(-1234.0)));
	VERIFY(SV("-1234.00")      == hamon::format(SV("{:#.6g}"), F(-1234.0)));

	VERIFY(SV("+1234.")        == hamon::format(SV("{:+#}"),  F(1234.0)));
	VERIFY(SV("+1.348p+10")    == hamon::format(SV("{:+#a}"), F(1234.0)));
	VERIFY(SV("+1.234000e+03") == hamon::format(SV("{:+#e}"), F(1234.0)));
	VERIFY(SV("+1234.000000")  == hamon::format(SV("{:+#f}"), F(1234.0)));
	VERIFY(SV("+1234.00")      == hamon::format(SV("{:+#g}"), F(1234.0)));

	VERIFY(SV("+1234.")        == hamon::format(SV("{:+#.6}"),  F(1234.0))); // # does not restore zeros
	VERIFY(SV("+1.348000p+10") == hamon::format(SV("{:+#.6a}"), F(1234.0)));
	VERIFY(SV("+1.234000e+03") == hamon::format(SV("{:+#.6e}"), F(1234.0)));
	VERIFY(SV("+1234.000000")  == hamon::format(SV("{:+#.6f}"), F(1234.0)));
	VERIFY(SV("+1234.00")      == hamon::format(SV("{:+#.6g}"), F(1234.0)));
	return true;
}

template <typename CharT, typename F>
/*HAMON_CXX20_CONSTEXPR*/ bool test_floating_point_impl()
{
	VERIFY(test_floating_point_hex_lower_case<CharT, F>());
	VERIFY(test_floating_point_hex_upper_case<CharT, F>());
	VERIFY(test_floating_point_hex_lower_case_precision<CharT, F>());
	VERIFY(test_floating_point_hex_upper_case_precision<CharT, F>());

	VERIFY(test_floating_point_scientific_lower_case<CharT, F>());
	VERIFY(test_floating_point_scientific_upper_case<CharT, F>());

	VERIFY(test_floating_point_fixed_lower_case<CharT, F>());
	VERIFY(test_floating_point_fixed_upper_case<CharT, F>());

	VERIFY(test_floating_point_general_lower_case<CharT, F>());
	VERIFY(test_floating_point_general_upper_case<CharT, F>());

	VERIFY(test_floating_point_default<CharT, F>());
	VERIFY(test_floating_point_default_precision<CharT, F>());

	VERIFY(test_floating_point_PR58714<CharT, F>());

	//// *** type ***
	//for (const auto& fmt : invalid_types<CharT>("aAeEfFgG"))
	//{
	//	check_exception("The type option contains an invalid value for a floating-point formatting argument", fmt, F(1));
	//}

	return true;
}

template <typename CharT>
/*HAMON_CXX20_CONSTEXPR*/ bool test_floating_point()
{
	// *** Test floating point format argument ***
	VERIFY(SV("hello 42") == hamon::format(SV("hello {}"), static_cast<float>(42)));
	VERIFY(SV("hello 42") == hamon::format(SV("hello {}"), static_cast<double>(42)));
	VERIFY(SV("hello 42") == hamon::format(SV("hello {}"), static_cast<long double>(42)));

	VERIFY(SV("hello 42") == hamon::format(std::locale(), SV("hello {}"), static_cast<float>(42)));
	VERIFY(SV("hello 42") == hamon::format(std::locale(), SV("hello {}"), static_cast<double>(42)));
	VERIFY(SV("hello 42") == hamon::format(std::locale(), SV("hello {}"), static_cast<long double>(42)));

	VERIFY(test_floating_point_impl<CharT, float>());
	VERIFY(test_floating_point_impl<CharT, double>());
//	VERIFY(test_floating_point_impl<CharT, long double>());		// TODO

	return true;
}

template <typename CharT, typename P>
/*HAMON_CXX20_CONSTEXPR*/ bool test_pointer_impl()
{
	// *** align-fill & width ***
	VERIFY(SV("answer is '   0x0'") == hamon::format(SV("answer is '{:6}'"),  P(nullptr)));
	VERIFY(SV("answer is '   0x0'") == hamon::format(SV("answer is '{:>6}'"), P(nullptr)));
	VERIFY(SV("answer is '0x0   '") == hamon::format(SV("answer is '{:<6}'"), P(nullptr)));
	VERIFY(SV("answer is ' 0x0  '") == hamon::format(SV("answer is '{:^6}'"), P(nullptr)));

	// The fill character ':' is allowed here (P0645) but not in ranges (P2286).
	VERIFY(SV("answer is ':::0x0'") == hamon::format(SV("answer is '{::>6}'"), P(nullptr)));
	VERIFY(SV("answer is '0x0:::'") == hamon::format(SV("answer is '{::<6}'"), P(nullptr)));
	VERIFY(SV("answer is ':0x0::'") == hamon::format(SV("answer is '{::^6}'"), P(nullptr)));

	// Test whether zero padding is ignored
	VERIFY(SV("answer is ':::0x0'") == hamon::format(SV("answer is '{::>06}'"), P(nullptr)));
	VERIFY(SV("answer is '0x0:::'") == hamon::format(SV("answer is '{::<06}'"), P(nullptr)));
	VERIFY(SV("answer is ':0x0::'") == hamon::format(SV("answer is '{::^06}'"), P(nullptr)));

	//// *** Sign ***
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:-}"), P(nullptr));
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:+}"), P(nullptr));
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{: }"), P(nullptr));

	//// *** alternate form ***
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:#}"), P(nullptr));

	// *** zero-padding ***
	VERIFY(SV("answer is '0x0000'") == hamon::format(SV("answer is '{:06}'"),  P(nullptr)));
	VERIFY(SV("answer is '0x0000'") == hamon::format(SV("answer is '{:06p}'"), P(nullptr)));
	VERIFY(SV("answer is '0X0000'") == hamon::format(SV("answer is '{:06P}'"), P(nullptr)));

	//// *** precision ***
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.}"), nullptr);
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.0}"), nullptr);
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.42}"), nullptr);

	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.{}}"), nullptr);
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.{}}"), nullptr, true);
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:.{}}"), nullptr, 1.0);

	//// *** locale-specific form ***
	//check_exception("The format specifier should consume the input or end with a '}'", SV("{:L}"), P(nullptr));

	//// *** type ***
	//for (const auto& fmt : invalid_types<CharT>("pP"))
	//{
	//	check_exception("The type option contains an invalid value for a pointer formatting argument", fmt, P(nullptr));
	//}

	return true;
}

template <typename CharT>
/*HAMON_CXX20_CONSTEXPR*/ bool test_pointer()
{
	// *** Test pointer formatter argument ***
	VERIFY(SV("hello 0x0")  == hamon::format(SV("hello {}"), nullptr));
	VERIFY(SV("hello 0x42") == hamon::format(SV("hello {}"), reinterpret_cast<void*>(0x42)));
	VERIFY(SV("hello 0x42") == hamon::format(SV("hello {}"), reinterpret_cast<const void*>(0x42)));

	VERIFY(SV("hello 0x0")  == hamon::format(std::locale(), SV("hello {}"), nullptr));
	VERIFY(SV("hello 0x42") == hamon::format(std::locale(), SV("hello {}"), reinterpret_cast<void*>(0x42)));
	VERIFY(SV("hello 0x42") == hamon::format(std::locale(), SV("hello {}"), reinterpret_cast<const void*>(0x42)));

	VERIFY(test_pointer_impl<CharT, std::nullptr_t>());
	VERIFY(test_pointer_impl<CharT, void*>());
	VERIFY(test_pointer_impl<CharT, const void*>());

	return true;
}

template <typename CharT>
/*HAMON_CXX20_CONSTEXPR*/ bool test_handle()
{
	// *** Valid permutations ***
	VERIFY(SV("answer is '0xaaaa'") == hamon::format(SV("answer is '{}'"),   status::foo));
	VERIFY(SV("answer is '0xaaaa'") == hamon::format(SV("answer is '{:x}'"), status::foo));
	VERIFY(SV("answer is '0XAAAA'") == hamon::format(SV("answer is '{:X}'"), status::foo));
	VERIFY(SV("answer is 'foo'")    == hamon::format(SV("answer is '{:s}'"), status::foo));

	VERIFY(SV("answer is '0x5555'") == hamon::format(SV("answer is '{}'"),   status::bar));
	VERIFY(SV("answer is '0x5555'") == hamon::format(SV("answer is '{:x}'"), status::bar));
	VERIFY(SV("answer is '0X5555'") == hamon::format(SV("answer is '{:X}'"), status::bar));
	VERIFY(SV("answer is 'bar'")    == hamon::format(SV("answer is '{:s}'"), status::bar));

	VERIFY(SV("answer is '0xaa55'") == hamon::format(SV("answer is '{}'"),   status::foobar));
	VERIFY(SV("answer is '0xaa55'") == hamon::format(SV("answer is '{:x}'"), status::foobar));
	VERIFY(SV("answer is '0XAA55'") == hamon::format(SV("answer is '{:X}'"), status::foobar));
	VERIFY(SV("answer is 'foobar'") == hamon::format(SV("answer is '{:s}'"), status::foobar));

	VERIFY(SV("answer is '0xaaaa'") == hamon::format(std::locale(), SV("answer is '{}'"),   status::foo));
	VERIFY(SV("answer is '0xaaaa'") == hamon::format(std::locale(), SV("answer is '{:x}'"), status::foo));
	VERIFY(SV("answer is '0XAAAA'") == hamon::format(std::locale(), SV("answer is '{:X}'"), status::foo));
	VERIFY(SV("answer is 'foo'")    == hamon::format(std::locale(), SV("answer is '{:s}'"), status::foo));

	VERIFY(SV("answer is '0x5555'") == hamon::format(std::locale(), SV("answer is '{}'"),   status::bar));
	VERIFY(SV("answer is '0x5555'") == hamon::format(std::locale(), SV("answer is '{:x}'"), status::bar));
	VERIFY(SV("answer is '0X5555'") == hamon::format(std::locale(), SV("answer is '{:X}'"), status::bar));
	VERIFY(SV("answer is 'bar'")    == hamon::format(std::locale(), SV("answer is '{:s}'"), status::bar));

	VERIFY(SV("answer is '0xaa55'") == hamon::format(std::locale(), SV("answer is '{}'"),   status::foobar));
	VERIFY(SV("answer is '0xaa55'") == hamon::format(std::locale(), SV("answer is '{:x}'"), status::foobar));
	VERIFY(SV("answer is '0XAA55'") == hamon::format(std::locale(), SV("answer is '{:X}'"), status::foobar));
	VERIFY(SV("answer is 'foobar'") == hamon::format(std::locale(), SV("answer is '{:s}'"), status::foobar));

	// P2418 Changed the argument from a const reference to a forwarding reference.
	// This mainly affects handle classes, however since we use an abstraction
	// layer here it's "tricky" to verify whether this test would do the "right"
	// thing. So these tests are done separately.

	//// *** type ***
	//for (const auto& fmt : invalid_types<CharT>("xXs"))
	//{
	//	check_exception("The type option contains an invalid value for a status formatting argument", fmt, status::foo);
	//}

	return true;
}

template <typename CharT>
/*HAMON_CXX20_CONSTEXPR*/ bool test_buffer_optimizations()
{
	// TODO
	return true;
}

template <typename CharT>
/*HAMON_CXX20_CONSTEXPR*/ bool test()
{
	VERIFY(test_escape<CharT>());
	VERIFY(test_arg_id<CharT>());
	VERIFY(test_many_args<CharT>());
	VERIFY(test_buffer_copy<CharT>());
	VERIFY(test_buffer_fill<CharT>());
	VERIFY(test_char<CharT>());
	VERIFY(test_char_as_integer<CharT>());
	VERIFY(test_char_to_wchar_t());
	VERIFY(test_string<CharT>());
	VERIFY(test_bool<CharT>());
	VERIFY(test_bool_as_integer<CharT>());
	VERIFY(test_signed_integer<CharT>());
	VERIFY(test_unsigned_integer<CharT>());
	VERIFY(test_floating_point<CharT>());
	VERIFY(test_pointer<CharT>());
	VERIFY(test_handle<CharT>());
	VERIFY(test_buffer_optimizations<CharT>());
	return true;
}

#undef SV
#undef STR

#undef VERIFY

GTEST_TEST(FormatTest, FormatTest)
{
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<char>());
	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(test<wchar_t>());
}

}	// namespace format_test

}	// namespace hamon_format_test
