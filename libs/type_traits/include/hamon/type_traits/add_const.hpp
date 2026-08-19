/**
 *	@file	add_const.hpp
 *
 *	@brief	add_const の定義
 */

#ifndef HAMON_TYPE_TRAITS_ADD_CONST_HPP
#define HAMON_TYPE_TRAITS_ADD_CONST_HPP

#include <hamon/config.hpp>

namespace hamon
{

// 21.3.8.2 Const-volatile modifications[meta.trans.cv]

/**
 *	@brief		型をconst修飾する
 *
 *	@tparam		T
 *
 *	add_constは、型Tにconst修飾を付加した型を、メンバ型typeとして定義する。
 *	型Tが参照、関数、すでに最上位がconst修飾された型である場合は、型Tをそのままメンバ型typeとして定義する。
 */
template <typename T>
struct add_const
{
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4180)	// 関数型へ適用された修飾子は無効なため、無視されます。
	using type = T const;
HAMON_WARNING_POP()
};

/**
 *	@brief	add_constのエイリアステンプレート
 */
template <typename T>
using add_const_t = typename add_const<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_ADD_CONST_HPP
