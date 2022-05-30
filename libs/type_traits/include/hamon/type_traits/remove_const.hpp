/**
 *	@file	remove_const.hpp
 *
 *	@brief	remove_const の定義
 */

#ifndef HAMON_TYPE_TRAITS_REMOVE_CONST_HPP
#define HAMON_TYPE_TRAITS_REMOVE_CONST_HPP

#include <type_traits>

namespace hamon
{

/**
 *	@brief		型のconst修飾を除去する。
 *
 *	@tparam		T
 *
 *	remove_constは、型Tに含まれる最上位のconst修飾を除去した型を、メンバ型typeとして定義する。
 */
using std::remove_const;

template <typename T>
using remove_const_t = typename remove_const<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_REMOVE_CONST_HPP
