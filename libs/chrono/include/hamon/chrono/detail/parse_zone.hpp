/**
 *	@file	parse_zone.hpp
 *
 *	@brief	parse_zone の定義
 */

#ifndef HAMON_CHRONO_DETAIL_PARSE_ZONE_HPP
#define HAMON_CHRONO_DETAIL_PARSE_ZONE_HPP

#include <hamon/chrono/tzdb.hpp>
#include <hamon/chrono/detail/tz.hpp>
#include <hamon/chrono/detail/parse.hpp>
#include <hamon/cctype/isdigit.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/vector.hpp>
#include <istream>

namespace hamon {
namespace chrono {
namespace detail {

inline tz::continuation_t::rules_t parse_rules(std::istream& input)
{
	int c = input.peek();
	// A single -  is not a SAVE but a special case.
	if (c == '-')
	{
		input.get();
		if (hamon::isblank(input.peek()))
		{
			return hamon::monostate{};
		}
		input.unget();
		return detail::parse_save(input);
	}

	if (hamon::isdigit(c) || c == '+')
	{
		return detail::parse_save(input);
	}

	return detail::parse_string(input);
}

inline tz::continuation_t parse_continuation(tz::rules_storage_type& rules, std::istream& input)
{
	tz::continuation_t result;

	result.m_rule_database = hamon::addressof(rules);

	// Note STDOFF is specified as
	//   This field has the same format as the AT and SAVE fields of rule lines;
	// These fields have different suffix letters, these letters seem
	// not to be used so do not allow any of them.

	result.m_stdoff = detail::parse_duration(input);
	detail::skip_mandatory_whitespace(input);
	result.m_rules = detail::parse_rules(input);
	detail::skip_mandatory_whitespace(input);
	result.m_format = detail::parse_string(input);
	detail::skip_optional_whitespace(input);

	if (detail::is_eol(input.peek()))
	{
		return result;
	}
	result.m_year = detail::parse_year(input);
	detail::skip_optional_whitespace(input);

	if (detail::is_eol(input.peek()))
	{
		return result;
	}
	result.m_in = detail::parse_month(input);
	detail::skip_optional_whitespace(input);

	if (detail::is_eol(input.peek()))
	{
		return result;
	}
	result.m_on = detail::parse_on(input);
	detail::skip_optional_whitespace(input);

	if (detail::is_eol(input.peek()))
	{
		return result;
	}
	result.m_at = detail::parse_at(input);

	return result;
}

inline void parse_zone(chrono::tzdb& db, tz::rules_storage_type& rules, std::istream& input)
{
	detail::skip_mandatory_whitespace(input);
	hamon::string name = detail::parse_string(input);
	detail::skip_mandatory_whitespace(input);

	hamon::vector<tz::continuation_t> continuations;
	do
	{
		// The first line must be valid, continuations are optional.
		continuations.emplace_back(detail::parse_continuation(rules, input));
		detail::skip_line(input);
		detail::skip_optional_whitespace(input);
	} while (hamon::isdigit(input.peek()) || input.peek() == '-');

	db.zones.emplace_back(hamon::chrono::detail::private_ctor_tag{},
		hamon::move(name), hamon::move(continuations), rules);
}

}	// namespace detail
}	// namespace chrono
}	// namespace hamon

#endif // HAMON_CHRONO_DETAIL_PARSE_ZONE_HPP
