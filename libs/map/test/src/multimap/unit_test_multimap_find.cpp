﻿/**
 *	@file	unit_test_multimap_find.cpp
 *
 *	@brief	find のテスト
 *
 *	iterator       find(const key_type& x);
 *	const_iterator find(const key_type& x) const;
 *	template<class K> iterator       find(const K& x);
 *	template<class K> const_iterator find(const K& x) const;
 */

#include <hamon/map/multimap.hpp>
#include <hamon/functional.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multimap_test
{

namespace find_test
{

#if !defined(HAMON_USE_STD_MULTIMAP)
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

// iterator find(const key_type& x);
template <typename Key, typename T>
MULTIMAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::multimap<Key, T>;
	using Iterator = typename Map::iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().find(hamon::declval<Key const&>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().find(hamon::declval<Key const&>())), "");

	Map v;

	VERIFY(v.find(Key{0}) == v.end());
	VERIFY(v.find(Key{1}) == v.end());
	VERIFY(v.find(Key{2}) == v.end());
	VERIFY(v.find(Key{3}) == v.end());

	v.emplace(Key{1}, T{10});

	VERIFY(v.find(Key{0}) == v.end());
	VERIFY(v.find(Key{1}) == hamon::next(v.begin(), 0));
	VERIFY(v.find(Key{2}) == v.end());
	VERIFY(v.find(Key{3}) == v.end());

	v.emplace(Key{2}, T{20});

	VERIFY(v.find(Key{0}) == v.end());
	VERIFY(v.find(Key{1}) == hamon::next(v.begin(), 0));
	VERIFY(v.find(Key{2}) == hamon::next(v.begin(), 1));
	VERIFY(v.find(Key{3}) == v.end());

	v.emplace(Key{0}, T{30});

	VERIFY(v.find(Key{0}) == hamon::next(v.begin(), 0));
	VERIFY(v.find(Key{1}) == hamon::next(v.begin(), 1));
	VERIFY(v.find(Key{2}) == hamon::next(v.begin(), 2));
	VERIFY(v.find(Key{3}) == v.end());

	v.emplace(Key{1}, T{40});

	VERIFY(v.find(Key{0}) == hamon::next(v.begin(), 0));
	VERIFY(v.find(Key{1}) == hamon::next(v.begin(), 1));
	VERIFY(v.find(Key{2}) == hamon::next(v.begin(), 3));
	VERIFY(v.find(Key{3}) == v.end());

	v.emplace(Key{0}, T{50});

	VERIFY(v.find(Key{0}) == hamon::next(v.begin(), 0));
	VERIFY(v.find(Key{1}) == hamon::next(v.begin(), 2));
	VERIFY(v.find(Key{2}) == hamon::next(v.begin(), 4));
	VERIFY(v.find(Key{3}) == v.end());

	v.emplace(Key{2}, T{60});

	VERIFY(v.find(Key{0}) == hamon::next(v.begin(), 0));
	VERIFY(v.find(Key{1}) == hamon::next(v.begin(), 2));
	VERIFY(v.find(Key{2}) == hamon::next(v.begin(), 4));
	VERIFY(v.find(Key{3}) == v.end());

	return true;
}

// const_iterator find(const key_type& x) const;
template <typename Key, typename T>
MULTIMAP_TEST_CONSTEXPR bool test2()
{
	using Map = hamon::multimap<Key, T>;
	using ConstIterator = typename Map::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().find(hamon::declval<Key const&>())), ConstIterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map const&>().find(hamon::declval<Key const&>())), "");

	Map const v
	{
		{Key{3}, T{30}},
		{Key{5}, T{60}},
		{Key{3}, T{40}},
		{Key{3}, T{50}},
		{Key{7}, T{70}},
		{Key{2}, T{10}},
		{Key{2}, T{20}},
	};

	VERIFY(v.find(Key{0}) == v.end());
	VERIFY(v.find(Key{1}) == v.end());
	VERIFY(v.find(Key{2}) == hamon::next(v.begin(), 0));
	VERIFY(v.find(Key{3}) == hamon::next(v.begin(), 2));
	VERIFY(v.find(Key{4}) == v.end());
	VERIFY(v.find(Key{5}) == hamon::next(v.begin(), 5));
	VERIFY(v.find(Key{6}) == v.end());
	VERIFY(v.find(Key{7}) == hamon::next(v.begin(), 6));
	VERIFY(v.find(Key{8}) == v.end());

	return true;
}

