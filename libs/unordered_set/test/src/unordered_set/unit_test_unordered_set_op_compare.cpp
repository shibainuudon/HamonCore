/**
 *	@file	unit_test_unordered_set_op_compare.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<class Key, class T, class Hash, class Pred, class Alloc>
 *	constexpr bool operator==(
 *		const unordered_set<Key, T, Hash, Pred, Alloc>& a,
 *		const unordered_set<Key, T, Hash, Pred, Alloc>& b);
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_set_test
{

namespace op_compare_test
{

#if !defined(HAMON_USE_STD_UNORDERED_SET)
#define UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
UNORDERED_SET_TEST_CONSTEXPR bool test()
{
	using Set = hamon::unordered_set<Key>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>() == hamon::declval<Set const&>()), bool>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>() != hamon::declval<Set const&>()), bool>::value, "");
	static_assert(!noexcept(hamon::declval<Set const&>() == hamon::declval<Set const&>()), "");
	static_assert(!noexcept(hamon::declval<Set const&>() != hamon::declval<Set const&>()), "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, OpCompareTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace op_compare_test

}	// namespace hamon_unordered_set_test
