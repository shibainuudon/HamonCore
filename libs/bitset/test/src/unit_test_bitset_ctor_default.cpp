/**
 *	@file	unit_test_bitset_ctor_default.cpp
 *
 *	@brief	デフォルトコンストラクタのテスト
 *
 *	constexpr bitset() noexcept;
 */

#include <hamon/bitset.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bitset_test
{

namespace ctor_default_test
{

template <hamon::size_t N>
void test()
{
	{
		HAMON_CXX11_CONSTEXPR hamon::bitset<N> b{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(N, b.size());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(b.all() == (N == 0));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.any());
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(b.none());
	}
}

GTEST_TEST(BitsetTest, CtorDefaultTest)
{
	test<0>();
	test<1>();
	test<2>();
	test<7>();
	test<8>();
	test<9>();
	test<15>();
	test<16>();
	test<17>();
	test<31>();
	test<32>();
	test<33>();
	test<63>();
	test<64>();
	test<65>();
	test<127>();
	test<128>();
	test<129>();
	test<255>();
	test<256>();
	test<257>();
}

}	// namespace ctor_default_test

}	// namespace hamon_bitset_test
