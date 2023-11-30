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
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace detail {

// 25.3.4.4 Concept weakly_incrementable	[iterator.concept.winc]

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept integral_nonbool =
	hamon::integral<T> &&
	!hamon::same_as<hamon::remove_cv_t<T>, bool>;

template <typename T>
concept is_integer_like =
	detail::integral_nonbool<T> ||
	detail::integer_class<T>::value;

template <typename T>
using is_integer_like_t = hamon::bool_constant<is_integer_like<T>>;

#else

template <typename T>
using integral_nonbool = hamon::conjunction<
	hamon::integral<T>,
	hamon::negation<hamon::same_as<hamon::remove_cv_t<T>, bool>>
>;

template <typename T>
using is_integer_like = hamon::disjunction<
	detail::integral_nonbool<T>,
	detail::integer_class<T>
>;

template <typename T>
using is_integer_like_t = is_integer_like<T>;

#endif

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ITERATOR_DETAIL_IS_INTEGER_LIKE_HPP
