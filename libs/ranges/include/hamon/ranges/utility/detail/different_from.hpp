/**
 *	@file	different_from.hpp
 *
 *	@brief	different_from の定義
 */

#ifndef HAMON_RANGES_UTILITY_DETAIL_DIFFERENT_FROM_HPP
#define HAMON_RANGES_UTILITY_DETAIL_DIFFERENT_FROM_HPP

#include <hamon/concepts/same_as.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

// [range.utility.helpers]/1

template <typename T, typename U>
HAMON_CONCEPT_OR_BOOL different_from =
	!hamon::same_as<
		hamon::remove_cvref_t<T>,
		hamon::remove_cvref_t<U>>;

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_UTILITY_DETAIL_DIFFERENT_FROM_HPP
