/**
 *	@file	subrange_constructible_from_iter_sent.hpp
 *
 *	@brief	subrange_constructible_from_iter_sent の定義
 */

#ifndef HAMON_RANGES_VIEWS_DETAIL_SUBRANGE_CONSTRUCTIBLE_FROM_ITER_SENT_HPP
#define HAMON_RANGES_VIEWS_DETAIL_SUBRANGE_CONSTRUCTIBLE_FROM_ITER_SENT_HPP

#include <hamon/ranges/views/detail/convertible_to_non_slicing.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename It2, typename It, bool StoreSize>
concept subrange_constructible_from_iter_sent =
	hamon::ranges::detail::convertible_to_non_slicing<It2, It> &&
	!StoreSize;

#else

template <typename It2, typename It, bool StoreSize>
using subrange_constructible_from_iter_sent = hamon::conjunction<
	hamon::ranges::detail::convertible_to_non_slicing<It2, It>,
	hamon::bool_constant<!StoreSize>
>;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_VIEWS_DETAIL_SUBRANGE_CONSTRUCTIBLE_FROM_ITER_SENT_HPP
