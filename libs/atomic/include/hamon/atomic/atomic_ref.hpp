/**
 *	@file	atomic_ref.hpp
 *
 *	@brief	atomic_ref の定義
 */

#ifndef HAMON_ATOMIC_ATOMIC_REF_HPP
#define HAMON_ATOMIC_ATOMIC_REF_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/atomic_is_always_lock_free.hpp>
#include <hamon/atomic/detail/atomic_is_lock_free.hpp>
#include <hamon/atomic/detail/atomic_ref_base.hpp>
#include <hamon/atomic/detail/atomic_required_alignment.hpp>
#include <hamon/atomic/detail/atomic_store.hpp>
#include <hamon/atomic/detail/atomic_load.hpp>
#include <hamon/atomic/detail/atomic_exchange.hpp>
#include <hamon/atomic/detail/atomic_compare_exchange_weak.hpp>
#include <hamon/atomic/detail/atomic_compare_exchange_strong.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/copy_cv.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_const.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_trivially_copyable.hpp>
#include <hamon/type_traits/is_volatile.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/assert.hpp>

namespace hamon
{

// 32.5.7 Class template atomic_ref[atomics.ref.generic]

template <typename T>
struct atomic_ref : public hamon::detail::atomic_ref_base<T>
{
private:
	using base = hamon::detail::atomic_ref_base<T>;

	using address_return_type = hamon::copy_cv_t<void, T>*;

public:
	using value_type = typename base::value_type;

	// [atomics.ref.ops]/1
	static constexpr hamon::size_t required_alignment = hamon::detail::atomic_required_alignment<T>::value;

	// [atomics.ref.ops]/3
	static constexpr bool is_always_lock_free = hamon::detail::atomic_is_always_lock_free<T>::value;

	// [atomics.ref.generic.general]/2
	static_assert(hamon::is_trivially_copyable_v<T>, "");

	// [atomics.ref.generic.general]/5
	static_assert(is_always_lock_free || !hamon::is_volatile_v<T>, "");

	bool is_lock_free() const noexcept
	{
		// [atomics.ref.ops]/4
		return hamon::detail::atomic_is_lock_free<T>();
	}

	constexpr explicit atomic_ref(T& obj)
		// [atomics.ref.ops]/6
		: base(hamon::addressof(obj))
	{}

	explicit atomic_ref(T&&) = delete;

	constexpr atomic_ref(atomic_ref const& ref) noexcept
		// [atomics.ref.ops]/8
		: base(ref)
	{}

	template <typename U,
		typename = hamon::enable_if_t<hamon::is_same_v<hamon::remove_cv_t<T>, hamon::remove_cv_t<U>>>, // [atomics.ref.ops]/9.1
		typename = hamon::enable_if_t<hamon::is_convertible_v<U*, T*>>                                 // [atomics.ref.ops]/9.2
	>
	constexpr atomic_ref(atomic_ref<U> const& ref) noexcept
		// [atomics.ref.ops]/10
		: base(ref)
	{}

	atomic_ref& operator=(atomic_ref const&) = delete;

	template <typename U = T, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.ops]/11
	constexpr void store(value_type desired, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.ops]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.ref.ops]/13
		hamon::detail::atomic_store(this->data(), desired, order);
	}

	template <typename U = T, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.ops]/14
	constexpr value_type operator=(value_type desired) const noexcept
	{
		// [atomics.ref.ops]/15
		store(desired);
		return desired;
	}

	constexpr value_type load(memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.ops]/16
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::acquire ||
			order == memory_order::seq_cst);

		// [atomics.ref.ops]/17,18
		return hamon::detail::atomic_load(this->data(), order);
	}

	constexpr operator value_type() const noexcept
	{
		// [atomics.ref.ops]/19
		return load();
	}

	template <typename U = T, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.ops]/20
	constexpr value_type exchange(value_type desired, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.ops]/21,22
		return hamon::detail::atomic_exchange(this->data(), desired, order);
	}

	template <typename U = T, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.ops]/23
	constexpr bool compare_exchange_weak(value_type& expected, value_type desired, memory_order success, memory_order failure) const noexcept
	{
		// [atomics.ref.ops]/24
		HAMON_ASSERT(
			failure == memory_order::relaxed ||
			failure == memory_order::acquire ||
			failure == memory_order::seq_cst);

		// [atomics.ref.ops]/25,26
		return hamon::detail::atomic_compare_exchange_weak(
			this->data(), hamon::addressof(expected), desired, success, failure);
	}

	template <typename U = T, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.ops]/23
	constexpr bool compare_exchange_strong(value_type& expected, value_type desired, memory_order success, memory_order failure) const noexcept
	{
		// [atomics.ref.ops]/24
		HAMON_ASSERT(
			failure == memory_order::relaxed ||
			failure == memory_order::acquire ||
			failure == memory_order::seq_cst);

		// [atomics.ref.ops]/25,26
		return hamon::detail::atomic_compare_exchange_strong(
			this->data(), hamon::addressof(expected), desired, success, failure);
	}

	template <typename U = T, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.ops]/23
	constexpr bool compare_exchange_weak(value_type& expected, value_type desired, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.ops]/25,26
		auto success = order;
		auto failure =
			(order == memory_order::acq_rel) ? memory_order::acquire :
			(order == memory_order::release) ? memory_order::relaxed :
			order;
		return hamon::detail::atomic_compare_exchange_weak(
			this->data(), hamon::addressof(expected), desired, success, failure);
	}

	template <typename U = T, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.ops]/23
	constexpr bool compare_exchange_strong(value_type& expected, value_type desired, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.ops]/25,26
		auto success = order;
		auto failure =
			(order == memory_order::acq_rel) ? memory_order::acquire :
			(order == memory_order::release) ? memory_order::relaxed :
			order;
		return hamon::detail::atomic_compare_exchange_strong(
			this->data(), hamon::addressof(expected), desired, success, failure);
	}

	constexpr void wait(value_type old, memory_order order = memory_order::seq_cst) const noexcept;

	template <typename U = T, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.ops]/31
	constexpr void notify_one() const noexcept;

	template <typename U = T, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.ops]/34
	constexpr void notify_all() const noexcept;

	constexpr address_return_type address() const noexcept
	{
		// [atomics.ref.ops]/37
		return this->data();
	}
};

}	// namespace hamon

#endif // HAMON_ATOMIC_ATOMIC_REF_HPP
