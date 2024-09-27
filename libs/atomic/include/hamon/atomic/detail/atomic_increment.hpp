/**
 *	@file	atomic_increment.hpp
 *
 *	@brief	atomic_increment の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_INCREMENT_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_INCREMENT_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/to_gcc_memory_order.hpp>
#include <hamon/atomic/detail/interlocked_increment.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <HAMON_CONSTRAINED_PARAM(hamon::integral, T)>
T atomic_increment(T* ptr, hamon::memory_order order)
{
#if defined(HAMON_MSVC)
	(void)order;
	return hamon::detail::interlocked_increment(ptr);
#else
	return __atomic_add_fetch(ptr, T(1), hamon::detail::to_gcc_memory_order(order));
#endif
}

template <HAMON_CONSTRAINED_PARAM(hamon::integral, T)>
T atomic_increment(T* ptr)
{
	return hamon::detail::atomic_increment(ptr, hamon::memory_order::seq_cst);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_INCREMENT_HPP
