/**
 *	@file	add_pointer.hpp
 *
 *	@brief	add_pointer の定義
 */

#ifndef HAMON_TYPE_TRAITS_ADD_POINTER_HPP
#define HAMON_TYPE_TRAITS_ADD_POINTER_HPP

#include <hamon/type_traits/void_t.hpp>
#include <hamon/type_traits/remove_reference.hpp>

namespace hamon
{

// 21.3.8.6 Pointer modifications[meta.trans.ptr]

namespace detail
{

template <typename T, typename = void>
struct add_pointer_impl
{
	using type = T;
};

template <typename T>
struct add_pointer_impl<T, hamon::void_t<hamon::remove_reference_t<T>*>>
{
	using type = hamon::remove_reference_t<T>*;
};

}	// namespace detail

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
template <typename T>
struct add_pointer
	: public detail::add_pointer_impl<T>
{};

/**
 *	@brief	add_pointerのエイリアステンプレート
 */
template <typename T>
using add_pointer_t = typename add_pointer<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_ADD_POINTER_HPP
