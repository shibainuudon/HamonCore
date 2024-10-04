/**
 *	@file	unit_test_forward_list_ctor_allocator.cpp
 *
 *	@brief	Allocatorを引数に取るコンストラクタのテスト
 *
 *	explicit forward_list(const Allocator&);
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace ctor_allocator_test
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
	S1() = delete;
};

struct S2
{
	S2() {}
};

struct S3
{
	int x;
	float y;
};

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

template <typename T, typename Allocator>
FORWARD_LIST_TEST_CONSTEXPR bool test1(Allocator const& alloc)
{
	{
		using ForwardList = hamon::forward_list<T, Allocator>;

		static_assert( hamon::is_constructible<ForwardList, Allocator const&>::value, "");
#if !defined(HAMON_USE_STD_FORWARD_LIST)
		static_assert( hamon::is_nothrow_constructible<ForwardList, Allocator const&>::value, "");
#endif
		static_assert(!hamon::is_implicitly_constructible<ForwardList, Allocator const&>::value, "");
		static_assert(!hamon::is_trivially_constructible<ForwardList, Allocator const&>::value, "");

		{
			ForwardList v(alloc);
			VERIFY(v.empty());
			VERIFY(v.get_allocator() == alloc);
		}
		{
			ForwardList v{alloc};
			VERIFY(v.empty());
			VERIFY(v.get_allocator() == alloc);
		}
		//{
		//	ForwardList v = {alloc};	// explicit指定されているので、これはできない
		//	VERIFY(v.empty());
		//	VERIFY(v.get_allocator() == alloc);
		//}
	}
	return true;
}

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test()
{
	{
		hamon::allocator<T> alloc;
		VERIFY(test1<T>(alloc));
	}
	{
		MyAllocator<T> alloc{42};
		VERIFY(test1<T>(alloc));
	}
	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, CtorAllocatorTest)
{
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<S1>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<S2>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test<S3>());
}

#undef FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef FORWARD_LIST_TEST_CONSTEXPR

}	// namespace ctor_allocator_test

}	// namespace hamon_forward_list_test
