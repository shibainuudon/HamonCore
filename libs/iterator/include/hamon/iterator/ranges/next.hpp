/**
 *	@file	next.hpp
 *
 *	@brief	ranges::next 関数の実装
 */

#ifndef HAMON_ITERATOR_RANGES_NEXT_HPP
#define HAMON_ITERATOR_RANGES_NEXT_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{
namespace ranges
{

using std::ranges::next;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/iterator/ranges/advance.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/iterator/concepts/random_access_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/cmath/abs.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace detail
{

// next(it) の実装

template <HAMON_CONSTRAINED_PARAM(hamon::random_access_iterator, It)>
inline HAMON_CXX11_CONSTEXPR It
next_impl(It it, hamon::detail::overload_priority<1>)
{
	return it + 1;
}

template <typename It>
inline HAMON_CXX14_CONSTEXPR It
next_impl(It it, hamon::detail::overload_priority<0>)
{
	++it;
	return it;
}

template <typename It>
inline HAMON_CXX11_CONSTEXPR It
next_impl(It it)
{
	return next_impl(it, hamon::detail::overload_priority<1>{});
}

// next(it, n) の実装

template <HAMON_CONSTRAINED_PARAM(hamon::random_access_iterator, It)>
inline HAMON_CXX11_CONSTEXPR It
next_impl(It it, hamon::iter_difference_t<It> n, hamon::detail::overload_priority<1>)
{
	return it + n;
}

template <typename It>
inline HAMON_CXX14_CONSTEXPR It
next_impl(It it, hamon::iter_difference_t<It> n, hamon::detail::overload_priority<0>)
{
	hamon::ranges::advance(it, n);
	return it;
}

template <typename It>
inline HAMON_CXX11_CONSTEXPR It
next_impl(It it, hamon::iter_difference_t<It> n)
{
	return next_impl(it, n, hamon::detail::overload_priority<1>{});
}

// next(it, bound) の実装

template <typename It, HAMON_CONSTRAINED_PARAM(hamon::convertible_to, It, Sent)>
inline HAMON_CXX11_CONSTEXPR It
next_impl(It /*it*/, Sent bound, hamon::detail::overload_priority<2>)
{
	return bound;
}

template <typename It, HAMON_CONSTRAINED_PARAM(hamon::sized_sentinel_for, It, Sent)>
inline HAMON_CXX11_CONSTEXPR It
next_impl(It it, Sent bound, hamon::detail::overload_priority<1>)
{
	return next_impl(it, bound - it);
}

template <typename It, HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, It, Sent)>
inline HAMON_CXX14_CONSTEXPR It
next_impl(It it, Sent bound, hamon::detail::overload_priority<0>)
{
	hamon::ranges::advance(it, bound);
	return it;
}

template <typename It, HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, It, Sent)>
inline HAMON_CXX11_CONSTEXPR It
next_impl(It it, Sent bound)
{
	return next_impl(it, bound, hamon::detail::overload_priority<2>{});
}

// next(it, n, bound) の実装

template <typename It, HAMON_CONSTRAINED_PARAM(hamon::sized_sentinel_for, It, Sent)>
inline HAMON_CXX11_CONSTEXPR It
next_impl(It it, hamon::iter_difference_t<It> n, Sent bound, hamon::detail::overload_priority<1>)
{
	return hamon::abs(n) >= hamon::abs(bound - it) ?
		next_impl(it, bound) :
		next_impl(it, n);
}

template <typename It, HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, It, Sent)>
inline HAMON_CXX14_CONSTEXPR It
next_impl(It it, hamon::iter_difference_t<It> n, Sent bound, hamon::detail::overload_priority<0>)
{
	hamon::ranges::advance(it, n, bound);
	return it;
}

template <typename It, HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, It, Sent)>
inline HAMON_CXX11_CONSTEXPR It
next_impl(It it, hamon::iter_difference_t<It> n, Sent bound)
{
	return next_impl(it, n, bound, hamon::detail::overload_priority<1>{});
}

}	// namespace detail

template <HAMON_CONSTRAINED_PARAM(hamon::input_or_output_iterator, It)>
inline HAMON_CXX11_CONSTEXPR It
next(It it)
{
	return hamon::ranges::detail::next_impl(it);
}

template <HAMON_CONSTRAINED_PARAM(hamon::input_or_output_iterator, It)>
inline HAMON_CXX11_CONSTEXPR It
next(It it, hamon::iter_difference_t<It> n)
{
	return hamon::ranges::detail::next_impl(it, n);
}

template <
	HAMON_CONSTRAINED_PARAM(hamon::input_or_output_iterator, It),
	HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, It, Sent)
>
inline HAMON_CXX11_CONSTEXPR It
next(It it, Sent bound)
{
	return hamon::ranges::detail::next_impl(it, bound);
}

template <
	HAMON_CONSTRAINED_PARAM(hamon::input_or_output_iterator, It),
	HAMON_CONSTRAINED_PARAM(hamon::sentinel_for, It, Sent)
>
inline HAMON_CXX11_CONSTEXPR It
next(It it, hamon::iter_difference_t<It> n, Sent bound)
{
	return hamon::ranges::detail::next_impl(it, n, bound);
}

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_RANGES_NEXT_HPP
