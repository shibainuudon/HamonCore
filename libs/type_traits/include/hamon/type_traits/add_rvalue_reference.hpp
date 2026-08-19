/**
 *	@file	add_rvalue_reference.hpp
 *
 *	@brief	add_rvalue_reference の定義
 */

#ifndef HAMON_TYPE_TRAITS_ADD_RVALUE_REFERENCE_HPP
#define HAMON_TYPE_TRAITS_ADD_RVALUE_REFERENCE_HPP

#include <hamon/type_traits/void_t.hpp>

namespace hamon
{

// 21.3.8.3 Reference modifications[meta.trans.ref]

namespace detail
{

template <typename T, typename = void>
struct add_rvalue_reference_impl
{
	using type = T;
};

template <typename T>
struct add_rvalue_reference_impl<T, hamon::void_t<T&&>>
{
	using type = T&&;
};

}	// namespace detail

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
template <typename T>
struct add_rvalue_reference
	: public detail::add_rvalue_reference_impl<T>
{};

/**
 *	@brief	add_rvalue_referenceのエイリアステンプレート
 */
template <typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_ADD_RVALUE_REFERENCE_HPP
