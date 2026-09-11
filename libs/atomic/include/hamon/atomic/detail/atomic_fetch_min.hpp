/**
 *	@file	atomic_fetch_min.hpp
 *
 *	@brief	atomic_fetch_min の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_FETCH_MIN_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_FETCH_MIN_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/atomic_load.hpp>
#include <hamon/atomic/detail/atomic_compare_exchange_weak.hpp>
#include <hamon/atomic/detail/to_gcc_memory_order.hpp>
#include <hamon/concepts/integral.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/utility/exchange.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

template <HAMON_CONSTRAINT(hamon::integral, T)>
HAMON_CXX14_CONSTEXPR T atomic_fetch_min(T* ptr, T val, hamon::memory_order order)
{
	if (hamon::is_constant_evaluated())
	{
		return hamon::exchange(*ptr, *ptr < val ? *ptr : val);
	}

#if HAMON_HAS_BUILTIN(__atomic_fetch_min)
	return __atomic_fetch_min(ptr, val, hamon::detail::to_gcc_memory_order(order));
#else
	T ret = hamon::detail::atomic_load(ptr, hamon::memory_order::relaxed);
	T value{};
	do
	{
		value = ret < val ? ret : val;
	}
	while (!hamon::detail::atomic_compare_exchange_weak(
		ptr, hamon::addressof(ret), value, order, hamon::memory_order::relaxed));

	return ret;
#endif
}

template <HAMON_CONSTRAINT(hamon::integral, T)>
HAMON_CXX14_CONSTEXPR T atomic_fetch_min(T* ptr, T val)
{
	return hamon::detail::atomic_fetch_min(ptr, val, hamon::memory_order::seq_cst);
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_FETCH_MIN_HPP
