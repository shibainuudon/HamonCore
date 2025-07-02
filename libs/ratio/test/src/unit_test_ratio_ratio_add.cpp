/**
 *	@file	unit_test_ratio_ratio_add.cpp
 *
 *	@brief	ratio_add のテスト
 */

#include <hamon/ratio/ratio_add.hpp>
#include <hamon/ratio/ratio.hpp>
#include <gtest/gtest.h>

GTEST_TEST(RatioTest, RatioAddTest)
{
	// 1/5 + 2/5 = 3/5
	{
		using r1 = hamon::ratio<1, 5>;
		using r2 = hamon::ratio<2, 5>;
		using r = hamon::ratio_add<r1, r2>;

		static_assert(r::num == 3, "");
		static_assert(r::den == 5, "");
	}

	// 1/3 + 1/6 = 1/2
	{
		using r1 = hamon::ratio<1, 3>;
		using r2 = hamon::ratio<1, 6>;
		using r = hamon::ratio_add<r1, r2>;

		static_assert(r::num == 1, "");
		static_assert(r::den == 2, "");
	}

	// 1/3 + -1/6 = 1/6
	{
		using r1 = hamon::ratio<1, 3>;
		using r2 = hamon::ratio<-1, 6>;
		using r = hamon::ratio_add<r1, r2>;

		static_assert(r::num == 1, "");
		static_assert(r::den == 6, "");
	}

	// 4/7 + 5/8 = 67/56
	{
		using r1 = hamon::ratio<4, 7>;
		using r2 = hamon::ratio<5, 8>;
		using r = hamon::ratio_add<r1, r2>;

		static_assert(r::num == 67, "");
		static_assert(r::den == 56, "");
	}

	// 56987354/467584654 + 544668/22145 = 127970191639601/5177331081415
	{
		using r1 = hamon::ratio<56987354, 467584654>;
		using r2 = hamon::ratio<544668, 22145>;
		using r = hamon::ratio_add<r1, r2>;

		static_assert(r::num == 127970191639601LL, "");
		static_assert(r::den == 5177331081415LL, "");
	}

	// 0/1 + 0/1 = 0/1
	{
		using r1 = hamon::ratio<0>;
		using r2 = hamon::ratio<0>;
		using r = hamon::ratio_add<r1, r2>;

		static_assert(r::num == 0, "");
		static_assert(r::den == 1, "");
	}

	// 1/1 + 0/1 = 1/1
	{
		using r1 = hamon::ratio<1>;
		using r2 = hamon::ratio<0>;
		using r = hamon::ratio_add<r1, r2>;

		static_assert(r::num == 1, "");
		static_assert(r::den == 1, "");
	}

	// 0/1 + 1/1 = 1/1
	{
		using r1 = hamon::ratio<0>;
		using r2 = hamon::ratio<1>;
		using r = hamon::ratio_add<r1, r2>;

		static_assert(r::num == 1, "");
		static_assert(r::den == 1, "");
	}
}
