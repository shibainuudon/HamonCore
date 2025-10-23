/**
 *	@file	parse_leap_seconds.hpp
 *
 *	@brief	parse_leap_seconds の定義
 */

#ifndef HAMON_CHRONO_DETAIL_PARSE_LEAP_SECONDS_HPP
#define HAMON_CHRONO_DETAIL_PARSE_LEAP_SECONDS_HPP

#include <hamon/chrono/detail/parse.hpp>
#include <hamon/chrono/leap_second.hpp>
#include <hamon/chrono/sys_days.hpp>
#include <hamon/chrono/sys_seconds.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/algorithm/ranges/sort.hpp>
#include <hamon/algorithm/ranges/adjacent_find.hpp>
#include <hamon/vector.hpp>
#include <istream>

namespace hamon {
namespace chrono {
namespace detail {

inline void parse_leap_seconds(hamon::vector<chrono::leap_second>& leap_seconds, std::istream& input)
{
	// The file stores dates since 1 January 1900, 00:00:00, we want
	// seconds since 1 January 1970.
	constexpr auto offset = chrono::sys_days{ 1970_y / January / 1 } - chrono::sys_days{ 1900_y / January / 1 };

	struct entry_t
	{
		chrono::sys_seconds m_timestamp;
		chrono::seconds m_value;

		entry_t(chrono::sys_seconds ts, chrono::seconds v)
			: m_timestamp(ts), m_value(v)
		{}
	};

	hamon::vector<entry_t> entries;
	[&] {
		while (true)
		{
			switch (input.peek())
			{
			case std::istream::traits_type::eof():
				return;

			case ' ':
			case '\t':
			case '\n':
				input.get();
				continue;

			case '#':
				detail::skip_line(input);
				continue;
			}

			chrono::sys_seconds date = chrono::sys_seconds{ chrono::seconds{detail::parse_integral(input, false)} } - offset;
			detail::skip_mandatory_whitespace(input);
			chrono::seconds value{ detail::parse_integral(input, false) };
			detail::skip_line(input);

			entries.emplace_back(date, value);
		}
	}();
	// The Standard requires the leap seconds to be sorted. The file
	// leap-seconds.list usually provides them in sorted order, but that is not
	// guaranteed so we ensure it here.
	hamon::ranges::sort(entries, {}, &entry_t::m_timestamp);

	// The database should contain the number of seconds inserted by a leap
	// second (1 or -1). So the difference between the two elements is stored.
	// std::ranges::views::adjacent has not been implemented yet.
	(void)hamon::ranges::adjacent_find(entries, [&](entry_t const& first, entry_t const& second) {
		leap_seconds.emplace_back(hamon::chrono::detail::private_ctor_tag{},
			second.m_timestamp, second.m_value - first.m_value);
		return false;
	});
}

}	// namespace detail
}	// namespace chrono
}	// namespace hamon

#endif // HAMON_CHRONO_DETAIL_PARSE_LEAP_SECONDS_HPP
