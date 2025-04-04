/**
 *	@file	unit_test_unordered_multimap_ctor_initializer_list.cpp
 *
 *	@brief	initializer_listを引数に取るコンストラクタのテスト
 *
 *	constexpr unordered_multimap(
 *		initializer_list<value_type> il,
 *		size_type n = see below,
 *		const hasher& hf = hasher(),
 *		const key_equal& eql = key_equal(),
 *		const allocator_type& a = allocator_type());
 *
 *	constexpr unordered_multimap(
 *		initializer_list<value_type> il,
 *		size_type n,
 *		const allocator_type& a)
 *
 *	constexpr unordered_multimap(
 *		initializer_list<value_type> il,
 *		size_type n,
 *		const hasher& hf,
 *		const allocator_type& a);
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multimap_test
{

namespace ctor_initializer_list_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
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
	using Map = hamon::unordered_multimap<Key, T>;
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

#if !(defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && (HAMON_CXX_STANDARD < 14))
	static_assert( hamon::is_constructible<Map, std::initializer_list<ValueType>, SizeType, Allocator const&>::value, "");
	static_assert( hamon::is_constructible<Map, std::initializer_list<ValueType>, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, std::initializer_list<ValueType>, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, std::initializer_list<ValueType>, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, std::initializer_list<ValueType>, SizeType, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, std::initializer_list<ValueType>, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, std::initializer_list<ValueType>, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, std::initializer_list<ValueType>, SizeType, Hasher const&, Allocator const&>::value, "");
#endif

#if 0
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
		VERIFY(v.max_load_factor() == 1.0);
	}
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
	}
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
			5,
			Hasher{}
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 5);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 5);
		VERIFY(v.max_load_factor() == 1.0);
	}
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
			10,
			Hasher{},
			KeyEqual{}
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 6);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 10);
		VERIFY(v.max_load_factor() == 1.0);
	}
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
			2,
			Hasher{},
			KeyEqual{},
			alloc
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 6);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 2);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.get_allocator() == alloc);
	}
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
			8,
			alloc
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 8);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.get_allocator() == alloc);
	}
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
			16,
			Hasher{},
			alloc
		};
		VERIFY(!v.empty());
		VERIFY(v.size() == 3);
		VERIFY(v.begin() != v.end());
		VERIFY(v.bucket_count() >= 16);
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.get_allocator() == alloc);
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, CtorInitializerListTest)
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

}	// namespace ctor_initializer_list_test

}	// namespace hamon_unordered_multimap_test
