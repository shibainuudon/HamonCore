/**
 *	@file	is_unbounded_array.hpp
 *
 *	@brief	is_unbounded_array の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_UNBOUNDED_ARRAY_HPP
#define HAMON_TYPE_TRAITS_IS_UNBOUNDED_ARRAY_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.4 Type properties[meta.unary.prop]

/**
 *	@brief		型Tが要素数の不明な配列型かを調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_unbounded_arrayは、Tが要素型の不明な配列型であるならばtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *
 *	要素数の不明な配列型とは、T[N]やT*を含まないT[]形式の配列型である。
 */
template <typename>
struct is_unbounded_array : public hamon::false_type {};

template <typename T>
struct is_unbounded_array<T[]> : public hamon::true_type {};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_unbounded_array_v  = is_unbounded_array<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_UNBOUNDED_ARRAY_HPP
