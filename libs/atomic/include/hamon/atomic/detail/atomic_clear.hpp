/**
 *	@file	atomic_clear.hpp
 *
 *	@brief	atomic_clear の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_CLEAR_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_CLEAR_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/to_gcc_memory_order.hpp>
#include <hamon/atomic/detail/atomic_store.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace detail
{

inline HAMON_CXX14_CONSTEXPR
void atomic_clear(bool* ptr, hamon::memory_order order)
{
	if (hamon::is_constant_evaluated())
	{
		*ptr = false;
		return;
	}

#if HAMON_HAS_BUILTIN(__atomic_clear)
	__atomic_clear(ptr, hamon::detail::to_gcc_memory_order(order));
#else
	hamon::detail::atomic_store(ptr, false, order);
#endif
}

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_CLEAR_HPP
