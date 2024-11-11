/**
 *	@file	unit_test_map_equal_range.cpp
 *
 *	@brief	equal_range のテスト
 *
 *	pair<iterator, iterator> equal_range(const key_type& x);
 *	pair<const_iterator, const_iterator> equal_range(const key_type& x) const;
 *	template<class K>
 *	pair<iterator, iterator> equal_range(const K& x);
 *	template<class K>
 *	pair<const_iterator, const_iterator> equal_range(const K& x) const;
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

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

// pair<iterator, iterator> equal_range(const key_type& x);
template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::map<Key, T>;
	using Iterator = typename Map::iterator;
#if defined(HAMON_USE_STD_MAP)
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
MAP_TEST_CONSTEXPR bool test2()
{
	using Map = hamon::map<Key, T>;
	using ConstIterator = typename Map::const_iterator;
#if defined(HAMON_USE_STD_MAP)
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
	VERIFY(v.equal_range(Key{2}) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(Key{3}) == Result{hamon::next(v.begin(), 1), hamon::next(v.begin(), 2)});
	VERIFY(v.equal_range(Key{4}) == Result{hamon::next(v.begin(), 2), hamon::next(v.begin(), 2)});
	VERIFY(v.equal_range(Key{5}) == Result{hamon::next(v.begin(), 2), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(Key{6}) == Result{hamon::next(v.begin(), 3), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(Key{7}) == Result{hamon::next(v.begin(), 3), v.end()});
	VERIFY(v.equal_range(Key{8}) == Result{v.end(), v.end()});

	return true;
}

#if !defined(HAMON_USE_STD_MAP) || \
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

// template<class K> pair<iterator, iterator> equal_range(const K& x);
MAP_TEST_CONSTEXPR bool test3()
{
	using Map = hamon::map<S, float, hamon::less<>>;
	using Iterator = typename Map::iterator;
#if defined(HAMON_USE_STD_MAP)
	using Result = std::pair<Iterator, Iterator>;
#else
	using Result = hamon::pair<Iterator, Iterator>;
#endif

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().equal_range(hamon::declval<int const&>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().equal_range(hamon::declval<int const&>())), "");

	Map v;

	VERIFY(v.equal_range(0) == Result{v.end(), v.end()});
	VERIFY(v.equal_range(1) == Result{v.end(), v.end()});
	VERIFY(v.equal_range(2) == Result{v.end(), v.end()});
	VERIFY(v.equal_range(3) == Result{v.end(), v.end()});

	v.emplace(S{2}, 10.0f);

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 0)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 0)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 0), v.end()});
	VERIFY(v.equal_range(3) == Result{v.end(), v.end()});

	v.emplace(S{1}, 20.0f);

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 0)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 1), v.end()});
	VERIFY(v.equal_range(3) == Result{v.end(), v.end()});

	v.emplace(S{0}, 30.0f);

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 1), hamon::next(v.begin(), 2)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 2), v.end()});
	VERIFY(v.equal_range(3) == Result{v.end(), v.end()});

	v.emplace(S{0}, 40.0f);

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 1), hamon::next(v.begin(), 2)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 2), v.end()});
	VERIFY(v.equal_range(3) == Result{v.end(), v.end()});

	v.emplace(S{0}, 50.0f);

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 1), hamon::next(v.begin(), 2)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 2), v.end()});
	VERIFY(v.equal_range(3) == Result{v.end(), v.end()});

	v.emplace(S{1}, 60.0f);

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 1), hamon::next(v.begin(), 2)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 2), v.end()});
	VERIFY(v.equal_range(3) == Result{v.end(), v.end()});

	return true;
}

// template<class K> pair<const_iterator, const_iterator> equal_range(const K& x) const;
MAP_TEST_CONSTEXPR bool test4()
{
	using Map = hamon::map<S, float, hamon::less<>>;
	using ConstIterator = typename Map::const_iterator;
#if defined(HAMON_USE_STD_MAP)
	using Result = std::pair<ConstIterator, ConstIterator>;
#else
	using Result = hamon::pair<ConstIterator, ConstIterator>;
#endif

	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().equal_range(hamon::declval<int const&>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Map const&>().equal_range(hamon::declval<int const&>())), "");

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

	VERIFY(v.equal_range(0) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 0)});
	VERIFY(v.equal_range(1) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 0)});
	VERIFY(v.equal_range(2) == Result{hamon::next(v.begin(), 0), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(3) == Result{hamon::next(v.begin(), 1), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(4) == Result{hamon::next(v.begin(), 1), hamon::next(v.begin(), 1)});
	VERIFY(v.equal_range(5) == Result{hamon::next(v.begin(), 1), hamon::next(v.begin(), 2)});
	VERIFY(v.equal_range(6) == Result{hamon::next(v.begin(), 2), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(7) == Result{hamon::next(v.begin(), 3), hamon::next(v.begin(), 3)});
	VERIFY(v.equal_range(8) == Result{hamon::next(v.begin(), 3), v.end()});
	VERIFY(v.equal_range(9) == Result{v.end(), v.end()});

	return true;
}

#endif

#undef VERIFY

GTEST_TEST(MapTest, EqualRangeTest)
{
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));

	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<int, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<int, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<int, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<char, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<char, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<char, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<float, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<float, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<float, float>()));

#if !defined(HAMON_USE_STD_MAP) || \
	defined(__cpp_lib_generic_associative_lookup) && (__cpp_lib_generic_associative_lookup >= 201304L)
	MAP_TEST_CONSTEXPR_EXPECT_TRUE(test3());
	MAP_TEST_CONSTEXPR_EXPECT_TRUE(test4());
#endif
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace equal_range_test

}	// namespace hamon_map_test
