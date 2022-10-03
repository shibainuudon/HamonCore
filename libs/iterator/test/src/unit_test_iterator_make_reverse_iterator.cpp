/**
 *	@file	unit_test_iterator_make_reverse_iterator.cpp
 *
 *	@brief	make_reverse_iterator のテスト
 */

#include <hamon/iterator/make_reverse_iterator.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_iterator_test
{

namespace make_reverse_iterator_test
{

inline HAMON_CXX14_CONSTEXPR bool make_reverse_iterator_test()
{
	char s[] = "123";
	auto it1 = hamon::make_reverse_iterator(s);
	hamon::reverse_iterator<char*> it2(s);
	return it1 == it2;
}

GTEST_TEST(IteratorTest, MakeReverseIteratorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(make_reverse_iterator_test());
}

}	// namespace make_reverse_iterator_test

}	// namespace hamon_iterator_test
