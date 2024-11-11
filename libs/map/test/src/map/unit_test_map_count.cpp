/**
 *	@file	unit_test_map_count.cpp
 *
 *	@brief	count のテスト
 *
 *	size_type      count(const key_type& x) const;
 *	template<class K> size_type count(const K& x) const;
 */

#include <hamon/map/map.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_map_test
{

namespace count_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

// size_type count(const key_type& x) const;
template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::map<Key, T>;
	using SizeType = typename Map::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().count(hamon::declval<Key const&>())), SizeType>::value, "");
	static_assert(!noexcept(hamon::declval<Map const&>().count(hamon::declval<Key const&>())), "");

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

	VERIFY(v.count(Key{0}) == 0);
	VERIFY(v.count(Key{1}) == 0);
	VERIFY(v.count(Key{2}) == 1);
	VERIFY(v.count(Key{3}) == 1);
	VERIFY(v.count(Key{4}) == 0);
	VERIFY(v.count(Key{5}) == 1);
	VERIFY(v.count(Key{6}) == 0);
	VERIFY(v.count(Key{7}) == 1);
	VERIFY(v.count(Key{8}) == 0);

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

// template<class K> size_type count(const K& x) const;
MAP_TEST_CONSTEXPR bool test2()
{
	using Map = hamon::map<S, float, hamon::less<>>;
	using SizeType = typename Map::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().count(hamon::declval<int const&>())), SizeType>::value, "");
	static_assert(!noexcept(hamon::declval<Map const&>().count(hamon::declval<int const&>())), "");

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

	VERIFY(v.count(0) == 0);
	VERIFY(v.count(1) == 0);
	VERIFY(v.count(2) == 1);
	VERIFY(v.count(3) == 0);
	VERIFY(v.count(4) == 0);
	VERIFY(v.count(5) == 1);
	VERIFY(v.count(6) == 1);
	VERIFY(v.count(7) == 0);
	VERIFY(v.count(8) == 1);
	VERIFY(v.count(9) == 0);

	return true;
}

#endif

#undef VERIFY

GTEST_TEST(MapTest, CountTest)
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

#if !defined(HAMON_USE_STD_MAP) || \
	defined(__cpp_lib_generic_associative_lookup) && (__cpp_lib_generic_associative_lookup >= 201304L)
	MAP_TEST_CONSTEXPR_EXPECT_TRUE(test2());
#endif
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace count_test

}	// namespace hamon_map_test
