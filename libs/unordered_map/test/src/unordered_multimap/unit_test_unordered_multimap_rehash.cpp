/**
 *	@file	unit_test_unordered_multimap_rehash.cpp
 *
 *	@brief	rehash のテスト
 *
 *	constexpr void rehash(size_type n);
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multimap_test
{

namespace rehash_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Map = hamon::unordered_multimap<Key, T>;
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

	v.clear();
	v.rehash(1);
	VERIFY(static_cast<float>(v.bucket_count()) >= static_cast<float>(v.size()) / v.max_load_factor());
	VERIFY(v.bucket_count() >= 1);

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, RehashTest)
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

}	// namespace rehash_test

}	// namespace hamon_unordered_multimap_test
