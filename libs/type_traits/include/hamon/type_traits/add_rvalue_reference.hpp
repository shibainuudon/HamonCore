/**
 *	@file	add_rvalue_reference.hpp
 *
 *	@brief	add_rvalue_reference の定義
 */

#ifndef HAMON_TYPE_TRAITS_ADD_RVALUE_REFERENCE_HPP
#define HAMON_TYPE_TRAITS_ADD_RVALUE_REFERENCE_HPP

#include <type_traits>

namespace hamon
{

/**
 *	@brief		型に右辺値参照を追加する
 *
 *	@tparam		T
 *
 *	Tがオブジェクト型もしくは関数型の場合(cv修飾や参照型でない)、T&&をメンバ型typeとして定義する。
 *	そうでない場合、Tをメンバ型typeとして定義する。
 *
 *	例)
 *	add_rvalue_reference<int>::type is int&&
 *	add_rvalue_reference<int&>::type is int&
 *	add_rvalue_reference<int&&>::type is int&&
 */
using std::add_rvalue_reference;

/**
 *	@brief	add_rvalue_referenceのエイリアステンプレート
 */
template <typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_ADD_RVALUE_REFERENCE_HPP
