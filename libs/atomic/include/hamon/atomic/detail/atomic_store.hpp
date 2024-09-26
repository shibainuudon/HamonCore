/**
 *	@file	atomic_store.hpp
 *
 *	@brief	atomic_store の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_STORE_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_STORE_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/to_gcc_memory_order.hpp>
#include <hamon/atomic/detail/interlocked_exchange.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <HAMON_CONSTRAINED_PARAM(hamon::integral, T)>
void atomic_store(T* ptr, T val, hamon::memory_order order)
{
#if defined(HAMON_MSVC)
	(void)order;
	hamon::detail::interlocked_exchange(ptr, val);
#else
	__atomic_store_n(ptr, val, hamon::detail::to_gcc_memory_order(order));
#endif
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, T)>
void atomic_store(T* ptr, T val)
{
	hamon::detail::atomic_store(ptr, val, hamon::memory_order::seq_cst);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_STORE_HPP
