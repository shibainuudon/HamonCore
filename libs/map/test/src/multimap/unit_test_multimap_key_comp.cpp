/**
 *	@file	unit_test_multimap_key_comp.cpp
 *
 *	@brief	key_comp のテスト
 *
 *	key_compare key_comp() const;
 */

#include <hamon/map/multimap.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multimap_test
{

namespace key_comp_test
{

#if !defined(HAMON_USE_STD_MULTIMAP)
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR              /**/
#endif

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

struct MyGreater
{
	int id;

	HAMON_CXX11_CONSTEXPR
	MyGreater() : id(0) {}

	HAMON_CXX11_CONSTEXPR
	MyGreater(int i) : id(i) {}

	template <typename T>
	HAMON_CXX11_CONSTEXPR
	bool operator()(T const& x, T const& y) const
	{
		return x > y;
	}

	HAMON_CXX11_CONSTEXPR
	bool operator==(MyGreater const& rhs) const
	{
		return id == rhs.id;
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T, typename Compare>
MULTIMAP_TEST_CONSTEXPR bool test_impl(Compare const& comp)
{
	using Map = hamon::multimap<Key, T, Compare>;

	{
		Map v(comp);
		static_assert(hamon::is_same<decltype(v.key_comp()), Compare>::value, "");
		static_assert(!noexcept(v.key_comp()), "");
		VERIFY(v.key_comp() == comp);
	}
	{
		Map const v(comp);
		static_assert(hamon::is_same<decltype(v.key_comp()), Compare>::value, "");
		static_assert(!noexcept(v.key_comp()), "");
		VERIFY(v.key_comp() == comp);
	}

	return true;
}

template <typename Key>
MULTIMAP_TEST_CONSTEXPR bool test()
{
	{
		MyLess comp{13};
		VERIFY(test_impl<Key, int>(comp));
		VERIFY(test_impl<Key, char>(comp));
		VERIFY(test_impl<Key, float>(comp));
	}
	{
		MyGreater comp{13};
		VERIFY(test_impl<Key, int>(comp));
		VERIFY(test_impl<Key, char>(comp));
		VERIFY(test_impl<Key, float>(comp));
	}

	return true;
}

#undef VERIFY

// Example module 97 key compare function
struct ModCmp
{
	bool operator()(int lhs, int rhs) const
	{
		return (lhs % 97) < (rhs % 97);
	}
};

GTEST_TEST(MultimapTest, KeyCompTest)
{
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());

	// https://en.cppreference.com/w/cpp/container/multimap/key_comp
	{
		hamon::multimap<int, char, ModCmp> cont;
		cont = {{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'}, {5, 'e'}};

		auto comp_func = cont.key_comp();

		auto it = cont.begin();
		EXPECT_TRUE (comp_func(it->first, 100));
		EXPECT_FALSE(comp_func(100, it->first));
		++it;
		EXPECT_TRUE (comp_func(it->first, 100));
		EXPECT_FALSE(comp_func(100, it->first));
		++it;
		EXPECT_FALSE(comp_func(it->first, 100));
		EXPECT_FALSE(comp_func(100, it->first));
		++it;
		EXPECT_FALSE(comp_func(it->first, 100));
		EXPECT_TRUE (comp_func(100, it->first));
		++it;
		EXPECT_FALSE(comp_func(it->first, 100));
		EXPECT_TRUE (comp_func(100, it->first));
		++it;
		EXPECT_TRUE(it == cont.end());
	}
}

#undef MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTIMAP_TEST_CONSTEXPR

}	// namespace key_comp_test

}	// namespace hamon_multimap_test
