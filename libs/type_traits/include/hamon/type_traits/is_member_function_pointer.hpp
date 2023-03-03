/**
 *	@file	is_member_function_pointer.hpp
 *
 *	@brief	is_member_function_pointer の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_MEMBER_FUNCTION_POINTER_HPP
#define HAMON_TYPE_TRAITS_IS_MEMBER_FUNCTION_POINTER_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	型Tがメンバ関数へのポインタか調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_member_function_pointerは、型Tがメンバ関数へのポインタであるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *
 *	データメンバへのポインタはメンバ関数へのポインタではない。
 *	staticなメンバ関数へのポインタはメンバ関数へのポインタではない。
 */
template <typename T>
struct is_member_function_pointer
	: public hamon::bool_constant<
		std::is_member_function_pointer<T>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_member_function_pointer_v = is_member_function_pointer<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_MEMBER_FUNCTION_POINTER_HPP
