/**
 *	@file	atomic_base_pointer.hpp
 *
 *	@brief	atomic_base_pointer の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_BASE_POINTER_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_BASE_POINTER_HPP

#include <hamon/cstddef/ptrdiff_t.hpp>

namespace hamon
{
namespace detail
{

// 32.5.8.5 Partial specialization for pointers[atomics.types.pointer]

template <typename T>
struct atomic_base_pointer
{
	using value_type = T*;
	using difference_type = hamon::ptrdiff_t;

	// [atomics.types.operations]/4
	static constexpr bool is_always_lock_free = hamon::detail::atomic_is_always_lock_free<T*>::value;

	bool is_lock_free() const volatile noexcept
	{
		// [atomics.types.operations]/5
		return hamon::detail::atomic_is_lock_free<T>();
	}

	bool is_lock_free() const noexcept
	{
		// [atomics.types.operations]/5
		return hamon::detail::atomic_is_lock_free<T>();
	}

	constexpr atomic_base_pointer() noexcept
		// [atomics.types.operations]/2
		: m_value()
	{}

	constexpr atomic_base_pointer(T* desired) noexcept
		// [atomics.types.operations]/3
		: m_value(desired)
	{}

	atomic_base_pointer(atomic_base_pointer const&) = delete;
	atomic_base_pointer& operator=(atomic_base_pointer const&) = delete;
	atomic_base_pointer& operator=(atomic_base_pointer const&) volatile = delete;

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/6
	void store(T* desired, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.operations]/7
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.operations]/8
		hamon::detail::atomic_store(data(), desired, order);
	}

	constexpr void store(T* desired, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.operations]/7
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.operations]/8
		hamon::detail::atomic_store(data(), desired, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/9
	T* operator=(T* desired) volatile noexcept
	{
		// [atomics.types.operations]/10
		store(desired);

		// [atomics.types.operations]/11
		return desired;
	}

	constexpr T* operator=(T* desired) noexcept
	{
		// [atomics.types.operations]/10
		store(desired);

		// [atomics.types.operations]/11
		return desired;
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/12
	T* load(memory_order order = memory_order::seq_cst) const volatile noexcept
	{
		// [atomics.types.operations]/13
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::acquire ||
			order == memory_order::seq_cst);

		// [atomics.types.operations]/14,15
		return hamon::detail::atomic_load(data(), order);
	}

	constexpr T* load(memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.types.operations]/13
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::acquire ||
			order == memory_order::seq_cst);

		// [atomics.types.operations]/14,15
		return hamon::detail::atomic_load(data(), order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/16
	operator T* () const volatile noexcept
	{
		// [atomics.types.operations]/17
		return load();
	}

	constexpr operator T* () const noexcept
	{
		// [atomics.types.operations]/17
		return load();
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/18
	T* exchange(T* desired, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.operations]/19,20
		return hamon::detail::atomic_exchange(data(), desired, order);
	}

	constexpr T* exchange(T* desired, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.operations]/19,20
		return hamon::detail::atomic_exchange(data(), desired, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/21
	bool compare_exchange_weak(T*& expected, T* desired, memory_order success, memory_order failure) volatile noexcept
	{
		// [atomics.types.operations]/22
		HAMON_ASSERT(
			failure == memory_order::relaxed ||
			failure == memory_order::acquire ||
			failure == memory_order::seq_cst);

		// [atomics.types.operations]/23,24
		return hamon::detail::atomic_compare_exchange_weak(
			data(), hamon::addressof(expected), desired, success, failure);
	}

	constexpr bool compare_exchange_weak(T*& expected, T* desired, memory_order success, memory_order failure) noexcept
	{
		// [atomics.types.operations]/22
		HAMON_ASSERT(
			failure == memory_order::relaxed ||
			failure == memory_order::acquire ||
			failure == memory_order::seq_cst);

		// [atomics.types.operations]/23,24
		return hamon::detail::atomic_compare_exchange_weak(
			data(), hamon::addressof(expected), desired, success, failure);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/21
	bool compare_exchange_strong(T*& expected, T* desired, memory_order success, memory_order failure) volatile noexcept
	{
		// [atomics.types.operations]/22
		HAMON_ASSERT(
			failure == memory_order::relaxed ||
			failure == memory_order::acquire ||
			failure == memory_order::seq_cst);

		// [atomics.types.operations]/23,24
		return hamon::detail::atomic_compare_exchange_strong(
			data(), hamon::addressof(expected), desired, success, failure);
	}

	constexpr bool compare_exchange_strong(T*& expected, T* desired, memory_order success, memory_order failure) noexcept
	{
		// [atomics.types.operations]/22
		HAMON_ASSERT(
			failure == memory_order::relaxed ||
			failure == memory_order::acquire ||
			failure == memory_order::seq_cst);

		// [atomics.types.operations]/23,24
		return hamon::detail::atomic_compare_exchange_strong(
			data(), hamon::addressof(expected), desired, success, failure);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/21
	bool compare_exchange_weak(T*& expected, T* desired, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.operations]/23,24
		auto success = order;
		auto failure =
			(order == memory_order::acq_rel) ? memory_order::acquire :
			(order == memory_order::release) ? memory_order::relaxed :
			order;
		return hamon::detail::atomic_compare_exchange_weak(
			data(), hamon::addressof(expected), desired, success, failure);
	}

	constexpr bool compare_exchange_weak(T*& expected, T* desired, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.operations]/23,24
		auto success = order;
		auto failure =
			(order == memory_order::acq_rel) ? memory_order::acquire :
			(order == memory_order::release) ? memory_order::relaxed :
			order;
		return hamon::detail::atomic_compare_exchange_weak(
			data(), hamon::addressof(expected), desired, success, failure);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/21
	bool compare_exchange_strong(T*& expected, T* desired, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.operations]/23,24
		auto success = order;
		auto failure =
			(order == memory_order::acq_rel) ? memory_order::acquire :
			(order == memory_order::release) ? memory_order::relaxed :
			order;
		return hamon::detail::atomic_compare_exchange_strong(
			data(), hamon::addressof(expected), desired, success, failure);
	}

	constexpr bool compare_exchange_strong(T*& expected, T* desired, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.operations]/23,24
		auto success = order;
		auto failure =
			(order == memory_order::acq_rel) ? memory_order::acquire :
			(order == memory_order::release) ? memory_order::relaxed :
			order;
		return hamon::detail::atomic_compare_exchange_strong(
			data(), hamon::addressof(expected), desired, success, failure);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.pointer]/5
	T* fetch_add(hamon::ptrdiff_t operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.pointer]/6
		static_assert(hamon::is_object_v<T>, "");

		// [atomics.types.pointer]/7,8
		return hamon::detail::atomic_fetch_add(data(), operand, order);
	}

	constexpr T* fetch_add(hamon::ptrdiff_t operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.pointer]/6
		static_assert(hamon::is_object_v<T>, "");

		// [atomics.types.pointer]/7,8
		return hamon::detail::atomic_fetch_add(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.pointer]/5
	T* fetch_sub(hamon::ptrdiff_t operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.pointer]/6
		static_assert(hamon::is_object_v<T>, "");
	}

	constexpr T* fetch_sub(hamon::ptrdiff_t operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.pointer]/6
		static_assert(hamon::is_object_v<T>, "");
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.pointer]/5
	T* fetch_max(T* operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.pointer]/6
		static_assert(hamon::is_object_v<T>, "");
	}

	constexpr T* fetch_max(T* operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.pointer]/6
		static_assert(hamon::is_object_v<T>, "");
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.pointer]/5
	T* fetch_min(T* operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.pointer]/6
		static_assert(hamon::is_object_v<T>, "");
	}

	constexpr T* fetch_min(T* operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.pointer]/6
		static_assert(hamon::is_object_v<T>, "");
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.pointer]/11
	void store_add(hamon::ptrdiff_t operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.pointer]/12
		static_assert(hamon::is_object_v<T>, "");
	}

	constexpr void store_add(hamon::ptrdiff_t operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.pointer]/12
		static_assert(hamon::is_object_v<T>, "");
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.pointer]/11
	void store_sub(hamon::ptrdiff_t operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.pointer]/12
		static_assert(hamon::is_object_v<T>, "");
	}

	constexpr void store_sub(hamon::ptrdiff_t operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.pointer]/12
		static_assert(hamon::is_object_v<T>, "");
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.pointer]/11
	void store_max(T* operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.pointer]/12
		static_assert(hamon::is_object_v<T>, "");
	}

	constexpr void store_max(T* operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.pointer]/12
		static_assert(hamon::is_object_v<T>, "");
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.pointer]/11
	void store_min(T* operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.pointer]/12
		static_assert(hamon::is_object_v<T>, "");
	}

	constexpr void store_min(T* operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.pointer]/12
		static_assert(hamon::is_object_v<T>, "");
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.memop]/1
	T* operator++(int) volatile noexcept
	{
		// [atomics.types.memop]/2
		return fetch_add(1);
	}

	constexpr T* operator++(int) noexcept
	{
		// [atomics.types.memop]/2
		return fetch_add(1);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.memop]/3
	T* operator--(int) volatile noexcept
	{
		// [atomics.types.memop]/4
		return fetch_sub(1);
	}

	constexpr T* operator--(int) noexcept
	{
		// [atomics.types.memop]/4
		return fetch_sub(1);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.memop]/5
	T* operator++() volatile noexcept
	{
		// [atomics.types.memop]/6
		return fetch_add(1) + 1;
	}

	constexpr T* operator++() noexcept
	{
		// [atomics.types.memop]/6
		return fetch_add(1) + 1;
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.memop]/7
	T* operator--() volatile noexcept
	{
		// [atomics.types.memop]/8
		return fetch_sub(1) - 1;
	}

	constexpr T* operator--() noexcept
	{
		// [atomics.types.memop]/8
		return fetch_sub(1) - 1;
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.pointer]/15
	T* operator+=(hamon::ptrdiff_t operand) volatile noexcept
	{
		// [atomics.types.pointer]/16
		return fetch_add(operand) + operand;
	}

	constexpr T* operator+=(hamon::ptrdiff_t operand) noexcept
	{
		// [atomics.types.pointer]/16
		return fetch_add(operand) + operand;
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.pointer]/15
	T* operator-=(hamon::ptrdiff_t operand) volatile noexcept
	{
		// [atomics.types.pointer]/16
		return fetch_sub(operand) - operand;
	}

	constexpr T* operator-=(hamon::ptrdiff_t operand) noexcept
	{
		// [atomics.types.pointer]/16
		return fetch_sub(operand) - operand;
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/29
	void wait(T*, memory_order = memory_order::seq_cst) const volatile noexcept;

	constexpr void wait(T*, memory_order = memory_order::seq_cst) const noexcept;

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/33
	void notify_one() volatile noexcept;

	constexpr void notify_one() noexcept;

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/36
	void notify_all() volatile noexcept;

	constexpr void notify_all() noexcept;

private:
	constexpr T** data() noexcept
	{
		return const_cast<T**>(hamon::addressof(m_value));
	}

	constexpr T** data() const noexcept
	{
		return const_cast<T**>(hamon::addressof(m_value));
	}

	constexpr T** data() volatile noexcept
	{
		return const_cast<T**>(hamon::addressof(m_value));
	}

	constexpr T** data() const volatile noexcept
	{
		return const_cast<T**>(hamon::addressof(m_value));
	}

	T* m_value;
};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_BASE_POINTER_HPP
