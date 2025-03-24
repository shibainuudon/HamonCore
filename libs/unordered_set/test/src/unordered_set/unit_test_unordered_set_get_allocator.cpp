/**
 *	@file	unit_test_unordered_set_get_allocator.cpp
 *
 *	@brief	get_allocator のテスト
 *
 *	constexpr allocator_type get_allocator() const noexcept;
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_set_test
{

namespace get_allocator_test
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
	using Allocator = typename Set::allocator_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().get_allocator()), Allocator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().get_allocator()), Allocator>::value, "");
	static_assert(noexcept(hamon::declval<Set&>().get_allocator()), "");
	static_assert(noexcept(hamon::declval<Set const&>().get_allocator()), "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, GetAllocatorTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace get_allocator_test

}	// namespace hamon_unordered_set_test
