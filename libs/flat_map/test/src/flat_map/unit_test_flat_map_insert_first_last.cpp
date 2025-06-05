/**
 *	@file	unit_test_flat_map_insert_first_last.cpp
 *
 *	@brief	insert のテスト
 *
 *	template<class InputIterator>
 *	constexpr void insert(InputIterator first, InputIterator last);
 *
 *	template<class InputIterator>
 *	constexpr void insert(sorted_unique_t, InputIterator first, InputIterator last);
 */

#include <hamon/flat_map/flat_map.hpp>
#include <hamon/algorithm/ranges/sort.hpp>
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
#include "iterator_test.hpp"
#include "flat_map_test_helper.hpp"

namespace hamon_flat_map_test
{

namespace insert_first_last_test
{

#if !defined(HAMON_USE_STD_FLAT_MAP)
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer, typename Compare, template <typename> class IteratorWrapper>
FLAT_MAP_TEST_CONSTEXPR bool test_impl()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map = hamon::flat_map<Key, T, Compare, KeyContainer, MappedContainer>;
	using ValueType = typename Map::value_type;
	using InputIterator = IteratorWrapper<ValueType>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<InputIterator>(), hamon::declval<InputIterator>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::sorted_unique, hamon::declval<InputIterator>(), hamon::declval<InputIterator>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<InputIterator>(), hamon::declval<InputIterator>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::sorted_unique, hamon::declval<InputIterator>(), hamon::declval<InputIterator>())), "");

	{
		Map v;
		{
			ValueType a[] =
			{
				{Key{1}, T{10}},
				{Key{3}, T{20}},
				{Key{2}, T{30}},
			};
			v.insert(InputIterator{a}, InputIterator{a + 3});
		}
		VERIFY(v.size() == 3);
		VERIFY(v[Key{1}] == T{10});
		VERIFY(v[Key{2}] == T{30});
		VERIFY(v[Key{3}] == T{20});
		{
			ValueType a[] =
			{
				{Key{5}, T{40}},
				{Key{1}, T{50}},
				{Key{2}, T{60}},
				{Key{4}, T{70}},
			};
			v.insert(InputIterator{a}, InputIterator{a + 4});
		}
		VERIFY(v.size() == 5);
		VERIFY(v[Key{1}] == T{10});
		VERIFY(v[Key{2}] == T{30});
		VERIFY(v[Key{3}] == T{20});
		VERIFY(v[Key{4}] == T{70});
		VERIFY(v[Key{5}] == T{40});
	}
	{
		Map v;
		{
			ValueType a[] =
			{
				{Key{1}, T{10}},
				{Key{3}, T{20}},
				{Key{2}, T{30}},
			};
			hamon::ranges::sort(a, v.value_comp());
			v.insert(hamon::sorted_unique, InputIterator{a}, InputIterator{a + 3});
		}
		VERIFY(v.size() == 3);
		VERIFY(v[Key{1}] == T{10});
		VERIFY(v[Key{2}] == T{30});
		VERIFY(v[Key{3}] == T{20});
		{
			ValueType a[] =
			{
				{Key{5}, T{40}},
				{Key{1}, T{50}},
				{Key{2}, T{60}},
				{Key{4}, T{70}},
			};
			hamon::ranges::sort(a, v.value_comp());
			v.insert(hamon::sorted_unique, InputIterator{a}, InputIterator{a + 4});
		}
		VERIFY(v.size() == 5);
		VERIFY(v[Key{1}] == T{10});
		VERIFY(v[Key{2}] == T{30});
		VERIFY(v[Key{3}] == T{20});
		VERIFY(v[Key{4}] == T{70});
		VERIFY(v[Key{5}] == T{40});
	}

	return true;
}

template <typename KeyContainer, typename MappedContainer, typename Compare>
FLAT_MAP_TEST_CONSTEXPR bool test()
{
	VERIFY(test_impl<KeyContainer, MappedContainer, Compare, cpp17_input_iterator_wrapper>());
//	VERIFY(test_impl<KeyContainer, MappedContainer, Compare, input_iterator_wrapper>());
	VERIFY(test_impl<KeyContainer, MappedContainer, Compare, forward_iterator_wrapper>());
	VERIFY(test_impl<KeyContainer, MappedContainer, Compare, bidirectional_iterator_wrapper>());
	VERIFY(test_impl<KeyContainer, MappedContainer, Compare, random_access_iterator_wrapper>());
	VERIFY(test_impl<KeyContainer, MappedContainer, Compare, contiguous_iterator_wrapper>());

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMapTest, InsertFirstLastTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<>>()));
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace insert_first_last_test

}	// namespace hamon_flat_map_test
