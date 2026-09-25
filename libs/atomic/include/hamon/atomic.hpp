/**
 *	@file	atomic.hpp
 *
 *	@brief	Atomic library
 */

#ifndef HAMON_ATOMIC_HPP
#define HAMON_ATOMIC_HPP

#include <hamon/atomic/atomic.hpp>
#include <hamon/atomic/atomic_alias.hpp>
#include <hamon/atomic/atomic_flag.hpp>
#include <hamon/atomic/atomic_nonmember.hpp>
#include <hamon/atomic/memory_order.hpp>

#if 0

// [atomics.lockfree], lock-free property
#define ATOMIC_BOOL_LOCK_FREE unspecified
#define ATOMIC_CHAR_LOCK_FREE unspecified
#define ATOMIC_CHAR8_T_LOCK_FREE unspecified
#define ATOMIC_CHAR16_T_LOCK_FREE unspecified
#define ATOMIC_CHAR32_T_LOCK_FREE unspecified
#define ATOMIC_WCHAR_T_LOCK_FREE unspecified
#define ATOMIC_SHORT_LOCK_FREE unspecified
#define ATOMIC_INT_LOCK_FREE unspecified
#define ATOMIC_LONG_LOCK_FREE unspecified
#define ATOMIC_LLONG_LOCK_FREE unspecified
#define ATOMIC_POINTER_LOCK_FREE unspecified

namespace std {
  // [atomics.ref.generic], class template atomic_ref
  template<class T> struct atomic_ref;


  // [atomics.fences], fences
  extern "C" constexpr void atomic_thread_fence(memory_order) noexcept;
  extern "C" constexpr void atomic_signal_fence(memory_order) noexcept;
}

#endif

#endif // HAMON_ATOMIC_HPP
