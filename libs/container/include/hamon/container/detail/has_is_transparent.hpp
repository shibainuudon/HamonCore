/**
 *	@file	has_is_transparent.hpp
 *
 *	@brief	has_is_transparent の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_HAS_IS_TRANSPARENT_HPP
#define HAMON_CONTAINER_DETAIL_HAS_IS_TRANSPARENT_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_is_transparent = requires { typename T::is_transparent; };

#else

template <typename T, typename = void>
struct has_is_transparent
	: public hamon::false_type {};

template <typename T>
struct has_is_transparent<T, hamon::void_t<typename T::is_transparent>>
	: public hamon::true_type {};

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_HAS_IS_TRANSPARENT_HPP
