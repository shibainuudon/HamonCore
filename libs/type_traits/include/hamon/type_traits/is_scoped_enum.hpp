/**
 *	@file	is_scoped_enum.hpp
 *
 *	@brief	is_scoped_enum の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_SCOPED_ENUM_HPP
#define HAMON_TYPE_TRAITS_IS_SCOPED_ENUM_HPP

#include <hamon/config.hpp>
#include <type_traits>

#if defined(__cpp_lib_is_scoped_enum) && (__cpp_lib_is_scoped_enum >= 202011)

namespace hamon
{

using std::is_scoped_enum;

}	// namespace hamon

#else

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/underlying_type.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/is_enum.hpp>
#include <hamon/type_traits/is_convertible.hpp>

namespace hamon
{

namespace detail
{

template <typename T, bool = hamon::is_enum<T>::value>
struct is_scoped_enum_impl : public std::false_type {};

template <typename T>
struct is_scoped_enum_impl<T, true>
	: public hamon::negation<
		hamon::is_convertible<T, hamon::underlying_type_t<T>>
	>
{};

}	// namespace detail

/**
 *	@brief	型Tがスコープ付きの列挙型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_scoped_enumは、型Tがスコープ付きの列挙型であるならばtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_scoped_enum
	: public detail::is_scoped_enum_impl<T>
{};

}	// namespace hamon

#endif

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

namespace hamon
{

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_scoped_enum_v = is_scoped_enum<T>::value;

}	// namespace hamon

#endif

#endif // HAMON_TYPE_TRAITS_IS_SCOPED_ENUM_HPP
