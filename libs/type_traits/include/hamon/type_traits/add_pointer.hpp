/**
 *	@file	add_pointer.hpp
 *
 *	@brief	add_pointer の定義
 */

#ifndef HAMON_TYPE_TRAITS_ADD_POINTER_HPP
#define HAMON_TYPE_TRAITS_ADD_POINTER_HPP

#include <type_traits>

namespace hamon
{

/**
 *	@brief		型にポインタを追加する
 *
 *	@tparam		T
 *
 *	Tが何らかの型Uの参照型の場合、U*をメンバ型typeとして定義する。
 *	Tが何らかのオブジェクト型、もしくは関数型(cv修飾や参照型を含まない)の場合、もしくは
 *	void型の場合(cv修飾を含む)、T*をメンバ型typeとして定義する。
 *	いずれでもない場合、Tをメンバ型typeとして定義する。
 */
using std::add_pointer;

/**
 *	@brief	add_pointerのエイリアステンプレート
 */
template <typename T>
using add_pointer_t = typename add_pointer<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_ADD_POINTER_HPP
