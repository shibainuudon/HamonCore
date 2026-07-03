/**
 *	@file	is_hasher.hpp
 *
 *	@brief	is_hasher の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_IS_HASHER_HPP
#define HAMON_CONTAINER_DETAIL_IS_HASHER_HPP

#include <hamon/concepts/integral.hpp>
#include <hamon/memory/detail/simple_allocator.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace detail {

// [unord.req.general]/248.3

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept is_hasher =
	!hamon::integral<T> &&
	!hamon::detail::simple_allocator<T>;

#else

template <typename T>
using is_hasher = hamon::bool_constant<
	!hamon::integral<T> &&
	!hamon::detail::simple_allocator<T>::value
>;

#endif

}	// namespace detail
}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_IS_HASHER_HPP
