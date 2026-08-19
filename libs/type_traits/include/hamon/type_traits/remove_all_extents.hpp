/**
 *	@file	remove_all_extents.hpp
 *
 *	@brief	remove_all_extents の定義
 */

#ifndef HAMON_TYPE_TRAITS_REMOVE_ALL_EXTENTS_HPP
#define HAMON_TYPE_TRAITS_REMOVE_ALL_EXTENTS_HPP

#include <hamon/cstddef/size_t.hpp>

namespace hamon
{

// 21.3.8.5 Array modifications[meta.trans.arr]

/**
 *	@brief		配列型Tから全ての次元を除去する。
 *
 *	@tparam		T
 *
 *	remove_all_extentsは、型Tが、何らかの型Uの多次元配列型である場合はU型を、
 *	そうでなければ型Tをメンバ型typeとして定義する。
 */
template <typename T>
struct remove_all_extents
{
	using type = T;
};

template <typename T, hamon::size_t N>
struct remove_all_extents<T[N]>
{
	using type = typename remove_all_extents<T>::type;
};

template <typename T>
struct remove_all_extents<T[]>
{
	using type = typename remove_all_extents<T>::type;
};

template <typename T>
using remove_all_extents_t = typename remove_all_extents<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_REMOVE_ALL_EXTENTS_HPP
