/**
 *	@file	unit_test_map_equal_range.cpp
 *
 *	@brief	equal_range のテスト
 *
 *	pair<iterator, iterator> equal_range(const key_type& x);
 *	pair<const_iterator, const_iterator> equal_range(const key_type& x) const;
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

namespace equal_range_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

// pair<iterator, iterator> equal_range(const key_type& x);
template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test1()
{
	using Map = hamon::map<Key, T>;
	using Iterator = typename Map::iterator;
	using Result = hamon::pair<Iterator, Iterator>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().equal_range(hamon::declval<Key const&>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().equal_range(hamon::declval<Key const&>())), "");

	Map v;

	VERIFY(v.equal_range(Key{0}) == Result{v.end(), v.end()});
	VERIFY(v.equal_range(Key{1}) == Result{v.end(), v.end()});
	VERIFY(v.equal_range(Key{2}) == Result{v.end(), v.end()});
	VERIFY(v.equal_range(Key{3}) == Result{v.end(), v.end()});

	v.emplace(Key{1}, T{10});

	VERIFY(v.equal_range(Key{0}) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 0)});
	VERIFY(v.equal_range(Key{1}) == Result{hamon::next(v.begin(), 0), v.end()});
	VERIFY(v.equal_range(Key{2}) == Result{v.end(), v.end()});
	VERIFY(v.equal_range(Key{3}) == Result{v.end(), v.end()});

	v.emplace(Key{2}, T{20});

	VERIFY(v.equal_range(Key{0}) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 0)});
	VERIFY(v.equal_range(Key{1}) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(Key{2}) == Result{hamon::next(v.begin(), 1), v.end()});
	VERIFY(v.equal_range(Key{3}) == Result{v.end(), v.end()});

	v.emplace(Key{0}, T{30});

	VERIFY(v.equal_range(Key{0}) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(Key{1}) == Result{hamon::next(v.begin(), 1), hamon::next(v.begin(), 2)});
	VERIFY(v.equal_range(Key{2}) == Result{hamon::next(v.begin(), 2), v.end()});
	VERIFY(v.equal_range(Key{3}) == Result{v.end(), v.end()});

	v.emplace(Key{1}, T{40});

	VERIFY(v.equal_range(Key{0}) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(Key{1}) == Result{hamon::next(v.begin(), 1), hamon::next(v.begin(), 2)});
	VERIFY(v.equal_range(Key{2}) == Result{hamon::next(v.begin(), 2), v.end()});
	VERIFY(v.equal_range(Key{3}) == Result{v.end(), v.end()});

	v.emplace(Key{0}, T{50});

	VERIFY(v.equal_range(Key{0}) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(Key{1}) == Result{hamon::next(v.begin(), 1), hamon::next(v.begin(), 2)});
	VERIFY(v.equal_range(Key{2}) == Result{hamon::next(v.begin(), 2), v.end()});
	VERIFY(v.equal_range(Key{3}) == Result{v.end(), v.end()});

	v.emplace(Key{2}, T{60});

	VERIFY(v.equal_range(Key{0}) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(Key{1}) == Result{hamon::next(v.begin(), 1), hamon::next(v.begin(), 2)});
	VERIFY(v.equal_range(Key{2}) == Result{hamon::next(v.begin(), 2), v.end()});
	VERIFY(v.equal_range(Key{3}) == Result{v.end(), v.end()});

	return true;
}

// pair<const_iterator, const_iterator> equal_range(const key_type& x) const;
template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test2()
{
	using Map = hamon::map<Key, T>;
	using ConstIterator = typename Map::const_iterator;
	using Result = hamon::pair<ConstIterator, ConstIterator>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().equal_range(hamon::declval<Key const&>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Map const&>().equal_range(hamon::declval<Key const&>())), "");

	Map const v
	{
		{Key{2}, T{10}},
		{Key{2}, T{20}},
		{Key{3}, T{30}},
		{Key{3}, T{40}},
		{Key{3}, T{50}},
		{Key{5}, T{60}},
		{Key{7}, T{70}},
	};

	VERIFY(v.equal_range(Key{0}) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 0)});
	VERIFY(v.equal_range(Key{1}) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 0)});
	VERIFY(v.equal_range(Key{2}) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(Key{3}) == Result{hamon::next(v.begin(), 1), hamon::next(v.begin(), 2)});
	VERIFY(v.equal_range(Key{4}) == Result{hamon::next(v.begin(), 2), hamon::next(v.begin(), 2)});
	VERIFY(v.equal_range(Key{5}) == Result{hamon::next(v.begin(), 2), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(Key{6}) == Result{hamon::next(v.begin(), 3), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(Key{7}) == Result{hamon::next(v.begin(), 3), v.end()});
	VERIFY(v.equal_range(Key{8}) == Result{v.end(), v.end()});

	return true;
}

#undef VERIFY

GTEST_TEST(MapTest, EqualRangeTest)
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

	// https://en.cppreference.com/w/cpp/container/map/equal_range
	{
		const hamon::map<int, const char*> m
		{
			{0, "zero"},
			{1, "one"},
			{2, "two"}
		};

		auto p = m.equal_range(1);
		EXPECT_EQ(1, p.first->first);
		EXPECT_STREQ("one", p.first->second);
		EXPECT_EQ(2, p.second->first);
		EXPECT_STREQ("two", p.second->second);

		auto pp = m.equal_range(-1);
		EXPECT_TRUE(pp.first == m.begin());
		EXPECT_TRUE(pp.second == m.begin());

		auto ppp = m.equal_range(3);
		EXPECT_TRUE(ppp.first == m.end());
		EXPECT_TRUE(ppp.second == m.end());
	}
}

}	// namespace equal_range_test

}	// namespace hamon_map_test
