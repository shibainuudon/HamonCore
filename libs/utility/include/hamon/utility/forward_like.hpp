/**
 *	@file	forward_like.hpp
 *
 *	@brief	forward_like を定義
 */

#ifndef HAMON_UTILITY_FORWARD_LIKE_HPP
#define HAMON_UTILITY_FORWARD_LIKE_HPP

#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/is_rvalue_reference.hpp>
#include <hamon/type_traits/is_const.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 22.2.4 Forward/move helpers[forward]

namespace forward_like_detail
{

// [forward]/6.1
template <typename A, typename B>
using COPY_CONST = hamon::conditional_t<hamon::is_const<A>::value, const B, B>;

// [forward]/6.2
template <typename A, typename B>
using OVERRIDE_REF = hamon::conditional_t<hamon::is_rvalue_reference<A>::value, hamon::remove_reference_t<B>&&, B&>;

// [forward]/6.3
template <typename T, typename U>
using V = OVERRIDE_REF<T&&, COPY_CONST<hamon::remove_reference_t<T>, hamon::remove_reference_t<U>>>;

}	// namespace forward_like_detail

template <typename T, typename U>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
forward_like(U&& x) HAMON_NOEXCEPT
-> forward_like_detail::V<T, U>
{
	// [forward]/7
	return static_cast<forward_like_detail::V<T, U>>(x);
}

}	// namespace hamon

#endif // HAMON_UTILITY_FORWARD_LIKE_HPP
