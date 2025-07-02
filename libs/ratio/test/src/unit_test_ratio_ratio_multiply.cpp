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

	// 56987354/467584654 * 544668/22145 = 15519594064236/5177331081415
	{
		using r1 = hamon::ratio<56987354, 467584654>;
		using r2 = hamon::ratio<544668, 22145>;
		using r = hamon::ratio_multiply<r1, r2>;

		static_assert(r::num == 15519594064236LL, "");
		static_assert(r::den == 5177331081415LL, "");
	}

	{
		using r1 = hamon::ratio<0>;
		using r2 = hamon::ratio<0>;
		using r = hamon::ratio_multiply<r1, r2>;

		static_assert(r::num == 0, "");
		static_assert(r::den == 1, "");
	}
	{
		using r1 = hamon::ratio<1>;
		using r2 = hamon::ratio<0>;
		using r = hamon::ratio_multiply<r1, r2>;

		static_assert(r::num == 0, "");
		static_assert(r::den == 1, "");
	}
	{
		using r1 = hamon::ratio<0>;
		using r2 = hamon::ratio<1>;
		using r = hamon::ratio_multiply<r1, r2>;

		static_assert(r::num == 0, "");
		static_assert(r::den == 1, "");
	}
}
