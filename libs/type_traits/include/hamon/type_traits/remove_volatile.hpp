﻿/**
 *	@file	remove_volatile.hpp
 *
 *	@brief	remove_volatile の定義
 */

#ifndef HAMON_TYPE_TRAITS_REMOVE_VOLATILE_HPP
#define HAMON_TYPE_TRAITS_REMOVE_VOLATILE_HPP

#include <type_traits>

namespace hamon
{

/**
 *	@brief		型のvolatile修飾を除去する。
 *
 *	@tparam		T
 *
 *	remove_volatileは、型Tに含まれる最上位のvolatile修飾を除去した型を、メンバ型typeとして定義する。
 */
using std::remove_volatile;

template <typename T>
using remove_volatile_t = typename remove_volatile<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_REMOVE_VOLATILE_HPP
