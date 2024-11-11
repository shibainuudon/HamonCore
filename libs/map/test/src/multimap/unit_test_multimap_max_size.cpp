/**
 *	@file	unit_test_multimap_max_size.cpp
 *
 *	@brief	max_size のテスト
 *
 *	size_type max_size() const noexcept;
 */

#include <hamon/map/multimap.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_multimap_test
{

namespace max_size_test
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
		static_assert(hamon::is_same<decltype(v.max_size()), SizeType>::value, "");
		static_assert(noexcept(v.max_size()), "");
		VERIFY(v.max_size() > 0);
	}
	{
		Map const v;
		static_assert(hamon::is_same<decltype(v.max_size()), SizeType>::value, "");
		static_assert(noexcept(v.max_size()), "");
		VERIFY(v.max_size() > 0);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MultimapTest, MaxSizeTest)
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
}

#undef MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MULTIMAP_TEST_CONSTEXPR

}	// namespace max_size_test

}	// namespace hamon_multimap_test
