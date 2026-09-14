/**
 *	@file	interlocked_exchange.hpp
 *
 *	@brief	interlocked_exchange の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_INTERLOCKED_EXCHANGE_HPP
#define HAMON_ATOMIC_DETAIL_INTERLOCKED_EXCHANGE_HPP

#include <hamon/bit/bit_cast.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

#if defined(HAMON_MSVC)
#include <intrin.h>

namespace hamon
{
namespace detail
{

template <typename T, hamon::enable_if_t<(sizeof(T) == 1)>* = nullptr>
T interlocked_exchange(T* ptr, T val)
{
	return hamon::bit_cast<T>(_InterlockedExchange8(reinterpret_cast<char volatile*>(ptr), hamon::bit_cast<char>(val)));
}

template <typename T, hamon::enable_if_t<(sizeof(T) == 2)>* = nullptr>
T interlocked_exchange(T* ptr, T val)
{
	return hamon::bit_cast<T>(_InterlockedExchange16(reinterpret_cast<short volatile*>(ptr), hamon::bit_cast<short>(val)));
}

template <typename T, hamon::enable_if_t<(sizeof(T) == 4)>* = nullptr>
T interlocked_exchange(T* ptr, T val)
{
	return hamon::bit_cast<T>(_InterlockedExchange(reinterpret_cast<long volatile*>(ptr), hamon::bit_cast<long>(val)));
}

template <typename T, hamon::enable_if_t<(sizeof(T) == 8)>* = nullptr>
T interlocked_exchange(T* ptr, T val)
{
	return hamon::bit_cast<T>(_interlockedexchange64(reinterpret_cast<long long volatile*>(ptr), hamon::bit_cast<long long>(val)));
}

}	// namespace detail
}	// namespace hamon

#endif

#endif // HAMON_ATOMIC_DETAIL_INTERLOCKED_EXCHANGE_HPP
