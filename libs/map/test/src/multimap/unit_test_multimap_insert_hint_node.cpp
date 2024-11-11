/**
 *	@file	unit_test_multimap_insert_hint_node.cpp
 *
 *	@brief	insert のテスト
 *
 *	iterator insert(const_iterator hint, node_type&& nh);
 */

#include <hamon/map/multimap.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multimap_test
{

namespace insert_hint_node_test
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

GTEST_TEST(MultimapTest, InsertHintNodeTest)
{
}

#undef MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTIMAP_TEST_CONSTEXPR

}	// namespace insert_hint_node_test

}	// namespace hamon_multimap_test
