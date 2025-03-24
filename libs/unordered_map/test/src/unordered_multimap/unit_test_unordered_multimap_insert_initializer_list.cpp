/**
 *	@file	unit_test_unordered_multimap_insert_initializer_list.cpp
 *
 *	@brief	insert のテスト
 *
 *	constexpr void insert(initializer_list<value_type>);
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include <initializer_list>
#include "constexpr_test.hpp"
#include "unordered_multimap_test_helper.hpp"

namespace hamon_unordered_multimap_test
{

namespace insert_initializer_list_test
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
	using ValueType = typename Map::value_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::initializer_list<ValueType>>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::initializer_list<ValueType>>())), "");

	Map v;
	v.max_load_factor(0.4f);

	{
		v.insert({
			{Key{3}, T{10}},
			{Key{2}, T{20}},
			{Key{3}, T{30}},
			{Key{1}, T{40}},
			{Key{2}, T{50}},
			{Key{3}, T{60}},
		});
		VERIFY(v.size() == 6);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 2);
		VERIFY(v.count(Key{3}) == 3);
		VERIFY(v.count(Key{4}) == 0);
	}
	{
		v.insert({
			{Key{2}, T{70}},
			{Key{4}, T{80}},
			{Key{0}, T{90}},
			{Key{1}, T{40}},
		});
		VERIFY(v.size() == 10);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.count(Key{0}) == 1);
		VERIFY(v.count(Key{1}) == 2);
		VERIFY(v.count(Key{2}) == 3);
		VERIFY(v.count(Key{3}) == 3);
		VERIFY(v.count(Key{4}) == 1);
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
		VERIFY(v.size() == 30);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, InsertInitializerListTest)
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

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		using Map = hamon::unordered_multimap<int, ThrowOnCopyIfNegative>;

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
		EXPECT_EQ(0u, v.count(0));
		EXPECT_EQ(1u, v.count(1));
		EXPECT_EQ(0u, v.count(2));
		EXPECT_EQ(1u, v.count(3));
		EXPECT_EQ(0u, v.count(4));

		// { 3, ThrowOnCopyIfNegative{-70}} をコピーするときに例外を投げる
		EXPECT_THROW(v.insert({
			{ 1, ThrowOnCopyIfNegative{ 50} },
			{ 2, ThrowOnCopyIfNegative{ 60} },
			{ 3, ThrowOnCopyIfNegative{-70} },
			{ 0, ThrowOnCopyIfNegative{ 80} },
		}), ThrowOnCopyIfNegative::Exception);
		EXPECT_EQ(4u, v.size());
		EXPECT_EQ(0u, v.count(0));
		EXPECT_EQ(2u, v.count(1));
		EXPECT_EQ(1u, v.count(2));
		EXPECT_EQ(1u, v.count(3));
		EXPECT_EQ(0u, v.count(4));
	}
#endif
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace insert_initializer_list_test

}	// namespace hamon_unordered_multimap_test
