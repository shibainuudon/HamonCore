/**
 *	@file	atomic_store_min.hpp
 *
 *	@brief	atomic_store_min の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_STORE_MIN_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_STORE_MIN_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/atomic_fetch_min.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

template <HAMON_CONSTRAINT(hamon::arithmetic, T)>
HAMON_CXX14_CONSTEXPR void atomic_store_min(T* ptr, T val, hamon::memory_order order)
{
	// TODO: __atomic_store_minビルトイン関数が実装されるまではatomic_fetch_minで代用する
	hamon::detail::atomic_fetch_min(ptr, val, order);
}

template <HAMON_CONSTRAINT(hamon::arithmetic, T)>
HAMON_CXX14_CONSTEXPR void atomic_store_min(T* ptr, T val)
{
	hamon::detail::atomic_store_min(ptr, val, hamon::memory_order::seq_cst);
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_STORE_MIN_HPP
