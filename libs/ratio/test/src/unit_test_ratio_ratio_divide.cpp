/**
 *	@file	unit_test_ratio_ratio_divide.cpp
 *
 *	@brief	ratio_divide のテスト
 */

#include <hamon/ratio/ratio_divide.hpp>
#include <hamon/ratio/ratio.hpp>
#include <gtest/gtest.h>

GTEST_TEST(RatioTest, RatioDivideTest)
{
	// 2/5 ÷ 5/3 = 6/25
	{
		using r1 = hamon::ratio<2, 5>;
		using r2 = hamon::ratio<5, 3>;
		using r = hamon::ratio_divide<r1, r2>;

		static_assert(r::num == 6, "");
		static_assert(r::den == 25, "");
	}

	// -1/3 ÷ 2/3 = -1/2
	{
		using r1 = hamon::ratio<-1, 3>;
		using r2 = hamon::ratio<2, 3>;
		using r = hamon::ratio_divide<r1, r2>;

		static_assert(r::num == -1, "");
		static_assert(r::den == 2, "");
	}

	// 4/7 ÷ -5/8 = -32/35
	{
		using r1 = hamon::ratio<4, 7>;
		using r2 = hamon::ratio<5, -8>;
		using r = hamon::ratio_divide<r1, r2>;

		static_assert(r::num == -32, "");
		static_assert(r::den == 35, "");
	}

	// -1/2 ÷ -1/3 = 3/2
	{
		using r1 = hamon::ratio<-1, 2>;
		using r2 = hamon::ratio<-1, 3>;
		using r = hamon::ratio_divide<r1, r2>;

		static_assert(r::num == 3, "");
		static_assert(r::den == 2, "");
	}

	// 56987354/467584654 ÷ 544668/22145 = 630992477165/127339199162436
	{
		using r1 = hamon::ratio<56987354, 467584654>;
		using r2 = hamon::ratio<544668, 22145>;
		using r = hamon::ratio_divide<r1, r2>;

		static_assert(r::num == 630992477165LL, "");
		static_assert(r::den == 127339199162436LL, "");
	}
}
