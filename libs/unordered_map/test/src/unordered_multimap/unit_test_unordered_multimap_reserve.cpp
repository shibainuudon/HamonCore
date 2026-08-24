/**
 *	@file	unit_test_unordered_multimap_reserve.cpp
 *
 *	@brief	reserve のテスト
 *
 *	constexpr void reserve(size_type n);
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multimap_test
{

namespace reserve_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Map = hamon::unordered_multimap<Key, T>;
	using SizeType = typename Map::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().reserve(hamon::declval<SizeType>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().reserve(hamon::declval<SizeType>())), "");

	Map v;

	v.max_load_factor(2.0f);
	v.reserve(22);

	VERIFY(static_cast<float>(v.bucket_count()) >= 22.0f / v.max_load_factor());

	for (int i = 0; i < 22; ++i)
	{
		v.emplace(static_cast<Key>(i), T{10});
	}

	v.reserve(99);

	VERIFY(static_cast<float>(v.bucket_count()) >= 99.0f / v.max_load_factor());

	for (int i = 0; i < 77; ++i)
	{
		v.emplace(static_cast<Key>(i+22), T{20});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, ReserveTest)
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

}	// namespace reserve_test

}	// namespace hamon_unordered_multimap_test
