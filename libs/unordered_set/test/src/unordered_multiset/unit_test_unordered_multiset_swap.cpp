/**
 *	@file	unit_test_unordered_multiset_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	constexpr void swap(unordered_multiset&)
 *		noexcept(allocator_traits<Allocator>::is_always_equal::value &&
 *			is_nothrow_swappable_v<Hash> && is_nothrow_swappable_v<Pred>);
 *
 *	template<class Key, class T, class Hash, class Pred, class Alloc>
 *	constexpr void swap(
 *		unordered_multiset<Key, T, Hash, Pred, Alloc>& x,
 *		unordered_multiset<Key, T, Hash, Pred, Alloc>& y)
 *			noexcept(noexcept(x.swap(y)));
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multiset_test_helper.hpp"

namespace hamon_unordered_multiset_test
{

namespace swap_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
UNORDERED_MULTISET_TEST_CONSTEXPR bool test()
{
	using Hasher = TestHash<Key>;
	using KeyEqual = TestEqualTo<Key>;

	{
		using Allocator = TestAllocator1<Key>;
		using Set = hamon::unordered_multiset<Key, Hasher, KeyEqual, Allocator>;

		static_assert(hamon::is_same<decltype(hamon::declval<Set&>().swap(hamon::declval<Set&>())), void>::value, "");
		static_assert(hamon::is_same<decltype(swap(hamon::declval<Set&>(), hamon::declval<Set&>())), void>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
		static_assert(!noexcept(hamon::declval<Set&>().swap(hamon::declval<Set&>())), "");
		static_assert(!noexcept(swap(hamon::declval<Set&>(), hamon::declval<Set&>())), "");
#endif

		Hasher h1{1};
		Hasher h2{2};
		KeyEqual pred1{3};
		KeyEqual pred2{4};
		Allocator alloc1{5};
		Allocator alloc2{6};

		Set v1
		{
			{ Key{1}, Key{2}, Key{3}, },
			2, h1, pred1, alloc1
		};

		Set v2
		{
			{ Key{1}, Key{2}, Key{3}, Key{4}, Key{5}, Key{6}, },
			2, h2, pred2, alloc2
		};

		v1.swap(v2);

		VERIFY(v1.size() == 6);
		VERIFY(v1.get_allocator() == alloc1);
		VERIFY(v1.get_allocator() == alloc2);
		VERIFY(v1.key_eq() != pred1);
		VERIFY(v1.key_eq() == pred2);
		VERIFY(v1.hash_function() != h1);
		VERIFY(v1.hash_function() == h2);

		VERIFY(v2.size() == 3);
		VERIFY(v2.get_allocator() == alloc1);
		VERIFY(v2.get_allocator() == alloc2);
		VERIFY(v2.key_eq() == pred1);
		VERIFY(v2.key_eq() != pred2);
		VERIFY(v2.hash_function() == h1);
		VERIFY(v2.hash_function() != h2);

		swap(v1, v2);

		VERIFY(v1.size() == 3);
		VERIFY(v1.get_allocator() == alloc1);
		VERIFY(v1.get_allocator() == alloc2);
		VERIFY(v1.key_eq() == pred1);
		VERIFY(v1.key_eq() != pred2);
		VERIFY(v1.hash_function() == h1);
		VERIFY(v1.hash_function() != h2);

		VERIFY(v2.size() == 6);
		VERIFY(v2.get_allocator() == alloc1);
		VERIFY(v2.get_allocator() == alloc2);
		VERIFY(v2.key_eq() != pred1);
		VERIFY(v2.key_eq() == pred2);
		VERIFY(v2.hash_function() != h1);
		VERIFY(v2.hash_function() == h2);
	}
	{
		using Allocator = TestAllocator2<Key>;
		using Set = hamon::unordered_multiset<Key, Hasher, KeyEqual, Allocator>;

		static_assert(hamon::is_same<decltype(hamon::declval<Set&>().swap(hamon::declval<Set&>())), void>::value, "");
		static_assert(hamon::is_same<decltype(swap(hamon::declval<Set&>(), hamon::declval<Set&>())), void>::value, "");
		static_assert(!noexcept(hamon::declval<Set&>().swap(hamon::declval<Set&>())), "");
		static_assert(!noexcept(swap(hamon::declval<Set&>(), hamon::declval<Set&>())), "");

		Hasher h1{1};
		Hasher h2{2};
		KeyEqual pred1{3};
		KeyEqual pred2{4};
		Allocator alloc1{5};
		Allocator alloc2{6};

		Set v1
		{
			{ Key{1}, Key{2}, Key{3}, },
			2, h1, pred1, alloc1
		};

		Set v2
		{
			{ Key{1}, Key{2}, Key{3}, Key{4}, Key{5}, Key{6}, },
			2, h2, pred2, alloc2
		};

		v1.swap(v2);

		VERIFY(v1.size() == 6);
		VERIFY(v1.get_allocator() != alloc1);
		VERIFY(v1.get_allocator() == alloc2);
		VERIFY(v1.key_eq() != pred1);
		VERIFY(v1.key_eq() == pred2);
		VERIFY(v1.hash_function() != h1);
		VERIFY(v1.hash_function() == h2);

		VERIFY(v2.size() == 3);
		VERIFY(v2.get_allocator() == alloc1);
		VERIFY(v2.get_allocator() != alloc2);
		VERIFY(v2.key_eq() == pred1);
		VERIFY(v2.key_eq() != pred2);
		VERIFY(v2.hash_function() == h1);
		VERIFY(v2.hash_function() != h2);

		swap(v1, v2);

		VERIFY(v1.size() == 3);
		VERIFY(v1.get_allocator() == alloc1);
		VERIFY(v1.get_allocator() != alloc2);
		VERIFY(v1.key_eq() == pred1);
		VERIFY(v1.key_eq() != pred2);
		VERIFY(v1.hash_function() == h1);
		VERIFY(v1.hash_function() != h2);

		VERIFY(v2.size() == 6);
		VERIFY(v2.get_allocator() != alloc1);
		VERIFY(v2.get_allocator() == alloc2);
		VERIFY(v2.key_eq() != pred1);
		VERIFY(v2.key_eq() == pred2);
		VERIFY(v2.hash_function() != h1);
		VERIFY(v2.hash_function() == h2);
	}
#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
	{
		using Allocator = TestAllocator6<Key>;
		using Set = hamon::unordered_multiset<Key, Hasher, KeyEqual, Allocator>;

		static_assert(hamon::is_same<decltype(hamon::declval<Set&>().swap(hamon::declval<Set&>())), void>::value, "");
		static_assert(hamon::is_same<decltype(swap(hamon::declval<Set&>(), hamon::declval<Set&>())), void>::value, "");
		static_assert(!noexcept(hamon::declval<Set&>().swap(hamon::declval<Set&>())), "");
		static_assert(!noexcept(swap(hamon::declval<Set&>(), hamon::declval<Set&>())), "");

		Hasher h1{1};
		Hasher h2{2};
		KeyEqual pred1{3};
		KeyEqual pred2{4};
		Allocator alloc1{5};
		Allocator alloc2{6};

		Set v1
		{
			{ Key{1}, Key{2}, Key{3}, },
			2, h1, pred1, alloc1
		};

		Set v2
		{
			{ Key{1}, Key{2}, Key{3}, Key{4}, Key{5}, Key{6}, },
			2, h2, pred2, alloc2
		};

		v1.swap(v2);

		VERIFY(v1.size() == 6);
		VERIFY(v1.get_allocator() == alloc1);
		VERIFY(v1.get_allocator() != alloc2);
		VERIFY(v1.key_eq() != pred1);
		VERIFY(v1.key_eq() == pred2);
		VERIFY(v1.hash_function() != h1);
		VERIFY(v1.hash_function() == h2);

		VERIFY(v2.size() == 3);
		VERIFY(v2.get_allocator() != alloc1);
		VERIFY(v2.get_allocator() == alloc2);
		VERIFY(v2.key_eq() == pred1);
		VERIFY(v2.key_eq() != pred2);
		VERIFY(v2.hash_function() == h1);
		VERIFY(v2.hash_function() != h2);

		swap(v1, v2);

		VERIFY(v1.size() == 3);
		VERIFY(v1.get_allocator() == alloc1);
		VERIFY(v1.get_allocator() != alloc2);
		VERIFY(v1.key_eq() == pred1);
		VERIFY(v1.key_eq() != pred2);
		VERIFY(v1.hash_function() == h1);
		VERIFY(v1.hash_function() != h2);

		VERIFY(v2.size() == 6);
		VERIFY(v2.get_allocator() != alloc1);
		VERIFY(v2.get_allocator() == alloc2);
		VERIFY(v2.key_eq() != pred1);
		VERIFY(v2.key_eq() == pred2);
		VERIFY(v2.hash_function() != h1);
		VERIFY(v2.hash_function() == h2);
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, SwapTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace swap_test

}	// namespace hamon_unordered_multiset_test
