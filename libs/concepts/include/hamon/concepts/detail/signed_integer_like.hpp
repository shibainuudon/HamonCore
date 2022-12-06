/**
 *	@file	signed_integer_like.hpp
 *
 *	@brief	signed_integer_like の定義
 */

#ifndef HAMON_CONCEPTS_DETAIL_SIGNED_INTEGER_LIKE_HPP
#define HAMON_CONCEPTS_DETAIL_SIGNED_INTEGER_LIKE_HPP

#include <hamon/concepts/signed_integral.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/detail/max_diff_type.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept signed_integer_like =
	hamon::signed_integral<T> ||
	hamon::same_as<T, hamon::detail::max_diff_type>;

template <typename T>
concept not_signed_integer_like = !signed_integer_like<T>;

template <typename T>
using signed_integer_like_t = hamon::bool_constant<signed_integer_like<T>>;

#else

template <typename T>
using signed_integer_like = hamon::disjunction<
	hamon::signed_integral<T>,
	hamon::same_as<T, hamon::detail::max_diff_type>
>;

template <typename T>
using not_signed_integer_like = hamon::negation<signed_integer_like<T>>;

template <typename T>
using signed_integer_like_t = signed_integer_like<T>;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_CONCEPTS_DETAIL_SIGNED_INTEGER_LIKE_HPP
