/**
 *	@file	unit_test_map_lower_bound.cpp
 *
 *	@brief	lower_bound のテスト
 *
 *	iterator       lower_bound(const key_type& x);
 *	const_iterator lower_bound(const key_type& x) const;
 */

#include <hamon/map/map.hpp>
#include <hamon/functional.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_map_test
{

namespace lower_bound_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

// iterator lower_bound(const key_type& x);
template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test1()
{
	using Map = hamon::map<Key, T>;
	using Iterator = typename Map::iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().lower_bound(hamon::declval<Key const&>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().lower_bound(hamon::declval<Key const&>())), "");

	Map v;

	VERIFY(v.lower_bound(Key{0}) == v.end());
	VERIFY(v.lower_bound(Key{1}) == v.end());
	VERIFY(v.lower_bound(Key{2}) == v.end());
	VERIFY(v.lower_bound(Key{3}) == v.end());

	v.emplace(Key{1}, T{10});

	VERIFY(v.lower_bound(Key{0}) == hamon::next(v.begin(), 0));
	VERIFY(v.lower_bound(Key{1}) == hamon::next(v.begin(), 0));
	VERIFY(v.lower_bound(Key{2}) == v.end());
	VERIFY(v.lower_bound(Key{3}) == v.end());

	v.emplace(Key{2}, T{20});

	VERIFY(v.lower_bound(Key{0}) == hamon::next(v.begin(), 0));
	VERIFY(v.lower_bound(Key{1}) == hamon::next(v.begin(), 0));
	VERIFY(v.lower_bound(Key{2}) == hamon::next(v.begin(), 1));
	VERIFY(v.lower_bound(Key{3}) == v.end());

	v.emplace(Key{0}, T{30});

	VERIFY(v.lower_bound(Key{0}) == hamon::next(v.begin(), 0));
	VERIFY(v.lower_bound(Key{1}) == hamon::next(v.begin(), 1));
	VERIFY(v.lower_bound(Key{2}) == hamon::next(v.begin(), 2));
	VERIFY(v.lower_bound(Key{3}) == v.end());

	return true;
}

// const_iterator lower_bound(const key_type& x) const;
template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test2()
{
	using Map = hamon::map<Key, T>;
	using ConstIterator = typename Map::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().lower_bound(hamon::declval<Key const&>())), ConstIterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map const&>().lower_bound(hamon::declval<Key const&>())), "");

	Map const v
	{
		{Key{2}, T{10}},
		{Key{3}, T{40}},
		{Key{3}, T{50}},
		{Key{2}, T{20}},
		{Key{7}, T{70}},
		{Key{5}, T{60}},
		{Key{3}, T{30}},
	};

	VERIFY(v.lower_bound(Key{0}) == hamon::next(v.begin(), 0));
	VERIFY(v.lower_bound(Key{1}) == hamon::next(v.begin(), 0));
	VERIFY(v.lower_bound(Key{2}) == hamon::next(v.begin(), 0));
	VERIFY(v.lower_bound(Key{3}) == hamon::next(v.begin(), 1));
	VERIFY(v.lower_bound(Key{4}) == hamon::next(v.begin(), 2));
	VERIFY(v.lower_bound(Key{5}) == hamon::next(v.begin(), 2));
	VERIFY(v.lower_bound(Key{6}) == hamon::next(v.begin(), 3));
	VERIFY(v.lower_bound(Key{7}) == hamon::next(v.begin(), 3));
	VERIFY(v.lower_bound(Key{8}) == v.end());

	return true;
}

#undef VERIFY

GTEST_TEST(MapTest, LowerBoundTest)
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
}

}	// namespace lower_bound_test

}	// namespace hamon_map_test
