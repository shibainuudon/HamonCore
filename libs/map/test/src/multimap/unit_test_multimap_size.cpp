/**
 *	@file	unit_test_multimap_size.cpp
 *
 *	@brief	size のテスト
 *
 *	size_type size() const noexcept;
 */

#include <hamon/map/multimap.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multimap_test
{

namespace size_test
{

#if !defined(HAMON_USE_STD_MULTIMAP)
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
MULTIMAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::multimap<Key, T>;
	using SizeType = typename Map::size_type;

	{
		Map v;
		static_assert(hamon::is_same<decltype(v.size()), SizeType>::value, "");
		static_assert(noexcept(v.size()), "");
		VERIFY(v.size() == 0);
	}
	{
		Map v
		{
			{Key{1}, T{10}},
			{Key{1}, T{20}},
			{Key{1}, T{30}},
			{Key{2}, T{40}},
			{Key{2}, T{50}},
			{Key{3}, T{60}},
		};
		VERIFY(v.size() == 6);
	}
	{
		Map const v;
		static_assert(hamon::is_same<decltype(v.size()), SizeType>::value, "");
		static_assert(noexcept(v.size()), "");
		VERIFY(v.size() == 0);
	}
	{
		Map const v
		{
			{Key{3}, T{10}},
			{Key{1}, T{20}},
			{Key{4}, T{30}},
			{Key{1}, T{40}},
			{Key{5}, T{50}},
			{Key{2}, T{60}},
		};
		VERIFY(v.size() == 6);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MultimapTest, SizeTest)
{
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

	// https://en.cppreference.com/w/cpp/container/multimap/size
	{
		hamon::multimap<int, char> nums {{1, 'a'}, {1, 'b'}, {2, 'c'}, {2, 'd'}};
		EXPECT_TRUE(nums.size() == 4);
	}
}

#undef MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTIMAP_TEST_CONSTEXPR

}	// namespace size_test

}	// namespace hamon_multimap_test
