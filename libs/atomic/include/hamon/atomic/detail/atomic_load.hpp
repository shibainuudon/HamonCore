/**
 *	@file	atomic_load.hpp
 *
 *	@brief	atomic_load の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_LOAD_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_LOAD_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/to_gcc_memory_order.hpp>
#include <hamon/atomic/detail/interlocked_exchange_add.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/config.hpp>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Watomic-alignment")

namespace hamon
{
namespace detail
{

template <typename T>
HAMON_CXX14_CONSTEXPR T atomic_load(T* ptr, hamon::memory_order order)
{
	if (hamon::is_constant_evaluated())
	{
		return *ptr;
	}

#if defined(HAMON_MSVC)
	(void)order;
	return hamon::detail::interlocked_exchange_add(ptr, T(0));
#else
	T ret{};
	__atomic_load(ptr, hamon::addressof(ret), hamon::detail::to_gcc_memory_order(order));
	return ret;
#endif
}

template <typename T>
HAMON_CXX14_CONSTEXPR T atomic_load(T* ptr)
{
	return hamon::detail::atomic_load(ptr, hamon::memory_order::seq_cst);
}

}	// namespace detail
}	// namespace hamon

HAMON_WARNING_POP()

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_LOAD_HPP
