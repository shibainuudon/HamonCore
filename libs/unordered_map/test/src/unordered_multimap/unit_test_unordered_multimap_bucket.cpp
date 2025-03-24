/**
 *	@file	unit_test_unordered_multimap_bucket.cpp
 *
 *	@brief	bucket のテスト
 *
 *	constexpr size_type bucket(const key_type& k) const;
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multimap_test_helper.hpp"

namespace hamon_unordered_multimap_test
{

namespace bucket_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::unordered_multimap<Key, T>;
	using SizeType = typename Map::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().bucket(hamon::declval<Key const&>())), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().bucket(hamon::declval<Key const&>())), SizeType>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
	//static_assert( noexcept(hamon::declval<Map&>().bucket(hamon::declval<Key const&>())), "");
	//static_assert( noexcept(hamon::declval<Map const&>().bucket(hamon::declval<Key const&>())), "");
#endif

	Map const v
	{
		{Key{3}, T{10}},
		{Key{1}, T{20}},
		{Key{4}, T{30}},
		{Key{1}, T{40}},
		{Key{5}, T{50}},
	};
	VERIFY(v.bucket(Key{0}) < v.bucket_count());
	VERIFY(v.bucket(Key{1}) < v.bucket_count());
	VERIFY(v.bucket(Key{2}) < v.bucket_count());
	VERIFY(v.bucket(Key{3}) < v.bucket_count());
	VERIFY(v.bucket(Key{4}) < v.bucket_count());
	VERIFY(v.bucket(Key{5}) < v.bucket_count());
	VERIFY(v.bucket(Key{100}) < v.bucket_count());

	return true;
}

template <typename Key, typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test_noexcept()
{
#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
	{
		using Map = hamon::unordered_multimap<Key, T, NoThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert( noexcept(hamon::declval<Map&>().bucket(hamon::declval<Key const&>())), "");
		static_assert( noexcept(hamon::declval<Map const&>().bucket(hamon::declval<Key const&>())), "");
	}
	{
		using Map = hamon::unordered_multimap<Key, T, NoThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert( noexcept(hamon::declval<Map&>().bucket(hamon::declval<Key const&>())), "");
		static_assert( noexcept(hamon::declval<Map const&>().bucket(hamon::declval<Key const&>())), "");
	}
	{
		using Map = hamon::unordered_multimap<Key, T, ThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Map&>().bucket(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Map const&>().bucket(hamon::declval<Key const&>())), "");
	}
	{
		using Map = hamon::unordered_multimap<Key, T, ThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Map&>().bucket(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Map const&>().bucket(hamon::declval<Key const&>())), "");
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, BucketTest)
{
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<int, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<int, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<int, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<char, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<char, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<char, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<float, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<float, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<float, float>()));
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace bucket_test

}	// namespace hamon_unordered_multimap_test
