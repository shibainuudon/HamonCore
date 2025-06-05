/**
 *	@file	unit_test_flat_multimap_ctor_range.cpp
 *
 *	@brief	Range を引数に取るコンストラクタのテスト
 *
 *	template<container-compatible-range<value_type> R>
 *	constexpr flat_multimap(from_range_t, R&& rg);
 *
 *	template<container-compatible-range<value_type> R>
 *	constexpr flat_multimap(from_range_t, R&& rg, const key_compare& comp);
 */

#include <hamon/flat_map/flat_multimap.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/ranges.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
{

namespace ctor_range_test
{

#if !defined(HAMON_USE_STD_FLAT_MAP)
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer, typename Compare, template <typename> class RangeWrapper>
FLAT_MAP_TEST_CONSTEXPR bool test_impl()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map = hamon::flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>;
	using ValueType = typename Map::value_type;
	using Range = RangeWrapper<ValueType>;

	static_assert( hamon::is_constructible<Map, hamon::from_range_t, Range const&>::value, "");
	static_assert( hamon::is_constructible<Map, hamon::from_range_t, Range&&>::value, "");
	static_assert( hamon::is_constructible<Map, hamon::from_range_t, Range const&, Compare const&>::value, "");
	static_assert( hamon::is_constructible<Map, hamon::from_range_t, Range&&, Compare const&>::value, "");

	static_assert(!hamon::is_nothrow_constructible<Map, hamon::from_range_t, Range const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, hamon::from_range_t, Range&&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, hamon::from_range_t, Range const&, Compare const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, hamon::from_range_t, Range&&, Compare const&>::value, "");

	static_assert( hamon::is_implicitly_constructible<Map, hamon::from_range_t, Range const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, hamon::from_range_t, Range&&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, hamon::from_range_t, Range const&, Compare const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, hamon::from_range_t, Range&&, Compare const&>::value, "");

	static_assert(!hamon::is_trivially_constructible<Map, hamon::from_range_t, Range const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, hamon::from_range_t, Range&&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, hamon::from_range_t, Range const&, Compare const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, hamon::from_range_t, Range&&, Compare const&>::value, "");

	{
		ValueType a[] =
		{
			{Key{1}, T{10}},
			{Key{3}, T{20}},
			{Key{2}, T{30}},
			{Key{1}, T{10}},
		};
		Range r(a);
		Map v{hamon::from_range, r};
		VERIFY(check_invariant(v));
		VERIFY(!v.empty());
		VERIFY(v.size() == 4);
		VERIFY(v.count(Key{1}) == 2);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 1);
	}
	{
		ValueType a[] =
		{
			{Key{2}, T{10}},
			{Key{0}, T{20}},
			{Key{1}, T{30}},
			{Key{2}, T{40}},
			{Key{2}, T{50}},
		};
		Map v{hamon::from_range, Range{a}};
		VERIFY(check_invariant(v));
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.count(Key{0}) == 1);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 3);
	}
	{
		ValueType a[] =
		{
			{Key{1}, T{10}},
			{Key{3}, T{20}},
			{Key{2}, T{30}},
		};
		Range r(a);
		TestLess<Key> const comp{42};
		hamon::flat_multimap<Key, T, TestLess<Key>, KeyContainer, MappedContainer> v{hamon::from_range, r, comp};
		VERIFY(check_invariant(v));
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(it->first == Key{1});
		VERIFY(it->second == T{10});
		++it;
		VERIFY(it->first == Key{2});
		VERIFY(it->second == T{30});
		++it;
		VERIFY(it->first == Key{3});
		VERIFY(it->second == T{20});
		++it;
		VERIFY(it == v.end());
	}

	return true;
}

template <typename KeyContainer, typename MappedContainer, typename Compare>
FLAT_MAP_TEST_CONSTEXPR bool test()
{
	VERIFY(test_impl<KeyContainer, MappedContainer, Compare, test_input_range>());
	VERIFY(test_impl<KeyContainer, MappedContainer, Compare, test_forward_range>());
	VERIFY(test_impl<KeyContainer, MappedContainer, Compare, test_bidirectional_range>());
	VERIFY(test_impl<KeyContainer, MappedContainer, Compare, test_random_access_range>());
	VERIFY(test_impl<KeyContainer, MappedContainer, Compare, test_contiguous_range>());
	VERIFY(test_impl<KeyContainer, MappedContainer, Compare, test_input_sized_range>());
	VERIFY(test_impl<KeyContainer, MappedContainer, Compare, test_forward_sized_range>());
	VERIFY(test_impl<KeyContainer, MappedContainer, Compare, test_bidirectional_sized_range>());
	VERIFY(test_impl<KeyContainer, MappedContainer, Compare, test_random_access_sized_range>());
	VERIFY(test_impl<KeyContainer, MappedContainer, Compare, test_contiguous_sized_range>());

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultimapTest, CtorRangeTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<>>()));
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace ctor_range_test

}	// namespace hamon_flat_multimap_test
