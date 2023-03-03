/**
 *	@file	is_union.hpp
 *
 *	@brief	is_union の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_UNION_HPP
#define HAMON_TYPE_TRAITS_IS_UNION_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	型Tが共用型かを調べる。
 *
 *	@tparam		T	チェックする型
 *
 *	is_unionは、型Tが共用型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_union
	: public hamon::bool_constant<
		std::is_union<T>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_union_v = is_union<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_UNION_HPP
