/**
 *	@file	unit_test_flat_multimap_ctor_first_last_alloc.cpp
 *
 *	@brief	first と last とアロケータを引数に取るコンストラクタのテスト
 *
 *	template<class InputIterator, class Alloc>
 *	constexpr flat_multimap(InputIterator first, InputIterator last, const Alloc& a);
 *
 *	template<class InputIterator, class Alloc>
 *	constexpr flat_multimap(InputIterator first, InputIterator last,
 *		const key_compare& comp, const Alloc& a);
 *
 *	template<class InputIterator, class Alloc>
 *	constexpr flat_multimap(sorted_equivalent_t, InputIterator first, InputIterator last,
 *		const Alloc& a);
 *
 *	template<class InputIterator, class Alloc>
 *	constexpr flat_multimap(sorted_equivalent_t, InputIterator first, InputIterator last,
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
#include "iterator_test.hpp"
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
{

namespace ctor_first_last_alloc_test
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
	using Map = hamon::flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>;
	using ValueType = typename Map::value_type;
	using InputIterator = IteratorWrapper<ValueType>;
	using Alloc = hamon::allocator<char>;

	static_assert( hamon::is_constructible<Map, InputIterator, InputIterator, Alloc const&>::value, "");
	static_assert( hamon::is_constructible<Map, InputIterator, InputIterator, Compare const&, Alloc const&>::value, "");
	static_assert( hamon::is_constructible<Map, hamon::sorted_equivalent_t, InputIterator, InputIterator, Alloc const&>::value, "");
	static_assert( hamon::is_constructible<Map, hamon::sorted_equivalent_t, InputIterator, InputIterator, Compare const&, Alloc const&>::value, "");

	static_assert(!hamon::is_nothrow_constructible<Map, InputIterator, InputIterator, Alloc const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, InputIterator, InputIterator, Compare const&, Alloc const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, hamon::sorted_equivalent_t, InputIterator, InputIterator, Alloc const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, hamon::sorted_equivalent_t, InputIterator, InputIterator, Compare const&, Alloc const&>::value, "");

	static_assert( hamon::is_implicitly_constructible<Map, InputIterator, InputIterator, Alloc const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, InputIterator, InputIterator, Compare const&, Alloc const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, hamon::sorted_equivalent_t, InputIterator, InputIterator, Alloc const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, hamon::sorted_equivalent_t, InputIterator, InputIterator, Compare const&, Alloc const&>::value, "");

	static_assert(!hamon::is_trivially_constructible<Map, InputIterator, InputIterator, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, InputIterator, InputIterator, Compare const&, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, hamon::sorted_equivalent_t, InputIterator, InputIterator, Alloc const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, hamon::sorted_equivalent_t, InputIterator, InputIterator, Compare const&, Alloc const&>::value, "");

	{
		ValueType a[] =
		{
			{Key{1}, T{10}},
			{Key{3}, T{20}},
			{Key{2}, T{30}},
		};
		Alloc const alloc;
		Map v{InputIterator{a}, InputIterator{a + 3}, alloc};
		VERIFY(check_invariant(v));
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 1);
	}
	{
		ValueType a[] =
		{
			{Key{1}, T{10}},
			{Key{3}, T{20}},
			{Key{2}, T{30}},
		};
		TestLess<Key> const comp{42};
		Alloc const alloc;
		hamon::flat_multimap<Key, T, TestLess<Key>, KeyContainer, MappedContainer> v{InputIterator{a}, InputIterator{a + 3}, comp, alloc};
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
		ValueType a[] =
		{
			{Key{1}, T{10}},
			{Key{3}, T{20}},
			{Key{2}, T{30}},
		};
		hamon::ranges::sort(a, Map{}.value_comp());
		Alloc const alloc;
		Map v{hamon::sorted_equivalent, InputIterator{a}, InputIterator{a + 3}, alloc};
		VERIFY(check_invariant(v));
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.count(Key{1}) == 1);
		VERIFY(v.count(Key{2}) == 1);
		VERIFY(v.count(Key{3}) == 1);
	}
	{
		ValueType a[] =
		{
			{Key{0}, T{40}},
			{Key{1}, T{20}},
			{Key{3}, T{10}},
			{Key{4}, T{30}},
		};
		TestLess<Key> const comp{43};
		Alloc const alloc;
		hamon::flat_multimap<Key, T, TestLess<Key>, KeyContainer, MappedContainer> v{hamon::sorted_equivalent, InputIterator{a}, InputIterator{a + 4}, comp, alloc};
		VERIFY(check_invariant(v));
		VERIFY(!v.empty());
		VERIFY(v.size() == 4);
		VERIFY(v.key_comp() == comp);
		auto it = v.begin();
		VERIFY(it->first == Key{0});
		VERIFY(it->second == T{40});
		++it;
		VERIFY(it->first == Key{1});
		VERIFY(it->second == T{20});
		++it;
		VERIFY(it->first == Key{3});
		VERIFY(it->second == T{10});
		++it;
		VERIFY(it->first == Key{4});
		VERIFY(it->second == T{30});
		++it;
		VERIFY(it == v.end());
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

GTEST_TEST(FlatMultimapTest, CtorFirstLastAllocTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<UseAllocContainer<int>, UseAllocContainer<char>, hamon::less<>>()));
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace ctor_first_last_alloc_test

}	// namespace hamon_flat_multimap_test
