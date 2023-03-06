/**
 *	@file	has_pointer.hpp
 *
 *	@brief	has_pointer の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_DETAIL_HAS_POINTER_HPP
#define HAMON_ITERATOR_CONCEPTS_DETAIL_HAS_POINTER_HPP

#include <hamon/type_traits/void_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

namespace detail
{

template <typename, typename = void>
struct has_pointer
	: public hamon::false_type {};
 
template <typename T>
struct has_pointer<T, hamon::void_t<typename T::pointer>>
	: public hamon::true_type {};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_DETAIL_HAS_POINTER_HPP
