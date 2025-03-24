/**
 *	@file	unit_test_unordered_map_contains.cpp
 *
 *	@brief	contains のテスト
 *
 *	constexpr bool contains(const key_type& k) const;
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_map_test_helper.hpp"

// P0458R2
#if !defined(HAMON_USE_STD_UNORDERED_MAP) || (HAMON_CXX_STANDARD >= 20)

namespace hamon_unordered_map_test
{

namespace contains_test
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

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().contains(hamon::declval<Key const&>())), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().contains(hamon::declval<Key const&>())), bool>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MAP)
	//static_assert( noexcept(hamon::declval<Map&>().contains(hamon::declval<Key const&>())), "");
	//static_assert( noexcept(hamon::declval<Map const&>().contains(hamon::declval<Key const&>())), "");
#endif

	Map const v
	{
		{Key{5}, T{60}},
		{Key{7}, T{70}},
		{Key{3}, T{40}},
		{Key{3}, T{30}},
		{Key{2}, T{10}},
		{Key{3}, T{50}},
		{Key{2}, T{20}},
	};

	VERIFY(v.contains(Key{0}) == false);
	VERIFY(v.contains(Key{1}) == false);
	VERIFY(v.contains(Key{2}) == true);
	VERIFY(v.contains(Key{3}) == true);
	VERIFY(v.contains(Key{4}) == false);
	VERIFY(v.contains(Key{5}) == true);
	VERIFY(v.contains(Key{6}) == false);
	VERIFY(v.contains(Key{7}) == true);
	VERIFY(v.contains(Key{8}) == false);

	return true;
}

template <typename Key, typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test_noexcept()
{
#if !defined(HAMON_USE_STD_UNORDERED_MAP)
	{
		using Map = hamon::unordered_map<Key, T, NoThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert( noexcept(hamon::declval<Map&>().contains(hamon::declval<Key const&>())), "");
		static_assert( noexcept(hamon::declval<Map const&>().contains(hamon::declval<Key const&>())), "");
	}
	{
		using Map = hamon::unordered_map<Key, T, NoThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Map&>().contains(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Map const&>().contains(hamon::declval<Key const&>())), "");
	}
	{
		using Map = hamon::unordered_map<Key, T, ThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Map&>().contains(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Map const&>().contains(hamon::declval<Key const&>())), "");
	}
	{
		using Map = hamon::unordered_map<Key, T, ThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Map&>().contains(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Map const&>().contains(hamon::declval<Key const&>())), "");
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, ContainsTest)
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

	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<int, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<int, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<int, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<char, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<char, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<char, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<float, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<float, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<float, float>()));
}

#undef UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MAP_TEST_CONSTEXPR

}	// namespace contains_test

}	// namespace hamon_unordered_map_test

#endif
