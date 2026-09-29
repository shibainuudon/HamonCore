/**
 *	@file	atomic_ref_base_integral.hpp
 *
 *	@brief	atomic_ref_base_integral の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_INTEGRAL_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_INTEGRAL_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/atomic_ref_base_common.hpp>
#include <hamon/atomic/detail/atomic_fetch_add.hpp>
#include <hamon/atomic/detail/atomic_fetch_and.hpp>
#include <hamon/atomic/detail/atomic_fetch_max.hpp>
#include <hamon/atomic/detail/atomic_fetch_min.hpp>
#include <hamon/atomic/detail/atomic_fetch_or.hpp>
#include <hamon/atomic/detail/atomic_fetch_sub.hpp>
#include <hamon/atomic/detail/atomic_fetch_xor.hpp>
#include <hamon/atomic/detail/atomic_store_add.hpp>
#include <hamon/atomic/detail/atomic_store_and.hpp>
#include <hamon/atomic/detail/atomic_store_max.hpp>
#include <hamon/atomic/detail/atomic_store_min.hpp>
#include <hamon/atomic/detail/atomic_store_or.hpp>
#include <hamon/atomic/detail/atomic_store_sub.hpp>
#include <hamon/atomic/detail/atomic_store_xor.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_const.hpp>
#include <hamon/assert.hpp>

namespace hamon
{
namespace detail
{

// 32.5.7.3 Specializations for integral types[atomics.ref.int]

template <typename integral_type>
struct atomic_ref_base_integral : public hamon::detail::atomic_ref_base_common<integral_type>
{
private:
	using base = hamon::detail::atomic_ref_base_common<integral_type>;
	using base::base;

public:
	using value_type = typename base::value_type;
	using difference_type = value_type;

	template <typename U = integral_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.int]/5
	constexpr value_type fetch_add(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.int]/6,7
		return hamon::detail::atomic_fetch_add(this->data(), operand, order);
	}

	template <typename U = integral_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.int]/5
	constexpr value_type fetch_sub(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.int]/6,7
		return hamon::detail::atomic_fetch_sub(this->data(), operand, order);
	}

	template <typename U = integral_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.int]/5
	constexpr value_type fetch_and(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.int]/6,7
		return hamon::detail::atomic_fetch_and(this->data(), operand, order);
	}

	template <typename U = integral_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.int]/5
	constexpr value_type fetch_or(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.int]/6,7
		return hamon::detail::atomic_fetch_or(this->data(), operand, order);
	}

	template <typename U = integral_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.int]/5
	constexpr value_type fetch_xor(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.int]/6,7
		return hamon::detail::atomic_fetch_xor(this->data(), operand, order);
	}

	template <typename U = integral_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.int]/5
	constexpr value_type fetch_max(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.int]/6,7
		return hamon::detail::atomic_fetch_max(this->data(), operand, order);
	}

	template <typename U = integral_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.int]/5
	constexpr value_type fetch_min(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.int]/6,7
		return hamon::detail::atomic_fetch_min(this->data(), operand, order);
	}

	template <typename U = integral_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.int]/10
	constexpr void store_add(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.ref.int]/12
		hamon::detail::atomic_store_add(this->data(), operand, order);
	}

	template <typename U = integral_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.int]/10
	constexpr void store_sub(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.ref.int]/12
		hamon::detail::atomic_store_sub(this->data(), operand, order);
	}

	template <typename U = integral_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.int]/10
	constexpr void store_and(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.ref.int]/12
		hamon::detail::atomic_store_and(this->data(), operand, order);
	}

	template <typename U = integral_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.int]/10
	constexpr void store_or(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.ref.int]/12
		hamon::detail::atomic_store_or(this->data(), operand, order);
	}

	template <typename U = integral_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.int]/10
	constexpr void store_xor(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.ref.int]/12
		hamon::detail::atomic_store_xor(this->data(), operand, order);
	}

	template <typename U = integral_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.int]/10
	constexpr void store_max(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.ref.int]/12
		hamon::detail::atomic_store_max(this->data(), operand, order);
	}

	template <typename U = integral_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.int]/10
	constexpr void store_min(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.ref.int]/12
		hamon::detail::atomic_store_min(this->data(), operand, order);
	}

	template <typename U = integral_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.memop]/2
	constexpr value_type operator++(int) const noexcept
	{
		// [atomics.ref.memop]/3
		return fetch_add(1);
	}

	template <typename U = integral_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.memop]/4
	constexpr value_type operator--(int) const noexcept
	{
		// [atomics.ref.memop]/5
		return fetch_sub(1);
	}

	template <typename U = integral_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.memop]/6
	constexpr value_type operator++() const noexcept
	{
		// [atomics.ref.memop]/7
		return fetch_add(1) + 1;
	}

	template <typename U = integral_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.memop]/8
	constexpr value_type operator--() const noexcept
	{
		// [atomics.ref.memop]/9
		return fetch_sub(1) - 1;
	}

	template <typename U = integral_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.int]/14
	constexpr value_type operator+=(value_type operand) const noexcept
	{
		// [atomics.ref.int]/15
		return fetch_add(operand) + operand;
	}

	template <typename U = integral_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.int]/14
	constexpr value_type operator-=(value_type operand) const noexcept
	{
		// [atomics.ref.int]/15
		return fetch_sub(operand) - operand;
	}

	template <typename U = integral_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.int]/14
	constexpr value_type operator&=(value_type operand) const noexcept
	{
		// [atomics.ref.int]/15
		return fetch_and(operand) & operand;
	}

	template <typename U = integral_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.int]/14
	constexpr value_type operator|=(value_type operand) const noexcept
	{
		// [atomics.ref.int]/15
		return fetch_or(operand) | operand;
	}

	template <typename U = integral_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.int]/14
	constexpr value_type operator^=(value_type operand) const noexcept
	{
		// [atomics.ref.int]/15
		return fetch_xor(operand) ^ operand;
	}
};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_INTEGRAL_HPP
