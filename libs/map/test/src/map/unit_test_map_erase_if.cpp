/**
 *	@file	unit_test_map_erase_if.cpp
 *
 *	@brief	erase_if のテスト
 *
 *	template<class Key, class T, class Compare, class Allocator, class Predicate>
 *	typename map<Key, T, Compare, Allocator>::size_type
 *	erase_if(map<Key, T, Compare, Allocator>& c, Predicate pred);
 */

#include <hamon/map/erase_if.hpp>
#include <hamon/map/map.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include <string>
#include <sstream>

namespace hamon_map_test
{

namespace erase_if_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
#endif

struct is_key_1
{
	template <typename T>
	constexpr bool operator()(T const& x) const
	{
		return x.first == 1;
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

MAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::map<int, char>;
	using SizeType = typename Map::size_type;

	static_assert(hamon::is_same<decltype(
		hamon::erase_if(hamon::declval<Map&>(), hamon::declval<is_key_1>())), SizeType>::value, "");
	static_assert(!noexcept(hamon::erase_if(hamon::declval<Map&>(), hamon::declval<is_key_1>())), "");

	{
		Map m =
		{
			{3, 'a'},
			{1, 'b'},
			{4, 'c'},
		};
		auto r = hamon::erase_if(m, is_key_1{});
		VERIFY(r == 1);
		Map const m2 =
		{
			{3, 'a'},
			{4, 'c'},
		};
		VERIFY(hamon::ranges::equal(m, m2));
	}
	return true;
}

#undef VERIFY

template <typename Key, typename T, typename C>
std::string ToString(const hamon::map<Key, T, C>& m)
{
	std::stringstream out;
	for (const auto& n : m)
	{
		out << "[" << n.first << "] = " << n.second << ", ";
	}
	return out.str();
}

GTEST_TEST(MapTest, EraseIfTest)
{
	MAP_TEST_CONSTEXPR_EXPECT_TRUE(test());

	// https://en.cppreference.com/w/cpp/container/map/erase_if
	{
		using Map = hamon::map<int, char>;
		using Pair = typename Map::value_type;

		Map data
		{
			{1, 'a'}, {2, 'b'}, {3, 'c'}, {4, 'd'},
			{5, 'e'}, {4, 'f'}, {5, 'g'}, {5, 'g'},
		};
		EXPECT_EQ("[1] = a, [2] = b, [3] = c, [4] = d, [5] = e, ", ToString(data));

		const auto count = hamon::erase_if(data, [](const Pair& item)
		{
			return (item.first & 1) == 1;
		});
		EXPECT_EQ("[2] = b, [4] = d, ", ToString(data));
		EXPECT_EQ(3u, count);
	}
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace erase_if_test

}	// namespace hamon_map_test
