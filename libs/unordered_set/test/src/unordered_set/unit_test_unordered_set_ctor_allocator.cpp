/**
 *	@file	unit_test_unordered_set_ctor_allocator.cpp
 *
 *	@brief	アロケータを引数に取るコンストラクタのテスト
 *
 *	constexpr explicit unordered_set(const Allocator&);
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/is_trivially_constructible.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_set_test
{

namespace ctor_allocator_test
{

#if !defined(HAMON_USE_STD_UNORDERED_SET) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
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

	static_assert( hamon::is_constructible<Set, Allocator const&>::value, "");
	static_assert(!hamon::is_nothrow_constructible<Set, Allocator const&>::value, "");
	static_assert(!hamon::is_implicitly_constructible<Set, Allocator const&>::value, "");
	static_assert(!hamon::is_trivially_constructible<Set, Allocator const&>::value, "");

	{
		Allocator alloc;
		Set v{alloc};
		VERIFY(v.empty());
		VERIFY(v.size() == 0);
		VERIFY(v.begin() == v.end());
		VERIFY(v.max_load_factor() == 1.0);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v.get_allocator() == alloc);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, CtorAllocatorTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace ctor_allocator_test

}	// namespace hamon_unordered_set_test
