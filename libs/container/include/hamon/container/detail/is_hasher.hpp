/**
 *	@file	is_hasher.hpp
 *
 *	@brief	is_hasher の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_IS_HASHER_HPP
#define HAMON_CONTAINER_DETAIL_IS_HASHER_HPP

#include <hamon/concepts/integral.hpp>
#include <hamon/memory/detail/simple_allocator.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace detail {

// [unord.req.general]/248.3

template <typename T>
HAMON_CONCEPT_OR_BOOL is_hasher =
	!hamon::integral<T> &&
	!hamon::detail::simple_allocator<T>;

}	// namespace detail
}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_IS_HASHER_HPP
