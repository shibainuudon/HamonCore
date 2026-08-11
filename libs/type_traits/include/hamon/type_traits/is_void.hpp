/**
 *	@file	is_void.hpp
 *
 *	@brief	is_void の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_VOID_HPP
#define HAMON_TYPE_TRAITS_IS_VOID_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.2 Primary type categories[meta.unary.cat]

/**
 *	@brief	型Tがvoidかを調べる。
 *
 *	@tparam		T	チェックする型
 *
 *	is_voidは、型Tがvoid(cv修飾を許容する)であれば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_void : public hamon::false_type{};

template <>
struct is_void<void> : public hamon::true_type{};
template <>
struct is_void<void const> : public hamon::true_type{};
template <>
struct is_void<void volatile> : public hamon::true_type{};
template <>
struct is_void<void const volatile> : public hamon::true_type{};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_void_v = is_void<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_VOID_HPP
