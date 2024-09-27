﻿/**
 *	@file	interlocked_xor.hpp
 *
 *	@brief	interlocked_xor の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_INTERLOCKED_XOR_HPP
#define HAMON_ATOMIC_DETAIL_INTERLOCKED_XOR_HPP

#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>
#if defined(HAMON_MSVC)
#include <intrin.h>

namespace hamon
{
namespace detail
{

template <typename T, hamon::enable_if_t<(sizeof(T) == 1)>* = nullptr>
T interlocked_xor(T* ptr, T val)
{
	return static_cast<T>(_InterlockedXor8(reinterpret_cast<char volatile*>(ptr), static_cast<char>(val)));
}

template <typename T, hamon::enable_if_t<(sizeof(T) == 2)>* = nullptr>
T interlocked_xor(T* ptr, T val)
{
	return static_cast<T>(_InterlockedXor16(reinterpret_cast<short volatile*>(ptr), static_cast<short>(val)));
}

template <typename T, hamon::enable_if_t<(sizeof(T) == 4)>* = nullptr>
T interlocked_xor(T* ptr, T val)
{
	return static_cast<T>(_InterlockedXor(reinterpret_cast<long volatile*>(ptr), static_cast<long>(val)));
}

template <typename T, hamon::enable_if_t<(sizeof(T) == 8)>* = nullptr>
T interlocked_xor(T* ptr, T val)
{
	return static_cast<T>(_interlockedxor64(reinterpret_cast<long long volatile*>(ptr), static_cast<long long>(val)));
}

}	// namespace detail
}	// namespace hamon

#endif

#endif // HAMON_ATOMIC_DETAIL_INTERLOCKED_XOR_HPP
