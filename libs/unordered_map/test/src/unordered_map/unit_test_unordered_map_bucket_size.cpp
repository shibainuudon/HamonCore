/**
 *	@file	unit_test_unordered_map_bucket_size.cpp
 *
 *	@brief	bucket_size のテスト
 *
 *	constexpr size_type bucket_size(size_type n) const;
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_map_test
{

namespace bucket_size_test
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

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().bucket_size(hamon::declval<SizeType>())), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().bucket_size(hamon::declval<SizeType>())), SizeType>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MAP)
	static_assert( noexcept(hamon::declval<Map&>().bucket_size(hamon::declval<SizeType>())), "");
	static_assert( noexcept(hamon::declval<Map const&>().bucket_size(hamon::declval<SizeType>())), "");
#endif

	Map const v
	{
		{Key{3}, T{10}},
		{Key{1}, T{20}},
		{Key{4}, T{30}},
		{Key{1}, T{40}},
		{Key{5}, T{50}},
	};
	VERIFY(v.bucket_size(v.bucket(Key{0})) >= 0);
	VERIFY(v.bucket_size(v.bucket(Key{1})) >= 1);
	VERIFY(v.bucket_size(v.bucket(Key{2})) >= 0);
	VERIFY(v.bucket_size(v.bucket(Key{3})) >= 1);
	VERIFY(v.bucket_size(v.bucket(Key{4})) >= 1);
	VERIFY(v.bucket_size(v.bucket(Key{5})) >= 1);

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, BucketSizeTest)
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

}	// namespace bucket_size_test

}	// namespace hamon_unordered_map_test
