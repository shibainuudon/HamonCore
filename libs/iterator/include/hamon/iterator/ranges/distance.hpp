/**
 *	@file	distance.hpp
 *
 *	@brief	ranges::distance 関数の実装
 */

#ifndef HAMON_ITERATOR_RANGES_DISTANCE_HPP
#define HAMON_ITERATOR_RANGES_DISTANCE_HPP

#include <hamon/iterator/config.hpp>

#if defined(HAMON_USE_STD_RANGES_ITERATOR)

namespace hamon
{
namespace ranges
{

using std::ranges::distance;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace ranges
{

namespace detail
{

template <
	typename It,
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::sized_sentinel_for<It> Sent
#else
	typename Sent,
	typename = hamon::enable_if_t<hamon::sized_sentinel_for<Sent, It>::value>
#endif
>
inline HAMON_CXX14_CONSTEXPR hamon::iter_difference_t<It>
distance_impl_1(hamon::detail::overload_priority<1>, It first, Sent last)
{
	return last - first;
}

template <typename It, typename Sent>
inline HAMON_CXX14_CONSTEXPR hamon::iter_difference_t<It>
distance_impl_1(hamon::detail::overload_priority<0>, It first, Sent last)
{
	hamon::iter_difference_t<It> n = 0;
	while (first != last)
	{
		++first;
		++n;
	}
	return n;
}

}	// namespace detail

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
inline HAMON_CXX14_CONSTEXPR hamon::iter_difference_t<It>
distance(It first, Sent last)
{
	return ranges::detail::distance_impl_1(
		hamon::detail::overload_priority<1>{}, first, last);
}

namespace detail
{

template <HAMON_CONSTRAINED_PARAM(ranges::sized_range, Range)>
inline HAMON_CXX14_CONSTEXPR ranges::range_difference_t<Range>
distance_impl_2(hamon::detail::overload_priority<1>, Range&& r)
{
	return static_cast<ranges::range_difference_t<Range>>(ranges::size(r));
}

template <typename Range>
inline HAMON_CXX14_CONSTEXPR ranges::range_difference_t<Range>
distance_impl_2(hamon::detail::overload_priority<0>, Range&& r)
{
	return ranges::distance(ranges::begin(r), ranges::end(r));
}

}	// namespace detail

template <HAMON_CONSTRAINED_PARAM(ranges::range, Range)>
inline HAMON_CXX14_CONSTEXPR ranges::range_difference_t<Range>
distance(Range&& r)
{
	return ranges::detail::distance_impl_2(
		hamon::detail::overload_priority<1>{}, hamon::forward<Range>(r));
}

}	// namespace ranges

}	// namespace hamon

#endif

#endif // HAMON_ITERATOR_RANGES_DISTANCE_HPP
