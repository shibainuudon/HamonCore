/**
 *	@file	unit_test_functional_hash_combine.cpp
 *
 *	@brief	hash_combine のテスト
 */

#include <hamon/functional/hash_combine.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "get_random_value.hpp"

namespace hamon_functional_test
{

namespace hash_combine_test
{

template <typename T = hamon::size_t,
	hamon::enable_if_t<sizeof(T) == 4>* = nullptr>
void test()
{
	/*HAMON_CXX11_CONSTEXPR_*/EXPECT_EQ(2654435769u, hamon::hash_combine(0, 0));
	/*HAMON_CXX11_CONSTEXPR_*/EXPECT_EQ(2654435770u, hamon::hash_combine(0, 1));
	/*HAMON_CXX11_CONSTEXPR_*/EXPECT_EQ(2654435771u, hamon::hash_combine(0, 2));
	/*HAMON_CXX11_CONSTEXPR_*/EXPECT_EQ(2654435832u, hamon::hash_combine(1, 0));
	/*HAMON_CXX11_CONSTEXPR_*/EXPECT_EQ(2654435835u, hamon::hash_combine(1, 1));
	/*HAMON_CXX11_CONSTEXPR_*/EXPECT_EQ(2654435834u, hamon::hash_combine(1, 2));
	/*HAMON_CXX11_CONSTEXPR_*/EXPECT_EQ(2654435869u, hamon::hash_combine(0, 100));
	/*HAMON_CXX11_CONSTEXPR_*/EXPECT_EQ(2654442166u, hamon::hash_combine(100, 0));
	/*HAMON_CXX11_CONSTEXPR_*/EXPECT_EQ(2654442322u, hamon::hash_combine(100, 100));
}

template <typename T = hamon::size_t,
	hamon::enable_if_t<sizeof(T) == 8>* = nullptr>
void test()
{
	/*HAMON_CXX11_CONSTEXPR_*/EXPECT_EQ(11400714819323198485u, hamon::hash_combine(0, 0));
	/*HAMON_CXX11_CONSTEXPR_*/EXPECT_EQ(11400714819323198486u, hamon::hash_combine(0, 1));
	/*HAMON_CXX11_CONSTEXPR_*/EXPECT_EQ(11400714819323198487u, hamon::hash_combine(0, 2));
	/*HAMON_CXX11_CONSTEXPR_*/EXPECT_EQ(11400714819323202580u, hamon::hash_combine(1, 0));
	/*HAMON_CXX11_CONSTEXPR_*/EXPECT_EQ(11400714819323202583u, hamon::hash_combine(1, 1));
	/*HAMON_CXX11_CONSTEXPR_*/EXPECT_EQ(11400714819323202582u, hamon::hash_combine(1, 2));
	/*HAMON_CXX11_CONSTEXPR_*/EXPECT_EQ(11400714819323198585u, hamon::hash_combine(0, 100));
	/*HAMON_CXX11_CONSTEXPR_*/EXPECT_EQ(11400714819323608191u, hamon::hash_combine(100, 0));
	/*HAMON_CXX11_CONSTEXPR_*/EXPECT_EQ(11400714819323608091u, hamon::hash_combine(100, 100));
}

GTEST_TEST(FunctionalTest, HashCombineTest)
{
	test();

	hamon::size_t h = 0;
	for (int i = 0; i < 100; ++i)
	{
		hamon::size_t h2 = hamon::hash_combine(h, 1);
		EXPECT_NE(h, h2);
		h = h2;
	}
}

}	// namespace hash_combine_test

}	// namespace hamon_functional_test
