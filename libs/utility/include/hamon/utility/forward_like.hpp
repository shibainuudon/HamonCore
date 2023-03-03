/**
 *	@file	forward_like.hpp
 *
 *	@brief	forward_like を定義
 */

#ifndef HAMON_UTILITY_FORWARD_LIKE_HPP
#define HAMON_UTILITY_FORWARD_LIKE_HPP

#include <utility>

#if defined(__cpp_lib_forward_like) && (__cpp_lib_forward_like >= 202207L)

namespace hamon
{

using std::forward_like;

}	// namespace hamon

#else

#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/is_rvalue_reference.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

namespace detail
{

template <typename A, typename B>
using CopyConst = hamon::conditional_t<std::is_const<A>::value, const B, B>;

template <typename A, typename B>
using OverrideRef = hamon::conditional_t<hamon::is_rvalue_reference<A>::value, hamon::remove_reference_t<B>&&, B&>;

template <typename A, typename B>
using ForwardLike = OverrideRef<A&&, CopyConst<hamon::remove_reference_t<A>, hamon::remove_reference_t<B>>>;

}	// namespace detail

template <typename T, typename U>
HAMON_NODISCARD inline HAMON_CXX11_CONSTEXPR auto
forward_like(U&& x) HAMON_NOEXCEPT
-> detail::ForwardLike<T, U>
{
	return static_cast<detail::ForwardLike<T, U>>(x);
}

}	// namespace hamon

#endif

#endif // HAMON_UTILITY_FORWARD_LIKE_HPP
