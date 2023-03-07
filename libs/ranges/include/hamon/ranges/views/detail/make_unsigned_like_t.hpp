/**
 *	@file	make_unsigned_like_t.hpp
 *
 *	@brief	make_unsigned_like_t の定義
 */

#ifndef HAMON_RANGES_VIEWS_DETAIL_MAKE_UNSIGNED_LIKE_T_HPP
#define HAMON_RANGES_VIEWS_DETAIL_MAKE_UNSIGNED_LIKE_T_HPP

#include <hamon/ranges/detail/to_unsigned_like.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon {
namespace ranges {
namespace detail {

template <typename T>
using make_unsigned_like_t =
	decltype(hamon::ranges::detail::to_unsigned_like(hamon::declval<T>()));

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_VIEWS_DETAIL_MAKE_UNSIGNED_LIKE_T_HPP
