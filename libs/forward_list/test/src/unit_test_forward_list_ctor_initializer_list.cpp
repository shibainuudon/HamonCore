﻿/**
 *	@file	unit_test_forward_list_ctor_initializer_list.cpp
 *
 *	@brief	initializer_listを引数に取るコンストラクタのテスト
 *
 *	forward_list(initializer_list<T>, const Allocator& = Allocator());
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace ctor_initializer_list_test
{

#if !defined(HAMON_USE_STD_FORWARD_LIST) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// MSVCでconstexprにすると内部コンパイラエラーになってしまう TODO
#define FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FORWARD_LIST_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define FORWARD_LIST_TEST_CONSTEXPR             /**/
#endif

struct S1
{
	int value;
};

HAMON_CXX11_CONSTEXPR bool
operator==(S1 const& lhs, S1 const& rhs)
{
	return lhs.value == rhs.value;
}

template <typename T>
struct MyAllocator
{
	using value_type = T;

	int id;

	MyAllocator() : id(13) {}

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
FORWARD_LIST_TEST_CONSTEXPR bool test_impl(Allocator const& alloc)
{
	using ForwardList = hamon::forward_list<T, Allocator>;

	static_assert( hamon::is_constructible<ForwardList, std::initializer_list<T>>::value, "");
	static_assert( hamon::is_constructible<ForwardList, std::initializer_list<T>, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<ForwardList, std::initializer_list<T>>::value, "");
	static_assert(!hamon::is_nothrow_constructible<ForwardList, std::initializer_list<T>, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<ForwardList, std::initializer_list<T>>::value, "");
	static_assert( hamon::is_implicitly_constructible<ForwardList, std::initializer_list<T>, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<ForwardList, std::initializer_list<T>>::value, "");
	static_assert(!hamon::is_trivially_constructible<ForwardList, std::initializer_list<T>, Allocator const&>::value, "");

	{
		ForwardList v = {T{1}, T{2}, T{3}};
		VERIFY(!v.empty());
		auto it = v.begin();
		VERIFY(*it++ == T{1});
		VERIFY(*it++ == T{2});
		VERIFY(*it++ == T{3});
		VERIFY(it == v.end());
	}
	{
		ForwardList v({T{3}, T{1}, T{4}, T{1}, T{5}}, alloc);
		VERIFY(v.get_allocator() == alloc);
		VERIFY(!v.empty());
		auto it = v.begin();
		VERIFY(*it++ == T{3});
		VERIFY(*it++ == T{1});
		VERIFY(*it++ == T{4});
		VERIFY(*it++ == T{1});
		VERIFY(*it++ == T{5});
		VERIFY(it == v.end());
	}
	{
		ForwardList v({});
		VERIFY(v.empty());
	}
	{
		ForwardList v({}, alloc);
		VERIFY(v.get_allocator() == alloc);
		VERIFY(v.empty());
	}

	return true;
}

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test1()
{
	hamon::allocator<T> alloc;
	VERIFY(test_impl<T>(alloc));
	return true;
}

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test2()
{
	MyAllocator<T> alloc;
	VERIFY(test_impl<T>(alloc));
	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, CtorInitializerListTest)
{
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<S1>());

	EXPECT_TRUE(test2<int>());
	EXPECT_TRUE(test2<char>());
	EXPECT_TRUE(test2<float>());
	EXPECT_TRUE(test2<S1>());
}

#undef FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef FORWARD_LIST_TEST_CONSTEXPR

}	// namespace ctor_initializer_list_test

}	// namespace hamon_forward_list_test
