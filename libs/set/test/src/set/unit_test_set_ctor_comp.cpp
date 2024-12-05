/**
 *	@file	unit_test_set_ctor_comp.cpp
 *
 *	@brief	compを引数に取るコンストラクタのテスト
 *
 *	explicit set(const Compare& comp, const Allocator& = Allocator());
 */

#include <hamon/set/set.hpp>
#include <hamon/functional.hpp>
#include <hamon/memory.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_set_test
{

namespace ctor_comp_test
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
	MyAllocator() : id(0) {}

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

	HAMON_CXX11_CONSTEXPR
	bool operator!=(MyAllocator const& rhs) const
	{
		return id != rhs.id;
	}
};

struct MyLess
{
	int id;

	HAMON_CXX11_CONSTEXPR
	MyLess(int i) : id(i) {}

	template <typename T>
	HAMON_CXX11_CONSTEXPR
	bool operator()(T const& x, T const& y) const
	{
		return x < y;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator==(MyLess const& rhs) const
	{
		return id == rhs.id;
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename Compare, typename Allocator>
SET_TEST_CONSTEXPR bool test_impl(Compare const& comp, Allocator const& alloc)
{
	using Set = hamon::set<Key, Compare, Allocator>;

	static_assert( hamon::is_constructible<Set, Compare const&>::value, "");
#if !defined(HAMON_USE_STD_SET)
	static_assert(!hamon::is_nothrow_constructible<Set, Compare const&>::value, "");
#endif
	static_assert(!hamon::is_implicitly_constructible<Set, Compare const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, Compare const&>::value, "");

	static_assert( hamon::is_constructible<Set, Compare const&, Allocator const&>::value, "");
#if !defined(HAMON_USE_STD_SET)
	static_assert(!hamon::is_nothrow_constructible<Set, Compare const&, Allocator const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Set, Compare const&, Allocator const&>::value, "");
#endif
	static_assert(!hamon::is_trivially_constructible<Set, Compare const&, Allocator const&>::value, "");

	{
		Set v(comp);
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
		VERIFY(v.key_comp() == comp);
		VERIFY(v.value_comp() == comp);
		VERIFY(v.get_allocator() == Allocator{});
	}
	{
		Set v{comp};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
		VERIFY(v.key_comp() == comp);
		VERIFY(v.value_comp() == comp);
		VERIFY(v.get_allocator() == Allocator{});
	}
	//{
	//	Set v = {comp};		// explicit指定されているので、これはできない
	//	VERIFY(v.empty());
	//	VERIFY(v.size() == 0);
	//	VERIFY(v.begin() == v.end());
	//	VERIFY(v.rbegin() == v.rend());
	//	VERIFY(v.key_comp() == comp);
	//	VERIFY(v.value_comp() == comp);
	//	VERIFY(v.get_allocator() == Allocator{});
	//}
	{
		Set v(comp, alloc);
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
		VERIFY(v.key_comp() == comp);
		VERIFY(v.value_comp() == comp);
		VERIFY(v.get_allocator() == alloc);
	}
	{
		Set v{comp, alloc};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
		VERIFY(v.key_comp() == comp);
		VERIFY(v.value_comp() == comp);
		VERIFY(v.get_allocator() == alloc);
	}
	//{
	//	Set v = {comp, alloc};
	//	VERIFY(v.empty());
	//	VERIFY(v.size() == 0);
	//	VERIFY(v.begin() == v.end());
	//	VERIFY(v.rbegin() == v.rend());
	//	VERIFY(v.key_comp() == comp);
	//	VERIFY(v.value_comp() == comp);
	//	VERIFY(v.get_allocator() == alloc);
	//}

	return true;
}

template <typename Key>
SET_TEST_CONSTEXPR bool test1()
{
	MyLess comp{13};
	hamon::allocator<Key> alloc;
	VERIFY(test_impl<Key>(comp, alloc));

	return true;
}

template <typename Key>
SET_TEST_CONSTEXPR bool test2()
{
	MyLess comp{14};
	MyAllocator<Key> alloc{42};
	VERIFY(test_impl<Key>(comp, alloc));

	return true;
}

#undef VERIFY

GTEST_TEST(SetTest, CtorCompTest)
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

}	// namespace ctor_comp_test

}	// namespace hamon_set_test
