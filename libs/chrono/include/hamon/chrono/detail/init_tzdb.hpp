/**
 *	@file	init_tzdb.hpp
 *
 *	@brief	init_tzdb の定義
 */

#ifndef HAMON_CHRONO_DETAIL_INIT_TZDB_HPP
#define HAMON_CHRONO_DETAIL_INIT_TZDB_HPP

#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/leap_second.hpp>
#include <hamon/chrono/sys_days.hpp>
#include <hamon/chrono/sys_seconds.hpp>
#include <hamon/chrono/tzdb.hpp>
#include <hamon/chrono/year_month_day.hpp>
#include <hamon/algorithm/ranges/sort.hpp>
#include <hamon/algorithm/ranges/adjacent_find.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/limits.hpp>
#include <hamon/stdexcept/runtime_error.hpp>
#include <hamon/string.hpp>
#include <hamon/vector.hpp>
#include <hamon/config.hpp>
#include <istream>
#include <sstream>

namespace hamon {
namespace chrono {
namespace detail {

HAMON_NODISCARD inline bool
is_whitespace(int c)
{
	return c == ' ' || c == '\t';
}

inline void
skip_optional_whitespace(std::istream& input)
{
	while (detail::is_whitespace(input.peek()))
	{
		input.get();
	}
}

inline void
skip_mandatory_whitespace(std::istream& input)
{
	if (!detail::is_whitespace(input.get()))
	{
		hamon::detail::throw_runtime_error("corrupt tzdb: expected whitespace");
	}

	detail::skip_optional_whitespace(input);
}

HAMON_NODISCARD inline bool
is_eol(int c)
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

HAMON_NODISCARD inline hamon::int64_t
parse_integral(std::istream& input, bool leading_zero_allowed)
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

inline void init_leap_seconds(hamon::vector<hamon::chrono::leap_second>& leap_seconds)
{
	constexpr auto offset = hamon::chrono::sys_days{ 1970_y / January / 1 } - hamon::chrono::sys_days{ 1900_y / January / 1 };

	const char* s =
#include <hamon/chrono/detail/leap-seconds.list>
	;

	std::istringstream input(s);

	struct entry_t
	{
		hamon::chrono::sys_seconds m_timestamp;
		hamon::chrono::seconds m_value;

		constexpr
		entry_t(hamon::chrono::sys_seconds ts, hamon::chrono::seconds v)
			: m_timestamp(ts), m_value(v)
		{}
	};
	hamon::vector<entry_t> entries;
	{
		bool loop = true;
		while (loop)
		{
			switch (input.peek())
			{
			case std::istream::traits_type::eof():
				loop = false;
				break;

			case ' ':
			case '\t':
			case '\n':
				input.get();
				break;

			case '#':
				detail::skip_line(input);
				break;

			default:
				{
					hamon::chrono::sys_seconds date = hamon::chrono::sys_seconds{ hamon::chrono::seconds{detail::parse_integral(input, false)} } - offset;
					detail::skip_mandatory_whitespace(input);
					hamon::chrono::seconds value{ detail::parse_integral(input, false) };
					detail::skip_line(input);

					entries.emplace_back(date, value);
				}
				break;
			}
		}
	}

	// The Standard requires the leap seconds to be sorted. The file
	// leap-seconds.list usually provides them in sorted order, but that is not
	// guaranteed so we ensure it here.
	hamon::ranges::sort(entries, {}, &entry_t::m_timestamp);

	// The database should contain the number of seconds inserted by a leap
	// second (1 or -1). So the difference between the two elements is stored.
	// std::ranges::views::adjacent has not been implemented yet.
	(void)hamon::ranges::adjacent_find(entries, [&](const entry_t& first, const entry_t& second) {
		leap_seconds.emplace_back(second.m_timestamp, second.m_value - first.m_value);
		return false;
	});
}

inline void init_tzdb(hamon::chrono::tzdb& tzdb)
{
	init_leap_seconds(tzdb.leap_seconds);
}

}	// namespace detail
}	// namespace chrono
}	// namespace hamon

#endif // HAMON_CHRONO_DETAIL_INIT_TZDB_HPP
