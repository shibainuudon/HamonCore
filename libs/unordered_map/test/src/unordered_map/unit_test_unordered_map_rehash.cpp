/**
 *	@file	unit_test_unordered_map_rehash.cpp
 *
 *	@brief	rehash のテスト
 *
 *	constexpr void rehash(size_type n);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_map_test
{

namespace rehash_test
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
	using SizeType = typename Map::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().rehash(hamon::declval<SizeType>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().rehash(hamon::declval<SizeType>())), "");

	Map v;

	v.rehash(10);
	VERIFY(static_cast<float>(v.bucket_count()) >= static_cast<float>(v.size()) / v.max_load_factor());
	VERIFY(v.bucket_count() >= 10);

	for (int i = 0; i < 100; ++i)
	{
		v.emplace(static_cast<Key>(i), T{100});
	}

	v.rehash(1000);
	VERIFY(static_cast<float>(v.bucket_count()) >= static_cast<float>(v.size()) / v.max_load_factor());
	VERIFY(v.bucket_count() >= 1000);

	VERIFY(v[0] == T{100});
	VERIFY(v[99] == T{100});

	v.clear();
	v.rehash(1);
	VERIFY(static_cast<float>(v.bucket_count()) >= static_cast<float>(v.size()) / v.max_load_factor());
	VERIFY(v.bucket_count() >= 1);

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, RehashTest)
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

}	// namespace rehash_test

}	// namespace hamon_unordered_map_test
