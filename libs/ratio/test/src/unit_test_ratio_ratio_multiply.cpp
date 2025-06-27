/**
 *	@file	unit_test_ratio_ratio_multiply.cpp
 *
 *	@brief	ratio_multiply のテスト
 */

#include <hamon/ratio/ratio_multiply.hpp>
#include <hamon/ratio/ratio.hpp>
#include <gtest/gtest.h>

GTEST_TEST(RatioTest, RatioMultiplyTest)
{
	// 2/5 * 3/5 = 6/25
	{
		using r1 = hamon::ratio<2, 5>;
		using r2 = hamon::ratio<3, 5>;
		using r = hamon::ratio_multiply<r1, r2>;

		static_assert(r::num == 6, "");
		static_assert(r::den == 25, "");
	}

	// 1/3 * 3/2 = 1/2
	{
		using r1 = hamon::ratio<1, 3>;
		using r2 = hamon::ratio<3, 2>;
		using r = hamon::ratio_multiply<r1, r2>;

		static_assert(r::num == 1, "");
		static_assert(r::den == 2, "");
	}

	// -4/7 * 5/8 = -5/14
	{
		using r1 = hamon::ratio<-4, 7>;
		using r2 = hamon::ratio<5, 8>;
		using r = hamon::ratio_multiply<r1, r2>;

		static_assert(r::num == -5, "");
		static_assert(r::den == 14, "");
	}
}
