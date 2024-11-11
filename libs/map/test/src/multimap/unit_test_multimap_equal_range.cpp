/**
 *	@file	unit_test_multimap_equal_range.cpp
 *
 *	@brief	equal_range のテスト
 *
 *	pair<iterator, iterator>               equal_range(const key_type& x);
 *	pair<const_iterator, const_iterator>   equal_range(const key_type& x) const;
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

namespace equal_range_test
{

#if !defined(HAMON_USE_STD_MULTIMAP)
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

// pair<iterator, iterator> equal_range(const key_type& x);
template <typename Key, typename T>
MULTIMAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::multimap<Key, T>;
	using Iterator = typename Map::iterator;
#if defined(HAMON_USE_STD_MULTIMAP)
	using Result = std::pair<Iterator, Iterator>;
#else
	using Result = hamon::pair<Iterator, Iterator>;
#endif

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
	VERIFY(v.equal_range(Key{1}) == Result{hamon::next(v.begin(), 1), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(Key{2}) == Result{hamon::next(v.begin(), 3), v.end()});
	VERIFY(v.equal_range(Key{3}) == Result{v.end(), v.end()});

	v.emplace(Key{0}, T{50});

	VERIFY(v.equal_range(Key{0}) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 2)});
	VERIFY(v.equal_range(Key{1}) == Result{hamon::next(v.begin(), 2), hamon::next(v.begin(), 4)});
	VERIFY(v.equal_range(Key{2}) == Result{hamon::next(v.begin(), 4), v.end()});
	VERIFY(v.equal_range(Key{3}) == Result{v.end(), v.end()});

	v.emplace(Key{2}, T{60});

	VERIFY(v.equal_range(Key{0}) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 2)});
	VERIFY(v.equal_range(Key{1}) == Result{hamon::next(v.begin(), 2), hamon::next(v.begin(), 4)});
	VERIFY(v.equal_range(Key{2}) == Result{hamon::next(v.begin(), 4), v.end()});
	VERIFY(v.equal_range(Key{3}) == Result{v.end(), v.end()});

	return true;
}

// pair<const_iterator, const_iterator> equal_range(const key_type& x) const;
template <typename Key, typename T>
MULTIMAP_TEST_CONSTEXPR bool test2()
{
	using Map = hamon::multimap<Key, T>;
	using ConstIterator = typename Map::const_iterator;
#if defined(HAMON_USE_STD_MULTIMAP)
	using Result = std::pair<ConstIterator, ConstIterator>;
#else
	using Result = hamon::pair<ConstIterator, ConstIterator>;
#endif

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
	VERIFY(v.equal_range(Key{2}) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 2)});
	VERIFY(v.equal_range(Key{3}) == Result{hamon::next(v.begin(), 2), hamon::next(v.begin(), 5)});
	VERIFY(v.equal_range(Key{4}) == Result{hamon::next(v.begin(), 5), hamon::next(v.begin(), 5)});
	VERIFY(v.equal_range(Key{5}) == Result{hamon::next(v.begin(), 5), hamon::next(v.begin(), 6)});
	VERIFY(v.equal_range(Key{6}) == Result{hamon::next(v.begin(), 6), hamon::next(v.begin(), 6)});
	VERIFY(v.equal_range(Key{7}) == Result{hamon::next(v.begin(), 6), v.end()});
	VERIFY(v.equal_range(Key{8}) == Result{v.end(), v.end()});

	return true;
}

#undef VERIFY

GTEST_TEST(MultimapTest, EqualRangeTest)
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

	// https://en.cppreference.com/w/cpp/container/multimap/equal_range
	{
		hamon::multimap<int, char> dict
		{
			{1, 'A'},
			{2, 'B'},
			{2, 'C'},
			{2, 'D'},
			{4, 'E'},
			{3, 'F'}
		};

		auto range = dict.equal_range(2);
		auto i = range.first;
		EXPECT_TRUE(i != range.second);
		EXPECT_EQ(2, i->first);
		EXPECT_EQ('B', i->second);
		++i;
		EXPECT_TRUE(i != range.second);
		EXPECT_EQ(2, i->first);
		EXPECT_EQ('C', i->second);
		++i;
		EXPECT_TRUE(i != range.second);
		EXPECT_EQ(2, i->first);
		EXPECT_EQ('D', i->second);
		++i;
		EXPECT_TRUE(i == range.second);
	}
}

#undef MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTIMAP_TEST_CONSTEXPR

}	// namespace equal_range_test

}	// namespace hamon_multimap_test
