/**
 *	@file	memory_order.hpp
 *
 *	@brief	memory_order の定義
 */

#ifndef HAMON_ATOMIC_MEMORY_ORDER_HPP
#define HAMON_ATOMIC_MEMORY_ORDER_HPP

#include <hamon/config.hpp>
#include <atomic>

namespace hamon
{

// 33.5.4 Order and consistency[atomics.order]

#if HAMON_CXX_STANDARD >= 20

using std::memory_order;
using std::memory_order_relaxed;
using std::memory_order_consume;
using std::memory_order_acquire;
using std::memory_order_release;
using std::memory_order_acq_rel;
using std::memory_order_seq_cst;

#else

enum class memory_order
{
	relaxed = std::memory_order_relaxed,
	consume = std::memory_order_consume,
	acquire = std::memory_order_acquire,
	release = std::memory_order_release,
	acq_rel = std::memory_order_acq_rel,
	seq_cst = std::memory_order_seq_cst,
};

HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR memory_order memory_order_relaxed = memory_order::relaxed;
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR memory_order memory_order_consume = memory_order::consume;
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR memory_order memory_order_acquire = memory_order::acquire;
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR memory_order memory_order_release = memory_order::release;
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR memory_order memory_order_acq_rel = memory_order::acq_rel;
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR memory_order memory_order_seq_cst = memory_order::seq_cst;

#endif

}	// namespace hamon

#endif // HAMON_ATOMIC_MEMORY_ORDER_HPP
