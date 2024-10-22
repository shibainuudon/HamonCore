/**
 *	@file	unit_test_list_ctor_n.cpp
 *
 *	@brief	要素数を引数に取るコンストラクタのテスト
 *
 *	explicit list(size_type n, const Allocator& = Allocator());
 */

#include <hamon/list/list.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_list_test
{

namespace ctor_n_test
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
LIST_TEST_CONSTEXPR bool test_impl(Allocator& alloc)
{
	using List = hamon::list<T, Allocator>;
	using SizeType = typename List::size_type;

	static_assert( hamon::is_constructible<List, SizeType>::value, "");
	static_assert( hamon::is_constructible<List, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<List, SizeType>::value, "");
	static_assert(!hamon::is_nothrow_constructible<List, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<List, SizeType>::value, "");
	static_assert(!hamon::is_implicitly_constructible<List, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<List, SizeType>::value, "");
	static_assert(!hamon::is_trivially_constructible<List, SizeType, Allocator const&>::value, "");

	{
		List v(3, alloc);
		VERIFY(v.get_allocator() == alloc);
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(it == v.rend());
		}
	}
	{
		List v(0, alloc);
		VERIFY(v.get_allocator() == alloc);
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
	}
	{
		List v(2);
		VERIFY(!v.empty());
		VERIFY(v.size() == 2);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == T{});
			VERIFY(*it++ == T{});
			VERIFY(it == v.rend());
		}
	}
	{
		List v(0);
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
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

GTEST_TEST(ListTest, CtorNTest)
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

}	// namespace ctor_n_test

}	// namespace hamon_list_test
