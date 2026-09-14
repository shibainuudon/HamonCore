/**
 *	@file	atomic_compare_exchange.hpp
 *
 *	@brief	atomic_compare_exchange の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_COMPARE_EXCHANGE_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_COMPARE_EXCHANGE_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/to_gcc_memory_order.hpp>
#include <hamon/atomic/detail/interlocked_compare_exchange.hpp>
#include <hamon/cstring/memcmp.hpp>
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
HAMON_CXX14_CONSTEXPR bool atomic_compare_exchange(T* ptr, T* expected, T desired, bool weak,
	hamon::memory_order success_memorder, hamon::memory_order failure_memorder)
{
	if (hamon::is_constant_evaluated())
	{
		if (hamon::memcmp(ptr, expected, sizeof(T)) == 0)
		{
			*ptr = desired;
			return true;
		}
		else
		{
			*expected = *ptr;
			return false;
		}
	}

#if defined(HAMON_MSVC)
	(void)weak;
	(void)success_memorder;
	(void)failure_memorder;
	T previous = *expected;
	*expected = hamon::detail::interlocked_compare_exchange(ptr, desired, previous);
	return hamon::memcmp(&previous, expected, sizeof(T)) == 0;
#else
	return __atomic_compare_exchange(
		ptr, expected, hamon::addressof(desired), weak,
		hamon::detail::to_gcc_memory_order(success_memorder),
		hamon::detail::to_gcc_memory_order(failure_memorder));
#endif
}

}	// namespace detail
}	// namespace hamon

HAMON_WARNING_POP()

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_COMPARE_EXCHANGE_HPP
