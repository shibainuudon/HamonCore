/**
 *	@file	is_null_pointer.hpp
 *
 *	@brief	is_null_pointer の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_NULL_POINTER_HPP
#define HAMON_TYPE_TRAITS_IS_NULL_POINTER_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/cstddef/nullptr_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.2 Primary type categories[meta.unary.cat]

/**
 *	@brief	型Tがnullptr_tか調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_null_pointerは、型Tがnullptr_tであれば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_null_pointer : public hamon::false_type{};

template <>
struct is_null_pointer<hamon::nullptr_t> : public hamon::true_type{};
template <>
struct is_null_pointer<hamon::nullptr_t const> : public hamon::true_type{};
template <>
struct is_null_pointer<hamon::nullptr_t volatile> : public hamon::true_type{};
template <>
struct is_null_pointer<hamon::nullptr_t const volatile> : public hamon::true_type{};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_null_pointer_v = is_null_pointer<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_NULL_POINTER_HPP
