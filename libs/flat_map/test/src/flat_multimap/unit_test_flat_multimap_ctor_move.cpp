/**
 *	@file	unit_test_flat_multimap_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 */

#include <hamon/flat_map/flat_multimap.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <deque>
#include "constexpr_test.hpp"
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
{

namespace ctor_move_test
{

#if !defined(HAMON_USE_STD_FLAT_MAP)
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename...> class TKeyContainer, template <typename...> class TMappedContainer>
FLAT_MAP_TEST_CONSTEXPR bool test()
{
	{
		using Key = int;
		using T = char;
		using Compare = TestLess<Key>;
		using KeyContainerAllocator = TestAllocator1<Key>;
		using MappedContainerAllocator = TestAllocator2<T>;
		using KeyContainer = TKeyContainer<Key, KeyContainerAllocator>;
		using MappedContainer = TMappedContainer<T, MappedContainerAllocator>;
		using Map = hamon::flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>;

		static_assert( hamon::is_constructible<Map, Map&&>::value, "");
		static_assert( hamon::is_nothrow_constructible<Map, Map&&>::value ==
			(hamon::is_nothrow_move_constructible<Compare>::value &&
			 hamon::is_nothrow_move_constructible<KeyContainer>::value &&
			 hamon::is_nothrow_move_constructible<MappedContainer>::value), "");
		static_assert( hamon::is_implicitly_constructible<Map, Map&&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Map, Map&&>::value, "");

		KeyContainerAllocator key_alloc{13};
		MappedContainerAllocator mapped__alloc{14};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		MappedContainer mapped_cont({T{10}, T{20}, T{30}}, mapped__alloc);
		Compare comp{15};
		Map v1(key_cont, mapped_cont, comp);
		Map v2 = hamon::move(v1);
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()               == comp);
		VERIFY(v2.keys()                   == key_cont);
		VERIFY(v2.values()                 == mapped_cont);
		VERIFY(v2.keys().get_allocator()   == key_alloc);
		VERIFY(v2.values().get_allocator() == mapped__alloc);
	}
	{
		using Key = float;
		using T = short;
		using Compare = TestLess<Key>;
		using KeyContainerAllocator = TestAllocator3<Key>;
		using MappedContainerAllocator = TestAllocator4<T>;
		using KeyContainer = TKeyContainer<Key, KeyContainerAllocator>;
		using MappedContainer = TMappedContainer<T, MappedContainerAllocator>;
		using Map = hamon::flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>;

		static_assert( hamon::is_constructible<Map, Map&&>::value, "");
		static_assert( hamon::is_nothrow_constructible<Map, Map&&>::value ==
			(hamon::is_nothrow_move_constructible<Compare>::value &&
			 hamon::is_nothrow_move_constructible<KeyContainer>::value &&
			 hamon::is_nothrow_move_constructible<MappedContainer>::value), "");
		static_assert( hamon::is_implicitly_constructible<Map, Map&&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Map, Map&&>::value, "");

		KeyContainerAllocator key_alloc{13};
		MappedContainerAllocator mapped__alloc{14};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		MappedContainer mapped_cont({T{10}, T{20}, T{30}}, mapped__alloc);
		Compare comp{15};
		Map v1(key_cont, mapped_cont, comp);
		Map v2 = hamon::move(v1);
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()               == comp);
		VERIFY(v2.keys()                   == key_cont);
		VERIFY(v2.values()                 == mapped_cont);
		VERIFY(v2.keys().get_allocator()   != key_alloc);
		VERIFY(v2.values().get_allocator() == mapped__alloc);
	}
	{
		using Key = long;
		using T = double;
		using Compare = TestLess<Key>;
		using KeyContainerAllocator = TestAllocator5<Key>;
		using MappedContainerAllocator = TestAllocator6<T>;
		using KeyContainer = TKeyContainer<Key, KeyContainerAllocator>;
		using MappedContainer = TMappedContainer<T, MappedContainerAllocator>;
		using Map = hamon::flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>;

		static_assert( hamon::is_constructible<Map, Map&&>::value, "");
		static_assert( hamon::is_nothrow_constructible<Map, Map&&>::value ==
			(hamon::is_nothrow_move_constructible<Compare>::value &&
			 hamon::is_nothrow_move_constructible<KeyContainer>::value &&
			 hamon::is_nothrow_move_constructible<MappedContainer>::value), "");
		static_assert( hamon::is_implicitly_constructible<Map, Map&&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Map, Map&&>::value, "");

		KeyContainerAllocator key_alloc{13};
		MappedContainerAllocator mapped__alloc{14};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		MappedContainer mapped_cont({T{10}, T{20}, T{30}}, mapped__alloc);
		Compare comp{15};
		Map v1(key_cont, mapped_cont, comp);
		Map v2 = hamon::move(v1);
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()               == comp);
		VERIFY(v2.keys()                   == key_cont);
		VERIFY(v2.values()                 == mapped_cont);
		VERIFY(v2.keys().get_allocator()   == key_alloc);
		VERIFY(v2.values().get_allocator() == mapped__alloc);
	}
	return true;
}

#undef VERIFY

template <template <typename...> class TKeyContainer, template <typename...> class TValueContainer>
void test_exceptions()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	using Key = int;
	using T = int;
	using Comp = hamon::less<Key>;
	{
		using KeyContainer = ThrowOnMoveContainer<Key>;
		using ValueContainer = TValueContainer<T>;
		using Map = hamon::flat_multimap<Key, T, Comp, KeyContainer, ValueContainer>;

		Map v;
		v.emplace(1, 1);
		v.emplace(2, 2);
		EXPECT_THROW(Map v2 = hamon::move(v), int);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = TKeyContainer<Key>;
		using ValueContainer = ThrowOnMoveContainer<T>;
		using Map = hamon::flat_multimap<Key, T, Comp, KeyContainer, ValueContainer>;

		Map v;
		v.emplace(1, 1);
		v.emplace(2, 2);
		EXPECT_THROW(Map v2 = hamon::move(v), int);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatMultimapTest, CtorMoveTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector, hamon::vector>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector, hamon::deque>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque, hamon::vector>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque, hamon::deque>()));

	EXPECT_TRUE((test<std::vector, std::vector>()));
	EXPECT_TRUE((test<std::vector, std::deque>()));
	EXPECT_TRUE((test<std::deque, std::vector>()));
	EXPECT_TRUE((test<std::deque, std::deque>()));

	test_exceptions<hamon::vector, hamon::vector>();
	test_exceptions<hamon::deque, hamon::deque>();
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace ctor_move_test

}	// namespace hamon_flat_multimap_test
