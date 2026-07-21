/**
 *	@file	all_random_access.hpp
 *
 *	@brief	all_random_access の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_DETAIL_ALL_RANDOM_ACCESS_HPP
#define HAMON_RANGES_ADAPTORS_DETAIL_ALL_RANDOM_ACCESS_HPP

#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/ranges/detail/maybe_const.hpp>
#include <hamon/type_traits/detail/all.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

#if defined(HAMON_HAS_CXX17_FOLD_EXPRESSIONS)

template <bool Const, typename... Views>
HAMON_CONCEPT_OR_BOOL all_random_access =
	(hamon::ranges::random_access_range<hamon::ranges::detail::maybe_const<Const, Views>> && ...);

#else

template <bool Const, typename... Views>
HAMON_CONCEPT_OR_BOOL all_random_access = hamon::detail::all_v<
	hamon::ranges::random_access_range<hamon::ranges::detail::maybe_const<Const, Views>>...>;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_ADAPTORS_DETAIL_ALL_RANDOM_ACCESS_HPP
