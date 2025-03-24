/**
 *	@file	unit_test_unordered_map_max_load_factor.cpp
 *
 *	@brief	max_load_factor のテスト
 *
 *	constexpr float max_load_factor() const noexcept;
 *	constexpr void max_load_factor(float z);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_map_test
{

namespace max_load_factor_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MAP)
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

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().max_load_factor()), float>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().max_load_factor()), float>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().max_load_factor(hamon::declval<float>())), void>::value, "");
	static_assert( noexcept(hamon::declval<Map&>().max_load_factor()), "");
	static_assert( noexcept(hamon::declval<Map const&>().max_load_factor()), "");
#if !defined(HAMON_USE_STD_UNORDERED_MAP)
	static_assert(!noexcept(hamon::declval<Map&>().max_load_factor(hamon::declval<float>())), "");
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, MaxLoadFactorTest)
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
}

#undef UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MAP_TEST_CONSTEXPR

}	// namespace max_load_factor_test

}	// namespace hamon_unordered_map_test
