﻿/**
 *	@file	unit_test_map_value_comp.cpp
 *
 *	@brief	value_comp のテスト
 *
 *	value_compare value_comp() const;
 */

#include <hamon/map/map.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_map_test
{

namespace value_comp_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
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
MAP_TEST_CONSTEXPR bool test_impl(Compare const& comp)
{
	using Map = hamon::map<Key, T, Compare>;
	using ValueCompare = typename Map::value_compare;

	{
		Map v(comp);
		static_assert(!hamon::is_same<decltype(v.value_comp()), Compare>::value, "");
		static_assert( hamon::is_same<decltype(v.value_comp()), ValueCompare>::value, "");
		static_assert(!noexcept(v.value_comp()), "");
		auto value_comp = v.value_comp();
		(void)value_comp;
	}
	{
		Map const v(comp);
		static_assert(!hamon::is_same<decltype(v.value_comp()), Compare>::value, "");
		static_assert( hamon::is_same<decltype(v.value_comp()), ValueCompare>::value, "");
		static_assert(!noexcept(v.value_comp()), "");
		auto value_comp = v.value_comp();
		(void)value_comp;
	}

	return true;
}

template <typename Key>
MAP_TEST_CONSTEXPR bool test()
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

GTEST_TEST(MapTest, ValueCompTest)
{
	MAP_TEST_CONSTEXPR_EXPECT_TRUE(test<int>());
	MAP_TEST_CONSTEXPR_EXPECT_TRUE(test<char>());
	MAP_TEST_CONSTEXPR_EXPECT_TRUE(test<float>());
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace value_comp_test

}	// namespace hamon_map_test