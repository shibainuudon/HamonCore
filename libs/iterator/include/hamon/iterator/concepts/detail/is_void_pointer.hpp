/**
 *	@file	is_void_pointer.hpp
 *
 *	@brief	is_void_pointer の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_DETAIL_IS_VOID_POINTER_HPP
#define HAMON_ITERATOR_CONCEPTS_DETAIL_IS_VOID_POINTER_HPP

#include <hamon/type_traits/remove_pointer.hpp>
#include <hamon/type_traits/is_void.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
using is_void_pointer = hamon::is_void<hamon::remove_pointer_t<T>>;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_DETAIL_IS_VOID_POINTER_HPP
