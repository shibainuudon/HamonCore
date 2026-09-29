/**
 *	@file	atomic_base_pointer.hpp
 *
 *	@brief	atomic_base_pointer の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_BASE_POINTER_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_BASE_POINTER_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/atomic_base_common.hpp>
#include <hamon/atomic/detail/atomic_fetch_add.hpp>
#include <hamon/atomic/detail/atomic_fetch_sub.hpp>
#include <hamon/atomic/detail/atomic_fetch_max.hpp>
#include <hamon/atomic/detail/atomic_fetch_min.hpp>
#include <hamon/atomic/detail/atomic_is_always_lock_free.hpp>
#include <hamon/atomic/detail/atomic_store_add.hpp>
#include <hamon/atomic/detail/atomic_store_sub.hpp>
#include <hamon/atomic/detail/atomic_store_max.hpp>
#include <hamon/atomic/detail/atomic_store_min.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_object.hpp>
#include <hamon/type_traits/remove_pointer.hpp>

namespace hamon
{
namespace detail
{

// 32.5.8.5 Partial specialization for pointers[atomics.types.pointer]

template <typename pointer_type>
struct atomic_base_pointer : public hamon::detail::atomic_base_common<pointer_type>
{
private:
	using base = hamon::detail::atomic_base_common<pointer_type>;
	using base::base;

public:
	using value_type = pointer_type;
	using difference_type = hamon::ptrdiff_t;

	// [atomics.types.operations]/4
	static constexpr bool is_always_lock_free = hamon::detail::atomic_is_always_lock_free<pointer_type>::value;

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.pointer]/5
	pointer_type fetch_add(hamon::ptrdiff_t operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.pointer]/6
		static_assert(hamon::is_object_v<hamon::remove_pointer_t<pointer_type>>, "");

		// [atomics.types.pointer]/7,8
		return hamon::detail::atomic_fetch_add(this->data(), operand, order);
	}

	constexpr pointer_type fetch_add(hamon::ptrdiff_t operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.pointer]/6
		static_assert(hamon::is_object_v<hamon::remove_pointer_t<pointer_type>>, "");

		// [atomics.types.pointer]/7,8
		return hamon::detail::atomic_fetch_add(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.pointer]/5
	pointer_type fetch_sub(hamon::ptrdiff_t operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.pointer]/6
		static_assert(hamon::is_object_v<hamon::remove_pointer_t<pointer_type>>, "");

		// [atomics.types.pointer]/7,8
		return hamon::detail::atomic_fetch_sub(this->data(), operand, order);
	}

	constexpr pointer_type fetch_sub(hamon::ptrdiff_t operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.pointer]/6
		static_assert(hamon::is_object_v<hamon::remove_pointer_t<pointer_type>>, "");

		// [atomics.types.pointer]/7,8
		return hamon::detail::atomic_fetch_sub(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.pointer]/5
	pointer_type fetch_max(pointer_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.pointer]/6
		static_assert(hamon::is_object_v<hamon::remove_pointer_t<pointer_type>>, "");

		// [atomics.types.pointer]/7,8
		return hamon::detail::atomic_fetch_max(this->data(), operand, order);
	}

	constexpr pointer_type fetch_max(pointer_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.pointer]/6
		static_assert(hamon::is_object_v<hamon::remove_pointer_t<pointer_type>>, "");

		// [atomics.types.pointer]/7,8
		return hamon::detail::atomic_fetch_max(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.pointer]/5
	pointer_type fetch_min(pointer_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.pointer]/6
		static_assert(hamon::is_object_v<hamon::remove_pointer_t<pointer_type>>, "");

		// [atomics.types.pointer]/7,8
		return hamon::detail::atomic_fetch_min(this->data(), operand, order);
	}

	constexpr pointer_type fetch_min(pointer_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.pointer]/6
		static_assert(hamon::is_object_v<hamon::remove_pointer_t<pointer_type>>, "");

		// [atomics.types.pointer]/7,8
		return hamon::detail::atomic_fetch_min(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.pointer]/11
	void store_add(hamon::ptrdiff_t operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.pointer]/12
		static_assert(hamon::is_object_v<hamon::remove_pointer_t<pointer_type>>, "");

		// [atomics.types.pointer]/13
		hamon::detail::atomic_store_add(this->data(), operand, order);
	}

	constexpr void store_add(hamon::ptrdiff_t operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.pointer]/12
		static_assert(hamon::is_object_v<hamon::remove_pointer_t<pointer_type>>, "");

		// [atomics.types.pointer]/13
		hamon::detail::atomic_store_add(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.pointer]/11
	void store_sub(hamon::ptrdiff_t operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.pointer]/12
		static_assert(hamon::is_object_v<hamon::remove_pointer_t<pointer_type>>, "");

		// [atomics.types.pointer]/13
		hamon::detail::atomic_store_sub(this->data(), operand, order);
	}

	constexpr void store_sub(hamon::ptrdiff_t operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.pointer]/12
		static_assert(hamon::is_object_v<hamon::remove_pointer_t<pointer_type>>, "");

		// [atomics.types.pointer]/13
		hamon::detail::atomic_store_sub(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.pointer]/11
	void store_max(pointer_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.pointer]/12
		static_assert(hamon::is_object_v<hamon::remove_pointer_t<pointer_type>>, "");

		// [atomics.types.pointer]/13
		hamon::detail::atomic_store_max(this->data(), operand, order);
	}

	constexpr void store_max(pointer_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.pointer]/12
		static_assert(hamon::is_object_v<hamon::remove_pointer_t<pointer_type>>, "");

		// [atomics.types.pointer]/13
		hamon::detail::atomic_store_max(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.pointer]/11
	void store_min(pointer_type operand, memory_order order = memory_order::seq_cst) volatile noexcept
	{
		// [atomics.types.pointer]/12
		static_assert(hamon::is_object_v<hamon::remove_pointer_t<pointer_type>>, "");

		// [atomics.types.pointer]/13
		hamon::detail::atomic_store_min(this->data(), operand, order);
	}

	constexpr void store_min(pointer_type operand, memory_order order = memory_order::seq_cst) noexcept
	{
		// [atomics.types.pointer]/12
		static_assert(hamon::is_object_v<hamon::remove_pointer_t<pointer_type>>, "");

		// [atomics.types.pointer]/13
		hamon::detail::atomic_store_min(this->data(), operand, order);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.memop]/1
	pointer_type operator++(int) volatile noexcept
	{
		// [atomics.types.memop]/2
		return fetch_add(1);
	}

	constexpr pointer_type operator++(int) noexcept
	{
		// [atomics.types.memop]/2
		return fetch_add(1);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.memop]/3
	pointer_type operator--(int) volatile noexcept
	{
		// [atomics.types.memop]/4
		return fetch_sub(1);
	}

	constexpr pointer_type operator--(int) noexcept
	{
		// [atomics.types.memop]/4
		return fetch_sub(1);
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.memop]/5
	pointer_type operator++() volatile noexcept
	{
		// [atomics.types.memop]/6
		return fetch_add(1) + 1;
	}

	constexpr pointer_type operator++() noexcept
	{
		// [atomics.types.memop]/6
		return fetch_add(1) + 1;
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.memop]/7
	pointer_type operator--() volatile noexcept
	{
		// [atomics.types.memop]/8
		return fetch_sub(1) - 1;
	}

	constexpr pointer_type operator--() noexcept
	{
		// [atomics.types.memop]/8
		return fetch_sub(1) - 1;
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.pointer]/15
	pointer_type operator+=(hamon::ptrdiff_t operand) volatile noexcept
	{
		// [atomics.types.pointer]/16
		return fetch_add(operand) + operand;
	}

	constexpr pointer_type operator+=(hamon::ptrdiff_t operand) noexcept
	{
		// [atomics.types.pointer]/16
		return fetch_add(operand) + operand;
	}

	template <bool B = is_always_lock_free, typename = hamon::enable_if_t<B>>	// [atomics.types.pointer]/15
	pointer_type operator-=(hamon::ptrdiff_t operand) volatile noexcept
	{
		// [atomics.types.pointer]/16
		return fetch_sub(operand) - operand;
	}

	constexpr pointer_type operator-=(hamon::ptrdiff_t operand) noexcept
	{
		// [atomics.types.pointer]/16
		return fetch_sub(operand) - operand;
	}
};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_BASE_POINTER_HPP
