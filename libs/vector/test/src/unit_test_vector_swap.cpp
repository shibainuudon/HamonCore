/**
 *	@file	unit_test_vector_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *  constexpr void swap(vector&)
 *    noexcept(allocator_traits<Allocator>::propagate_on_container_swap::value ||
 *             allocator_traits<Allocator>::is_always_equal::value);
 *
 *  template<class T, class Allocator>
 *  constexpr void swap(vector<T, Allocator>& x, vector<T, Allocator>& y)
 *    noexcept(noexcept(x.swap(y)));
 */

#include <hamon/vector.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_vector_test
{

namespace swap_test
{

template <typename T>
struct MyAllocator1
{
	using value_type = T;
	using is_always_equal = hamon::false_type;
	using propagate_on_container_swap = hamon::true_type;

	int id;

	MyAllocator1() : id(0) {}

	MyAllocator1(int i) : id(i) {}

	template <typename U>
	MyAllocator1(MyAllocator1<U> const& a) : id(a.id) {}

	T* allocate(hamon::size_t n)
	{
		return static_cast<T*>(::operator new(n * sizeof(T)));
	}

	void deallocate(T* p, hamon::size_t n)
	{
		// [allocator.members]/11
		::operator delete(p);
		(void)n;
	}

	bool operator==(MyAllocator1 const& rhs) const
	{
		return id == rhs.id;
	}

	bool operator!=(MyAllocator1 const& rhs) const
	{
		return id != rhs.id;
	}
};

template <typename T>
struct MyAllocator2
{
	using value_type = T;
	using is_always_equal = hamon::false_type;
	using propagate_on_container_swap = hamon::false_type;

	int id;

	MyAllocator2() : id(0) {}

	MyAllocator2(int i) : id(i) {}

	template <typename U>
	MyAllocator2(MyAllocator2<U> const& a) : id(a.id) {}

	T* allocate(hamon::size_t n)
	{
		return static_cast<T*>(::operator new(n * sizeof(T)));
	}

	void deallocate(T* p, hamon::size_t n)
	{
		// [allocator.members]/11
		::operator delete(p);
		(void)n;
	}

	bool operator==(MyAllocator2 const& rhs) const
	{
		return id == rhs.id;
	}

	bool operator!=(MyAllocator2 const& rhs) const
	{
		return id != rhs.id;
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test1()
{
	using Vector = hamon::vector<T>;

	{
		Vector v;
		static_assert(hamon::is_same<decltype(v.swap(v)), void>::value, "");
		static_assert(hamon::is_same<decltype(swap(v, v)), void>::value, "");
		static_assert(noexcept(v.swap(v)), "");
		static_assert(noexcept(swap(v, v)), "");
	}
	{
		Vector v1{1,2,3};
		Vector v2{4,5};
		VERIFY(v1.size() == 3);
		VERIFY(v2.size() == 2);

		v1.swap(v2);
		VERIFY(v1.size() == 2);
		VERIFY(v1[0] == 4);
		VERIFY(v1[1] == 5);
		VERIFY(v2.size() == 3);
		VERIFY(v2[0] == 1);
		VERIFY(v2[1] == 2);
		VERIFY(v2[2] == 3);

		swap(v1, v2);
		VERIFY(v1.size() == 3);
		VERIFY(v1[0] == 1);
		VERIFY(v1[1] == 2);
		VERIFY(v1[2] == 3);
		VERIFY(v2.size() == 2);
		VERIFY(v2[0] == 4);
		VERIFY(v2[1] == 5);
	}
	{
		Vector v1{42};
		Vector v2;
		VERIFY(v1.size() == 1);
		VERIFY(v2.size() == 0);

		v1.swap(v2);
		VERIFY(v1.size() == 0);
		VERIFY(v2.size() == 1);
		VERIFY(v2[0] == 42);

		swap(v1, v2);
		VERIFY(v1.size() == 1);
		VERIFY(v1[0] == 42);
		VERIFY(v2.size() == 0);
	}

	return true;
}

template <typename T>
bool test2()
{
	using Allocator = MyAllocator1<T>;
	using Vector = hamon::vector<T, Allocator>;

	{
		Vector v;
		static_assert(hamon::is_same<decltype(v.swap(v)), void>::value, "");
		static_assert(hamon::is_same<decltype(swap(v, v)), void>::value, "");
#if !defined(HAMON_USE_STD_VECTOR)
		static_assert( noexcept(v.swap(v)), "");
		static_assert( noexcept(swap(v, v)), "");
#endif
	}
	{
		Allocator alloc1{10};
		Allocator alloc2{20};
		Vector v1{{1,2}, alloc1};
		Vector v2{{3,4,5,6}, alloc2};
		VERIFY(v1.get_allocator().id == 10);
		VERIFY(v2.get_allocator().id == 20);
		VERIFY(v1.size() == 2);
		VERIFY(v2.size() == 4);

		v1.swap(v2);
		VERIFY(v1.get_allocator().id == 20);
		VERIFY(v2.get_allocator().id == 10);
		VERIFY(v1.size() == 4);
		VERIFY(v1[0] == 3);
		VERIFY(v1[1] == 4);
		VERIFY(v1[2] == 5);
		VERIFY(v1[3] == 6);
		VERIFY(v2.size() == 2);
		VERIFY(v2[0] == 1);
		VERIFY(v2[1] == 2);

		swap(v1, v2);
		VERIFY(v1.get_allocator().id == 10);
		VERIFY(v2.get_allocator().id == 20);
		VERIFY(v1.size() == 2);
		VERIFY(v1[0] == 1);
		VERIFY(v1[1] == 2);
		VERIFY(v2.size() == 4);
		VERIFY(v2[0] == 3);
		VERIFY(v2[1] == 4);
		VERIFY(v2[2] == 5);
		VERIFY(v2[3] == 6);
	}

	return true;
}

template <typename T>
bool test3()
{
	// 標準ライブラリの実装によっては、propagate_on_container_swap::valueがfalseのときにエラーになる
#if !defined(HAMON_USE_STD_VECTOR)
	using Allocator = MyAllocator2<T>;
	using Vector = hamon::vector<T, Allocator>;

	{
		Vector v;
		static_assert(hamon::is_same<decltype(v.swap(v)), void>::value, "");
		static_assert(hamon::is_same<decltype(swap(v, v)), void>::value, "");
		static_assert(!noexcept(v.swap(v)), "");
		static_assert(!noexcept(swap(v, v)), "");
	}
	{
		Allocator alloc1{10};
		Allocator alloc2{20};
		Vector v1{{1,2}, alloc1};
		Vector v2{{3,4,5,6}, alloc2};
		VERIFY(v1.get_allocator().id == 10);
		VERIFY(v2.get_allocator().id == 20);
		VERIFY(v1.size() == 2);
		VERIFY(v2.size() == 4);

		v1.swap(v2);
		VERIFY(v1.get_allocator().id == 10);
		VERIFY(v2.get_allocator().id == 20);
		VERIFY(v1.size() == 4);
		VERIFY(v1[0] == 3);
		VERIFY(v1[1] == 4);
		VERIFY(v1[2] == 5);
		VERIFY(v1[3] == 6);
		VERIFY(v2.size() == 2);
		VERIFY(v2[0] == 1);
		VERIFY(v2[1] == 2);

		swap(v1, v2);
		VERIFY(v1.get_allocator().id == 10);
		VERIFY(v2.get_allocator().id == 20);
		VERIFY(v1.size() == 2);
		VERIFY(v1[0] == 1);
		VERIFY(v1[1] == 2);
		VERIFY(v2.size() == 4);
		VERIFY(v2[0] == 3);
		VERIFY(v2[1] == 4);
		VERIFY(v2[2] == 5);
		VERIFY(v2[3] == 6);
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(VectorTest, SwapTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<float>());

	EXPECT_TRUE(test2<int>());
	EXPECT_TRUE(test2<char>());
	EXPECT_TRUE(test2<float>());

	EXPECT_TRUE(test3<int>());
	EXPECT_TRUE(test3<char>());
	EXPECT_TRUE(test3<float>());
}

}	// namespace swap_test

}	// namespace hamon_vector_test
