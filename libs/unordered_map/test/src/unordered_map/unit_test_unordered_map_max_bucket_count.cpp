/**
 *	@file	unit_test_unordered_map_max_bucket_count.cpp
 *
 *	@brief	max_bucket_count のテスト
 *
 *	constexpr size_type max_bucket_count() const noexcept;
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_map_test
{

namespace max_bucket_count_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Map = hamon::unordered_map<Key, T>;
	using SizeType = typename Map::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().max_bucket_count()), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().max_bucket_count()), SizeType>::value, "");
	static_assert(noexcept(hamon::declval<Map&>().max_bucket_count()), "");
	static_assert(noexcept(hamon::declval<Map const&>().max_bucket_count()), "");

	{
		Map const v;
		VERIFY(v.max_bucket_count() > 0);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, MaxBucketCountTest)
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
}

}	// namespace max_bucket_count_test

}	// namespace hamon_unordered_map_test
