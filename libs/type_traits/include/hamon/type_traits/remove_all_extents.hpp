/**
 *	@file	remove_all_extents.hpp
 *
 *	@brief	remove_all_extents の定義
 */

#ifndef HAMON_TYPE_TRAITS_REMOVE_ALL_EXTENTS_HPP
#define HAMON_TYPE_TRAITS_REMOVE_ALL_EXTENTS_HPP

#include <type_traits>

namespace hamon
{

/**
 *	@brief		配列型Tから全ての次元を除去する。
 *
 *	@tparam		T
 *
 *	remove_all_extentsは、型Tが、何らかの型Uの多次元配列型である場合はU型を、
 *	そうでなければ型Tをメンバ型typeとして定義する。
 */
using std::remove_all_extents;

template <typename T>
using remove_all_extents_t = typename remove_all_extents<T>::type;

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_REMOVE_ALL_EXTENTS_HPP
