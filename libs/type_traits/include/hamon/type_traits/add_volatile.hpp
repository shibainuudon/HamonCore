/**
 *	@file	add_volatile.hpp
 *
 *	@brief	add_volatile の定義
 */

#ifndef HAMON_TYPE_TRAITS_ADD_VOLATILE_HPP
#define HAMON_TYPE_TRAITS_ADD_VOLATILE_HPP

#include <type_traits>

namespace hamon
{

/**
 *	@brief		型をvolatile修飾する
 *
 *	@tparam		T
 *
 *	add_volatileは、型Tにvolatile修飾を付加した型を、メンバ型typeとして定義する。
 *	型Tが参照、関数、すでに最上位がvolatile修飾された型である場合は、型Tをそのままメンバ型typeとして定義する。
 */
using std::add_volatile;

/**
 *	@brief	add_volatileのエイリアステンプレート
 */
template <typename T>
using add_volatile_t = typename add_volatile<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_ADD_VOLATILE_HPP
