/**
 *	@file	atomic_decrement.hpp
 *
 *	@brief	atomic_decrement の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_DECREMENT_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_DECREMENT_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/to_gcc_memory_order.hpp>
#include <hamon/atomic/detail/interlocked_decrement.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <HAMON_CONSTRAINED_PARAM(hamon::integral, T)>
T atomic_decrement(T* ptr, hamon::memory_order order)
{
#if defined(HAMON_MSVC)
	(void)order;
	return hamon::detail::interlocked_decrement(ptr);
#else
	return __atomic_sub_fetch(ptr, T(1), hamon::detail::to_gcc_memory_order(order));
#endif
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, T)>
T atomic_decrement(T* ptr)
{
	return hamon::detail::atomic_decrement(ptr, hamon::memory_order::seq_cst);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_DECREMENT_HPP
