/**
 *	@file	literals.hpp
 *
 *	@brief	リテラルの定義
 */

#ifndef HAMON_CHRONO_DURATION_LITERALS_HPP
#define HAMON_CHRONO_DURATION_LITERALS_HPP

#include <hamon/chrono/duration/typedefs.hpp>

// 29.5.9 Suffixes for duration literals[time.duration.literals]

namespace hamon
{

inline namespace literals
{
inline namespace chrono_literals
{

// アンダースコアで始まらないユーザー定義リテラルのサフィックス名は、
// 標準C++の将来の拡張のために予約されているため、アンダースコアから始まる名前に変更した。

HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
chrono::hours
operator"" _h(unsigned long long hours) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [time.duration.literals]/5
	return chrono::hours(hours);
}

HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
chrono::duration<double, std::ratio<3600, 1>>
operator"" _h(long double hours) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [time.duration.literals]/5
	return chrono::duration<double, std::ratio<3600, 1>>(hours);
}

HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
chrono::minutes
operator"" _min(unsigned long long minutes) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [time.duration.literals]/6
	return chrono::minutes(minutes);
}

HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
chrono::duration<double, std::ratio<60, 1>>
operator"" _min(long double minutes) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [time.duration.literals]/6
	return chrono::duration<double, std::ratio<60, 1>>(minutes);
}

HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
chrono::seconds
operator"" _s(unsigned long long sec) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [time.duration.literals]/7
	return chrono::seconds(sec);
}

HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
chrono::duration<double>
operator"" _s(long double sec) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [time.duration.literals]/7
	return chrono::duration<double>(sec);
}

HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
chrono::milliseconds
operator"" _ms(unsigned long long msec) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [time.duration.literals]/9
	return chrono::milliseconds(msec);
}

HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
chrono::duration<double, std::milli>
operator"" _ms(long double msec) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [time.duration.literals]/9
	return chrono::duration<double, std::milli>(msec);
}

HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
chrono::microseconds
operator"" _us(unsigned long long usec) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [time.duration.literals]/10
	return chrono::microseconds(usec);
}

HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
chrono::duration<double, std::micro>
operator"" _us(long double usec) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [time.duration.literals]/10
	return chrono::duration<double, std::micro>(usec);
}

HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
chrono::nanoseconds
operator"" _ns(unsigned long long nsec) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [time.duration.literals]/11
	return chrono::nanoseconds(nsec);
}

HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
chrono::duration<double, std::nano>
operator"" _ns(long double nsec) HAMON_NOEXCEPT	// noexcept as an extension
{
	// [time.duration.literals]/11
	return chrono::duration<double, std::nano>(nsec);
}

}	// inline namespace chrono_literals
}	// inline namespace literals

namespace chrono {
using namespace literals::chrono_literals;
}

}	// namespace hamon

#endif // HAMON_CHRONO_DURATION_LITERALS_HPP
