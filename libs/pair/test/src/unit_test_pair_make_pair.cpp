/**
 *	@file	unit_test_pair_make_pair.cpp
 *
 *	@brief	make_pair のテスト
 * 
 *	template<class T1, class T2>
 *	constexpr pair<unwrap_ref_decay_t<T1>, unwrap_ref_decay_t<T2>>
 *	make_pair(T1&& x, T2&& y);
 */

#include <hamon/pair/make_pair.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/functional.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace make_pair_test
{

GTEST_TEST(PairTest, MakePairTest)
{
	{
		auto p = hamon::make_pair(1, 2.5f);
		static_assert(hamon::is_same<decltype(p), hamon::pair<int, float>>::value, "");
		EXPECT_EQ(1,    p.first);
		EXPECT_EQ(2.5f, p.second);
	}
	{
		long x = 2;
		double const y = 3;
		auto p = hamon::make_pair(x, y);
		static_assert(hamon::is_same<decltype(p), hamon::pair<long, double>>::value, "");
		EXPECT_EQ(2, p.first);
		EXPECT_EQ(3, p.second);
	}
	{
		int n = 1;
		auto p = hamon::make_pair(hamon::ref(n), "hello");
		static_assert(hamon::is_same<decltype(p), hamon::pair<int&, const char*>>::value, "");
		EXPECT_EQ(1, p.first);
		EXPECT_STREQ("hello", p.second);
	}
	{
		HAMON_CXX11_CONSTEXPR auto p = hamon::make_pair(1, 2.5f);
		static_assert(hamon::is_same<decltype(p), hamon::pair<int, float> const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1,    p.first);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2.5f, p.second);
	}
	{
		HAMON_CXX11_CONSTEXPR auto p = hamon::make_pair(3L, 4.0);
		static_assert(hamon::is_same<decltype(p), hamon::pair<long, double> const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3, p.first);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4, p.second);
	}
}

}	// namespace make_pair_test

}	// namespace hamon_pair_test
