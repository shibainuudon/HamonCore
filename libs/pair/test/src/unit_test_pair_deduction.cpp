/**
 *	@file	unit_test_pair_deduction.cpp
 *
 *	@brief	deduction guides のテスト
 * 
 *	template<class T1, class T2>
 *	pair(T1, T2) -> pair<T1, T2>;
 */

#include <hamon/pair.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace deduction_test
{

GTEST_TEST(PairTest, DeductionTest)
{
#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
	{
		hamon::pair p{5, 6u};
		static_assert(hamon::is_same<decltype(p), hamon::pair<int, unsigned int>>::value, "");
		EXPECT_EQ(p.first, 5);
		EXPECT_EQ(p.second, 6u);
	}
	{
		float const f = 0.5f;
		int const i = 2;
		hamon::pair p{f, i};
		static_assert(hamon::is_same<decltype(p), hamon::pair<float, int>>::value, "");
		EXPECT_EQ(p.first, 0.5f);
		EXPECT_EQ(p.second, 2);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::pair p{5, 6u};
		static_assert(hamon::is_same<decltype(p), hamon::pair<int, unsigned int> const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(p.first, 5);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(p.second, 6u);
	}
	{
		HAMON_CXX11_CONSTEXPR float const f = 0.5f;
		HAMON_CXX11_CONSTEXPR int const i = 2;
		HAMON_CXX11_CONSTEXPR hamon::pair p{f, i};
		static_assert(hamon::is_same<decltype(p), hamon::pair<float, int> const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(p.first, 0.5f);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(p.second, 2);
	}
#endif
}

}	// namespace deduction_test

}	// namespace hamon_pair_test
