/**
 *	@file	atomic_ref_base_floating_point.hpp
 *
 *	@brief	atomic_ref_base_floating_point の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_FLOATING_POINT_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_FLOATING_POINT_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/atomic_ref_base_common.hpp>
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
#include <hamon/atomic/detail/atomic_store_sub.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_const.hpp>
#include <hamon/assert.hpp>

namespace hamon
{
namespace detail
{

// 32.5.7.4 Specializations for floating-point types[atomics.ref.float]

template <typename floating_point_type>
struct atomic_ref_base_floating_point : public hamon::detail::atomic_ref_base_common<floating_point_type>
{
private:
	using base = hamon::detail::atomic_ref_base_common<floating_point_type>;
	using base::base;

public:
	using value_type = typename base::value_type;
	using difference_type = value_type;

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.float]/5
	constexpr value_type fetch_add(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.float]/6
		return hamon::detail::atomic_fetch_add(this->data(), operand, order);
	}

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.float]/5
	constexpr value_type fetch_sub(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.float]/6
		return hamon::detail::atomic_fetch_sub(this->data(), operand, order);
	}

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.float]/5
	constexpr value_type fetch_max(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.float]/6,9.3,10
		return hamon::detail::atomic_fetch_fmaximum_num(this->data(), operand, order);
	}

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.float]/5
	constexpr value_type fetch_min(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.float]/6,9.3,10
		return hamon::detail::atomic_fetch_fminimum_num(this->data(), operand, order);
	}

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.float]/5
	constexpr value_type fetch_fmaximum(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.float]/6,9.1
		return hamon::detail::atomic_fetch_fmaximum(this->data(), operand, order);
	}

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.float]/5
	constexpr value_type fetch_fminimum(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.float]/6,9.1
		return hamon::detail::atomic_fetch_fminimum(this->data(), operand, order);
	}

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.float]/5
	constexpr value_type fetch_fmaximum_num(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.float]/6,9.2
		return hamon::detail::atomic_fetch_fmaximum_num(this->data(), operand, order);
	}

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.float]/5
	constexpr value_type fetch_fminimum_num(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.float]/6,9.2
		return hamon::detail::atomic_fetch_fminimum_num(this->data(), operand, order);
	}

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.float]/11
	constexpr void store_add(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.ref.float]/13
		hamon::detail::atomic_store_add(this->data(), operand, order);
	}

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.float]/11
	constexpr void store_sub(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.ref.float]/13
		hamon::detail::atomic_store_sub(this->data(), operand, order);
	}

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.float]/11
	constexpr void store_max(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.ref.float]/13,15.3,16
		hamon::detail::atomic_store_fmaximum_num(this->data(), operand, order);
	}

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.float]/11
	constexpr void store_min(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.ref.float]/13,15.3,16
		hamon::detail::atomic_store_fminimum_num(this->data(), operand, order);
	}

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.float]/11
	constexpr void store_fmaximum(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.ref.float]/13,15.1
		hamon::detail::atomic_store_fmaximum(this->data(), operand, order);
	}

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.float]/11
	constexpr void store_fminimum(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.ref.float]/13,15.1
		hamon::detail::atomic_store_fminimum(this->data(), operand, order);
	}

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.float]/11
	constexpr void store_fmaximum_num(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.ref.float]/13,15.2
		hamon::detail::atomic_store_fmaximum_num(this->data(), operand, order);
	}

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.float]/11
	constexpr void store_fminimum_num(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.float]/12
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.ref.float]/13,15.2
		hamon::detail::atomic_store_fminimum_num(this->data(), operand, order);
	}

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.float]/17
	constexpr value_type operator+=(value_type operand) const noexcept
	{
		// [atomics.ref.float]/18
		return fetch_add(operand) + operand;
	}

	template <typename U = floating_point_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.float]/17
	constexpr value_type operator-=(value_type operand) const noexcept
	{
		// [atomics.ref.float]/18
		return fetch_sub(operand) - operand;
	}
};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_FLOATING_POINT_HPP
