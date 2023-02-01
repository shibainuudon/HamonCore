﻿/**
 *	@file	is_null_pointer.hpp
 *
 *	@brief	is_null_pointer の定義
 */

#ifndef HAMON_TYPE_TRAITS_IS_NULL_POINTER_HPP
#define HAMON_TYPE_TRAITS_IS_NULL_POINTER_HPP

#include <hamon/config.hpp>
#include <type_traits>

#if defined(__cpp_lib_is_null_pointer) && (__cpp_lib_is_null_pointer >= 201309)

namespace hamon
{

using std::is_null_pointer;

}	// namespace hamon

#else

#include <hamon/type_traits/remove_cv.hpp>
#include <cstddef>

namespace hamon
{

/**
 *	@brief	型Tがnullptr_tか調べる
 *
 *	@tparam		T	チェックする型
 *
 *	is_null_pointerは、型Tがnullptr_tであれば
 *	true_typeから派生し、そうでなければfalse_typeから派生する。
 */
template <typename T>
struct is_null_pointer
	: public std::is_same<
		hamon::remove_cv_t<T>, std::nullptr_t
	>
{};

}	// namespace hamon

#endif

namespace hamon
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR
bool is_null_pointer_v = is_null_pointer<T>::value;

#endif

}	// namespace hamon

#endif // HAMON_TYPE_TRAITS_IS_NULL_POINTER_HPP