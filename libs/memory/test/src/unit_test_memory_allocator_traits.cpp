/**
 *	@file	unit_test_memory_allocator_traits.cpp
 *
 *	@brief	allocator_traits のテスト
 */

#include <hamon/memory/allocator_traits.hpp>
#include <hamon/memory/allocation_result.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/cstddef.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_memory_test
{

namespace allocator_traits_test
{

struct MyAllocator1
{
	using value_type = int;

	template <typename>
	struct rebind
	{
		using other = MyAllocator1;
	};
};

template <typename T>
struct MyAllocator2
{
	using value_type = T;
	using pointer = char;
	using const_pointer = short;
	using void_pointer = long;
	using const_void_pointer = float;
	using difference_type = int;
	using size_type = unsigned int;
	using propagate_on_container_copy_assignment = hamon::true_type;
	using propagate_on_container_move_assignment = hamon::false_type;
	using propagate_on_container_swap = hamon::true_type;
	using is_always_equal = hamon::false_type;
};

template <typename T>
struct MyAllocator3
{
	using value_type = T;

	value_type		m_value{};
	hamon::size_t	m_size{};

	HAMON_CXX14_CONSTEXPR T* allocate(hamon::size_t n)
	{
		m_size += n;
		return &m_value;
	}

	HAMON_CXX14_CONSTEXPR void deallocate(T* p, hamon::size_t n) HAMON_NOEXCEPT
	{
		m_size -= n;
		(void)p;
	}
};

template <typename T>
struct MyAllocator4
{
	using value_type = T;

	value_type		m_value{};
	hamon::size_t	m_size{};

	HAMON_CXX14_CONSTEXPR T* allocate(hamon::size_t n)
	{
		m_size += n;
		return &m_value;
	}

	HAMON_CXX14_CONSTEXPR T* allocate(hamon::size_t n, const void*)
	{
		m_size += n;
		return &m_value;
	}

	HAMON_CXX14_CONSTEXPR hamon::allocation_result<T*, hamon::size_t> allocate_at_least(hamon::size_t n)
	{
		m_size += n;
		return {&m_value, n};
	}

	HAMON_CXX14_CONSTEXPR void deallocate(T* p, hamon::size_t n) HAMON_NOEXCEPT
	{
		m_size -= n;
		(void)p;
	}

	HAMON_CXX14_CONSTEXPR void construct(T* p, int v)
	{
		(void)p;
		m_value = v;
	}

	HAMON_CXX14_CONSTEXPR void destroy(T* p)
	{
		(void)p;
		m_value = 0;
	}

	HAMON_CXX11_CONSTEXPR hamon::size_t max_size() const { return 1; }

	HAMON_CXX14_CONSTEXPR MyAllocator4 select_on_container_copy_construction() const { return {}; }
};

template <typename T>
struct MyAllocator5
{
	using value_type = T;

	HAMON_CXX14_CONSTEXPR T* allocate(hamon::size_t n)
	{
		return static_cast<T*>(::operator new(sizeof(T) * n));
	}

	HAMON_CXX14_CONSTEXPR void deallocate(T* p, hamon::size_t n) HAMON_NOEXCEPT
	{
		(void)n;
		::operator delete(p);
	}
};

struct S
{
	int m_value;

	HAMON_CXX11_CONSTEXPR S() : m_value(0) {}
	HAMON_CXX11_CONSTEXPR S(int) : m_value(1) {}
	HAMON_CXX11_CONSTEXPR S(int, int, int) : m_value(3) {}
	HAMON_CXX20_CONSTEXPR ~S() { m_value = -1; }
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool allocate_deallocate_test()
{
	// allocate(Alloc& a, size_type n);
	{
		using Allocator = MyAllocator3<int>;
		using Traits = hamon::allocator_traits<Allocator>;
		Allocator alloc;
		hamon::size_t const size = 3;
		auto p = Traits::allocate(alloc, size);
		VERIFY(p == &alloc.m_value);
		VERIFY(alloc.m_size == size);
		Traits::deallocate(alloc, p, size);
		VERIFY(alloc.m_size == 0);
	}

	// allocate(Alloc& a, size_type n, const_void_pointer hint);
	{
		using Allocator = MyAllocator3<int>;
		using Traits = hamon::allocator_traits<Allocator>;
		Allocator alloc;
		hamon::size_t const size = 4;
		const void* hint = nullptr;
		auto p = Traits::allocate(alloc, size, hint);
		VERIFY(p == &alloc.m_value);
		VERIFY(alloc.m_size == size);
		Traits::deallocate(alloc, p, size);
		VERIFY(alloc.m_size == 0);
	}
	{
		using Allocator = MyAllocator4<int>;
		using Traits = hamon::allocator_traits<Allocator>;
		Allocator alloc;
		hamon::size_t const size = 4;
		const void* hint = nullptr;
		auto p = Traits::allocate(alloc, size, hint);
		VERIFY(p == &alloc.m_value);
		VERIFY(alloc.m_size == size);
		Traits::deallocate(alloc, p, size);
		VERIFY(alloc.m_size == 0);
	}

	// allocate_at_least(Alloc& a, size_type n);
	{
		using Allocator = MyAllocator3<int>;
		using Traits = hamon::allocator_traits<Allocator>;
		Allocator alloc;
		hamon::size_t const size = 5;
		auto ret = Traits::allocate_at_least(alloc, size);
		VERIFY(ret.ptr == &alloc.m_value);
		VERIFY(ret.count == size);
		VERIFY(alloc.m_size == size);
		Traits::deallocate(alloc, ret.ptr, size);
		VERIFY(alloc.m_size == 0);
	}
	{
		using Allocator = MyAllocator4<int>;
		using Traits = hamon::allocator_traits<Allocator>;
		Allocator alloc;
		hamon::size_t const size = 5;
		auto ret = Traits::allocate_at_least(alloc, size);
		VERIFY(ret.ptr == &alloc.m_value);
		VERIFY(ret.count == size);
		VERIFY(alloc.m_size == size);
		Traits::deallocate(alloc, ret.ptr, size);
		VERIFY(alloc.m_size == 0);
	}

	return true;
}

HAMON_CXX14_CONSTEXPR bool construct_destroy_test()
{
	{
		using Allocator = MyAllocator4<int>;
		using Traits = hamon::allocator_traits<Allocator>;
		Allocator alloc;
		int* p = nullptr;
		Traits::construct(alloc, p, 42);
		VERIFY(alloc.m_value == 42);
		Traits::destroy(alloc, p);
		VERIFY(alloc.m_value == 0);
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool max_size_test()
{
	{
		using Allocator = MyAllocator3<int>;
		using Traits = hamon::allocator_traits<Allocator>;
		Allocator alloc;
		VERIFY(Traits::max_size(alloc) == std::numeric_limits<hamon::size_t>::max() / sizeof(int));
	}
	{
		using Allocator = MyAllocator4<int>;
		using Traits = hamon::allocator_traits<Allocator>;
		Allocator alloc;
		VERIFY(Traits::max_size(alloc) == 1);
	}
	return true;
}

HAMON_CXX14_CONSTEXPR bool select_on_container_copy_construction_test()
{
	{
		using Allocator = MyAllocator3<int>;
		using Traits = hamon::allocator_traits<Allocator>;
		Allocator alloc;
		hamon::size_t const size = 2;
		auto p = Traits::allocate(alloc, size);
		auto a2 = Traits::select_on_container_copy_construction(alloc);
		VERIFY(a2.m_size == alloc.m_size);
		Traits::deallocate(alloc, p, size);
	}
	{
		using Allocator = MyAllocator4<int>;
		using Traits = hamon::allocator_traits<Allocator>;
		Allocator alloc;
		hamon::size_t const size = 2;
		auto p = Traits::allocate(alloc, size);
		auto a2 = Traits::select_on_container_copy_construction(alloc);
		VERIFY(a2.m_size == 0);
		Traits::deallocate(alloc, p, size);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(MemoryTest, AllocatorTraitsTest)
{
	using Traits1 = hamon::allocator_traits<MyAllocator1>;
	using Traits2 = hamon::allocator_traits<MyAllocator2<int>>;

	// allocator_type
	static_assert(hamon::is_same<Traits1::allocator_type, MyAllocator1>::value, "");
	static_assert(hamon::is_same<Traits2::allocator_type, MyAllocator2<int>>::value, "");

	// value_type
	static_assert(hamon::is_same<Traits1::value_type, int>::value, "");
	static_assert(hamon::is_same<Traits2::value_type, int>::value, "");

	// pointer
	static_assert(hamon::is_same<Traits1::pointer, int*>::value, "");
	static_assert(hamon::is_same<Traits2::pointer, char>::value, "");

	// const_pointer
	static_assert(hamon::is_same<Traits1::const_pointer, const int*>::value, "");
	static_assert(hamon::is_same<Traits2::const_pointer, short>::value, "");

	// void_pointer
	static_assert(hamon::is_same<Traits1::void_pointer, void*>::value, "");
	static_assert(hamon::is_same<Traits2::void_pointer, long>::value, "");

	// const_void_pointer
	static_assert(hamon::is_same<Traits1::const_void_pointer, const void*>::value, "");
	static_assert(hamon::is_same<Traits2::const_void_pointer, float>::value, "");

	// difference_type
	static_assert(hamon::is_same<Traits1::difference_type, hamon::ptrdiff_t>::value, "");
	static_assert(hamon::is_same<Traits2::difference_type, int>::value, "");

	// size_type
	static_assert(hamon::is_same<Traits1::size_type, hamon::size_t>::value, "");
	static_assert(hamon::is_same<Traits2::size_type, unsigned int>::value, "");

	// propagate_on_container_copy_assignment
	static_assert(hamon::is_same<Traits1::propagate_on_container_copy_assignment, hamon::false_type>::value, "");
	static_assert(hamon::is_same<Traits2::propagate_on_container_copy_assignment, hamon::true_type>::value, "");

	// propagate_on_container_move_assignment
	static_assert(hamon::is_same<Traits1::propagate_on_container_move_assignment, hamon::false_type>::value, "");
	static_assert(hamon::is_same<Traits2::propagate_on_container_move_assignment, hamon::false_type>::value, "");

	// propagate_on_container_swap
	static_assert(hamon::is_same<Traits1::propagate_on_container_swap, hamon::false_type>::value, "");
	static_assert(hamon::is_same<Traits2::propagate_on_container_swap, hamon::true_type>::value, "");

	// is_always_equal
	static_assert(hamon::is_same<Traits1::is_always_equal, hamon::true_type>::value, "");
	static_assert(hamon::is_same<Traits2::is_always_equal, hamon::false_type>::value, "");

	// rebind_alloc
	static_assert(hamon::is_same<Traits1::template rebind_alloc<float>, MyAllocator1>::value, "");
	static_assert(hamon::is_same<Traits2::template rebind_alloc<float>, MyAllocator2<float>>::value, "");

	// rebind_traits
	static_assert(hamon::is_same<Traits1::template rebind_traits<float>, hamon::allocator_traits<MyAllocator1>>::value, "");
	static_assert(hamon::is_same<Traits2::template rebind_traits<float>, hamon::allocator_traits<MyAllocator2<float>>>::value, "");

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(allocate_deallocate_test());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(construct_destroy_test());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(max_size_test());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(select_on_container_copy_construction_test());

	{
		using Allocator = MyAllocator5<S>;
		using Traits = hamon::allocator_traits<Allocator>;
		Allocator alloc;
		auto p = Traits::allocate(alloc, 1);
		Traits::construct(alloc, p, 0);
		EXPECT_EQ(p->m_value, 1);
		Traits::destroy(alloc, p);
		Traits::deallocate(alloc, p, 1);
	}
}

}	// namespace allocator_traits_test

}	// namespace hamon_memory_test
