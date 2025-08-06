/**
 *	@file	hive_test_helper.hpp
 *
 *	@brief
 */

#ifndef HAMON_HIVE_TEST_HELPER_HPP
#define HAMON_HIVE_TEST_HELPER_HPP

#include <hamon/memory.hpp>
#include <hamon/config.hpp>

namespace hamon_hive_test
{

// is_always_equal == true_type なアロケータ
template <typename T>
struct TestAllocator1
{
	using value_type = T;

	HAMON_CXX11_CONSTEXPR
	TestAllocator1() {}

	explicit HAMON_CXX11_CONSTEXPR
	TestAllocator1(int) {}

	template <typename U>
	HAMON_CXX11_CONSTEXPR
	TestAllocator1(TestAllocator1<U> const&) {}

	HAMON_CXX20_CONSTEXPR
	T* allocate(hamon::size_t n)
	{
		return std::allocator<T>{}.allocate(n);
	}

	HAMON_CXX20_CONSTEXPR
	void deallocate(T* p, hamon::size_t n)
	{
		std::allocator<T>{}.deallocate(p, n);
	}

	HAMON_CXX11_CONSTEXPR
	bool operator==(TestAllocator1 const&) const
	{
		return true;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator!=(TestAllocator1 const&) const
	{
		return false;
	}
};

// is_always_equal == false_type なアロケータ
template <typename T>
struct TestAllocator2
{
	using value_type = T;
	using is_always_equal = std::false_type;
	using propagate_on_container_copy_assignment = std::true_type;
	using propagate_on_container_move_assignment = std::true_type;
	using propagate_on_container_swap = std::true_type;

	int id;

	HAMON_CXX11_CONSTEXPR
	TestAllocator2() : id(0) {}

	explicit HAMON_CXX11_CONSTEXPR
	TestAllocator2(int i) : id(i) {}

	template <typename U>
	HAMON_CXX11_CONSTEXPR
	TestAllocator2(TestAllocator2<U> const& a) : id(a.id) {}

	HAMON_CXX20_CONSTEXPR
	T* allocate(hamon::size_t n)
	{
		return std::allocator<T>{}.allocate(n);
	}

	HAMON_CXX20_CONSTEXPR
	void deallocate(T* p, hamon::size_t n)
	{
		std::allocator<T>{}.deallocate(p, n);
	}

	HAMON_CXX11_CONSTEXPR
	bool operator==(TestAllocator2 const& rhs) const
	{
		return id == rhs.id;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator!=(TestAllocator2 const& rhs) const
	{
		return id != rhs.id;
	}
};

// is_always_equal == false_type かつ、
// select_on_container_copy_construction で伝播しないアロケータ
template <typename T>
struct TestAllocator3
{
	using value_type = T;
	using is_always_equal = std::false_type;

	int id;

	HAMON_CXX11_CONSTEXPR
	TestAllocator3() : id(0) {}

	explicit HAMON_CXX11_CONSTEXPR
	TestAllocator3(int i) : id(i) {}

	template <typename U>
	HAMON_CXX11_CONSTEXPR
	TestAllocator3(TestAllocator3<U> const& a) : id(a.id) {}

	HAMON_CXX20_CONSTEXPR
	T* allocate(hamon::size_t n)
	{
		return std::allocator<T>{}.allocate(n);
	}

	HAMON_CXX20_CONSTEXPR
	void deallocate(T* p, hamon::size_t n)
	{
		std::allocator<T>{}.deallocate(p, n);
	}

	HAMON_CXX11_CONSTEXPR
	bool operator==(TestAllocator3 const& rhs) const
	{
		return id == rhs.id;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator!=(TestAllocator3 const& rhs) const
	{
		return id != rhs.id;
	}

	HAMON_CXX11_CONSTEXPR TestAllocator3
	select_on_container_copy_construction() const noexcept
	{
		// don't propagate on copy
		return TestAllocator3{0};
	}
};

// is_always_equal == false_type
// propagate_on_container_copy_assignment == true_type
// propagate_on_container_move_assignment == false_type なアロケータ
template <typename T>
struct TestAllocator4
{
	using value_type = T;
	using is_always_equal = std::false_type;
	using propagate_on_container_copy_assignment = std::true_type;
	using propagate_on_container_move_assignment = std::false_type;

	int id;

	HAMON_CXX11_CONSTEXPR
	TestAllocator4() : id(0) {}

	explicit HAMON_CXX11_CONSTEXPR
	TestAllocator4(int i) : id(i) {}

	template <typename U>
	HAMON_CXX11_CONSTEXPR
	TestAllocator4(TestAllocator4<U> const& a) : id(a.id) {}

