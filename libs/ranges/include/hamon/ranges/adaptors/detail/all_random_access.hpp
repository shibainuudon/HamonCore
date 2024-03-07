/**
 *	@file	all_random_access.hpp
 *
 *	@brief	all_random_access の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_DETAIL_ALL_RANDOM_ACCESS_HPP
#define HAMON_RANGES_ADAPTORS_DETAIL_ALL_RANDOM_ACCESS_HPP

#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/ranges/detail/maybe_const.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <bool Const, typename... Views>
concept all_random_access =
	(hamon::ranges::random_access_range<hamon::ranges::detail::maybe_const<Const, Views>> && ...);

template <bool Const, typename... Views>
using all_random_access_t = hamon::bool_constant<all_random_access<Const, Views...>>;

#else

template <bool Const, typename... Views>
using all_random_access_t = hamon::conjunction<
	hamon::ranges::random_access_range_t<hamon::ranges::detail::maybe_const<Const, Views>>...>;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_ADAPTORS_DETAIL_ALL_RANDOM_ACCESS_HPP
