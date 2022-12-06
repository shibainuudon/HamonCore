/**
 *	@file	is_integer_like.hpp
 *
 *	@brief	is_integer_like の定義
 */

#ifndef HAMON_RANGES_DETAIL_IS_INTEGER_LIKE_HPP
#define HAMON_RANGES_DETAIL_IS_INTEGER_LIKE_HPP

#include <hamon/detail/max_diff_type.hpp>
#include <hamon/detail/max_size_type.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/integral.hpp>
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
concept cv_bool = hamon::same_as<const volatile T, const volatile bool>;

template <typename T>
concept integral_nonbool =
	hamon::integral<T> &&
	!detail::cv_bool<T>;

template <typename T>
concept is_integer_like =
	detail::integral_nonbool<T> ||
	hamon::same_as<T, hamon::detail::max_diff_type> ||
	hamon::same_as<T, hamon::detail::max_size_type>;

template <typename T>
using is_integer_like_t = hamon::bool_constant<is_integer_like<T>>;

#else

template <typename T>
using cv_bool = hamon::same_as<const volatile T, const volatile bool>;

template <typename T>
using integral_nonbool = hamon::conjunction<
	hamon::integral<T>,
	hamon::negation<detail::cv_bool<T>>
>;

template <typename T>
using is_integer_like = hamon::disjunction<
	detail::integral_nonbool<T>,
	hamon::same_as<T, hamon::detail::max_diff_type>,
	hamon::same_as<T, hamon::detail::max_size_type>
>;

template <typename T>
using is_integer_like_t = is_integer_like<T>;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_IS_INTEGER_LIKE_HPP
