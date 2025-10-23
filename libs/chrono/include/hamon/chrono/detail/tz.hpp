/**
 *	@file	tz.hpp
 *
 *	@brief	tz の定義
 */

#ifndef HAMON_CHRONO_DETAIL_TZ_HPP
#define HAMON_CHRONO_DETAIL_TZ_HPP

#include <hamon/chrono/year_month_day.hpp>
#include <hamon/chrono/year.hpp>
#include <hamon/chrono/month.hpp>
#include <hamon/chrono/sys_days.hpp>
#include <hamon/chrono/weekday.hpp>
#include <hamon/chrono/day.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/pair.hpp>
#include <hamon/string.hpp>
#include <hamon/variant.hpp>
#include <hamon/vector.hpp>

namespace hamon {
namespace chrono {
namespace detail {

namespace tz
{

// Sun>=8   first Sunday on or after the eighth
// Sun<=25  last Sunday on or before the 25th
struct constrained_weekday_t
{
	chrono::year_month_day operator()(chrono::year year_, chrono::month month_) const
	{
		auto result = static_cast<chrono::sys_days>(chrono::year_month_day{ year_, month_, m_day });
		chrono::weekday wd{ static_cast<chrono::sys_days>(result) };

		if (m_comparison == comparison_t::le)
		{
			result -= wd - m_weekday;
		}
		else
		{
			result += m_weekday - wd;
		}

		return result;
	}

	enum comparison_t { le, ge };

	chrono::weekday m_weekday;
	comparison_t m_comparison;
	chrono::day m_day;
};

// The on field has a few alternative presentations
//  5        the fifth of the month
//  lastSun  the last Sunday in the month
//  lastMon  the last Monday in the month
//  Sun>=8   first Sunday on or after the eighth
//  Sun<=25  last Sunday on or before the 25th
using on_t = hamon::variant<chrono::day, chrono::weekday_last, tz::constrained_weekday_t>;

enum class clock_t { local, standard, universal };

struct at_t
{
	chrono::seconds m_time{ 0 };
	tz::clock_t m_clock{ tz::clock_t::local };

	at_t() = default;
	at_t(chrono::seconds t, tz::clock_t c)
		: m_time(t), m_clock(c)
	{}
};

struct save_t
{
	chrono::seconds m_time;
	bool m_is_dst;
};

// The names of the fields match the fields of a Rule.
struct rule_t
{
	chrono::year m_from;
	chrono::year m_to;
	chrono::month m_in;
	tz::on_t m_on;
	tz::at_t m_at;
	tz::save_t m_save;
	hamon::string m_letters;
};

using rules_storage_type = hamon::vector<hamon::pair<hamon::string, hamon::vector<tz::rule_t>>>; // TODO TZDB use flat_map;

struct continuation_t
{
	// Non-owning link to the RULE entries.
	tz::rules_storage_type* m_rule_database;

	chrono::seconds m_stdoff;

	// The RULES is either a SAVE or a NAME.
	// The size_t is used as cache. After loading the rules they are
	// sorted and remain stable, then an index in the vector can be
	// used.
	// If this field contains - then standard time always
	// applies. This is indicated by the monostate.
	// TODO TZDB Investigate implantation the size_t based caching.
	using rules_t = hamon::variant<hamon::monostate, tz::save_t, hamon::string /*, size_t*/>;

	rules_t m_rules;

	hamon::string m_format;
	// TODO TZDB the until field can contain more than just a year.
	// Parts of the UNTIL, the optional parts are default initialized
	//    optional<year> __until_;
	chrono::year m_year = chrono::year::min();
	chrono::month m_in{ January };
	tz::on_t m_on{ chrono::day{1} };
	tz::at_t m_at{ chrono::seconds{0}, tz::clock_t::local };
};

}	// namespace tz

}	// namespace detail
}	// namespace chrono
}	// namespace hamon

#endif // HAMON_CHRONO_DETAIL_TZ_HPP
