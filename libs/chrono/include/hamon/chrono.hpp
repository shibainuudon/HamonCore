/**
 *	@file	chrono.hpp
 *
 *	@brief	Chrono library
 */

#ifndef HAMON_CHRONO_HPP
#define HAMON_CHRONO_HPP

#include <hamon/chrono/config.hpp>
#include <hamon/chrono/day.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/is_clock.hpp>
#include <hamon/chrono/last_spec.hpp>
#include <hamon/chrono/local_days.hpp>
#include <hamon/chrono/local_seconds.hpp>
#include <hamon/chrono/local_time.hpp>
#include <hamon/chrono/month.hpp>
#include <hamon/chrono/month_day.hpp>
#include <hamon/chrono/month_weekday.hpp>
#include <hamon/chrono/steady_clock.hpp>
#include <hamon/chrono/sys_days.hpp>
#include <hamon/chrono/sys_seconds.hpp>
#include <hamon/chrono/sys_time.hpp>
#include <hamon/chrono/system_clock.hpp>
#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/treat_as_floating_point.hpp>
#include <hamon/chrono/weekday.hpp>
#include <hamon/chrono/year.hpp>

#if 0

namespace std::chrono
{

// [time.clock.utc], class utc_clock
class utc_clock;

template<class Duration>
using utc_time  = time_point<utc_clock, Duration>;
using utc_seconds = utc_time<seconds>;

template<class charT, class traits, class Duration>
basic_ostream<charT, traits>&
operator<<(basic_ostream<charT, traits>& os, const utc_time<Duration>& t);
template<class charT, class traits, class Duration, class Alloc = allocator<charT>>
basic_istream<charT, traits>&
from_stream(basic_istream<charT, traits>& is, const charT* fmt,
			utc_time<Duration>& tp,
			basic_string<charT, traits, Alloc>* abbrev = nullptr,
			minutes* offset = nullptr);

struct leap_second_info;

template<class Duration>
leap_second_info get_leap_second_info(const utc_time<Duration>& ut);

// [time.clock.tai], class tai_clock
class tai_clock;

template<class Duration>
using tai_time  = time_point<tai_clock, Duration>;
using tai_seconds = tai_time<seconds>;

template<class charT, class traits, class Duration>
basic_ostream<charT, traits>&
operator<<(basic_ostream<charT, traits>& os, const tai_time<Duration>& t);
template<class charT, class traits, class Duration, class Alloc = allocator<charT>>
basic_istream<charT, traits>&
from_stream(basic_istream<charT, traits>& is, const charT* fmt,
			tai_time<Duration>& tp,
			basic_string<charT, traits, Alloc>* abbrev = nullptr,
			minutes* offset = nullptr);

// [time.clock.gps], class gps_clock
class gps_clock;

template<class Duration>
using gps_time  = time_point<gps_clock, Duration>;
using gps_seconds = gps_time<seconds>;

template<class charT, class traits, class Duration>
basic_ostream<charT, traits>&
operator<<(basic_ostream<charT, traits>& os, const gps_time<Duration>& t);
template<class charT, class traits, class Duration, class Alloc = allocator<charT>>
basic_istream<charT, traits>&
from_stream(basic_istream<charT, traits>& is, const charT* fmt,
			gps_time<Duration>& tp,
			basic_string<charT, traits, Alloc>* abbrev = nullptr,
			minutes* offset = nullptr);

// [time.clock.file], type file_clock
using file_clock = see below;

template<class Duration>
using file_time = time_point<file_clock, Duration>;

template<class charT, class traits, class Duration>
basic_ostream<charT, traits>&
operator<<(basic_ostream<charT, traits>& os, const file_time<Duration>& tp);
template<class charT, class traits, class Duration, class Alloc = allocator<charT>>
basic_istream<charT, traits>&
from_stream(basic_istream<charT, traits>& is, const charT* fmt,
			file_time<Duration>& tp,
			basic_string<charT, traits, Alloc>* abbrev = nullptr,
			minutes* offset = nullptr);

// [time.clock.hires], class high_resolution_clock
class high_resolution_clock;

// [time.clock.cast], time_point conversions
template<class DestClock, class SourceClock>
struct clock_time_conversion;

template<class DestClock, class SourceClock, class Duration>
auto clock_cast(const time_point<SourceClock, Duration>& t);



// [time.cal.ym], class year_month
class year_month;

constexpr bool operator==(const year_month& x, const year_month& y) noexcept;
constexpr strong_ordering operator<=>(const year_month& x, const year_month& y) noexcept;

constexpr year_month operator+(const year_month& ym, const months& dm) noexcept;
constexpr year_month operator+(const months& dm, const year_month& ym) noexcept;
constexpr year_month operator-(const year_month& ym, const months& dm) noexcept;
constexpr months operator-(const year_month& x, const year_month& y) noexcept;
constexpr year_month operator+(const year_month& ym, const years& dy) noexcept;
constexpr year_month operator+(const years& dy, const year_month& ym) noexcept;
constexpr year_month operator-(const year_month& ym, const years& dy) noexcept;

template<class charT, class traits>
basic_ostream<charT, traits>&
operator<<(basic_ostream<charT, traits>& os, const year_month& ym);

template<class charT, class traits, class Alloc = allocator<charT>>
basic_istream<charT, traits>&
from_stream(basic_istream<charT, traits>& is, const charT* fmt,
			year_month& ym, basic_string<charT, traits, Alloc>* abbrev = nullptr,
			minutes* offset = nullptr);

// [time.cal.ymd], class year_month_day
class year_month_day;

constexpr bool operator==(const year_month_day& x, const year_month_day& y) noexcept;
constexpr strong_ordering operator<=>(const year_month_day& x,
									  const year_month_day& y) noexcept;

constexpr year_month_day operator+(const year_month_day& ymd, const months& dm) noexcept;
constexpr year_month_day operator+(const months& dm, const year_month_day& ymd) noexcept;
constexpr year_month_day operator+(const year_month_day& ymd, const years& dy) noexcept;
constexpr year_month_day operator+(const years& dy, const year_month_day& ymd) noexcept;
constexpr year_month_day operator-(const year_month_day& ymd, const months& dm) noexcept;
constexpr year_month_day operator-(const year_month_day& ymd, const years& dy) noexcept;

template<class charT, class traits>
basic_ostream<charT, traits>&
operator<<(basic_ostream<charT, traits>& os, const year_month_day& ymd);

template<class charT, class traits, class Alloc = allocator<charT>>
basic_istream<charT, traits>&
from_stream(basic_istream<charT, traits>& is, const charT* fmt,
			year_month_day& ymd,
			basic_string<charT, traits, Alloc>* abbrev = nullptr,
			minutes* offset = nullptr);

// [time.cal.ymdlast], class year_month_day_last
class year_month_day_last;

constexpr bool operator==(const year_month_day_last& x,
						  const year_month_day_last& y) noexcept;
constexpr strong_ordering operator<=>(const year_month_day_last& x,
									  const year_month_day_last& y) noexcept;

constexpr year_month_day_last
operator+(const year_month_day_last& ymdl, const months& dm) noexcept;
constexpr year_month_day_last
operator+(const months& dm, const year_month_day_last& ymdl) noexcept;
constexpr year_month_day_last
operator+(const year_month_day_last& ymdl, const years& dy) noexcept;
constexpr year_month_day_last
operator+(const years& dy, const year_month_day_last& ymdl) noexcept;
constexpr year_month_day_last
operator-(const year_month_day_last& ymdl, const months& dm) noexcept;
constexpr year_month_day_last
operator-(const year_month_day_last& ymdl, const years& dy) noexcept;

template<class charT, class traits>
basic_ostream<charT, traits>&
operator<<(basic_ostream<charT, traits>& os, const year_month_day_last& ymdl);

// [time.cal.ymwd], class year_month_weekday
class year_month_weekday;

constexpr bool operator==(const year_month_weekday& x,
						  const year_month_weekday& y) noexcept;

constexpr year_month_weekday
operator+(const year_month_weekday& ymwd, const months& dm) noexcept;
constexpr year_month_weekday
operator+(const months& dm, const year_month_weekday& ymwd) noexcept;
constexpr year_month_weekday
operator+(const year_month_weekday& ymwd, const years& dy) noexcept;
constexpr year_month_weekday
operator+(const years& dy, const year_month_weekday& ymwd) noexcept;
constexpr year_month_weekday
operator-(const year_month_weekday& ymwd, const months& dm) noexcept;
constexpr year_month_weekday
operator-(const year_month_weekday& ymwd, const years& dy) noexcept;

template<class charT, class traits>
basic_ostream<charT, traits>&
operator<<(basic_ostream<charT, traits>& os, const year_month_weekday& ymwd);

// [time.cal.ymwdlast], class year_month_weekday_last
class year_month_weekday_last;

constexpr bool operator==(const year_month_weekday_last& x,
						  const year_month_weekday_last& y) noexcept;

constexpr year_month_weekday_last
operator+(const year_month_weekday_last& ymwdl, const months& dm) noexcept;
constexpr year_month_weekday_last
operator+(const months& dm, const year_month_weekday_last& ymwdl) noexcept;
constexpr year_month_weekday_last
operator+(const year_month_weekday_last& ymwdl, const years& dy) noexcept;
constexpr year_month_weekday_last
operator+(const years& dy, const year_month_weekday_last& ymwdl) noexcept;
constexpr year_month_weekday_last
operator-(const year_month_weekday_last& ymwdl, const months& dm) noexcept;
constexpr year_month_weekday_last
operator-(const year_month_weekday_last& ymwdl, const years& dy) noexcept;

template<class charT, class traits>
basic_ostream<charT, traits>&
operator<<(basic_ostream<charT, traits>& os, const year_month_weekday_last& ymwdl);

// [time.cal.operators], civil calendar conventional syntax operators
constexpr year_month
operator/(const year& y, const month& m) noexcept;
constexpr year_month
operator/(const year& y, int m) noexcept;
constexpr year_month_day
operator/(const year_month& ym, const day& d) noexcept;
constexpr year_month_day
operator/(const year_month& ym, int d) noexcept;
constexpr year_month_day
operator/(const year& y, const month_day& md) noexcept;
constexpr year_month_day
operator/(int y, const month_day& md) noexcept;
constexpr year_month_day
operator/(const month_day& md, const year& y) noexcept;
constexpr year_month_day
operator/(const month_day& md, int y) noexcept;
constexpr year_month_day_last
operator/(const year_month& ym, last_spec) noexcept;
constexpr year_month_day_last
operator/(const year& y, const month_day_last& mdl) noexcept;
constexpr year_month_day_last
operator/(int y, const month_day_last& mdl) noexcept;
constexpr year_month_day_last
operator/(const month_day_last& mdl, const year& y) noexcept;
constexpr year_month_day_last
operator/(const month_day_last& mdl, int y) noexcept;
constexpr year_month_weekday
operator/(const year_month& ym, const weekday_indexed& wdi) noexcept;
constexpr year_month_weekday
operator/(const year& y, const month_weekday& mwd) noexcept;
constexpr year_month_weekday
operator/(int y, const month_weekday& mwd) noexcept;
constexpr year_month_weekday
operator/(const month_weekday& mwd, const year& y) noexcept;
constexpr year_month_weekday
operator/(const month_weekday& mwd, int y) noexcept;
constexpr year_month_weekday_last
operator/(const year_month& ym, const weekday_last& wdl) noexcept;
constexpr year_month_weekday_last
operator/(const year& y, const month_weekday_last& mwdl) noexcept;
constexpr year_month_weekday_last
operator/(int y, const month_weekday_last& mwdl) noexcept;
constexpr year_month_weekday_last
operator/(const month_weekday_last& mwdl, const year& y) noexcept;
constexpr year_month_weekday_last
operator/(const month_weekday_last& mwdl, int y) noexcept;

// [time.hms], class template hh_mm_ss
template<class Duration> class hh_mm_ss;

template<class charT, class traits, class Duration>
basic_ostream<charT, traits>&
operator<<(basic_ostream<charT, traits>& os, const hh_mm_ss<Duration>& hms);

// [time.12], 12/24 hour functions
constexpr bool is_am(const hours& h) noexcept;
constexpr bool is_pm(const hours& h) noexcept;
constexpr hours make12(const hours& h) noexcept;
constexpr hours make24(const hours& h, bool is_pm) noexcept;

// [time.zone.db], time zone database
struct tzdb;
class tzdb_list;

// [time.zone.db.access], time zone database access
const tzdb& get_tzdb();
tzdb_list& get_tzdb_list();
const time_zone* locate_zone(string_view tz_name);
const time_zone* current_zone();

// [time.zone.db.remote], remote time zone database support
const tzdb& reload_tzdb();
string remote_version();

// [time.zone.exception], exception classes
class nonexistent_local_time;
class ambiguous_local_time;

// [time.zone.info], information classes
struct sys_info;
template<class charT, class traits>
basic_ostream<charT, traits>&
operator<<(basic_ostream<charT, traits>& os, const sys_info& si);

struct local_info;
template<class charT, class traits>
basic_ostream<charT, traits>&
operator<<(basic_ostream<charT, traits>& os, const local_info& li);

// [time.zone.timezone], class time_zone
enum class choose { earliest, latest };
class time_zone;

bool operator==(const time_zone& x, const time_zone& y) noexcept;
strong_ordering operator<=>(const time_zone& x, const time_zone& y) noexcept;

// [time.zone.zonedtraits], class template zoned_traits
template<class T> struct zoned_traits;

// [time.zone.zonedtime], class template zoned_time
template<class Duration, class TimeZonePtr = const time_zone*> class zoned_time;

using zoned_seconds = zoned_time<seconds>;

template<class Duration1, class Duration2, class TimeZonePtr>
bool operator==(const zoned_time<Duration1, TimeZonePtr>& x,
				const zoned_time<Duration2, TimeZonePtr>& y);

template<class charT, class traits, class Duration, class TimeZonePtr>
basic_ostream<charT, traits>&
operator<<(basic_ostream<charT, traits>& os,
		   const zoned_time<Duration, TimeZonePtr>& t);

// [time.zone.leap], leap second support
class leap_second;

constexpr bool operator==(const leap_second& x, const leap_second& y);
constexpr strong_ordering operator<=>(const leap_second& x, const leap_second& y);

template<class Duration>
constexpr bool operator==(const leap_second& x, const sys_time<Duration>& y);
template<class Duration>
constexpr bool operator< (const leap_second& x, const sys_time<Duration>& y);
template<class Duration>
constexpr bool operator< (const sys_time<Duration>& x, const leap_second& y);
template<class Duration>
constexpr bool operator> (const leap_second& x, const sys_time<Duration>& y);
template<class Duration>
constexpr bool operator> (const sys_time<Duration>& x, const leap_second& y);
template<class Duration>
constexpr bool operator<=(const leap_second& x, const sys_time<Duration>& y);
template<class Duration>
constexpr bool operator<=(const sys_time<Duration>& x, const leap_second& y);
template<class Duration>
constexpr bool operator>=(const leap_second& x, const sys_time<Duration>& y);
template<class Duration>
constexpr bool operator>=(const sys_time<Duration>& x, const leap_second& y);
template<class Duration>
requires three_way_comparable_with<sys_seconds, sys_time<Duration>>
constexpr auto operator<=>(const leap_second& x, const sys_time<Duration>& y);

// [time.zone.link], class time_zone_link
class time_zone_link;

bool operator==(const time_zone_link& x, const time_zone_link& y);
strong_ordering operator<=>(const time_zone_link& x, const time_zone_link& y);

// [time.format], formatting
template<class Duration> struct local-time-format-t;        // exposition only
template<class Duration>
local-time-format-t<Duration>
local_time_format(local_time<Duration> time, const string* abbrev = nullptr,
				  const seconds* offset_sec = nullptr);
}

