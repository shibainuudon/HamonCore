/**
 *	@file	parse_version.hpp
 *
 *	@brief	parse_version の定義
 */

#ifndef HAMON_CHRONO_DETAIL_PARSE_VERSION_HPP
#define HAMON_CHRONO_DETAIL_PARSE_VERSION_HPP

#include <hamon/chrono/detail/parse.hpp>
#include <hamon/string.hpp>
#include <istream>

namespace hamon {
namespace chrono {
namespace detail {

inline hamon::string parse_version(std::istream& input)
{
	// The first line in tzdata.zi contains
	//    # version YYYYw
	// The parser expects this pattern
	// #\s*version\s*\(.*)
	// This part is not documented.
	detail::matches(input, '#');
	detail::skip_optional_whitespace(input);
	detail::matches(input, "version");
	detail::skip_mandatory_whitespace(input);
	return detail::parse_string(input);
}

}	// namespace detail
}	// namespace chrono
}	// namespace hamon

#endif // HAMON_CHRONO_DETAIL_PARSE_VERSION_HPP
