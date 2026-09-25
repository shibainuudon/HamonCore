/**
 *	@file	atomic_ref_base_pointer.hpp
 *
 *	@brief	atomic_ref_base_pointer の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_POINTER_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_POINTER_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/atomic_fetch_add.hpp>
#include <hamon/atomic/detail/atomic_fetch_max.hpp>
#include <hamon/atomic/detail/atomic_fetch_min.hpp>
#include <hamon/atomic/detail/atomic_fetch_sub.hpp>
#include <hamon/atomic/detail/atomic_store_add.hpp>
#include <hamon/atomic/detail/atomic_store_max.hpp>
#include <hamon/atomic/detail/atomic_store_min.hpp>
#include <hamon/atomic/detail/atomic_store_sub.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_const.hpp>
#include <hamon/type_traits/is_object.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/type_traits/remove_pointer.hpp>
#include <hamon/assert.hpp>

namespace hamon
{
namespace detail
{

// 32.5.7.5 Specialization for pointers[atomics.ref.pointer]

template <typename pointer_type>
struct atomic_ref_base_pointer
{
public:
	using value_type = hamon::remove_cv_t<pointer_type>;
	using difference_type = hamon::ptrdiff_t;

	template <typename U = pointer_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.pointer]/6
	constexpr value_type fetch_add(difference_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.pointer]/7
		static_assert(hamon::is_object_v<hamon::remove_pointer_t<pointer_type>>, "");

		// [atomics.ref.pointer]/8,9
		return hamon::detail::atomic_fetch_add(this->ptr, operand, order);
	}

	template <typename U = pointer_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.pointer]/6
	constexpr value_type fetch_sub(difference_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.pointer]/7
		static_assert(hamon::is_object_v<hamon::remove_pointer_t<pointer_type>>, "");

		// [atomics.ref.pointer]/8,9
		return hamon::detail::atomic_fetch_sub(this->ptr, operand, order);
	}

	template <typename U = pointer_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.pointer]/6
	constexpr value_type fetch_max(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.pointer]/7
		static_assert(hamon::is_object_v<hamon::remove_pointer_t<pointer_type>>, "");

		// [atomics.ref.pointer]/8,9,11
		return hamon::detail::atomic_fetch_max(this->ptr, operand, order);
	}

	template <typename U = pointer_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.pointer]/6
	constexpr value_type fetch_min(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.pointer]/7
		static_assert(hamon::is_object_v<hamon::remove_pointer_t<pointer_type>>, "");

		// [atomics.ref.pointer]/8,9,11
		return hamon::detail::atomic_fetch_min(this->ptr, operand, order);
	}

	template <typename U = pointer_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.pointer]/12
	constexpr void store_add(difference_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.pointer]/13
		static_assert(hamon::is_object_v<hamon::remove_pointer_t<pointer_type>>, "");

		// [atomics.ref.pointer]/14
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.ref.pointer]/15
		hamon::detail::atomic_store_add(this->ptr, operand, order);
	}

	template <typename U = pointer_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.pointer]/12
	constexpr void store_sub(difference_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.pointer]/13
		static_assert(hamon::is_object_v<hamon::remove_pointer_t<pointer_type>>, "");

		// [atomics.ref.pointer]/14
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.ref.pointer]/15
		hamon::detail::atomic_store_sub(this->ptr, operand, order);
	}

	template <typename U = pointer_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.pointer]/12
	constexpr void store_max(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.pointer]/13
		static_assert(hamon::is_object_v<hamon::remove_pointer_t<pointer_type>>, "");

		// [atomics.ref.pointer]/14
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.ref.pointer]/15
		hamon::detail::atomic_store_max(this->ptr, operand, order);
	}

	template <typename U = pointer_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.pointer]/12
	constexpr void store_min(value_type operand, memory_order order = memory_order::seq_cst) const noexcept
	{
		// [atomics.ref.pointer]/13
		static_assert(hamon::is_object_v<hamon::remove_pointer_t<pointer_type>>, "");

		// [atomics.ref.pointer]/14
		HAMON_ASSERT(
			order == memory_order::relaxed ||
			order == memory_order::release ||
			order == memory_order::seq_cst);

		// [atomics.ref.pointer]/15
		hamon::detail::atomic_store_min(this->ptr, operand, order);
	}

	template <typename U = pointer_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.memop]/2
	constexpr value_type operator++(int) const noexcept
	{
		// [atomics.ref.memop]/3
		return fetch_add(1);
	}

	template <typename U = pointer_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.memop]/4
	constexpr value_type operator--(int) const noexcept
	{
		// [atomics.ref.memop]/5
		return fetch_sub(1);
	}

	template <typename U = pointer_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.memop]/6
	constexpr value_type operator++() const noexcept
	{
		// [atomics.ref.memop]/7
		return fetch_add(1) + 1;
	}

	template <typename U = pointer_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.memop]/8
	constexpr value_type operator--() const noexcept
	{
		// [atomics.ref.memop]/9
		return fetch_sub(1) - 1;
	}

	template <typename U = pointer_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.pointer]/17
	constexpr value_type operator+=(difference_type operand) const noexcept
	{
		// [atomics.ref.pointer]/18
		return fetch_add(operand) + operand;
	}

	template <typename U = pointer_type, typename = hamon::enable_if_t<!hamon::is_const_v<U>>>	// [atomics.ref.pointer]/17
	constexpr value_type operator-=(difference_type operand) const noexcept
	{
		// [atomics.ref.pointer]/18
		return fetch_sub(operand) - operand;
	}

protected:
	constexpr atomic_ref_base_pointer(pointer_type* p)
		: ptr(const_cast<value_type*>(p))
	{}

	template <typename U>
	constexpr atomic_ref_base_pointer(atomic_ref_base_pointer<U> const& ref)
		: ptr(ref.ptr)
	{}

protected:
	value_type* ptr;

	template <typename>
	friend struct atomic_ref_base_pointer;
};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_POINTER_HPP
