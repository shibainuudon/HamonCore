/**
 *	@file	alloc_rebind.hpp
 *
 *	@brief	alloc_rebind の定義
 */

#ifndef HAMON_CONTAINER_DETAIL_ALLOC_REBIND_HPP
#define HAMON_CONTAINER_DETAIL_ALLOC_REBIND_HPP

#include <hamon/memory/allocator_traits.hpp>

namespace hamon {
namespace detail {

// [container.adaptors.general]/8
template <typename Allocator, typename T>
using alloc_rebind = typename hamon::allocator_traits<Allocator>::template rebind_alloc<T>;

}	// namespace detail
}	// namespace hamon

#endif // HAMON_CONTAINER_DETAIL_ALLOC_REBIND_HPP
