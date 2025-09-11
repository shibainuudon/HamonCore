/**
 *	@file	reference_converts_from_temporary.hpp
 *
 *	@brief	reference_converts_from_temporary の定義
 */

#ifndef HAMON_TYPE_TRAITS_REFERENCE_CONVERTS_FROM_TEMPORARY_HPP
#define HAMON_TYPE_TRAITS_REFERENCE_CONVERTS_FROM_TEMPORARY_HPP

#include <hamon/config.hpp>
#include <type_traits>

#if defined(__cpp_lib_reference_from_temporary) && (__cpp_lib_reference_from_temporary >= 202202L)

namespace hamon
{

using std::reference_converts_from_temporary;

}	// namespace hamon

#elif HAMON_HAS_BUILTIN(__reference_converts_from_temporary) && !defined(HAMON_CLANG)

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename T, typename U>
struct reference_converts_from_temporary
	: public hamon::bool_constant<
		__reference_converts_from_temporary(T, U)
	>
{};

}	// namespace hamon

#else
#  define HAMON_NO_REFERENCE_CONVERTS_FROM_TEMPORARY
#endif

#if !defined(HAMON_NO_REFERENCE_CONVERTS_FROM_TEMPORARY)

#define HAMON_HAS_REFERENCE_CONVERTS_FROM_TEMPORARY

namespace hamon
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
template <typename T, typename U>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool reference_converts_from_temporary_v = reference_converts_from_temporary<T, U>::value;
#endif

}	// namespace hamon

#endif

#endif // HAMON_TYPE_TRAITS_REFERENCE_CONVERTS_FROM_TEMPORARY_HPP
