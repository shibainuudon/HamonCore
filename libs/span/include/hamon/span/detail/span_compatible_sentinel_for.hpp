/**
 *	@file	span_compatible_sentinel_for.hpp
 *
 *	@brief
 */

#ifndef HAMON_SPAN_DETAIL_SPAN_COMPATIBLE_SENTINEL_FOR_HPP
#define HAMON_SPAN_DETAIL_SPAN_COMPATIBLE_SENTINEL_FOR_HPP

#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/config.hpp>
#include <type_traits>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Sentinel, typename It>
concept span_compatible_sentinel_for =
	hamon::sized_sentinel_for<Sentinel, It> &&
	!std::is_convertible<Sentinel, std::size_t>::value;

#else

template <typename Sentinel, typename It>
using span_compatible_sentinel_for = hamon::conjunction<
	hamon::sized_sentinel_for<Sentinel, It>,
	hamon::negation<std::is_convertible<Sentinel, std::size_t>>
>;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_SPAN_DETAIL_SPAN_COMPATIBLE_SENTINEL_FOR_HPP
