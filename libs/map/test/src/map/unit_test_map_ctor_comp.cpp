/**
 *	@file	unit_test_map_ctor_comp.cpp
 *
 *	@brief	compを引数に取るコンストラクタのテスト
 *
 *	explicit map(const Compare& comp, const Allocator& = Allocator());
 */

#include <hamon/map/map.hpp>
#include <hamon/functional.hpp>
#include <hamon/memory.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_map_test
{

namespace ctor_comp_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
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

template <typename Key, typename T, typename Compare, typename Allocator>
MAP_TEST_CONSTEXPR bool test_impl(Compare const& comp, Allocator const& alloc)
{
	using Map = hamon::map<Key, T, Compare, Allocator>;

	static_assert( hamon::is_constructible<Map, Compare const&>::value, "");
#if !defined(HAMON_USE_STD_MAP)
	static_assert(!hamon::is_nothrow_constructible<Map, Compare const&>::value, "");
#endif
	static_assert(!hamon::is_implicitly_constructible<Map, Compare const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, Compare const&>::value, "");

	static_assert( hamon::is_constructible<Map, Compare const&, Allocator const&>::value, "");
#if !defined(HAMON_USE_STD_MAP)
	static_assert(!hamon::is_nothrow_constructible<Map, Compare const&, Allocator const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Map, Compare const&, Allocator const&>::value, "");
#endif
	static_assert(!hamon::is_trivially_constructible<Map, Compare const&, Allocator const&>::value, "");

	{
		Map v(comp);
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
		VERIFY(v.key_comp() == comp);
		VERIFY(v.get_allocator() == Allocator{});
	}
	{
		Map v{comp};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
		VERIFY(v.key_comp() == comp);
		VERIFY(v.get_allocator() == Allocator{});
	}
	//{
	//	Map v = {comp};		// explicit指定されているので、これはできない
	//	VERIFY(v.empty());
	//	VERIFY(v.size() == 0);
	//	VERIFY(v.begin() == v.end());
	//	VERIFY(v.rbegin() == v.rend());
	//	VERIFY(v.key_comp() == comp);
	//	VERIFY(v.get_allocator() == Allocator{});
	//}
	{
		Map v(comp, alloc);
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
		VERIFY(v.key_comp() == comp);
		VERIFY(v.get_allocator() == alloc);
	}
	{
		Map v{comp, alloc};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
		VERIFY(v.key_comp() == comp);
		VERIFY(v.get_allocator() == alloc);
	}
	//{
	//	Map v = {comp, alloc};
	//	VERIFY(v.empty());
	//	VERIFY(v.size() == 0);
	//	VERIFY(v.begin() == v.end());
	//	VERIFY(v.rbegin() == v.rend());
	//	VERIFY(v.key_comp() == comp);
	//	VERIFY(v.get_allocator() == alloc);
	//}

	return true;
}

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test1_2()
{
	MyLess comp{13};
	hamon::allocator<typename hamon::map<Key, T>::value_type> alloc;
	VERIFY(test_impl<Key, T>(comp, alloc));

	return true;
}

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test2_2()
{
	MyLess comp{14};
	MyAllocator<typename hamon::map<Key, T>::value_type> alloc{42};
	VERIFY(test_impl<Key, T>(comp, alloc));

	return true;
}

template <typename Key>
MAP_TEST_CONSTEXPR bool test1()
{
	VERIFY(test1_2<Key, int>());
	VERIFY(test1_2<Key, char>());
	VERIFY(test1_2<Key, float>());

	return true;
}

template <typename Key>
MAP_TEST_CONSTEXPR bool test2()
{
	VERIFY(test2_2<Key, int>());
	VERIFY(test2_2<Key, char>());
	VERIFY(test2_2<Key, float>());

	return true;
}

#undef VERIFY

GTEST_TEST(MapTest, CtorCompTest)
{
	MAP_TEST_CONSTEXPR_EXPECT_TRUE(test1<int>());
	MAP_TEST_CONSTEXPR_EXPECT_TRUE(test1<char>());
	MAP_TEST_CONSTEXPR_EXPECT_TRUE(test1<float>());

	EXPECT_TRUE(test2<int>());
	EXPECT_TRUE(test2<char>());
	EXPECT_TRUE(test2<float>());
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace ctor_comp_test

}	// namespace hamon_map_test