	HAMON_CXX20_CONSTEXPR
	T* allocate(hamon::size_t n)
	{
		return std::allocator<T>{}.allocate(n);
	}

	HAMON_CXX20_CONSTEXPR
	void deallocate(T* p, hamon::size_t n)
	{
		std::allocator<T>{}.deallocate(p, n);
	}

	HAMON_CXX11_CONSTEXPR
	bool operator==(TestAllocator4 const& rhs) const
	{
		return id == rhs.id;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator!=(TestAllocator4 const& rhs) const
	{
		return id != rhs.id;
	}
};

// is_always_equal == false_type
// propagate_on_container_copy_assignment == false_type
// propagate_on_container_move_assignment == true_type なアロケータ
template <typename T>
struct TestAllocator5
{
	using value_type = T;
	using is_always_equal = std::false_type;
	using propagate_on_container_copy_assignment = std::false_type;
	using propagate_on_container_move_assignment = std::true_type;

	int id;

	HAMON_CXX11_CONSTEXPR
	TestAllocator5() : id(0) {}

	explicit HAMON_CXX11_CONSTEXPR
	TestAllocator5(int i) : id(i) {}

	template <typename U>
	HAMON_CXX11_CONSTEXPR
	TestAllocator5(TestAllocator5<U> const& a) : id(a.id) {}

	HAMON_CXX20_CONSTEXPR
	T* allocate(hamon::size_t n)
	{
		return std::allocator<T>{}.allocate(n);
	}

	HAMON_CXX20_CONSTEXPR
	void deallocate(T* p, hamon::size_t n)
	{
		std::allocator<T>{}.deallocate(p, n);
	}

	HAMON_CXX11_CONSTEXPR
	bool operator==(TestAllocator5 const& rhs) const
	{
		return id == rhs.id;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator!=(TestAllocator5 const& rhs) const
	{
		return id != rhs.id;
	}
};

// is_always_equal == false_type
// propagate_on_container_swap == false_type なアロケータ
template <typename T>
struct TestAllocator6
{
	using value_type = T;
	using is_always_equal = std::false_type;
	using propagate_on_container_swap = std::false_type;

	int id;

	HAMON_CXX11_CONSTEXPR
	TestAllocator6() : id(0) {}

	explicit HAMON_CXX11_CONSTEXPR
	TestAllocator6(int i) : id(i) {}

	template <typename U>
	HAMON_CXX11_CONSTEXPR
	TestAllocator6(TestAllocator6<U> const& a) : id(a.id) {}

	HAMON_CXX20_CONSTEXPR
	T* allocate(hamon::size_t n)
	{
		return std::allocator<T>{}.allocate(n);
	}

	HAMON_CXX20_CONSTEXPR
	void deallocate(T* p, hamon::size_t n)
	{
		std::allocator<T>{}.deallocate(p, n);
	}

	HAMON_CXX11_CONSTEXPR
	bool operator==(TestAllocator6 const& rhs) const
	{
		return id == rhs.id;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator!=(TestAllocator6 const& rhs) const
	{
		return id != rhs.id;
	}
};

#if !defined(HAMON_NO_EXCEPTIONS)

template <typename T>
struct ThrowAllocator
{
	using value_type = T;

	int* throw_after;

	HAMON_CXX11_CONSTEXPR
	ThrowAllocator() : throw_after(nullptr) {}

	explicit HAMON_CXX11_CONSTEXPR
	ThrowAllocator(int* x) : throw_after(x) {}

	template <typename U>
	HAMON_CXX11_CONSTEXPR
	ThrowAllocator(ThrowAllocator<U> const& x) : throw_after(x.throw_after) {}

	HAMON_CXX20_CONSTEXPR
	T* allocate(hamon::size_t n)
	{
		if (throw_after != nullptr)
		{
			--(*throw_after);
			if (*throw_after <= 0)
			{
				throw std::bad_alloc();
			}
		}

		return std::allocator<T>{}.allocate(n);
	}

	HAMON_CXX20_CONSTEXPR
	void deallocate(T* p, hamon::size_t n)
	{
		std::allocator<T>{}.deallocate(p, n);
	}

	HAMON_CXX11_CONSTEXPR
	bool operator==(ThrowAllocator const& rhs) const
	{
		return throw_after == rhs.throw_after;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator!=(ThrowAllocator const& rhs) const
	{
		return !(*this == rhs);
	}
};

#endif

}	// namespace hamon_hive_test

#endif // HAMON_HIVE_TEST_HELPER_HPP
