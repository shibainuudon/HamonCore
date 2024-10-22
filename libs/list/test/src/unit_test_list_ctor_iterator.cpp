/**
 *	@file	unit_test_list_ctor_iterator.cpp
 *
 *	@brief	イテレータを引数に取るコンストラクタのテスト
 *
 *	template<class InputIterator>
 *	list(InputIterator first, InputIterator last, const Allocator& = Allocator());
 */

#include <hamon/list/list.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_list_test
{

namespace ctor_iterator_test
{

#if !defined(HAMON_USE_STD_LIST) && \
	!(defined(HAMON_MSVC) && (HAMON_MSVC < 1930))// VS2019でconstexprにすると内部コンパイラエラーになってしまう
#define LIST_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define LIST_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define LIST_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define LIST_TEST_CONSTEXPR             /**/
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

template <typename T, template <typename> class IteratorWrapper, typename Allocator>
LIST_TEST_CONSTEXPR bool test_impl2(Allocator const& alloc)
{
	using List = hamon::list<T, Allocator>;
	using Iterator = IteratorWrapper<T>;

	static_assert( hamon::is_constructible<List, Iterator, Iterator>::value, "");
	static_assert( hamon::is_constructible<List, Iterator, Iterator, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<List, Iterator, Iterator>::value, "");
	static_assert(!hamon::is_nothrow_constructible<List, Iterator, Iterator, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<List, Iterator, Iterator>::value, "");
	static_assert( hamon::is_implicitly_constructible<List, Iterator, Iterator, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<List, Iterator, Iterator>::value, "");
	static_assert(!hamon::is_trivially_constructible<List, Iterator, Iterator, Allocator const&>::value, "");

	T a[] = {T{1}, T{2}, T{3}};
	{
		List v(Iterator{a}, Iterator{a + 3});
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == a[0]);
			VERIFY(*it++ == a[1]);
			VERIFY(*it++ == a[2]);
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == a[2]);
			VERIFY(*it++ == a[1]);
			VERIFY(*it++ == a[0]);
			VERIFY(it == v.rend());
		}
	}
	{
		List v(Iterator{a}, Iterator{a + 3}, alloc);
		VERIFY(v.get_allocator() == alloc);
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.rbegin() != v.rend());
		{
			auto it = v.begin();
			VERIFY(*it++ == a[0]);
			VERIFY(*it++ == a[1]);
			VERIFY(*it++ == a[2]);
			VERIFY(it == v.end());
		}
		{
			auto it = v.rbegin();
			VERIFY(*it++ == a[2]);
			VERIFY(*it++ == a[1]);
			VERIFY(*it++ == a[0]);
			VERIFY(it == v.rend());
		}
	}
	{
		List v(Iterator{a}, Iterator{a});
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
	}
	{
		List v(Iterator{a}, Iterator{a}, alloc);
		VERIFY(v.get_allocator() == alloc);
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
	}

	return true;
}

template <typename T, typename Allocator>
LIST_TEST_CONSTEXPR bool test_impl(Allocator const& alloc)
{
	return
		test_impl2<T, cpp17_input_iterator_wrapper>(alloc) &&
		//test_impl2<T, input_iterator_wrapper>(alloc) &&
		test_impl2<T, forward_iterator_wrapper>(alloc) &&
		test_impl2<T, bidirectional_iterator_wrapper>(alloc) &&
		test_impl2<T, random_access_iterator_wrapper>(alloc) &&
		test_impl2<T, contiguous_iterator_wrapper>(alloc);
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

GTEST_TEST(ListTest, CtorIteratorTest)
{
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());
	LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<S1>());

	EXPECT_TRUE(test2<int>());
	EXPECT_TRUE(test2<char>());
	EXPECT_TRUE(test2<float>());
	EXPECT_TRUE(test2<S1>());
}

#undef LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef LIST_TEST_CONSTEXPR

}	// namespace ctor_iterator_test

}	// namespace hamon_list_test
