/**
 *	@file	memory_order.hpp
 *
 *	@brief	memory_order の定義
 */

#ifndef HAMON_ATOMIC_MEMORY_ORDER_HPP
#define HAMON_ATOMIC_MEMORY_ORDER_HPP

#include <hamon/config.hpp>

namespace hamon
{

// 32.5.4 Order and consistency[atomics.order]

enum class memory_order
{
	relaxed = 0,
//	consume は C++26 で削除された
	acquire = 2,
	release = 3,
	acq_rel = 4,
	seq_cst = 5,
};

HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR memory_order memory_order_relaxed = memory_order::relaxed;
//HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR memory_order memory_order_consume = memory_order::consume;
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR memory_order memory_order_acquire = memory_order::acquire;
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR memory_order memory_order_release = memory_order::release;
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR memory_order memory_order_acq_rel = memory_order::acq_rel;
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR memory_order memory_order_seq_cst = memory_order::seq_cst;

}	// namespace hamon

#endif // HAMON_ATOMIC_MEMORY_ORDER_HPP
