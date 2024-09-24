/**
 *	@file	atomic_compare_exchange_weak.hpp
 *
 *	@brief	atomic_compare_exchange_weak の実装
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_COMPARE_EXCHANGE_WEAK_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_COMPARE_EXCHANGE_WEAK_HPP

#include <hamon/config.hpp>
#if defined(HAMON_MSVC)
#include <intrin.h>
#endif

namespace hamon
{

namespace detail
{

bool atomic_compare_exchange_weak(long* ptr, long* expected, long desired)
{
#if defined(HAMON_MSVC)
	long previous = *expected;
	*expected = _InterlockedCompareExchange(ptr, desired, previous);
	return previous == *expected;
#else
	return __atomic_compare_exchange_n(ptr, expected, desired, true, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
#endif
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_COMPARE_EXCHANGE_WEAK_HPP
