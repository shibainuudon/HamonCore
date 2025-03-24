/**
 *	@file	unit_test_unordered_map_ctor_n.cpp
 *
 *	@brief	バケット数を引数に取るコンストラクタのテスト
 *
 *	constexpr explicit unordered_map(
 *		size_type n,
 *		const hasher& hf = hasher(),
 *		const key_equal& eql = key_equal(),
 *		const allocator_type& alloc = allocator_type());
 * 
 *	constexpr unordered_map(size_type n, const allocator_type& a)
 *		: unordered_map(n, hasher(), key_equal(), a) { }
 *
 *	constexpr unordered_map(size_type n, const hasher& hf, const allocator_type& a)
 *		: unordered_map(n, hf, key_equal(), a) { }
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_map_test
{

namespace ctor_n_test
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

	static_assert( hamon::is_constructible<Map, SizeType>::value, "");
	static_assert( hamon::is_constructible<Map, SizeType, Hasher const&>::value, "");
	static_assert( hamon::is_constructible<Map, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert( hamon::is_constructible<Map, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, SizeType>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, SizeType, Hasher const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MAP)
	static_assert(!hamon::is_implicitly_constructible<Map, SizeType>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Map, SizeType, Hasher const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Map, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Map, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");
#endif
	static_assert(!hamon::is_trivially_constructible<Map, SizeType>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, SizeType, Hasher const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, SizeType, Hasher const&, KeyEqual const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, SizeType, Hasher const&, KeyEqual const&, Allocator const&>::value, "");

	// (n)
	{
		Map v{10};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.bucket_count() >= 10);
	}
	// (n, hf)
	{
		Map v{8, Hasher{}};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.bucket_count() >= 8);
	}
	// (n, hf, eql, a)
	{
		Map v{17, Hasher{}, KeyEqual{}};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.bucket_count() >= 17);
	}
	// (n, hf, eql, a)
	{
		Allocator alloc;
		Map v{3, Hasher{}, KeyEqual{}, alloc};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.bucket_count() >= 3);
		VERIFY(v.get_allocator() == alloc);
	}

#if !(defined(HAMON_USE_STD_UNORDERED_MAP) && (HAMON_CXX_STANDARD < 14))
	static_assert( hamon::is_constructible<Map, SizeType, Allocator const&>::value, "");
	static_assert( hamon::is_constructible<Map, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Map, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, SizeType, Allocator const&>::value, "");
	static_assert( hamon::is_implicitly_constructible<Map, SizeType, Hasher const&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, SizeType, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, SizeType, Hasher const&, Allocator const&>::value, "");

	// (n, a)
	{
		Allocator alloc;
		Map v{4, alloc};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.bucket_count() >= 4);
		VERIFY(v.get_allocator() == alloc);
	}
	// (n, hf, a)
	{
		Allocator alloc;
		Map v{1, Hasher{}, alloc};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.bucket_count() >= 1);
		VERIFY(v.get_allocator() == alloc);
	}
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, CtorNTest)
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

}	// namespace ctor_n_test

}	// namespace hamon_unordered_map_test
