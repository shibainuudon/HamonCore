/**
 *	@file	unit_test_ratio_ratio.cpp
 *
 *	@brief	ratio のテスト
 */

#include <hamon/ratio/ratio.hpp>
#include <gtest/gtest.h>

GTEST_TEST(RatioTest, RatioTest)
{
	{
		using r = hamon::ratio<1, 5>;
		static_assert(r::num == 1, "");
		static_assert(r::den == 5, "");
	}
	{
		using r = hamon::ratio<3, 12>;
		static_assert(r::num == 1, "");
		static_assert(r::den == 4, "");
	}
	{
		using r = hamon::ratio<-12, 15>;
		static_assert(r::num == -4, "");
		static_assert(r::den == 5, "");
	}
	{
		using r = hamon::ratio<16, -12>;
		static_assert(r::num == -4, "");
		static_assert(r::den == 3, "");
	}
	{
		using r = hamon::ratio<-16, -14>;
		static_assert(r::num == 8, "");
		static_assert(r::den == 7, "");
	}
}
