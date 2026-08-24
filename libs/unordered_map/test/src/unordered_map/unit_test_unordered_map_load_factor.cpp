/**
 *	@file	unit_test_unordered_map_load_factor.cpp
 *
 *	@brief	load_factor のテスト
 *
 *	constexpr float load_factor() const noexcept;
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "get_random_value.hpp"

namespace hamon_unordered_map_test
{

namespace load_factor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Map = hamon::unordered_map<Key, T>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().load_factor()), float>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().load_factor()), float>::value, "");
	static_assert(noexcept(hamon::declval<Map&>().load_factor()), "");
	static_assert(noexcept(hamon::declval<Map const&>().load_factor()), "");

	Map v;
	VERIFY(v.load_factor() == 0);
	for (int i = 0; i < 100; ++i)
	{
		v.emplace(static_cast<Key>(i), T{10});
		VERIFY(v.load_factor() <= v.max_load_factor());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, LoadFactorTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

	{
		using Key = int;
		using T = float;
		hamon::unordered_map<Key, T> v;
		EXPECT_TRUE(v.load_factor() == 0);
		for (int i = 0; i < 1000; ++i)
		{
			v.emplace(get_random_value<Key>(), get_random_value<T>());
			EXPECT_TRUE(v.load_factor() <= v.max_load_factor());
		}
	}
}

}	// namespace load_factor_test

}	// namespace hamon_unordered_map_test
