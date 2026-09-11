/**
 *	@file	atomic_base_floating_point.hpp
 *
 *	@brief	atomic_base_floating_point の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_BASE_FLOATING_POINT_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_BASE_FLOATING_POINT_HPP

#include <hamon/atomic/detail/atomic_is_always_lock_free.hpp>

namespace hamon
{
namespace detail
{

// 32.5.8.4 Specializations for floating-point types[atomics.types.float]

template <typename T>
struct atomic_base_floating_point
{
	using value_type = T;
	using difference_type = value_type;

	static constexpr bool is_always_lock_free = hamon::detail::atomic_is_always_lock_free<T>::value;
	bool is_lock_free() const volatile noexcept;
	bool is_lock_free() const noexcept;

	constexpr atomic_base_floating_point() noexcept;
	constexpr atomic_base_floating_point(T) noexcept;
	atomic_base_floating_point(const atomic_base_floating_point&) = delete;
	atomic_base_floating_point& operator=(const atomic_base_floating_point&) = delete;
	atomic_base_floating_point& operator=(const atomic_base_floating_point&) volatile = delete;

	void store(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr void store(T, memory_order = memory_order::seq_cst) noexcept;
	T operator=(T) volatile noexcept;
	constexpr T operator=(T) noexcept;
	T load(memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr T load(memory_order = memory_order::seq_cst) noexcept;
	operator T() volatile noexcept;
	constexpr operator T() noexcept;

	T exchange(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr T exchange(T, memory_order = memory_order::seq_cst) noexcept;
	bool compare_exchange_weak(T&, T, memory_order, memory_order) volatile noexcept;
	constexpr bool compare_exchange_weak(T&, T, memory_order, memory_order) noexcept;
	bool compare_exchange_strong(T&, T, memory_order, memory_order) volatile noexcept;
	constexpr bool compare_exchange_strong(T&, T, memory_order, memory_order) noexcept;
	bool compare_exchange_weak(T&, T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr bool compare_exchange_weak(T&, T, memory_order = memory_order::seq_cst) noexcept;
	bool compare_exchange_strong(T&, T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr bool compare_exchange_strong(T&, T, memory_order = memory_order::seq_cst) noexcept;

	T fetch_add(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr T fetch_add(T, memory_order = memory_order::seq_cst) noexcept;
	T fetch_sub(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr T fetch_sub(T, memory_order = memory_order::seq_cst) noexcept;
	T fetch_max(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr T fetch_max(T, memory_order = memory_order::seq_cst) noexcept;
	T fetch_min(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr T fetch_min(T, memory_order = memory_order::seq_cst) noexcept;
	T fetch_fmaximum(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr T fetch_fmaximum(T, memory_order = memory_order::seq_cst) noexcept;
	T fetch_fminimum(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr T fetch_fminimum(T, memory_order = memory_order::seq_cst) noexcept;
	T fetch_fmaximum_num(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr T fetch_fmaximum_num(T, memory_order = memory_order::seq_cst) noexcept;
	T fetch_fminimum_num(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr T fetch_fminimum_num(T, memory_order = memory_order::seq_cst) noexcept;

	void store_add(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr void store_add(T, memory_order = memory_order::seq_cst) noexcept;
	void store_sub(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr void store_sub(T, memory_order = memory_order::seq_cst) noexcept;
	void store_max(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr void store_max(T, memory_order = memory_order::seq_cst) noexcept;
	void store_min(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr void store_min(T, memory_order = memory_order::seq_cst) noexcept;
	void store_fmaximum(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr void store_fmaximum(T, memory_order = memory_order::seq_cst) noexcept;
	void store_fminimum(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr void store_fminimum(T, memory_order = memory_order::seq_cst) noexcept;
	void store_fmaximum_num(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr void store_fmaximum_num(T, memory_order = memory_order::seq_cst) noexcept;
	void store_fminimum_num(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr void store_fminimum_num(T, memory_order = memory_order::seq_cst) noexcept;

	T operator+=(T) volatile noexcept;
	constexpr T operator+=(T) noexcept;
	T operator-=(T) volatile noexcept;
	constexpr T operator-=(T) noexcept;

	void wait(T, memory_order = memory_order::seq_cst) const volatile noexcept;
	constexpr void wait(T, memory_order = memory_order::seq_cst) const noexcept;
	void notify_one() volatile noexcept;
	constexpr void notify_one() noexcept;
	void notify_all() volatile noexcept;
	constexpr void notify_all() noexcept;
};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_BASE_FLOATING_POINT_HPP
