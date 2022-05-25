/**
 *	@file	remove_extent.hpp
 *
 *	@brief	remove_extent の定義
 */

#ifndef HAMON_TYPE_TRAITS_REMOVE_EXTENT_HPP
#define HAMON_TYPE_TRAITS_REMOVE_EXTENT_HPP

#include <type_traits>

namespace hamon
{

/**
 *	@brief		配列型Tから次元を除去する。
 *
 *	@tparam		T
 *
 *	remove_extentは、型Tが、何らかの型Uの配列型である場合はU型を、
 *	そうでなければ型Tをメンバ型typeとして定義する。
 */
using std::remove_extent;

template <typename T>
using remove_extent_t = typename remove_extent<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_REMOVE_EXTENT_HPP
