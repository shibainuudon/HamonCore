/**
 *	@file	to_gcc_memory_order.hpp
 *
 *	@brief	to_gcc_memory_order の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_TO_GCC_MEMORY_ORDER_HPP
#define HAMON_ATOMIC_DETAIL_TO_GCC_MEMORY_ORDER_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

inline HAMON_CXX11_CONSTEXPR int
to_gcc_memory_order(hamon::memory_order order)
{
#if defined(__ATOMIC_RELAXED) && defined(__ATOMIC_ACQUIRE) && \
	defined(__ATOMIC_RELEASE) && defined(__ATOMIC_ACQ_REL) && defined(__ATOMIC_SEQ_CST)
	return
		order == hamon::memory_order::relaxed ? __ATOMIC_RELAXED :
		order == hamon::memory_order::acquire ? __ATOMIC_ACQUIRE :
		order == hamon::memory_order::release ? __ATOMIC_RELEASE :
		order == hamon::memory_order::acq_rel ? __ATOMIC_ACQ_REL :
		order == hamon::memory_order::seq_cst ? __ATOMIC_SEQ_CST : 0;
#else
	return static_cast<int>(order);
#endif
}


}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_TO_GCC_MEMORY_ORDER_HPP
