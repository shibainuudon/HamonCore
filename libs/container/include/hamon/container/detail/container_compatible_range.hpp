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
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace detail {

// [container.intro.reqmts]/2

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename R, typename T>
HAMON_CONCEPT_OR_BOOL container_compatible_range =
	hamon::ranges::input_range<R> &&
	hamon::convertible_to<hamon::ranges::range_reference_t<R>, T>;

#else

template <typename R, typename T, typename = void>
struct container_compatible_range_impl
	: public hamon::false_type{};

template <typename R, typename T>
struct container_compatible_range_impl<R, T, hamon::enable_if_t<
	hamon::ranges::input_range<R> &&
	hamon::convertible_to<hamon::ranges::range_reference_t<R>, T>
>> : public hamon::true_type{};

template <typename R, typename T>
HAMON_CONCEPT_OR_BOOL container_compatible_range =
	container_compatible_range_impl<R, T>::value;

#endif

}	// namespace detail
}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_CONTAINER_COMPATIBLE_RANGE_HPP
