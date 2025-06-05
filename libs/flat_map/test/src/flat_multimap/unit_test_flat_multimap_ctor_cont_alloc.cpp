/**
 *	@file	unit_test_flat_multimap_ctor_cont_alloc.cpp
 *
 *	@brief	key_cont と mapped_cont とアロケータを引数に取るコンストラクタのテスト
 *
 *	template<class Alloc>
 *	constexpr flat_multimap(const key_container_type& key_cont,
 *		const mapped_container_type& mapped_cont, const Alloc& a);
 *
 *	template<class Alloc>
 *	constexpr flat_multimap(const key_container_type& key_cont,
 *		const mapped_container_type& mapped_cont,
 *		const key_compare& comp, const Alloc& a);
 *
 *	template<class Alloc>
 *	constexpr flat_multimap(sorted_equivalent_t, const key_container_type& key_cont,
 *		const mapped_container_type& mapped_cont, const Alloc& a);
 *
 *	template<class Alloc>
 *	constexpr flat_multimap(sorted_equivalent_t, const key_container_type& key_cont,
 *		const mapped_container_type& mapped_cont,
 *		const key_compare& comp, const Alloc& a);
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

namespace ctor_cont_alloc_test
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
	using Alloc = hamon::allocator<char>;

	static_assert( hamon::is_constructible<Map, KeyContainer, MappedContainer, Alloc const&>::value, "");
	static_assert( hamon::is_constructible<Map, KeyContainer, MappedContainer, Compare const&, Alloc const&>::value, "");
	static_assert( hamon::is_constructible<Map, hamon::sorted_equivalent_t, KeyContainer, MappedContainer, Alloc const&>::value, "");
	static_assert( hamon::is_constructible<Map, hamon::sorted_equivalent_t, KeyContainer, MappedContainer, Compare const&, Alloc const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, KeyContainer, MappedContainer, Alloc const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, KeyContainer, MappedContainer, Compare const&, Alloc const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, hamon::sorted_equivalent_t, KeyContainer, MappedContainer, Alloc const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, hamon::sorted_equivalent_t, KeyContainer, MappedContainer, Compare const&, Alloc const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, KeyContainer, MappedContainer, Alloc const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, KeyContainer, MappedContainer, Compare const&, Alloc const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, hamon::sorted_equivalent_t, KeyContainer, MappedContainer, Alloc const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, hamon::sorted_equivalent_t, KeyContainer, MappedContainer, Compare const&, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, KeyContainer, MappedContainer, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, KeyContainer, MappedContainer, Compare const&, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, hamon::sorted_equivalent_t, KeyContainer, MappedContainer, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, hamon::sorted_equivalent_t, KeyContainer, MappedContainer, Compare const&, Alloc const&>::value, "");

	{
		KeyContainer const key_cont {Key{3}, Key{1}, Key{4}};
		MappedContainer const mapped_cont {T{10}, T{20}, T{30}};
		Alloc const alloc;
		Map v{key_cont, mapped_cont, alloc};
		VERIFY(check_invariant(v));
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{3}) == 1);
		VERIFY(v.count(Key{4}) == 1);
	}
	{
		KeyContainer key_cont {Key{3}, Key{1}, Key{4}, Key{2}};
		MappedContainer mapped_cont {T{10}, T{20}, T{30}, T{40}};
		TestLess<Key> const comp{42};
		Alloc const alloc;
		hamon::flat_multimap<Key, T, TestLess<Key>, KeyContainer, MappedContainer> v{key_cont, mapped_cont, comp, alloc};
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
		Alloc const alloc;
		Map v{hamon::sorted_equivalent, key_cont, mapped_cont, alloc};
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
		Alloc const alloc;
		hamon::flat_multimap<Key, T, TestLess<Key>, KeyContainer, MappedContainer> v{hamon::sorted_equivalent, key_cont, mapped_cont, comp, alloc};
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

GTEST_TEST(FlatMultimapTest, CtorContAllocTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<UseAllocContainer<int>, UseAllocContainer<char>, hamon::less<>>()));
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace ctor_cont_alloc_test

}	// namespace hamon_flat_multimap_test
