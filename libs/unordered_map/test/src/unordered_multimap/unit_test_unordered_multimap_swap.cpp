/**
 *	@file	unit_test_unordered_multimap_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	constexpr void swap(unordered_multimap&)
 *		noexcept(allocator_traits<Allocator>::is_always_equal::value &&
 *			is_nothrow_swappable_v<Hash> && is_nothrow_swappable_v<Pred>);
 *
 *	template<class Key, class T, class Hash, class Pred, class Alloc>
 *	constexpr void swap(
 *		unordered_multimap<Key, T, Hash, Pred, Alloc>& x,
 *		unordered_multimap<Key, T, Hash, Pred, Alloc>& y)
 *			noexcept(noexcept(x.swap(y)));
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multimap_test
{

namespace swap_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP)
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::unordered_multimap<Key, T>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().swap(hamon::declval<Map&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(swap(hamon::declval<Map&>(), hamon::declval<Map&>())), void>::value, "");
// TODO
//	static_assert(noexcept(hamon::declval<Map&>().swap(hamon::declval<Map&>())), "");
//	static_assert(noexcept(swap(hamon::declval<Map&>(), hamon::declval<Map&>())), "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, SwapTest)
{
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace swap_test

}	// namespace hamon_unordered_multimap_test
