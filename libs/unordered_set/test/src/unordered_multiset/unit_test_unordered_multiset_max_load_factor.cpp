/**
 *	@file	unit_test_unordered_multiset_max_load_factor.cpp
 *
 *	@brief	max_load_factor のテスト
 *
 *	constexpr float max_load_factor() const noexcept;
 *	constexpr void max_load_factor(float z);
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_multiset_test
{

namespace max_load_factor_test
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

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().max_load_factor()), float>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().max_load_factor()), float>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().max_load_factor(hamon::declval<float>())), void>::value, "");
	static_assert( noexcept(hamon::declval<Set&>().max_load_factor()), "");
	static_assert( noexcept(hamon::declval<Set const&>().max_load_factor()), "");
#if !defined(HAMON_USE_STD_UNORDERED_MULTISET)
	static_assert(!noexcept(hamon::declval<Set&>().max_load_factor(hamon::declval<float>())), "");
#endif

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, MaxLoadFactorTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace max_load_factor_test

}	// namespace hamon_unordered_multiset_test
