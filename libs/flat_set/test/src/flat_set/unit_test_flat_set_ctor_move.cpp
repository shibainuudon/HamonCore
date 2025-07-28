/**
 *	@file	unit_test_flat_set_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 */

#include <hamon/flat_set/flat_set.hpp>
#include <hamon/functional.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <deque>
#include "constexpr_test.hpp"
#include "flat_set_test_helper.hpp"

namespace hamon_flat_set_test
{

namespace ctor_move_test
{

#if !defined(HAMON_USE_STD_FLAT_SET)
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename...> class TKeyContainer>
FLAT_SET_TEST_CONSTEXPR bool test()
{
	{
		using Key = int;
		using Compare = TestLess<Key>;
		using KeyContainerAllocator = TestAllocator1<Key>;
		using KeyContainer = TKeyContainer<Key, KeyContainerAllocator>;
		using Set = hamon::flat_set<Key, Compare, KeyContainer>;

		static_assert( hamon::is_constructible<Set, Set&&>::value, "");
		static_assert( hamon::is_nothrow_constructible<Set, Set&&>::value ==
			(hamon::is_nothrow_move_constructible<Compare>::value &&
			 hamon::is_nothrow_move_constructible<KeyContainer>::value), "");
		static_assert( hamon::is_implicitly_constructible<Set, Set&&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Set, Set&&>::value, "");

		KeyContainerAllocator key_alloc{13};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		Compare comp{15};
		Set v1(key_cont, comp);
		Set v2 = hamon::move(v1);
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()          == comp);
		auto keys = hamon::move(v2).extract();
		VERIFY(keys                   == key_cont);
		VERIFY(keys.get_allocator()   == key_alloc);
	}
	{
		using Key = double;
		using Compare = TestLess<Key>;
		using KeyContainerAllocator = TestAllocator2<Key>;
		using KeyContainer = TKeyContainer<Key, KeyContainerAllocator>;
		using Set = hamon::flat_set<Key, Compare, KeyContainer>;

		static_assert( hamon::is_constructible<Set, Set&&>::value, "");
		static_assert( hamon::is_nothrow_constructible<Set, Set&&>::value ==
			(hamon::is_nothrow_move_constructible<Compare>::value &&
			 hamon::is_nothrow_move_constructible<KeyContainer>::value), "");
		static_assert( hamon::is_implicitly_constructible<Set, Set&&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Set, Set&&>::value, "");

		KeyContainerAllocator key_alloc{13};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		Compare comp{15};
		Set v1(key_cont, comp);
		Set v2 = hamon::move(v1);
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()          == comp);
		auto keys = hamon::move(v2).extract();
		VERIFY(keys                   == key_cont);
		VERIFY(keys.get_allocator()   == key_alloc);
	}
	{
		using Key = short;
		using Compare = TestLess<Key>;
		using KeyContainerAllocator = TestAllocator3<Key>;
		using KeyContainer = TKeyContainer<Key, KeyContainerAllocator>;
		using Set = hamon::flat_set<Key, Compare, KeyContainer>;

		static_assert( hamon::is_constructible<Set, Set&&>::value, "");
		static_assert( hamon::is_nothrow_constructible<Set, Set&&>::value ==
			(hamon::is_nothrow_move_constructible<Compare>::value &&
			 hamon::is_nothrow_move_constructible<KeyContainer>::value), "");
		static_assert( hamon::is_implicitly_constructible<Set, Set&&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Set, Set&&>::value, "");

		KeyContainerAllocator key_alloc{13};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		Compare comp{15};
		Set v1(key_cont, comp);
		Set v2 = hamon::move(v1);
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()          == comp);
		auto keys = hamon::move(v2).extract();
		VERIFY(keys                   == key_cont);
		VERIFY(keys.get_allocator()   != key_alloc);
	}
	{
		using Key = float;
		using Compare = TestLess<Key>;
		using KeyContainerAllocator = TestAllocator4<Key>;
		using KeyContainer = TKeyContainer<Key, KeyContainerAllocator>;
		using Set = hamon::flat_set<Key, Compare, KeyContainer>;

		static_assert( hamon::is_constructible<Set, Set&&>::value, "");
		static_assert( hamon::is_nothrow_constructible<Set, Set&&>::value ==
			(hamon::is_nothrow_move_constructible<Compare>::value &&
			 hamon::is_nothrow_move_constructible<KeyContainer>::value), "");
		static_assert( hamon::is_implicitly_constructible<Set, Set&&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Set, Set&&>::value, "");

		KeyContainerAllocator key_alloc{13};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		Compare comp{15};
		Set v1(key_cont, comp);
		Set v2 = hamon::move(v1);
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()          == comp);
		auto keys = hamon::move(v2).extract();
		VERIFY(keys                   == key_cont);
		VERIFY(keys.get_allocator()   == key_alloc);
	}
	{
		using Key = long;
		using Compare = TestLess<Key>;
		using KeyContainerAllocator = TestAllocator5<Key>;
		using KeyContainer = TKeyContainer<Key, KeyContainerAllocator>;
		using Set = hamon::flat_set<Key, Compare, KeyContainer>;

		static_assert( hamon::is_constructible<Set, Set&&>::value, "");
		static_assert( hamon::is_nothrow_constructible<Set, Set&&>::value ==
			(hamon::is_nothrow_move_constructible<Compare>::value &&
			 hamon::is_nothrow_move_constructible<KeyContainer>::value), "");
		static_assert( hamon::is_implicitly_constructible<Set, Set&&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Set, Set&&>::value, "");

		KeyContainerAllocator key_alloc{13};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		Compare comp{15};
		Set v1(key_cont, comp);
		Set v2 = hamon::move(v1);
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()          == comp);
		auto keys = hamon::move(v2).extract();
		VERIFY(keys                   == key_cont);
		VERIFY(keys.get_allocator()   == key_alloc);
	}
	{
		using Key = char;
		using Compare = TestLess<Key>;
		using KeyContainerAllocator = TestAllocator6<Key>;
		using KeyContainer = TKeyContainer<Key, KeyContainerAllocator>;
		using Set = hamon::flat_set<Key, Compare, KeyContainer>;

		static_assert( hamon::is_constructible<Set, Set&&>::value, "");
		static_assert( hamon::is_nothrow_constructible<Set, Set&&>::value ==
			(hamon::is_nothrow_move_constructible<Compare>::value &&
			 hamon::is_nothrow_move_constructible<KeyContainer>::value), "");
		static_assert( hamon::is_implicitly_constructible<Set, Set&&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Set, Set&&>::value, "");

		KeyContainerAllocator key_alloc{13};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		Compare comp{15};
		Set v1(key_cont, comp);
		Set v2 = hamon::move(v1);
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()          == comp);
		auto keys = hamon::move(v2).extract();
		VERIFY(keys                   == key_cont);
		VERIFY(keys.get_allocator()   == key_alloc);
	}

	return true;
}

#undef VERIFY

void test_exceptions()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	using Key = int;
	using Comp = hamon::less<Key>;
	{
		using KeyContainer = ThrowOnMoveContainer<Key>;
		using Set = hamon::flat_set<Key, Comp, KeyContainer>;

		Set v;
		v.emplace(1);
		v.emplace(2);
		EXPECT_THROW(Set v2 = hamon::move(v), int);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatSetTest, CtorMoveTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque>()));

	EXPECT_TRUE((test<std::vector>()));
	EXPECT_TRUE((test<std::deque>()));

	test_exceptions();
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace ctor_move_test

}	// namespace hamon_flat_set_test
