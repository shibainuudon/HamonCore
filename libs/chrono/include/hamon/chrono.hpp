/**
 *	@file	chrono.hpp
 *
 *	@brief	Chrono library
 */

#ifndef HAMON_CHRONO_HPP
#define HAMON_CHRONO_HPP

#include <hamon/chrono/choose.hpp>
#include <hamon/chrono/clock_cast.hpp>
#include <hamon/chrono/clock_time_conversion.hpp>
#include <hamon/chrono/config.hpp>
#include <hamon/chrono/day.hpp>
#include <hamon/chrono/duration.hpp>
#include <hamon/chrono/file_clock.hpp>
#include <hamon/chrono/file_time.hpp>
#include <hamon/chrono/get_leap_second_info.hpp>
#include <hamon/chrono/get_tzdb.hpp>
#include <hamon/chrono/get_tzdb_list.hpp>
#include <hamon/chrono/gps_clock.hpp>
#include <hamon/chrono/gps_seconds.hpp>
#include <hamon/chrono/gps_time.hpp>
#include <hamon/chrono/hh_mm_ss.hpp>
#include <hamon/chrono/high_resolution_clock.hpp>
#include <hamon/chrono/is_clock.hpp>
#include <hamon/chrono/last_spec.hpp>
#include <hamon/chrono/leap_second.hpp>
#include <hamon/chrono/leap_second_info.hpp>
#include <hamon/chrono/local_days.hpp>
#include <hamon/chrono/local_info.hpp>
#include <hamon/chrono/local_seconds.hpp>
#include <hamon/chrono/local_time.hpp>
#include <hamon/chrono/locate_zone.hpp>
#include <hamon/chrono/month.hpp>
#include <hamon/chrono/month_day.hpp>
#include <hamon/chrono/month_weekday.hpp>
#include <hamon/chrono/steady_clock.hpp>
#include <hamon/chrono/sys_days.hpp>
#include <hamon/chrono/sys_info.hpp>
#include <hamon/chrono/sys_seconds.hpp>
#include <hamon/chrono/sys_time.hpp>
#include <hamon/chrono/system_clock.hpp>
#include <hamon/chrono/tai_clock.hpp>
#include <hamon/chrono/tai_seconds.hpp>
#include <hamon/chrono/tai_time.hpp>
#include <hamon/chrono/time_point.hpp>
#include <hamon/chrono/time_zone.hpp>
#include <hamon/chrono/time_zone_link.hpp>
#include <hamon/chrono/treat_as_floating_point.hpp>
#include <hamon/chrono/tzdb.hpp>
#include <hamon/chrono/tzdb_list.hpp>
#include <hamon/chrono/utc_clock.hpp>
#include <hamon/chrono/utc_seconds.hpp>
#include <hamon/chrono/utc_time.hpp>
#include <hamon/chrono/weekday.hpp>
#include <hamon/chrono/year.hpp>
#include <hamon/chrono/year_month.hpp>
#include <hamon/chrono/year_month_day.hpp>
#include <hamon/chrono/year_month_weekday.hpp>

#if 0

