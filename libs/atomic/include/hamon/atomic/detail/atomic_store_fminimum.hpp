/**
 *	@file	atomic_store_fminimum.hpp
 *
 *	@brief	atomic_store_fminimum の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_STORE_FMINIMUM_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_STORE_FMINIMUM_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/atomic_fetch_fminimum.hpp>
#include <hamon/concepts/arithmetic.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

template <HAMON_CONSTRAINT(hamon::arithmetic, T)>
HAMON_CXX14_CONSTEXPR void atomic_store_fminimum(T* ptr, T val, hamon::memory_order order)
{
	// TODO: __atomic_store_fminimumビルトイン関数が実装されるまではatomic_fetch_fminimumで代用する
	hamon::detail::atomic_fetch_fminimum(ptr, val, order);
}

template <HAMON_CONSTRAINT(hamon::arithmetic, T)>
HAMON_CXX14_CONSTEXPR void atomic_store_fminimum(T* ptr, T val)
{
	hamon::detail::atomic_store_fminimum(ptr, val, hamon::memory_order::seq_cst);
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_STORE_FMINIMUM_HPP
