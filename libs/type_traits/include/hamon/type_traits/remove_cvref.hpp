﻿/**
 *	@file	remove_cvref.hpp
 *
 *	@brief	remove_cvref
 */

#ifndef HAMON_TYPE_TRAITS_REMOVE_CVREF_HPP
#define HAMON_TYPE_TRAITS_REMOVE_CVREF_HPP

#include <type_traits>

#if defined(__cpp_lib_remove_cvref) && (__cpp_lib_remove_cvref >= 201711)

namespace hamon
{

using std::remove_cvref;
using std::remove_cvref_t;

}	// namespace hamon

#else

#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/type_traits/remove_reference.hpp>

namespace hamon
{

/**
 *	@brief		型TからCV修飾と参照を除去する。
 *
 *	@tparam		T
 */
template <typename T>
struct remove_cvref
	: public hamon::remove_cv<hamon::remove_reference_t<T>>
{};

/**
 *	@brief	remove_cvrefのエイリアステンプレート
 */
template <typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

}	// namespace hamon

#endif

#endif // HAMON_TYPE_TRAITS_REMOVE_CVREF_HPP
