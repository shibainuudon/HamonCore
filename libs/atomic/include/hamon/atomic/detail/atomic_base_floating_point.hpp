/**
 *	@file	atomic_base_floating_point.hpp
 *
 *	@brief	atomic_base_floating_point の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_BASE_FLOATING_POINT_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_BASE_FLOATING_POINT_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/atomic_base_common.hpp>
#include <hamon/atomic/detail/atomic_fetch_add.hpp>
#include <hamon/atomic/detail/atomic_fetch_fmaximum.hpp>
#include <hamon/atomic/detail/atomic_fetch_fmaximum_num.hpp>
#include <hamon/atomic/detail/atomic_fetch_fminimum.hpp>
#include <hamon/atomic/detail/atomic_fetch_fminimum_num.hpp>
#include <hamon/atomic/detail/atomic_fetch_sub.hpp>
#include <hamon/atomic/detail/atomic_store_add.hpp>
#include <hamon/atomic/detail/atomic_store_fmaximum.hpp>
#include <hamon/atomic/detail/atomic_store_fmaximum_num.hpp>
#include <hamon/atomic/detail/atomic_store_fminimum.hpp>
#include <hamon/atomic/detail/atomic_store_fminimum_num.hpp>
#include <hamon/atomic/detail/atomic_store_max.hpp>
#include <hamon/atomic/detail/atomic_store_min.hpp>
#include <hamon/atomic/detail/atomic_store_sub.hpp>
#include <hamon/atomic/detail/atomic_is_always_lock_free.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/assert.hpp>

namespace hamon
{
namespace detail
{

// 32.5.8.4 Specializations for floating-point types[atomics.types.float]

template <typename floating_point_type>
struct atomic_base_floating_point : public hamon::detail::atomic_base_common<floating_point_type>
{
private:
	using base = hamon::detail::atomic_base_common<floating_point_type>;
	using base::base;

public:
	using value_type = floating_point_type;
	using difference_type = value_type;

	// [atomics.types.operations]/4
	static constexpr bool is_always_lock_free = hamon::detail::atomic_is_always_lock_free<floating_point_type>::value;

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/5
	floating_point_type fetch_add(floating_point_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/6
		return hamon::detail::atomic_fetch_add(this->data(), operand, order);
	}

	constexpr floating_point_type fetch_add(floating_point_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/6
		return hamon::detail::atomic_fetch_add(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/5
	floating_point_type fetch_sub(floating_point_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/6
		return hamon::detail::atomic_fetch_sub(this->data(), operand, order);
	}

	constexpr floating_point_type fetch_sub(floating_point_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/6
		return hamon::detail::atomic_fetch_sub(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/5
	floating_point_type fetch_max(floating_point_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/6,9.3,10
		return hamon::detail::atomic_fetch_fmaximum_num(this->data(), operand, order);
	}

	constexpr floating_point_type fetch_max(floating_point_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/6,9.3,10
		return hamon::detail::atomic_fetch_fmaximum_num(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/5
	floating_point_type fetch_min(floating_point_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/6,9.3,10
		return hamon::detail::atomic_fetch_fminimum_num(this->data(), operand, order);
	}

	constexpr floating_point_type fetch_min(floating_point_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/6,9.3,10
		return hamon::detail::atomic_fetch_fminimum_num(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/5
	floating_point_type fetch_fmaximum(floating_point_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/6,9.1
		return hamon::detail::atomic_fetch_fmaximum(this->data(), operand, order);
	}

	constexpr floating_point_type fetch_fmaximum(floating_point_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/6,9.1
		return hamon::detail::atomic_fetch_fmaximum(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/5
	floating_point_type fetch_fminimum(floating_point_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/6,9.1
		return hamon::detail::atomic_fetch_fminimum(this->data(), operand, order);
	}

	constexpr floating_point_type fetch_fminimum(floating_point_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/6,9.1
		return hamon::detail::atomic_fetch_fminimum(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/5
	floating_point_type fetch_fmaximum_num(floating_point_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/6,9.2
		return hamon::detail::atomic_fetch_fmaximum_num(this->data(), operand, order);
	}

	constexpr floating_point_type fetch_fmaximum_num(floating_point_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/6,9.2
		return hamon::detail::atomic_fetch_fmaximum_num(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/5
	floating_point_type fetch_fminimum_num(floating_point_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/6,9.2
		return hamon::detail::atomic_fetch_fminimum_num(this->data(), operand, order);
	}

	constexpr floating_point_type fetch_fminimum_num(floating_point_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/6,9.2
		return hamon::detail::atomic_fetch_fminimum_num(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/11
	void store_add(floating_point_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13
		hamon::detail::atomic_store_add(this->data(), operand, order);
	}

	constexpr void store_add(floating_point_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13
		hamon::detail::atomic_store_add(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/11
	void store_sub(floating_point_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13
		hamon::detail::atomic_store_sub(this->data(), operand, order);
	}

	constexpr void store_sub(floating_point_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13
		hamon::detail::atomic_store_sub(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/11
	void store_max(floating_point_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13,15.3/16
		hamon::detail::atomic_store_max(this->data(), operand, order);
	}

	constexpr void store_max(floating_point_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13,15.3/16
		hamon::detail::atomic_store_max(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/11
	void store_min(floating_point_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13,15.3/16
		hamon::detail::atomic_store_min(this->data(), operand, order);
	}

	constexpr void store_min(floating_point_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13,15.3/16
		hamon::detail::atomic_store_min(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/11
	void store_fmaximum(floating_point_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13,15.1
		hamon::detail::atomic_store_fmaximum(this->data(), operand, order);
	}

	constexpr void store_fmaximum(floating_point_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13,15.1
		hamon::detail::atomic_store_fmaximum(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/11
	void store_fminimum(floating_point_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13,15.1
		hamon::detail::atomic_store_fminimum(this->data(), operand, order);
	}

	constexpr void store_fminimum(floating_point_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13,15.1
		hamon::detail::atomic_store_fminimum(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/11
	void store_fmaximum_num(floating_point_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13,15.2
		hamon::detail::atomic_store_fmaximum_num(this->data(), operand, order);
	}

	constexpr void store_fmaximum_num(floating_point_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13,15.2
		hamon::detail::atomic_store_fmaximum_num(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/11
	void store_fminimum_num(floating_point_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13,15.2
		hamon::detail::atomic_store_fminimum_num(this->data(), operand, order);
	}

	constexpr void store_fminimum_num(floating_point_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.float]/13,15.2
		hamon::detail::atomic_store_fminimum_num(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/17
	floating_point_type operator+=(floating_point_type operand) volatile noexcept
	{
		// [atomics.types.float]/18
		return fetch_add(operand) + operand;
	}

	constexpr floating_point_type operator+=(floating_point_type operand) noexcept
	{
		// [atomics.types.float]/18
		return fetch_add(operand) + operand;
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.float]/17
	floating_point_type operator-=(floating_point_type operand) volatile noexcept
	{
		// [atomics.types.float]/18
		return fetch_sub(operand) - operand;
	}

	constexpr floating_point_type operator-=(floating_point_type operand) noexcept
	{
		// [atomics.types.float]/18
		return fetch_sub(operand) - operand;
	}
};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_BASE_FLOATING_POINT_HPP
