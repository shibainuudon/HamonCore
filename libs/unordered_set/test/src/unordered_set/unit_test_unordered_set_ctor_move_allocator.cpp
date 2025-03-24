/**
 *	@file	unit_test_unordered_set_ctor_move_allocator.cpp
 *
 *	@brief	ムーブとallocatorを引数に取るコンストラクタのテスト
 *
 *	constexpr unordered_set(unordered_set&&, const type_identity_t<Allocator>&);
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_set_test
{

namespace ctor_move_allocator_test
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

	static_assert( hamon::is_constructible<Set, Set&&, Allocator const&>::value, "");
#if !defined(HAMON_USE_STD_UNORDERED_SET)
	static_assert(!hamon::is_nothrow_constructible<Set, Set&&, Allocator const&>::value, "");
#endif
	static_assert( hamon::is_implicitly_constructible<Set, Set&&, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, Set&&, Allocator const&>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, CtorMoveAllocatorTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace ctor_move_allocator_test

}	// namespace hamon_unordered_set_test
