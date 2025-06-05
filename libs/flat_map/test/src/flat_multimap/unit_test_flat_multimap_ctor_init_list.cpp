/**
 *	@file	unit_test_flat_multimap_ctor_init_list.cpp
 *
 *	@brief	initializer_list を引数に取るコンストラクタのテスト
 *
 *	constexpr flat_multimap(initializer_list<value_type> il,
 *		const key_compare& comp = key_compare());
 *
 *	constexpr flat_multimap(sorted_equivalent_t, initializer_list<value_type> il,
 *		const key_compare& comp = key_compare());
 */

#include <hamon/flat_map/flat_multimap.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
{

namespace ctor_init_list_test
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

	static_assert( hamon::is_constructible<Map, std::initializer_list<ValueType>>::value, "");
	static_assert( hamon::is_constructible<Map, std::initializer_list<ValueType>, Compare const&>::value, "");
	static_assert( hamon::is_constructible<Map, hamon::sorted_equivalent_t, std::initializer_list<ValueType>>::value, "");
	static_assert( hamon::is_constructible<Map, hamon::sorted_equivalent_t, std::initializer_list<ValueType>, Compare const&>::value, "");

	static_assert(!hamon::is_nothrow_constructible<Map, std::initializer_list<ValueType>>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, std::initializer_list<ValueType>, Compare const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, hamon::sorted_equivalent_t, std::initializer_list<ValueType>>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, hamon::sorted_equivalent_t, std::initializer_list<ValueType>, Compare const&>::value, "");

	static_assert( hamon::is_implicitly_constructible<Map, std::initializer_list<ValueType>>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, std::initializer_list<ValueType>, Compare const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, hamon::sorted_equivalent_t, std::initializer_list<ValueType>>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, hamon::sorted_equivalent_t, std::initializer_list<ValueType>, Compare const&>::value, "");

	static_assert(!hamon::is_trivially_constructible<Map, std::initializer_list<ValueType>>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, std::initializer_list<ValueType>, Compare const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, hamon::sorted_equivalent_t, std::initializer_list<ValueType>>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, hamon::sorted_equivalent_t, std::initializer_list<ValueType>, Compare const&>::value, "");

	{
		Map v
		{
			{Key{1}, T{10}},
			{Key{3}, T{20}},
			{Key{2}, T{30}},
			{Key{2}, T{40}},
		};
		VERIFY(check_invariant(v));
		VERIFY(!v.empty());
		VERIFY(v.size() == 4);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 2);
		VERIFY(v.count(Key{3}) == 1);
	}
	{
		TestLess<Key> const comp{42};
		hamon::flat_multimap<Key, T, TestLess<Key>, KeyContainer, MappedContainer> v
		{
			{
				{Key{1}, T{10}},
				{Key{3}, T{20}},
				{Key{2}, T{30}},
			},
			comp
		};
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 3);
		VERIFY(v.key_comp() == comp);
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
	{
		hamon::flat_multimap<Key, T, hamon::greater<>, KeyContainer, MappedContainer> v
		{
			hamon::sorted_equivalent,
			{
				{Key{4}, T{10}},
				{Key{3}, T{20}},
				{Key{1}, T{30}},
			}
		};
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(it->first == Key{4});
		VERIFY(it->second == T{10});
		++it;
		VERIFY(it->first == Key{3});
		VERIFY(it->second == T{20});
		++it;
		VERIFY(it->first == Key{1});
		VERIFY(it->second == T{30});
		++it;
		VERIFY(it == v.end());
	}
	{
		TestLess<Key> const comp{42};
		hamon::flat_multimap<Key, T, TestLess<Key>, KeyContainer, MappedContainer> v
		{
			hamon::sorted_equivalent,
			{
				{Key{1}, T{10}},
				{Key{2}, T{30}},
				{Key{3}, T{20}},
				{Key{4}, T{40}},
			},
			comp
		};
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 4);
		VERIFY(v.key_comp() == comp);
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
		VERIFY(it->first == Key{4});
		VERIFY(it->second == T{40});
		++it;
		VERIFY(it == v.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultimapTest, CtorInitListTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<>>()));
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace ctor_init_list_test

}	// namespace hamon_flat_multimap_test
