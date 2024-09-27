/**
 *	@file	atomic_fetch_and.hpp
 *
 *	@brief	atomic_fetch_and の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_FETCH_AND_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_FETCH_AND_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/to_gcc_memory_order.hpp>
#include <hamon/atomic/detail/interlocked_and.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <HAMON_CONSTRAINED_PARAM(hamon::integral, T)>
T atomic_fetch_and(T* ptr, T val, hamon::memory_order order)
{
#if defined(HAMON_MSVC)
	(void)order;
	return hamon::detail::interlocked_and(ptr, val);
#else
	return __atomic_fetch_and(ptr, val, hamon::detail::to_gcc_memory_order(order));
#endif
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, T)>
T atomic_fetch_and(T* ptr, T val)
{
	return hamon::detail::atomic_fetch_and(ptr, val, hamon::memory_order::seq_cst);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_FETCH_AND_HPP
