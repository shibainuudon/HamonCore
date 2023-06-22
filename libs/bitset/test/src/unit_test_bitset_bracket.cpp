/**
 *	@file	unit_test_bitset_bracket.cpp
 *
 *	@brief	operator[]のテスト
 *
 *	constexpr bool operator[](size_t pos) const;
 *	constexpr bitset::reference operator[](size_t pos);
 */

#include <hamon/bitset.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bitset_test
{

namespace bracket_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		const hamon::bitset<8> b("00110110");
		VERIFY(b[0] == false);
		VERIFY(b[1] == true);
		VERIFY(b[7] == false);
	}
	{
		hamon::bitset<8> b;
		b[0] = true;
		b[2] = false;
		b[7] = true;
		VERIFY(b == hamon::bitset<8>("10000001"));
	}
	{
		const hamon::bitset<64> b("0101111101011111010111110101111101011111010111110101111101011111");
		VERIFY(b[0] == true);
		VERIFY(b[1] == true);
		VERIFY(b[7] == false);
		VERIFY(b[8] == true);
		VERIFY(b[31] == false);
		VERIFY(b[32] == true);
		VERIFY(b[61] == false);
		VERIFY(b[62] == true);
		VERIFY(b[63] == false);
		VERIFY(b[62] == true);
		VERIFY(b[63] == false);
	}
	{
		hamon::bitset<64> b;
		b[0] = true;
		b[2] = false;
		b[7] = true;
		b[8].flip();
		b[16] = b[7];
		b[17] = ~b[7];
		b[62] = false;
		b[63] = true;
		VERIFY(b == hamon::bitset<64>("1000000000000000000000000000000000000000000000010000000110000001"));

#if !defined(HAMON_USE_STD_BITSET)
		b[18] = b[9].flip();
		VERIFY(b == hamon::bitset<64>("1000000000000000000000000000000000000000000001010000001110000001"));
		b[19] = b[9].flip();
		VERIFY(b == hamon::bitset<64>("1000000000000000000000000000000000000000000001010000000110000001"));
#endif
	}

	return true;
}

#undef VERIFY

GTEST_TEST(BitsetTest, BracketTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace bracket_test

}	// namespace hamon_bitset_test
