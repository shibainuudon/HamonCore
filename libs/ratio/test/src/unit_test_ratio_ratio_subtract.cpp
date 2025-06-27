/**
 *	@file	unit_test_ratio_ratio_subtract.cpp
 *
 *	@brief	ratio_subtract のテスト
 */

#include <hamon/ratio/ratio_subtract.hpp>
#include <hamon/ratio/ratio.hpp>
#include <gtest/gtest.h>

GTEST_TEST(RatioTest, RatioSubtractTest)
{
	// 3/5 - 2/5 = 1/5
	{
		using r1 = hamon::ratio<3, 5>;
		using r2 = hamon::ratio<2, 5>;
		using r = hamon::ratio_subtract<r1, r2>;

		static_assert(r::num == 1, "");
		static_assert(r::den == 5, "");
	}

	// 4/7 - 5/8 = -3/56
	{
		using r1 = hamon::ratio<4, 7>;
		using r2 = hamon::ratio<5, 8>;
		using r = hamon::ratio_subtract<r1, r2>;

		static_assert(r::num == -3, "");
		static_assert(r::den == 56, "");
	}

	// 1/3 - -1/6 = 1/2
	{
		using r1 = hamon::ratio<1, 3>;
		using r2 = hamon::ratio<-1, 6>;
		using r = hamon::ratio_subtract<r1, r2>;

		static_assert(r::num == 1, "");
		static_assert(r::den == 2, "");
	}

	// -1/6 - 1/3 = -1/2
	{
		using r1 = hamon::ratio<-1, 6>;
		using r2 = hamon::ratio<1, 3>;
		using r = hamon::ratio_subtract<r1, r2>;

		static_assert(r::num == -1, "");
		static_assert(r::den == 2, "");
	}
}
