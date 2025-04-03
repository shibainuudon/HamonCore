/**
 *	@file	unit_test_unordered_map_extract_heterogeneous.cpp
 *
 *	@brief	extract のテスト
 *
 *	template<class K> constexpr node_type extract(K&& x);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_map_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MAP) || \
	(defined(__cpp_lib_associative_heterogeneous_erasure) && (__cpp_lib_associative_heterogeneous_erasure >= 202110L))

namespace hamon_unordered_map_test
{

namespace extract_heterogeneous_test
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
UNORDERED_MAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::unordered_map<Key, T, decltype(hamon::ranges::hash), hamon::equal_to<>>;
	using NodeType = typename Map::node_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().extract(hamon::declval<int>())), NodeType>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().extract(hamon::declval<int>())), "");

	return true;
}

template <typename Map, typename K, typename = void>
struct is_extract_invocable
	: public hamon::false_type {};

template <typename Map, typename K>
struct is_extract_invocable<Map, K, hamon::void_t<decltype(hamon::declval<Map>().extract(hamon::declval<K>()))>>
	: public hamon::true_type {};

template <typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test2()
{
	using Map1 = hamon::unordered_map<TransparentKey, T>;
	using Map2 = hamon::unordered_map<TransparentKey, T, decltype(hamon::ranges::hash)>;
	using Map3 = hamon::unordered_map<TransparentKey, T, hamon::hash<TransparentKey>, hamon::equal_to<>>;
	using Map4 = hamon::unordered_map<TransparentKey, T, decltype(hamon::ranges::hash), hamon::equal_to<>>;

	static_assert(!is_extract_invocable<Map1&, int>::value, "");
	static_assert(!is_extract_invocable<Map2&, int>::value, "");
	static_assert(!is_extract_invocable<Map3&, int>::value, "");
	static_assert( is_extract_invocable<Map4&, int>::value, "");

	static_assert(!is_extract_invocable<Map1 const&, int>::value, "");
	static_assert(!is_extract_invocable<Map2 const&, int>::value, "");
	static_assert(!is_extract_invocable<Map3 const&, int>::value, "");
	static_assert(!is_extract_invocable<Map4 const&, int>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, ExtractHeterogeneousTest)
{
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));

	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test2<int>());
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test2<char>());
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE(test2<float>());
}

#undef UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MAP_TEST_CONSTEXPR

}	// namespace extract_heterogeneous_test

}	// namespace hamon_unordered_map_test

#endif
