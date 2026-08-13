/**
 *	@file	is_reference.hpp
 *
 *	@brief	is_reference の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_REFERENCE_HPP
#define HAMON_TYPE_TRAITS_IS_REFERENCE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.3 Composite type traits

/**
 *	@brief	型Tが参照型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_referenceは、型Tが左辺値参照型もしくは右辺値参照型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_reference : public hamon::false_type{};

template <typename T>
struct is_reference<T&> : public hamon::true_type{};
template <typename T>
struct is_reference<T&&> : public hamon::true_type{};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_reference_v = is_reference<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_REFERENCE_HPP
