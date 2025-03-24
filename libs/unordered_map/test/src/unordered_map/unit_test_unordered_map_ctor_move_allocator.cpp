/**
 *	@file	unit_test_unordered_map_ctor_move_allocator.cpp
 *
 *	@brief	ムーブとallocatorを引数に取るコンストラクタのテスト
 *
 *	constexpr unordered_map(unordered_map&&, const type_identity_t<Allocator>&);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_map_test_helper.hpp"

namespace hamon_unordered_map_test
{

namespace ctor_move_allocator_test
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

		static_assert( hamon::is_constructible<Map, Map&&, Allocator const&>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MAP)
		static_assert( hamon::is_nothrow_constructible<Map, Map&&, Allocator const&>::value, "");
#endif
		static_assert( hamon::is_implicitly_constructible<Map, Map&&, Allocator const&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Map, Map&&, Allocator const&>::value, "");

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
			45, h1, pred1, alloc1
		};

		auto const size = v1.size();
		auto const bucket_count = v1.bucket_count();
		auto const max_load_factor = v1.max_load_factor();

		Map const v2{hamon::move(v1), alloc2};

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
		VERIFY(v2.at(Key{1}) == T{10});
		VERIFY(v2.at(Key{2}) == T{20});
		VERIFY(v2.at(Key{3}) == T{30});
		VERIFY(v2.at(Key{4}) == T{40});
		VERIFY(v2.at(Key{5}) == T{50});
		VERIFY(v2.at(Key{6}) == T{60});
	}
	{
		using Allocator = TestAllocator2<ValueType>;
		using Map = hamon::unordered_map<Key, T, Hasher, KeyEqual, Allocator>;

		static_assert(hamon::is_constructible<Map, Map&&, Allocator const&>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MAP)
		static_assert(!hamon::is_nothrow_constructible<Map, Map&&, Allocator const&>::value, "");
#endif
		static_assert(hamon::is_implicitly_constructible<Map, Map&&, Allocator const&>::value, "");
		static_assert(!hamon::is_trivially_constructible<Map, Map&&, Allocator const&>::value, "");

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
			42, h1, pred1, alloc1
		};

		auto const size = v1.size();
//		auto const bucket_count = v1.bucket_count();
		auto const max_load_factor = v1.max_load_factor();

		Map const v2{hamon::move(v1), alloc2};

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
		VERIFY(v2.at(Key{1}) == T{10});
		VERIFY(v2.at(Key{2}) == T{20});
		VERIFY(v2.at(Key{3}) == T{30});
		VERIFY(v2.at(Key{4}) == T{40});
		VERIFY(v2.at(Key{5}) == T{50});
		VERIFY(v2.at(Key{6}) == T{60});
	}
	{
		using Map = hamon::unordered_map<Key, T>;

		Map v1{};
		v1.max_load_factor(1.5f);
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

		Map const v2{hamon::move(v1), v1.get_allocator()};

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

GTEST_TEST(UnorderedMapTest, CtorMoveAllocatorTest)
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

}	// namespace ctor_move_allocator_test

}	// namespace hamon_unordered_map_test
