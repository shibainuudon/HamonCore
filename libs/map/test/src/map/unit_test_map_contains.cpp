/**
 *	@file	unit_test_map_contains.cpp
 *
 *	@brief	contains のテスト
 *
 *	bool           contains(const key_type& x) const;
 *	template<class K> bool contains(const K& x) const;
 */

#include <hamon/map/map.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

// P0458R2
#if !defined(HAMON_USE_STD_MAP) || (HAMON_CXX_STANDARD >= 20)

namespace hamon_map_test
{

namespace contains_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

// bool contains(const key_type& x) const;
template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::map<Key, T>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().contains(hamon::declval<Key const&>())), bool>::value, "");
	static_assert(!noexcept(hamon::declval<Map const&>().contains(hamon::declval<Key const&>())), "");

	Map const v
	{
		{Key{5}, T{60}},
		{Key{7}, T{70}},
		{Key{3}, T{40}},
		{Key{3}, T{30}},
		{Key{2}, T{10}},
		{Key{3}, T{50}},
		{Key{2}, T{20}},
	};

	VERIFY(v.contains(Key{0}) == false);
	VERIFY(v.contains(Key{1}) == false);
	VERIFY(v.contains(Key{2}) == true);
	VERIFY(v.contains(Key{3}) == true);
	VERIFY(v.contains(Key{4}) == false);
	VERIFY(v.contains(Key{5}) == true);
	VERIFY(v.contains(Key{6}) == false);
	VERIFY(v.contains(Key{7}) == true);
	VERIFY(v.contains(Key{8}) == false);

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
};

// template<class K> bool contains(const K& x) const;
MAP_TEST_CONSTEXPR bool test2()
{
	using Map = hamon::map<S, float, hamon::less<>>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().contains(hamon::declval<int const&>())), bool>::value, "");
	static_assert(!noexcept(hamon::declval<Map const&>().contains(hamon::declval<int const&>())), "");

	Map const v
	{
		{S{8}, 13.5f},
		{S{2}, 10.5f},
		{S{5}, 11.5f},
		{S{8}, 13.5f},
		{S{5}, 11.5f},
		{S{6}, 12.5f},
		{S{8}, 13.5f},
	};

	VERIFY(v.contains(0) == false);
	VERIFY(v.contains(1) == false);
	VERIFY(v.contains(2) == true);
	VERIFY(v.contains(3) == false);
	VERIFY(v.contains(4) == false);
	VERIFY(v.contains(5) == true);
	VERIFY(v.contains(6) == true);
	VERIFY(v.contains(7) == false);
	VERIFY(v.contains(8) == true);
	VERIFY(v.contains(9) == false);

	return true;
}

#undef VERIFY

GTEST_TEST(MapTest, ContainsTest)
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

	MAP_TEST_CONSTEXPR_EXPECT_TRUE(test2());

	// https://en.cppreference.com/w/cpp/container/map/contains
	{
		hamon::map<int, char> example{{1, 'a'}, {2, 'b'}};
		EXPECT_TRUE(example.contains(2));
		EXPECT_FALSE(example.contains(5));
	}
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace contains_test

}	// namespace hamon_map_test

#endif
