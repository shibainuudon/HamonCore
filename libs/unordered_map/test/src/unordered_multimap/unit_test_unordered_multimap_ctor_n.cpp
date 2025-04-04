﻿/**
 *	@file	unit_test_unordered_multimap_ctor_n.cpp
 *
 *	@brief	バケット数を引数に取るコンストラクタのテスト
 *
 *	constexpr explicit unordered_multimap(
 *		size_type n,
 *		const hasher& hf = hasher(),
 *		const key_equal& eql = key_equal(),
 *		const allocator_type& a = allocator_type());
 *
 *	constexpr unordered_multimap(size_type n, const allocator_type& a)
 *		: unordered_multimap(n, hasher(), key_equal(), a) { }
 *
 *	constexpr unordered_multimap(size_type n, const hasher& hf, const allocator_type& a)
 *		: unordered_multimap(n, hf, key_equal(), a) { }
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multimap_test
{

namespace ctor_n_test
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

	static_assert( hamon::is_constructible<Map, SizeType>::value, "");
	static_assert( hamon::is_constructible<Map, SizeType, Hasher const&>::value, "");
	static_assert( hamon::is_constructible<Map, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert( hamon::is_constructible<Map, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, SizeType>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, SizeType, Hasher const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
#if !(defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && (defined(HAMON_STDLIB_DINKUMWARE) || defined(HAMON_APPLE_CLANG)))
	static_assert(!hamon::is_implicitly_constructible<Map, SizeType>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Map, SizeType, Hasher const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Map, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Map, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
#endif
	static_assert(!hamon::is_trivially_constructible<Map, SizeType>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, SizeType, Hasher const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");

#if !(defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && (HAMON_CXX_STANDARD < 14))
	static_assert( hamon::is_constructible<Map, SizeType, Allocator const&>::value, "");
	static_assert( hamon::is_constructible<Map, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, SizeType, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, SizeType, Hasher const&, Allocator const&>::value, "");
#endif

#if 0
	{
		Map v{10};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.bucket_count() >= 10);
	}
	{
		Map v{8, Hasher{}};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.bucket_count() >= 8);
	}
	{
		Map v{17, Hasher{}, KeyEqual{}};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.bucket_count() >= 17);
	}
	{
		Allocator alloc;
		Map v{3, Hasher{}, KeyEqual{}, alloc};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.bucket_count() >= 3);
		VERIFY(v.get_allocator() == alloc);
	}
	{
		Allocator alloc;
		Map v{4, alloc};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.bucket_count() >= 4);
		VERIFY(v.get_allocator() == alloc);
	}
	{
		Allocator alloc;
		Map v{1, Hasher{}, alloc};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.bucket_count() >= 1);
		VERIFY(v.get_allocator() == alloc);
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, CtorNTest)
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

}	// namespace ctor_n_test

}	// namespace hamon_unordered_multimap_test
