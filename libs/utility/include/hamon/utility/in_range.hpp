/**
 *	@file	in_range.hpp
 *
 *	@brief	in_range を定義
 */

#ifndef HAMON_UTILITY_IN_RANGE_HPP
#define HAMON_UTILITY_IN_RANGE_HPP

#include <utility>

#if defined(__cpp_lib_integer_comparison_functions) && (__cpp_lib_integer_comparison_functions >= 202002L)

namespace hamon
{

using std::in_range;

}	// namespace hamon

#else

#include <hamon/type_traits/make_unsigned.hpp>
#include <hamon/type_traits/is_signed.hpp>
#include <hamon/utility/detail/is_standard_integer.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <typename U, typename T,
	bool = hamon::is_signed<U>::value,
	bool = hamon::is_signed<T>::value
>
struct in_range_impl
{
	static HAMON_CONSTEXPR bool
	invoke(T t) HAMON_NOEXCEPT
	{
		return hamon::numeric_limits<U>::min() <= t && t <= hamon::numeric_limits<U>::max();
	}
};

template <typename U, typename T>
struct in_range_impl<U, T, false, true>
{
	static HAMON_CONSTEXPR bool
	invoke(T t) HAMON_NOEXCEPT
	{
		return t >= 0 && hamon::make_unsigned_t<T>(t) <= hamon::numeric_limits<U>::max();
	}
};

template <typename U, typename T>
struct in_range_impl<U, T, true, false>
{
	static HAMON_CONSTEXPR bool
	invoke(T t) HAMON_NOEXCEPT
	{
		return t <= hamon::make_unsigned_t<U>(hamon::numeric_limits<U>::max());
	}
};

}	// namespace detail

template <typename U, typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR bool
in_range(T t) HAMON_NOEXCEPT
{
	static_assert(hamon::detail::is_standard_integer<U>::value, "");
	static_assert(hamon::detail::is_standard_integer<T>::value, "");

	return detail::in_range_impl<U, T>::invoke(t);
}

}	// namespace hamon

#endif

#endif // HAMON_UTILITY_IN_RANGE_HPP
