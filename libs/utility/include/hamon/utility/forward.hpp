/**
 *	@file	forward.hpp
 *
 *	@brief	forward を定義
 */

#ifndef HAMON_UTILITY_FORWARD_HPP
#define HAMON_UTILITY_FORWARD_HPP

#include <hamon/config.hpp>

#if HAMON_CXX_STANDARD >= 14

#include <utility>

namespace hamon
{

using std::forward;

}	// namespace hamon

#else

#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/is_lvalue_reference.hpp>

namespace hamon
{

template <typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR T&&
forward(hamon::remove_reference_t<T>& t) HAMON_NOEXCEPT
{
	return static_cast<T&&>(t);
}

template <typename T>
HAMON_NODISCARD inline HAMON_CONSTEXPR T&&
forward(hamon::remove_reference_t<T>&& t) HAMON_NOEXCEPT
{
	static_assert(!hamon::is_lvalue_reference<T>::value, "");
	return static_cast<T&&>(t);
}

}	// namespace hamon

#endif

#endif // HAMON_UTILITY_FORWARD_HPP
