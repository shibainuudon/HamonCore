﻿/**
 *	@file	unit_test_unordered_multimap_insert_heterogeneous.cpp
 *
 *	@brief	insert のテスト
 *
 *	template<class P> constexpr iterator insert(P&& obj);
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multimap_test
{

namespace insert_heterogeneous_test
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
	using Map = hamon::unordered_multimap<Key, T>;
	using Iterator = typename Map::iterator;

	// from std::pair

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::pair<int, float>>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::pair<char, int>>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::pair<float, char>>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::pair<int, float>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::pair<char, int>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::pair<float, char>>())), "");

#if 0
	Map v;
	{
		auto r = v.insert(std::make_pair(1, 0.5f));
		VERIFY(r.first->first == 1);
		VERIFY(r.first->second == 0.5);
		VERIFY(r.second == true);

		VERIFY(v.size() == 1);
		VERIFY(v[1] == 0.5);
	}
	{
		auto r = v.insert(std::make_pair(char{2}, 1.5));
		VERIFY(r.first->first == 2);
		VERIFY(r.first->second == 1.5);
		VERIFY(r.second == true);

		VERIFY(v.size() == 2);
		VERIFY(v[1] == 0.5);
		VERIFY(v[2] == 1.5);
	}
	{
		auto r = v.insert(std::make_pair(short{0}, 2.5));
		VERIFY(r.first->first == 0);
		VERIFY(r.first->second == 2.5);
		VERIFY(r.second == true);

		VERIFY(v.size() == 3);
		VERIFY(v[0] == 2.5);
		VERIFY(v[1] == 0.5);
		VERIFY(v[2] == 1.5);
	}
	{
		auto r = v.insert(std::make_pair(char{1}, 3.5f));
		VERIFY(r.first->first == 1);
		VERIFY(r.first->second == 0.5);
		VERIFY(r.second == false);

		VERIFY(v.size() == 3);
		VERIFY(v[0] == 2.5);
		VERIFY(v[1] == 0.5);
		VERIFY(v[2] == 1.5);
	}
#endif

	return true;
}

template <typename Map, typename P, typename = void>
struct is_insert_invocable
	: public hamon::false_type {};

template <typename Map, typename P>
struct is_insert_invocable<Map, P, hamon::void_t<decltype(hamon::declval<Map>().insert(hamon::declval<P>()))>>
	: public hamon::true_type {};

struct S1
{
	explicit S1(int);
};

struct S2
{
	explicit S2(S1 const&);
};

UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test2()
{
	using Map1 = hamon::unordered_multimap<int, S1>;
	using Map2 = hamon::unordered_multimap<int, S2>;

	static_assert( is_insert_invocable<Map1&, std::pair<int, int>>::value, "");
	static_assert(!is_insert_invocable<Map2&, std::pair<int, int>>::value, "");
	static_assert( is_insert_invocable<Map2&, std::pair<int, S1>>::value, "");

	static_assert(!is_insert_invocable<Map1 const&, std::pair<int, int>>::value, "");
	static_assert(!is_insert_invocable<Map2 const&, std::pair<int, int>>::value, "");
	static_assert(!is_insert_invocable<Map2 const&, std::pair<int, S1>>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, InsertHeterogeneousTest)
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

	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test2());
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace insert_heterogeneous_test

}	// namespace hamon_unordered_multimap_test
