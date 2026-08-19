/**
 *	@file	remove_volatile.hpp
 *
 *	@brief	remove_volatile の定義
 */

#ifndef HAMON_TYPE_TRAITS_REMOVE_VOLATILE_HPP
#define HAMON_TYPE_TRAITS_REMOVE_VOLATILE_HPP

namespace hamon
{

// 21.3.8.2 Const-volatile modifications[meta.trans.cv]

/**
 *	@brief		型のvolatile修飾を除去する。
 *
 *	@tparam		T
 *
 *	remove_volatileは、型Tに含まれる最上位のvolatile修飾を除去した型を、メンバ型typeとして定義する。
 */
template <typename T>
struct remove_volatile
{
	using type = T;
};

template <typename T>
struct remove_volatile<T volatile>
{
	using type = T;
};

template <typename T>
using remove_volatile_t = typename remove_volatile<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_REMOVE_VOLATILE_HPP
