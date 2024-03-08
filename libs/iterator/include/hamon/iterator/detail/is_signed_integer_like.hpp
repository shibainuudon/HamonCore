/**
 *	@file	is_signed_integer_like.hpp
 *
 *	@brief	is_signed_integer_like の定義
 */

#ifndef HAMON_ITERATOR_DETAIL_IS_SIGNED_INTEGER_LIKE_HPP
#define HAMON_ITERATOR_DETAIL_IS_SIGNED_INTEGER_LIKE_HPP

#include <hamon/iterator/detail/signed_integer_class.hpp>
#include <hamon/concepts/signed_integral.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace detail {

// 25.3.4.4 Concept weakly_incrementable	[iterator.concept.winc]

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept is_signed_integer_like =
	hamon::signed_integral<T> ||
	detail::signed_integer_class<T>::value;

template <typename T>
using is_signed_integer_like_t = hamon::bool_constant<is_signed_integer_like<T>>;

#else

template <typename T>
using is_signed_integer_like = hamon::disjunction<
	hamon::signed_integral<T>,
	detail::signed_integer_class<T>
>;

template <typename T>
using is_signed_integer_like_t = is_signed_integer_like<T>;

#endif

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ITERATOR_DETAIL_IS_SIGNED_INTEGER_LIKE_HPP
