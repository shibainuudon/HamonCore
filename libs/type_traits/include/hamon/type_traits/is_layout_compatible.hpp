/**
 *	@file	is_layout_compatible.hpp
 *
 *	@brief	is_layout_compatible の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_LAYOUT_COMPATIBLE_HPP
#define HAMON_TYPE_TRAITS_IS_LAYOUT_COMPATIBLE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.7 Relationships between types[meta.rel]

#if HAMON_HAS_BUILTIN(__is_layout_compatible) || defined(HAMON_MSVC)

#define HAMON_HAS_IS_LAYOUT_COMPATIBLE

template <typename T, typename U>
struct is_layout_compatible
	: public hamon::bool_constant<
		__is_layout_compatible(T, U)
	>
{};

template <typename T, typename U>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_layout_compatible_v = is_layout_compatible<T, U>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_LAYOUT_COMPATIBLE_HPP
