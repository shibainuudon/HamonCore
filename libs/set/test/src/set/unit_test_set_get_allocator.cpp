﻿/**
 *	@file	unit_test_set_get_allocator.cpp
 *
 *	@brief	get_allocator のテスト
 *
 *	allocator_type get_allocator() const noexcept;
 */

#include <hamon/set/set.hpp>
#include <hamon/functional.hpp>
#include <hamon/memory.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_set_test
{

namespace get_allocator_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
#endif

template <typename T>
struct MyAllocator
{
	using value_type = T;

	int id;

	HAMON_CXX11_CONSTEXPR
	MyAllocator(int i) : id(i) {}

	template <typename U>
	HAMON_CXX11_CONSTEXPR
	MyAllocator(MyAllocator<U> const& a) : id(a.id) {}

	HAMON_CXX20_CONSTEXPR
	T* allocate(hamon::size_t n)
	{
		return static_cast<T*>(::operator new(n * sizeof(T)));
	}

	HAMON_CXX20_CONSTEXPR
	void deallocate(T* p, hamon::size_t n)
	{
		// [allocator.members]/11
		::operator delete(p);
		(void)n;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator==(MyAllocator const& rhs) const
	{
		return id == rhs.id;
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename Allocator>
SET_TEST_CONSTEXPR bool test_impl(Allocator const& alloc)
{
	using Set = hamon::set<Key, hamon::less<>, Allocator>;

	{
		Set v(alloc);
		static_assert(hamon::is_same<decltype(v.get_allocator()), Allocator>::value, "");
		static_assert(noexcept(v.get_allocator()), "");
		VERIFY(v.get_allocator() == alloc);
	}
	{
		Set const v(alloc);
		static_assert(hamon::is_same<decltype(v.get_allocator()), Allocator>::value, "");
		static_assert(noexcept(v.get_allocator()), "");
		VERIFY(v.get_allocator() == alloc);
	}

	return true;
}

template <typename Key>
SET_TEST_CONSTEXPR bool test1()
{
	hamon::allocator<Key> alloc;
	VERIFY(test_impl<Key>(alloc));

	return true;
}

template <typename Key>
SET_TEST_CONSTEXPR bool test2()
{
	MyAllocator<Key> alloc{42};
	VERIFY(test_impl<Key>(alloc));

	return true;
}

#undef VERIFY

GTEST_TEST(SetTest, GetAllocatorTest)
{
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	SET_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());

	EXPECT_TRUE(test2<int>());
	EXPECT_TRUE(test2<char>());
	EXPECT_TRUE(test2<float>());
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace get_allocator_test

}	// namespace hamon_set_test