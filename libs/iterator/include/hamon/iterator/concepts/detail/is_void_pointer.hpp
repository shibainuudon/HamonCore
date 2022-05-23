﻿/**
 *	@file	is_void_pointer.hpp
 *
 *	@brief	is_void_pointer の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_DETAIL_IS_VOID_POINTER_HPP
#define HAMON_ITERATOR_CONCEPTS_DETAIL_IS_VOID_POINTER_HPP

#include <type_traits>

namespace hamon
{

namespace detail
{

template <typename T>
using is_void_pointer = std::is_void<typename std::remove_pointer<T>::type>;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_DETAIL_IS_VOID_POINTER_HPP