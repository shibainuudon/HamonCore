/**
 *	@file	unit_test_deque_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *  void swap(deque&)
 *		noexcept(allocator_traits<Allocator>::is_always_equal::value);
 *
 *  template<class T, class Allocator>
 *	void swap(deque<T, Allocator>& x, deque<T, Allocator>& y)
 *		noexcept(noexcept(x.swap(y)));
 */

#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_deque_test
{

namespace swap_test
{

template <typename T>
struct MyAllocator
{
	using value_type = T;
	using is_always_equal = hamon::false_type;
	using propagate_on_container_swap = hamon::true_type;

	int id;

	MyAllocator() : id(0) {}

	MyAllocator(int i) : id(i) {}

	template <typename U>
	MyAllocator(MyAllocator<U> const& a) : id(a.id) {}

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

	bool operator==(MyAllocator const& rhs) const
	{
		return id == rhs.id;
	}

	bool operator!=(MyAllocator const& rhs) const
	{
		return id != rhs.id;
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test1()
{
	using Deque = hamon::deque<T>;

	static_assert(hamon::is_same<
		decltype(hamon::declval<Deque&>().swap(hamon::declval<Deque&>())),
		void
	>::value, "");
	static_assert(hamon::is_same<
		decltype(swap(hamon::declval<Deque&>(), hamon::declval<Deque&>())),
		void
	>::value, "");

	static_assert(noexcept(
		hamon::declval<Deque&>().swap(hamon::declval<Deque&>())), "");
	static_assert(noexcept(
		swap(hamon::declval<Deque&>(), hamon::declval<Deque&>())), "");

	{
		Deque v1 {1,2,3};
		Deque v2 {11,12,13,14};
		VERIFY(v1.size() == 3);
		VERIFY(v1[0] == 1);
		VERIFY(v1[1] == 2);
		VERIFY(v1[2] == 3);
		VERIFY(v2.size() == 4);
		VERIFY(v2[0] == 11);
		VERIFY(v2[1] == 12);
		VERIFY(v2[2] == 13);
		VERIFY(v2[3] == 14);

		v1.swap(v2);
		VERIFY(v1.size() == 4);
		VERIFY(v1[0] == 11);
		VERIFY(v1[1] == 12);
		VERIFY(v1[2] == 13);
		VERIFY(v1[3] == 14);
		VERIFY(v2.size() == 3);
		VERIFY(v2[0] == 1);
		VERIFY(v2[1] == 2);
		VERIFY(v2[2] == 3);

		swap(v1, v2);
		VERIFY(v1.size() == 3);
		VERIFY(v1[0] == 1);
		VERIFY(v1[1] == 2);
		VERIFY(v1[2] == 3);
		VERIFY(v2.size() == 4);
		VERIFY(v2[0] == 11);
		VERIFY(v2[1] == 12);
		VERIFY(v2[2] == 13);
		VERIFY(v2[3] == 14);
	}
	return true;
}

template <typename T>
bool test2()
{
	using Allocator = MyAllocator<T>;
	using Deque = hamon::deque<T, Allocator>;

	{
		Deque v;
		static_assert(hamon::is_same<decltype(v.swap(v)), void>::value, "");
		static_assert(hamon::is_same<decltype(swap(v, v)), void>::value, "");
#if !defined(HAMON_USE_STD_DEQUE)
		static_assert(!noexcept(v.swap(v)), "");
		static_assert(!noexcept(swap(v, v)), "");
#endif
	}
	{
		Allocator alloc1{10};
		Allocator alloc2{20};
		Deque v1{{1,2}, alloc1};
		Deque v2{{3,4,5,6}, alloc2};
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

#undef VERIFY

GTEST_TEST(DequeTest, SwapTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<double>());

	EXPECT_TRUE(test2<int>());
	EXPECT_TRUE(test2<char>());
	EXPECT_TRUE(test2<float>());
}

}	// namespace swap_test

}	// namespace hamon_deque_test
