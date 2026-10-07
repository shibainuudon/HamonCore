/**
 *	@file	unit_test_utility_make_index_range.cpp
 *
 *	@brief	make_index_range のテスト
 */

#include <hamon/utility/make_index_range.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace hamon_utility_test
{

namespace make_index_range_test
{

GTEST_TEST(UtilityTest, MakeIndexRangeTest)
{
	{
		using Seq = hamon::make_index_range<1, 5>;
		static_assert(hamon::is_same_v<Seq, hamon::index_sequence<1, 2, 3, 4>>, "");
	}
	{
		using Seq = hamon::make_index_range<3, 8>;
		static_assert(hamon::is_same_v<Seq, hamon::index_sequence<3, 4, 5, 6, 7>>, "");
	}
	{
		using Seq = hamon::make_index_range<5, 5>;
		static_assert(hamon::is_same_v<Seq, hamon::index_sequence<>>, "");
	}
}

}	// namespace make_index_range_test

}	// namespace hamon_utility_test
