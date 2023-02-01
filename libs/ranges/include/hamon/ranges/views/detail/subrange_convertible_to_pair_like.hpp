/**
 *	@file	subrange_convertible_to_pair_like.hpp
 *
 *	@brief	subrange_convertible_to_pair_like の定義
 */

#ifndef HAMON_RANGES_VIEWS_DETAIL_SUBRANGE_CONVERTIBLE_TO_PAIR_LIKE_HPP
#define HAMON_RANGES_VIEWS_DETAIL_SUBRANGE_CONVERTIBLE_TO_PAIR_LIKE_HPP

#include <hamon/ranges/views/detail/pair_like_convertible_from.hpp>
#include <hamon/ranges/detail/different_from.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename PairLike, typename It, typename Sent, typename Subrange>
concept subrange_convertible_to_pair_like =
	hamon::ranges::detail::different_from<PairLike, Subrange> &&
	detail::pair_like_convertible_from<PairLike, It const&, Sent const&>;
#else

template <typename PairLike, typename It, typename Sent, typename Subrange>
using subrange_convertible_to_pair_like = hamon::conjunction<
	hamon::ranges::detail::different_from<PairLike, Subrange>,
	detail::pair_like_convertible_from<PairLike, It const&, Sent const&>
>;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_VIEWS_DETAIL_SUBRANGE_CONVERTIBLE_TO_PAIR_LIKE_HPP
