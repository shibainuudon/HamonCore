/**
 *	@file	is_pointer.hpp
 *
 *	@brief	is_pointer の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_POINTER_HPP
#define HAMON_TYPE_TRAITS_IS_POINTER_HPP

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

/**
 *	@brief	型Tがポインタ型か調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_pointerは、型Tがポインタ型であるならば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 *	関数へのポインタはポインタ型であるが、staticではないメンバへのポインタは、ポインタ型ではない。
 *	nullptrはポインタ型へ変換できるが，nullptr_t型はポインタ型ではない。
 */
template <typename T>
struct is_pointer
	: public hamon::bool_constant<
		std::is_pointer<T>::value
	>
{};

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_pointer_v = is_pointer<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_POINTER_HPP
