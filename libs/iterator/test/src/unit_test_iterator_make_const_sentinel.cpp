/**
 *	@file	unit_test_iterator_make_const_sentinel.cpp
 *
 *	@brief	make_const_sentinel のテスト
 */

#include <hamon/iterator/make_const_sentinel.hpp>
#include <hamon/iterator/basic_const_iterator.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>

namespace hamon_iterator_test
{

namespace make_const_sentinel_test
{

GTEST_TEST(IteratorTest, MakeConstSentinelTest)
{
	hamon::vector<int> vec { 1, 2, 3, 4, 5 };
	{
		auto it = hamon::make_const_sentinel(vec.end());
		static_assert(hamon::is_same<decltype(it), hamon::basic_const_iterator<typename hamon::vector<int>::iterator>>::value, "");
	}
	{
		auto it = hamon::make_const_sentinel(vec.cend());
		static_assert(hamon::is_same<decltype(it), typename hamon::vector<int>::const_iterator>::value, "");
	}
}

}	// namespace make_const_sentinel_test

}	// namespace hamon_iterator_test
