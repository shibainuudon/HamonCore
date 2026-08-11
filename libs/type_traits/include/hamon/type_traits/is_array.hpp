/**
 *	@file	is_array.hpp
 *
 *	@brief	is_array の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_ARRAY_HPP
#define HAMON_TYPE_TRAITS_IS_ARRAY_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.2 Primary type categories[meta.unary.cat]

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
struct is_array : public hamon::false_type{};

template <typename T>
struct is_array<T[]> : public hamon::true_type{};

template <typename T, hamon::size_t N>
struct is_array<T[N]> : public hamon::true_type{};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_array_v = is_array<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_ARRAY_HPP
