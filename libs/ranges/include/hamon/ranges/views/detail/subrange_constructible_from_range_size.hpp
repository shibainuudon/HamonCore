/**
 *	@file	subrange_constructible_from_range_size.hpp
 *
 *	@brief	subrange_constructible_from_range_size の定義
 */

#ifndef HAMON_RANGES_VIEWS_DETAIL_SUBRANGE_CONSTRUCTIBLE_FROM_RANGE_SIZE_HPP
#define HAMON_RANGES_VIEWS_DETAIL_SUBRANGE_CONSTRUCTIBLE_FROM_RANGE_SIZE_HPP

#include <hamon/ranges/views/detail/convertible_to_non_slicing.hpp>
#include <hamon/ranges/views/subrange_kind.hpp>
#include <hamon/ranges/concepts/borrowed_range.hpp>
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

template <typename Rng, typename It, typename Sent, ranges::subrange_kind Kind>
concept subrange_constructible_from_range_size =
	hamon::ranges::borrowed_range<Rng> &&
	detail::convertible_to_non_slicing<hamon::ranges::iterator_t<Rng>, It> &&
	hamon::convertible_to<hamon::ranges::sentinel_t<Rng>, Sent> &&
	(Kind == ranges::subrange_kind::sized);

#else

template <typename Rng, typename It, typename Sent, ranges::subrange_kind Kind>
using subrange_constructible_from_range_size = hamon::conjunction<
	hamon::ranges::borrowed_range<Rng>,
	detail::convertible_to_non_slicing<hamon::ranges::iterator_t<Rng>, It>,
	hamon::convertible_to<hamon::ranges::sentinel_t<Rng>, Sent>,
	hamon::bool_constant<Kind == ranges::subrange_kind::sized>
>;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_VIEWS_DETAIL_SUBRANGE_CONSTRUCTIBLE_FROM_RANGE_SIZE_HPP
