/**
 *	@file	unit_test_unordered_map_ctor_move_allocator.cpp
 *
 *	@brief	ムーブとallocatorを引数に取るコンストラクタのテスト
 *
 *	constexpr unordered_map(unordered_map&&, const type_identity_t<Allocator>&);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_map_test
{

namespace ctor_move_allocator_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MAP)
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
	using Allocator = typename Map::allocator_type;

	static_assert( hamon::is_constructible<Map, Map&&, Allocator const&>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MAP)
	static_assert(!hamon::is_nothrow_constructible<Map, Map&&, Allocator const&>::value, "");
#endif
	static_assert( hamon::is_implicitly_constructible<Map, Map&&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Map, Map&&, Allocator const&>::value, "");

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
