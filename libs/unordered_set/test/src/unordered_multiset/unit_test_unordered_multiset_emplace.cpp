﻿/**
 *	@file	unit_test_unordered_multiset_emplace.cpp
 *
 *	@brief	emplace のテスト
 *
 *	template<class... Args> constexpr iterator emplace(Args&&... args);
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multiset_test
{

namespace emplace_test
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
UNORDERED_MULTISET_TEST_CONSTEXPR bool test1()
{
	using Set = hamon::unordered_multiset<Key>;
	using ValueType = typename Set::value_type;
	using Iterator = typename Set::iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().emplace(hamon::declval<ValueType&&>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().emplace(hamon::declval<ValueType const&>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().emplace(hamon::declval<ValueType&&>())), "");
	static_assert(!noexcept(hamon::declval<Set&>().emplace(hamon::declval<ValueType const&>())), "");

	return true;
}

struct S1
{
	int x;
	int y;

	constexpr S1(int i, int j) : x(i), y(j) {}

	S1(S1&&)                 = delete;
	S1(S1 const&)            = delete;
	S1& operator=(S1&&)      = delete;
	S1& operator=(S1 const&) = delete;
};

UNORDERED_MULTISET_TEST_CONSTEXPR bool test2()
{
	using Set = hamon::unordered_multiset<S1>;
	using Iterator = typename Set::iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().emplace(hamon::declval<int>(), hamon::declval<int>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().emplace(hamon::declval<int>(), hamon::declval<int>())), "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, EmplaceTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<float>()));

	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test2());
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace emplace_test

}	// namespace hamon_unordered_multiset_test
