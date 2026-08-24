/**
 *	@file	unit_test_unordered_map_bucket.cpp
 *
 *	@brief	bucket のテスト
 *
 *	constexpr size_type bucket(const key_type& k) const;
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_map_test_helper.hpp"

namespace hamon_unordered_map_test
{

namespace bucket_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Map = hamon::unordered_map<Key, T>;
	using SizeType = typename Map::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().bucket(hamon::declval<Key const&>())), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().bucket(hamon::declval<Key const&>())), SizeType>::value, "");
	//static_assert( noexcept(hamon::declval<Map&>().bucket(hamon::declval<Key const&>())), "");
	//static_assert( noexcept(hamon::declval<Map const&>().bucket(hamon::declval<Key const&>())), "");

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
HAMON_CXX20_CONSTEXPR bool test_noexcept()
{
	{
		using Map = hamon::unordered_map<Key, T, NoThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert( noexcept(hamon::declval<Map&>().bucket(hamon::declval<Key const&>())), "");
		static_assert( noexcept(hamon::declval<Map const&>().bucket(hamon::declval<Key const&>())), "");
	}
	{
		using Map = hamon::unordered_map<Key, T, NoThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert( noexcept(hamon::declval<Map&>().bucket(hamon::declval<Key const&>())), "");
		static_assert( noexcept(hamon::declval<Map const&>().bucket(hamon::declval<Key const&>())), "");
	}
	{
		using Map = hamon::unordered_map<Key, T, ThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Map&>().bucket(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Map const&>().bucket(hamon::declval<Key const&>())), "");
	}
	{
		using Map = hamon::unordered_map<Key, T, ThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Map&>().bucket(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Map const&>().bucket(hamon::declval<Key const&>())), "");
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, BucketTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<int, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<int, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<int, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<char, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<char, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<char, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<float, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<float, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<float, float>()));
}

}	// namespace bucket_test

}	// namespace hamon_unordered_map_test
