/**
 *	@file	unit_test_forward_list_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 *
 *	forward_list(const forward_list& x);
 *	forward_list(const forward_list& x, const type_identity_t<Allocator>&);
 */

#include <hamon/forward_list/forward_list.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_forward_list_test
{

namespace ctor_copy_test
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
struct MyAllocator1
{
	using value_type = T;

	int id;

	MyAllocator1() : id(13) {}

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

	int id;

	MyAllocator2() : id(13) {}

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

	MyAllocator2 select_on_container_copy_construction() const noexcept
	{
		// don't propagate on copy
		return {};
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test1()
{
	using Allocator = hamon::allocator<T>;
	using ForwardList = hamon::forward_list<T, Allocator>;

	static_assert( hamon::is_constructible<ForwardList, ForwardList const&>::value, "");
	static_assert( hamon::is_constructible<ForwardList, ForwardList const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<ForwardList, ForwardList const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<ForwardList, ForwardList const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<ForwardList, ForwardList const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<ForwardList, ForwardList const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<ForwardList, ForwardList const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<ForwardList, ForwardList const&, Allocator const&>::value, "");

	{
		Allocator alloc;
		ForwardList const v1{{1,2,3}, alloc};
		ForwardList v2{v1};
		VERIFY(v1.get_allocator() == alloc);
		VERIFY(v2.get_allocator() == alloc);
		{
			auto it = v1.begin();
			VERIFY(*it++ == 1);
			VERIFY(*it++ == 2);
			VERIFY(*it++ == 3);
			VERIFY(it == v1.end());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == 1);
			VERIFY(*it++ == 2);
			VERIFY(*it++ == 3);
			VERIFY(it == v2.end());
		}
	}
	{
		Allocator alloc;
		ForwardList const v1{1,2,3};
		ForwardList v2{v1, alloc};
		VERIFY(v2.get_allocator() == alloc);
		{
			auto it = v1.begin();
			VERIFY(*it++ == 1);
			VERIFY(*it++ == 2);
			VERIFY(*it++ == 3);
			VERIFY(it == v1.end());
		}
		{
			auto it = v2.begin();
			VERIFY(*it++ == 1);
			VERIFY(*it++ == 2);
			VERIFY(*it++ == 3);
			VERIFY(it == v2.end());
		}
	}

	return true;
}

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test2()
{
	using Allocator = MyAllocator1<T>;
	using ForwardList = hamon::forward_list<T, Allocator>;

	{
		Allocator alloc{42};
		ForwardList const v1{{1,2,3}, alloc};
		ForwardList v2{v1};
		VERIFY(v1.get_allocator() == v2.get_allocator());
		VERIFY(v1.get_allocator() == alloc);
		VERIFY(v2.get_allocator() == alloc);
	}
	{
		Allocator alloc1{42};
		Allocator alloc2{43};
		ForwardList const v1{{1,2,3}, alloc1};
		ForwardList v2{v1, alloc2};
		VERIFY(v1.get_allocator() != v2.get_allocator());
		VERIFY(v1.get_allocator() == alloc1);
		VERIFY(v2.get_allocator() == alloc2);
	}

	return true;
}

template <typename T>
FORWARD_LIST_TEST_CONSTEXPR bool test3()
{
	using Allocator = MyAllocator2<T>;
	using ForwardList = hamon::forward_list<T, Allocator>;

	{
		Allocator alloc{42};
		ForwardList const v1{{1,2,3}, alloc};
		ForwardList v2{v1};
		VERIFY(v1.get_allocator() != v2.get_allocator());
		VERIFY(v1.get_allocator() == alloc);
		VERIFY(v2.get_allocator() != alloc);
	}
	{
		Allocator alloc1{42};
		Allocator alloc2{43};
		ForwardList const v1{{1,2,3}, alloc1};
		ForwardList v2{v1, alloc2};
		VERIFY(v1.get_allocator() != v2.get_allocator());
		VERIFY(v1.get_allocator() == alloc1);
		VERIFY(v2.get_allocator() == alloc2);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(ForwardListTest, CtorCopyTest)
{
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());

	EXPECT_TRUE(test2<int>());
	EXPECT_TRUE(test2<char>());
	EXPECT_TRUE(test2<float>());

	EXPECT_TRUE(test3<int>());
	EXPECT_TRUE(test3<char>());
	EXPECT_TRUE(test3<float>());
}

#undef FORWARD_LIST_TEST_CONSTEXPR_EXPECT_TRUE
#undef FORWARD_LIST_TEST_CONSTEXPR

}	// namespace ctor_copy_test

}	// namespace hamon_forward_list_test
