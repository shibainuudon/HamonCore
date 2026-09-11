/**
 *	@file	atomic_base_integral.hpp
 *
 *	@brief	atomic_base_integral の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_BASE_INTEGRAL_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_BASE_INTEGRAL_HPP

#include <hamon/atomic/detail/atomic_is_always_lock_free.hpp>
#include <hamon/atomic/detail/atomic_load.hpp>
#include <hamon/atomic/detail/atomic_store.hpp>
#include <hamon/memory/addressof.hpp>

namespace hamon
{
namespace detail
{

// 32.5.8.3 Specializations for integers[atomics.types.int]

template <typename T>
struct atomic_base_integral
{
	using value_type = T;
	using difference_type = value_type;

	static constexpr bool is_always_lock_free = hamon::detail::atomic_is_always_lock_free<T>::value;
	bool is_lock_free() const volatile noexcept;
	bool is_lock_free() const noexcept;

	constexpr atomic_base_integral() noexcept
		: m_value()
	{}

	constexpr atomic_base_integral(T desired) noexcept
		: m_value(desired)
	{}

	atomic_base_integral(const atomic_base_integral&) = delete;
	atomic_base_integral& operator=(const atomic_base_integral&) = delete;
	atomic_base_integral& operator=(const atomic_base_integral&) volatile = delete;

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/6
	void store(T desired, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.operations]/8
		hamon::detail::atomic_store((T*)hamon::addressof(m_value), desired, order);
	}

	constexpr void store(T desired, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.operations]/8
		hamon::detail::atomic_store(hamon::addressof(m_value), desired, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/9
	T operator=(T desired) volatile noexcept
	{
		// [atomics.types.operations]/10
		store(desired);

		// [atomics.types.operations]/11
		return desired;
	}

	constexpr T operator=(T desired) noexcept
	{
		// [atomics.types.operations]/10
		store(desired);

		// [atomics.types.operations]/11
		return desired;
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/12
	T load(memory_order order = memory_order::seq_cst) const volatile noexcept
	{
		// [atomics.types.operations]/14,15
		return hamon::detail::atomic_load(hamon::addressof(m_value), order);
	}

	constexpr T load(memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.types.operations]/14,15
		return hamon::detail::atomic_load(hamon::addressof(m_value), order);
	}

	operator T() const volatile noexcept;
	constexpr operator T() const noexcept;

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
	T fetch_and(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr T fetch_and(T, memory_order = memory_order::seq_cst) noexcept;
	T fetch_or(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr T fetch_or(T, memory_order = memory_order::seq_cst) noexcept;
	T fetch_xor(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr T fetch_xor(T, memory_order = memory_order::seq_cst) noexcept;
	T fetch_max(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr T fetch_max(T, memory_order = memory_order::seq_cst) noexcept;
	T fetch_min(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr T fetch_min(T, memory_order = memory_order::seq_cst) noexcept;

	void store_add(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr void store_add(T, memory_order = memory_order::seq_cst) noexcept;
	void store_sub(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr void store_sub(T, memory_order = memory_order::seq_cst) noexcept;
	void store_and(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr void store_and(T, memory_order = memory_order::seq_cst) noexcept;
	void store_or(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr void store_or(T, memory_order = memory_order::seq_cst) noexcept;
	void store_xor(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr void store_xor(T, memory_order = memory_order::seq_cst) noexcept;
	void store_max(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr void store_max(T, memory_order = memory_order::seq_cst) noexcept;
	void store_min(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr void store_min(T, memory_order = memory_order::seq_cst) noexcept;

	T operator++(int) volatile noexcept;
	constexpr T operator++(int) noexcept;
	T operator--(int) volatile noexcept;
	constexpr T operator--(int) noexcept;
	T operator++() volatile noexcept;
	constexpr T operator++() noexcept;
	T operator--() volatile noexcept;
	constexpr T operator--() noexcept;
	T operator+=(T) volatile noexcept;
	constexpr T operator+=(T) noexcept;
	T operator-=(T) volatile noexcept;
	constexpr T operator-=(T) noexcept;
	T operator&=(T) volatile noexcept;
	constexpr T operator&=(T) noexcept;
	T operator|=(T) volatile noexcept;
	constexpr T operator|=(T) noexcept;
	T operator^=(T) volatile noexcept;
	constexpr T operator^=(T) noexcept;

	void wait(T, memory_order = memory_order::seq_cst) const volatile noexcept;
	constexpr void wait(T, memory_order = memory_order::seq_cst) const noexcept;
	void notify_one() volatile noexcept;
	constexpr void notify_one() noexcept;
	void notify_all() volatile noexcept;
	constexpr void notify_all() noexcept;

private:
	T m_value;
};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_BASE_INTEGRAL_HPP
