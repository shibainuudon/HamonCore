/**
 *	@file	unit_test_set_op_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<class Key, class Compare, class Allocator>
 *	bool operator==(const set<Key, Compare, Allocator>& x,
 *		const set<Key, Compare, Allocator>& y);
 *
 *	template<class Key, class Compare, class Allocator>
 *	synth-three-way-result<Key> operator<=>(const set<Key, Compare, Allocator>& x,
 *		const set<Key, Compare, Allocator>& y);
 */

#include <hamon/set/set.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_set_test
{

namespace op_compare_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
SET_TEST_CONSTEXPR bool test()
{
	return true;
}

#undef VERIFY

GTEST_TEST(SetTest, OpCompareTest)
{
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace op_compare_test

}	// namespace hamon_set_test
