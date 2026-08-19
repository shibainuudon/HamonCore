/**
 *	@file	add_volatile.hpp
 *
 *	@brief	add_volatile の定義
 */

#ifndef HAMON_TYPE_TRAITS_ADD_VOLATILE_HPP
#define HAMON_TYPE_TRAITS_ADD_VOLATILE_HPP

#include <hamon/config.hpp>

namespace hamon
{

// 21.3.8.2 Const-volatile modifications[meta.trans.cv]

/**
 *	@brief		型をvolatile修飾する
 *
 *	@tparam		T
 *
 *	add_volatileは、型Tにvolatile修飾を付加した型を、メンバ型typeとして定義する。
 *	型Tが参照、関数、すでに最上位がvolatile修飾された型である場合は、型Tをそのままメンバ型typeとして定義する。
 */
template <typename T>
struct add_volatile
{
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4180)	// 関数型へ適用された修飾子は無効なため、無視されます。
	using type = T volatile;
HAMON_WARNING_POP()
};

/**
 *	@brief	add_volatileのエイリアステンプレート
 */
template <typename T>
using add_volatile_t = typename add_volatile<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_ADD_VOLATILE_HPP
