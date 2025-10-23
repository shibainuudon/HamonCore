/**
 *	@file	parse.hpp
 *
 *	@brief	parse の定義
 */

#ifndef HAMON_CHRONO_DETAIL_PARSE_HPP
#define HAMON_CHRONO_DETAIL_PARSE_HPP

#include <hamon/chrono/day.hpp>
#include <hamon/chrono/weekday.hpp>
#include <hamon/chrono/month.hpp>
#include <hamon/chrono/year.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/detail/tz.hpp>

#include <hamon/cstdint/int64_t.hpp>
#include <hamon/cctype/isalpha.hpp>
#include <hamon/cctype/isblank.hpp>
#include <hamon/cctype/isdigit.hpp>
#include <hamon/cctype/islower.hpp>
#include <hamon/cctype/tolower.hpp>
#include <hamon/limits.hpp>
#include <hamon/stdexcept/runtime_error.hpp>
#include <hamon/string.hpp>
#include <hamon/string_view.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>
#include <istream>

namespace hamon {
namespace chrono {
namespace detail {

//===----------------------------------------------------------------------===//
//                           Details
//===----------------------------------------------------------------------===//

inline void skip_optional_whitespace(std::istream& input)
{
	while (hamon::isblank(input.peek()))
	{
		input.get();
	}
}

inline void skip_mandatory_whitespace(std::istream& input)
{
	if (!hamon::isblank(input.get()))
	{
		hamon::detail::throw_runtime_error("corrupt tzdb: expected whitespace");
	}

	detail::skip_optional_whitespace(input);
}

inline bool is_eol(int c)
{
	return c == '\n' || c == hamon::char_traits<char>::eof();
}

inline void skip_line(std::istream& input)
{
	while (!detail::is_eol(input.peek()))
	{
		input.get();
	}
	input.get();
}

inline void skip(std::istream& input, char suffix)
{
	if (hamon::tolower(input.peek()) == suffix)
	{
		input.get();
	}
}

inline void skip(std::istream& input, hamon::string_view suffix)
{
	for (auto c : suffix)
	{
		if (hamon::tolower(input.peek()) == c)
		{
			input.get();
		}
	}
}

inline void matches(std::istream& input, char expected)
{
	HAMON_ASSERT(!hamon::isalpha(expected) || hamon::islower(expected));
	int c = input.get();
	if (hamon::tolower(c) != expected)
	{
		hamon::detail::throw_runtime_error((
			hamon::string("corrupt tzdb: expected character '") + expected +
			"', got '" + static_cast<char>(c) + "' instead"
		).c_str());
	}
}

inline void matches(std::istream& input, hamon::string_view expected)
{
	for (auto c : expected)
	{
		HAMON_ASSERT(!hamon::isalpha(c) || hamon::islower(c));
		int actual = input.get();
		if (hamon::tolower(actual) != c)
		{
			hamon::detail::throw_runtime_error((
				hamon::string("corrupt tzdb: expected character '") + c +
				"' from string '" + hamon::string(expected) +
				"', got '" + static_cast<char>(actual) + "' instead"
			).c_str());
		}
	}
}

inline hamon::string parse_string(std::istream& input)
{
	hamon::string result;
	while (true)
	{
		int c = input.get();
		switch (c)
		{
		case ' ':
		case '\t':
		case '\n':
			input.unget();
			HAMON_FALLTHROUGH();
		case std::istream::traits_type::eof():
			if (result.empty())
			{
				hamon::detail::throw_runtime_error("corrupt tzdb: expected a string");
			}

			return result;

		default:
			result.push_back(static_cast<char>(c));
		}
	}
}

inline hamon::int64_t parse_integral(std::istream& input, bool leading_zero_allowed)
{
	hamon::int64_t result = input.get();
	if (leading_zero_allowed)
	{
		if (result < '0' || result > '9')
		{
			hamon::detail::throw_runtime_error("corrupt tzdb: expected a digit");
		}
	}
	else
	{
		if (result < '1' || result > '9')
		{
			hamon::detail::throw_runtime_error("corrupt tzdb: expected a non-zero digit");
		}
	}
	result -= '0';
	while (true)
	{
		if (input.peek() < '0' || input.peek() > '9')
		{
			return result;
		}

		// In order to avoid possible overflows we limit the accepted range.
		// Most values parsed are expected to be very small:
		// - 8784 hours in a year
		// - 31 days in a month
		// - year no real maximum, these values are expected to be less than
		//   the range of the year type.
		//
		// However the leapseconds use a seconds after epoch value. Using an
		// int would run into an overflow in 2038. By using a 64-bit value
		// the range is large enough for the bilions of years. Limiting that
		// range slightly to make the code easier is not an issue.
		if (result > (hamon::numeric_limits<hamon::int64_t>::max() / 16))
		{
			hamon::detail::throw_runtime_error("corrupt tzdb: integral too large");
		}

		result *= 10;
		result += input.get() - '0';
	}
}

//===----------------------------------------------------------------------===//
//                          Calendar
//===----------------------------------------------------------------------===//

inline chrono::day parse_day(std::istream& input)
{
	auto result = detail::parse_integral(input, false);
	if (result > 31)
	{
		hamon::detail::throw_runtime_error("corrupt tzdb day: value too large");
	}
	return chrono::day{ static_cast<unsigned>(result) };
}

inline chrono::weekday parse_weekday(std::istream& input)
{
	// TZDB allows the shortest unique name.
	switch (hamon::tolower(input.get()))
	{
	case 'f':
		detail::skip(input, "riday");
		return Friday;

	case 'm':
		detail::skip(input, "onday");
		return Monday;

	case 's':
		switch (hamon::tolower(input.get()))
		{
		case 'a':
			detail::skip(input, "turday");
			return Saturday;

		case 'u':
			detail::skip(input, "nday");
			return Sunday;
		}
		break;

	case 't':
		switch (hamon::tolower(input.get()))
		{
		case 'h':
			detail::skip(input, "ursday");
			return Thursday;

		case 'u':
			detail::skip(input, "esday");
			return Tuesday;
		}
		break;
	case 'w':
		detail::skip(input, "ednesday");
		return Wednesday;
	}

	hamon::detail::throw_runtime_error("corrupt tzdb weekday: invalid name");
}

inline chrono::month parse_month(std::istream& input)
{
	// TZDB allows the shortest unique name.
	switch (hamon::tolower(input.get()))
	{
	case 'a':
		switch (hamon::tolower(input.get()))
		{
		case 'p':
			detail::skip(input, "ril");
			return April;

		case 'u':
			detail::skip(input, "gust");
			return August;
		}
		break;

	case 'd':
		detail::skip(input, "ecember");
		return December;

	case 'f':
		detail::skip(input, "ebruary");
		return February;

	case 'j':
		switch (hamon::tolower(input.get()))
		{
		case 'a':
			detail::skip(input, "nuary");
			return January;

		case 'u':
			switch (hamon::tolower(input.get()))
			{
			case 'n':
				detail::skip(input, 'e');
				return June;

			case 'l':
				detail::skip(input, 'y');
				return July;
			}
		}
		break;

	case 'm':
		if (hamon::tolower(input.get()) == 'a')
		{
			switch (hamon::tolower(input.get()))
			{
			case 'y':
				return May;

			case 'r':
				detail::skip(input, "ch");
				return March;
			}
		}
		break;

	case 'n':
		detail::skip(input, "ovember");
		return November;

	case 'o':
		detail::skip(input, "ctober");
		return October;

	case 's':
		detail::skip(input, "eptember");
		return September;
	}
	hamon::detail::throw_runtime_error("corrupt tzdb month: invalid name");
}

inline chrono::year parse_year_value(std::istream& input)
{
	bool negative = (input.peek() == '-');
	if (negative) /*[[unlikely]]*/
	{
		input.get();
	}

	hamon::int64_t result = detail::parse_integral(input, true);
	if (result > static_cast<int>(chrono::year::max()))
	{
		if (negative)
		{
			hamon::detail::throw_runtime_error("corrupt tzdb year: year is less than the minimum");
		}

		hamon::detail::throw_runtime_error("corrupt tzdb year: year is greater than the maximum");
	}

	return chrono::year{ static_cast<int>(negative ? -result : result) };
}

inline chrono::year parse_year(std::istream& input)
{
	if (hamon::tolower(input.peek()) != 'm') /*[[likely]]*/
	{
		return detail::parse_year_value(input);
	}

	input.get();
	switch (hamon::tolower(input.peek()))
	{
	case 'i':
		input.get();
		detail::skip(input, 'n');
		HAMON_FALLTHROUGH();

	case ' ':
		// The m is minimum, even when that is ambiguous.
		return chrono::year::min();

	case 'a':
		input.get();
		detail::skip(input, 'x');
		return chrono::year::max();
	}

	hamon::detail::throw_runtime_error("corrupt tzdb year: expected 'min' or 'max'");
}

//===----------------------------------------------------------------------===//
//                        TZDB fields
//===----------------------------------------------------------------------===//

inline tz::constrained_weekday_t::comparison_t parse_comparison(std::istream& input)
{
	switch (input.get())
	{
	case '>':
		detail::matches(input, '=');
		return tz::constrained_weekday_t::comparison_t::ge;

	case '<':
		detail::matches(input, '=');
		return tz::constrained_weekday_t::comparison_t::le;
	}
	hamon::detail::throw_runtime_error("corrupt tzdb on: expected '>=' or '<='");
}

inline tz::on_t parse_on(std::istream& input)
{
	if (hamon::isdigit(input.peek()))
	{
		return detail::parse_day(input);
	}

	if (hamon::tolower(input.peek()) == 'l')
	{
		detail::matches(input, "last");
		return chrono::weekday_last(detail::parse_weekday(input));
	}

	return tz::constrained_weekday_t{
		detail::parse_weekday(input), detail::parse_comparison(input), detail::parse_day(input) };
}

inline chrono::seconds parse_duration(std::istream& input)
{
	chrono::seconds result{ 0 };
	int c = input.peek();
	bool negative = c == '-';
	if (negative)
	{
		input.get();
		// Negative is either a negative value or a single -.
		// The latter means 0 and the parsing is complete.
		if (!hamon::isdigit(input.peek()))
		{
			return result;
		}
	}

	result += chrono::hours(detail::parse_integral(input, true));
	if (input.peek() != ':')
	{
		return negative ? -result : result;
	}

	input.get();
	result += chrono::minutes(detail::parse_integral(input, true));
	if (input.peek() != ':')
	{
		return negative ? -result : result;
	}

	input.get();
	result += chrono::seconds(detail::parse_integral(input, true));
	if (input.peek() != '.')
	{
		return negative ? -result : result;
	}

	input.get();
	(void)detail::parse_integral(input, true); // Truncate the digits.

	return negative ? -result : result;
}

inline tz::clock_t parse_clock(std::istream& input)
{
	switch (input.get())
	{
	// case sensitive
	case 'w':
		return tz::clock_t::local;
	case 's':
		return tz::clock_t::standard;

	case 'u':
	case 'g':
	case 'z':
		return tz::clock_t::universal;
	}

	input.unget();
	return tz::clock_t::local;
}

inline bool parse_dst(std::istream& input, chrono::seconds offset)
{
	switch (input.get())
	{
	// case sensitive
	case 's':
		return false;

	case 'd':
		return true;
	}

	input.unget();
	return offset != 0_s;
}

inline tz::at_t parse_at(std::istream& input)
{
	return { detail::parse_duration(input), detail::parse_clock(input) };
}

inline tz::save_t parse_save(std::istream& input)
{
	chrono::seconds time = detail::parse_duration(input);
	return { time, detail::parse_dst(input, time) };
}

}	// namespace detail
}	// namespace chrono
}	// namespace hamon

#endif // HAMON_CHRONO_DETAIL_PARSE_HPP
