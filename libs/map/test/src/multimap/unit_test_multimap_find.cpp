/**
 *	@file	unit_test_multimap_find.cpp
 *
 *	@brief	find のテスト
 *
 *	iterator       find(const key_type& x);
 *	const_iterator find(const key_type& x) const;
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

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

// iterator find(const key_type& x);
template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test1()
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
HAMON_CXX20_CONSTEXPR bool test2()
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

#undef VERIFY

GTEST_TEST(MultimapTest, FindTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<int, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<char, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<char, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<char, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<float, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<int, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<int, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<int, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<char, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<char, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<char, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<float, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<float, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<float, float>()));

	// https://en.cppreference.com/w/cpp/container/multimap/find
	{
		// Simple comparison demo.
		hamon::multimap<int, char> example {{1, 'a'}, {2, 'b'}};
		auto search = example.find(2);
		EXPECT_TRUE(search != example.end());
		EXPECT_EQ(2, search->first);
		EXPECT_EQ('b', search->second);
	}
}

}	// namespace find_test

}	// namespace hamon_multimap_test
