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

#if !defined(HAMON_USE_STD_UNORDERED_MAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test()
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
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

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

#undef UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MAP_TEST_CONSTEXPR

}	// namespace load_factor_test

}	// namespace hamon_unordered_map_test
