/**
 *	@file	add_cv.hpp
 *
 *	@brief	add_cv の定義
 */

#ifndef HAMON_TYPE_TRAITS_ADD_CV_HPP
#define HAMON_TYPE_TRAITS_ADD_CV_HPP

#include <hamon/type_traits/add_const.hpp>
#include <hamon/type_traits/add_volatile.hpp>

namespace hamon
{

// 21.3.8.2 Const-volatile modifications[meta.trans.cv]

/**
 *	@brief		型をconst-volatile修飾する
 *
 *	@tparam		T
 *
 *	add_cvは、型Tにconst修飾およびvolatile修飾両方を付加した型を、メンバ型typeとして定義する。
 *	型Tが参照、関数、すでに最上位がconst-volatile修飾された型である場合は、型Tをそのままメンバ型typeとして定義する。
 */
template <typename T>
struct add_cv
{
	using type = hamon::add_const_t<hamon::add_volatile_t<T>>;
};

/**
 *	@brief	add_cvのエイリアステンプレート
 */
template <typename T>
using add_cv_t = typename add_cv<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_ADD_CV_HPP
