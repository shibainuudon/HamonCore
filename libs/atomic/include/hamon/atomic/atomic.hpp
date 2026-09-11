/**
 *	@file	atomic.hpp
 *
 *	@brief	atomic の定義
 */

#ifndef HAMON_ATOMIC_ATOMIC_HPP
#define HAMON_ATOMIC_ATOMIC_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/atomic_base.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 32.5.8 Class template atomic[atomics.types.generic]

template <typename T>
struct atomic : public hamon::detail::atomic_base<T>
{
private:
	using base = hamon::detail::atomic_base<T>;

public:
	using base::base;
};

// 32.5.8.5 Partial specialization for pointers[atomics.types.pointer]

template <typename T>
struct atomic<T*>
{
	using value_type = T*;
	using difference_type = hamon::ptrdiff_t;

	static constexpr bool is_always_lock_free = hamon::detail::atomic_is_always_lock_free<T*>::value;
	bool is_lock_free() const volatile noexcept;
	bool is_lock_free() const noexcept;

	constexpr atomic() noexcept;
	constexpr atomic(T*) noexcept;
	atomic(const atomic&) = delete;
	atomic& operator=(const atomic&) = delete;
	atomic& operator=(const atomic&) volatile = delete;

	void store(T*, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr void store(T*, memory_order = memory_order::seq_cst) noexcept;
	T* operator=(T*) volatile noexcept;
	constexpr T* operator=(T*) noexcept;
	T* load(memory_order = memory_order::seq_cst) const volatile noexcept;
	constexpr T* load(memory_order = memory_order::seq_cst) const noexcept;
	operator T* () const volatile noexcept;
	constexpr operator T* () const noexcept;

	T* exchange(T*, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr T* exchange(T*, memory_order = memory_order::seq_cst) noexcept;
	bool compare_exchange_weak(T*&, T*, memory_order, memory_order) volatile noexcept;
	constexpr bool compare_exchange_weak(T*&, T*, memory_order, memory_order) noexcept;
	bool compare_exchange_strong(T*&, T*, memory_order, memory_order) volatile noexcept;
	constexpr bool compare_exchange_strong(T*&, T*, memory_order, memory_order) noexcept;
	bool compare_exchange_weak(T*&, T*, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr bool compare_exchange_weak(T*&, T*, memory_order = memory_order::seq_cst) noexcept;
	bool compare_exchange_strong(T*&, T*, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr bool compare_exchange_strong(T*&, T*, memory_order = memory_order::seq_cst) noexcept;

	T* fetch_add(ptrdiff_t, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr T* fetch_add(ptrdiff_t, memory_order = memory_order::seq_cst) noexcept;
	T* fetch_sub(ptrdiff_t, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr T* fetch_sub(ptrdiff_t, memory_order = memory_order::seq_cst) noexcept;
	T* fetch_max(T*, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr T* fetch_max(T*, memory_order = memory_order::seq_cst) noexcept;
	T* fetch_min(T*, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr T* fetch_min(T*, memory_order = memory_order::seq_cst) noexcept;

	void store_add(ptrdiff_t, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr void store_add(ptrdiff_t, memory_order = memory_order::seq_cst) noexcept;
	void store_sub(ptrdiff_t, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr void store_sub(ptrdiff_t, memory_order = memory_order::seq_cst) noexcept;
	void store_max(T*, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr void store_max(T*, memory_order = memory_order::seq_cst) noexcept;
	void store_min(T*, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr void store_min(T*, memory_order = memory_order::seq_cst) noexcept;

	T* operator++(int) volatile noexcept;
	constexpr T* operator++(int) noexcept;
	T* operator--(int) volatile noexcept;
	constexpr T* operator--(int) noexcept;
	T* operator++() volatile noexcept;
	constexpr T* operator++() noexcept;
	T* operator--() volatile noexcept;
	constexpr T* operator--() noexcept;
	T* operator+=(ptrdiff_t) volatile noexcept;
	constexpr T* operator+=(ptrdiff_t) noexcept;
	T* operator-=(ptrdiff_t) volatile noexcept;
	constexpr T* operator-=(ptrdiff_t) noexcept;

	void wait(T*, memory_order = memory_order::seq_cst) const volatile noexcept;
	constexpr void wait(T*, memory_order = memory_order::seq_cst) const noexcept;
	void notify_one() volatile noexcept;
	constexpr void notify_one() noexcept;
	void notify_all() volatile noexcept;
	constexpr void notify_all() noexcept;
};

}	// namespace hamon

#endif // HAMON_ATOMIC_ATOMIC_HPP
