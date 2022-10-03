/**
 *	@file	integer_like.hpp
 *
 *	@brief	integer_like の定義
 */

#ifndef HAMON_RANGES_DETAIL_INTEGER_LIKE_HPP
#define HAMON_RANGES_DETAIL_INTEGER_LIKE_HPP

#include <hamon/ranges/detail/integral_nonbool.hpp>
#include <hamon/ranges/detail/max_diff_type.hpp>
#include <hamon/ranges/detail/max_size_type.hpp>
#include <hamon/concepts/same_as.hpp>
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
concept integer_like =
	detail::integral_nonbool<T> ||
	hamon::same_as<T, detail::max_diff_type> ||
	hamon::same_as<T, detail::max_size_type>;

template <typename T>
concept not_integer_like = !integer_like<T>;

template <typename T>
using integer_like_t = hamon::bool_constant<integer_like<T>>;

#else

template <typename T>
using integer_like = hamon::disjunction<
	detail::integral_nonbool<T>,
	hamon::same_as<T, detail::max_diff_type>,
	hamon::same_as<T, detail::max_size_type>
>;

template <typename T>
using not_integer_like = hamon::negation<integer_like<T>>;

template <typename T>
using integer_like_t = integer_like<T>;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_INTEGER_LIKE_HPP
