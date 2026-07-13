/**
 *	@file	is_unsigned_integer_like.hpp
 *
 *	@brief	is_unsigned_integer_like の定義
 */

#ifndef HAMON_ITERATOR_DETAIL_IS_UNSIGNED_INTEGER_LIKE_HPP
#define HAMON_ITERATOR_DETAIL_IS_UNSIGNED_INTEGER_LIKE_HPP

#include <hamon/iterator/detail/unsigned_integer_class.hpp>
#include <hamon/concepts/unsigned_integral.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace detail {

// 25.3.4.4 Concept weakly_incrementable	[iterator.concept.winc]

template <typename T>
HAMON_CONCEPT_OR_BOOL is_unsigned_integer_like =
	hamon::unsigned_integral<T> ||
	detail::unsigned_integer_class<T>::value;

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ITERATOR_DETAIL_IS_UNSIGNED_INTEGER_LIKE_HPP
