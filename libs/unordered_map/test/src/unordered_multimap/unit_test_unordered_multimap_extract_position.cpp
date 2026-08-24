/**
 *	@file	unit_test_unordered_multimap_extract_position.cpp
 *
 *	@brief	extract のテスト
 *
 *	constexpr node_type extract(const_iterator position);
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

namespace extract_position_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Map = hamon::unordered_multimap<Key, T>;
	using NodeType = typename Map::node_type;
	using ConstIterator = typename Map::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().extract(hamon::declval<ConstIterator>())), NodeType>::value, "");
	//static_assert( noexcept(hamon::declval<Map&>().extract(hamon::declval<ConstIterator>())), "");

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
	VERIFY(v.size() == 7);

	{
		auto i = v.begin();
		auto& x = *i;
		auto r = v.extract(i);
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.key() == x.first);
		VERIFY(r.mapped() == x.second);
		VERIFY(v.size() == 6);
	}
	{
		auto i = hamon::next(v.begin(), 1);
		auto& x = *i;
		auto r = v.extract(i);
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.key() == x.first);
		VERIFY(r.mapped() == x.second);
		VERIFY(v.size() == 5);
	}
	{
		auto i = hamon::next(v.begin(), 4);
		auto& x = *i;
		auto r = v.extract(i);
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.key() == x.first);
		VERIFY(r.mapped() == x.second);
		VERIFY(v.size() == 4);
	}

	return true;
}

template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test_noexcept()
{
	{
		using Map = hamon::unordered_multimap<Key, T, NoThrowHash<Key>, NoThrowEqualTo<Key>>;
		using ConstIterator = typename Map::const_iterator;
		static_assert( noexcept(hamon::declval<Map&>().extract(hamon::declval<ConstIterator>())), "");
	}
	{
		using Map = hamon::unordered_multimap<Key, T, NoThrowHash<Key>, ThrowEqualTo<Key>>;
		using ConstIterator = typename Map::const_iterator;
		static_assert( noexcept(hamon::declval<Map&>().extract(hamon::declval<ConstIterator>())), "");
	}
	{
		using Map = hamon::unordered_multimap<Key, T, ThrowHash<Key>, NoThrowEqualTo<Key>>;
		using ConstIterator = typename Map::const_iterator;
		static_assert( noexcept(hamon::declval<Map&>().extract(hamon::declval<ConstIterator>())), "");
	}
	{
		using Map = hamon::unordered_multimap<Key, T, ThrowHash<Key>, ThrowEqualTo<Key>>;
		using ConstIterator = typename Map::const_iterator;
		static_assert( noexcept(hamon::declval<Map&>().extract(hamon::declval<ConstIterator>())), "");
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, ExtractPositionTest)
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

}	// namespace extract_position_test

}	// namespace hamon_unordered_multimap_test
