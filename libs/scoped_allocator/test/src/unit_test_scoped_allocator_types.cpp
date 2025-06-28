/**
 *	@file	unit_test_scoped_allocator_types.cpp
 *
 *	@brief	types のテスト
 */

#include <hamon/scoped_allocator/scoped_allocator_adaptor.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/string.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>

namespace hamon_scoped_allocator_test
{

namespace types_test
{

template <typename T, bool POC, bool POM, bool POS, bool IAE>
class MyAlloc : public hamon::allocator<T>
{
public:
	using size_type = hamon::size_t;
	using difference_type = hamon::ptrdiff_t;
	using pointer = T*;
	using const_pointer = T const*;

	using propagate_on_container_copy_assignment = hamon::bool_constant<POC>;
	using propagate_on_container_move_assignment = hamon::bool_constant<POM>;
	using propagate_on_container_swap            = hamon::bool_constant<POS>;
	using is_always_equal                        = hamon::bool_constant<IAE>;
};

template <typename T>
class MyAlloc2 : public hamon::allocator<T>
{
public:
	using size_type = hamon::size_t;
	using difference_type = hamon::ptrdiff_t;
	using pointer = T*;
	using const_pointer = T const*;

};

GTEST_TEST(ScopedAllocatorTest, TypesTest)
{
	{
		using Alloc = MyAlloc<int, false, false, false, false>;
		using ScopedAlloc = hamon::scoped_allocator_adaptor<Alloc>;
		static_assert(hamon::is_same<typename ScopedAlloc::outer_allocator_type, Alloc>::value, "");
		static_assert(hamon::is_same<typename ScopedAlloc::inner_allocator_type, hamon::scoped_allocator_adaptor<Alloc>>::value, "");
		static_assert(hamon::is_same<typename ScopedAlloc::value_type,      typename Alloc::value_type>::value, "");
		static_assert(hamon::is_same<typename ScopedAlloc::size_type,       typename Alloc::size_type>::value, "");
		static_assert(hamon::is_same<typename ScopedAlloc::difference_type, typename Alloc::difference_type>::value, "");
		static_assert(hamon::is_same<typename ScopedAlloc::pointer,         typename Alloc::pointer>::value, "");
		static_assert(hamon::is_same<typename ScopedAlloc::const_pointer,   typename Alloc::const_pointer>::value, "");
		static_assert(hamon::is_same<typename ScopedAlloc::void_pointer,       void*>::value, "");
		static_assert(hamon::is_same<typename ScopedAlloc::const_void_pointer, void const*>::value, "");
		static_assert(!ScopedAlloc::propagate_on_container_copy_assignment::value, "");
		static_assert(!ScopedAlloc::propagate_on_container_move_assignment::value, "");
		static_assert(!ScopedAlloc::propagate_on_container_swap::value, "");
		static_assert(!ScopedAlloc::is_always_equal::value, "");
	}
	{
		using Alloc = MyAlloc<int, true, false, false, false>;
		using ScopedAlloc = hamon::scoped_allocator_adaptor<Alloc>;
		static_assert( ScopedAlloc::propagate_on_container_copy_assignment::value, "");
		static_assert(!ScopedAlloc::propagate_on_container_move_assignment::value, "");
		static_assert(!ScopedAlloc::propagate_on_container_swap::value, "");
		static_assert(!ScopedAlloc::is_always_equal::value, "");
	}
	{
		using Alloc = MyAlloc<int, false, true, false, false>;
		using ScopedAlloc = hamon::scoped_allocator_adaptor<Alloc>;
		static_assert(!ScopedAlloc::propagate_on_container_copy_assignment::value, "");
		static_assert( ScopedAlloc::propagate_on_container_move_assignment::value, "");
		static_assert(!ScopedAlloc::propagate_on_container_swap::value, "");
		static_assert(!ScopedAlloc::is_always_equal::value, "");
	}
	{
		using Alloc = MyAlloc<int, false, false, true, false>;
		using ScopedAlloc = hamon::scoped_allocator_adaptor<Alloc>;
		static_assert(!ScopedAlloc::propagate_on_container_copy_assignment::value, "");
		static_assert(!ScopedAlloc::propagate_on_container_move_assignment::value, "");
		static_assert( ScopedAlloc::propagate_on_container_swap::value, "");
		static_assert(!ScopedAlloc::is_always_equal::value, "");
	}
	{
		using Alloc = MyAlloc<int, false, false, false, true>;
		using ScopedAlloc = hamon::scoped_allocator_adaptor<Alloc>;
		static_assert(!ScopedAlloc::propagate_on_container_copy_assignment::value, "");
		static_assert(!ScopedAlloc::propagate_on_container_move_assignment::value, "");
		static_assert(!ScopedAlloc::propagate_on_container_swap::value, "");
		static_assert( ScopedAlloc::is_always_equal::value, "");
	}

	{
		using OuterAlloc = MyAlloc<hamon::string, false, false, false, false>;
		using InnerAlloc = MyAlloc<char, false, false, false, false>;
		using ScopedAlloc = hamon::scoped_allocator_adaptor<OuterAlloc, InnerAlloc>;
		static_assert(hamon::is_same<typename ScopedAlloc::outer_allocator_type, OuterAlloc>::value, "");
		static_assert(hamon::is_same<typename ScopedAlloc::inner_allocator_type, hamon::scoped_allocator_adaptor<InnerAlloc>>::value, "");
		static_assert(hamon::is_same<typename ScopedAlloc::value_type,      typename OuterAlloc::value_type>::value, "");
		static_assert(hamon::is_same<typename ScopedAlloc::size_type,       typename OuterAlloc::size_type>::value, "");
		static_assert(hamon::is_same<typename ScopedAlloc::difference_type, typename OuterAlloc::difference_type>::value, "");
		static_assert(hamon::is_same<typename ScopedAlloc::pointer,         typename OuterAlloc::pointer>::value, "");
		static_assert(hamon::is_same<typename ScopedAlloc::const_pointer,   typename OuterAlloc::const_pointer>::value, "");
		static_assert(hamon::is_same<typename ScopedAlloc::void_pointer,       void*>::value, "");
		static_assert(hamon::is_same<typename ScopedAlloc::const_void_pointer, void const*>::value, "");
		static_assert(!ScopedAlloc::propagate_on_container_copy_assignment::value, "");
		static_assert(!ScopedAlloc::propagate_on_container_move_assignment::value, "");
		static_assert(!ScopedAlloc::propagate_on_container_swap::value, "");
		static_assert(!ScopedAlloc::is_always_equal::value, "");
	}
	{
		using OuterAlloc = MyAlloc<hamon::string, true, true, true, true>;
		using InnerAlloc = MyAlloc<char, false, false, false, false>;
		using ScopedAlloc = hamon::scoped_allocator_adaptor<OuterAlloc, InnerAlloc>;
		static_assert(!ScopedAlloc::propagate_on_container_copy_assignment::value, "");
		static_assert(!ScopedAlloc::propagate_on_container_move_assignment::value, "");
		static_assert(!ScopedAlloc::propagate_on_container_swap::value, "");
		static_assert(!ScopedAlloc::is_always_equal::value, "");
	}
	{
		using OuterAlloc = MyAlloc<hamon::string, true, true, true, true>;
		using InnerAlloc = MyAlloc<char, true, false, false, false>;
		using ScopedAlloc = hamon::scoped_allocator_adaptor<OuterAlloc, InnerAlloc>;
		static_assert( ScopedAlloc::propagate_on_container_copy_assignment::value, "");
		static_assert(!ScopedAlloc::propagate_on_container_move_assignment::value, "");
		static_assert(!ScopedAlloc::propagate_on_container_swap::value, "");
		static_assert(!ScopedAlloc::is_always_equal::value, "");
	}
	{
		using OuterAlloc = MyAlloc<hamon::string, true, true, true, true>;
		using InnerAlloc = MyAlloc<char, false, true, false, false>;
		using ScopedAlloc = hamon::scoped_allocator_adaptor<OuterAlloc, InnerAlloc>;
		static_assert(!ScopedAlloc::propagate_on_container_copy_assignment::value, "");
		static_assert( ScopedAlloc::propagate_on_container_move_assignment::value, "");
		static_assert(!ScopedAlloc::propagate_on_container_swap::value, "");
		static_assert(!ScopedAlloc::is_always_equal::value, "");
	}
	{
		using OuterAlloc = MyAlloc<hamon::string, true, true, true, true>;
		using InnerAlloc = MyAlloc<char, false, false, true, false>;
		using ScopedAlloc = hamon::scoped_allocator_adaptor<OuterAlloc, InnerAlloc>;
		static_assert(!ScopedAlloc::propagate_on_container_copy_assignment::value, "");
		static_assert(!ScopedAlloc::propagate_on_container_move_assignment::value, "");
		static_assert( ScopedAlloc::propagate_on_container_swap::value, "");
		static_assert(!ScopedAlloc::is_always_equal::value, "");
	}
	{
		using OuterAlloc = MyAlloc<hamon::string, true, true, true, true>;
		using InnerAlloc = MyAlloc<char, false, false, false, true>;
		using ScopedAlloc = hamon::scoped_allocator_adaptor<OuterAlloc, InnerAlloc>;
		static_assert(!ScopedAlloc::propagate_on_container_copy_assignment::value, "");
		static_assert(!ScopedAlloc::propagate_on_container_move_assignment::value, "");
		static_assert(!ScopedAlloc::propagate_on_container_swap::value, "");
		static_assert( ScopedAlloc::is_always_equal::value, "");
	}
	{
		using OuterAlloc = MyAlloc<hamon::string, false, false, false, false>;
		using InnerAlloc = MyAlloc<char, true, true, true, true>;
		using ScopedAlloc = hamon::scoped_allocator_adaptor<OuterAlloc, InnerAlloc>;
		static_assert(!ScopedAlloc::propagate_on_container_copy_assignment::value, "");
		static_assert(!ScopedAlloc::propagate_on_container_move_assignment::value, "");
		static_assert(!ScopedAlloc::propagate_on_container_swap::value, "");
		static_assert(!ScopedAlloc::is_always_equal::value, "");
	}
}

}	// namespace types_test

}	// namespace hamon_scoped_allocator_test
