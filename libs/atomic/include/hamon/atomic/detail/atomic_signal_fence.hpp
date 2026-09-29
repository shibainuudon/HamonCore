/**
 *	@file	atomic_signal_fence.hpp
 *
 *	@brief	atomic_signal_fence の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_SIGNAL_FENCE_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_SIGNAL_FENCE_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/to_gcc_memory_order.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_MSVC)
#include <intrin.h>		// _ReadWriteBarrier
#endif

namespace hamon
{
namespace detail
{

constexpr void atomic_signal_fence(memory_order order) noexcept
{
	if (hamon::is_constant_evaluated())
	{
		// do nothing
		return;
	}

#if HAMON_HAS_BUILTIN(__atomic_signal_fence)
	__atomic_signal_fence(hamon::detail::to_gcc_memory_order(order));

#elif defined(HAMON_MSVC)
	if (order == memory_order::relaxed)
	{
		// do nothing
		return;
	}

	_ReadWriteBarrier();
#endif
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_SIGNAL_FENCE_HPP
