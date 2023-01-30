/**
 *	@file	cmp_less.hpp
 *
 *	@brief	cmp_less を定義
 */

#ifndef HAMON_UTILITY_CMP_LESS_HPP
#define HAMON_UTILITY_CMP_LESS_HPP

#include <utility>

#if defined(__cpp_lib_integer_comparison_functions) && (__cpp_lib_integer_comparison_functions >= 202002L)

namespace hamon
{

using std::cmp_less;

}	// namespace hamon

#else

#include <hamon/type_traits/make_unsigned.hpp>
#include <hamon/utility/detail/is_standard_integer.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

namespace detail
{

template <typename T, typename U,
	bool = std::is_signed<T>::value,
	bool = std::is_signed<U>::value
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
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
cmp_less(T t, U u) HAMON_NOEXCEPT
{
	static_assert(hamon::detail::is_standard_integer<T>::value, "");
	static_assert(hamon::detail::is_standard_integer<U>::value, "");

	return detail::cmp_less_impl<T, U>::invoke(t, u);
}

}	// namespace hamon

#endif

#endif // HAMON_UTILITY_CMP_LESS_HPP
