/**
 *	@file	atomic_base_general.hpp
 *
 *	@brief	atomic_base_general の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_BASE_GENERAL_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_BASE_GENERAL_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/atomic_compare_exchange_strong.hpp>
#include <hamon/atomic/detail/atomic_compare_exchange_weak.hpp>
#include <hamon/atomic/detail/atomic_exchange.hpp>
#include <hamon/atomic/detail/atomic_is_always_lock_free.hpp>
#include <hamon/atomic/detail/atomic_is_lock_free.hpp>
#include <hamon/atomic/detail/atomic_load.hpp>
#include <hamon/atomic/detail/atomic_store.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_default_constructible.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_trivially_copyable.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/assert.hpp>

namespace hamon
{
namespace detail
{

// 32.5.8.1 General[atomics.types.generic.general]

template <typename T>
struct atomic_base_general
{
	static_assert(hamon::is_trivially_copyable_v<T>, "");	// [atomics.types.generic.general]1.1
	static_assert(hamon::is_copy_constructible_v<T>, "");	// [atomics.types.generic.general]1.2
	static_assert(hamon::is_move_constructible_v<T>, "");	// [atomics.types.generic.general]1.3
	static_assert(hamon::is_copy_assignable_v<T>, "");		// [atomics.types.generic.general]1.4
	static_assert(hamon::is_move_assignable_v<T>, "");		// [atomics.types.generic.general]1.5
	static_assert(hamon::is_same_v<T, hamon::remove_cv_t<T>>, "");	// [atomics.types.generic.general]1.6

	using value_type = T;

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

	// [atomics.types.operations], operations on atomic types
	template <typename U = T,
		typename = hamon::enable_if_t<hamon::is_default_constructible_v<U>>>	// [atomics.types.operations]/1
	constexpr atomic_base_general()
		noexcept(hamon::is_nothrow_default_constructible_v<T>)
		// [atomics.types.operations]/2
		: m_value()
	{}

	constexpr atomic_base_general(T desired) noexcept
		// [atomics.types.operations]/3
		: m_value(desired)
	{}

	atomic_base_general(atomic_base_general const&) = delete;
	atomic_base_general& operator=(atomic_base_general const&) = delete;
	atomic_base_general& operator=(atomic_base_general const&) volatile = delete;

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

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/29
	void wait(T, memory_order = memory_order::seq_cst) const volatile noexcept;

	constexpr void wait(T, memory_order = memory_order::seq_cst) const noexcept;

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/29
	void notify_one() volatile noexcept;

	constexpr void notify_one() noexcept;

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.operations]/29
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

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_BASE_GENERAL_HPP
