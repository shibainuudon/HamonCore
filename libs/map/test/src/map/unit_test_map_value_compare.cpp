/**
 *	@file	unit_test_map_value_compare.cpp
 *
 *	@brief	value_compare のテスト
 *
 *	class value_compare {
 *	protected:
 *		Compare comp;
 *		value_compare(Compare c) : comp(c) {}
 *
 *	public:
 *		bool operator()(const value_type& x, const value_type& y) const {
 *			return comp(x.first, y.first);
 *		}
 *	};
 */

#include <hamon/map/map.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_map_test
{

namespace value_compare_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test()
{
	return true;
}

#undef VERIFY

GTEST_TEST(MapTest, ValueCompareTest)
{
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace value_compare_test

}	// namespace hamon_map_test
