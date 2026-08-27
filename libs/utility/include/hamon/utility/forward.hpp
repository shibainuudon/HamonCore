/**
 *	@file	forward.hpp
 *
 *	@brief	forward を定義
 */

#ifndef HAMON_UTILITY_FORWARD_HPP
#define HAMON_UTILITY_FORWARD_HPP

#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/is_lvalue_reference.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 22.2.4 Forward/move helpers[forward]

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
T&& forward(hamon::remove_reference_t<T>& t) HAMON_NOEXCEPT
{
	// [forward]/1
	return static_cast<T&&>(t);
}

template <typename T>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
T&& forward(hamon::remove_reference_t<T>&& t) HAMON_NOEXCEPT
{
	// [forward]/2
	static_assert(!hamon::is_lvalue_reference_v<T>, "");

	// [forward]/1
	return static_cast<T&&>(t);
}

}	// namespace hamon

#endif // HAMON_UTILITY_FORWARD_HPP
