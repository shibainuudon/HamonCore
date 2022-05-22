/**
 *	@file	has_difference_type.hpp
 *
 *	@brief	has_difference_type の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_DETAIL_HAS_DIFFERENCE_TYPE_HPP
#define HAMON_ITERATOR_CONCEPTS_DETAIL_HAS_DIFFERENCE_TYPE_HPP

#include <hamon/type_traits/void_t.hpp>
#include <type_traits>

namespace hamon
{

namespace detail
{

template <typename, typename = void>
struct has_difference_type
	: public std::false_type {};
 
template <typename T>
struct has_difference_type<T, hamon::void_t<typename T::difference_type>>
	: public std::true_type {};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_DETAIL_HAS_DIFFERENCE_TYPE_HPP
