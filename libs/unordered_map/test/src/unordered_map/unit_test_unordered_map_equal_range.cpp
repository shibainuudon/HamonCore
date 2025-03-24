/**
 *	@file	unit_test_unordered_map_equal_range.cpp
 *
 *	@brief	equal_range のテスト
 *
 *	constexpr pair<iterator, iterator>               equal_range(const key_type& k);
 *	constexpr pair<const_iterator, const_iterator>   equal_range(const key_type& k) const;
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/iterator/distance.hpp>
#include <hamon/pair/pair.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_map_test_helper.hpp"

namespace hamon_unordered_map_test
{

namespace equal_range_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::unordered_map<Key, T>;
	using SizeType = typename Map::size_type;
	using Iterator = typename Map::iterator;
	using ConstIterator = typename Map::const_iterator;
#if defined(HAMON_USE_STD_UNORDERED_MAP)
	using Result1 = std::pair<Iterator, Iterator>;
	using Result2 = std::pair<ConstIterator, ConstIterator>;
#else
	using Result1 = hamon::pair<Iterator, Iterator>;
	using Result2 = hamon::pair<ConstIterator, ConstIterator>;
#endif

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().equal_range(hamon::declval<Key const&>())), Result1>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().equal_range(hamon::declval<Key const&>())), Result2>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MAP)
	//static_assert( noexcept(hamon::declval<Map&>().equal_range(hamon::declval<Key const&>())), "");
	//static_assert( noexcept(hamon::declval<Map const&>().equal_range(hamon::declval<Key const&>())), "");
#endif

	{
		auto check = [](Map& v, Key k, SizeType size)
		{
			auto r = v.equal_range(k);
			VERIFY(SizeType(hamon::distance(r.first, r.second)) == size);
			for (auto it = r.first; it != r.second; ++it)
			{
				VERIFY(it->first == k);
			}
			return true;
		};

		Map v
		{
			{Key{5}, T{60}},
			{Key{7}, T{70}},
			{Key{3}, T{40}},
			{Key{3}, T{30}},
			{Key{2}, T{10}},
			{Key{3}, T{50}},
			{Key{2}, T{20}},
		};

		VERIFY(check(v, Key{0}, 0));
		VERIFY(check(v, Key{1}, 0));
		VERIFY(check(v, Key{2}, 1));
		VERIFY(check(v, Key{3}, 1));
		VERIFY(check(v, Key{4}, 0));
		VERIFY(check(v, Key{5}, 1));
		VERIFY(check(v, Key{6}, 0));
		VERIFY(check(v, Key{7}, 1));
	}
	{
		auto check = [](Map const& v, Key k, SizeType size)
		{
			auto r = v.equal_range(k);
			VERIFY(SizeType(hamon::distance(r.first, r.second)) == size);
			for (auto it = r.first; it != r.second; ++it)
			{
				VERIFY(it->first == k);
			}
			return true;
		};

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

		VERIFY(check(v, Key{0}, 0));
		VERIFY(check(v, Key{1}, 0));
		VERIFY(check(v, Key{2}, 1));
		VERIFY(check(v, Key{3}, 1));
		VERIFY(check(v, Key{4}, 0));
		VERIFY(check(v, Key{5}, 1));
		VERIFY(check(v, Key{6}, 0));
		VERIFY(check(v, Key{7}, 1));
	}

	return true;
}

template <typename Key, typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test_noexcept()
{
#if !defined(HAMON_USE_STD_UNORDERED_MAP)
	{
		using Map = hamon::unordered_map<Key, T, NoThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert( noexcept(hamon::declval<Map&>().equal_range(hamon::declval<Key const&>())), "");
		static_assert( noexcept(hamon::declval<Map const&>().equal_range(hamon::declval<Key const&>())), "");
	}
	{
		using Map = hamon::unordered_map<Key, T, NoThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Map&>().equal_range(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Map const&>().equal_range(hamon::declval<Key const&>())), "");
	}
	{
		using Map = hamon::unordered_map<Key, T, ThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Map&>().equal_range(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Map const&>().equal_range(hamon::declval<Key const&>())), "");
	}
	{
		using Map = hamon::unordered_map<Key, T, ThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Map&>().equal_range(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Map const&>().equal_range(hamon::declval<Key const&>())), "");
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, EqualRangeTest)
{
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<int, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<int, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<int, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<char, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<char, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<char, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<float, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<float, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test_noexcept<float, float>()));
}

#undef UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MAP_TEST_CONSTEXPR

}	// namespace equal_range_test

}	// namespace hamon_unordered_map_test
