/**
 *	@file	unit_test_unordered_map_op_assign_move.cpp
 *
 *	@brief	ムーブ代入演算子のテスト
 *
 *	constexpr unordered_map& operator=(unordered_map&&)
 *		noexcept(allocator_traits<Allocator>::is_always_equal::value &&
 *			is_nothrow_move_assignable_v<Hash> &&
 *			is_nothrow_move_assignable_v<Pred>);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/type_traits/is_move_assignable.hpp>
#include <hamon/type_traits/is_nothrow_move_assignable.hpp>
#include <hamon/type_traits/is_trivially_move_assignable.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_map_test_helper.hpp"

namespace hamon_unordered_map_test
{

namespace op_assign_move_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test()
{
	using ValueType = typename hamon::unordered_map<Key, T>::value_type;
	using Hasher = TestHash<Key>;
	using KeyEqual = TestEqualTo<Key>;

	{
		using Allocator = TestAllocator1<ValueType>;
		using Map = hamon::unordered_map<Key, T, Hasher, KeyEqual, Allocator>;

		static_assert( hamon::is_move_assignable<Map>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MAP)
		static_assert( hamon::is_nothrow_move_assignable<Map>::value, "");
#endif
		static_assert(!hamon::is_trivially_move_assignable<Map>::value, "");

		Hasher h1{1};
		Hasher h2{2};
		KeyEqual pred1{3};
		KeyEqual pred2{4};
		Allocator alloc1{5};
		Allocator alloc2{6};

		Map v1{0, h2, pred2, alloc2};
		v1.max_load_factor(1.5f);
		VERIFY(v1.empty());

		Map v2
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

		auto const size = v2.size();
		auto const bucket_count = v2.bucket_count();
		auto const max_load_factor = v2.max_load_factor();

		{
			auto& r = (v1 = hamon::move(v2));
			VERIFY(&r == &v1);
			VERIFY(&r != &v2);
		}
		VERIFY(!v1.empty());
		VERIFY(v1.size() == size);
		VERIFY(v1.begin() != v1.end());
		VERIFY(v1.bucket_count() == bucket_count);
		VERIFY(v1.max_load_factor() == max_load_factor);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.get_allocator() == alloc1);
		VERIFY(v1.get_allocator() == alloc2);
		VERIFY(v1.key_eq() == pred1);
		VERIFY(v1.key_eq() != pred2);
		VERIFY(v1.hash_function() == h1);
		VERIFY(v1.hash_function() != h2);
		VERIFY(v1.at(Key{1}) == T{10});
		VERIFY(v1.at(Key{2}) == T{20});
		VERIFY(v1.at(Key{3}) == T{30});
		VERIFY(v1.at(Key{4}) == T{40});
		VERIFY(v1.at(Key{5}) == T{50});
		VERIFY(v1.at(Key{6}) == T{60});
	}
	{
		using Allocator = TestAllocator4<ValueType>;
		using Map = hamon::unordered_map<Key, T, Hasher, KeyEqual, Allocator>;

		static_assert( hamon::is_move_assignable<Map>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MAP)
		static_assert(!hamon::is_nothrow_move_assignable<Map>::value, "");
#endif
		static_assert(!hamon::is_trivially_move_assignable<Map>::value, "");

		Hasher h1{1};
		Hasher h2{2};
		KeyEqual pred1{3};
		KeyEqual pred2{4};
		Allocator alloc1{5};
		Allocator alloc2{6};

		Map v1{0, h2, pred2, alloc2};
		VERIFY(v1.empty());

		Map v2{2, h1, pred1, alloc1};
		v2.max_load_factor(1.5f);
		v2.insert({
			{ Key{1}, T{10} },
			{ Key{2}, T{20} },
			{ Key{3}, T{30} },
			{ Key{4}, T{40} },
			{ Key{5}, T{50} },
			{ Key{6}, T{60} },
		});

		auto const size = v2.size();
		auto const bucket_count = v2.bucket_count();
		auto const max_load_factor = v2.max_load_factor();

		{
			auto& r = (v1 = hamon::move(v2));
			VERIFY(&r == &v1);
			VERIFY(&r != &v2);
		}
		VERIFY(!v1.empty());
		VERIFY(v1.size() == size);
		VERIFY(v1.begin() != v1.end());
		VERIFY(v1.bucket_count() == bucket_count);
		VERIFY(v1.max_load_factor() == max_load_factor);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.get_allocator() != alloc1);	// allocator not propagated
		VERIFY(v1.get_allocator() == alloc2);
		VERIFY(v1.key_eq() == pred1);
		VERIFY(v1.key_eq() != pred2);
		VERIFY(v1.hash_function() == h1);
		VERIFY(v1.hash_function() != h2);
		VERIFY(v1.at(Key{1}) == T{10});
		VERIFY(v1.at(Key{2}) == T{20});
		VERIFY(v1.at(Key{3}) == T{30});
		VERIFY(v1.at(Key{4}) == T{40});
		VERIFY(v1.at(Key{5}) == T{50});
		VERIFY(v1.at(Key{6}) == T{60});
	}
	{
		using Allocator = TestAllocator5<ValueType>;
		using Map = hamon::unordered_map<Key, T, Hasher, KeyEqual, Allocator>;

		static_assert( hamon::is_move_assignable<Map>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MAP)
		static_assert(!hamon::is_nothrow_move_assignable<Map>::value, "");
#endif
		static_assert(!hamon::is_trivially_move_assignable<Map>::value, "");

		Hasher h1{1};
		Hasher h2{2};
		KeyEqual pred1{3};
		KeyEqual pred2{4};
		Allocator alloc1{5};
		Allocator alloc2{6};

		Map v1{0, h2, pred2, alloc2};
		v1.max_load_factor(0.5f);
		VERIFY(v1.empty());

		Map v2
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

		auto const size = v2.size();
		auto const bucket_count = v2.bucket_count();
		auto const max_load_factor = v2.max_load_factor();

		{
			auto& r = (v1 = hamon::move(v2));
			VERIFY(&r == &v1);
			VERIFY(&r != &v2);
		}
		VERIFY(!v1.empty());
		VERIFY(v1.size() == size);
		VERIFY(v1.begin() != v1.end());
		VERIFY(v1.bucket_count() == bucket_count);
		VERIFY(v1.max_load_factor() == max_load_factor);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.get_allocator() == alloc1);
		VERIFY(v1.get_allocator() != alloc2);
		VERIFY(v1.key_eq() == pred1);
		VERIFY(v1.key_eq() != pred2);
		VERIFY(v1.hash_function() == h1);
		VERIFY(v1.hash_function() != h2);
		VERIFY(v1.at(Key{1}) == T{10});
		VERIFY(v1.at(Key{2}) == T{20});
		VERIFY(v1.at(Key{3}) == T{30});
		VERIFY(v1.at(Key{4}) == T{40});
		VERIFY(v1.at(Key{5}) == T{50});
		VERIFY(v1.at(Key{6}) == T{60});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, OpAssignMoveTest)
{
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

#undef UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MAP_TEST_CONSTEXPR

}	// namespace op_assign_move_test

}	// namespace hamon_unordered_map_test
