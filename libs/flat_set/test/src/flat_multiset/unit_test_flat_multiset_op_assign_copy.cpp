/**
 *	@file	unit_test_flat_multiset_op_assign_copy.cpp
 *
 *	@brief	コピー代入演算子のテスト
 */

#include <hamon/flat_set/flat_multiset.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <deque>
#include "constexpr_test.hpp"
#include "flat_multiset_test_helper.hpp"

namespace hamon_flat_multiset_test
{

namespace op_assign_copy_test
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
		using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;

		static_assert( hamon::is_assignable<Set, Set const&>::value, "");
		static_assert(!hamon::is_nothrow_assignable<Set, Set const&>::value, "");
		static_assert(!hamon::is_trivially_assignable<Set, Set const&>::value, "");

		KeyContainerAllocator key_alloc{13};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		Compare comp{15};
		Set v1(key_cont, comp);
		Set v2;
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		v2 = v1;
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()         == comp);
		auto keys2 = hamon::move(v2).extract();
		VERIFY(keys2                 == key_cont);
		VERIFY(keys2.get_allocator() == key_alloc);
		v2.replace(hamon::move(keys2));

		// v1 is unchanged
		VERIFY(v1.key_comp()         == comp);
		auto keys1 = hamon::move(v1).extract();
		VERIFY(keys1                 == key_cont);
		VERIFY(keys1.get_allocator() == key_alloc);

		// self-assignment
		v2 = static_cast<Set const&>(v2);
		VERIFY(v2.key_comp()          == comp);
		keys2 = hamon::move(v2).extract();
		VERIFY(keys2                 == key_cont);
		VERIFY(keys2.get_allocator() == key_alloc);
	}
	{
		using Key = int;
		using Compare = TestLess<Key>;
		using KeyContainerAllocator = TestAllocator2<Key>;
		using KeyContainer = TKeyContainer<Key, KeyContainerAllocator>;
		using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;

		static_assert( hamon::is_assignable<Set, Set const&>::value, "");
		static_assert(!hamon::is_nothrow_assignable<Set, Set const&>::value, "");
		static_assert(!hamon::is_trivially_assignable<Set, Set const&>::value, "");

		KeyContainerAllocator key_alloc{13};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		Compare comp{15};
		Set v1(key_cont, comp);
		Set v2;
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		v2 = v1;
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()         == comp);
		auto keys2 = hamon::move(v2).extract();
		VERIFY(keys2                 == key_cont);
		VERIFY(keys2.get_allocator() == key_alloc);
		v2.replace(hamon::move(keys2));

		// v1 is unchanged
		VERIFY(v1.key_comp()         == comp);
		auto keys1 = hamon::move(v1).extract();
		VERIFY(keys1                 == key_cont);
		VERIFY(keys1.get_allocator() == key_alloc);

		// self-assignment
		v2 = static_cast<Set const&>(v2);
		VERIFY(v2.key_comp()          == comp);
		keys2 = hamon::move(v2).extract();
		VERIFY(keys2                 == key_cont);
		VERIFY(keys2.get_allocator() == key_alloc);
	}
	{
		using Key = int;
		using Compare = TestLess<Key>;
		using KeyContainerAllocator = TestAllocator3<Key>;
		using KeyContainer = TKeyContainer<Key, KeyContainerAllocator>;
		using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;

		static_assert( hamon::is_assignable<Set, Set const&>::value, "");
		static_assert(!hamon::is_nothrow_assignable<Set, Set const&>::value, "");
		static_assert(!hamon::is_trivially_assignable<Set, Set const&>::value, "");

		KeyContainerAllocator key_alloc{13};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		Compare comp{15};
		Set v1(key_cont, comp);
		Set v2;
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		v2 = v1;
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()         == comp);
		auto keys2 = hamon::move(v2).extract();
		VERIFY(keys2                 == key_cont);
		VERIFY(keys2.get_allocator() != key_alloc);
		v2.replace(hamon::move(keys2));

		// v1 is unchanged
		VERIFY(v1.key_comp()         == comp);
		auto keys1 = hamon::move(v1).extract();
		VERIFY(keys1                 == key_cont);
		VERIFY(keys1.get_allocator() != key_alloc);

		// self-assignment
		v2 = static_cast<Set const&>(v2);
		VERIFY(v2.key_comp()          == comp);
		keys2 = hamon::move(v2).extract();
		VERIFY(keys2                 == key_cont);
		VERIFY(keys2.get_allocator() != key_alloc);
	}
	{
		using Key = int;
		using Compare = TestLess<Key>;
		using KeyContainerAllocator = TestAllocator4<Key>;
		using KeyContainer = TKeyContainer<Key, KeyContainerAllocator>;
		using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;

		static_assert( hamon::is_assignable<Set, Set const&>::value, "");
		static_assert(!hamon::is_nothrow_assignable<Set, Set const&>::value, "");
		static_assert(!hamon::is_trivially_assignable<Set, Set const&>::value, "");

		KeyContainerAllocator key_alloc{13};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		Compare comp{15};
		Set v1(key_cont, comp);
		Set v2;
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		v2 = v1;
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()         == comp);
		auto keys2 = hamon::move(v2).extract();
		VERIFY(keys2                 == key_cont);
		VERIFY(keys2.get_allocator() == key_alloc);
		v2.replace(hamon::move(keys2));

		// v1 is unchanged
		VERIFY(v1.key_comp()         == comp);
		auto keys1 = hamon::move(v1).extract();
		VERIFY(keys1                 == key_cont);
		VERIFY(keys1.get_allocator() == key_alloc);

		// self-assignment
		v2 = static_cast<Set const&>(v2);
		VERIFY(v2.key_comp()          == comp);
		keys2 = hamon::move(v2).extract();
		VERIFY(keys2                 == key_cont);
		VERIFY(keys2.get_allocator() == key_alloc);
	}
	{
		using Key = int;
		using Compare = TestLess<Key>;
		using KeyContainerAllocator = TestAllocator5<Key>;
		using KeyContainer = TKeyContainer<Key, KeyContainerAllocator>;
		using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;

		static_assert( hamon::is_assignable<Set, Set const&>::value, "");
		static_assert(!hamon::is_nothrow_assignable<Set, Set const&>::value, "");
		static_assert(!hamon::is_trivially_assignable<Set, Set const&>::value, "");

		KeyContainerAllocator key_alloc{13};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		Compare comp{15};
		Set v1(key_cont, comp);
		Set v2;
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		v2 = v1;
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()         == comp);
		auto keys2 = hamon::move(v2).extract();
		VERIFY(keys2                 == key_cont);
		VERIFY(keys2.get_allocator() != key_alloc);
		v2.replace(hamon::move(keys2));

		// v1 is unchanged
		VERIFY(v1.key_comp()         == comp);
		auto keys1 = hamon::move(v1).extract();
		VERIFY(keys1                 == key_cont);
		VERIFY(keys1.get_allocator() == key_alloc);

		// self-assignment
		v2 = static_cast<Set const&>(v2);
		VERIFY(v2.key_comp()          == comp);
		keys2 = hamon::move(v2).extract();
		VERIFY(keys2                 == key_cont);
		VERIFY(keys2.get_allocator() != key_alloc);
	}
	{
		using Key = int;
		using Compare = TestLess<Key>;
		using KeyContainerAllocator = TestAllocator6<Key>;
		using KeyContainer = TKeyContainer<Key, KeyContainerAllocator>;
		using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;

		static_assert( hamon::is_assignable<Set, Set const&>::value, "");
		static_assert(!hamon::is_nothrow_assignable<Set, Set const&>::value, "");
		static_assert(!hamon::is_trivially_assignable<Set, Set const&>::value, "");

		KeyContainerAllocator key_alloc{13};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		Compare comp{15};
		Set v1(key_cont, comp);
		Set v2;
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		v2 = v1;
		VERIFY(check_invariant(v1));
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()         == comp);
		auto keys2 = hamon::move(v2).extract();
		VERIFY(keys2                 == key_cont);
		VERIFY(keys2.get_allocator() != key_alloc);
		v2.replace(hamon::move(keys2));

		// v1 is unchanged
		VERIFY(v1.key_comp()         == comp);
		auto keys1 = hamon::move(v1).extract();
		VERIFY(keys1                 == key_cont);
		VERIFY(keys1.get_allocator() == key_alloc);

		// self-assignment
		v2 = static_cast<Set const&>(v2);
		VERIFY(v2.key_comp()          == comp);
		keys2 = hamon::move(v2).extract();
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
		using KeyContainer = TKeyContainer<Key, ThrowAllocator<Key>>;
		using Set = hamon::flat_multiset<Key, Comp, KeyContainer>;

		KeyContainer a{Key{1}, Key{2}, Key{3}, Key{4}};
		Set v(hamon::sorted_equivalent, hamon::move(a));

		int throw_after = INT_MAX;
		ThrowAllocator<Key> alloc{&throw_after};

		Set v2(alloc);

		throw_after = 1;

		EXPECT_THROW(v2 = v, std::bad_alloc);
		EXPECT_TRUE(check_invariant(v));
		EXPECT_TRUE(check_invariant(v2));
	}
#endif
}

GTEST_TEST(FlatMultisetTest, OpAssignCopyTest)
{
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector>()));
	FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque>()));

	EXPECT_TRUE((test<std::vector>()));
	EXPECT_TRUE((test<std::deque>()));

	test_exceptions<hamon::vector>();
	test_exceptions<hamon::deque>();
}

#undef FLAT_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_SET_TEST_CONSTEXPR

}	// namespace op_assign_copy_test

}	// namespace hamon_flat_multiset_test
