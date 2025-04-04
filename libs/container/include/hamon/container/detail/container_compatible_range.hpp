/**
 *	@file	container_compatible_range.hpp
 *
 *	@brief	container_compatible_range の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_CONTAINER_COMPATIBLE_RANGE_HPP
#define HAMON_CONTAINER_DETAIL_CONTAINER_COMPATIBLE_RANGE_HPP

#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace detail {

// [container.intro.reqmts]/2

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename R, typename T>
concept container_compatible_range =
	hamon::ranges::input_range<R> &&
	hamon::convertible_to<hamon::ranges::range_reference_t<R>, T>;

#else

template <typename R, typename T>
using container_compatible_range = hamon::conjunction<
	hamon::ranges::input_range_t<R>,
	hamon::convertible_to_t<hamon::ranges::range_reference_t<R>, T>
>;

#endif

}	// namespace detail
}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_CONTAINER_COMPATIBLE_RANGE_HPP
