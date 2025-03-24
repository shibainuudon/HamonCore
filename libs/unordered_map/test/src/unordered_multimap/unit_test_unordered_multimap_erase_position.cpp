/**
 *	@file	unit_test_unordered_multimap_erase_position.cpp
 *
 *	@brief	erase のテスト
 *
 *	constexpr iterator  erase(iterator position);
 *	constexpr iterator  erase(const_iterator position);
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multimap_test_helper.hpp"

namespace hamon_unordered_multimap_test
{

namespace erase_position_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::unordered_multimap<Key, T>;
	using Iterator = typename Map::iterator;
	using ConstIterator = typename Map::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().erase(hamon::declval<Iterator>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().erase(hamon::declval<ConstIterator>())), Iterator>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
	//static_assert( noexcept(hamon::declval<Map&>().erase(hamon::declval<Iterator>())), "");
	//static_assert( noexcept(hamon::declval<Map&>().erase(hamon::declval<ConstIterator>())), "");
#endif

	Map v
	{
		{Key{11}, T{60}},
		{Key{13}, T{70}},
		{Key{12}, T{40}},
		{Key{14}, T{30}},
		{Key{14}, T{10}},
		{Key{14}, T{50}},
		{Key{10}, T{20}},
		{Key{14}, T{50}},
	};
	VERIFY(v.size() == 8);
	{
		auto i = v.begin();
		auto j = hamon::next(i);
		auto r = v.erase(i);
		VERIFY(r == j);
	}
	VERIFY(v.size() == 7);
	{
		auto i = hamon::next(v.cbegin(), 2);
		auto j = hamon::next(i);
		auto r = v.erase(i);
		VERIFY(r == j);
	}
	VERIFY(v.size() == 6);
	{
		auto i = hamon::next(v.begin(), 3);
		auto j = hamon::next(i);
		auto r = v.erase(i);
		VERIFY(r == j);
	}
	VERIFY(v.size() == 5);

	return true;
}

template <typename Key, typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test_noexcept()
{
#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
	{
		using Map = hamon::unordered_multimap<Key, T, NoThrowHash<Key>, NoThrowEqualTo<Key>>;
		using Iterator = typename Map::iterator;
		using ConstIterator = typename Map::const_iterator;
		static_assert( noexcept(hamon::declval<Map&>().erase(hamon::declval<Iterator>())), "");
		static_assert( noexcept(hamon::declval<Map&>().erase(hamon::declval<ConstIterator>())), "");
	}
	{
		using Map = hamon::unordered_multimap<Key, T, NoThrowHash<Key>, ThrowEqualTo<Key>>;
		using Iterator = typename Map::iterator;
		using ConstIterator = typename Map::const_iterator;
		static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<Iterator>())), "");
		static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<ConstIterator>())), "");
	}
	{
		using Map = hamon::unordered_multimap<Key, T, ThrowHash<Key>, NoThrowEqualTo<Key>>;
		using Iterator = typename Map::iterator;
		using ConstIterator = typename Map::const_iterator;
		static_assert( noexcept(hamon::declval<Map&>().erase(hamon::declval<Iterator>())), "");
		static_assert( noexcept(hamon::declval<Map&>().erase(hamon::declval<ConstIterator>())), "");
	}
	{
		using Map = hamon::unordered_multimap<Key, T, ThrowHash<Key>, ThrowEqualTo<Key>>;
		using Iterator = typename Map::iterator;
		using ConstIterator = typename Map::const_iterator;
		static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<Iterator>())), "");
		static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<ConstIterator>())), "");
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, ErasePositionTest)
{
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<int, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<int, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<int, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<char, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<char, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<char, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<float, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<float, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<float, float>()));
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace erase_position_test

}	// namespace hamon_unordered_multimap_test
