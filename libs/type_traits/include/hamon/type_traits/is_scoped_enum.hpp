/**
 *	@file	is_scoped_enum.hpp
 *
 *	@brief	is_scoped_enum の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_SCOPED_ENUM_HPP
#define HAMON_TYPE_TRAITS_IS_SCOPED_ENUM_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/underlying_type.hpp>
#include <hamon/type_traits/is_enum.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.4 Type properties[meta.unary.prop]

namespace detail
{

template <typename T, bool = hamon::is_enum<T>::value>
struct is_scoped_enum_impl : public hamon::false_type {};

template <typename T>
struct is_scoped_enum_impl<T, true>
	: public hamon::bool_constant<
		!hamon::is_convertible_v<T, hamon::underlying_type_t<T>>
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

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_scoped_enum_v = is_scoped_enum<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_SCOPED_ENUM_HPP
