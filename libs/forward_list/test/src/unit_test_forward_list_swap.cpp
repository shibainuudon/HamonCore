/**
 *	@file	unit_test_forward_list_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	void swap(forward_list&)
 *		noexcept(allocator_traits<Allocator>::is_always_equal::value);
 *
 *	template<class T, class Allocator>
 *	void swap(forward_list<T, Allocator>& x, forward_list<T, Allocator>& y)
 *		noexcept(noexcept(x.swap(y)));
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace swap_test
{

#if !defined(HAMON_USE_STD_FORWARD_LIST) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// MSVCでconstexprにすると内部コンパイラエラーになってしまう TODO
#define FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FORWARD_LIST_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define FORWARD_LIST_TEST_CONSTEXPR             /**/
#endif

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
FORWARD_LIST_TEST_CONSTEXPR bool test1()
{
	using ForwardList = hamon::forward_list<T>;

	{
		ForwardList v;
		static_assert(hamon::is_same<decltype(v.swap(v)), void>::value, "");
		static_assert(hamon::is_same<decltype(swap(v, v)), void>::value, "");
		static_assert(noexcept(v.swap(v)), "");
		static_assert(noexcept(swap(v, v)), "");
	}
	{
		ForwardList v1{1,2,3};
		ForwardList v2{4,5};

		v1.swap(v2);
		{
			auto it = v1.begin();
			VERIFY(*it++ == 4);
			VERIFY(*it++ == 5);
			VERIFY(it == v1.end());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == 1);
			VERIFY(*it++ == 2);
			VERIFY(*it++ == 3);
			VERIFY(it == v2.end());
		}

		swap(v1, v2);
		{
			auto it = v1.begin();
			VERIFY(*it++ == 1);
			VERIFY(*it++ == 2);
			VERIFY(*it++ == 3);
			VERIFY(it == v1.end());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == 4);
			VERIFY(*it++ == 5);
			VERIFY(it == v2.end());
		}
	}

	return true;
}

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test2()
{
	using Allocator = MyAllocator<T>;
	using ForwardList = hamon::forward_list<T, Allocator>;

	{
		ForwardList v;
		static_assert(hamon::is_same<decltype(v.swap(v)), void>::value, "");
		static_assert(hamon::is_same<decltype(swap(v, v)), void>::value, "");
#if !defined(HAMON_USE_STD_FORWARD_LIST)
		static_assert(!noexcept(v.swap(v)), "");
		static_assert(!noexcept(swap(v, v)), "");
#endif
	}
	{
		Allocator alloc1{10};
		Allocator alloc2{20};
		ForwardList v1{{1,2}, alloc1};
		ForwardList v2{{3,4,5,6}, alloc2};
		VERIFY(v1.get_allocator().id == 10);
		VERIFY(v2.get_allocator().id == 20);

		v1.swap(v2);
		VERIFY(v1.get_allocator().id == 20);
		VERIFY(v2.get_allocator().id == 10);
		{
			auto it = v1.begin();
			VERIFY(*it++ == 3);
			VERIFY(*it++ == 4);
			VERIFY(*it++ == 5);
			VERIFY(*it++ == 6);
			VERIFY(it == v1.end());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == 1);
			VERIFY(*it++ == 2);
			VERIFY(it == v2.end());
		}

		swap(v1, v2);
		VERIFY(v1.get_allocator().id == 10);
		VERIFY(v2.get_allocator().id == 20);
		{
			auto it = v1.begin();
			VERIFY(*it++ == 1);
			VERIFY(*it++ == 2);
			VERIFY(it == v1.end());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == 3);
			VERIFY(*it++ == 4);
			VERIFY(*it++ == 5);
			VERIFY(*it++ == 6);
			VERIFY(it == v2.end());
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, SwapTest)
{
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());

	EXPECT_TRUE(test2<int>());
	EXPECT_TRUE(test2<char>());
	EXPECT_TRUE(test2<float>());
}

#undef FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef FORWARD_LIST_TEST_CONSTEXPR

}	// namespace swap_test

}	// namespace hamon_forward_list_test
