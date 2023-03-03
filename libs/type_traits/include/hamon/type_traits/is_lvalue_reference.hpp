/**
 *	@file	is_lvalue_reference.hpp
 *
 *	@brief	is_lvalue_reference の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_LVALUE_REFERENCE_HPP
#define HAMON_TYPE_TRAITS_IS_LVALUE_REFERENCE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	型Tが左辺値参照型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_lvalue_referenceは、型Tが左辺値参照型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_lvalue_reference
	: public hamon::bool_constant<
		std::is_lvalue_reference<T>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_lvalue_reference_v = is_lvalue_reference<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_LVALUE_REFERENCE_HPP
