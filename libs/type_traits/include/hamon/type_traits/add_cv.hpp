/**
 *	@file	add_cv.hpp
 *
 *	@brief	add_cv の定義
 */

#ifndef HAMON_TYPE_TRAITS_ADD_CV_HPP
#define HAMON_TYPE_TRAITS_ADD_CV_HPP

#include <type_traits>

namespace hamon
{

/**
 *	@brief		型をconst-volatile修飾する
 *
 *	@tparam		T
 *
 *	add_cvは、型Tにconst修飾およびvolatile修飾両方を付加した型を、メンバ型typeとして定義する。
 *	型Tが参照、関数、すでに最上位がconst-volatile修飾された型である場合は、型Tをそのままメンバ型typeとして定義する。
 */
using std::add_cv;

/**
 *	@brief	add_cvのエイリアステンプレート
 */
template <typename T>
using add_cv_t = typename add_cv<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_ADD_CV_HPP
