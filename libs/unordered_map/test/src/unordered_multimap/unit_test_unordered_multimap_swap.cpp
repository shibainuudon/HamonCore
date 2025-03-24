/**
 *	@file	unit_test_unordered_multimap_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	constexpr void swap(unordered_multimap&)
 *		noexcept(allocator_traits<Allocator>::is_always_equal::value &&
 *			is_nothrow_swappable_v<Hash> && is_nothrow_swappable_v<Pred>);
 *
 *	template<class Key, class T, class Hash, class Pred, class Alloc>
 *	constexpr void swap(
 *		unordered_multimap<Key, T, Hash, Pred, Alloc>& x,
 *		unordered_multimap<Key, T, Hash, Pred, Alloc>& y)
 *			noexcept(noexcept(x.swap(y)));
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multimap_test_helper.hpp"

namespace hamon_unordered_multimap_test
{

namespace swap_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test()
{
	using ValueType = typename hamon::unordered_multimap<Key, T>::value_type;
	using Hasher = TestHash<Key>;
	using KeyEqual = TestEqualTo<Key>;

	{
		using Allocator = TestAllocator1<ValueType>;
		using Map = hamon::unordered_multimap<Key, T, Hasher, KeyEqual, Allocator>;

		static_assert(hamon::is_same<decltype(hamon::declval<Map&>().swap(hamon::declval<Map&>())), void>::value, "");
		static_assert(hamon::is_same<decltype(swap(hamon::declval<Map&>(), hamon::declval<Map&>())), void>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
		static_assert(!noexcept(hamon::declval<Map&>().swap(hamon::declval<Map&>())), "");
		static_assert(!noexcept(swap(hamon::declval<Map&>(), hamon::declval<Map&>())), "");
#endif

		Hasher h1{1};
		Hasher h2{2};
		KeyEqual pred1{3};
		KeyEqual pred2{4};
		Allocator alloc1{5};
		Allocator alloc2{6};

		Map v1
		{
			{
				{ Key{1}, T{10} },
				{ Key{2}, T{20} },
				{ Key{3}, T{30} },
			},
			2, h1, pred1, alloc1
		};

		Map v2
		{
			{
				{ Key{1}, T{40} },
				{ Key{2}, T{50} },
				{ Key{3}, T{60} },
				{ Key{4}, T{70} },
				{ Key{5}, T{80} },
				{ Key{6}, T{90} },
			},
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
		using Allocator = TestAllocator2<ValueType>;
		using Map = hamon::unordered_multimap<Key, T, Hasher, KeyEqual, Allocator>;

		static_assert(hamon::is_same<decltype(hamon::declval<Map&>().swap(hamon::declval<Map&>())), void>::value, "");
		static_assert(hamon::is_same<decltype(swap(hamon::declval<Map&>(), hamon::declval<Map&>())), void>::value, "");
		static_assert(!noexcept(hamon::declval<Map&>().swap(hamon::declval<Map&>())), "");
		static_assert(!noexcept(swap(hamon::declval<Map&>(), hamon::declval<Map&>())), "");

		Hasher h1{1};
		Hasher h2{2};
		KeyEqual pred1{3};
		KeyEqual pred2{4};
		Allocator alloc1{5};
		Allocator alloc2{6};

		Map v1
		{
			{
				{ Key{1}, T{10} },
				{ Key{2}, T{20} },
				{ Key{3}, T{30} },
			},
			2, h1, pred1, alloc1
		};

		Map v2
		{
			{
				{ Key{1}, T{40} },
				{ Key{2}, T{50} },
				{ Key{3}, T{60} },
				{ Key{4}, T{70} },
				{ Key{5}, T{80} },
				{ Key{6}, T{90} },
			},
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
#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
	{
		using Allocator = TestAllocator6<ValueType>;
		using Map = hamon::unordered_multimap<Key, T, Hasher, KeyEqual, Allocator>;

		static_assert(hamon::is_same<decltype(hamon::declval<Map&>().swap(hamon::declval<Map&>())), void>::value, "");
		static_assert(hamon::is_same<decltype(swap(hamon::declval<Map&>(), hamon::declval<Map&>())), void>::value, "");
		static_assert(!noexcept(hamon::declval<Map&>().swap(hamon::declval<Map&>())), "");
		static_assert(!noexcept(swap(hamon::declval<Map&>(), hamon::declval<Map&>())), "");

		Hasher h1{1};
		Hasher h2{2};
		KeyEqual pred1{3};
		KeyEqual pred2{4};
		Allocator alloc1{5};
		Allocator alloc2{6};

		Map v1
		{
			{
				{ Key{1}, T{10} },
				{ Key{2}, T{20} },
				{ Key{3}, T{30} },
			},
			2, h1, pred1, alloc1
		};

		Map v2
		{
			{
				{ Key{1}, T{40} },
				{ Key{2}, T{50} },
				{ Key{3}, T{60} },
				{ Key{4}, T{70} },
				{ Key{5}, T{80} },
				{ Key{6}, T{90} },
			},
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

GTEST_TEST(UnorderedMultimapTest, SwapTest)
{
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace swap_test

}	// namespace hamon_unordered_multimap_test
