﻿/**
 *	@file	unit_test_multiset_merge.cpp
 *
 *	@brief	merge のテスト
 *
 *	template<class C2>
 *	void merge(multiset<Key, C2, Allocator>& source);
 *	template<class C2>
 *	void merge(multiset<Key, C2, Allocator>&& source);
 *	template<class C2>
 *	void merge(set<Key, C2, Allocator>& source);
 *	template<class C2>
 *	void merge(set<Key, C2, Allocator>&& source);
 */

#include <hamon/set/multiset.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multiset_test
{

namespace merge_test
{

#if !defined(HAMON_USE_STD_MULTISET)
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTISET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
MULTISET_TEST_CONSTEXPR bool test()
{
	return true;
}

#undef VERIFY

GTEST_TEST(MultisetTest, MergeTest)
{
}

#undef MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTISET_TEST_CONSTEXPR

}	// namespace merge_test

}	// namespace hamon_multiset_test