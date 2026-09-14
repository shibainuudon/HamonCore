/**
 *	@file	clear_padding_if_needed.hpp
 *
 *	@brief	clear_padding_if_needed の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_CLEAR_PADDING_IF_NEEDED_HPP
#define HAMON_ATOMIC_DETAIL_CLEAR_PADDING_IF_NEEDED_HPP

#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/has_unique_object_representations.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

#if HAMON_HAS_BUILTIN(__builtin_clear_padding)

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool needs_clear_padding_v =
	!hamon::has_unique_object_representations_v<T> &&
	!hamon::is_same_v<T, float> &&
	!hamon::is_same_v<T, double>;

template <typename T, hamon::enable_if_t<needs_clear_padding_v<T>>* = nullptr>
constexpr void clear_padding_if_needed(T& x) noexcept
{
	if (!hamon::is_constant_evaluated())
	{
		__builtin_clear_padding(hamon::addressof(x));
	}
}

template <typename T, hamon::enable_if_t<!needs_clear_padding_v<T>>* = nullptr>
constexpr void clear_padding_if_needed(T&) noexcept
{
}

#else

template <typename T>
constexpr void clear_padding_if_needed(T&) noexcept
{
}

#endif

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_CLEAR_PADDING_IF_NEEDED_HPP
