﻿/**
 *	@file	unit_test_unordered_multiset_bucket.cpp
 *
 *	@brief	bucket のテスト
 *
 *	constexpr size_type bucket(const key_type& k) const;
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multiset_test
{

namespace bucket_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
UNORDERED_MULTISET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::unordered_multiset<Key>;
	using SizeType = typename Set::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().bucket(hamon::declval<Key const&>())), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().bucket(hamon::declval<Key const&>())), SizeType>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
	static_assert(!noexcept(hamon::declval<Set&>().bucket(hamon::declval<Key const&>())), "");
	static_assert(!noexcept(hamon::declval<Set const&>().bucket(hamon::declval<Key const&>())), "");
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, BucketTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace bucket_test

}	// namespace hamon_unordered_multiset_test
