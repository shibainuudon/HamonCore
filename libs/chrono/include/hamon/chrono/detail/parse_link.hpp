/**
 *	@file	parse_link.hpp
 *
 *	@brief	parse_link の定義
 */

#ifndef HAMON_CHRONO_DETAIL_PARSE_LINK_HPP
#define HAMON_CHRONO_DETAIL_PARSE_LINK_HPP

#include <hamon/chrono/tzdb.hpp>
#include <hamon/chrono/detail/parse.hpp>
#include <hamon/string.hpp>
#include <hamon/utility/move.hpp>
#include <istream>

namespace hamon {
namespace chrono {
namespace detail {

inline void parse_link(chrono::tzdb& db, std::istream& input)
{
	detail::skip_mandatory_whitespace(input);
	hamon::string target = detail::parse_string(input);
	detail::skip_mandatory_whitespace(input);
	hamon::string name = detail::parse_string(input);
	detail::skip_line(input);

	db.links.emplace_back(hamon::chrono::detail::private_ctor_tag{},
		hamon::move(name), hamon::move(target));
}

}	// namespace detail
}	// namespace chrono
}	// namespace hamon

#endif // HAMON_CHRONO_DETAIL_PARSE_LINK_HPP
