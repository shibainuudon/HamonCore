/**
 *	@file	atomic_compare_exchange.hpp
 *
 *	@brief	atomic_compare_exchange の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_COMPARE_EXCHANGE_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_COMPARE_EXCHANGE_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/to_gcc_memory_order.hpp>
#include <hamon/atomic/detail/interlocked_compare_exchange.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <HAMON_CONSTRAINED_PARAM(hamon::integral, T)>
bool atomic_compare_exchange(T* ptr, T* expected, T desired, bool weak,
	hamon::memory_order success_memorder, hamon::memory_order failure_memorder)
{
#if defined(HAMON_MSVC)
	(void)weak;
	(void)success_memorder;
	(void)failure_memorder;
	T previous = *expected;
	*expected = hamon::detail::interlocked_compare_exchange(ptr, desired, previous);
	return previous == *expected;
#else
	return __atomic_compare_exchange_n(
		ptr, expected, desired, weak,
		hamon::detail::to_gcc_memory_order(success_memorder),
		hamon::detail::to_gcc_memory_order(failure_memorder));
#endif
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_COMPARE_EXCHANGE_HPP