namespace std
{

template<class Rep, class Period, class charT>
struct formatter<chrono::duration<Rep, Period>, charT>;
template<class Duration, class charT>
struct formatter<chrono::sys_time<Duration>, charT>;
template<class Duration, class charT>
struct formatter<chrono::utc_time<Duration>, charT>;
template<class Duration, class charT>
struct formatter<chrono::tai_time<Duration>, charT>;
template<class Duration, class charT>
struct formatter<chrono::gps_time<Duration>, charT>;
template<class Duration, class charT>
struct formatter<chrono::file_time<Duration>, charT>;
template<class Duration, class charT>
struct formatter<chrono::local_time<Duration>, charT>;
template<class Duration, class charT>
struct formatter<chrono::local-time-format-t<Duration>, charT>;
template<class charT> struct formatter<chrono::day, charT>;
template<class charT> struct formatter<chrono::month, charT>;
template<class charT> struct formatter<chrono::year, charT>;
template<class charT> struct formatter<chrono::weekday, charT>;
template<class charT> struct formatter<chrono::weekday_indexed, charT>;
template<class charT> struct formatter<chrono::weekday_last, charT>;
template<class charT> struct formatter<chrono::month_day, charT>;
template<class charT> struct formatter<chrono::month_day_last, charT>;
template<class charT> struct formatter<chrono::month_weekday, charT>;
template<class charT> struct formatter<chrono::month_weekday_last, charT>;
template<class charT> struct formatter<chrono::year_month, charT>;
template<class charT> struct formatter<chrono::year_month_day, charT>;
template<class charT> struct formatter<chrono::year_month_day_last, charT>;
template<class charT> struct formatter<chrono::year_month_weekday, charT>;
template<class charT> struct formatter<chrono::year_month_weekday_last, charT>;
template<class Rep, class Period, class charT>
struct formatter<chrono::hh_mm_ss<duration<Rep, Period>>, charT>;
template<class charT> struct formatter<chrono::sys_info, charT>;
template<class charT> struct formatter<chrono::local_info, charT>;
template<class Duration, class TimeZonePtr, class charT>
struct formatter<chrono::zoned_time<Duration, TimeZonePtr>, charT>;

}

