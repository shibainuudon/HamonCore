﻿/**
 *	@file	unit_test_unordered_multimap_contains_heterogeneous.cpp
 *
 *	@brief	contains のテスト
 *
 *	template<class K>
 *	constexpr bool contains(const K& k) const;
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multimap_test_helper.hpp"

// P0458R2
#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) || (HAMON_CXX_STANDARD >= 20)

namespace hamon_unordered_multimap_test
{

namespace contains_heterogeneous_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::unordered_multimap<Key, T, decltype(hamon::ranges::hash), hamon::equal_to<>>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().contains(hamon::declval<int>())), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().contains(hamon::declval<int>())), bool>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().contains(hamon::declval<int>())), "");
	static_assert(!noexcept(hamon::declval<Map const&>().contains(hamon::declval<int>())), "");

	return true;
}

template <typename Map, typename K, typename = void>
struct is_contains_invocable
	: public hamon::false_type {};

template <typename Map, typename K>
struct is_contains_invocable<Map, K, hamon::void_t<decltype(hamon::declval<Map>().contains(hamon::declval<K>()))>>
	: public hamon::true_type {};

template <typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test2()
{
	using Map1 = hamon::unordered_multimap<TransparentKey, T>;
	using Map2 = hamon::unordered_multimap<TransparentKey, T, decltype(hamon::ranges::hash)>;
	using Map3 = hamon::unordered_multimap<TransparentKey, T, hamon::hash<TransparentKey>, hamon::equal_to<>>;
	using Map4 = hamon::unordered_multimap<TransparentKey, T, decltype(hamon::ranges::hash), hamon::equal_to<>>;

	static_assert(!is_contains_invocable<Map1&, int>::value, "");
	static_assert(!is_contains_invocable<Map2&, int>::value, "");
	static_assert(!is_contains_invocable<Map3&, int>::value, "");
	static_assert( is_contains_invocable<Map4&, int>::value, "");

	static_assert(!is_contains_invocable<Map1 const&, int>::value, "");
	static_assert(!is_contains_invocable<Map2 const&, int>::value, "");
	static_assert(!is_contains_invocable<Map3 const&, int>::value, "");
	static_assert( is_contains_invocable<Map4 const&, int>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, ContainsHeterogeneousTest)
{
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));

	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test2<int>());
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test2<char>());
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test2<float>());
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace contains_heterogeneous_test

}	// namespace hamon_unordered_multimap_test

#endif
