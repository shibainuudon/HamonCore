/**
 *	@file	unit_test_algorithm_ranges_copy_n.cpp
 *
 *	@brief	ranges::copy_n のテスト
 */

#include <hamon/algorithm/ranges/copy_n.hpp>
#include <hamon/algorithm/ranges/equal.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_copy_n_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template<
	template <typename> class in_wrapper,
	template <typename> class out_wrapper
>
inline HAMON_CXX14_CONSTEXPR bool
test01()
{
	namespace ranges = hamon::ranges;

	int x[] = { 1,2,3,4,5,6,7 };
	for (int i = -1; i <= 7; i++)
	{
		test_range<int, in_wrapper<int>> rx(x);
		int w[7]{};
		test_range<int, out_wrapper<int>> rw(w);
		ranges::copy_n(rx.begin(), i, rw.begin());
		if (i >= 0)
		{
			VERIFY(ranges::equal(x, x + i, w, w + i));
		}
	}
	return true;
}

inline HAMON_CXX14_CONSTEXPR bool
test02()
{
	namespace ranges = hamon::ranges;

	int x[] = { 1,2,3 };
	int y[2]{};
	auto res = ranges::copy_n(x, 2, y);
	VERIFY(res.in  == x + 2);
	VERIFY(res.out == y + 2);
	VERIFY(ranges::equal(x, x + 2, y, y + 2));

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesCopyNTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((
		test01<input_iterator_wrapper, output_iterator_wrapper>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((
		test01<random_access_iterator_wrapper, output_iterator_wrapper>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((
		test01<random_access_iterator_wrapper, random_access_iterator_wrapper>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace ranges_copy_n_test

}	// namespace hamon_algorithm_test
