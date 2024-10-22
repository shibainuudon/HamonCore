/**
 *	@file	unit_test_list_get_allocator.cpp
 *
 *	@brief	get_allocator のテスト
 *
 *	allocator_type get_allocator() const noexcept;
 */

#include <hamon/list/list.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_list_test
{

namespace get_allocator_test
{

#if !defined(HAMON_USE_STD_LIST) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// VS2019でconstexprにすると内部コンパイラエラーになってしまう
#define LIST_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define LIST_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define LIST_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define LIST_TEST_CONSTEXPR             /**/
#endif

template <typename T>
struct MyAllocator
{
	using value_type = T;
	using is_always_equal = hamon::false_type;

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
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename Allocator>
LIST_TEST_CONSTEXPR bool test_impl(Allocator& alloc)
{
	using List = hamon::list<T, Allocator>;

	{
		List v;
		List const cv;
		static_assert(hamon::is_same<decltype(v.get_allocator()), Allocator>::value, "");
		static_assert(hamon::is_same<decltype(cv.get_allocator()), Allocator>::value, "");
		static_assert(noexcept(v.get_allocator()), "");
		static_assert(noexcept(cv.get_allocator()), "");
	}
	{
		List v(alloc);
		VERIFY(v.get_allocator() == alloc);
	}

	return true;
}

template <typename T>
LIST_TEST_CONSTEXPR bool test1()
{
	hamon::allocator<T> alloc;
	VERIFY(test_impl<T>(alloc));
	return true;
}

template <typename T>
LIST_TEST_CONSTEXPR bool test2()
{
	MyAllocator<T> alloc{42};
	VERIFY(test_impl<T>(alloc));
	return true;
}

#undef VERIFY

GTEST_TEST(ListTest, GetAllocatorTest)
{
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());

	EXPECT_TRUE(test2<int>());
	EXPECT_TRUE(test2<char>());
	EXPECT_TRUE(test2<float>());
}

#undef LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef LIST_TEST_CONSTEXPR

}	// namespace get_allocator_test

}	// namespace hamon_list_test
