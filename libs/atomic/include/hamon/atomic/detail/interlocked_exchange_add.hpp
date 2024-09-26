/**
 *	@file	interlocked_exchange_add.hpp
 *
 *	@brief	interlocked_exchange_add の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_INTERLOCKED_EXCHANGE_ADD_HPP
#define HAMON_ATOMIC_DETAIL_INTERLOCKED_EXCHANGE_ADD_HPP

#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#if defined(HAMON_MSVC)
#include <intrin.h>

namespace hamon
{
namespace detail
{

template <typename T, hamon::enable_if_t<(sizeof(T) == 1)>* = nullptr>
T interlocked_exchange_add(T* ptr, T val)
{
	return static_cast<T>(_InterlockedExchangeAdd8(reinterpret_cast<char volatile*>(ptr), static_cast<char>(val)));
}

template <typename T, hamon::enable_if_t<(sizeof(T) == 2)>* = nullptr>
T interlocked_exchange_add(T* ptr, T val)
{
	return static_cast<T>(_InterlockedExchangeAdd16(reinterpret_cast<short volatile*>(ptr), static_cast<short>(val)));
}

template <typename T, hamon::enable_if_t<(sizeof(T) == 4)>* = nullptr>
T interlocked_exchange_add(T* ptr, T val)
{
	return static_cast<T>(_InterlockedExchangeAdd(reinterpret_cast<long volatile*>(ptr), static_cast<long>(val)));
}

template <typename T, hamon::enable_if_t<(sizeof(T) == 8)>* = nullptr>
T interlocked_exchange_add(T* ptr, T val)
{
	return static_cast<T>(_interlockedexchangeadd64(reinterpret_cast<long long volatile*>(ptr), static_cast<long long>(val)));
}

}	// namespace detail
}	// namespace hamon

#endif

#endif // HAMON_ATOMIC_DETAIL_INTERLOCKED_EXCHANGE_ADD_HPP
