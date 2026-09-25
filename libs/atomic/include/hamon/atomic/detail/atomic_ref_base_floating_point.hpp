/**
 *	@file	atomic_ref_base_floating_point.hpp
 *
 *	@brief	atomic_ref_base_floating_point の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_FLOATING_POINT_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_FLOATING_POINT_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/atomic_is_always_lock_free.hpp>
#include <hamon/atomic/detail/atomic_is_lock_free.hpp>
#include <hamon/atomic/detail/atomic_required_alignment.hpp>
#include <hamon/atomic/detail/atomic_store.hpp>
#include <hamon/atomic/detail/atomic_load.hpp>
#include <hamon/atomic/detail/atomic_exchange.hpp>
#include <hamon/atomic/detail/atomic_compare_exchange_weak.hpp>
#include <hamon/atomic/detail/atomic_compare_exchange_strong.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/copy_cv.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/assert.hpp>

namespace hamon
{
namespace detail
{

// 32.5.7.4 Specializations for floating-point types[atomics.ref.float]

template <typename T>
struct atomic_ref_base_floating_point
{
private:
	using floating_point_type = T;

	floating_point_type* ptr;

	using address_return_type = hamon::copy_cv_t<void, floating_point_type>*;

public:
	using value_type = hamon::remove_cv_t<floating_point_type>;
	using difference_type = value_type;

	// [atomics.ref.ops]/1
	static constexpr hamon::size_t required_alignment = hamon::detail::atomic_required_alignment<floating_point_type>::value;

	// [atomics.ref.ops]/3
	static constexpr bool is_always_lock_free = hamon::detail::atomic_is_always_lock_free<floating_point_type>::value;

	// [atomics.ref.float]/2
	static_assert(is_always_lock_free || !hamon::is_volatile_v<floating_point_type>, "");

	bool is_lock_free() const noexcept
	{
		// [atomics.ref.ops]/4
		return hamon::detail::atomic_is_lock_free<floating_point_type>();
	}

	constexpr explicit atomic_ref_base_floating_point(floating_point_type& obj)
		// [atomics.ref.ops]/6
		: ptr(hamon::addressof(obj))
	{}

	explicit atomic_ref_base_floating_point(floating_point_type&&) = delete;

	constexpr atomic_ref_base_floating_point(atomic_ref_base_floating_point const& ref) noexcept
		// [atomics.ref.ops]/8
		: ptr(ref.ptr)
	{}

	template <typename U,
		typename = hamon::enable_if_t<hamon::is_same_v<hamon::remove_cv_t<floating_point_type>, hamon::remove_cv_t<U>>>, // [atomics.ref.ops]/9.1
		typename = hamon::enable_if_t<hamon::is_convertible_v<U*, floating_point_type*>>                                 // [atomics.ref.ops]/9.2
	>
	constexpr atomic_ref_base_floating_point(atomic_ref_base_floating_point<U> const& ref) noexcept
		// [atomics.ref.ops]/10
		: ptr(ref.ptr)
	{}

	atomic_ref_base_floating_point& operator=(atomic_ref_base_floating_point const&) = delete;

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.ops]/11
	constexpr void store(value_type desired, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.ops]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.ref.ops]/13
		hamon::detail::atomic_store(ptr, desired, order);
	}

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.ops]/14
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
		return hamon::detail::atomic_load(ptr, order);
	}

	constexpr operator value_type() const noexcept
	{
		// [atomics.ref.ops]/19
		return load();
	}

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.ops]/20
	constexpr value_type exchange(value_type desired, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.ops]/21,22
		return hamon::detail::atomic_exchange(ptr, desired, order);
	}

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.ops]/23
	constexpr bool compare_exchange_weak(value_type& expected, value_type desired, memory_order success, memory_order failure) const noexcept
	{
		// [atomics.ref.ops]/24
		HAMON_ASSERT(
			failure == memory_order::relaxed ||
			failure == memory_order::acquire ||
			failure == memory_order::seq_cst);

		// [atomics.ref.ops]/25,26
		return hamon::detail::atomic_compare_exchange_weak(
			ptr, hamon::addressof(expected), desired, success, failure);
	}

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.ops]/23
	constexpr bool compare_exchange_strong(value_type& expected, value_type desired, memory_order success, memory_order failure) const noexcept
	{
		// [atomics.ref.ops]/24
		HAMON_ASSERT(
			failure == memory_order::relaxed ||
			failure == memory_order::acquire ||
			failure == memory_order::seq_cst);

		// [atomics.ref.ops]/25,26
		return hamon::detail::atomic_compare_exchange_strong(
			ptr, hamon::addressof(expected), desired, success, failure);
	}

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.ops]/23
	constexpr bool compare_exchange_weak(value_type& expected, value_type desired, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.ops]/25,26
		auto success = order;
		auto failure =
			(order == memory_order::acq_rel) ? memory_order::acquire :
			(order == memory_order::release) ? memory_order::relaxed :
			order;
		return hamon::detail::atomic_compare_exchange_weak(
			ptr, hamon::addressof(expected), desired, success, failure);
	}

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.ops]/23
	constexpr bool compare_exchange_strong(value_type& expected, value_type desired, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.ops]/25,26
		auto success = order;
		auto failure =
			(order == memory_order::acq_rel) ? memory_order::acquire :
			(order == memory_order::release) ? memory_order::relaxed :
			order;
		return hamon::detail::atomic_compare_exchange_strong(
			ptr, hamon::addressof(expected), desired, success, failure);
	}

	constexpr value_type fetch_add(value_type, memory_order = memory_order::seq_cst) const noexcept;
	constexpr value_type fetch_sub(value_type, memory_order = memory_order::seq_cst) const noexcept;

	constexpr value_type fetch_max(value_type, memory_order = memory_order::seq_cst) const noexcept;
	constexpr value_type fetch_min(value_type, memory_order = memory_order::seq_cst) const noexcept;
	constexpr value_type fetch_fmaximum(value_type, memory_order = memory_order::seq_cst) const noexcept;
	constexpr value_type fetch_fminimum(value_type, memory_order = memory_order::seq_cst) const noexcept;
	constexpr value_type fetch_fmaximum_num(value_type, memory_order = memory_order::seq_cst) const noexcept;
	constexpr value_type fetch_fminimum_num(value_type, memory_order = memory_order::seq_cst) const noexcept;

	constexpr void store_add(value_type, memory_order = memory_order::seq_cst) const noexcept;
	constexpr void store_sub(value_type, memory_order = memory_order::seq_cst) const noexcept;
	constexpr void store_max(value_type, memory_order = memory_order::seq_cst) const noexcept;
	constexpr void store_min(value_type, memory_order = memory_order::seq_cst) const noexcept;
	constexpr void store_fmaximum(value_type, memory_order = memory_order::seq_cst) const noexcept;
	constexpr void store_fminimum(value_type, memory_order = memory_order::seq_cst) const noexcept;
	constexpr void store_fmaximum_num(value_type, memory_order = memory_order::seq_cst) const noexcept;
	constexpr void store_fminimum_num(value_type, memory_order = memory_order::seq_cst) const noexcept;

	constexpr value_type operator+=(value_type) const noexcept;
	constexpr value_type operator-=(value_type) const noexcept;

	constexpr void wait(value_type, memory_order = memory_order::seq_cst) const noexcept;

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.ops]/31
	constexpr void notify_one() const noexcept;

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.ops]/34
	constexpr void notify_all() const noexcept;

	constexpr address_return_type address() const noexcept
	{
		// [atomics.ref.ops]/37
		return ptr;
	}
};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_FLOATING_POINT_HPP
