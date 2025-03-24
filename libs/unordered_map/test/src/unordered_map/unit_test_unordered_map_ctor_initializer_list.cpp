/**
 *	@file	unit_test_unordered_map_ctor_initializer_list.cpp
 *
 *	@brief	initializer_listを引数に取るコンストラクタのテスト
 *
 *	constexpr unordered_map(
 *		initializer_list<value_type> il,
 *		size_type n = see below,
 *		const hasher& hf = hasher(),
 *		const key_equal& eql = key_equal(),
 *		const allocator_type& a = allocator_type());
 *
 *	constexpr unordered_map(
 *		initializer_list<value_type> il,
 *		size_type n,
 *		const allocator_type& a)
 *
 *	constexpr unordered_map(
 *		initializer_list<value_type> il,
 *		size_type n,
 *		const hasher& hf,
 *		const allocator_type& a);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <gtest/gtest.h>
#include <initializer_list>
#include "constexpr_test.hpp"

namespace hamon_unordered_map_test
{

namespace ctor_initializer_list_test
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
	using Map = hamon::unordered_map<Key, T>;
	using SizeType  = typename Map::size_type;
	using Hasher    = typename Map::hasher;
	using KeyEqual  = typename Map::key_equal;
	using Allocator = typename Map::allocator_type;
	using ValueType = typename Map::value_type;

	static_assert( hamon::is_constructible<Map, std::initializer_list<ValueType>>::value, "");
	static_assert( hamon::is_constructible<Map, std::initializer_list<ValueType>, SizeType>::value, "");
	static_assert( hamon::is_constructible<Map, std::initializer_list<ValueType>, SizeType, Hasher const&>::value, "");
	static_assert( hamon::is_constructible<Map, std::initializer_list<ValueType>, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert( hamon::is_constructible<Map, std::initializer_list<ValueType>, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, std::initializer_list<ValueType>>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, std::initializer_list<ValueType>, SizeType>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, std::initializer_list<ValueType>, SizeType, Hasher const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, std::initializer_list<ValueType>, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, std::initializer_list<ValueType>, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, std::initializer_list<ValueType>>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, std::initializer_list<ValueType>, SizeType>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, std::initializer_list<ValueType>, SizeType, Hasher const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, std::initializer_list<ValueType>, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, std::initializer_list<ValueType>, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, std::initializer_list<ValueType>>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, std::initializer_list<ValueType>, SizeType>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, std::initializer_list<ValueType>, SizeType, Hasher const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, std::initializer_list<ValueType>, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, std::initializer_list<ValueType>, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");

	// (il)
	{
		Map v
		{
			{Key{2}, T{10}},
			{Key{3}, T{20}},
			{Key{1}, T{30}},
			{Key{1}, T{40}},
			{Key{2}, T{50}},
			{Key{3}, T{60}},
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 1);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	{
		Map v
		{
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
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 50);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 1);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	// (il, n)
	{
		Map v
		{
			{
				{ Key{3}, T{10} },
				{ Key{1}, T{20} },
				{ Key{4}, T{30} },
				{ Key{1}, T{40} },
				{ Key{5}, T{50} },
			},
			3
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 4);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 3);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	// (il, n, hf)
	{
		Map v
		{
			{
				{ Key{3}, T{10} },
				{ Key{1}, T{20} },
				{ Key{4}, T{30} },
				{ Key{1}, T{40} },
				{ Key{5}, T{50} },
				{ Key{2}, T{60} },
			},
			5, Hasher{}
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 5);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	// (il, n, hf, eql)
	{
		Map v
		{
			{
				{ Key{1}, T{10} },
				{ Key{2}, T{20} },
				{ Key{3}, T{30} },
				{ Key{4}, T{40} },
				{ Key{5}, T{50} },
				{ Key{6}, T{60} },
			},
			10, Hasher{}, KeyEqual{}
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 6);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 10);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
	}
	// (il, n, hf, eql, a)
	{
		Allocator alloc;
		Map v
		{
			{
				{ Key{1}, T{10} },
				{ Key{2}, T{20} },
				{ Key{3}, T{30} },
				{ Key{4}, T{40} },
				{ Key{5}, T{50} },
				{ Key{6}, T{60} },
			},
			2, Hasher{}, KeyEqual{}, alloc
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 6);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 2);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.get_allocator() == alloc);
	}

#if !(defined(HAMON_USE_STD_UNORDERED_MAP) && (HAMON_CXX_STANDARD < 14))
	static_assert( hamon::is_constructible<Map, std::initializer_list<ValueType>, SizeType, Allocator const&>::value, "");
	static_assert( hamon::is_constructible<Map, std::initializer_list<ValueType>, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, std::initializer_list<ValueType>, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, std::initializer_list<ValueType>, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, std::initializer_list<ValueType>, SizeType, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, std::initializer_list<ValueType>, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, std::initializer_list<ValueType>, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, std::initializer_list<ValueType>, SizeType, Hasher const&, Allocator const&>::value, "");

	// (il, n, a)
	{
		Allocator alloc;
		Map v
		{
			{
				{Key{2}, T{10}},
				{Key{3}, T{20}},
				{Key{1}, T{30}},
				{Key{1}, T{40}},
				{Key{2}, T{50}},
				{Key{3}, T{60}},
			},
			8, alloc
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 8);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.get_allocator() == alloc);
	}
	// (il, n, hf, a)
	{
		Allocator alloc;
		Map v
		{
			{
				{Key{2}, T{10}},
				{Key{3}, T{20}},
				{Key{1}, T{30}},
				{Key{1}, T{40}},
				{Key{2}, T{50}},
				{Key{3}, T{60}},
			},
			16, Hasher{}, alloc
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 16);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.get_allocator() == alloc);
	}
#endif

#if !defined(HAMON_USE_STD_UNORDERED_MAP)	// TODO(LWG 2713)
	static_assert( hamon::is_constructible<Map, std::initializer_list<ValueType>, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, std::initializer_list<ValueType>, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, std::initializer_list<ValueType>, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, std::initializer_list<ValueType>, Allocator const&>::value, "");

	// (il, a)
	{
		Allocator alloc;
		Map v
		{
			{
				{Key{2}, T{10}},
				{Key{3}, T{20}},
				{Key{1}, T{30}},
				{Key{1}, T{40}},
				{Key{2}, T{50}},
				{Key{3}, T{60}},
			},
			alloc
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 1);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.get_allocator() == alloc);
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, CtorInitializerListTest)
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

}	// namespace ctor_initializer_list_test

}	// namespace hamon_unordered_map_test
