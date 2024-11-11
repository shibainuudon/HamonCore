/**
 *	@file	unit_test_multimap_op_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<class Key, class T, class Compare, class Allocator>
 *	bool operator==(const multimap<Key, T, Compare, Allocator>& x,
 *		const multimap<Key, T, Compare, Allocator>& y);
 *
 *	template<class Key, class T, class Compare, class Allocator>
 *	synth-three-way-result<pair<const Key, T>>
 *	operator<=>(const multimap<Key, T, Compare, Allocator>& x,
 *		const multimap<Key, T, Compare, Allocator>& y);
 */

#include <hamon/map/multimap.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multimap_test
{

namespace op_compare_test
{

#if !defined(HAMON_USE_STD_MULTIMAP)
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
MULTIMAP_TEST_CONSTEXPR bool test()
{
	return true;
}

#undef VERIFY

GTEST_TEST(MultimapTest, OpCompareTest)
{
}

#undef MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTIMAP_TEST_CONSTEXPR

}	// namespace op_compare_test

}	// namespace hamon_multimap_test
