/**
 *	@file	atomic_base_integral.hpp
 *
 *	@brief	atomic_base_integral の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_BASE_INTEGRAL_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_BASE_INTEGRAL_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/atomic_base_common.hpp>
#include <hamon/atomic/detail/atomic_fetch_add.hpp>
#include <hamon/atomic/detail/atomic_fetch_and.hpp>
#include <hamon/atomic/detail/atomic_fetch_max.hpp>
#include <hamon/atomic/detail/atomic_fetch_min.hpp>
#include <hamon/atomic/detail/atomic_fetch_or.hpp>
#include <hamon/atomic/detail/atomic_fetch_sub.hpp>
#include <hamon/atomic/detail/atomic_fetch_xor.hpp>
#include <hamon/atomic/detail/atomic_is_always_lock_free.hpp>
#include <hamon/atomic/detail/atomic_store_add.hpp>
#include <hamon/atomic/detail/atomic_store_and.hpp>
#include <hamon/atomic/detail/atomic_store_max.hpp>
#include <hamon/atomic/detail/atomic_store_min.hpp>
#include <hamon/atomic/detail/atomic_store_or.hpp>
#include <hamon/atomic/detail/atomic_store_sub.hpp>
#include <hamon/atomic/detail/atomic_store_xor.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/assert.hpp>

namespace hamon
{
namespace detail
{

// 32.5.8.3 Specializations for integers[atomics.types.int]

template <typename integral_type>
struct atomic_base_integral : public hamon::detail::atomic_base_common<integral_type>
{
private:
	using base = hamon::detail::atomic_base_common<integral_type>;
	using base::base;

public:
	using value_type = integral_type;
	using difference_type = value_type;

	// [atomics.types.operations]/4
	static constexpr bool is_always_lock_free = hamon::detail::atomic_is_always_lock_free<integral_type>::value;

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/5
	integral_type fetch_add(integral_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_add(this->data(), operand, order);
	}

	constexpr integral_type fetch_add(integral_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_add(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/5
	integral_type fetch_sub(integral_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_sub(this->data(), operand, order);
	}

	constexpr integral_type fetch_sub(integral_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_sub(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/5
	integral_type fetch_and(integral_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_and(this->data(), operand, order);
	}

	constexpr integral_type fetch_and(integral_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_and(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/5
	integral_type fetch_or(integral_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_or(this->data(), operand, order);
	}

	constexpr integral_type fetch_or(integral_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_or(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/5
	integral_type fetch_xor(integral_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_xor(this->data(), operand, order);
	}

	constexpr integral_type fetch_xor(integral_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_xor(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/5
	integral_type fetch_max(integral_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_max(this->data(), operand, order);
	}

	constexpr integral_type fetch_max(integral_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_max(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/5
	integral_type fetch_min(integral_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_min(this->data(), operand, order);
	}

	constexpr integral_type fetch_min(integral_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/6,7
		return hamon::detail::atomic_fetch_min(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/10
	void store_add(integral_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_add(this->data(), operand, order);
	}

	constexpr void store_add(integral_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_add(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/10
	void store_sub(integral_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_sub(this->data(), operand, order);
	}

	constexpr void store_sub(integral_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_sub(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/10
	void store_and(integral_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_and(this->data(), operand, order);
	}

	constexpr void store_and(integral_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_and(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/10
	void store_or(integral_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_or(this->data(), operand, order);
	}

	constexpr void store_or(integral_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_or(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/10
	void store_xor(integral_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_xor(this->data(), operand, order);
	}

	constexpr void store_xor(integral_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_xor(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/10
	void store_max(integral_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_max(this->data(), operand, order);
	}

	constexpr void store_max(integral_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_max(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/10
	void store_min(integral_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_min(this->data(), operand, order);
	}

	constexpr void store_min(integral_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.int]/11
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.types.int]/12
		hamon::detail::atomic_store_min(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.memop]/1
	integral_type operator++(int) volatile noexcept
	{
		// [atomics.types.memop]/2
		return fetch_add(integral_type(1));
	}

	constexpr integral_type operator++(int) noexcept
	{
		// [atomics.types.memop]/2
		return fetch_add(integral_type(1));
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.memop]/3
	integral_type operator--(int) volatile noexcept
	{
		// [atomics.types.memop]/4
		return fetch_sub(integral_type(1));
	}

	constexpr integral_type operator--(int) noexcept
	{
		// [atomics.types.memop]/4
		return fetch_sub(integral_type(1));
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.memop]/5
	integral_type operator++() volatile noexcept
	{
		// [atomics.types.memop]/6
		return fetch_add(integral_type(1)) + integral_type(1);
	}

	constexpr integral_type operator++() noexcept
	{
		// [atomics.types.memop]/6
		return fetch_add(integral_type(1)) + integral_type(1);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.memop]/7
	integral_type operator--() volatile noexcept
	{
		// [atomics.types.memop]/8
		return fetch_sub(integral_type(1)) - integral_type(1);
	}

	constexpr integral_type operator--() noexcept
	{
		// [atomics.types.memop]/8
		return fetch_sub(integral_type(1)) - integral_type(1);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/14
	integral_type operator+=(integral_type operand) volatile noexcept
	{
		// [atomics.types.int]/15
		return fetch_add(operand) + operand;
	}

	constexpr integral_type operator+=(integral_type operand) noexcept
	{
		// [atomics.types.int]/15
		return fetch_add(operand) + operand;
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/14
	integral_type operator-=(integral_type operand) volatile noexcept
	{
		// [atomics.types.int]/15
		return fetch_sub(operand) - operand;
	}

	constexpr integral_type operator-=(integral_type operand) noexcept
	{
		// [atomics.types.int]/15
		return fetch_sub(operand) - operand;
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/14
	integral_type operator&=(integral_type operand) volatile noexcept
	{
		// [atomics.types.int]/15
		return fetch_and(operand) & operand;
	}

	constexpr integral_type operator&=(integral_type operand) noexcept
	{
		// [atomics.types.int]/15
		return fetch_and(operand) & operand;
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/14
	integral_type operator|=(integral_type operand) volatile noexcept
	{
		// [atomics.types.int]/15
		return fetch_or(operand) | operand;
	}

	constexpr integral_type operator|=(integral_type operand) noexcept
	{
		// [atomics.types.int]/15
		return fetch_or(operand) | operand;
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.int]/14
	integral_type operator^=(integral_type operand) volatile noexcept
	{
		// [atomics.types.int]/15
		return fetch_xor(operand) ^ operand;
	}

	constexpr integral_type operator^=(integral_type operand) noexcept
	{
		// [atomics.types.int]/15
		return fetch_xor(operand) ^ operand;
	}
};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_BASE_INTEGRAL_HPP
