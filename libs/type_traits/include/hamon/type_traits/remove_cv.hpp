/**
 *	@file	remove_cv.hpp
 *
 *	@brief	remove_cv の定義
 */

#ifndef HAMON_TYPE_TRAITS_REMOVE_CV_HPP
#define HAMON_TYPE_TRAITS_REMOVE_CV_HPP

#include <type_traits>

namespace hamon
{

/**
 *	@brief		型のconst-volatile修飾を除去する。
 *
 *	@tparam		T
 *
 *	remove_cvは、型Tに含まれる最上位のconst-volatile修飾を除去した型を、メンバ型typeとして定義する。
 */
using std::remove_cv;

template <typename T>
using remove_cv_t = typename remove_cv<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_REMOVE_CV_HPP
