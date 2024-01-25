/**
 *	@file	to_string.hpp
 *
 *	@brief	to_string の定義
 */

#ifndef HAMON_STRING_TO_STRING_HPP
#define HAMON_STRING_TO_STRING_HPP

#include <hamon/string/config.hpp>

#if defined(HAMON_USE_STD_STRING)

#include <string>

namespace hamon
{

using std::to_string;

}	// namespace hamon

#else

#include <hamon/string/string.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_floating_point.hpp>
#include <hamon/type_traits/is_signed.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/limits.hpp>
#include <hamon/cstddef.hpp>
#include <hamon/config.hpp>
#include <cstdio>	// snprintf

namespace hamon
{

namespace detail
{

#if 0	// TODO

template <typename T>
hamon::string to_string_impl(const char* /*fmt*/, T val)
{
	// since C++26
	// [string.conversions]/7
	return std::format("{}", val);
}

#else

template <typename T, typename = hamon::enable_if_t<hamon::is_floating_point<T>::value>>
HAMON_CXX11_CONSTEXPR hamon::size_t to_string_buffer_size(hamon::detail::overload_priority<2>)
{
	return hamon::numeric_limits<T>::max_exponent10 + 1
		+ 6		// fixed precision (printf's default)
		+ 3;	// '-' + '.' + '\0'
}

template <typename T, typename = hamon::enable_if_t<hamon::is_signed<T>::value>>
HAMON_CXX11_CONSTEXPR hamon::size_t to_string_buffer_size(hamon::detail::overload_priority<1>)
{
	return hamon::numeric_limits<T>::digits10 + 1
		+ 2;	// '-' + '\0'
}

template <typename T, typename = hamon::enable_if_t<hamon::is_unsigned<T>::value>>
HAMON_CXX11_CONSTEXPR hamon::size_t to_string_buffer_size(hamon::detail::overload_priority<0>)
{
	return hamon::numeric_limits<T>::digits10 + 1
		+ 1;	// '\0'
}

template <typename T>
HAMON_CXX11_CONSTEXPR hamon::size_t to_string_buffer_size()
{
	return to_string_buffer_size<T>(hamon::detail::overload_priority<2>{});
}

template <typename T>
hamon::string to_string_impl(const char* fmt, T val)
{
	auto constexpr size = to_string_buffer_size<T>();
	char buf[size];
	std::snprintf(buf, size, fmt, val);
	return buf;
}

#endif

}	// namespace detail

// 23.4.5 Numeric conversions[string.conversions]

inline hamon::string to_string(int val)
{
	return detail::to_string_impl("%d", val);
}

inline hamon::string to_string(unsigned val)
{
	return detail::to_string_impl("%u", val);
}

inline hamon::string to_string(long val)
{
	return detail::to_string_impl("%ld", val);
}

inline hamon::string to_string(unsigned long val)
{
	return detail::to_string_impl("%lu", val);
}

inline hamon::string to_string(long long val)
{
	return detail::to_string_impl("%lld", val);
}

inline hamon::string to_string(unsigned long long val)
{
	return detail::to_string_impl("%llu", val);
}

inline hamon::string to_string(float val)
{
	return detail::to_string_impl("%f", val);
}

inline hamon::string to_string(double val)
{
	return detail::to_string_impl("%f", val);
}

inline hamon::string to_string(long double val)
{
	return detail::to_string_impl("%Lf", val);
}

}	// namespace hamon

#endif

#endif // HAMON_STRING_TO_STRING_HPP
