/**
 *	@file	atomic_nonmember.hpp
 *
 *	@brief	[atomics.nonmembers] の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_NONMEMBER_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_NONMEMBER_HPP

#include <hamon/atomic/atomic.hpp>
#include <hamon/atomic/memory_order.hpp>

namespace hamon
{

// 32.5.9 Non-member functions[atomics.nonmembers]

template <typename T>
bool atomic_is_lock_free(atomic<T> const volatile* a) noexcept
{
	return a->is_lock_free();
}

template <typename T>
bool atomic_is_lock_free(atomic<T> const* a) noexcept
{
	return a->is_lock_free();
}

template <typename T>
void atomic_store(atomic<T> volatile* a, typename atomic<T>::value_type desired) noexcept
{
	a->store(desired);
}

template <typename T>
constexpr void atomic_store(atomic<T>* a, typename atomic<T>::value_type desired) noexcept
{
	a->store(desired);
}

template <typename T>
void atomic_store_explicit(atomic<T> volatile* a, typename atomic<T>::value_type desired, memory_order order) noexcept
{
	a->store(desired, order);
}

template <typename T>
constexpr void atomic_store_explicit(atomic<T>* a, typename atomic<T>::value_type desired, memory_order order) noexcept
{
	a->store(desired, order);
}

template <typename T>
T atomic_load(atomic<T> const volatile* a) noexcept
{
	return a->load();
}

template <typename T>
constexpr T atomic_load(atomic<T> const* a) noexcept
{
	return a->load();
}

template <typename T>
T atomic_load_explicit(atomic<T> const volatile* a, memory_order order) noexcept
{
	return a->load(order);
}

template <typename T>
constexpr T atomic_load_explicit(atomic<T> const* a, memory_order order) noexcept
{
	return a->load(order);
}

template <typename T>
T atomic_exchange(atomic<T> volatile* a, typename atomic<T>::value_type desired) noexcept
{
	return a->exchange(desired);
}

template <typename T>
constexpr T atomic_exchange(atomic<T>* a, typename atomic<T>::value_type desired) noexcept
{
	return a->exchange(desired);
}

template <typename T>
T atomic_exchange_explicit(atomic<T> volatile* a, typename atomic<T>::value_type desired, memory_order order) noexcept
{
	return a->exchange(desired, order);
}

template <typename T>
constexpr T atomic_exchange_explicit(atomic<T>* a, typename atomic<T>::value_type desired, memory_order order) noexcept
{
	return a->exchange(desired, order);
}

template <typename T>
bool atomic_compare_exchange_weak(atomic<T> volatile* a,
	typename atomic<T>::value_type* expected,
	typename atomic<T>::value_type desired) noexcept
{
	return a->compare_exchange_weak(*expected, desired);
}

template <typename T>
constexpr bool atomic_compare_exchange_weak(atomic<T>* a,
	typename atomic<T>::value_type* expected,
	typename atomic<T>::value_type desired) noexcept
{
	return a->compare_exchange_weak(*expected, desired);
}

template <typename T>
bool atomic_compare_exchange_strong(atomic<T> volatile* a,
	typename atomic<T>::value_type* expected,
	typename atomic<T>::value_type desired) noexcept
{
	return a->compare_exchange_strong(*expected, desired);
}

template <typename T>
constexpr bool atomic_compare_exchange_strong(atomic<T>* a,
	typename atomic<T>::value_type* expected,
	typename atomic<T>::value_type desired) noexcept
{
	return a->compare_exchange_strong(*expected, desired);
}

template <typename T>
bool atomic_compare_exchange_weak_explicit(atomic<T> volatile* a,
	typename atomic<T>::value_type* expected,
	typename atomic<T>::value_type desired,
	memory_order success, memory_order failure) noexcept
{
	return a->compare_exchange_weak(*expected, desired, success, failure);
}

template <typename T>
constexpr bool atomic_compare_exchange_weak_explicit(atomic<T>* a,
	typename atomic<T>::value_type* expected,
	typename atomic<T>::value_type desired,
	memory_order success, memory_order failure) noexcept
{
	return a->compare_exchange_weak(*expected, desired, success, failure);
}

template <typename T>
bool atomic_compare_exchange_strong_explicit(atomic<T> volatile* a,
	typename atomic<T>::value_type* expected,
	typename atomic<T>::value_type desired,
	memory_order success, memory_order failure) noexcept
{
	return a->compare_exchange_strong(*expected, desired, success, failure);
}

template <typename T>
constexpr bool atomic_compare_exchange_strong_explicit(atomic<T>* a,
	typename atomic<T>::value_type* expected,
	typename atomic<T>::value_type desired,
	memory_order success, memory_order failure) noexcept
{
	return a->compare_exchange_strong(*expected, desired, success, failure);
}

template <typename T>
T atomic_fetch_add(atomic<T> volatile* a, typename atomic<T>::difference_type operand) noexcept
{
	return a->fetch_add(operand);
}

template <typename T>
constexpr T atomic_fetch_add(atomic<T>* a, typename atomic<T>::difference_type operand) noexcept
{
	return a->fetch_add(operand);
}

template <typename T>
T atomic_fetch_add_explicit(atomic<T> volatile* a, typename atomic<T>::difference_type operand, memory_order order) noexcept
{
	return a->fetch_add(operand, order);
}

template <typename T>
constexpr T atomic_fetch_add_explicit(atomic<T>* a, typename atomic<T>::difference_type operand, memory_order order) noexcept
{
	return a->fetch_add(operand, order);
}

template <typename T>
T atomic_fetch_sub(atomic<T> volatile* a, typename atomic<T>::difference_type operand) noexcept
{
	return a->fetch_sub(operand);
}

template <typename T>
constexpr T atomic_fetch_sub(atomic<T>* a, typename atomic<T>::difference_type operand) noexcept
{
	return a->fetch_sub(operand);
}

template <typename T>
T atomic_fetch_sub_explicit(atomic<T> volatile* a, typename atomic<T>::difference_type operand, memory_order order) noexcept
{
	return a->fetch_sub(operand, order);
}

template <typename T>
constexpr T atomic_fetch_sub_explicit(atomic<T>* a, typename atomic<T>::difference_type operand, memory_order order) noexcept
{
	return a->fetch_sub(operand, order);
}

template <typename T>
T atomic_fetch_and(atomic<T> volatile* a, typename atomic<T>::value_type operand) noexcept
{
	return a->fetch_and(operand);
}

template <typename T>
constexpr T atomic_fetch_and(atomic<T>* a, typename atomic<T>::value_type operand) noexcept
{
	return a->fetch_and(operand);
}

template <typename T>
T atomic_fetch_and_explicit(atomic<T> volatile* a, typename atomic<T>::value_type operand, memory_order order) noexcept
{
	return a->fetch_and(operand, order);
}

template <typename T>
constexpr T atomic_fetch_and_explicit(atomic<T>* a, typename atomic<T>::value_type operand, memory_order order) noexcept
{
	return a->fetch_and(operand, order);
}

template <typename T>
T atomic_fetch_or(atomic<T> volatile* a, typename atomic<T>::value_type operand) noexcept
{
	return a->fetch_or(operand);
}

template <typename T>
constexpr T atomic_fetch_or(atomic<T>* a, typename atomic<T>::value_type operand) noexcept
{
	return a->fetch_or(operand);
}

template <typename T>
T atomic_fetch_or_explicit(atomic<T> volatile* a, typename atomic<T>::value_type operand, memory_order order) noexcept
{
	return a->fetch_or(operand, order);
}

template <typename T>
constexpr T atomic_fetch_or_explicit(atomic<T>* a, typename atomic<T>::value_type operand, memory_order order) noexcept
{
	return a->fetch_or(operand, order);
}

template <typename T>
T atomic_fetch_xor(atomic<T> volatile* a, typename atomic<T>::value_type operand) noexcept
{
	return a->fetch_xor(operand);
}

template <typename T>
constexpr T atomic_fetch_xor(atomic<T>* a, typename atomic<T>::value_type operand) noexcept
{
	return a->fetch_xor(operand);
}

template <typename T>
T atomic_fetch_xor_explicit(atomic<T> volatile* a, typename atomic<T>::value_type operand, memory_order order) noexcept
{
	return a->fetch_xor(operand, order);
}

template <typename T>
constexpr T atomic_fetch_xor_explicit(atomic<T>* a, typename atomic<T>::value_type operand, memory_order order) noexcept
{
	return a->fetch_xor(operand, order);
}

template <typename T>
T atomic_fetch_max(atomic<T> volatile* a, typename atomic<T>::value_type operand) noexcept
{
	return a->fetch_max(operand);
}

template <typename T>
constexpr T atomic_fetch_max(atomic<T>* a, typename atomic<T>::value_type operand) noexcept
{
	return a->fetch_max(operand);
}

template <typename T>
T atomic_fetch_max_explicit(atomic<T> volatile* a, typename atomic<T>::value_type operand, memory_order order) noexcept
{
	return a->fetch_max(operand, order);
}

template <typename T>
constexpr T atomic_fetch_max_explicit(atomic<T>* a, typename atomic<T>::value_type operand, memory_order order) noexcept
{
	return a->fetch_max(operand, order);
}

template <typename T>
T atomic_fetch_min(atomic<T> volatile* a, typename atomic<T>::value_type operand) noexcept
{
	return a->fetch_min(operand);
}

template <typename T>
constexpr T atomic_fetch_min(atomic<T>* a, typename atomic<T>::value_type operand) noexcept
{
	return a->fetch_min(operand);
}

template <typename T>
T atomic_fetch_min_explicit(atomic<T> volatile* a, typename atomic<T>::value_type operand, memory_order order) noexcept
{
	return a->fetch_min(operand, order);
}

template <typename T>
constexpr T atomic_fetch_min_explicit(atomic<T>* a, typename atomic<T>::value_type operand, memory_order order) noexcept
{
	return a->fetch_min(operand, order);
}

template <typename T>
void atomic_store_add(atomic<T> volatile* a, typename atomic<T>::difference_type operand) noexcept
{
	a->store_add(operand);
}

template <typename T>
constexpr void atomic_store_add(atomic<T>* a, typename atomic<T>::difference_type operand) noexcept
{
	a->store_add(operand);
}

template <typename T>
void atomic_store_add_explicit(atomic<T> volatile* a, typename atomic<T>::difference_type operand, memory_order order) noexcept
{
	a->store_add(operand, order);
}

template <typename T>
constexpr void atomic_store_add_explicit(atomic<T>* a, typename atomic<T>::difference_type operand, memory_order order) noexcept
{
	a->store_add(operand, order);
}

template <typename T>
void atomic_store_sub(atomic<T> volatile* a, typename atomic<T>::difference_type operand) noexcept
{
	a->store_sub(operand);
}

template <typename T>
constexpr void atomic_store_sub(atomic<T>* a, typename atomic<T>::difference_type operand) noexcept
{
	a->store_sub(operand);
}

template <typename T>
void atomic_store_sub_explicit(atomic<T> volatile* a, typename atomic<T>::difference_type operand, memory_order order) noexcept
{
	a->store_sub(operand, order);
}

template <typename T>
constexpr void atomic_store_sub_explicit(atomic<T>* a, typename atomic<T>::difference_type operand, memory_order order) noexcept
{
	a->store_sub(operand, order);
}

template <typename T>
void atomic_store_and(atomic<T> volatile* a, typename atomic<T>::value_type operand) noexcept
{
	a->store_and(operand);
}

template <typename T>
constexpr void atomic_store_and(atomic<T>* a, typename atomic<T>::value_type operand) noexcept
{
	a->store_and(operand);
}

template <typename T>
void atomic_store_and_explicit(atomic<T> volatile* a, typename atomic<T>::value_type operand, memory_order order) noexcept
{
	a->store_and(operand, order);
}

template <typename T>
constexpr void atomic_store_and_explicit(atomic<T>* a, typename atomic<T>::value_type operand, memory_order order) noexcept
{
	a->store_and(operand, order);
}

template <typename T>
void atomic_store_or(atomic<T> volatile* a, typename atomic<T>::value_type operand) noexcept
{
	a->store_or(operand);
}

template <typename T>
constexpr void atomic_store_or(atomic<T>* a, typename atomic<T>::value_type operand) noexcept
{
	a->store_or(operand);
}

template <typename T>
void atomic_store_or_explicit(atomic<T> volatile* a, typename atomic<T>::value_type operand, memory_order order) noexcept
{
	a->store_or(operand, order);
}

template <typename T>
constexpr void atomic_store_or_explicit(atomic<T>* a, typename atomic<T>::value_type operand, memory_order order) noexcept
{
	a->store_or(operand, order);
}

template <typename T>
void atomic_store_xor(atomic<T> volatile* a, typename atomic<T>::value_type operand) noexcept
{
	a->store_xor(operand);
}

template <typename T>
constexpr void atomic_store_xor(atomic<T>* a, typename atomic<T>::value_type operand) noexcept
{
	a->store_xor(operand);
}

template <typename T>
void atomic_store_xor_explicit(atomic<T> volatile* a, typename atomic<T>::value_type operand, memory_order order) noexcept
{
	a->store_xor(operand, order);
}

template <typename T>
constexpr void atomic_store_xor_explicit(atomic<T>* a, typename atomic<T>::value_type operand, memory_order order) noexcept
{
	a->store_xor(operand, order);
}

template <typename T>
void atomic_store_max(atomic<T> volatile* a, typename atomic<T>::value_type operand) noexcept
{
	a->store_max(operand);
}

template <typename T>
constexpr void atomic_store_max(atomic<T>* a, typename atomic<T>::value_type operand) noexcept
{
	a->store_max(operand);
}

template <typename T>
void atomic_store_max_explicit(atomic<T> volatile* a, typename atomic<T>::value_type operand, memory_order order) noexcept
{
	a->store_max(operand, order);
}

template <typename T>
constexpr void atomic_store_max_explicit(atomic<T>* a, typename atomic<T>::value_type operand, memory_order order) noexcept
{
	a->store_max(operand, order);
}

template <typename T>
void atomic_store_min(atomic<T> volatile* a, typename atomic<T>::value_type operand) noexcept
{
	a->store_min(operand);
}

template <typename T>
constexpr void atomic_store_min(atomic<T>* a, typename atomic<T>::value_type operand) noexcept
{
	a->store_min(operand);
}

template <typename T>
void atomic_store_min_explicit(atomic<T> volatile* a, typename atomic<T>::value_type operand, memory_order order) noexcept
{
	a->store_min(operand, order);
}

template <typename T>
constexpr void atomic_store_min_explicit(atomic<T>* a, typename atomic<T>::value_type operand, memory_order order) noexcept
{
	a->store_min(operand, order);
}

template <typename T>
void atomic_wait(atomic<T> const volatile* a, typename atomic<T>::value_type old) noexcept;

template <typename T>
constexpr void atomic_wait(atomic<T> const* a, typename atomic<T>::value_type old) noexcept;

template <typename T>
void atomic_wait_explicit(atomic<T> const volatile* a, typename atomic<T>::value_type old, memory_order order) noexcept;

template <typename T>
constexpr void atomic_wait_explicit(atomic<T> const* a, typename atomic<T>::value_type old, memory_order order) noexcept;

template <typename T>
void atomic_notify_one(atomic<T> volatile* a) noexcept;

template <typename T>
constexpr void atomic_notify_one(atomic<T>* a) noexcept;

template <typename T>
void atomic_notify_all(atomic<T> volatile* a) noexcept;

template <typename T>
constexpr void atomic_notify_all(atomic<T>* a) noexcept;

}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_NONMEMBER_HPP
