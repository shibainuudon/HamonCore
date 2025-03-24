/**
 *	@file	unit_test_unordered_map_get_allocator.cpp
 *
 *	@brief	get_allocator のテスト
 *
 *	constexpr allocator_type get_allocator() const noexcept;
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/functional/hash.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_map_test_helper.hpp"

namespace hamon_unordered_map_test
{

namespace get_allocator_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test()
{
	using ValueType = typename hamon::unordered_map<Key, T>::value_type;

	{
		using Allocator = TestAllocator1<ValueType>;
		using Map = hamon::unordered_map<Key, T, hamon::hash<Key>, hamon::equal_to<Key>, Allocator>;

		static_assert(hamon::is_same<decltype(hamon::declval<Map&>().get_allocator()), Allocator>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().get_allocator()), Allocator>::value, "");
		static_assert(noexcept(hamon::declval<Map&>().get_allocator()), "");
		static_assert(noexcept(hamon::declval<Map const&>().get_allocator()), "");

		Allocator alloc1{42};
		Allocator alloc2{43};
		{
			Map const v{alloc1};
			VERIFY(v.get_allocator() == alloc1);
			VERIFY(v.get_allocator() == alloc2);
		}
		{
			Map const v{alloc2};
			VERIFY(v.get_allocator() == alloc1);
			VERIFY(v.get_allocator() == alloc2);
		}
	}
	{
		using Allocator = TestAllocator2<ValueType>;
		using Map = hamon::unordered_map<Key, T, hamon::hash<Key>, hamon::equal_to<Key>, Allocator>;

		static_assert(hamon::is_same<decltype(hamon::declval<Map&>().get_allocator()), Allocator>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().get_allocator()), Allocator>::value, "");
		static_assert(noexcept(hamon::declval<Map&>().get_allocator()), "");
		static_assert(noexcept(hamon::declval<Map const&>().get_allocator()), "");

		Allocator alloc1{42};
		Allocator alloc2{43};
		{
			Map const v{alloc1};
			VERIFY(v.get_allocator() == alloc1);
			VERIFY(v.get_allocator() != alloc2);
		}
		{
			Map const v{alloc2};
			VERIFY(v.get_allocator() != alloc1);
			VERIFY(v.get_allocator() == alloc2);
		}
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, GetAllocatorTest)
{
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

#undef UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MAP_TEST_CONSTEXPR

}	// namespace get_allocator_test

}	// namespace hamon_unordered_map_test
