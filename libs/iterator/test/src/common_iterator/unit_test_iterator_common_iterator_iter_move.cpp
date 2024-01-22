/**
 *	@file	unit_test_iterator_common_iterator_iter_move.cpp
 *
 *	@brief	iter_move のテスト
 *
 *	friend constexpr decltype(auto)
 *	iter_move(const common_iterator& i)
 *		noexcept(noexcept(ranges::iter_move(declval<const I&>())))
 *		requires input_iterator<I>;
 */

#include <hamon/iterator/common_iterator.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_iterator_test {
namespace common_iterator_test {
namespace iter_move_test {

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using I = int*;
	using S = int const*;
	using CI = hamon::common_iterator<I, S>;
	int n = 42;
	CI it{&n};
	VERIFY(hamon::ranges::iter_move(it) == 42);

	return true;
}

#undef VERIFY

GTEST_TEST(CommonIteratorTest, IterMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iter_move_test
}	// namespace common_iterator_test
}	// namespace hamon_iterator_test
