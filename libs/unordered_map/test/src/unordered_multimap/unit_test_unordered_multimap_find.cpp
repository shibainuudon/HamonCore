/**
 *	@file	unit_test_unordered_multimap_find.cpp
 *
 *	@brief	find のテスト
 *
 *	constexpr iterator         find(const key_type& k);
 *	constexpr const_iterator   find(const key_type& k) const;
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multimap_test_helper.hpp"

namespace hamon_unordered_multimap_test
{

namespace find_test
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

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().find(hamon::declval<Key const&>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().find(hamon::declval<Key const&>())), ConstIterator>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
	//static_assert( noexcept(hamon::declval<Map&>().find(hamon::declval<Key const&>())), "");
	//static_assert( noexcept(hamon::declval<Map const&>().find(hamon::declval<Key const&>())), "");
#endif

	{
		Map v
		{
			{Key{0}, T{10}},
			{Key{2}, T{20}},
			{Key{4}, T{30}},
			{Key{0}, T{40}},
			{Key{4}, T{50}},
			{Key{0}, T{60}},
			{Key{1}, T{70}},
		};

		VERIFY(v.find(Key{0}) != v.end());
		VERIFY(v.find(Key{1}) != v.end());
		VERIFY(v.find(Key{2}) != v.end());
		VERIFY(v.find(Key{3}) == v.end());
		VERIFY(v.find(Key{4}) != v.end());
		VERIFY(v.find(Key{5}) == v.end());

		VERIFY(v.find(Key{0})->first == Key{0});
		VERIFY(v.find(Key{1})->first == Key{1});
		VERIFY(v.find(Key{1})->second == T{70});
		VERIFY(v.find(Key{2})->first == Key{2});
		VERIFY(v.find(Key{2})->second == T{20});
		VERIFY(v.find(Key{4})->first == Key{4});
	}
	{
		Map const v
		{
			{Key{0}, T{10}},
			{Key{2}, T{20}},
			{Key{4}, T{30}},
			{Key{0}, T{40}},
			{Key{4}, T{50}},
			{Key{0}, T{60}},
			{Key{1}, T{70}},
		};

		VERIFY(v.find(Key{0}) != v.end());
		VERIFY(v.find(Key{1}) != v.end());
		VERIFY(v.find(Key{2}) != v.end());
		VERIFY(v.find(Key{3}) == v.end());
		VERIFY(v.find(Key{4}) != v.end());
		VERIFY(v.find(Key{5}) == v.end());

		VERIFY(v.find(Key{0})->first == Key{0});
		VERIFY(v.find(Key{1})->first == Key{1});
		VERIFY(v.find(Key{1})->second == T{70});
		VERIFY(v.find(Key{2})->first == Key{2});
		VERIFY(v.find(Key{2})->second == T{20});
		VERIFY(v.find(Key{4})->first == Key{4});
	}

	return true;
}

template <typename Key, typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test_noexcept()
{
#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
	{
		using Map = hamon::unordered_multimap<Key, T, NoThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert( noexcept(hamon::declval<Map&>().find(hamon::declval<Key const&>())), "");
		static_assert( noexcept(hamon::declval<Map const&>().find(hamon::declval<Key const&>())), "");
	}
	{
		using Map = hamon::unordered_multimap<Key, T, NoThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Map&>().find(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Map const&>().find(hamon::declval<Key const&>())), "");
	}
	{
		using Map = hamon::unordered_multimap<Key, T, ThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Map&>().find(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Map const&>().find(hamon::declval<Key const&>())), "");
	}
	{
		using Map = hamon::unordered_multimap<Key, T, ThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Map&>().find(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Map const&>().find(hamon::declval<Key const&>())), "");
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, FindTest)
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

}	// namespace find_test

}	// namespace hamon_unordered_multimap_test
