/**
 *	@file	atomic.hpp
 *
 *	@brief	Atomic library
 */

#ifndef HAMON_ATOMIC_HPP
#define HAMON_ATOMIC_HPP

#include <hamon/atomic/atomic.hpp>
#include <hamon/atomic/atomic_alias.hpp>
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

  // [atomics.flag], flag type and operations
  struct atomic_flag;

  bool atomic_flag_test(const volatile atomic_flag*) noexcept;
  constexpr bool atomic_flag_test(const atomic_flag*) noexcept;
  bool atomic_flag_test_explicit(const volatile atomic_flag*, memory_order) noexcept;
  constexpr bool atomic_flag_test_explicit(const atomic_flag*, memory_order) noexcept;
  bool atomic_flag_test_and_set(volatile atomic_flag*) noexcept;
  constexpr bool atomic_flag_test_and_set(atomic_flag*) noexcept;
  bool atomic_flag_test_and_set_explicit(volatile atomic_flag*, memory_order) noexcept;
  constexpr bool atomic_flag_test_and_set_explicit(atomic_flag*, memory_order) noexcept;
  void atomic_flag_clear(volatile atomic_flag*) noexcept;
  constexpr void atomic_flag_clear(atomic_flag*) noexcept;
  void atomic_flag_clear_explicit(volatile atomic_flag*, memory_order) noexcept;
  constexpr void atomic_flag_clear_explicit(atomic_flag*, memory_order) noexcept;

  void atomic_flag_wait(const volatile atomic_flag*, bool) noexcept;
  constexpr void atomic_flag_wait(const atomic_flag*, bool) noexcept;
  void atomic_flag_wait_explicit(const volatile atomic_flag*, bool, memory_order) noexcept;
  constexpr void atomic_flag_wait_explicit(const atomic_flag*, bool, memory_order) noexcept;
  void atomic_flag_notify_one(volatile atomic_flag*) noexcept;
  constexpr void atomic_flag_notify_one(atomic_flag*) noexcept;
  void atomic_flag_notify_all(volatile atomic_flag*) noexcept;
  constexpr void atomic_flag_notify_all(atomic_flag*) noexcept;
  #define ATOMIC_FLAG_INIT see below

  // [atomics.fences], fences
  extern "C" constexpr void atomic_thread_fence(memory_order) noexcept;
  extern "C" constexpr void atomic_signal_fence(memory_order) noexcept;
}

#endif

#endif // HAMON_ATOMIC_HPP
