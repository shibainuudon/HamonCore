/**
 *	@file	unit_test_flat_multiset_op_assign_move.cpp
 *
 *	@brief	ムーブ代入演算子のテスト
 */

#include <hamon/flat_set/flat_multiset.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <deque>
#include "constexpr_test.hpp"
#include "flat_multiset_test_helper.hpp"

namespace hamon_flat_multiset_test
{

namespace op_assign_move_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <template <typename...> class TKeyContainer>
HAMON_CXX20_CONSTEXPR bool test()
{
	{
		using Key = int;
		using Compare = TestLess<Key>;
		using KeyContainerAllocator = TestAllocator1<Key>;
		using KeyContainer = TKeyContainer<Key, KeyContainerAllocator>;
		using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;

		static_assert( hamon::is_assignable<Set, Set&&>::value, "");
		static_assert( hamon::is_nothrow_assignable<Set, Set&&>::value ==
			(hamon::is_nothrow_move_assignable<Compare>::value &&
			 hamon::is_nothrow_move_assignable<KeyContainer>::value), "");
		static_assert(!hamon::is_trivially_assignable<Set, Set&&>::value, "");

		KeyContainerAllocator key_alloc{13};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		Compare comp{15};
		Set v1(key_cont, comp);
		Set v2;
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		v2 = hamon::move(v1);
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()         == comp);
		auto keys2 = hamon::move(v2).extract();
		VERIFY(keys2                 == key_cont);
		VERIFY(keys2.get_allocator() == key_alloc);
	}
	{
		using Key = int;
		using Compare = TestLess<Key>;
		using KeyContainerAllocator = TestAllocator2<Key>;
		using KeyContainer = TKeyContainer<Key, KeyContainerAllocator>;
		using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;

		static_assert( hamon::is_assignable<Set, Set&&>::value, "");
		static_assert( hamon::is_nothrow_assignable<Set, Set&&>::value ==
			(hamon::is_nothrow_move_assignable<Compare>::value &&
			 hamon::is_nothrow_move_assignable<KeyContainer>::value), "");
		static_assert(!hamon::is_trivially_assignable<Set, Set&&>::value, "");

		KeyContainerAllocator key_alloc{13};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		Compare comp{15};
		Set v1(key_cont, comp);
		Set v2;
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		v2 = hamon::move(v1);
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()         == comp);
		auto keys2 = hamon::move(v2).extract();
		VERIFY(keys2                 == key_cont);
		VERIFY(keys2.get_allocator() == key_alloc);
	}
	{
		using Key = int;
		using Compare = TestLess<Key>;
		using KeyContainerAllocator = TestAllocator3<Key>;
		using KeyContainer = TKeyContainer<Key, KeyContainerAllocator>;
		using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;

		static_assert( hamon::is_assignable<Set, Set&&>::value, "");
		static_assert( hamon::is_nothrow_assignable<Set, Set&&>::value ==
			(hamon::is_nothrow_move_assignable<Compare>::value &&
			 hamon::is_nothrow_move_assignable<KeyContainer>::value), "");
		static_assert(!hamon::is_trivially_assignable<Set, Set&&>::value, "");

		KeyContainerAllocator key_alloc{13};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		Compare comp{15};
		Set v1(key_cont, comp);
		Set v2;
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		v2 = hamon::move(v1);
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()         == comp);
		auto keys2 = hamon::move(v2).extract();
		VERIFY(keys2                 == key_cont);
		VERIFY(keys2.get_allocator() != key_alloc);
	}
	{
		using Key = int;
		using Compare = TestLess<Key>;
		using KeyContainerAllocator = TestAllocator4<Key>;
		using KeyContainer = TKeyContainer<Key, KeyContainerAllocator>;
		using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;

		static_assert( hamon::is_assignable<Set, Set&&>::value, "");
		static_assert( hamon::is_nothrow_assignable<Set, Set&&>::value ==
			(hamon::is_nothrow_move_assignable<Compare>::value &&
			 hamon::is_nothrow_move_assignable<KeyContainer>::value), "");
		static_assert(!hamon::is_trivially_assignable<Set, Set&&>::value, "");

		KeyContainerAllocator key_alloc{13};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		Compare comp{15};
		Set v1(key_cont, comp);
		Set v2;
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		v2 = hamon::move(v1);
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()         == comp);
		auto keys2 = hamon::move(v2).extract();
		VERIFY(keys2                 == key_cont);
		VERIFY(keys2.get_allocator() != key_alloc);
	}
	{
		using Key = int;
		using Compare = TestLess<Key>;
		using KeyContainerAllocator = TestAllocator5<Key>;
		using KeyContainer = TKeyContainer<Key, KeyContainerAllocator>;
		using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;

		static_assert( hamon::is_assignable<Set, Set&&>::value, "");
		static_assert( hamon::is_nothrow_assignable<Set, Set&&>::value ==
			(hamon::is_nothrow_move_assignable<Compare>::value &&
			 hamon::is_nothrow_move_assignable<KeyContainer>::value), "");
		static_assert(!hamon::is_trivially_assignable<Set, Set&&>::value, "");

		KeyContainerAllocator key_alloc{13};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		Compare comp{15};
		Set v1(key_cont, comp);
		Set v2;
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		v2 = hamon::move(v1);
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()         == comp);
		auto keys2 = hamon::move(v2).extract();
		VERIFY(keys2                 == key_cont);
		VERIFY(keys2.get_allocator() == key_alloc);
	}
	{
		using Key = int;
		using Compare = TestLess<Key>;
		using KeyContainerAllocator = TestAllocator6<Key>;
		using KeyContainer = TKeyContainer<Key, KeyContainerAllocator>;
		using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;

		static_assert( hamon::is_assignable<Set, Set&&>::value, "");
		static_assert( hamon::is_nothrow_assignable<Set, Set&&>::value ==
			(hamon::is_nothrow_move_assignable<Compare>::value &&
			 hamon::is_nothrow_move_assignable<KeyContainer>::value), "");
		static_assert(!hamon::is_trivially_assignable<Set, Set&&>::value, "");

		KeyContainerAllocator key_alloc{13};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		Compare comp{15};
		Set v1(key_cont, comp);
		Set v2;
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		v2 = hamon::move(v1);
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()         == comp);
		auto keys2 = hamon::move(v2).extract();
		VERIFY(keys2                 == key_cont);
		VERIFY(keys2.get_allocator() != key_alloc);
	}
	return true;
}

#undef VERIFY

template <template <typename...> class TKeyContainer>
void test_exceptions()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	using Key = int;
	using Comp = hamon::less<Key>;
	{
		using KeyContainer = ThrowOnMoveContainer<Key>;
		using Set = hamon::flat_multiset<Key, Comp, KeyContainer>;

		Set v1;
		v1.emplace(1);
		v1.emplace(2);

		Set v2;
		v2.emplace(3);

		EXPECT_THROW(v2 = hamon::move(v1), int);
		EXPECT_TRUE(check_invariant(v1));
		EXPECT_TRUE(check_invariant(v2));
	}
#endif
}

GTEST_TEST(FlatMultisetTest, OpAssignMoveTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque>()));

	EXPECT_TRUE((test<std::vector>()));
	EXPECT_TRUE((test<std::deque>()));

	test_exceptions<hamon::vector>();
	test_exceptions<hamon::deque>();
}

}	// namespace op_assign_move_test

}	// namespace hamon_flat_multiset_test
