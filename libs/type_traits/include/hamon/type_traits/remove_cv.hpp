/**
 *	@file	remove_cv.hpp
 *
 *	@brief	remove_cv の定義
 */

#ifndef HAMON_TYPE_TRAITS_REMOVE_CV_HPP
#define HAMON_TYPE_TRAITS_REMOVE_CV_HPP

#include <hamon/type_traits/remove_const.hpp>
#include <hamon/type_traits/remove_volatile.hpp>

namespace hamon
{

// 21.3.8.2 Const-volatile modifications[meta.trans.cv]

/**
 *	@brief		型のconst-volatile修飾を除去する。
 *
 *	@tparam		T
 *
 *	remove_cvは、型Tに含まれる最上位のconst-volatile修飾を除去した型を、メンバ型typeとして定義する。
 */
template <typename T>
struct remove_cv
{
	using type = hamon::remove_const_t<hamon::remove_volatile_t<T>>;
};

template <typename T>
using remove_cv_t = typename remove_cv<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_REMOVE_CV_HPP
