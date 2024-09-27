/**
 *	@file	interlocked_increment.hpp
 *
 *	@brief	interlocked_increment の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_INTERLOCKED_INCREMENT_HPP
#define HAMON_ATOMIC_DETAIL_INTERLOCKED_INCREMENT_HPP

#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#if defined(HAMON_MSVC)
#include <intrin.h>

namespace hamon
{
namespace detail
{

template <typename T, hamon::enable_if_t<(sizeof(T) == 1)>* = nullptr>
T interlocked_increment(T* ptr)
{
	// _InterlockedIncrement8は無い
	auto before = _InterlockedExchangeAdd8(reinterpret_cast<char volatile*>(ptr), 1);
	++before;
	return static_cast<T>(before);
}

template <typename T, hamon::enable_if_t<(sizeof(T) == 2)>* = nullptr>
T interlocked_increment(T* ptr)
{
	return static_cast<T>(_InterlockedIncrement16(reinterpret_cast<short volatile*>(ptr)));
}

template <typename T, hamon::enable_if_t<(sizeof(T) == 4)>* = nullptr>
T interlocked_increment(T* ptr)
{
	return static_cast<T>(_InterlockedIncrement(reinterpret_cast<long volatile*>(ptr)));
}

template <typename T, hamon::enable_if_t<(sizeof(T) == 8)>* = nullptr>
T interlocked_increment(T* ptr)
{
	return static_cast<T>(_interlockedincrement64(reinterpret_cast<long long volatile*>(ptr)));
}

}	// namespace detail
}	// namespace hamon

#endif

#endif // HAMON_ATOMIC_DETAIL_INTERLOCKED_INCREMENT_HPP
