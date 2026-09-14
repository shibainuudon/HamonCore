/**
 *	@file	atomic_base_general.hpp
 *
 *	@brief	atomic_base_general の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_BASE_GENERAL_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_BASE_GENERAL_HPP

#include <hamon/atomic/detail/atomic_is_always_lock_free.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <hamon/type_traits/is_copy_constructible.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_trivially_copyable.hpp>
#include <hamon/type_traits/remove_cv.hpp>

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

	static constexpr bool is_always_lock_free = hamon::detail::atomic_is_always_lock_free<T>::value;
	bool is_lock_free() const volatile noexcept;
	bool is_lock_free() const noexcept;

	// [atomics.types.operations], operations on atomic types
	constexpr atomic_base_general() noexcept(is_nothrow_default_constructible_v<T>);
	constexpr atomic_base_general(T) noexcept;
	atomic_base_general(atomic_base_general const&) = delete;
	atomic_base_general& operator=(atomic_base_general const&) = delete;
	atomic_base_general& operator=(atomic_base_general const&) volatile = delete;

	T load(memory_order = memory_order::seq_cst) const volatile noexcept;
	constexpr T load(memory_order = memory_order::seq_cst) const noexcept;
	operator T() const volatile noexcept;
	constexpr operator T() const noexcept;
	void store(T, memory_order = memory_order::seq_cst) volatile noexcept;
	constexpr void store(T, memory_order = memory_order::seq_cst) noexcept;
	T operator=(T) volatile noexcept;
	constexpr T operator=(T) noexcept;

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

	void wait(T, memory_order = memory_order::seq_cst) const volatile noexcept;
	constexpr void wait(T, memory_order = memory_order::seq_cst) const noexcept;
	void notify_one() volatile noexcept;
	constexpr void notify_one() noexcept;
	void notify_all() volatile noexcept;
	constexpr void notify_all() noexcept;
};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_BASE_GENERAL_HPP
