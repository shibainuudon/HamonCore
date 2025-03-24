/**
 *	@file	unit_test_unordered_multimap_op_assign_copy.cpp
 *
 *	@brief	コピー代入演算子のテスト
 *
 *	constexpr unordered_multimap& operator=(const unordered_multimap&);
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/type_traits/is_copy_assignable.hpp>
#include <hamon/type_traits/is_nothrow_copy_assignable.hpp>
#include <hamon/type_traits/is_trivially_copy_assignable.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multimap_test_helper.hpp"

namespace hamon_unordered_multimap_test
{

namespace op_assign_copy_test
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
		using Allocator = TestAllocator4<ValueType>;
		using Map = hamon::unordered_multimap<Key, T, Hasher, KeyEqual, Allocator>;

		static_assert( hamon::is_copy_assignable<Map>::value, "");
		static_assert(!hamon::is_nothrow_copy_assignable<Map>::value, "");
		static_assert(!hamon::is_trivially_copy_assignable<Map>::value, "");

		Hasher h1{1};
		Hasher h2{2};
		KeyEqual pred1{3};
		KeyEqual pred2{4};
		Allocator alloc1{5};
		Allocator alloc2{6};

		Map v1{0, h2, pred2, alloc2};
		VERIFY(v1.empty());

		Map const v2
		{
			{
				{ Key{1}, T{10} },
				{ Key{2}, T{20} },
				{ Key{3}, T{30} },
				{ Key{4}, T{40} },
				{ Key{5}, T{50} },
				{ Key{6}, T{60} },
			},
			2, h1, pred1, alloc1
		};

		{
			auto& r = (v1 = v2);
			VERIFY(&r == &v1);
			VERIFY(&r != &v2);
		}
		VERIFY(!v1.empty());
		VERIFY(v1.size() == v2.size());
		VERIFY(v1.begin() != v1.end());
		VERIFY(v1.bucket_count() == v2.bucket_count());
		VERIFY(v1.max_load_factor() == v2.max_load_factor());
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.get_allocator() == alloc1);
		VERIFY(v1.get_allocator() != alloc2);
		VERIFY(v1.key_eq() == pred1);
		VERIFY(v1.key_eq() != pred2);
		VERIFY(v1.hash_function() == h1);
		VERIFY(v1.hash_function() != h2);

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
		{
			auto& r = (v1 = v1);
			VERIFY(&r == &v1);
			VERIFY(&r != &v2);
		}
HAMON_WARNING_POP()
		VERIFY(!v1.empty());
		VERIFY(v1.size() == v2.size());
		VERIFY(v1.begin() != v1.end());
		VERIFY(v1.bucket_count() == v2.bucket_count());
		VERIFY(v1.max_load_factor() == v2.max_load_factor());
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.get_allocator() == alloc1);
		VERIFY(v1.get_allocator() != alloc2);
		VERIFY(v1.key_eq() == pred1);
		VERIFY(v1.key_eq() != pred2);
		VERIFY(v1.hash_function() == h1);
		VERIFY(v1.hash_function() != h2);
	}
	{
		using Allocator = TestAllocator5<ValueType>;
		using Map = hamon::unordered_multimap<Key, T, Hasher, KeyEqual, Allocator>;

		static_assert( hamon::is_copy_assignable<Map>::value, "");
		static_assert(!hamon::is_nothrow_copy_assignable<Map>::value, "");
		static_assert(!hamon::is_trivially_copy_assignable<Map>::value, "");

		Hasher h1{1};
		Hasher h2{2};
		KeyEqual pred1{3};
		KeyEqual pred2{4};
		Allocator alloc1{5};
		Allocator alloc2{6};

		Map v1{0, h2, pred2, alloc2};
		v1.max_load_factor(0.5f);
		VERIFY(v1.empty());

		Map const v2
		{
			{
				{ Key{1}, T{10} },
				{ Key{2}, T{20} },
				{ Key{3}, T{30} },
				{ Key{4}, T{40} },
				{ Key{5}, T{50} },
				{ Key{6}, T{60} },
			},
			2, h1, pred1, alloc1
		};

		{
			auto& r = (v1 = v2);
			VERIFY(&r == &v1);
			VERIFY(&r != &v2);
		}
		VERIFY(!v1.empty());
		VERIFY(v1.size() == v2.size());
		VERIFY(v1.begin() != v1.end());
		VERIFY(v1.bucket_count() == v2.bucket_count());
		VERIFY(v1.max_load_factor() == v2.max_load_factor());
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.get_allocator() != alloc1);	// allocator not propagated
		VERIFY(v1.get_allocator() == alloc2);
		VERIFY(v1.key_eq() == pred1);
		VERIFY(v1.key_eq() != pred2);
		VERIFY(v1.hash_function() == h1);
		VERIFY(v1.hash_function() != h2);

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_CLANG("-Wself-assign-overloaded")
		{
			auto& r = (v1 = v1);
			VERIFY(&r == &v1);
			VERIFY(&r != &v2);
		}
HAMON_WARNING_POP()
		VERIFY(!v1.empty());
		VERIFY(v1.size() == v2.size());
		VERIFY(v1.begin() != v1.end());
		VERIFY(v1.bucket_count() == v2.bucket_count());
		VERIFY(v1.max_load_factor() == v2.max_load_factor());
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.get_allocator() != alloc1);	// allocator not propagated
		VERIFY(v1.get_allocator() == alloc2);
		VERIFY(v1.key_eq() == pred1);
		VERIFY(v1.key_eq() != pred2);
		VERIFY(v1.hash_function() == h1);
		VERIFY(v1.hash_function() != h2);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, OpAssignCopyTest)
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

}	// namespace op_assign_copy_test

}	// namespace hamon_unordered_multimap_test
