/**
 *	@file	unit_test_unordered_set_get_allocator.cpp
 *
 *	@brief	get_allocator のテスト
 *
 *	constexpr allocator_type get_allocator() const noexcept;
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_set_test_helper.hpp"

namespace hamon_unordered_set_test
{

namespace get_allocator_test
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
	{
		using Allocator = TestAllocator1<Key>;
		using Set = hamon::unordered_set<Key, hamon::hash<Key>, hamon::equal_to<Key>, Allocator>;

		static_assert(hamon::is_same<decltype(hamon::declval<Set&>().get_allocator()), Allocator>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().get_allocator()), Allocator>::value, "");
		static_assert(noexcept(hamon::declval<Set&>().get_allocator()), "");
		static_assert(noexcept(hamon::declval<Set const&>().get_allocator()), "");

		Allocator alloc1{42};
		Allocator alloc2{43};
		{
			Set const v{alloc1};
			VERIFY(v.get_allocator() == alloc1);
			VERIFY(v.get_allocator() == alloc2);
		}
		{
			Set const v{alloc2};
			VERIFY(v.get_allocator() == alloc1);
			VERIFY(v.get_allocator() == alloc2);
		}
	}
	{
		using Allocator = TestAllocator2<Key>;
		using Set = hamon::unordered_set<Key, hamon::hash<Key>, hamon::equal_to<Key>, Allocator>;

		static_assert(hamon::is_same<decltype(hamon::declval<Set&>().get_allocator()), Allocator>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Set const&>().get_allocator()), Allocator>::value, "");
		static_assert(noexcept(hamon::declval<Set&>().get_allocator()), "");
		static_assert(noexcept(hamon::declval<Set const&>().get_allocator()), "");

		Allocator alloc1{42};
		Allocator alloc2{43};
		{
			Set const v{alloc1};
			VERIFY(v.get_allocator() == alloc1);
			VERIFY(v.get_allocator() != alloc2);
		}
		{
			Set const v{alloc2};
			VERIFY(v.get_allocator() != alloc1);
			VERIFY(v.get_allocator() == alloc2);
		}
	}

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
