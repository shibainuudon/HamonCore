/**
 *	@file	unit_test_iterator_make_const_iterator.cpp
 *
 *	@brief	make_const_iterator のテスト
 */

#include <hamon/iterator/make_const_iterator.hpp>
#include <hamon/iterator/basic_const_iterator.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <vector>

namespace hamon_iterator_test
{

namespace make_const_iterator_test
{

GTEST_TEST(IteratorTest, MakeConstIteratorTest)
{
	std::vector<int> vec { 1, 2, 3, 4, 5 };
	{
		auto it = hamon::make_const_iterator(vec.begin());
		EXPECT_EQ(1, *it);
		static_assert(hamon::is_same<decltype(it), hamon::basic_const_iterator<typename std::vector<int>::iterator>>::value, "");
	}
	{
		auto it = hamon::make_const_iterator(vec.cbegin());
		EXPECT_EQ(1, *it);
		static_assert(hamon::is_same<decltype(it), typename std::vector<int>::const_iterator>::value, "");
	}
}

}	// namespace make_const_iterator_test

}	// namespace hamon_iterator_test
