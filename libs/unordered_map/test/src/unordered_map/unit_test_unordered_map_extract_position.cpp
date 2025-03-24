/**
 *	@file	unit_test_unordered_map_extract_position.cpp
 *
 *	@brief	extract のテスト
 *
 *	constexpr node_type extract(const_iterator position);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/iterator/next.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_map_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MAP) || \
	(defined(__cpp_lib_node_extract) && (__cpp_lib_node_extract >= 201606L))

namespace hamon_unordered_map_test
{

namespace extract_position_test
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
	using NodeType = typename Map::node_type;
	using ConstIterator = typename Map::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().extract(hamon::declval<ConstIterator>())), NodeType>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MAP)
	static_assert( noexcept(hamon::declval<Map&>().extract(hamon::declval<ConstIterator>())), "");
#endif

	Map v
	{
		{Key{3}, T{10}},
		{Key{1}, T{20}},
		{Key{4}, T{30}},
		{Key{1}, T{40}},
		{Key{5}, T{50}},
		{Key{4}, T{60}},
		{Key{4}, T{70}},
	};
	VERIFY(v.size() == 4);

	{
		auto i = v.begin();
		auto& x = *i;
		auto r = v.extract(i);
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.key() == x.first);
		VERIFY(r.mapped() == x.second);
		VERIFY(v.size() == 3);
	}
	{
		auto i = hamon::next(v.begin(), 2);
		auto& x = *i;
		auto r = v.extract(i);
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.key() == x.first);
		VERIFY(r.mapped() == x.second);
		VERIFY(v.size() == 2);
	}
	{
		auto i = hamon::next(v.begin(), 1);
		auto& x = *i;
		auto r = v.extract(i);
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.key() == x.first);
		VERIFY(r.mapped() == x.second);
		VERIFY(v.size() == 1);
	}
	{
		auto i = v.begin();
		auto& x = *i;
		auto r = v.extract(i);
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.key() == x.first);
		VERIFY(r.mapped() == x.second);
		VERIFY(v.size() == 0);
	}

	return true;
}

template <typename Key, typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test_noexcept()
{
#if !defined(HAMON_USE_STD_UNORDERED_MAP)
	{
		using Map = hamon::unordered_map<Key, T, NoThrowHash<Key>, NoThrowEqualTo<Key>>;
		using ConstIterator = typename Map::const_iterator;
		static_assert( noexcept(hamon::declval<Map&>().extract(hamon::declval<ConstIterator>())), "");
	}
	{
		using Map = hamon::unordered_map<Key, T, NoThrowHash<Key>, ThrowEqualTo<Key>>;
		using ConstIterator = typename Map::const_iterator;
		static_assert( noexcept(hamon::declval<Map&>().extract(hamon::declval<ConstIterator>())), "");
	}
	{
		using Map = hamon::unordered_map<Key, T, ThrowHash<Key>, NoThrowEqualTo<Key>>;
		using ConstIterator = typename Map::const_iterator;
		static_assert( noexcept(hamon::declval<Map&>().extract(hamon::declval<ConstIterator>())), "");
	}
	{
		using Map = hamon::unordered_map<Key, T, ThrowHash<Key>, ThrowEqualTo<Key>>;
		using ConstIterator = typename Map::const_iterator;
		static_assert( noexcept(hamon::declval<Map&>().extract(hamon::declval<ConstIterator>())), "");
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, ExtractPositionTest)
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

}	// namespace extract_position_test

}	// namespace hamon_unordered_map_test

#endif
