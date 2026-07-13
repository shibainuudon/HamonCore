/**
 *	@file	is_integer_like.hpp
 *
 *	@brief	is_integer_like の定義
 */

#ifndef HAMON_ITERATOR_DETAIL_IS_INTEGER_LIKE_HPP
#define HAMON_ITERATOR_DETAIL_IS_INTEGER_LIKE_HPP

#include <hamon/iterator/detail/integer_class.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace detail {

// 25.3.4.4 Concept weakly_incrementable	[iterator.concept.winc]

template <typename T>
HAMON_CONCEPT_OR_BOOL integral_nonbool =
	hamon::integral<T> &&
	!hamon::same_as<hamon::remove_cv_t<T>, bool>;

template <typename T>
HAMON_CONCEPT_OR_BOOL is_integer_like =
	detail::integral_nonbool<T> ||
	detail::integer_class<T>::value;

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ITERATOR_DETAIL_IS_INTEGER_LIKE_HPP
