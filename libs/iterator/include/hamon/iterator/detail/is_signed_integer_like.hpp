/**
 *	@file	is_signed_integer_like.hpp
 *
 *	@brief	is_signed_integer_like の定義
 */

#ifndef HAMON_ITERATOR_DETAIL_IS_SIGNED_INTEGER_LIKE_HPP
#define HAMON_ITERATOR_DETAIL_IS_SIGNED_INTEGER_LIKE_HPP

#include <hamon/iterator/detail/signed_integer_class.hpp>
#include <hamon/concepts/signed_integral.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace detail {

// 25.3.4.4 Concept weakly_incrementable	[iterator.concept.winc]

template <typename T>
HAMON_CONCEPT_OR_BOOL is_signed_integer_like =
	hamon::signed_integral<T> ||
	detail::signed_integer_class<T>::value;

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ITERATOR_DETAIL_IS_SIGNED_INTEGER_LIKE_HPP
