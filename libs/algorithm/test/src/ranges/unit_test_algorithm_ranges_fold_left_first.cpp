/**
 *	@file	unit_test_algorithm_ranges_fold_left_first.cpp
 *
 *	@brief	ranges::fold_left_first のテスト
 */

#include <hamon/algorithm/ranges/fold_left_first.hpp>
#include <hamon/functional/ranges/plus.hpp>
#include <hamon/functional/ranges/multiplies.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/array.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_fold_left_first_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test01()
{
	namespace ranges = hamon::ranges;

	{
		int x[] = { 1,2,3,4,5 };
		{
			auto ret = ranges::fold_left_first(ranges::begin(x), ranges::end(x), ranges::plus{});
			VERIFY(ret.has_value());
			VERIFY(ret.value() == 15);
		}
		{
			auto ret = ranges::fold_left_first(ranges::begin(x), ranges::end(x), ranges::multiplies{});
			VERIFY(ret.has_value());
			VERIFY(ret.value() == 120);
		}
		{
			auto ret = ranges::fold_left_first(ranges::begin(x), ranges::begin(x), ranges::plus{});
			VERIFY(!ret.has_value());
		}
	}
	{
		hamon::array<int, 8> x = { 8,7,6,5,4,3,2,1 };
		VERIFY(ranges::fold_left_first(ranges::begin(x), ranges::end(x), ranges::plus{}) == 36);
		VERIFY(ranges::fold_left_first(ranges::begin(x), ranges::end(x), ranges::multiplies{}) == 40320);
	}
	return true;
}

template <template <typename> class RangeWrapper>
inline HAMON_CXX14_CONSTEXPR bool test02()
{
	namespace ranges = hamon::ranges;

	{
		int x[] = { 1,2,3,4,5 };
		RangeWrapper<int> rx(x);
		VERIFY(ranges::fold_left_first(rx, ranges::plus{}) == 15);
		VERIFY(ranges::fold_left_first(rx, ranges::multiplies{}) == 120);
	}
	{
		int x[] = { 8,7,6,5,4,3,2,1 };
		RangeWrapper<int> rx(x);
		VERIFY(ranges::fold_left_first(rx, ranges::plus{}) == 36);
		VERIFY(ranges::fold_left_first(rx, ranges::multiplies{}) == 40320);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(AlgorithmTest, RangesFoldLeftFirstTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<test_input_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<test_forward_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<test_bidirectional_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<test_random_access_range>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02<test_contiguous_range>());
}

}	// namespace ranges_fold_left_first_test

}	// namespace hamon_algorithm_test
