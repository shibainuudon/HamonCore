/**
 *	@file	unit_test_unordered_multiset_op_assign_move.cpp
 *
 *	@brief	ムーブ代入演算子のテスト
 *
 *	constexpr unordered_multiset& operator=(unordered_multiset&&)
 *		noexcept(allocator_traits<Allocator>::is_always_equal::value &&
 *			is_nothrow_move_assignable_v<Hash> &&
 *			is_nothrow_move_assignable_v<Pred>);
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <hamon/type_traits/is_nothrow_move_assignable.hpp>
#include <hamon/type_traits/is_trivially_move_assignable.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multiset_test_helper.hpp"

namespace hamon_unordered_multiset_test
{

namespace op_assign_move_test
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

		static_assert( hamon::is_move_assignable<Set>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
		static_assert( hamon::is_nothrow_move_assignable<Set>::value, "");
#endif
		static_assert(!hamon::is_trivially_move_assignable<Set>::value, "");

		Hasher h1{1};
		Hasher h2{2};
		KeyEqual pred1{3};
		KeyEqual pred2{4};
		Allocator alloc1{5};
		Allocator alloc2{6};

		Set v1{0, h2, pred2, alloc2};
		VERIFY(v1.empty());

		Set v2
		{
			{ Key{1}, Key{2}, Key{3}, Key{4}, Key{5}, Key{6}, },
			64, h1, pred1, alloc1
		};

		auto const size = v2.size();
		auto const max_load_factor = v2.max_load_factor();

		{
			auto& r = (v1 = hamon::move(v2));
			VERIFY(&r == &v1);
			VERIFY(&r != &v2);
		}
		VERIFY(!v1.empty());
		VERIFY(v1.size() == size);
		VERIFY(v1.max_load_factor() == max_load_factor);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.get_allocator() == alloc1);
		VERIFY(v1.get_allocator() == alloc2);
		VERIFY(v1.key_eq() == pred1);
		VERIFY(v1.key_eq() != pred2);
		VERIFY(v1.hash_function() == h1);
		VERIFY(v1.hash_function() != h2);
	}
	{
		using Allocator = TestAllocator4<Key>;
		using Set = hamon::unordered_multiset<Key, Hasher, KeyEqual, Allocator>;

		static_assert( hamon::is_move_assignable<Set>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
		static_assert(!hamon::is_nothrow_move_assignable<Set>::value, "");
#endif
		static_assert(!hamon::is_trivially_move_assignable<Set>::value, "");

		Hasher h1{1};
		Hasher h2{2};
		KeyEqual pred1{3};
		KeyEqual pred2{4};
		Allocator alloc1{5};
		Allocator alloc2{6};

		Set v1{128, h2, pred2, alloc2};
		VERIFY(v1.empty());

		Set v2
		{
			{ Key{1}, Key{2}, Key{3}, Key{4}, Key{5}, Key{6}, },
			2, h1, pred1, alloc1
		};

		auto const size = v2.size();
		auto const max_load_factor = v2.max_load_factor();

		{
			auto& r = (v1 = hamon::move(v2));
			VERIFY(&r == &v1);
			VERIFY(&r != &v2);
		}
		VERIFY(!v1.empty());
		VERIFY(v1.size() == size);
		VERIFY(v1.max_load_factor() == max_load_factor);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.get_allocator() != alloc1);	// allocator not propagated
		VERIFY(v1.get_allocator() == alloc2);
		VERIFY(v1.key_eq() == pred1);
		VERIFY(v1.key_eq() != pred2);
		VERIFY(v1.hash_function() == h1);
		VERIFY(v1.hash_function() != h2);
	}
	{
		using Allocator = TestAllocator5<Key>;
		using Set = hamon::unordered_multiset<Key, Hasher, KeyEqual, Allocator>;

		static_assert( hamon::is_move_assignable<Set>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
		static_assert(!hamon::is_nothrow_move_assignable<Set>::value, "");
#endif
		static_assert(!hamon::is_trivially_move_assignable<Set>::value, "");

		Hasher h1{1};
		Hasher h2{2};
		KeyEqual pred1{3};
		KeyEqual pred2{4};
		Allocator alloc1{5};
		Allocator alloc2{6};

		Set v1{32, h2, pred2, alloc2};
		VERIFY(v1.empty());

		Set v2
		{
			{ Key{1}, Key{2}, Key{3}, Key{4}, Key{5}, Key{6}, },
			32, h1, pred1, alloc1
		};

		auto const size = v2.size();
		auto const max_load_factor = v2.max_load_factor();

		{
			auto& r = (v1 = hamon::move(v2));
			VERIFY(&r == &v1);
			VERIFY(&r != &v2);
		}
		VERIFY(!v1.empty());
		VERIFY(v1.size() == size);
		VERIFY(v1.max_load_factor() == max_load_factor);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.get_allocator() == alloc1);
		VERIFY(v1.get_allocator() != alloc2);
		VERIFY(v1.key_eq() == pred1);
		VERIFY(v1.key_eq() != pred2);
		VERIFY(v1.hash_function() == h1);
		VERIFY(v1.hash_function() != h2);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, OpAssignMoveTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace op_assign_move_test

}	// namespace hamon_unordered_multiset_test
