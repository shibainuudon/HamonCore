/**
 *	@file	is_array.hpp
 *
 *	@brief	is_array の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_ARRAY_HPP
#define HAMON_TYPE_TRAITS_IS_ARRAY_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	型Tが配列型かを調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_arrayは、Tが配列型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	要素数が未知(T[])だとしても判断することができる。
 *	クラステンプレートarrayは、配列型とは見なされない。
 */
template <typename T>
struct is_array
	: public hamon::bool_constant<
		std::is_array<T>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_array_v = is_array<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_ARRAY_HPP
