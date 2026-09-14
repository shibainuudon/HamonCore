/**
 *	@file	atomic_base_floating_point.hpp
 *
 *	@brief	atomic_base_floating_point の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_BASE_FLOATING_POINT_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_BASE_FLOATING_POINT_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/atomic_compare_exchange_strong.hpp>
#include <hamon/atomic/detail/atomic_compare_exchange_weak.hpp>
#include <hamon/atomic/detail/atomic_exchange.hpp>
#include <hamon/atomic/detail/atomic_fetch_add.hpp>
#include <hamon/atomic/detail/atomic_fetch_fmaximum.hpp>
#include <hamon/atomic/detail/atomic_fetch_fmaximum_num.hpp>
#include <hamon/atomic/detail/atomic_fetch_fminimum.hpp>
#include <hamon/atomic/detail/atomic_fetch_fminimum_num.hpp>
#include <hamon/atomic/detail/atomic_fetch_sub.hpp>
#include <hamon/atomic/detail/atomic_load.hpp>
#include <hamon/atomic/detail/atomic_store.hpp>
#include <hamon/atomic/detail/atomic_store_add.hpp>
#include <hamon/atomic/detail/atomic_store_fmaximum.hpp>
#include <hamon/atomic/detail/atomic_store_fmaximum_num.hpp>
#include <hamon/atomic/detail/atomic_store_fminimum.hpp>
#include <hamon/atomic/detail/atomic_store_fminimum_num.hpp>
#include <hamon/atomic/detail/atomic_store_max.hpp>
#include <hamon/atomic/detail/atomic_store_min.hpp>
#include <hamon/atomic/detail/atomic_store_sub.hpp>
#include <hamon/atomic/detail/atomic_is_always_lock_free.hpp>
#include <hamon/atomic/detail/atomic_is_lock_free.hpp>
#include <hamon/atomic/detail/clear_padding_if_needed.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/assert.hpp>

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

	// [atomics.types.operations]/4
	static constexpr bool is_always_lock_free = hamon::detail::atomic_is_always_lock_free<T>::value;

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

	constexpr atomic_base_floating_point() noexcept
		// [atomics.types.operations]/2
		: m_value()
	{}

	constexpr atomic_base_floating_point(T desired) noexcept
		// [atomics.types.operations]/3
		: m_value(desired)
	{
		hamon::detail::clear_padding_if_needed(m_value);
	}

	atomic_base_floating_point(atomic_base_floating_point const&) = delete;
	atomic_base_floating_point& operator=(atomic_base_floating_point const&) = delete;
	atomic_base_floating_point& operator=(atomic_base_floating_point const&) volatile = delete;

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/6
	void store(T desired, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.operations]/7
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		hamon::detail::clear_padding_if_needed(desired);

		// [atomics.types.operations]/8
		hamon::detail::atomic_store(data(), desired, order);
	}

	constexpr void store(T desired, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.operations]/7
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		hamon::detail::clear_padding_if_needed(desired);

		// [atomics.types.operations]/8
		hamon::detail::atomic_store(data(), desired, order);
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
		// [atomics.types.operations]/13
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::acquire ||
			order == memory_order::seq_cst);

		// [atomics.types.operations]/14,15
		return hamon::detail::atomic_load(data(), order);
	}

	constexpr T load(memory_order order = memory_order::seq_cst) const noexcept
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
	operator T() const volatile noexcept
	{
		// [atomics.types.operations]/17
		return load();
	}

	constexpr operator T() const noexcept
	{
		// [atomics.types.operations]/17
		return load();
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/18
	T exchange(T desired, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		hamon::detail::clear_padding_if_needed(desired);

		// [atomics.types.operations]/19,20
		return hamon::detail::atomic_exchange(data(), desired, order);
	}

	constexpr T exchange(T desired, memory_order order = memory_order::seq_cst) noexcept
	{
		hamon::detail::clear_padding_if_needed(desired);

		// [atomics.types.operations]/19,20
		return hamon::detail::atomic_exchange(data(), desired, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/21
	bool compare_exchange_weak(T& expected, T desired, memory_order success, memory_order failure) volatile noexcept
	{
		// [atomics.types.operations]/22
		HAMON_ASSERT(
			failure == memory_order::relaxed ||
			failure == memory_order::acquire ||
			failure == memory_order::seq_cst);

		hamon::detail::clear_padding_if_needed(expected);
		hamon::detail::clear_padding_if_needed(desired);

		// [atomics.types.operations]/23,24
		return hamon::detail::atomic_compare_exchange_weak(
			data(), hamon::addressof(expected), desired, success, failure);
	}

	constexpr bool compare_exchange_weak(T& expected, T desired, memory_order success, memory_order failure) noexcept
	{
		// [atomics.types.operations]/22
		HAMON_ASSERT(
			failure == memory_order::relaxed ||
			failure == memory_order::acquire ||
			failure == memory_order::seq_cst);

		hamon::detail::clear_padding_if_needed(expected);
		hamon::detail::clear_padding_if_needed(desired);

		// [atomics.types.operations]/23,24
		return hamon::detail::atomic_compare_exchange_weak(
			data(), hamon::addressof(expected), desired, success, failure);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/21
	bool compare_exchange_strong(T& expected, T desired, memory_order success, memory_order failure) volatile noexcept
	{
		// [atomics.types.operations]/22
		HAMON_ASSERT(
			failure == memory_order::relaxed ||
			failure == memory_order::acquire ||
			failure == memory_order::seq_cst);

		hamon::detail::clear_padding_if_needed(expected);
		hamon::detail::clear_padding_if_needed(desired);

		// [atomics.types.operations]/23,24
		return hamon::detail::atomic_compare_exchange_strong(
			data(), hamon::addressof(expected), desired, success, failure);
	}

	constexpr bool compare_exchange_strong(T& expected, T desired, memory_order success, memory_order failure) noexcept
	{
		// [atomics.types.operations]/22
		HAMON_ASSERT(
			failure == memory_order::relaxed ||
			failure == memory_order::acquire ||
			failure == memory_order::seq_cst);

		hamon::detail::clear_padding_if_needed(expected);
		hamon::detail::clear_padding_if_needed(desired);

		// [atomics.types.operations]/23,24
		return hamon::detail::atomic_compare_exchange_strong(
			data(), hamon::addressof(expected), desired, success, failure);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/21
	bool compare_exchange_weak(T& expected, T desired, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.operations]/23,24
		auto success = order;
		auto failure =
			(order == memory_order::acq_rel) ? memory_order::acquire :
			(order == memory_order::release) ? memory_order::relaxed :
			order;
		return compare_exchange_weak(expected, desired, success, failure);
	}

	constexpr bool compare_exchange_weak(T& expected, T desired, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.operations]/23,24
		auto success = order;
		auto failure =
			(order == memory_order::acq_rel) ? memory_order::acquire :
			(order == memory_order::release) ? memory_order::relaxed :
			order;
		return compare_exchange_weak(expected, desired, success, failure);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/21
	bool compare_exchange_strong(T& expected, T desired, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.operations]/23,24
		auto success = order;
		auto failure =
			(order == memory_order::acq_rel) ? memory_order::acquire :
			(order == memory_order::release) ? memory_order::relaxed :
			order;
		return compare_exchange_strong(expected, desired, success, failure);
	}

	constexpr bool compare_exchange_strong(T& expected, T desired, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.operations]/23,24
		auto success = order;
		auto failure =
			(order == memory_order::acq_rel) ? memory_order::acquire :
			(order == memory_order::release) ? memory_order::relaxed :
			order;
		return compare_exchange_strong(expected, desired, success, failure);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/5
	T fetch_add(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/6
		return hamon::detail::atomic_fetch_add(data(), operand, order);
	}

	constexpr T fetch_add(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/6
		return hamon::detail::atomic_fetch_add(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/5
	T fetch_sub(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/6
		return hamon::detail::atomic_fetch_sub(data(), operand, order);
	}

	constexpr T fetch_sub(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/6
		return hamon::detail::atomic_fetch_sub(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/5
	T fetch_max(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/6,9.3,10
		return hamon::detail::atomic_fetch_fmaximum_num(data(), operand, order);
	}

	constexpr T fetch_max(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/6,9.3,10
		return hamon::detail::atomic_fetch_fmaximum_num(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/5
	T fetch_min(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/6,9.3,10
		return hamon::detail::atomic_fetch_fminimum_num(data(), operand, order);
	}

	constexpr T fetch_min(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/6,9.3,10
		return hamon::detail::atomic_fetch_fminimum_num(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/5
	T fetch_fmaximum(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/6,9.1
		return hamon::detail::atomic_fetch_fmaximum(data(), operand, order);
	}

	constexpr T fetch_fmaximum(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/6,9.1
		return hamon::detail::atomic_fetch_fmaximum(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/5
	T fetch_fminimum(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/6,9.1
		return hamon::detail::atomic_fetch_fminimum(data(), operand, order);
	}

	constexpr T fetch_fminimum(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/6,9.1
		return hamon::detail::atomic_fetch_fminimum(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/5
	T fetch_fmaximum_num(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/6,9.2
		return hamon::detail::atomic_fetch_fmaximum_num(data(), operand, order);
	}

	constexpr T fetch_fmaximum_num(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/6,9.2
		return hamon::detail::atomic_fetch_fmaximum_num(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/5
	T fetch_fminimum_num(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/6,9.2
		return hamon::detail::atomic_fetch_fminimum_num(data(), operand, order);
	}

	constexpr T fetch_fminimum_num(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/6,9.2
		return hamon::detail::atomic_fetch_fminimum_num(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/11
	void store_add(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13
		hamon::detail::atomic_store_add(data(), operand, order);
	}

	constexpr void store_add(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13
		hamon::detail::atomic_store_add(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/11
	void store_sub(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13
		hamon::detail::atomic_store_sub(data(), operand, order);
	}

	constexpr void store_sub(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13
		hamon::detail::atomic_store_sub(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/11
	void store_max(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13,15.3/16
		hamon::detail::atomic_store_max(data(), operand, order);
	}

	constexpr void store_max(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13,15.3/16
		hamon::detail::atomic_store_max(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/11
	void store_min(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13,15.3/16
		hamon::detail::atomic_store_min(data(), operand, order);
	}

	constexpr void store_min(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13,15.3/16
		hamon::detail::atomic_store_min(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/11
	void store_fmaximum(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13,15.1
		hamon::detail::atomic_store_fmaximum(data(), operand, order);
	}

	constexpr void store_fmaximum(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13,15.1
		hamon::detail::atomic_store_fmaximum(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/11
	void store_fminimum(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13,15.1
		hamon::detail::atomic_store_fminimum(data(), operand, order);
	}

	constexpr void store_fminimum(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13,15.1
		hamon::detail::atomic_store_fminimum(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/11
	void store_fmaximum_num(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13,15.2
		hamon::detail::atomic_store_fmaximum_num(data(), operand, order);
	}

	constexpr void store_fmaximum_num(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13,15.2
		hamon::detail::atomic_store_fmaximum_num(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/11
	void store_fminimum_num(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13,15.2
		hamon::detail::atomic_store_fminimum_num(data(), operand, order);
	}

	constexpr void store_fminimum_num(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13,15.2
		hamon::detail::atomic_store_fminimum_num(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/17
	T operator+=(T operand) volatile noexcept
	{
		// [atomics.types.float]/18
		return fetch_add(operand) + operand;
	}

	constexpr T operator+=(T operand) noexcept
	{
		// [atomics.types.float]/18
		return fetch_add(operand) + operand;
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/17
	T operator-=(T operand) volatile noexcept
	{
		// [atomics.types.float]/18
		return fetch_sub(operand) - operand;
	}

	constexpr T operator-=(T operand) noexcept
	{
		// [atomics.types.float]/18
		return fetch_sub(operand) - operand;
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/29
	void wait(T, memory_order = memory_order::seq_cst) const volatile noexcept;

	constexpr void wait(T, memory_order = memory_order::seq_cst) const noexcept;

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/33
	void notify_one() volatile noexcept;

	constexpr void notify_one() noexcept;

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/36
	void notify_all() volatile noexcept;

	constexpr void notify_all() noexcept;

private:
	constexpr T* data() noexcept
	{
		return const_cast<T*>(hamon::addressof(m_value));
	}

	constexpr T* data() const noexcept
	{
		return const_cast<T*>(hamon::addressof(m_value));
	}

	constexpr T* data() volatile noexcept
	{
		return const_cast<T*>(hamon::addressof(m_value));
	}

	constexpr T* data() const volatile noexcept
	{
		return const_cast<T*>(hamon::addressof(m_value));
	}

	T m_value;
};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_BASE_FLOATING_POINT_HPP
