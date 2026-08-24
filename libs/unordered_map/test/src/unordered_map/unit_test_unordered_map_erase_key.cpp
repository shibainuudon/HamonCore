/**
 *	@file	unit_test_unordered_map_erase_key.cpp
 *
 *	@brief	erase のテスト
 *
 *	constexpr size_type erase(const key_type& k);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_map_test_helper.hpp"

namespace hamon_unordered_map_test
{

namespace erase_key_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Map = hamon::unordered_map<Key, T>;
	using SizeType = typename Map::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().erase(hamon::declval<Key const&>())), SizeType>::value, "");
	//static_assert( noexcept(hamon::declval<Map&>().erase(hamon::declval<Key const&>())), "");

	Map v
	{
		{Key{5}, T{60}},
		{Key{7}, T{70}},
		{Key{3}, T{40}},
		{Key{2}, T{10}},
		{Key{0}, T{20}},
	};
	VERIFY(v.size() == 5);

	VERIFY(v.erase(Key{0}) == 1);
	VERIFY(v.size() == 4);

	VERIFY(v.erase(Key{0}) == 0);
	VERIFY(v.size() == 4);

	VERIFY(v.erase(Key{1}) == 0);
	VERIFY(v.size() == 4);

	VERIFY(v.erase(Key{2}) == 1);
	VERIFY(v.size() == 3);

	VERIFY(v.erase(Key{3}) == 1);
	VERIFY(v.size() == 2);

	VERIFY(v.erase(Key{4}) == 0);
	VERIFY(v.size() == 2);

	VERIFY(v.erase(Key{5}) == 1);
	VERIFY(v.size() == 1);

	VERIFY(v.erase(Key{6}) == 0);
	VERIFY(v.size() == 1);

	VERIFY(v.erase(Key{7}) == 1);
	VERIFY(v.size() == 0);

	return true;
}

template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test_noexcept()
{
	{
		using Map = hamon::unordered_map<Key, T, NoThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert( noexcept(hamon::declval<Map&>().erase(hamon::declval<Key const&>())), "");
	}
	{
		using Map = hamon::unordered_map<Key, T, NoThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<Key const&>())), "");
	}
	{
		using Map = hamon::unordered_map<Key, T, ThrowHash<Key>, NoThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<Key const&>())), "");
	}
	{
		using Map = hamon::unordered_map<Key, T, ThrowHash<Key>, ThrowEqualTo<Key>>;
		static_assert(!noexcept(hamon::declval<Map&>().erase(hamon::declval<Key const&>())), "");
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, EraseKeyTest)
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

}	// namespace erase_key_test

}	// namespace hamon_unordered_map_test
