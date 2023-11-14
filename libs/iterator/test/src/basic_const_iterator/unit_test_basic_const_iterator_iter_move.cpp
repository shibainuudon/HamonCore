/**
 *	@file	unit_test_basic_const_iterator_iter_move.cpp
 *
 *	@brief	iter_move のテスト
 *
 *	friend constexpr rvalue-reference iter_move(const basic_const_iterator& i) noexcept(...);
 */

#include <hamon/iterator/basic_const_iterator.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test
{

namespace basic_const_iterator_test
{

namespace iter_move_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test01()
{
	using Iter = random_access_iterator_wrapper<int>;
	int a[3] = {3, 1, 4};
	hamon::basic_const_iterator<Iter> ci{Iter{a}};

	auto x = hamon::ranges::iter_move(ci);
	VERIFY(3 == x);

	return true;
}

#undef VERIFY

GTEST_TEST(BasicConstIteratorTest, IterMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace iter_move_test

}	// namespace basic_const_iterator_test

}	// namespace hamon_iterator_test
