/**
 *	@file	unit_test_map_insert_or_assign.cpp
 *
 *	@brief	insert_or_assign のテスト
 *
 *	template<class M>
 *	pair<iterator, bool> insert_or_assign(const key_type& k, M&& obj);
 *	template<class M>
 *	pair<iterator, bool> insert_or_assign(key_type&& k, M&& obj);
 *	template<class K, class M>
 *	pair<iterator, bool> insert_or_assign(K&& k, M&& obj);
 *	template<class M>
 *	iterator insert_or_assign(const_iterator hint, const key_type& k, M&& obj);
 *	template<class M>
 *	iterator insert_or_assign(const_iterator hint, key_type&& k, M&& obj);
 *	template<class K, class M>
 *	iterator insert_or_assign(const_iterator hint, K&& k, M&& obj);
 */

#include <hamon/map/map.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_map_test
{

namespace insert_or_assign_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test()
{
	return true;
}

#undef VERIFY

GTEST_TEST(MapTest, InsertOrAssignTest)
{
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace insert_or_assign_test

}	// namespace hamon_map_test