namespace std::chrono
{

// [time.clock.utc], class utc_clock
//class utc_clock;

//template<class Duration>
//using utc_time  = time_point<utc_clock, Duration>;
//using utc_seconds = utc_time<seconds>;

//template<class charT, class traits, class Duration>
//basic_ostream<charT, traits>&
//operator<<(basic_ostream<charT, traits>& os, const utc_time<Duration>& t);
//template<class charT, class traits, class Duration, class Alloc = allocator<charT>>
//basic_istream<charT, traits>&
//from_stream(basic_istream<charT, traits>& is, const charT* fmt,
//			utc_time<Duration>& tp,
//			basic_string<charT, traits, Alloc>* abbrev = nullptr,
//			minutes* offset = nullptr);

//struct leap_second_info;

//template<class Duration>
//leap_second_info get_leap_second_info(const utc_time<Duration>& ut);

// [time.clock.tai], class tai_clock
//class tai_clock;

//template<class Duration>
//using tai_time  = time_point<tai_clock, Duration>;
//using tai_seconds = tai_time<seconds>;

//template<class charT, class traits, class Duration>
//basic_ostream<charT, traits>&
//operator<<(basic_ostream<charT, traits>& os, const tai_time<Duration>& t);
//template<class charT, class traits, class Duration, class Alloc = allocator<charT>>
//basic_istream<charT, traits>&
//from_stream(basic_istream<charT, traits>& is, const charT* fmt,
//			tai_time<Duration>& tp,
//			basic_string<charT, traits, Alloc>* abbrev = nullptr,
//			minutes* offset = nullptr);

// [time.clock.gps], class gps_clock
//class gps_clock;
//
//template<class Duration>
//using gps_time  = time_point<gps_clock, Duration>;
//using gps_seconds = gps_time<seconds>;
//
//template<class charT, class traits, class Duration>
//basic_ostream<charT, traits>&
//operator<<(basic_ostream<charT, traits>& os, const gps_time<Duration>& t);
//template<class charT, class traits, class Duration, class Alloc = allocator<charT>>
//basic_istream<charT, traits>&
//from_stream(basic_istream<charT, traits>& is, const charT* fmt,
//			gps_time<Duration>& tp,
//			basic_string<charT, traits, Alloc>* abbrev = nullptr,
//			minutes* offset = nullptr);

// [time.clock.file], type file_clock
//using file_clock = see below;

//template<class Duration>
//using file_time = time_point<file_clock, Duration>;

//template<class charT, class traits, class Duration>
//basic_ostream<charT, traits>&
//operator<<(basic_ostream<charT, traits>& os, const file_time<Duration>& tp);
//template<class charT, class traits, class Duration, class Alloc = allocator<charT>>
//basic_istream<charT, traits>&
//from_stream(basic_istream<charT, traits>& is, const charT* fmt,
//			file_time<Duration>& tp,
//			basic_string<charT, traits, Alloc>* abbrev = nullptr,
//			minutes* offset = nullptr);

//// [time.clock.hires], class high_resolution_clock
//class high_resolution_clock;

//// [time.clock.cast], time_point conversions
//template<class DestClock, class SourceClock>
//struct clock_time_conversion;

//template<class DestClock, class SourceClock, class Duration>
//auto clock_cast(const time_point<SourceClock, Duration>& t);







//// [time.hms], class template hh_mm_ss
//template<class Duration> class hh_mm_ss;
//
//template<class charT, class traits, class Duration>
//basic_ostream<charT, traits>&
//operator<<(basic_ostream<charT, traits>& os, const hh_mm_ss<Duration>& hms);

// [time.12], 12/24 hour functions
constexpr bool is_am(const hours& h) noexcept;
constexpr bool is_pm(const hours& h) noexcept;
constexpr hours make12(const hours& h) noexcept;
constexpr hours make24(const hours& h, bool is_pm) noexcept;

// [time.zone.db], time zone database
//struct tzdb;
//class tzdb_list;

// [time.zone.db.access], time zone database access
//const tzdb& get_tzdb();
//tzdb_list& get_tzdb_list();
//const time_zone* locate_zone(string_view tz_name);
const time_zone* current_zone();

// [time.zone.db.remote], remote time zone database support
const tzdb& reload_tzdb();
string remote_version();

// [time.zone.exception], exception classes
class nonexistent_local_time;
class ambiguous_local_time;

//// [time.zone.timezone], class time_zone
//enum class choose { earliest, latest };
//class time_zone;
//
//bool operator==(const time_zone& x, const time_zone& y) noexcept;
//strong_ordering operator<=>(const time_zone& x, const time_zone& y) noexcept;

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

//// [time.zone.leap], leap second support
//class leap_second;
//
//constexpr bool operator==(const leap_second& x, const leap_second& y);
//constexpr strong_ordering operator<=>(const leap_second& x, const leap_second& y);
//
//template<class Duration>
//constexpr bool operator==(const leap_second& x, const sys_time<Duration>& y);
//template<class Duration>
//constexpr bool operator< (const leap_second& x, const sys_time<Duration>& y);
//template<class Duration>
//constexpr bool operator< (const sys_time<Duration>& x, const leap_second& y);
//template<class Duration>
//constexpr bool operator> (const leap_second& x, const sys_time<Duration>& y);
//template<class Duration>
//constexpr bool operator> (const sys_time<Duration>& x, const leap_second& y);
//template<class Duration>
//constexpr bool operator<=(const leap_second& x, const sys_time<Duration>& y);
//template<class Duration>
//constexpr bool operator<=(const sys_time<Duration>& x, const leap_second& y);
//template<class Duration>
//constexpr bool operator>=(const leap_second& x, const sys_time<Duration>& y);
//template<class Duration>
//constexpr bool operator>=(const sys_time<Duration>& x, const leap_second& y);
//template<class Duration>
//requires three_way_comparable_with<sys_seconds, sys_time<Duration>>
//constexpr auto operator<=>(const leap_second& x, const sys_time<Duration>& y);

//// [time.zone.link], class time_zone_link
//class time_zone_link;
//
//bool operator==(const time_zone_link& x, const time_zone_link& y);
//strong_ordering operator<=>(const time_zone_link& x, const time_zone_link& y);

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
