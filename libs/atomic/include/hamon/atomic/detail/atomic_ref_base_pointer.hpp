/**
 *	@file	atomic_ref_base_pointer.hpp
 *
 *	@brief	atomic_ref_base_pointer の定義
 */

#ifndef HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_POINTER_HPP
#define HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_POINTER_HPP

#include <hamon/atomic/memory_order.hpp>
#include <hamon/atomic/detail/atomic_is_always_lock_free.hpp>
#include <hamon/atomic/detail/atomic_required_alignment.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/copy_cv.hpp>
#include <hamon/type_traits/remove_cv.hpp>

namespace hamon
{
namespace detail
{

// 32.5.7.5 Specialization for pointers[atomics.ref.pointer]

template <typename T>
struct atomic_ref_base_pointer
{
private:
	using pointer_type = T*;

	pointer_type* ptr;

	using address_return_type = hamon::copy_cv_t<void, pointer_type>*;

public:
	using value_type = hamon::remove_cv_t<pointer_type>;
	using difference_type = hamon::ptrdiff_t;

	// [atomics.ref.ops]/1
	static constexpr hamon::size_t required_alignment = hamon::detail::atomic_required_alignment<pointer_type>::value;

	// [atomics.ref.ops]/3
	static constexpr bool is_always_lock_free = hamon::detail::atomic_is_always_lock_free<pointer_type>::value;

	// [atomics.ref.pointer]/3
	static_assert(is_always_lock_free || !hamon::is_volatile_v<pointer_type>, "");

	bool is_lock_free() const noexcept
	{
		// [atomics.ref.ops]/4
		return hamon::detail::atomic_is_lock_free<pointer_type>();
	}

	constexpr explicit atomic_ref_base_pointer(pointer_type& obj)
		// [atomics.ref.ops]/6
		: ptr(hamon::addressof(obj))
	{}

	explicit atomic_ref_base_pointer(pointer_type&&) = delete;

	constexpr atomic_ref_base_pointer(atomic_ref_base_pointer const& ref) noexcept
		// [atomics.ref.ops]/8
		: ptr(ref.ptr)
	{}

	template <typename U>
	constexpr atomic_ref_base_pointer(atomic_ref_base_pointer<U> const&) noexcept;

	atomic_ref_base_pointer& operator=(atomic_ref_base_pointer const&) = delete;

	constexpr void store(value_type, memory_order = memory_order::seq_cst) const noexcept;
	constexpr value_type operator=(value_type) const noexcept;
	constexpr value_type load(memory_order = memory_order::seq_cst) const noexcept;
	constexpr operator value_type() const noexcept;

	constexpr value_type exchange(value_type, memory_order = memory_order::seq_cst) const noexcept;
	constexpr bool compare_exchange_weak(value_type&, value_type, memory_order, memory_order) const noexcept;
	constexpr bool compare_exchange_strong(value_type&, value_type, memory_order, memory_order) const noexcept;
	constexpr bool compare_exchange_weak(value_type&, value_type, memory_order = memory_order::seq_cst) const noexcept;
	constexpr bool compare_exchange_strong(value_type&, value_type, memory_order = memory_order::seq_cst) const noexcept;

	constexpr value_type fetch_add(difference_type, memory_order = memory_order::seq_cst) const noexcept;
	constexpr value_type fetch_sub(difference_type, memory_order = memory_order::seq_cst) const noexcept;
	constexpr value_type fetch_max(value_type, memory_order = memory_order::seq_cst) const noexcept;
	constexpr value_type fetch_min(value_type, memory_order = memory_order::seq_cst) const noexcept;

	constexpr void store_add(difference_type, memory_order = memory_order::seq_cst) const noexcept;
	constexpr void store_sub(difference_type, memory_order = memory_order::seq_cst) const noexcept;
	constexpr void store_max(value_type, memory_order = memory_order::seq_cst) const noexcept;
	constexpr void store_min(value_type, memory_order = memory_order::seq_cst) const noexcept;

	constexpr value_type operator++(int) const noexcept;
	constexpr value_type operator--(int) const noexcept;
	constexpr value_type operator++() const noexcept;
	constexpr value_type operator--() const noexcept;
	constexpr value_type operator+=(difference_type) const noexcept;
	constexpr value_type operator-=(difference_type) const noexcept;

	constexpr void wait(value_type, memory_order = memory_order::seq_cst) const noexcept;
	constexpr void notify_one() const noexcept;
	constexpr void notify_all() const noexcept;

	constexpr address_return_type address() const noexcept;
};

}	// namespace detail
}	// namespace hamon

#endif // HAMON_ATOMIC_DETAIL_ATOMIC_REF_BASE_POINTER_HPP
