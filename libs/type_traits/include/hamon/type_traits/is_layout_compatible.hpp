/**
 *	@file	is_layout_compatible.hpp
 *
 *	@brief	is_layout_compatible の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_LAYOUT_COMPATIBLE_HPP
#define HAMON_TYPE_TRAITS_IS_LAYOUT_COMPATIBLE_HPP

#include <hamon/config.hpp>
#include <type_traits>

#if defined(__cpp_lib_is_layout_compatible) && (__cpp_lib_is_layout_compatible >= 201907)

namespace hamon
{

using std::is_layout_compatible;

}	// namespace hamon

#elif (defined(HAMON_MSVC) && HAMON_MSVC >= 1920) ||	\
	HAMON_HAS_BUILTIN(__is_layout_compatible)

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename T, typename U>
struct is_layout_compatible
	: public hamon::bool_constant<__is_layout_compatible(T, U)> {};

}	// namespace hamon

#else
#  define HAMON_NO_IS_LAYOUT_COMPATIBLE
#endif

#if !defined(HAMON_NO_IS_LAYOUT_COMPATIBLE)

#define HAMON_HAS_IS_LAYOUT_COMPATIBLE

namespace hamon
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
template <typename T, typename U>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_layout_compatible_v =
	is_layout_compatible<T, U>::value;
#endif

}	// namespace hamon

#endif

#endif // HAMON_TYPE_TRAITS_IS_LAYOUT_COMPATIBLE_HPP
