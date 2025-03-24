/**
 *	@file	unit_test_unordered_multiset_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	constexpr void swap(unordered_multiset&)
 *		noexcept(allocator_traits<Allocator>::is_always_equal::value &&
 *			is_nothrow_swappable_v<Hash> && is_nothrow_swappable_v<Pred>);
 *
 *	template<class Key, class T, class Hash, class Pred, class Alloc>
 *	constexpr void swap(
 *		unordered_multiset<Key, T, Hash, Pred, Alloc>& x,
 *		unordered_multiset<Key, T, Hash, Pred, Alloc>& y)
 *			noexcept(noexcept(x.swap(y)));
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multiset_test
{

namespace swap_test
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

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().swap(hamon::declval<Set&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(swap(hamon::declval<Set&>(), hamon::declval<Set&>())), void>::value, "");
// TODO
//	static_assert(noexcept(hamon::declval<Set&>().swap(hamon::declval<Set&>())), "");
//	static_assert(noexcept(swap(hamon::declval<Set&>(), hamon::declval<Set&>())), "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, SwapTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace swap_test

}	// namespace hamon_unordered_multiset_test
