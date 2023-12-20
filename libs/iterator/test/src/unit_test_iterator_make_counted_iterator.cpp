/**
 *	@file	unit_test_iterator_make_counted_iterator.cpp
 *
 *	@brief	make_counted_iterator のテスト
 */

#include <hamon/iterator/make_counted_iterator.hpp>
#include <hamon/concepts/same_as.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_iterator_test {
namespace make_counted_iterator_test {

HAMON_CXX14_CONSTEXPR bool test()
{
	int a[] = { 1, 2, 3, 4, 5, 6, 7 };
	auto it1 = hamon::make_counted_iterator(a, 3);
	static_assert(hamon::same_as_t<decltype(it1), hamon::counted_iterator<int*>>::value, "");
	hamon::counted_iterator<int*> it2(a, 3);
	return it1 == it2;
}

GTEST_TEST(IteratorTest, MakeCountedIteratorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace make_counted_iterator_test
}	// namespace hamon_iterator_test
