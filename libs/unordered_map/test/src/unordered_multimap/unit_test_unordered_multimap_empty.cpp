﻿/**
 *	@file	unit_test_unordered_multimap_empty.cpp
 *
 *	@brief	empty のテスト
 *
 *	constexpr bool empty() const noexcept;
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multimap_test
{

namespace empty_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
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

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().empty()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().empty()), bool>::value, "");
	static_assert(noexcept(hamon::declval<Map&>().empty()), "");
	static_assert(noexcept(hamon::declval<Map const&>().empty()), "");

#if 0
	{
		Map v;
		VERIFY(v.empty() == true);
	}
	{
		Map const v;
		VERIFY(v.empty() == true);
	}
	{
		Map const v
		{
			{Key{2}, T{10}},
			{Key{3}, T{20}},
			{Key{1}, T{30}},
			{Key{1}, T{40}},
			{Key{2}, T{50}},
			{Key{3}, T{60}},
		};
		VERIFY(v.empty() == false);
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, EmptyTest)
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
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace empty_test

}	// namespace hamon_unordered_multimap_test
