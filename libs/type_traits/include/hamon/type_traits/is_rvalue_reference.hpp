/**
 *	@file	is_rvalue_reference.hpp
 *
 *	@brief	is_rvalue_reference の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_RVALUE_REFERENCE_HPP
#define HAMON_TYPE_TRAITS_IS_RVALUE_REFERENCE_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.2 Primary type categories[meta.unary.cat]

/**
 *	@brief	型Tが右辺値参照型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_rvalue_referenceは、型Tが右辺値参照型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_rvalue_reference : public hamon::false_type{};

template <typename T>
struct is_rvalue_reference<T&&> : public hamon::true_type{};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_rvalue_reference_v = is_rvalue_reference<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_RVALUE_REFERENCE_HPP
