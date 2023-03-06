/**
 *	@file	move.hpp
 *
 *	@brief	move を定義
 */

#ifndef HAMON_UTILITY_MOVE_HPP
#define HAMON_UTILITY_MOVE_HPP

#include <hamon/config.hpp>

#if 0//HAMON_CXX_STANDARD >= 14

#include <utility>

namespace hamon
{

using std::move;

}	// namespace hamon

#else

#include <hamon/type_traits/remove_reference.hpp>

namespace hamon
{

template <typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR hamon::remove_reference_t<T>&&
move(T&& x) HAMON_NOEXCEPT
{
	return static_cast<hamon::remove_reference_t<T>&&>(x);
}

}	// namespace hamon

#endif

#endif // HAMON_UTILITY_MOVE_HPP
