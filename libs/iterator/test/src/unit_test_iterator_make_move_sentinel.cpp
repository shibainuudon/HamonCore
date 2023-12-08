/**
 *	@file	unit_test_iterator_make_move_sentinel.cpp
 *
 *	@brief	make_move_sentinel のテスト
 */

#include <hamon/iterator/make_move_sentinel.hpp>
#include <hamon/concepts/same_as.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_iterator_test
{

namespace make_move_sentinel_test
{

inline HAMON_CXX14_CONSTEXPR bool make_move_sentinel_test()
{
	char s[] = "123";
	auto sent1 = hamon::make_move_sentinel(s);
	static_assert(hamon::same_as_t<decltype(sent1), hamon::move_sentinel<char*>>::value, "");
	hamon::move_sentinel<char*> sent2(s);
	return sent1.base() == sent2.base();
}

GTEST_TEST(IteratorTest, MakeMoveSentinelTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(make_move_sentinel_test());
}

}	// namespace make_move_sentinel_test

}	// namespace hamon_iterator_test
