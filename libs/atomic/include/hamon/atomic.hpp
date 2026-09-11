/**
 *	@file	atomic.hpp
 *
 *	@brief	Atomic library
 */

#ifndef HAMON_ATOMIC_HPP
#define HAMON_ATOMIC_HPP

#include <hamon/atomic/atomic.hpp>
#include <hamon/atomic/memory_order.hpp>

#if 0

// mostly freestanding
namespace std {
  // [atomics.order], order and consistency
  enum class memory_order : unspecified;
  inline constexpr memory_order memory_order_relaxed = memory_order::relaxed;
  inline constexpr memory_order memory_order_acquire = memory_order::acquire;
  inline constexpr memory_order memory_order_release = memory_order::release;
  inline constexpr memory_order memory_order_acq_rel = memory_order::acq_rel;
  inline constexpr memory_order memory_order_seq_cst = memory_order::seq_cst;
}

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

  // [atomics.types.generic], class template atomic
  template<class T> struct atomic;
  // [atomics.types.pointer], partial specialization for pointers
  template<class T> struct atomic<T*>;

  // [atomics.nonmembers], non-member functions
  template<class T>
    bool atomic_is_lock_free(const volatile atomic<T>*) noexcept;
  template<class T>
    bool atomic_is_lock_free(const atomic<T>*) noexcept;
  template<class T>
    void atomic_store(volatile atomic<T>*, typename atomic<T>::value_type) noexcept;
  template<class T>
    constexpr void atomic_store(atomic<T>*, typename atomic<T>::value_type) noexcept;
  template<class T>
    void atomic_store_explicit(volatile atomic<T>*, typename atomic<T>::value_type,
                               memory_order) noexcept;
  template<class T>
    constexpr void atomic_store_explicit(atomic<T>*, typename atomic<T>::value_type,
                                         memory_order) noexcept;
  template<class T>
    T atomic_load(const volatile atomic<T>*) noexcept;
  template<class T>
    constexpr T atomic_load(const atomic<T>*) noexcept;
  template<class T>
    T atomic_load_explicit(const volatile atomic<T>*, memory_order) noexcept;
  template<class T>
    constexpr T atomic_load_explicit(const atomic<T>*, memory_order) noexcept;
  template<class T>
    T atomic_exchange(volatile atomic<T>*, typename atomic<T>::value_type) noexcept;
  template<class T>
    constexpr T atomic_exchange(atomic<T>*, typename atomic<T>::value_type) noexcept;
  template<class T>
    T atomic_exchange_explicit(volatile atomic<T>*, typename atomic<T>::value_type,
                               memory_order) noexcept;
  template<class T>
    constexpr T atomic_exchange_explicit(atomic<T>*, typename atomic<T>::value_type,
                                         memory_order) noexcept;
  template<class T>
    bool atomic_compare_exchange_weak(volatile atomic<T>*,
                                      typename atomic<T>::value_type*,
                                      typename atomic<T>::value_type) noexcept;
  template<class T>
    constexpr bool atomic_compare_exchange_weak(atomic<T>*,
                                                typename atomic<T>::value_type*,
                                                typename atomic<T>::value_type) noexcept;
  template<class T>
    bool atomic_compare_exchange_strong(volatile atomic<T>*,
                                        typename atomic<T>::value_type*,
                                        typename atomic<T>::value_type) noexcept;
  template<class T>
    constexpr bool atomic_compare_exchange_strong(atomic<T>*,
                                                  typename atomic<T>::value_type*,
                                                  typename atomic<T>::value_type) noexcept;
  template<class T>
    bool atomic_compare_exchange_weak_explicit(volatile atomic<T>*,
                                               typename atomic<T>::value_type*,
                                               typename atomic<T>::value_type,
                                               memory_order, memory_order) noexcept;
  template<class T>
    constexpr bool atomic_compare_exchange_weak_explicit(atomic<T>*,
                                                         typename atomic<T>::value_type*,
                                                         typename atomic<T>::value_type,
                                                         memory_order, memory_order) noexcept;
  template<class T>
    bool atomic_compare_exchange_strong_explicit(volatile atomic<T>*,
                                                 typename atomic<T>::value_type*,
                                                 typename atomic<T>::value_type,
                                                 memory_order, memory_order) noexcept;
  template<class T>
    constexpr bool atomic_compare_exchange_strong_explicit(atomic<T>*,
                                                           typename atomic<T>::value_type*,
                                                           typename atomic<T>::value_type,
                                                           memory_order, memory_order) noexcept;

  template<class T>
    T atomic_fetch_add(volatile atomic<T>*, typename atomic<T>::difference_type) noexcept;
  template<class T>
    constexpr T atomic_fetch_add(atomic<T>*, typename atomic<T>::difference_type) noexcept;
  template<class T>
    T atomic_fetch_add_explicit(volatile atomic<T>*, typename atomic<T>::difference_type,
                                memory_order) noexcept;
  template<class T>
    constexpr T atomic_fetch_add_explicit(atomic<T>*, typename atomic<T>::difference_type,
                                          memory_order) noexcept;
  template<class T>
    T atomic_fetch_sub(volatile atomic<T>*, typename atomic<T>::difference_type) noexcept;
  template<class T>
    constexpr T atomic_fetch_sub(atomic<T>*, typename atomic<T>::difference_type) noexcept;
  template<class T>
    T atomic_fetch_sub_explicit(volatile atomic<T>*, typename atomic<T>::difference_type,
                                memory_order) noexcept;
  template<class T>
    constexpr T atomic_fetch_sub_explicit(atomic<T>*, typename atomic<T>::difference_type,
                                          memory_order) noexcept;
  template<class T>
    T atomic_fetch_and(volatile atomic<T>*, typename atomic<T>::value_type) noexcept;
  template<class T>
    constexpr T atomic_fetch_and(atomic<T>*, typename atomic<T>::value_type) noexcept;
  template<class T>
    T atomic_fetch_and_explicit(volatile atomic<T>*, typename atomic<T>::value_type,
                                memory_order) noexcept;
  template<class T>
    constexpr T atomic_fetch_and_explicit(atomic<T>*, typename atomic<T>::value_type,
                                          memory_order) noexcept;
  template<class T>
    T atomic_fetch_or(volatile atomic<T>*, typename atomic<T>::value_type) noexcept;
  template<class T>
    constexpr T atomic_fetch_or(atomic<T>*, typename atomic<T>::value_type) noexcept;
  template<class T>
    T atomic_fetch_or_explicit(volatile atomic<T>*, typename atomic<T>::value_type,
                               memory_order) noexcept;
  template<class T>
    constexpr T atomic_fetch_or_explicit(atomic<T>*, typename atomic<T>::value_type,
                                         memory_order) noexcept;
  template<class T>
    T atomic_fetch_xor(volatile atomic<T>*, typename atomic<T>::value_type) noexcept;
  template<class T>
    constexpr T atomic_fetch_xor(atomic<T>*, typename atomic<T>::value_type) noexcept;
  template<class T>
    T atomic_fetch_xor_explicit(volatile atomic<T>*, typename atomic<T>::value_type,
                                memory_order) noexcept;
  template<class T>
    constexpr T atomic_fetch_xor_explicit(atomic<T>*, typename atomic<T>::value_type,
                                          memory_order) noexcept;
  template<class T>
    T atomic_fetch_max(volatile atomic<T>*, typename atomic<T>::value_type) noexcept;
  template<class T>
    constexpr T atomic_fetch_max(atomic<T>*, typename atomic<T>::value_type) noexcept;
  template<class T>
    T atomic_fetch_max_explicit(volatile atomic<T>*, typename atomic<T>::value_type,
                                memory_order) noexcept;
  template<class T>
    constexpr T atomic_fetch_max_explicit(atomic<T>*, typename atomic<T>::value_type,
                                          memory_order) noexcept;
  template<class T>
    T atomic_fetch_min(volatile atomic<T>*, typename atomic<T>::value_type) noexcept;
  template<class T>
    constexpr T atomic_fetch_min(atomic<T>*, typename atomic<T>::value_type) noexcept;
  template<class T>
    T atomic_fetch_min_explicit(volatile atomic<T>*, typename atomic<T>::value_type,
                                memory_order) noexcept;
  template<class T>
    constexpr T atomic_fetch_min_explicit(atomic<T>*, typename atomic<T>::value_type,
                                          memory_order) noexcept;

  template<class T>
    void atomic_store_add(volatile atomic<T>*, typename atomic<T>::difference_type) noexcept;
  template<class T>
    constexpr void atomic_store_add(atomic<T>*, typename atomic<T>::difference_type) noexcept;
  template<class T>
    void atomic_store_add_explicit(volatile atomic<T>*, typename atomic<T>::difference_type,
                                   memory_order) noexcept;
  template<class T>
    constexpr void atomic_store_add_explicit(atomic<T>*, typename atomic<T>::difference_type,
                                             memory_order) noexcept;
  template<class T>
    void atomic_store_sub(volatile atomic<T>*, typename atomic<T>::difference_type) noexcept;
  template<class T>
    constexpr void atomic_store_sub(atomic<T>*, typename atomic<T>::difference_type) noexcept;
  template<class T>
    void atomic_store_sub_explicit(volatile atomic<T>*, typename atomic<T>::difference_type,
                                   memory_order) noexcept;
  template<class T>
    constexpr void atomic_store_sub_explicit(atomic<T>*, typename atomic<T>::difference_type,
                                             memory_order) noexcept;
  template<class T>
    void atomic_store_and(volatile atomic<T>*, typename atomic<T>::value_type) noexcept;
  template<class T>
    constexpr void atomic_store_and(atomic<T>*, typename atomic<T>::value_type) noexcept;
  template<class T>
    void atomic_store_and_explicit(volatile atomic<T>*, typename atomic<T>::value_type,
                                   memory_order) noexcept;
  template<class T>
    constexpr void atomic_store_and_explicit(atomic<T>*, typename atomic<T>::value_type,
                                             memory_order) noexcept;
  template<class T>
    void atomic_store_or(volatile atomic<T>*, typename atomic<T>::value_type) noexcept;
  template<class T>
    constexpr void atomic_store_or(atomic<T>*, typename atomic<T>::value_type) noexcept;
  template<class T>
    void atomic_store_or_explicit(volatile atomic<T>*, typename atomic<T>::value_type,
                                  memory_order) noexcept;
  template<class T>
    constexpr void atomic_store_or_explicit(atomic<T>*, typename atomic<T>::value_type,
                                            memory_order) noexcept;
  template<class T>
    void atomic_store_xor(volatile atomic<T>*, typename atomic<T>::value_type) noexcept;
  template<class T>
    constexpr void atomic_store_xor(atomic<T>*, typename atomic<T>::value_type) noexcept;
  template<class T>
    void atomic_store_xor_explicit(volatile atomic<T>*, typename atomic<T>::value_type,
                                   memory_order) noexcept;
  template<class T>
    constexpr void atomic_store_xor_explicit(atomic<T>*, typename atomic<T>::value_type,
                                             memory_order) noexcept;
  template<class T>
    void atomic_store_max(volatile atomic<T>*, typename atomic<T>::value_type) noexcept;
  template<class T>
    constexpr void atomic_store_max(atomic<T>*, typename atomic<T>::value_type) noexcept;
  template<class T>
    void atomic_store_max_explicit(volatile atomic<T>*, typename atomic<T>::value_type,
                                   memory_order) noexcept;
  template<class T>
    constexpr void atomic_store_max_explicit(atomic<T>*, typename atomic<T>::value_type,
                                             memory_order) noexcept;
  template<class T>
    void atomic_store_min(volatile atomic<T>*, typename atomic<T>::value_type) noexcept;
  template<class T>
    constexpr void atomic_store_min(atomic<T>*, typename atomic<T>::value_type) noexcept;
  template<class T>
    void atomic_store_min_explicit(volatile atomic<T>*, typename atomic<T>::value_type,
                                   memory_order) noexcept;
  template<class T>
    constexpr void atomic_store_min_explicit(atomic<T>*, typename atomic<T>::value_type,
                                             memory_order) noexcept;

  template<class T>
    void atomic_wait(const volatile atomic<T>*, typename atomic<T>::value_type) noexcept;
  template<class T>
    constexpr void atomic_wait(const atomic<T>*, typename atomic<T>::value_type) noexcept;
  template<class T>
    void atomic_wait_explicit(const volatile atomic<T>*, typename atomic<T>::value_type,
                              memory_order) noexcept;
  template<class T>
    constexpr void atomic_wait_explicit(const atomic<T>*, typename atomic<T>::value_type,
                                        memory_order) noexcept;
  template<class T>
    void atomic_notify_one(volatile atomic<T>*) noexcept;
  template<class T>
    constexpr void atomic_notify_one(atomic<T>*) noexcept;
  template<class T>
    void atomic_notify_all(volatile atomic<T>*) noexcept;
  template<class T>
    constexpr void atomic_notify_all(atomic<T>*) noexcept;

  // [atomics.alias], type aliases
  using atomic_bool           = atomic<bool>;
  using atomic_char           = atomic<char>;
  using atomic_schar          = atomic<signed char>;
  using atomic_uchar          = atomic<unsigned char>;
  using atomic_short          = atomic<short>;
  using atomic_ushort         = atomic<unsigned short>;
  using atomic_int            = atomic<int>;
  using atomic_uint           = atomic<unsigned int>;
  using atomic_long           = atomic<long>;
  using atomic_ulong          = atomic<unsigned long>;
  using atomic_llong          = atomic<long long>;
  using atomic_ullong         = atomic<unsigned long long>;
  using atomic_char8_t        = atomic<char8_t>;
  using atomic_char16_t       = atomic<char16_t>;
  using atomic_char32_t       = atomic<char32_t>;
  using atomic_wchar_t        = atomic<wchar_t>;

  using atomic_int8_t         = atomic<int8_t>;
  using atomic_uint8_t        = atomic<uint8_t>;
  using atomic_int16_t        = atomic<int16_t>;
  using atomic_uint16_t       = atomic<uint16_t>;
  using atomic_int32_t        = atomic<int32_t>;
  using atomic_uint32_t       = atomic<uint32_t>;
  using atomic_int64_t        = atomic<int64_t>;
  using atomic_uint64_t       = atomic<uint64_t>;

  using atomic_int_least8_t   = atomic<int_least8_t>;
  using atomic_uint_least8_t  = atomic<uint_least8_t>;
  using atomic_int_least16_t  = atomic<int_least16_t>;
  using atomic_uint_least16_t = atomic<uint_least16_t>;
  using atomic_int_least32_t  = atomic<int_least32_t>;
  using atomic_uint_least32_t = atomic<uint_least32_t>;
  using atomic_int_least64_t  = atomic<int_least64_t>;
  using atomic_uint_least64_t = atomic<uint_least64_t>;

  using atomic_int_fast8_t    = atomic<int_fast8_t>;
  using atomic_uint_fast8_t   = atomic<uint_fast8_t>;
  using atomic_int_fast16_t   = atomic<int_fast16_t>;
  using atomic_uint_fast16_t  = atomic<uint_fast16_t>;
  using atomic_int_fast32_t   = atomic<int_fast32_t>;
  using atomic_uint_fast32_t  = atomic<uint_fast32_t>;
  using atomic_int_fast64_t   = atomic<int_fast64_t>;
  using atomic_uint_fast64_t  = atomic<uint_fast64_t>;

  using atomic_intptr_t       = atomic<intptr_t>;
  using atomic_uintptr_t      = atomic<uintptr_t>;
  using atomic_size_t         = atomic<size_t>;
  using atomic_ptrdiff_t      = atomic<ptrdiff_t>;
  using atomic_intmax_t       = atomic<intmax_t>;
  using atomic_uintmax_t      = atomic<uintmax_t>;

  using atomic_signed_lock_free   = see below;                  // hosted
  using atomic_unsigned_lock_free = see below;                  // hosted

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
