/**
 *	@file	different_from.hpp
 *
 *	@brief	different_from の定義
 */

#ifndef HAMON_RANGES_UTILITY_DETAIL_DIFFERENT_FROM_HPP
#define HAMON_RANGES_UTILITY_DETAIL_DIFFERENT_FROM_HPP

#include <hamon/concepts/same_as.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

// [range.utility.helpers]/1

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, typename U>
concept different_from =
	!hamon::same_as<
		hamon::remove_cvref_t<T>,
		hamon::remove_cvref_t<U>>;

#else

template <typename T, typename U>
using different_from =
	hamon::negation<
		hamon::same_as<
			hamon::remove_cvref_t<T>,
			hamon::remove_cvref_t<U>
		>
	>;

#endif

template <typename T, typename U>
using different_from_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::ranges::detail::different_from<T, U>>;
#else
	hamon::ranges::detail::different_from<T, U>;
#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_UTILITY_DETAIL_DIFFERENT_FROM_HPP
