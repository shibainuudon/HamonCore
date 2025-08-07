/**
 *	@file	format_test_helper.hpp
 *
 *	@brief
 */

#ifndef HAMON_FORMAT_TEST_HELPER_HPP
#define HAMON_FORMAT_TEST_HELPER_HPP

#include <hamon/format/basic_format_parse_context.hpp>
#include <hamon/format/basic_format_context.hpp>
#include <hamon/format/format_error.hpp>
#include <hamon/format/formatter.hpp>
#include <hamon/format/format_string.hpp>
#include <hamon/format/wformat_string.hpp>
#include <hamon/format/format_context.hpp>
#include <hamon/format/wformat_context.hpp>
#include <hamon/algorithm/copy.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/detail/statically_widen.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/string_view.hpp>

#define LOCALE_en_US_UTF_8     "en_US.UTF-8"
#define LOCALE_fr_FR_UTF_8     "fr_FR.UTF-8"

namespace hamon_format_test
{

// test_format_string_t
template <typename T, typename... Args>
struct test_format_string {};

template <typename... Args>
struct test_format_string<char, Args...>
{
	using type = hamon::format_string<Args...>;
};

template <typename... Args>
struct test_format_string<wchar_t, Args...>
{
	using type = hamon::wformat_string<Args...>;
};

template <typename T, typename... Args>
using test_format_string_t = typename test_format_string<T, Args...>::type;

// test_format_context_t
template <typename T>
struct test_format_context {};

template <>
struct test_format_context<char>
{
	using type = hamon::format_context;
};

template <>
struct test_format_context<wchar_t>
{
	using type = hamon::wformat_context;
};

template <typename T>
using test_format_context_t = typename test_format_context<T>::type;

// A user-defined type used to test the handle formatter.
enum class status : hamon::uint16_t { foo = 0xAAAA, bar = 0x5555, foobar = 0xAA55 };

enum class color { black, red, gold };

}	// namespace hamon_format_test

// The formatter for a user-defined type used to test the handle formatter.
template <typename CharT>
struct hamon::formatter<hamon_format_test::status, CharT>
{
	// During the 2023 Issaquah meeting LEWG made it clear a formatter is
	// required to call its parse function. LWG3892 Adds the wording for that
	// requirement. Therefore this formatter is initialized in an invalid state.
	// A call to parse sets it in a valid state and a call to format validates
	// the state.
	int type = -1;

	constexpr auto parse(hamon::basic_format_parse_context<CharT>& parse_ctx)
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

	template <typename Out>
	auto format(hamon_format_test::status s, hamon::basic_format_context<Out, CharT>& ctx) const
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
			end = std::to_chars(&buffer[2], hamon::end(buffer), static_cast<hamon::uint16_t>(s), 16).ptr;
			buffer[6] = '\0';
			break;

		case 1:
			begin = buffer;
			buffer[0] = '0';
			buffer[1] = 'X';
			end = std::to_chars(&buffer[2], hamon::end(buffer), static_cast<hamon::uint16_t>(s), 16).ptr;
			hamon::transform(static_cast<const char*>(&buffer[2]), end, &buffer[2], [](char c) {
				return static_cast<char>(std::toupper(c)); });
			buffer[6] = '\0';
			break;

		case 2:
			switch (s)
			{
			case hamon_format_test::status::foo:
				begin = names[0];
				break;
			case hamon_format_test::status::bar:
				begin = names[1];
				break;
			case hamon_format_test::status::foobar:
				begin = names[2];
				break;
			}
			end = begin + std::strlen(begin);
			break;
		}

		return hamon::copy(begin, end, ctx.out());
	}
};

#define SV(Str)		hamon::basic_string_view<CharT>(HAMON_STATICALLY_WIDEN(CharT, Str), sizeof(Str) - 1)

template <class CharT>
struct hamon::formatter<hamon_format_test::color, CharT> : hamon::formatter<hamon::basic_string_view<CharT>, CharT>
{
	static constexpr hamon::basic_string_view<CharT> color_names[] = { SV("black"), SV("red"), SV("gold") };

	auto format(hamon_format_test::color c, auto& ctx) const
	{
		return hamon::formatter<hamon::basic_string_view<CharT>, CharT>::format(color_names[static_cast<int>(c)], ctx);
	}
};

#undef SV

#endif // HAMON_FORMAT_TEST_HELPER_HPP
