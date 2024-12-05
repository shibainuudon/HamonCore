/**
 *	@file	unit_test_map_ctor_allocator.cpp
 *
 *	@brief	allocatorを引数に取るコンストラクタのテスト
 *
 *	explicit map(const Allocator&);
 */

#include <hamon/map/map.hpp>
#include <hamon/functional.hpp>
#include <hamon/memory.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_map_test
{

namespace ctor_allocator_test
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

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T, typename Allocator>
MAP_TEST_CONSTEXPR bool test_impl(Allocator const& alloc)
{
	using Map = hamon::map<Key, T, hamon::less<>, Allocator>;

	static_assert( hamon::is_constructible<Map, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, Allocator const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Map, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, Allocator const&>::value, "");

	{
		Map v(alloc);
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
		VERIFY(v.get_allocator() == alloc);
	}
	{
		Map v{alloc};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.rbegin() == v.rend());
		VERIFY(v.get_allocator() == alloc);
	}
	//{
	//	Map v = {alloc};	// explicit指定されているので、これはできない
	//	VERIFY(v.empty());
	//	VERIFY(v.size() == 0);
	//	VERIFY(v.begin() == v.end());
	//	VERIFY(v.rbegin() == v.rend());
	//	VERIFY(v.get_allocator() == alloc);
	//}

	return true;
}

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test1_2()
{
	hamon::allocator<std::pair<const Key, T>> alloc;
	VERIFY(test_impl<Key, T>(alloc));

	return true;
}

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test2_2()
{
	MyAllocator<std::pair<const Key, T>> alloc{42};
	VERIFY(test_impl<Key, T>(alloc));

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

GTEST_TEST(MapTest, CtorAllocatorTest)
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

}	// namespace ctor_allocator_test

}	// namespace hamon_map_test
