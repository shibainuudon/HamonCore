/**
 *	@file	unit_test_flat_map_ctor_cont.cpp
 *
 *	@brief	key_cont と mapped_cont を引数に取るコンストラクタのテスト
 *
 *	constexpr flat_map(key_container_type key_cont, mapped_container_type mapped_cont,
 *		const key_compare& comp = key_compare());
 *
 *  constexpr flat_map(sorted_unique_t, key_container_type key_cont,
 *		mapped_container_type mapped_cont,
 *		const key_compare& comp = key_compare());
 */

#include <hamon/flat_map/flat_map.hpp>
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
#include "flat_map_test_helper.hpp"

namespace hamon_flat_map_test
{

namespace ctor_cont_test
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
	using Map = hamon::flat_map<Key, T, Compare, KeyContainer, MappedContainer>;

	static_assert( hamon::is_constructible<Map, KeyContainer, MappedContainer>::value, "");
	static_assert( hamon::is_constructible<Map, KeyContainer, MappedContainer, Compare const&>::value, "");
	static_assert( hamon::is_constructible<Map, hamon::sorted_unique_t, KeyContainer, MappedContainer>::value, "");
	static_assert( hamon::is_constructible<Map, hamon::sorted_unique_t, KeyContainer, MappedContainer, Compare const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, KeyContainer, MappedContainer>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, KeyContainer, MappedContainer, Compare const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, hamon::sorted_unique_t, KeyContainer, MappedContainer>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, hamon::sorted_unique_t, KeyContainer, MappedContainer, Compare const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, KeyContainer, MappedContainer>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, KeyContainer, MappedContainer, Compare const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, hamon::sorted_unique_t, KeyContainer, MappedContainer>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, hamon::sorted_unique_t, KeyContainer, MappedContainer, Compare const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, KeyContainer, MappedContainer>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, KeyContainer, MappedContainer, Compare const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, hamon::sorted_unique_t, KeyContainer, MappedContainer>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, hamon::sorted_unique_t, KeyContainer, MappedContainer, Compare const&>::value, "");

	{
		KeyContainer const key_cont {Key{3}, Key{1}, Key{4}};
		MappedContainer const mapped_cont {T{10}, T{20}, T{30}};
		Map v{key_cont, mapped_cont};
		VERIFY(check_invariant(v));
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v[Key{1}] == T{20});
		VERIFY(v[Key{3}] == T{10});
		VERIFY(v[Key{4}] == T{30});
	}
	{
		KeyContainer key_cont {Key{3}, Key{1}, Key{4}, Key{2}};
		MappedContainer mapped_cont {T{10}, T{20}, T{30}, T{40}};
		TestLess<Key> const comp{42};
		hamon::flat_map<Key, T, TestLess<Key>, KeyContainer, MappedContainer> v{hamon::move(key_cont), hamon::move(mapped_cont), comp};
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 4);
		VERIFY(v.key_comp() == comp);
		auto it = v.begin();
		VERIFY(it->first == Key{1});
		VERIFY(it->second == T{20});
		++it;
		VERIFY(it->first == Key{2});
		VERIFY(it->second == T{40});
		++it;
		VERIFY(it->first == Key{3});
		VERIFY(it->second == T{10});
		++it;
		VERIFY(it->first == Key{4});
		VERIFY(it->second == T{30});
		++it;
		VERIFY(it == v.end());
	}
	{
		KeyContainer key_cont {Key{3}, Key{1}, Key{4}};
		MappedContainer mapped_cont {T{10}, T{20}, T{30}};
		hamon::ranges::sort(key_cont, Compare{});
		Map v{hamon::sorted_unique, hamon::move(key_cont), hamon::move(mapped_cont)};
		VERIFY(check_invariant(v));
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY( v.contains(Key{1}));
		VERIFY(!v.contains(Key{2}));
		VERIFY( v.contains(Key{3}));
		VERIFY( v.contains(Key{4}));
	}
	{
		KeyContainer key_cont {Key{3}, Key{1}, Key{4}, Key{2}};
		MappedContainer mapped_cont {T{10}, T{20}, T{30}, T{40}};
		TestLess<Key> const comp{42};
		hamon::ranges::sort(key_cont, comp);
		hamon::flat_map<Key, T, TestLess<Key>, KeyContainer, MappedContainer> v{hamon::sorted_unique, key_cont, mapped_cont, comp};
		VERIFY(check_invariant(v));
		VERIFY(v.size() == 4);
		VERIFY(v.key_comp() == comp);
		auto it = v.begin();
		VERIFY(it->first == Key{1});
		VERIFY(it->second == T{10});
		++it;
		VERIFY(it->first == Key{2});
		VERIFY(it->second == T{20});
		++it;
		VERIFY(it->first == Key{3});
		VERIFY(it->second == T{30});
		++it;
		VERIFY(it->first == Key{4});
		VERIFY(it->second == T{40});
		++it;
		VERIFY(it == v.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMapTest, CtorContTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<>>()));
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace ctor_cont_test

}	// namespace hamon_flat_map_test
