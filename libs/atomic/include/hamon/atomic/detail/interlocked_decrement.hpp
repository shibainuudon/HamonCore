/**
 *	@file	interlocked_decrement.hpp
 *
 *	@brief	interlocked_decrement の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_INTERLOCKED_DECREMENT_HPP
#define HAMON_ATOMIC_DETAIL_INTERLOCKED_DECREMENT_HPP

#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#if defined(HAMON_MSVC)
#include <intrin.h>

namespace hamon
{
namespace detail
{

template <typename T, hamon::enable_if_t<(sizeof(T) == 1)>* = nullptr>
T interlocked_decrement(T* ptr)
{
	// _InterlockedDecrement8は無い
	auto before = _InterlockedExchangeAdd8(reinterpret_cast<char volatile*>(ptr), char(-1));
	--before;
	return static_cast<T>(before);
}

template <typename T, hamon::enable_if_t<(sizeof(T) == 2)>* = nullptr>
T interlocked_decrement(T* ptr)
{
	return static_cast<T>(_InterlockedDecrement16(reinterpret_cast<short volatile*>(ptr)));
}

template <typename T, hamon::enable_if_t<(sizeof(T) == 4)>* = nullptr>
T interlocked_decrement(T* ptr)
{
	return static_cast<T>(_InterlockedDecrement(reinterpret_cast<long volatile*>(ptr)));
}

template <typename T, hamon::enable_if_t<(sizeof(T) == 8)>* = nullptr>
T interlocked_decrement(T* ptr)
{
	return static_cast<T>(_interlockeddecrement64(reinterpret_cast<long long volatile*>(ptr)));
}

}	// namespace detail
}	// namespace hamon

#endif

#endif // HAMON_ATOMIC_DETAIL_INTERLOCKED_DECREMENT_HPP
