/**
 *	@file	remove_pointer.hpp
 *
 *	@brief	remove_pointer の定義
 */

#ifndef HAMON_TYPE_TRAITS_REMOVE_POINTER_HPP
#define HAMON_TYPE_TRAITS_REMOVE_POINTER_HPP

#include <type_traits>

namespace hamon
{

/**
 *	@brief		型Tからポインタを除去する。
 *
 *	@tparam		T
 *
 *	remove_pointerは、型Tが何らかの型Uへの(cv修飾された)ポインタである場合、
 *	型に含まれるポインタを除去した型Uを、メンバ型typeとして定義する。
 *	そうでなければ、型Tをそのままメンバ型typeとして定義する。
 */
using std::remove_pointer;

template <typename T>
using remove_pointer_t = typename remove_pointer<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_REMOVE_POINTER_HPP
