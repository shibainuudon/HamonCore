/**
 *	@file	all_bidirectional.hpp
 *
 *	@brief	all_bidirectional の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_DETAIL_ALL_BIDIRECTIONAL_HPP
#define HAMON_RANGES_ADAPTORS_DETAIL_ALL_BIDIRECTIONAL_HPP

#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <hamon/ranges/detail/maybe_const.hpp>
#include <hamon/type_traits/detail/all.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

#if defined(HAMON_HAS_CXX17_FOLD_EXPRESSIONS)

template <bool Const, typename... Views>
HAMON_CONCEPT_OR_BOOL all_bidirectional =
	(hamon::ranges::bidirectional_range<hamon::ranges::detail::maybe_const<Const, Views>> && ...);

#else

template <bool Const, typename... Views>
HAMON_CONCEPT_OR_BOOL all_bidirectional = hamon::detail::all_v<
	hamon::ranges::bidirectional_range<hamon::ranges::detail::maybe_const<Const, Views>>...>;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_ADAPTORS_DETAIL_ALL_BIDIRECTIONAL_HPP
