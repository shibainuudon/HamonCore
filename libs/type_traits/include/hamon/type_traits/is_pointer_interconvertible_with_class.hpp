/**
 *	@file	is_pointer_interconvertible_with_class.hpp
 *
 *	@brief	is_pointer_interconvertible_with_class の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS_HPP
#define HAMON_TYPE_TRAITS_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS_HPP

#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

#if defined(__cpp_lib_is_pointer_interconvertible) && (__cpp_lib_is_pointer_interconvertible >= 201907)

using std::is_pointer_interconvertible_with_class;

#elif HAMON_HAS_BUILTIN(__builtin_is_pointer_interconvertible_with_class)

template <typename S, typename M>
constexpr bool is_pointer_interconvertible_with_class(M S::*m) noexcept
{
	return __builtin_is_pointer_interconvertible_with_class(m);
}

#elif (defined(HAMON_MSVC) && HAMON_MSVC >= 1920) ||	\
	HAMON_HAS_BUILTIN(__is_pointer_interconvertible_with_class)

template <typename S, typename M>
constexpr bool is_pointer_interconvertible_with_class(M S::*m) noexcept
{
	return __is_pointer_interconvertible_with_class(S, m);
}

#else

#  define HAMON_NO_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS

#endif

}	// namespace hamon

#if !defined(HAMON_NO_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS)
#  define HAMON_HAS_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS
#endif

#endif // HAMON_TYPE_TRAITS_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS_HPP
