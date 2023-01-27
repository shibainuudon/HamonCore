/**
 *	@file	is_pointer_interconvertible_base_of.hpp
 *
 *	@brief	is_pointer_interconvertible_base_of の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_POINTER_INTERCONVERTIBLE_BASE_OF_HPP
#define HAMON_TYPE_TRAITS_IS_POINTER_INTERCONVERTIBLE_BASE_OF_HPP

#include <hamon/config.hpp>
#include <type_traits>

#if defined(__cpp_lib_is_pointer_interconvertible) && (__cpp_lib_is_pointer_interconvertible >= 201907)

namespace hamon
{

using std::is_pointer_interconvertible_base_of;

}	// namespace hamon

#elif (defined(HAMON_MSVC) && HAMON_MSVC >= 1920) ||	\
	HAMON_HAS_BUILTIN(__is_pointer_interconvertible_base_of)

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename Base, typename Derived>
struct is_pointer_interconvertible_base_of
	: public hamon::bool_constant<__is_pointer_interconvertible_base_of(Base, Derived)> {};

}	// namespace hamon

#else
#  define HAMON_NO_IS_POINTER_INTERCONVERTIBLE_BASE_OF
#endif

#if !defined(HAMON_NO_IS_POINTER_INTERCONVERTIBLE_BASE_OF)

#define HAMON_HAS_IS_POINTER_INTERCONVERTIBLE_BASE_OF

namespace hamon
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
template <typename Base, typename Derived>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_pointer_interconvertible_base_of_v =
	is_pointer_interconvertible_base_of<Base, Derived>::value;
#endif

}	// namespace hamon

#endif

#endif // HAMON_TYPE_TRAITS_IS_POINTER_INTERCONVERTIBLE_BASE_OF_HPP
