/**
 *	@file	atomic_compare_exchange_strong.hpp
 *
 *	@brief	atomic_compare_exchange_strong の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_COMPARE_EXCHANGE_STRONG_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_COMPARE_EXCHANGE_STRONG_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/atomic_compare_exchange.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

template <typename T>
HAMON_CXX14_CONSTEXPR bool atomic_compare_exchange_strong(T* ptr, T* expected, T desired,
	hamon::memory_order success_memorder, hamon::memory_order failure_memorder)
{
	return hamon::detail::atomic_compare_exchange(
		ptr, expected, desired, false, success_memorder, failure_memorder);
}

template <typename T>
HAMON_CXX14_CONSTEXPR bool atomic_compare_exchange_strong(T* ptr, T* expected, T desired)
{
	return hamon::detail::atomic_compare_exchange_strong(ptr, expected, desired,
		hamon::memory_order::seq_cst, hamon::memory_order::seq_cst);
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_COMPARE_EXCHANGE_STRONG_HPP
