/**
 *	@file	unit_test_unordered_map_erase_position.cpp
 *
 *	@brief	erase のテスト
 *
 *	constexpr iterator  erase(iterator position);
 *	constexpr iterator  erase(const_iterator position);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_map_test_helper.hpp"

namespace hamon_unordered_map_test
{

namespace erase_position_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Map = hamon::unordered_map<Key, T>;
	using Iterator = typename Map::iterator;
	using ConstIterator = typename Map::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().erase(hamon::declval<Iterator>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().erase(hamon::declval<ConstIterator>())), Iterator>::value, "");
	//static_assert( noexcept(hamon::declval<Map&>().erase(hamon::declval<Iterator>())), "");
	//static_assert( noexcept(hamon::declval<Map&>().erase(hamon::declval<ConstIterator>())), "");

	Map v
	{
		{Key{5}, T{60}},
		{Key{7}, T{70}},
		{Key{1}, T{40}},
		{Key{3}, T{30}},
		{Key{2}, T{10}},
		{Key{4}, T{50}},
		{Key{0}, T{20}},
	};
	VERIFY(v.size() == 7);
	{
		auto i = v.begin();
		auto j = hamon::next(i);
		auto r = v.erase(i);
		VERIFY(r == j);
	}
	VERIFY(v.size() == 6);
	{
		auto i = hamon::next(v.cbegin(), 5);
		auto j = hamon::next(i);
		auto r = v.erase(i);
		VERIFY(r == j);
	}
	VERIFY(v.size() == 5);
	{
		auto i = hamon::next(v.begin(), 1);
		auto j = hamon::next(i);
		auto r = v.erase(i);
		VERIFY(r == j);
	}
	VERIFY(v.size() == 4);

	return true;
}

template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test_noexcept()
{
	{
		using Map = hamon::unordered_map<Key, T, NoThrowHash<Key>, NoThrowEqualTo<Key>>;
		using Iterator = typename Map::iterator;
		using ConstIterator = typename Map::const_iterator;
		static_assert( noexcept(hamon::declval<Map&>().erase(hamon::declval<Iterator>())), "");
		static_assert( noexcept(hamon::declval<Map&>().erase(hamon::declval<ConstIterator>())), "");
	}
	{
		using Map = hamon::unordered_map<Key, T, NoThrowHash<Key>, ThrowEqualTo<Key>>;
		using Iterator = typename Map::iterator;
		using ConstIterator = typename Map::const_iterator;
		static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<Iterator>())), "");
		static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<ConstIterator>())), "");
	}
	{
		using Map = hamon::unordered_map<Key, T, ThrowHash<Key>, NoThrowEqualTo<Key>>;
		using Iterator = typename Map::iterator;
		using ConstIterator = typename Map::const_iterator;
		static_assert( noexcept(hamon::declval<Map&>().erase(hamon::declval<Iterator>())), "");
		static_assert( noexcept(hamon::declval<Map&>().erase(hamon::declval<ConstIterator>())), "");
	}
	{
		using Map = hamon::unordered_map<Key, T, ThrowHash<Key>, ThrowEqualTo<Key>>;
		using Iterator = typename Map::iterator;
		using ConstIterator = typename Map::const_iterator;
		static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<Iterator>())), "");
		static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<ConstIterator>())), "");
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, ErasePositionTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<int, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<int, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<int, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<char, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<char, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<char, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<float, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<float, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test_noexcept<float, float>()));
}

}	// namespace erase_position_test

}	// namespace hamon_unordered_map_test
