/**
 *	@file	integral_nonbool.hpp
 *
 *	@brief	integral_nonbool の定義
 */

#ifndef HAMON_RANGES_DETAIL_INTEGRAL_NONBOOL_HPP
#define HAMON_RANGES_DETAIL_INTEGRAL_NONBOOL_HPP

#include <hamon/ranges/detail/cv_bool.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/type_traits/conjunction.hpp>
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
concept integral_nonbool =
	hamon::integral<T> &&
	!detail::cv_bool<T>;

#else

template <typename T>
using integral_nonbool = hamon::conjunction<
	hamon::integral<T>,
	hamon::negation<detail::cv_bool<T>>
>;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace hamon

#endif // HAMON_RANGES_DETAIL_INTEGRAL_NONBOOL_HPP
