/**
 *	@file	unit_test_flat_multiset_ctor_copy.cpp
 *
 *	@brief	コピーコンストラクタのテスト
 */

#include <hamon/flat_set/flat_multiset.hpp>
#include <hamon/functional.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <deque>
#include "constexpr_test.hpp"
#include "flat_multiset_test_helper.hpp"

namespace hamon_flat_multiset_test
{

namespace ctor_copy_test
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

		static_assert( hamon::is_constructible<Set, Set const&>::value, "");
		static_assert(!hamon::is_nothrow_constructible<Set, Set const&>::value, "");
		static_assert( hamon::is_implicitly_constructible<Set, Set const&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Set, Set const&>::value, "");

		KeyContainerAllocator key_alloc{13};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		Compare comp{15};
		Set v1(key_cont, comp);
		Set v2 = v1;
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()           == comp);
		auto keys2 = hamon::move(v2).extract();
		VERIFY(keys2                   == key_cont);
		VERIFY(keys2.get_allocator()   == key_alloc);

		// v1 is unchanged
		VERIFY(v1.key_comp()           == comp);
		auto keys1 = hamon::move(v1).extract();
		VERIFY(keys1                   == key_cont);
		VERIFY(keys1.get_allocator()   == key_alloc);
	}
	{
		using Key = char;
		using Compare = TestLess<Key>;
		using KeyContainerAllocator = TestAllocator2<Key>;
		using KeyContainer = TKeyContainer<Key, KeyContainerAllocator>;
		using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;

		static_assert( hamon::is_constructible<Set, Set const&>::value, "");
		static_assert(!hamon::is_nothrow_constructible<Set, Set const&>::value, "");
		static_assert( hamon::is_implicitly_constructible<Set, Set const&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Set, Set const&>::value, "");

		KeyContainerAllocator key_alloc{13};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		Compare comp{15};
		Set v1(key_cont, comp);
		Set v2 = v1;
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()           == comp);
		auto keys2 = hamon::move(v2).extract();
		VERIFY(keys2                   == key_cont);
		VERIFY(keys2.get_allocator()   == key_alloc);

		// v1 is unchanged
		VERIFY(v1.key_comp()           == comp);
		auto keys1 = hamon::move(v1).extract();
		VERIFY(keys1                   == key_cont);
		VERIFY(keys1.get_allocator()   == key_alloc);
	}
	{
		using Key = float;
		using Compare = TestLess<Key>;
		using KeyContainerAllocator = TestAllocator3<Key>;
		using KeyContainer = TKeyContainer<Key, KeyContainerAllocator>;
		using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;

		static_assert( hamon::is_constructible<Set, Set const&>::value, "");
		static_assert(!hamon::is_nothrow_constructible<Set, Set const&>::value, "");
		static_assert( hamon::is_implicitly_constructible<Set, Set const&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Set, Set const&>::value, "");

		KeyContainerAllocator key_alloc{13};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		Compare comp{15};
		Set v1(key_cont, comp);
		Set v2 = v1;
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()           == comp);
		auto keys2 = hamon::move(v2).extract();
		VERIFY(keys2                   == key_cont);
		VERIFY(keys2.get_allocator()   != key_alloc);

		// v1 is unchanged
		VERIFY(v1.key_comp()           == comp);
		auto keys1 = hamon::move(v1).extract();
		VERIFY(keys1                   == key_cont);
		VERIFY(keys1.get_allocator()   != key_alloc);
	}
	{
		using Key = short;
		using Compare = TestLess<Key>;
		using KeyContainerAllocator = TestAllocator4<Key>;
		using KeyContainer = TKeyContainer<Key, KeyContainerAllocator>;
		using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;

		static_assert( hamon::is_constructible<Set, Set const&>::value, "");
		static_assert(!hamon::is_nothrow_constructible<Set, Set const&>::value, "");
		static_assert( hamon::is_implicitly_constructible<Set, Set const&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Set, Set const&>::value, "");

		KeyContainerAllocator key_alloc{13};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		Compare comp{15};
		Set v1(key_cont, comp);
		Set v2 = v1;
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()           == comp);
		auto keys2 = hamon::move(v2).extract();
		VERIFY(keys2                   == key_cont);
		VERIFY(keys2.get_allocator()   == key_alloc);

		// v1 is unchanged
		VERIFY(v1.key_comp()           == comp);
		auto keys1 = hamon::move(v1).extract();
		VERIFY(keys1                   == key_cont);
		VERIFY(keys1.get_allocator()   == key_alloc);
	}
	{
		using Key = long;
		using Compare = TestLess<Key>;
		using KeyContainerAllocator = TestAllocator5<Key>;
		using KeyContainer = TKeyContainer<Key, KeyContainerAllocator>;
		using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;

		static_assert( hamon::is_constructible<Set, Set const&>::value, "");
		static_assert(!hamon::is_nothrow_constructible<Set, Set const&>::value, "");
		static_assert( hamon::is_implicitly_constructible<Set, Set const&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Set, Set const&>::value, "");

		KeyContainerAllocator key_alloc{13};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		Compare comp{15};
		Set v1(key_cont, comp);
		Set v2 = v1;
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()           == comp);
		auto keys2 = hamon::move(v2).extract();
		VERIFY(keys2                   == key_cont);
		VERIFY(keys2.get_allocator()   == key_alloc);

		// v1 is unchanged
		VERIFY(v1.key_comp()           == comp);
		auto keys1 = hamon::move(v1).extract();
		VERIFY(keys1                   == key_cont);
		VERIFY(keys1.get_allocator()   == key_alloc);
	}
	{
		using Key = double;
		using Compare = TestLess<Key>;
		using KeyContainerAllocator = TestAllocator6<Key>;
		using KeyContainer = TKeyContainer<Key, KeyContainerAllocator>;
		using Set = hamon::flat_multiset<Key, Compare, KeyContainer>;

		static_assert( hamon::is_constructible<Set, Set const&>::value, "");
		static_assert(!hamon::is_nothrow_constructible<Set, Set const&>::value, "");
		static_assert( hamon::is_implicitly_constructible<Set, Set const&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Set, Set const&>::value, "");

		KeyContainerAllocator key_alloc{13};
		KeyContainer key_cont({Key{1},Key{2},Key{3}}, key_alloc);
		Compare comp{15};
		Set v1(key_cont, comp);
		Set v2 = v1;
		VERIFY(check_invariant(v2));
		VERIFY(v2.key_comp()           == comp);
		auto keys2 = hamon::move(v2).extract();
		VERIFY(keys2                   == key_cont);
		VERIFY(keys2.get_allocator()   == key_alloc);

		// v1 is unchanged
		VERIFY(v1.key_comp()           == comp);
		auto keys1 = hamon::move(v1).extract();
		VERIFY(keys1                   == key_cont);
		VERIFY(keys1.get_allocator()   == key_alloc);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultisetTest, CtorCopyTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque>()));

	EXPECT_TRUE((test<std::vector>()));
	EXPECT_TRUE((test<std::deque>()));
}

}	// namespace ctor_copy_test

}	// namespace hamon_flat_multiset_test
