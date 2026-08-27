/**
 *	@file	cmp_less.hpp
 *
 *	@brief	cmp_less を定義
 */

#ifndef HAMON_UTILITY_CMP_LESS_HPP
#define HAMON_UTILITY_CMP_LESS_HPP

#include <hamon/utility/detail/is_standard_integer.hpp>
#include <hamon/type_traits/make_unsigned.hpp>
#include <hamon/type_traits/is_signed.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 22.2.7 Integer comparison functions[utility.intcmp]

namespace detail
{

// [utility.intcmp]/5

template <typename T, typename U,
	bool = hamon::is_signed<T>::value,
	bool = hamon::is_signed<U>::value
>
struct cmp_less_impl
{
	static HAMON_CONSTEXPR bool
	invoke(T t, U u) HAMON_NOEXCEPT
	{
		return t < u;
	}
};

template <typename T, typename U>
struct cmp_less_impl<T, U, true, false>
{
	static HAMON_CONSTEXPR bool
	invoke(T t, U u) HAMON_NOEXCEPT
	{
		return t < 0 || hamon::make_unsigned_t<T>(t) < u;
	}
};

template <typename T, typename U>
struct cmp_less_impl<T, U, false, true>
{
	static HAMON_CONSTEXPR bool
	invoke(T t, U u) HAMON_NOEXCEPT
	{
		return u >= 0 && t < hamon::make_unsigned_t<U>(u);
	}
};

}	// namespace detail

template <typename T, typename U>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
bool cmp_less(T t, U u) HAMON_NOEXCEPT
{
	// [utility.intcmp]/4
	static_assert(hamon::detail::is_standard_integer<T>::value, "");
	static_assert(hamon::detail::is_standard_integer<U>::value, "");

	return detail::cmp_less_impl<T, U>::invoke(t, u);
}

}	// namespace hamon

#endif // HAMON_UTILITY_CMP_LESS_HPP
