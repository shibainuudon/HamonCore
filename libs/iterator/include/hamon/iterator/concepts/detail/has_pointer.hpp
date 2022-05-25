/**
 *	@file	has_pointer.hpp
 *
 *	@brief	has_pointer の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_DETAIL_HAS_POINTER_HPP
#define HAMON_ITERATOR_CONCEPTS_DETAIL_HAS_POINTER_HPP

#include <hamon/type_traits/void_t.hpp>
#include <type_traits>

namespace hamon
{

namespace detail
{

template <typename, typename = void>
struct has_pointer
	: public std::false_type {};
 
template <typename T>
struct has_pointer<T, hamon::void_t<typename T::pointer>>
	: public std::true_type {};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_DETAIL_HAS_POINTER_HPP
