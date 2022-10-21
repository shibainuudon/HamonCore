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
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

template <HAMON_CONSTRAINED_PARAM(hamon::input_or_output_iterator, It)>
inline HAMON_CXX14_CONSTEXPR It
next(It x)
{
	++x;
	return x;
}

template <HAMON_CONSTRAINED_PARAM(hamon::input_or_output_iterator, It)>
inline HAMON_CXX14_CONSTEXPR It
next(It x, hamon::iter_difference_t<It> n)
{
	ranges::advance(x, n);
	return x;
}

template <
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::input_or_output_iterator It, hamon::sentinel_for<It> Sent
#else
	typename It, typename Sent,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::input_or_output_iterator<It>,
		hamon::sentinel_for<Sent, It>
	>::value>
#endif
>
inline HAMON_CXX14_CONSTEXPR It
next(It x, Sent bound)
{
	ranges::advance(x, bound);
	return x;
}

template <
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::input_or_output_iterator It, hamon::sentinel_for<It> Sent
#else
	typename It, typename Sent,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::input_or_output_iterator<It>,
		hamon::sentinel_for<Sent, It>
	>::value>
#endif
>
inline HAMON_CXX14_CONSTEXPR It
next(It x, hamon::iter_difference_t<It> n, Sent bound)
{
	ranges::advance(x, n, bound);
	return x;
}

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_RANGES_NEXT_HPP