namespace std::chrono
{

// [time.parse], parsing
template<class charT, class Parsable>
unspecified
parse(const charT* fmt, Parsable& tp);
template<class charT, class traits, class Alloc, class Parsable>
unspecified
parse(const basic_string<charT, traits, Alloc>& fmt, Parsable& tp);

template<class charT, class traits, class Alloc, class Parsable>
unspecified
parse(const charT* fmt, Parsable& tp,
	  basic_string<charT, traits, Alloc>& abbrev);
template<class charT, class traits, class Alloc, class Parsable>
unspecified
parse(const basic_string<charT, traits, Alloc>& fmt, Parsable& tp,
	  basic_string<charT, traits, Alloc>& abbrev);

template<class charT, class Parsable>
unspecified
parse(const charT* fmt, Parsable& tp, minutes& offset);
template<class charT, class traits, class Alloc, class Parsable>
unspecified
parse(const basic_string<charT, traits, Alloc>& fmt, Parsable& tp,
	  minutes& offset);

template<class charT, class traits, class Alloc, class Parsable>
unspecified
parse(const charT* fmt, Parsable& tp,
	  basic_string<charT, traits, Alloc>& abbrev, minutes& offset);
template<class charT, class traits, class Alloc, class Parsable>
unspecified
parse(const basic_string<charT, traits, Alloc>& fmt, Parsable& tp,
	  basic_string<charT, traits, Alloc>& abbrev, minutes& offset);

}

namespace std {
  // [time.hash], hash support
template<class T> struct hash;
template<class Rep, class Period> struct hash<chrono::duration<Rep, Period>>;
template<class Clock, class Duration> struct hash<chrono::time_point<Clock, Duration>>;
template<> struct hash<chrono::day>;
template<> struct hash<chrono::month>;
template<> struct hash<chrono::year>;
template<> struct hash<chrono::weekday>;
template<> struct hash<chrono::weekday_indexed>;
template<> struct hash<chrono::weekday_last>;
template<> struct hash<chrono::month_day>;
template<> struct hash<chrono::month_day_last>;
template<> struct hash<chrono::month_weekday>;
template<> struct hash<chrono::month_weekday_last>;
template<> struct hash<chrono::year_month>;
template<> struct hash<chrono::year_month_day>;
template<> struct hash<chrono::year_month_day_last>;
template<> struct hash<chrono::year_month_weekday>;
template<> struct hash<chrono::year_month_weekday_last>;
template<class Duration, class TimeZonePtr>
struct hash<chrono::zoned_time<Duration, TimeZonePtr>>;
template<> struct hash<chrono::leap_second>;
}
#endif

#endif // HAMON_CHRONO_HPP
