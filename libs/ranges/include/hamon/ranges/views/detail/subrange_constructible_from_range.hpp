/**
 *	@file	subrange_constructible_from_range.hpp
 *
 *	@brief	subrange_constructible_from_range の定義
 */

#ifndef HAMON_RANGES_VIEWS_DETAIL_SUBRANGE_CONSTRUCTIBLE_FROM_RANGE_HPP
#define HAMON_RANGES_VIEWS_DETAIL_SUBRANGE_CONSTRUCTIBLE_FROM_RANGE_HPP

#include <hamon/ranges/views/detail/convertible_to_non_slicing.hpp>
#include <hamon/ranges/concepts/borrowed_range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/detail/different_from.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Rng, typename It, typename Sent, typename Subrange, bool StoreSize>
concept subrange_constructible_from_range =
	hamon::ranges::detail::different_from<Rng, Subrange> &&
	hamon::ranges::borrowed_range<Rng> &&
	detail::convertible_to_non_slicing<hamon::ranges::iterator_t<Rng>, It> &&
	hamon::convertible_to<hamon::ranges::sentinel_t<Rng>, Sent> &&
	(!StoreSize || hamon::ranges::sized_range<Rng>);

#else

template <typename Rng, typename It, typename Sent, typename Subrange, bool StoreSize>
using subrange_constructible_from_range = hamon::conjunction<
	hamon::ranges::detail::different_from<Rng, Subrange>,
	hamon::ranges::borrowed_range<Rng>,
	detail::convertible_to_non_slicing<hamon::ranges::iterator_t<Rng>, It>,
	hamon::convertible_to<hamon::ranges::sentinel_t<Rng>, Sent>,
	hamon::bool_constant<(!StoreSize || hamon::ranges::sized_range<Rng>::value)>
>;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_VIEWS_DETAIL_SUBRANGE_CONSTRUCTIBLE_FROM_RANGE_HPP
