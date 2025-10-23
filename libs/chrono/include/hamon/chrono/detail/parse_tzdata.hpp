/**
 *	@file	parse_tzdata.hpp
 *
 *	@brief	parse_tzdata の定義
 */

#ifndef HAMON_CHRONO_DETAIL_PARSE_TZDATA_HPP
#define HAMON_CHRONO_DETAIL_PARSE_TZDATA_HPP

#include <hamon/chrono/tzdb.hpp>
#include <hamon/chrono/detail/tz.hpp>
#include <hamon/chrono/detail/parse.hpp>
#include <hamon/chrono/detail/parse_link.hpp>
#include <hamon/chrono/detail/parse_rule.hpp>
#include <hamon/chrono/detail/parse_version.hpp>
#include <hamon/chrono/detail/parse_zone.hpp>
#include <hamon/cctype/tolower.hpp>
#include <hamon/stdexcept/runtime_error.hpp>
#include <istream>

namespace hamon {
namespace chrono {
namespace detail {

inline void parse_tzdata(chrono::tzdb& db, tz::rules_storage_type& rules, std::istream& input)
{
	db.version = detail::parse_version(input);

	while (true)
	{
		int c = hamon::tolower(input.get());

		switch (c)
		{
		case std::istream::traits_type::eof():
			return;

		case ' ':
		case '\t':
		case '\n':
			break;

		case '#':
			detail::skip_line(input);
			break;

		case 'r':
			detail::skip(input, "ule");
			detail::parse_rule(rules, input);
			break;

		case 'z':
			detail::skip(input, "one");
			detail::parse_zone(db, rules, input);
			break;

		case 'l':
			detail::skip(input, "ink");
			detail::parse_link(db, input);
			break;

		default:
			hamon::detail::throw_runtime_error("corrupt tzdb: unexpected input");
		}
	}
}

}	// namespace detail
}	// namespace chrono
}	// namespace hamon

#endif // HAMON_CHRONO_DETAIL_PARSE_TZDATA_HPP
