/**
 *	@file	unit_test_unordered_map_find_heterogeneous.cpp
 *
 *	@brief	find のテスト
 *
 *	template<class K>
 *	constexpr iterator       find(const K& k);
 *	template<class K>
 *	constexpr const_iterator find(const K& k) const;
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_map_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MAP) || \
	defined(__cpp_lib_generic_unordered_lookup) && (__cpp_lib_generic_unordered_lookup >= 201811L)

namespace hamon_unordered_map_test
{

namespace find_heterogeneous_test
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
	using Iterator = typename Map::iterator;
	using ConstIterator = typename Map::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().find(hamon::declval<int>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().find(hamon::declval<int>())), ConstIterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().find(hamon::declval<int>())), "");
	static_assert(!noexcept(hamon::declval<Map const&>().find(hamon::declval<int>())), "");

	return true;
}

template <typename Set, typename K, typename = void>
struct is_find_invocable
	: public hamon::false_type {};

template <typename Set, typename K>
struct is_find_invocable<Set, K, hamon::void_t<decltype(hamon::declval<Set>().find(hamon::declval<K>()))>>
	: public hamon::true_type {};

template <typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test2()
{
	using Map1 = hamon::unordered_map<TransparentKey, T>;
	using Map2 = hamon::unordered_map<TransparentKey, T, decltype(hamon::ranges::hash)>;
	using Map3 = hamon::unordered_map<TransparentKey, T, hamon::hash<TransparentKey>, hamon::equal_to<>>;
	using Map4 = hamon::unordered_map<TransparentKey, T, decltype(hamon::ranges::hash), hamon::equal_to<>>;

	static_assert(!is_find_invocable<Map1&, int>::value, "");
	static_assert(!is_find_invocable<Map2&, int>::value, "");
	static_assert(!is_find_invocable<Map3&, int>::value, "");
	static_assert( is_find_invocable<Map4&, int>::value, "");

	static_assert(!is_find_invocable<Map1 const&, int>::value, "");
	static_assert(!is_find_invocable<Map2 const&, int>::value, "");
	static_assert(!is_find_invocable<Map3 const&, int>::value, "");
	static_assert( is_find_invocable<Map4 const&, int>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, FindHeterogeneousTest)
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

}	// namespace find_heterogeneous_test

}	// namespace hamon_unordered_map_test

#endif
