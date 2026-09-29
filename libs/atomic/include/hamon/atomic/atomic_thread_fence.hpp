/**
 *	@file	atomic_thread_fence.hpp
 *
 *	@brief	atomic_thread_fence の定義
 */

#ifndef HAMON_ATOMIC_ATOMIC_THREAD_FENCE_HPP
#define HAMON_ATOMIC_ATOMIC_THREAD_FENCE_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/atomic_thread_fence.hpp>

namespace hamon
{

// 32.5.11 Fences[atomics.fences]

constexpr void atomic_thread_fence(memory_order order) noexcept
{
	hamon::detail::atomic_thread_fence(order);
}

}	// namespace hamon

#endif // HAMON_ATOMIC_ATOMIC_THREAD_FENCE_HPP
