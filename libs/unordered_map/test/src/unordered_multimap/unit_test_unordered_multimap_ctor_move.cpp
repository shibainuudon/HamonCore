/**
 *	@file	unit_test_unordered_multimap_ctor_move.cpp
 *
 *	@brief	ムーブコンストラクタのテスト
 *
 *	constexpr unordered_multimap(unordered_multimap&&);
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/type_traits/is_move_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_implicitly_move_constructible.hpp>
#include <hamon/type_traits/is_trivially_move_constructible.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multimap_test_helper.hpp"

namespace hamon_unordered_multimap_test
{

namespace ctor_move_test
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
		using Allocator = TestAllocator2<ValueType>;
		using Map = hamon::unordered_multimap<Key, T, Hasher, KeyEqual, Allocator>;

		static_assert( hamon::is_move_constructible<Map>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
		static_assert( hamon::is_nothrow_move_constructible<Map>::value, "");
#endif
		static_assert( hamon::is_implicitly_move_constructible<Map>::value, "");
		static_assert(!hamon::is_trivially_move_constructible<Map>::value, "");

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
				{ Key{4}, T{40} },
				{ Key{5}, T{50} },
				{ Key{6}, T{60} },
			},
			0, h1, pred1, alloc1
		};

		auto const size = v1.size();
		auto const bucket_count = v1.bucket_count();
		auto const max_load_factor = v1.max_load_factor();

		Map const v2{hamon::move(v1)};

		VERIFY(!v2.empty());
		VERIFY(v2.size() == size);
		VERIFY(v2.begin() != v2.end());
		VERIFY(v2.bucket_count() == bucket_count);
		VERIFY(v2.max_load_factor() == max_load_factor);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.get_allocator() == alloc1);
		VERIFY(v2.get_allocator() != alloc2);
		VERIFY(v2.key_eq() == pred1);
		VERIFY(v2.key_eq() != pred2);
		VERIFY(v2.hash_function() == h1);
		VERIFY(v2.hash_function() != h2);
	}
	{
		using Allocator = TestAllocator3<ValueType>;
		using Map = hamon::unordered_multimap<Key, T, Hasher, KeyEqual, Allocator>;

		static_assert( hamon::is_move_constructible<Map>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
		static_assert( hamon::is_nothrow_move_constructible<Map>::value, "");
#endif
		static_assert( hamon::is_implicitly_move_constructible<Map>::value, "");
		static_assert(!hamon::is_trivially_move_constructible<Map>::value, "");

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
				{ Key{4}, T{40} },
				{ Key{5}, T{50} },
				{ Key{6}, T{60} },
			},
			8, h1, pred1, alloc1
		};

		auto const size = v1.size();
		auto const bucket_count = v1.bucket_count();
		auto const max_load_factor = v1.max_load_factor();

		Map const v2{hamon::move(v1)};

		VERIFY(!v2.empty());
		VERIFY(v2.size() == size);
		VERIFY(v2.begin() != v2.end());
		VERIFY(v2.bucket_count() == bucket_count);
		VERIFY(v2.max_load_factor() == max_load_factor);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.get_allocator() == alloc1);
		VERIFY(v2.get_allocator() != alloc2);
		VERIFY(v2.key_eq() == pred1);
		VERIFY(v2.key_eq() != pred2);
		VERIFY(v2.hash_function() == h1);
		VERIFY(v2.hash_function() != h2);
	}
	{
		using Map = hamon::unordered_multimap<Key, T>;

		Map v1{};
		v1.max_load_factor(0.75f);
		v1.insert({
			{Key{0}, T{10}}, {Key{10}, T{10}}, {Key{20}, T{10}}, {Key{30}, T{10}}, {Key{40}, T{10}},
			{Key{1}, T{10}}, {Key{11}, T{10}}, {Key{21}, T{10}}, {Key{31}, T{10}}, {Key{41}, T{10}},
			{Key{2}, T{10}}, {Key{12}, T{10}}, {Key{22}, T{10}}, {Key{32}, T{10}}, {Key{42}, T{10}},
			{Key{3}, T{10}}, {Key{13}, T{10}}, {Key{23}, T{10}}, {Key{33}, T{10}}, {Key{43}, T{10}},
			{Key{4}, T{10}}, {Key{14}, T{10}}, {Key{24}, T{10}}, {Key{34}, T{10}}, {Key{44}, T{10}},
			{Key{5}, T{10}}, {Key{15}, T{10}}, {Key{25}, T{10}}, {Key{35}, T{10}}, {Key{45}, T{10}},
			{Key{6}, T{10}}, {Key{16}, T{10}}, {Key{26}, T{10}}, {Key{36}, T{10}}, {Key{46}, T{10}},
			{Key{7}, T{10}}, {Key{17}, T{10}}, {Key{27}, T{10}}, {Key{37}, T{10}}, {Key{47}, T{10}},
			{Key{8}, T{10}}, {Key{18}, T{10}}, {Key{28}, T{10}}, {Key{38}, T{10}}, {Key{48}, T{10}},
			{Key{9}, T{10}}, {Key{19}, T{10}}, {Key{29}, T{10}}, {Key{39}, T{10}}, {Key{49}, T{10}},
		});

		auto const size = v1.size();
		auto const bucket_count = v1.bucket_count();
		auto const max_load_factor = v1.max_load_factor();

		Map const v2{hamon::move(v1)};

		VERIFY(!v2.empty());
		VERIFY(v2.size() == size);
		VERIFY(v2.begin() != v2.end());
		VERIFY(v2.bucket_count() == bucket_count);
		VERIFY(v2.max_load_factor() == max_load_factor);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, CtorMoveTest)
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

}	// namespace ctor_move_test

}	// namespace hamon_unordered_multimap_test
