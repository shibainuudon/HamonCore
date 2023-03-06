/**
 *	@file	is_bounded_array.hpp
 *
 *	@brief	is_bounded_array の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_BOUNDED_ARRAY_HPP
#define HAMON_TYPE_TRAITS_IS_BOUNDED_ARRAY_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>
#include <cstddef>

namespace hamon
{

#if defined(__cpp_lib_bounded_array_traits) && (__cpp_lib_bounded_array_traits >= 201902)

using std::is_bounded_array;

#else

/**
 *	@brief		型Tが要素数の判明している配列型かを調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_bounded_arrayは、Tが要素型の判明している配列型であるならばtrue_typeから派生し、
 *	そうでなければfalse_typeから派生する。
 *
 *	要素数の判明している配列型とは、T[]を含まないT[N]形式の配列型である。
 */
template <typename T>
struct is_bounded_array : public hamon::false_type {};

template <typename T, std::size_t N>
struct is_bounded_array<T[N]> : public hamon::true_type {};

#endif

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_bounded_array_v  = is_bounded_array<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_BOUNDED_ARRAY_HPP
