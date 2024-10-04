/**
 *	@file	unit_test_forward_list_ctor_n_value.cpp
 *
 *	@brief	要素数と値を引数に取るコンストラクタのテスト
 *
 *	forward_list(size_type n, const T& value, const Allocator& = Allocator());
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace ctor_n_value_test
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

struct S2
{
	int x;
	float y;
};

HAMON_CXX11_CONSTEXPR bool
operator==(S2 const& lhs, S2 const& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
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
FORWARD_LIST_TEST_CONSTEXPR bool test_impl(T const& value, Allocator const& alloc)
{
	using ForwardList = hamon::forward_list<T, Allocator>;
	using SizeType = typename ForwardList::size_type;

	static_assert( hamon::is_constructible<ForwardList, SizeType, T const&>::value, "");
	static_assert( hamon::is_constructible<ForwardList, SizeType, T const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<ForwardList, SizeType, T const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<ForwardList, SizeType, T const&, Allocator const&>::value, "");
//	static_assert( hamon::is_implicitly_constructible<ForwardList, SizeType, T const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<ForwardList, SizeType, T const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<ForwardList, SizeType, T const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<ForwardList, SizeType, T const&, Allocator const&>::value, "");

	{
		ForwardList v(3, value, alloc);
		VERIFY(v.get_allocator() == alloc);
		VERIFY(!v.empty());
		auto it = v.begin();
		VERIFY(*it++ == value);
		VERIFY(*it++ == value);
		VERIFY(*it++ == value);
		VERIFY(it == v.end());
	}
	{
		ForwardList v(0, value, alloc);
		VERIFY(v.get_allocator() == alloc);
		VERIFY(v.empty());
	}
	{
		ForwardList v(2, value);
		VERIFY(!v.empty());
		auto it = v.begin();
		VERIFY(*it++ == value);
		VERIFY(*it++ == value);
		VERIFY(it == v.end());
	}
	{
		ForwardList v(0, value);
		VERIFY(v.empty());
	}

	return true;
}

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test1(T const& value)
{
	hamon::allocator<T> alloc;
	VERIFY(test_impl<T>(value, alloc));
	return true;
}

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test2(T const& value)
{
	MyAllocator<T> alloc;
	VERIFY(test_impl<T>(value, alloc));
	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, CtorNValueTest)
{
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>(10));
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>(20));
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>(0.5f));
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<S1>(S1{10}));
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<S2>(S2{1,2}));

	EXPECT_TRUE(test2<int>(1));
	EXPECT_TRUE(test2<char>(2));
	EXPECT_TRUE(test2<float>(3));
	EXPECT_TRUE(test2<S1>(S1{4}));
	EXPECT_TRUE(test2<S2>(S2{5,6}));
}

#undef FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef FORWARD_LIST_TEST_CONSTEXPR

}	// namespace ctor_n_value_test

}	// namespace hamon_forward_list_test
