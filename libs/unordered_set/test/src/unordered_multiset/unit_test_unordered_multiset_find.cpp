/**
 *	@file	unit_test_unordered_multiset_find.cpp
 *
 *	@brief	find のテスト
 *
 *	constexpr iterator         find(const key_type& k);
 *	constexpr const_iterator   find(const key_type& k) const;
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multiset_test
{

namespace find_test
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
	using Iterator = typename Set::iterator;
	using ConstIterator = typename Set::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().find(hamon::declval<Key const&>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().find(hamon::declval<Key const&>())), ConstIterator>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().find(hamon::declval<Key const&>())), "");
	static_assert(!noexcept(hamon::declval<Set const&>().find(hamon::declval<Key const&>())), "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, FindTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace find_test

}	// namespace hamon_unordered_multiset_test
