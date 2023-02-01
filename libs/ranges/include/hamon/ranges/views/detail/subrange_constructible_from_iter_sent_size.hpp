/**
 *	@file	subrange_constructible_from_iter_sent_size.hpp
 *
 *	@brief	subrange_constructible_from_iter_sent_size の定義
 */

#ifndef HAMON_RANGES_VIEWS_DETAIL_SUBRANGE_CONSTRUCTIBLE_FROM_ITER_SENT_SIZE_HPP
#define HAMON_RANGES_VIEWS_DETAIL_SUBRANGE_CONSTRUCTIBLE_FROM_ITER_SENT_SIZE_HPP

#include <hamon/ranges/views/subrange_kind.hpp>
#include <hamon/ranges/views/detail/convertible_to_non_slicing.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace detail {

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename It2, typename It, ranges::subrange_kind Kind>
concept subrange_constructible_from_iter_sent_size =
	hamon::ranges::detail::convertible_to_non_slicing<It2, It> &&
	Kind == ranges::subrange_kind::sized;

#else

template <typename It2, typename It, ranges::subrange_kind Kind>
using subrange_constructible_from_iter_sent_size = hamon::conjunction<
	hamon::ranges::detail::convertible_to_non_slicing<It2, It>,
	hamon::bool_constant<Kind == ranges::subrange_kind::sized>
>;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_VIEWS_DETAIL_SUBRANGE_CONSTRUCTIBLE_FROM_ITER_SENT_SIZE_HPP
