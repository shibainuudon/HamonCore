/**
 *	@file	atomic_store_max.hpp
 *
 *	@brief	atomic_store_max の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_STORE_MAX_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_STORE_MAX_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/atomic_fetch_max.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

template <HAMON_CONSTRAINT(hamon::arithmetic, T)>
HAMON_CXX14_CONSTEXPR void atomic_store_max(T* ptr, T val, hamon::memory_order order)
{
	// TODO: __atomic_store_maxビルトイン関数が実装されるまではatomic_fetch_maxで代用する
	hamon::detail::atomic_fetch_max(ptr, val, order);
}

template <HAMON_CONSTRAINT(hamon::arithmetic, T)>
HAMON_CXX14_CONSTEXPR void atomic_store_max(T* ptr, T val)
{
	hamon::detail::atomic_store_max(ptr, val, hamon::memory_order::seq_cst);
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_STORE_MAX_HPP
