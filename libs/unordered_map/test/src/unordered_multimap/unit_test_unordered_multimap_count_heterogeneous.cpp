﻿/**
 *	@file	unit_test_unordered_multimap_count_heterogeneous.cpp
 *
 *	@brief	count のテスト
 *
 *	template<class K>
 *	constexpr size_type count(const K& k) const;
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) || \
	defined(__cpp_lib_generic_unordered_lookup) && (__cpp_lib_generic_unordered_lookup >= 201811L)

namespace hamon_unordered_multimap_test
{

namespace count_heterogeneous_test
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
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::unordered_multimap<Key, T, decltype(hamon::ranges::hash), hamon::equal_to<>>;
	using SizeType = typename Map::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().count(hamon::declval<int>())), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().count(hamon::declval<int>())), SizeType>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().count(hamon::declval<int>())), "");
	static_assert(!noexcept(hamon::declval<Map const&>().count(hamon::declval<int>())), "");

	return true;
}

struct S
{
	int value;

	friend constexpr bool operator<(S const& lhs, S const& rhs)
	{
		return lhs.value < rhs.value;
	}

	friend constexpr bool operator<(S const& lhs, int rhs)
	{
		return lhs.value < rhs;
	}

	friend constexpr bool operator<(int lhs, S const& rhs)
	{
		return lhs < rhs.value;
	}

	constexpr hamon::size_t hash() const { return hamon::hash<int>{}(value); }
};

template <typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test2()
{
	using Map = hamon::unordered_multimap<S, T, decltype(hamon::ranges::hash), hamon::equal_to<>>;
	using SizeType = typename Map::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().count(hamon::declval<int>())), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().count(hamon::declval<int>())), SizeType>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().count(hamon::declval<int>())), "");
	static_assert(!noexcept(hamon::declval<Map const&>().count(hamon::declval<int>())), "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, CountHeterogeneousTest)
{
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));

	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test2<int>());
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test2<char>());
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test2<float>());
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace count_heterogeneous_test

}	// namespace hamon_unordered_multimap_test

#endif