#if !defined(HAMON_USE_STD_MULTIMAP) || \
	defined(__cpp_lib_generic_associative_lookup) && (__cpp_lib_generic_associative_lookup >= 201304L)

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
};

// template<class K> iterator find(const K& x);
MULTIMAP_TEST_CONSTEXPR bool test3()
{
	using Map = hamon::multimap<S, float, hamon::less<>>;
	using Iterator = typename Map::iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().find(hamon::declval<int const&>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().find(hamon::declval<int const&>())), "");

	Map v;

	VERIFY(v.find(0) == v.end());
	VERIFY(v.find(1) == v.end());
	VERIFY(v.find(2) == v.end());
	VERIFY(v.find(3) == v.end());

	v.emplace(S{2}, 10.0f);

	VERIFY(v.find(0) == v.end());
	VERIFY(v.find(1) == v.end());
	VERIFY(v.find(2) == hamon::next(v.begin(), 0));
	VERIFY(v.find(3) == v.end());

	v.emplace(S{1}, 20.0f);

	VERIFY(v.find(0) == v.end());
	VERIFY(v.find(1) == hamon::next(v.begin(), 0));
	VERIFY(v.find(2) == hamon::next(v.begin(), 1));
	VERIFY(v.find(3) == v.end());

	v.emplace(S{0}, 30.0f);

	VERIFY(v.find(0) == hamon::next(v.begin(), 0));
	VERIFY(v.find(1) == hamon::next(v.begin(), 1));
	VERIFY(v.find(2) == hamon::next(v.begin(), 2));
	VERIFY(v.find(3) == v.end());

	v.emplace(S{0}, 40.0f);

	VERIFY(v.find(0) == hamon::next(v.begin(), 0));
	VERIFY(v.find(1) == hamon::next(v.begin(), 2));
	VERIFY(v.find(2) == hamon::next(v.begin(), 3));
	VERIFY(v.find(3) == v.end());

	v.emplace(S{0}, 50.0f);

	VERIFY(v.find(0) == hamon::next(v.begin(), 0));
	VERIFY(v.find(1) == hamon::next(v.begin(), 3));
	VERIFY(v.find(2) == hamon::next(v.begin(), 4));
	VERIFY(v.find(3) == v.end());

	v.emplace(S{1}, 60.0f);

	VERIFY(v.find(0) == hamon::next(v.begin(), 0));
	VERIFY(v.find(1) == hamon::next(v.begin(), 3));
	VERIFY(v.find(2) == hamon::next(v.begin(), 5));
	VERIFY(v.find(3) == v.end());

	return true;
}

// template<class K> const_iterator find(const K& x) const;
MULTIMAP_TEST_CONSTEXPR bool test4()
{
	using Map = hamon::multimap<S, float, hamon::less<>>;
	using ConstIterator = typename Map::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().find(hamon::declval<int const&>())), ConstIterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map const&>().find(hamon::declval<int const&>())), "");

	Map const v
	{
		{S{2}, 10.5f},
		{S{5}, 11.5f},
		{S{5}, 11.5f},
		{S{6}, 12.5f},
		{S{8}, 13.5f},
		{S{8}, 13.5f},
		{S{8}, 13.5f},
	};

	VERIFY(v.find(0) == v.end());
	VERIFY(v.find(1) == v.end());
	VERIFY(v.find(2) == hamon::next(v.begin(), 0));
	VERIFY(v.find(3) == v.end());
	VERIFY(v.find(4) == v.end());
	VERIFY(v.find(5) == hamon::next(v.begin(), 1));
	VERIFY(v.find(6) == hamon::next(v.begin(), 3));
	VERIFY(v.find(7) == v.end());
	VERIFY(v.find(8) == hamon::next(v.begin(), 4));
	VERIFY(v.find(9) == v.end());

	return true;
}

#endif

#undef VERIFY

GTEST_TEST(MultimapTest, FindTest)
{
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, float>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));

	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<int, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<int, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<int, float>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<char, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<char, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<char, float>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<float, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<float, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<float, float>()));

#if !defined(HAMON_USE_STD_MULTIMAP) || \
	defined(__cpp_lib_generic_associative_lookup) && (__cpp_lib_generic_associative_lookup >= 201304L)
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test3());
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE(test4());
#endif
}

#undef MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTIMAP_TEST_CONSTEXPR

}	// namespace find_test

}	// namespace hamon_multimap_test