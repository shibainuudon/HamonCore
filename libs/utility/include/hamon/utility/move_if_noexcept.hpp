/**
 *	@file	move_if_noexcept.hpp
 *
 *	@brief	move_if_noexcept を定義
 */

#ifndef HAMON_UTILITY_MOVE_IF_NOEXCEPT_HPP
#define HAMON_UTILITY_MOVE_IF_NOEXCEPT_HPP

#include <hamon/config.hpp>

#if HAMON_CXX_STANDARD >= 14

#include <utility>

namespace hamon
{

using std::move_if_noexcept;

}	// namespace hamon

#else

#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/utility/move.hpp>

namespace hamon
{

template <typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR
hamon::conditional_t<  
	!hamon::is_nothrow_move_constructible<T>::value &&
	hamon::is_copy_constructible<T>::value,
	T const&,
	T&&>
move_if_noexcept(T& x) HAMON_NOEXCEPT
{
	return hamon::move(x);
}

}	// namespace hamon

#endif

#endif // HAMON_UTILITY_MOVE_IF_NOEXCEPT_HPP
