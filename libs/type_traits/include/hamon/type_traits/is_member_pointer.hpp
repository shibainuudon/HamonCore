/**
 *	@file	is_member_pointer.hpp
 *
 *	@brief	is_member_pointer の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_MEMBER_POINTER_HPP
#define HAMON_TYPE_TRAITS_IS_MEMBER_POINTER_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	型Tがメンバポインタ型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_member_pointerは、型Tがメンバポインタ型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *
 *	メンバポインタ型は、データメンバへのポインタ型、
 *	メンバ関数へのポインタ型、およびそれらのcv修飾を含む。
 */
template <typename T>
struct is_member_pointer
	: public hamon::bool_constant<
		std::is_member_pointer<T>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_member_pointer_v = is_member_pointer<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_MEMBER_POINTER_HPP
