/**
 *	@file	interlocked_compare_exchange.hpp
 *
 *	@brief	interlocked_compare_exchange の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_INTERLOCKED_COMPARE_EXCHANGE_HPP
#define HAMON_ATOMIC_DETAIL_INTERLOCKED_COMPARE_EXCHANGE_HPP

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
T interlocked_compare_exchange(T* ptr, T exchange, T comparand)
{
	return hamon::bit_cast<T>(_InterlockedCompareExchange8(reinterpret_cast<char volatile*>(ptr), hamon::bit_cast<char>(exchange), hamon::bit_cast<char>(comparand)));
}

template <typename T, hamon::enable_if_t<(sizeof(T) == 2)>* = nullptr>
T interlocked_compare_exchange(T* ptr, T exchange, T comparand)
{
	return hamon::bit_cast<T>(_InterlockedCompareExchange16(reinterpret_cast<short volatile*>(ptr), hamon::bit_cast<short>(exchange), hamon::bit_cast<short>(comparand)));
}

template <typename T, hamon::enable_if_t<(sizeof(T) == 4)>* = nullptr>
T interlocked_compare_exchange(T* ptr, T exchange, T comparand)
{
	return hamon::bit_cast<T>(_InterlockedCompareExchange(reinterpret_cast<long volatile*>(ptr), hamon::bit_cast<long>(exchange), hamon::bit_cast<long>(comparand)));
}

template <typename T, hamon::enable_if_t<(sizeof(T) == 8)>* = nullptr>
T interlocked_compare_exchange(T* ptr, T exchange, T comparand)
{
	return hamon::bit_cast<T>(_InterlockedCompareExchange64(reinterpret_cast<long long volatile*>(ptr), hamon::bit_cast<long long>(exchange), hamon::bit_cast<long long>(comparand)));
}

}	// namespace detail
}	// namespace hamon

#endif

#endif // HAMON_ATOMIC_DETAIL_INTERLOCKED_COMPARE_EXCHANGE_HPP
