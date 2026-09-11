/**
 *	@file	atomic_exchange.hpp
 *
 *	@brief	atomic_exchange の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_EXCHANGE_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_EXCHANGE_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/to_gcc_memory_order.hpp>
#include <hamon/atomic/detail/interlocked_exchange.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/utility/exchange.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <HAMON_CONSTRAINT(hamon::integral, T)>
HAMON_CXX14_CONSTEXPR T atomic_exchange(T* ptr, T val, hamon::memory_order order)
{
	if (hamon::is_constant_evaluated())
	{
		return hamon::exchange(*ptr, val);
	}

#if defined(HAMON_MSVC)
	(void)order;
	return hamon::detail::interlocked_exchange(ptr, val);
#else
	return __atomic_exchange_n(ptr, val, hamon::detail::to_gcc_memory_order(order));
#endif
}

template <HAMON_CONSTRAINT(hamon::integral, T)>
HAMON_CXX14_CONSTEXPR T atomic_exchange(T* ptr, T val)
{
	return hamon::detail::atomic_exchange(ptr, val, hamon::memory_order::seq_cst);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_EXCHANGE_HPP
