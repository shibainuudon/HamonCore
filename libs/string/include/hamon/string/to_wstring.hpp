/**
 *	@file	to_wstring.hpp
 *
 *	@brief	to_wstring の定義
 */

#ifndef HAMON_STRING_TO_WSTRING_HPP
#define HAMON_STRING_TO_WSTRING_HPP

#include <hamon/string/config.hpp>

#if defined(HAMON_USE_STD_STRING)

#include <string>

namespace hamon
{

using std::to_wstring;

}	// namespace hamon

#else

#include <hamon/string/wstring.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_floating_point.hpp>
#include <hamon/type_traits/is_signed.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/limits.hpp>
#include <hamon/cstddef.hpp>
#include <hamon/config.hpp>
#include <cwchar>	// swprintf

namespace hamon
{

namespace detail
{

#if 0	// TODO

template <typename T>
hamon::wstring to_wstring_impl(const wchar_t* /*fmt*/, T val)
{
	// since C++26
	// [string.conversions]/14
	return std::format(L"{}", val);
}

#else

template <typename T, typename = hamon::enable_if_t<hamon::is_floating_point<T>::value>>
HAMON_CXX11_CONSTEXPR hamon::size_t to_wstring_buffer_size(hamon::detail::overload_priority<2>)
{
	return hamon::numeric_limits<T>::max_exponent10 + 1
		+ 6		// fixed precision (printf's default)
		+ 3;	// '-' + '.' + '\0'
}

template <typename T, typename = hamon::enable_if_t<hamon::is_signed<T>::value>>
HAMON_CXX11_CONSTEXPR hamon::size_t to_wstring_buffer_size(hamon::detail::overload_priority<1>)
{
	return hamon::numeric_limits<T>::digits10 + 1
		+ 2;	// '-' + '\0'
}

template <typename T, typename = hamon::enable_if_t<hamon::is_unsigned<T>::value>>
HAMON_CXX11_CONSTEXPR hamon::size_t to_wstring_buffer_size(hamon::detail::overload_priority<0>)
{
	return hamon::numeric_limits<T>::digits10 + 1
		+ 1;	// '\0'
}

template <typename T>
HAMON_CXX11_CONSTEXPR hamon::size_t to_wstring_buffer_size()
{
	return to_wstring_buffer_size<T>(hamon::detail::overload_priority<2>{});
}

template <typename T>
hamon::wstring to_wstring_impl(const wchar_t* fmt, T val)
{
	auto constexpr size = to_wstring_buffer_size<T>();
	wchar_t buf[size];
	std::swprintf(buf, size, fmt, val);
	return buf;
}

#endif

}	// namespace detail

// 23.4.5 Numeric conversions[string.conversions]

inline hamon::wstring to_wstring(int val)
{
	return detail::to_wstring_impl(L"%d", val);
}

inline hamon::wstring to_wstring(unsigned val)
{
	return detail::to_wstring_impl(L"%u", val);
}

inline hamon::wstring to_wstring(long val)
{
	return detail::to_wstring_impl(L"%ld", val);
}

inline hamon::wstring to_wstring(unsigned long val)
{
	return detail::to_wstring_impl(L"%lu", val);
}

inline hamon::wstring to_wstring(long long val)
{
	return detail::to_wstring_impl(L"%lld", val);
}

inline hamon::wstring to_wstring(unsigned long long val)
{
	return detail::to_wstring_impl(L"%llu", val);
}

inline hamon::wstring to_wstring(float val)
{
	return detail::to_wstring_impl(L"%f", val);
}

inline hamon::wstring to_wstring(double val)
{
	return detail::to_wstring_impl(L"%f", val);
}

inline hamon::wstring to_wstring(long double val)
{
	return detail::to_wstring_impl(L"%Lf", val);
}

}	// namespace hamon

#endif

#endif // HAMON_STRING_TO_WSTRING_HPP
