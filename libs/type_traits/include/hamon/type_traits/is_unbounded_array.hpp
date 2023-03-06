/**
 *	@file	is_unbounded_array.hpp
 *
 *	@brief	is_unbounded_array の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_UNBOUNDED_ARRAY_HPP
#define HAMON_TYPE_TRAITS_IS_UNBOUNDED_ARRAY_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

#if defined(__cpp_lib_bounded_array_traits) && (__cpp_lib_bounded_array_traits >= 201902)

using std::is_unbounded_array;

#else

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

#endif

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_unbounded_array_v  = is_unbounded_array<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_UNBOUNDED_ARRAY_HPP
