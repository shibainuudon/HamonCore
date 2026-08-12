/**
 *	@file	is_member_object_pointer.hpp
 *
 *	@brief	is_member_object_pointer の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_MEMBER_OBJECT_POINTER_HPP
#define HAMON_TYPE_TRAITS_IS_MEMBER_OBJECT_POINTER_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_member_function_pointer.hpp>
#include <hamon/type_traits/is_member_pointer.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 21.3.5.2 Primary type categories[meta.unary.cat]

/**
 *	@brief	型Tがデータメンバへのポインタか調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_member_object_pointerは、型Tがデータメンバへのポインタであるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *
 *	メンバ関数へのポインタはデータメンバへのポインタではない。
 *	staticなデータメンバへのポインタはデータメンバへのポインタではない。
 */
template <typename T>
struct is_member_object_pointer
	: public hamon::bool_constant<
		hamon::is_member_pointer<T>::value &&
		!hamon::is_member_function_pointer<T>::value
	>
{};

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
bool is_member_object_pointer_v = is_member_object_pointer<T>::value;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_MEMBER_OBJECT_POINTER_HPP
