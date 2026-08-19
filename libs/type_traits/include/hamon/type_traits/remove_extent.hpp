/**
 *	@file	remove_extent.hpp
 *
 *	@brief	remove_extent の定義
 */

#ifndef HAMON_TYPE_TRAITS_REMOVE_EXTENT_HPP
#define HAMON_TYPE_TRAITS_REMOVE_EXTENT_HPP

#include <hamon/cstddef/size_t.hpp>

namespace hamon
{

// 21.3.8.5 Array modifications[meta.trans.arr]

/**
 *	@brief		配列型Tから次元を除去する。
 *
 *	@tparam		T
 *
 *	remove_extentは、型Tが、何らかの型Uの配列型である場合はU型を、
 *	そうでなければ型Tをメンバ型typeとして定義する。
 */
template <typename T>
struct remove_extent
{
	using type = T;
};

template <typename T, hamon::size_t N>
struct remove_extent<T[N]>
{
	using type = T;
};

template <typename T>
struct remove_extent<T[]>
{
	using type = T;
};

template <typename T>
using remove_extent_t = typename remove_extent<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_REMOVE_EXTENT_HPP
