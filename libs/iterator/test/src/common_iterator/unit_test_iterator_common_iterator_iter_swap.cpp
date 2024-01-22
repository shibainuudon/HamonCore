/**
 *	@file	unit_test_iterator_common_iterator_iter_swap.cpp
 *
 *	@brief	iter_swap のテスト
 *
 *	template<indirectly_swappable<I> I2, class S2>
 *	friend constexpr void iter_swap(const common_iterator& x, const common_iterator<I2, S2>& y)
 *		noexcept(noexcept(ranges::iter_swap(declval<const I&>(), declval<const I2&>())));
 */

#include <hamon/iterator/common_iterator.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_iterator_test {
namespace common_iterator_test {
namespace iter_swap_test {

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test00()
{
	using I = int*;
	using S = int const*;
	using CI = hamon::common_iterator<I, S>;
	int a[] = {1, 2, 3};
	CI it1{I{&a[0]}};
	CI it2{I{&a[1]}};

	VERIFY(a[0] == 1);
	VERIFY(a[1] == 2);
	VERIFY(a[2] == 3);

	hamon::ranges::iter_swap(it1, it2);

	VERIFY(a[0] == 2);
	VERIFY(a[1] == 1);
	VERIFY(a[2] == 3);

	return true;
}

#undef VERIFY

GTEST_TEST(CommonIteratorTest, IterSwapTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test00());
}

}	// namespace iter_swap_test
}	// namespace common_iterator_test
}	// namespace hamon_iterator_test
