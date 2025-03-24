/**
 *	@file	unit_test_unordered_map_insert_initializer_list.cpp
 *
 *	@brief	insert のテスト
 *
 *	constexpr void insert(initializer_list<value_type>);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include <initializer_list>
#include "constexpr_test.hpp"
#include "unordered_map_test_helper.hpp"

namespace hamon_unordered_map_test
{

namespace insert_initializer_list_test
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
	using ValueType = typename Map::value_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::initializer_list<ValueType>>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::initializer_list<ValueType>>())), "");

	Map v;

	{
		v.insert({
			{Key{3}, T{10}},
			{Key{2}, T{20}},
			{Key{3}, T{30}},
			{Key{1}, T{40}},
			{Key{2}, T{50}},
			{Key{3}, T{60}},
		});
		VERIFY(v.size() == 3);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[1] == 40);
		VERIFY(v[2] == 20);
		VERIFY(v[3] == 10);
	}
	{
		v.insert({
			{Key{2}, T{70}},
			{Key{4}, T{80}},
			{Key{0}, T{90}},
			{Key{1}, T{40}},
		});
		VERIFY(v.size() == 5);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[0] == 90);
		VERIFY(v[1] == 40);
		VERIFY(v[2] == 20);
		VERIFY(v[3] == 10);
		VERIFY(v[4] == 80);
	}
	{
		v.insert({
			{Key{10}, T{42}},
			{Key{11}, T{42}},
			{Key{12}, T{42}},
			{Key{13}, T{42}},
			{Key{14}, T{42}},
			{Key{15}, T{42}},
			{Key{16}, T{42}},
			{Key{17}, T{42}},
			{Key{18}, T{42}},
			{Key{19}, T{42}},
			{Key{20}, T{43}},
			{Key{21}, T{43}},
			{Key{22}, T{43}},
			{Key{23}, T{43}},
			{Key{24}, T{43}},
			{Key{25}, T{43}},
			{Key{26}, T{43}},
			{Key{27}, T{43}},
			{Key{28}, T{43}},
			{Key{29}, T{43}},
		});
		VERIFY(v.size() == 25);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[0] == 90);
		VERIFY(v[1] == 40);
		VERIFY(v[2] == 20);
		VERIFY(v[3] == 10);
		VERIFY(v[4] == 80);
		VERIFY(v[10] == 42);
		VERIFY(v[11] == 42);
		VERIFY(v[12] == 42);
		VERIFY(v[13] == 42);
		VERIFY(v[14] == 42);
		VERIFY(v[15] == 42);
		VERIFY(v[16] == 42);
		VERIFY(v[17] == 42);
		VERIFY(v[18] == 42);
		VERIFY(v[19] == 42);
		VERIFY(v[20] == 43);
		VERIFY(v[21] == 43);
		VERIFY(v[22] == 43);
		VERIFY(v[23] == 43);
		VERIFY(v[24] == 43);
		VERIFY(v[25] == 43);
		VERIFY(v[26] == 43);
		VERIFY(v[27] == 43);
		VERIFY(v[28] == 43);
		VERIFY(v[29] == 43);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, InsertInitializerListTest)
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

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		using Map = hamon::unordered_map<int, ThrowOnCopyIfNegative>;

		Map v;
		EXPECT_EQ(0u, v.size());

		// { 4, ThrowOnCopyIfNegative{-30}} をコピーするときに例外を投げる
		EXPECT_THROW(v.insert({
			{ 3, ThrowOnCopyIfNegative{ 10} },
			{ 1, ThrowOnCopyIfNegative{ 20} },
			{ 4, ThrowOnCopyIfNegative{-30} },
			{ 1, ThrowOnCopyIfNegative{ 40} },
		}), ThrowOnCopyIfNegative::Exception);
		EXPECT_EQ(2u, v.size());
		EXPECT_EQ(v.at(1).value, 20);
		EXPECT_EQ(v.at(3).value, 10);

		// { 3, ThrowOnCopyIfNegative{-70}} は挿入されないので例外を投げない
		EXPECT_NO_THROW(v.insert({
			{ 1, ThrowOnCopyIfNegative{ 50} },
			{ 2, ThrowOnCopyIfNegative{ 60} },
			{ 3, ThrowOnCopyIfNegative{-70} },
			{ 0, ThrowOnCopyIfNegative{ 80} },
		}));
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(v.at(0).value, 80);
		EXPECT_EQ(v.at(1).value, 20);
		EXPECT_EQ(v.at(2).value, 60);
		EXPECT_EQ(v.at(3).value, 10);
	}
#endif
}

#undef UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MAP_TEST_CONSTEXPR

}	// namespace insert_initializer_list_test

}	// namespace hamon_unordered_map_test
