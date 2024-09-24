/**
 *	@file	atomic_fetch_sub.hpp
 *
 *	@brief	atomic_fetch_sub の実装
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_FETCH_SUB_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_FETCH_SUB_HPP

#include <hamon/config.hpp>
#if defined(HAMON_MSVC)
#include <intrin.h>
#endif

namespace hamon
{

namespace detail
{

long atomic_fetch_sub(long* x, long a)
{
#if defined(HAMON_MSVC)
	return _InterlockedExchangeAdd(x, -a);
#else
	return __atomic_fetch_sub(x, a, __ATOMIC_SEQ_CST);
#endif
}

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_FETCH_SUB_HPP
