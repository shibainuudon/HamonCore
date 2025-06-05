/**
 *	@file	unit_test_flat_multimap_insert_init_list.cpp
 *
 *	@brief	insert のテスト
 *
 *	constexpr void insert(initializer_list<value_type> il);
 *	constexpr void insert(sorted_equivalent_t, initializer_list<value_type> il);
 */

#include <hamon/flat_map/flat_multimap.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
{

namespace insert_init_list_test
{

#if !defined(HAMON_USE_STD_FLAT_MAP)
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer, typename Compare>
FLAT_MAP_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map = hamon::flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>;
	using ValueType = typename Map::value_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<std::initializer_list<ValueType>>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::sorted_equivalent, hamon::declval<std::initializer_list<ValueType>>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<std::initializer_list<ValueType>>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::sorted_equivalent, hamon::declval<std::initializer_list<ValueType>>())), "");

	{
		Map v;

		v.insert({
			{Key{1}, T{10}},
			{Key{3}, T{20}},
			{Key{2}, T{30}},
		});
		VERIFY(v.size() == 3);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 0);
		VERIFY(v.count(Key{5}) == 0);

		v.insert({
			{Key{5}, T{40}},
			{Key{1}, T{50}},
			{Key{2}, T{60}},
			{Key{4}, T{70}},
		});
		VERIFY(v.size() == 7);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 2);
		VERIFY(v.count(Key{2}) == 2);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 1);
		VERIFY(v.count(Key{5}) == 1);
	}
	{
		hamon::flat_multimap<Key, T, hamon::less<Key>, KeyContainer, MappedContainer> v;

		v.insert(hamon::sorted_equivalent, {
			{Key{1}, T{10}},
			{Key{2}, T{20}},
			{Key{3}, T{30}},
		});
		VERIFY(v.size() == 3);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 0);
		VERIFY(v.count(Key{5}) == 0);

		v.insert(hamon::sorted_equivalent, {
			{Key{1}, T{40}},
			{Key{4}, T{50}},
			{Key{5}, T{60}},
		});
		VERIFY(v.size() == 6);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 2);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 1);
		VERIFY(v.count(Key{5}) == 1);
	}
	{
		hamon::flat_multimap<Key, T, hamon::greater<Key>, KeyContainer, MappedContainer> v;

		v.insert(hamon::sorted_equivalent, {
			{Key{4}, T{10}},
			{Key{2}, T{20}},
			{Key{1}, T{30}},
		});
		VERIFY(v.size() == 3);
		VERIFY(v.count(Key{0}) == 0);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 0);
		VERIFY(v.count(Key{4}) == 1);
		VERIFY(v.count(Key{5}) == 0);

		v.insert(hamon::sorted_equivalent, {
			{Key{5}, T{40}},
			{Key{4}, T{50}},
			{Key{3}, T{60}},
			{Key{2}, T{70}},
			{Key{1}, T{80}},
			{Key{0}, T{90}},
		});
		VERIFY(v.size() == 9);
		VERIFY(v.count(Key{0}) == 1);
		VERIFY(v.count(Key{1}) == 2);
		VERIFY(v.count(Key{2}) == 2);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 2);
		VERIFY(v.count(Key{5}) == 1);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultimapTest, InsertInitListTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<int>>()));
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace insert_init_list_test

}	// namespace hamon_flat_multimap_test
