/**
 *	@file	unit_test_utility_make_integer_range.cpp
 *
 *	@brief	make_integer_range のテスト
 */

#include <hamon/utility/make_integer_range.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>

namespace hamon_utility_test
{

namespace make_integer_range_test
{

GTEST_TEST(UtilityTest, MakeIntegerRangeTest)
{
	{
		using Seq = hamon::make_integer_range<int, 3, 7>;
		static_assert(hamon::is_same_v<Seq, hamon::integer_sequence<int, 3, 4, 5, 6>>, "");
	}
	{
		using Seq = hamon::make_integer_range<short, -2, 2>;
		static_assert(hamon::is_same_v<Seq, hamon::integer_sequence<short, -2, -1, 0, 1>>, "");
	}
}

}	// namespace make_integer_range_test

}	// namespace hamon_utility_test
