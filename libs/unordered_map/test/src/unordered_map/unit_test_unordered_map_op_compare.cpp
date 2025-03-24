/**
 *	@file	unit_test_unordered_map_op_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<class Key, class T, class Hash, class Pred, class Alloc>
 *	constexpr bool operator==(
 *		const unordered_map<Key, T, Hash, Pred, Alloc>& a,
 *		const unordered_map<Key, T, Hash, Pred, Alloc>& b);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_map_test
{

namespace op_compare_test
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

	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>() == hamon::declval<Map const&>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>() != hamon::declval<Map const&>()), bool>::value, "");
	static_assert(!noexcept(hamon::declval<Map const&>() == hamon::declval<Map const&>()), "");
	static_assert(!noexcept(hamon::declval<Map const&>() != hamon::declval<Map const&>()), "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, OpCompareTest)
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

}	// namespace op_compare_test

}	// namespace hamon_unordered_map_test
