/**
 *	@file	move.hpp
 *
 *	@brief	move を定義
 */

#ifndef HAMON_UTILITY_MOVE_HPP
#define HAMON_UTILITY_MOVE_HPP

#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 22.2.4 Forward/move helpers[forward]

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
hamon::remove_reference_t<T>&&
move(T&& x) HAMON_NOEXCEPT
{
	// [forward]/10
	return static_cast<hamon::remove_reference_t<T>&&>(x);
}

}	// namespace hamon

#endif // HAMON_UTILITY_MOVE_HPP
