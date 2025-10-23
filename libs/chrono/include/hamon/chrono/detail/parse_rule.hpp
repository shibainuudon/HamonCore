/**
 *	@file	parse_rule.hpp
 *
 *	@brief	parse_rule の定義
 */

#ifndef HAMON_CHRONO_DETAIL_PARSE_RULE_HPP
#define HAMON_CHRONO_DETAIL_PARSE_RULE_HPP

#include <hamon/chrono/year.hpp>
#include <hamon/chrono/detail/tz.hpp>
#include <hamon/chrono/detail/parse.hpp>
#include <hamon/algorithm/ranges/find.hpp>
#include <hamon/cctype/tolower.hpp>
#include <hamon/string.hpp>
#include <hamon/vector.hpp>
#include <istream>

namespace hamon {
namespace chrono {
namespace detail {

inline chrono::year parse_to(std::istream& input, chrono::year only)
{
	if (hamon::tolower(input.peek()) != 'o')
	{
		return detail::parse_year(input);
	}

	input.get();
	detail::skip(input, "nly");
	return only;
}

inline hamon::string parse_letters(std::istream& input)
{
	hamon::string result = detail::parse_string(input);
	// Canonicalize "-" to "" since they are equivalent in the specification.
	return result != "-" ? result : "";
}

inline tz::rule_t& create_rule_entry(tz::rules_storage_type& rules, hamon::string const& name)
{
	auto result = [&]() -> tz::rule_t&
	{
		auto& rule = rules.emplace_back(name, hamon::vector<tz::rule_t>{});
		return rule.second.emplace_back();
	};

	if (rules.empty())
	{
		return result();
	}

	// Typically rules are in contiguous order in the database.
	// But there are exceptions, some rules are interleaved.
	if (rules.back().first == name)
	{
		return rules.back().second.emplace_back();
	}

	auto it = hamon::ranges::find(rules, name, [](tz::rules_storage_type::const_reference r) { return r.first; });
	if (it != hamon::ranges::end(rules))
	{
		return it->second.emplace_back();
	}

	return result();
}

inline void parse_rule(tz::rules_storage_type& rules, std::istream& input)
{
	detail::skip_mandatory_whitespace(input);
	hamon::string name = detail::parse_string(input);

	tz::rule_t& rule = detail::create_rule_entry(rules, name);

	detail::skip_mandatory_whitespace(input);
	rule.m_from = detail::parse_year(input);
	detail::skip_mandatory_whitespace(input);
	rule.m_to = detail::parse_to(input, rule.m_from);
	detail::skip_mandatory_whitespace(input);
	detail::matches(input, '-');
	detail::skip_mandatory_whitespace(input);
	rule.m_in = detail::parse_month(input);
	detail::skip_mandatory_whitespace(input);
	rule.m_on = detail::parse_on(input);
	detail::skip_mandatory_whitespace(input);
	rule.m_at = detail::parse_at(input);
	detail::skip_mandatory_whitespace(input);
	rule.m_save = detail::parse_save(input);
	detail::skip_mandatory_whitespace(input);
	rule.m_letters = detail::parse_letters(input);
	detail::skip_line(input);
}

}	// namespace detail
}	// namespace chrono
}	// namespace hamon

#endif // HAMON_CHRONO_DETAIL_PARSE_RULE_HPP
