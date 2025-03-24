/**
 *	@file	unit_test_unordered_multiset_ctor_move_allocator.cpp
 *
 *	@brief	ムーブとallocatorを引数に取るコンストラクタのテスト
 *
 *	constexpr unordered_multiset(unordered_multiset&&, const type_identity_t<Allocator>&);
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multiset_test_helper.hpp"

namespace hamon_unordered_multiset_test
{

namespace ctor_move_allocator_test
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

		static_assert( hamon::is_constructible<Set, Set&&, Allocator const&>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
		static_assert( hamon::is_nothrow_constructible<Set, Set&&, Allocator const&>::value, "");
#endif
		static_assert( hamon::is_implicitly_constructible<Set, Set&&, Allocator const&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Set, Set&&, Allocator const&>::value, "");

		Hasher h1{1};
		Hasher h2{2};
		KeyEqual pred1{3};
		KeyEqual pred2{4};
		Allocator alloc1{5};
		Allocator alloc2{6};

		Set v1 { 1, h1, pred1, alloc1 };
		v1.max_load_factor(0.75f);
		v1.insert({ Key{1}, Key{2}, Key{3}, Key{4}, Key{5}, Key{6}, });

		auto const size = v1.size();
		auto const bucket_count = v1.bucket_count();
		auto const max_load_factor = v1.max_load_factor();

		Set const v2{hamon::move(v1), alloc2};

		VERIFY(!v2.empty());
		VERIFY(v2.size() == size);
		VERIFY(v2.begin() != v2.end());
		VERIFY(v2.bucket_count() == bucket_count);
		VERIFY(v2.max_load_factor() == max_load_factor);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.get_allocator() == alloc1);
		VERIFY(v2.get_allocator() == alloc2);
		VERIFY(v2.key_eq() == pred1);
		VERIFY(v2.key_eq() != pred2);
		VERIFY(v2.hash_function() == h1);
		VERIFY(v2.hash_function() != h2);
	}
	{
		using Allocator = TestAllocator2<Key>;
		using Set = hamon::unordered_multiset<Key, Hasher, KeyEqual, Allocator>;

		static_assert(hamon::is_constructible<Set, Set&&, Allocator const&>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
		static_assert(!hamon::is_nothrow_constructible<Set, Set&&, Allocator const&>::value, "");
#endif
		static_assert(hamon::is_implicitly_constructible<Set, Set&&, Allocator const&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Set, Set&&, Allocator const&>::value, "");

		Hasher h1{1};
		Hasher h2{2};
		KeyEqual pred1{3};
		KeyEqual pred2{4};
		Allocator alloc1{5};
		Allocator alloc2{6};

		Set v1 { 64, h1, pred1, alloc1 };
		v1.max_load_factor(0.75f);
		v1.insert({ Key{1}, Key{2}, Key{3}, Key{4}, Key{5}, Key{6}, });

		auto const size = v1.size();
//		auto const bucket_count = v1.bucket_count();
		auto const max_load_factor = v1.max_load_factor();

		Set const v2{hamon::move(v1), alloc2};

		VERIFY(!v2.empty());
		VERIFY(v2.size() == size);
		VERIFY(v2.begin() != v2.end());
//		VERIFY(v2.bucket_count() == bucket_count);
		VERIFY(v2.max_load_factor() == max_load_factor);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.get_allocator() != alloc1);
		VERIFY(v2.get_allocator() == alloc2);
		VERIFY(v2.key_eq() == pred1);
		VERIFY(v2.key_eq() != pred2);
		VERIFY(v2.hash_function() == h1);
		VERIFY(v2.hash_function() != h2);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, CtorMoveAllocatorTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace ctor_move_allocator_test

}	// namespace hamon_unordered_multiset_test
