/**
 *	@file	unit_test_unordered_multiset_merge.cpp
 *
 *	@brief	merge のテスト
 *
 *	template<class H2, class P2>
 *	constexpr void merge(unordered_multiset<Key, T, H2, P2, Allocator>& source);
 *
 *	template<class H2, class P2>
 *	constexpr void merge(unordered_multiset<Key, T, H2, P2, Allocator>&& source);
 *
 *	template<class H2, class P2>
 *	constexpr void merge(unordered_set<Key, T, H2, P2, Allocator>& source);
 *
 *	template<class H2, class P2>
 *	constexpr void merge(unordered_set<Key, T, H2, P2, Allocator>&& source);
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) || \
	(defined(__cpp_lib_node_extract) && (__cpp_lib_node_extract >= 201606L))

namespace hamon_unordered_multiset_test
{

namespace merge_test
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

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().merge(hamon::declval<Set&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().merge(hamon::declval<Set&&>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().merge(hamon::declval<Set&>())), "");
	static_assert(!noexcept(hamon::declval<Set&>().merge(hamon::declval<Set&&>())), "");

	return true;
}

template <typename Key>
UNORDERED_MULTISET_TEST_CONSTEXPR bool test2()
{
	using Set1 = hamon::unordered_multiset<Key>;
	using Set2 = hamon::unordered_multiset<Key, decltype(hamon::ranges::hash), hamon::equal_to<>>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set1&>().merge(hamon::declval<Set2&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set1&>().merge(hamon::declval<Set2&&>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Set1&>().merge(hamon::declval<Set2&>())), "");
	static_assert(!noexcept(hamon::declval<Set1&>().merge(hamon::declval<Set2&&>())), "");

	return true;
}

template <typename Key>
UNORDERED_MULTISET_TEST_CONSTEXPR bool test3()
{
	using Set1 = hamon::unordered_multiset<Key>;
	using Set2 = hamon::unordered_set<Key, decltype(hamon::ranges::hash), hamon::equal_to<>>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set1&>().merge(hamon::declval<Set2&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set1&>().merge(hamon::declval<Set2&&>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Set1&>().merge(hamon::declval<Set2&>())), "");
	static_assert(!noexcept(hamon::declval<Set1&>().merge(hamon::declval<Set2&&>())), "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, MergeTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<float>()));

	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test2<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test2<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test2<float>()));

	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test3<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test3<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test3<float>()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace merge_test

}	// namespace hamon_unordered_multiset_test

#endif
