/**
 *	@file	to_chars.hpp
 *
 *	@brief	to_chars の定義
 */

#ifndef HAMON_CHARCONV_TO_CHARS_HPP
#define HAMON_CHARCONV_TO_CHARS_HPP

#include <hamon/charconv/config.hpp>

#if defined(HAMON_USE_STD_CHARCONV)

#include <charconv>

namespace hamon
{

using std::to_chars_result;
using std::to_chars;

}	// namespace hamon

#else

#include <hamon/charconv/detail/negate_unsigned.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <hamon/type_traits/make_unsigned.hpp>
#include <hamon/config.hpp>
#include <system_error>

namespace hamon
{

struct to_chars_result
{
	char* ptr;
	std::errc ec;
#if defined(HAMON_HAS_CXX20_CONSISTENT_DEFAULTED_COMPARISONS)
	friend bool operator==(to_chars_result const&, to_chars_result const&) = default;
#else
	friend HAMON_CXX11_CONSTEXPR bool
	operator==(to_chars_result const& lhs, to_chars_result const& rhs)
	{
		return
			lhs.ptr == rhs.ptr &&
			lhs.ec  == rhs.ec;
	}
#endif
#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
	friend HAMON_CXX11_CONSTEXPR bool
	operator!=(to_chars_result const& lhs, to_chars_result const& rhs)
	{
		return !(lhs == rhs);
	}
#endif
};

namespace charconv_detail
{

template <typename T>
inline HAMON_CXX14_CONSTEXPR int
to_chars_integral_width(T value, T base)
{
	int result = 0;
	
	do
	{
		value = static_cast<T>(value / base);
		++result;
	}
	while (value != 0);

	return result;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR to_chars_result
to_chars_unsigned_integral(char* first, char* last, T value, T base)
{
	auto n = to_chars_integral_width(value, base);
	if (n > (last - first))
	{
		return {last, std::errc::value_too_large};
	}

	last = first + n;
	auto p = last;
	do
	{
		auto c = value % base;
		value = static_cast<T>(value / base);
		*--p = "0123456789abcdefghijklmnopqrstuvwxyz"[c];
	}
	while (value != 0);

	return {last, std::errc{}};
}

template <typename T, typename = hamon::enable_if_t<hamon::is_unsigned<T>::value>>
inline HAMON_CXX14_CONSTEXPR to_chars_result
to_chars_integral(char* first, char* last, T value, int base, hamon::detail::overload_priority<1>)
{
	return to_chars_unsigned_integral(first, last, value, static_cast<T>(base));
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR to_chars_result
to_chars_integral(char* first, char* last, T value, int base, hamon::detail::overload_priority<0>)
{
	using UT = hamon::make_unsigned_t<T>;
	auto x = static_cast<UT>(value);
	if (value < 0 && first != last)
	{
		*first++ = '-';
		x = negate_unsigned(x);
	}
	return to_chars_unsigned_integral(first, last, x, static_cast<UT>(base));
}

}	// namespace charconv_detail

template <typename T, typename = hamon::enable_if_t<hamon::is_integral<T>::value>>
inline HAMON_CXX14_CONSTEXPR to_chars_result
to_chars(char* first, char* last, T value, int base = 10)
{
	return hamon::charconv_detail::to_chars_integral(
		first, last, value, base, hamon::detail::overload_priority<1>{});
}

to_chars_result to_chars(char*, char*, bool, int = 10) = delete;

}	// namespace hamon

#endif

#endif // HAMON_CHARCONV_TO_CHARS_HPP
