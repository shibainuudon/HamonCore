/**
 *	@file	unit_test_map_try_emplace.cpp
 *
 *	@brief	try_emplace のテスト
 *
 *	template<class... Args>
 *	pair<iterator, bool> try_emplace(const key_type& k, Args&&... args);
 *	template<class... Args>
 *	pair<iterator, bool> try_emplace(key_type&& k, Args&&... args);
 *	template<class K, class... Args>
 *	pair<iterator, bool> try_emplace(K&& k, Args&&... args);
 *	template<class... Args>
 *	iterator try_emplace(const_iterator hint, const key_type& k, Args&&... args);
 *	template<class... Args>
 *	iterator try_emplace(const_iterator hint, key_type&& k, Args&&... args);
 *	template<class K, class... Args>
 *	iterator try_emplace(const_iterator hint, K&& k, Args&&... args);
 */

#include <hamon/map/map.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_map_test
{

namespace try_emplace_test
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

GTEST_TEST(MapTest, TryEmplaceTest)
{
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace try_emplace_test

}	// namespace hamon_map_test
