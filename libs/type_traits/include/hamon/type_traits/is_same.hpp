/**
 *	@file	is_same.hpp
 *
 *	@brief	is_same の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_SAME_HPP
#define HAMON_TYPE_TRAITS_IS_SAME_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	2つの型TとUが同じ型か調べる
 *
 *	@tparam	T
 *	@tparam	U
 *
 *	is_sameは、CV修飾子が同じであることを含め型Tと型Uが同じ型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T, typename U>
struct is_same : public hamon::bool_constant<std::is_same<T, U>::value> {};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T, typename U>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_same_v = is_same<T, U>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_SAME_HPP
