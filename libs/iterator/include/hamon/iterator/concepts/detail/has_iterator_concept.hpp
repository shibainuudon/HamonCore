/**
 *	@file	has_iterator_concept.hpp
 *
 *	@brief	has_iterator_concept の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_DETAIL_HAS_ITERATOR_CONCEPT_HPP
#define HAMON_ITERATOR_CONCEPTS_DETAIL_HAS_ITERATOR_CONCEPT_HPP

#include <hamon/type_traits/void_t.hpp>
#include <type_traits>

namespace hamon
{

namespace detail
{

template <typename T, typename = void>
struct has_iterator_concept
	: public std::false_type {};

template <typename T>
struct has_iterator_concept<T, hamon::void_t<typename T::iterator_concept>>
	: public std::true_type {};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_DETAIL_HAS_ITERATOR_CONCEPT_HPP
