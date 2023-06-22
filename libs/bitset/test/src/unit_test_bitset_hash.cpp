/**
 *	@file	unit_test_bitset_hash.cpp
 *
 *	@brief	hash関数のテスト
 *
 *	template<size_t N> struct hash<bitset<N>>;
 */

#include <hamon/bitset.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(BitsetTest, HashTest)
{
	{
		using Bitset = hamon::bitset<0>;

		HAMON_CXX11_CONSTEXPR Bitset b1;
		HAMON_CXX11_CONSTEXPR Bitset b2 = ~Bitset{};

#if !defined(HAMON_USE_STD_BITSET)
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b1.hash(), b2.hash());
#endif

		using Hash = std::hash<Bitset>;
		Hash h;
		EXPECT_EQ(h(b1), h(b2));
	}
	{
		using Bitset = hamon::bitset<1>;

		HAMON_CXX11_CONSTEXPR Bitset b1;
		HAMON_CXX11_CONSTEXPR Bitset b2(0);
		HAMON_CXX11_CONSTEXPR Bitset b3(1);
		HAMON_CXX11_CONSTEXPR Bitset b4 = ~Bitset{};

#if !defined(HAMON_USE_STD_BITSET)
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b1.hash(), b2.hash());
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(b1.hash(), b3.hash());
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(b1.hash(), b4.hash());
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(b2.hash(), b3.hash());
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(b2.hash(), b4.hash());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b3.hash(), b4.hash());
#endif

		using Hash = std::hash<Bitset>;
		Hash h;
		EXPECT_EQ(h(b1), h(b2));
		EXPECT_NE(h(b1), h(b3));
		EXPECT_NE(h(b1), h(b4));
		EXPECT_NE(h(b2), h(b3));
		EXPECT_NE(h(b2), h(b4));
		EXPECT_EQ(h(b3), h(b4));
	}
	{
		using Bitset = hamon::bitset<31>;

		HAMON_CXX11_CONSTEXPR Bitset b1;
		HAMON_CXX11_CONSTEXPR Bitset b2(0x7fffffff);
		HAMON_CXX11_CONSTEXPR Bitset b3(0);
		HAMON_CXX11_CONSTEXPR Bitset b4 = ~Bitset{};

#if !defined(HAMON_USE_STD_BITSET)
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(b1.hash(), b2.hash());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b1.hash(), b3.hash());
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(b1.hash(), b4.hash());
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(b2.hash(), b3.hash());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b2.hash(), b4.hash());
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(b3.hash(), b4.hash());
#endif

		using Hash = std::hash<Bitset>;
		Hash h;
		EXPECT_NE(h(b1), h(b2));
		EXPECT_EQ(h(b1), h(b3));
		EXPECT_NE(h(b1), h(b4));
		EXPECT_NE(h(b2), h(b3));
		EXPECT_EQ(h(b2), h(b4));
		EXPECT_NE(h(b3), h(b4));
	}
	{
		using Bitset = hamon::bitset<64>;

		HAMON_CXX11_CONSTEXPR Bitset b1;
		HAMON_CXX11_CONSTEXPR Bitset b2("1000000000000000000000000000000000000000000000000000000000000000");
		HAMON_CXX11_CONSTEXPR Bitset b3("0000000000000000000000000000000000000000000000000000000000000001");
		HAMON_CXX11_CONSTEXPR Bitset b4("0000000000000000000000000000000000000000000000000000000000000000");

#if !defined(HAMON_USE_STD_BITSET)
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(b1.hash(), b2.hash());
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(b1.hash(), b3.hash());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b1.hash(), b4.hash());
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(b2.hash(), b3.hash());
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(b2.hash(), b4.hash());
		HAMON_CXX11_CONSTEXPR_EXPECT_NE(b3.hash(), b4.hash());
#endif

		using Hash = std::hash<Bitset>;
		Hash h;
		EXPECT_NE(h(b1), h(b2));
		EXPECT_NE(h(b1), h(b3));
		EXPECT_EQ(h(b1), h(b4));
		EXPECT_NE(h(b2), h(b3));
		EXPECT_NE(h(b2), h(b4));
		EXPECT_NE(h(b3), h(b4));
	}
}
