/**
 *	@file	move_if_noexcept.hpp
 *
 *	@brief	move_if_noexcept を定義
 */

#ifndef HAMON_UTILITY_MOVE_IF_NOEXCEPT_HPP
#define HAMON_UTILITY_MOVE_IF_NOEXCEPT_HPP

#include <hamon/utility/move.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 22.2.4 Forward/move helpers[forward]

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
hamon::conditional_t<  
	!hamon::is_nothrow_move_constructible_v<T> &&
	hamon::is_copy_constructible_v<T>,
	T const&,
	T&&>
move_if_noexcept(T& x) HAMON_NOEXCEPT
{
	// [forward]/12
	return hamon::move(x);
}

}	// namespace hamon

#endif // HAMON_UTILITY_MOVE_IF_NOEXCEPT_HPP
