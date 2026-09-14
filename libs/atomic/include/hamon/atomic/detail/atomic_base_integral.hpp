/**
 *	@file	atomic_base_integral.hpp
 *
 *	@brief	atomic_base_integral の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_BASE_INTEGRAL_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_BASE_INTEGRAL_HPP

#include <hamon/atomic/detail/atomic_is_always_lock_free.hpp>
#include <hamon/atomic/detail/atomic_is_lock_free.hpp>
#include <hamon/atomic/detail/atomic_load.hpp>
#include <hamon/atomic/detail/atomic_store.hpp>
#include <hamon/atomic/detail/atomic_exchange.hpp>
#include <hamon/atomic/detail/atomic_compare_exchange_weak.hpp>
#include <hamon/atomic/detail/atomic_compare_exchange_strong.hpp>
#include <hamon/atomic/detail/atomic_fetch_add.hpp>
#include <hamon/atomic/detail/atomic_fetch_sub.hpp>
#include <hamon/atomic/detail/atomic_fetch_and.hpp>
#include <hamon/atomic/detail/atomic_fetch_or.hpp>
#include <hamon/atomic/detail/atomic_fetch_xor.hpp>
#include <hamon/atomic/detail/atomic_fetch_max.hpp>
#include <hamon/atomic/detail/atomic_fetch_min.hpp>
#include <hamon/atomic/detail/atomic_store_add.hpp>
#include <hamon/atomic/detail/atomic_store_sub.hpp>
#include <hamon/atomic/detail/atomic_store_and.hpp>
#include <hamon/atomic/detail/atomic_store_or.hpp>
#include <hamon/atomic/detail/atomic_store_xor.hpp>
#include <hamon/atomic/detail/atomic_store_max.hpp>
#include <hamon/atomic/detail/atomic_store_min.hpp>
#include <hamon/atomic/detail/atomic_wait.hpp>
#include <hamon/atomic/detail/atomic_notify_one.hpp>
#include <hamon/atomic/detail/atomic_notify_all.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/assert.hpp>

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

	constexpr atomic_base_integral() noexcept
		// [atomics.types.operations]/2
		: m_value()
	{}

	constexpr atomic_base_integral(T desired) noexcept
		// [atomics.types.operations]/3
		: m_value(desired)
	{}

	atomic_base_integral(atomic_base_integral const&) = delete;
	atomic_base_integral& operator=(atomic_base_integral const&) = delete;
	atomic_base_integral& operator=(atomic_base_integral const&) volatile = delete;

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/6
	void store(T desired, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.operations]/7
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

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
		// [atomics.types.operations]/19,20
		return hamon::detail::atomic_exchange(data(), desired, order);
	}

	constexpr T exchange(T desired, memory_order order = memory_order::seq_cst) noexcept
	{
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
		return hamon::detail::atomic_compare_exchange_weak(
			data(), hamon::addressof(expected), desired, success, failure);
	}

	constexpr bool compare_exchange_weak(T& expected, T desired, memory_order order = memory_order::seq_cst) noexcept
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
	bool compare_exchange_strong(T& expected, T desired, memory_order order = memory_order::seq_cst) volatile noexcept
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

	constexpr bool compare_exchange_strong(T& expected, T desired, memory_order order = memory_order::seq_cst) noexcept
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

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/5
	T fetch_add(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_add(data(), operand, order);
	}

	constexpr T fetch_add(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_add(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/5
	T fetch_sub(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_sub(data(), operand, order);
	}

	constexpr T fetch_sub(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_sub(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/5
	T fetch_and(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_and(data(), operand, order);
	}

	constexpr T fetch_and(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_and(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/5
	T fetch_or(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_or(data(), operand, order);
	}

	constexpr T fetch_or(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_or(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/5
	T fetch_xor(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_xor(data(), operand, order);
	}

	constexpr T fetch_xor(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_xor(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/5
	T fetch_max(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_max(data(), operand, order);
	}

	constexpr T fetch_max(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_max(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/5
	T fetch_min(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_min(data(), operand, order);
	}

	constexpr T fetch_min(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_min(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/10
	void store_add(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_add(data(), operand, order);
	}

	constexpr void store_add(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_add(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/10
	void store_sub(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_sub(data(), operand, order);
	}

	constexpr void store_sub(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_sub(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/10
	void store_and(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_and(data(), operand, order);
	}

	constexpr void store_and(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_and(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/10
	void store_or(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_or(data(), operand, order);
	}

	constexpr void store_or(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_or(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/10
	void store_xor(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_xor(data(), operand, order);
	}

	constexpr void store_xor(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_xor(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/10
	void store_max(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_max(data(), operand, order);
	}

	constexpr void store_max(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_max(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/10
	void store_min(T operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_min(data(), operand, order);
	}

	constexpr void store_min(T operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_min(data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.memop]/1
	T operator++(int) volatile noexcept
	{
		// [atomics.types.memop]/2
		return fetch_add(T(1));
	}

	constexpr T operator++(int) noexcept
	{
		// [atomics.types.memop]/2
		return fetch_add(T(1));
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.memop]/3
	T operator--(int) volatile noexcept
	{
		// [atomics.types.memop]/4
		return fetch_sub(T(1));
	}

	constexpr T operator--(int) noexcept
	{
		// [atomics.types.memop]/4
		return fetch_sub(T(1));
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.memop]/5
	T operator++() volatile noexcept
	{
		// [atomics.types.memop]/6
		return fetch_add(T(1)) + T(1);
	}

	constexpr T operator++() noexcept
	{
		// [atomics.types.memop]/6
		return fetch_add(T(1)) + T(1);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.memop]/7
	T operator--() volatile noexcept
	{
		// [atomics.types.memop]/8
		return fetch_sub(T(1)) - T(1);
	}

	constexpr T operator--() noexcept
	{
		// [atomics.types.memop]/8
		return fetch_sub(T(1)) - T(1);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/14
	T operator+=(T operand) volatile noexcept
	{
		// [atomics.types.int]/15
		return fetch_add(operand) + operand;
	}

	constexpr T operator+=(T operand) noexcept
	{
		// [atomics.types.int]/15
		return fetch_add(operand) + operand;
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/14
	T operator-=(T operand) volatile noexcept
	{
		// [atomics.types.int]/15
		return fetch_sub(operand) - operand;
	}

	constexpr T operator-=(T operand) noexcept
	{
		// [atomics.types.int]/15
		return fetch_sub(operand) - operand;
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/14
	T operator&=(T operand) volatile noexcept
	{
		// [atomics.types.int]/15
		return fetch_and(operand) & operand;
	}

	constexpr T operator&=(T operand) noexcept
	{
		// [atomics.types.int]/15
		return fetch_and(operand) & operand;
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/14
	T operator|=(T operand) volatile noexcept
	{
		// [atomics.types.int]/15
		return fetch_or(operand) | operand;
	}

	constexpr T operator|=(T operand) noexcept
	{
		// [atomics.types.int]/15
		return fetch_or(operand) | operand;
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/14
	T operator^=(T operand) volatile noexcept
	{
		// [atomics.types.int]/15
		return fetch_xor(operand) ^ operand;
	}

	constexpr T operator^=(T operand) noexcept
	{
		// [atomics.types.int]/15
		return fetch_xor(operand) ^ operand;
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/29
	void wait(T old, memory_order order = memory_order::seq_cst) const volatile noexcept;/*
	{
		// [atomics.types.operations]/30
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::acquire ||
			order == memory_order::seq_cst);

		// [atomics.types.operations]/31
		hamon::detail::atomic_wait(data(), old, order);
	}*/

	constexpr void wait(T old, memory_order order = memory_order::seq_cst) const noexcept;/*
	{
		// [atomics.types.operations]/30
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::acquire ||
			order == memory_order::seq_cst);

		// [atomics.types.operations]/31
		hamon::detail::atomic_wait(data(), old, order);
	}*/

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/33
	void notify_one() volatile noexcept;/*
	{
		// [atomics.types.operations]/34
		hamon::detail::atomic_notify_one(data());
	}*/

	constexpr void notify_one() noexcept;/*
	{
		// [atomics.types.operations]/34
		hamon::detail::atomic_notify_one(data());
	}*/

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/36
	void notify_all() volatile noexcept;/*
	{
		// [atomics.types.operations]/37
		hamon::detail::atomic_notify_all(data());
	}*/

	constexpr void notify_all() noexcept;/*
	{
		// [atomics.types.operations]/37
		hamon::detail::atomic_notify_all(data());
	}*/

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

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_BASE_INTEGRAL_HPP
