/**
 *	@file	unit_test_unordered_map_insert_or_assign_heterogeneous.cpp
 *
 *	@brief	insert_or_assign のテスト
 *
 *	template<class K, class M>
 *	constexpr pair<iterator, bool> insert_or_assign(K&& k, M&& obj);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/functional.hpp>
#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_map_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MAP) || \
	(defined(__cpp_lib_associative_heterogeneous_insertion) && (__cpp_lib_associative_heterogeneous_insertion >= 202306L))

namespace hamon_unordered_map_test
{

namespace insert_or_assign_heterogeneous_test
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
#if defined(HAMON_USE_STD_UNORDERED_MAP)
	using Result = std::pair<Iterator, bool>;
#else
	using Result = hamon::pair<Iterator, bool>;
#endif

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert_or_assign(hamon::declval<int>(), hamon::declval<T>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert_or_assign(hamon::declval<int>(), hamon::declval<T>())), "");

	return true;
}

template <typename Map, typename K, typename M, typename = void>
struct is_insert_or_assign_invocable
	: public hamon::false_type {};

template <typename Map, typename K, typename M>
struct is_insert_or_assign_invocable<Map, K, M, hamon::void_t<decltype(hamon::declval<Map>().insert_or_assign(hamon::declval<K>(), hamon::declval<M>()))>>
	: public hamon::true_type {};

template <typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test2()
{
	using Map1 = hamon::unordered_map<TransparentKey, T>;
	using Map2 = hamon::unordered_map<TransparentKey, T, decltype(hamon::ranges::hash)>;
	using Map3 = hamon::unordered_map<TransparentKey, T, hamon::hash<TransparentKey>, hamon::equal_to<>>;
	using Map4 = hamon::unordered_map<TransparentKey, T, decltype(hamon::ranges::hash), hamon::equal_to<>>;

	static_assert(!is_insert_or_assign_invocable<Map1&, int, T>::value, "");
	static_assert(!is_insert_or_assign_invocable<Map2&, int, T>::value, "");
	static_assert(!is_insert_or_assign_invocable<Map3&, int, T>::value, "");
	static_assert( is_insert_or_assign_invocable<Map4&, int, T>::value, "");

	static_assert(!is_insert_or_assign_invocable<Map1 const&, int, T>::value, "");
	static_assert(!is_insert_or_assign_invocable<Map2 const&, int, T>::value, "");
	static_assert(!is_insert_or_assign_invocable<Map3 const&, int, T>::value, "");
	static_assert(!is_insert_or_assign_invocable<Map4 const&, int, T>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, InsertOrAssignHeterogeneousTest)
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

}	// namespace insert_or_assign_heterogeneous_test

}	// namespace hamon_unordered_map_test

#endif
