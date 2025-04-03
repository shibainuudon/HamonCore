﻿/**
 *	@file	unit_test_unordered_multiset_equal_range_heterogeneous.cpp
 *
 *	@brief	equal_range のテスト
 *
 *	template<class K>
*	constexpr pair<iterator, iterator>             equal_range(const K& k);
*	template<class K>
*	constexpr pair<const_iterator, const_iterator> equal_range(const K& k) const;
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multiset_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) || \
	defined(__cpp_lib_generic_unordered_lookup) && (__cpp_lib_generic_unordered_lookup >= 201811L)

namespace hamon_unordered_multiset_test
{

namespace equal_range_heterogeneous_test
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
	using Set = hamon::unordered_multiset<Key, decltype(hamon::ranges::hash), hamon::equal_to<>>;
	using Iterator = typename Set::iterator;
	using ConstIterator = typename Set::const_iterator;
#if defined(HAMON_USE_STD_UNORDERED_MULTISET)
	using Result1 = std::pair<Iterator, Iterator>;
	using Result2 = std::pair<ConstIterator, ConstIterator>;
#else
	using Result1 = hamon::pair<Iterator, Iterator>;
	using Result2 = hamon::pair<ConstIterator, ConstIterator>;
#endif

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().equal_range(hamon::declval<int>())), Result1>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().equal_range(hamon::declval<int>())), Result2>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().equal_range(hamon::declval<int>())), "");
	static_assert(!noexcept(hamon::declval<Set const&>().equal_range(hamon::declval<int>())), "");

	return true;
}

template <typename Set, typename K, typename = void>
struct is_equal_range_invocable
	: public hamon::false_type {};

template <typename Set, typename K>
struct is_equal_range_invocable<Set, K, hamon::void_t<decltype(hamon::declval<Set>().equal_range(hamon::declval<K>()))>>
	: public hamon::true_type {};

UNORDERED_MULTISET_TEST_CONSTEXPR bool test2()
{
	using Set1 = hamon::unordered_multiset<TransparentKey>;
	using Set2 = hamon::unordered_multiset<TransparentKey, decltype(hamon::ranges::hash)>;
	using Set3 = hamon::unordered_multiset<TransparentKey, hamon::hash<TransparentKey>, hamon::equal_to<>>;
	using Set4 = hamon::unordered_multiset<TransparentKey, decltype(hamon::ranges::hash), hamon::equal_to<>>;

	static_assert(!is_equal_range_invocable<Set1&, int>::value, "");
	static_assert(!is_equal_range_invocable<Set2&, int>::value, "");
	static_assert(!is_equal_range_invocable<Set3&, int>::value, "");
	static_assert( is_equal_range_invocable<Set4&, int>::value, "");

	static_assert(!is_equal_range_invocable<Set1 const&, int>::value, "");
	static_assert(!is_equal_range_invocable<Set2 const&, int>::value, "");
	static_assert(!is_equal_range_invocable<Set3 const&, int>::value, "");
	static_assert( is_equal_range_invocable<Set4 const&, int>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, EqualRangeHeterogeneousTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<float>()));

	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE(test2());
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace equal_range_heterogeneous_test

}	// namespace hamon_unordered_multiset_test

#endif
