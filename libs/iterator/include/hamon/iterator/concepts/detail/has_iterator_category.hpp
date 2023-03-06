/**
 *	@file	has_iterator_category.hpp
 *
 *	@brief	has_iterator_category の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_DETAIL_HAS_ITERATOR_CATEGORY_HPP
#define HAMON_ITERATOR_CONCEPTS_DETAIL_HAS_ITERATOR_CATEGORY_HPP

#include <hamon/type_traits/void_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

namespace detail
{

template <typename, typename = void>
struct has_iterator_category
	: public hamon::false_type {};
 
template <typename T>
struct has_iterator_category<T, hamon::void_t<typename T::iterator_category>>
	: public hamon::true_type {};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_DETAIL_HAS_ITERATOR_CATEGORY_HPP
