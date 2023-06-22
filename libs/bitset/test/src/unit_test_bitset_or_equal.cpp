/**
 *	@file	unit_test_bitset_or_equal.cpp
 *
 *	@brief	operator|= のテスト
 *
 *	constexpr bitset& operator|=(const bitset& rhs) noexcept;
 */

#include <hamon/bitset.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bitset_test
{

namespace or_equal_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::bitset<0> b;
		auto const t = b |= hamon::bitset<0>();
		VERIFY(b == hamon::bitset<0>(""));
		VERIFY(0x00u == b.to_ulong());
		VERIFY(0u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<7> b("1111000");
		auto const t = b |= hamon::bitset<7>("0101010");
		VERIFY(b == hamon::bitset<7>("1111010"));
		VERIFY(0x7Au == b.to_ulong());
		VERIFY(5u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<8> b("11110000");
		auto const t = b |= hamon::bitset<8>("01010101");
		VERIFY(b == hamon::bitset<8>("11110101"));
		VERIFY(0xF5u == b.to_ulong());
		VERIFY(6u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<9> b("111100001");
		auto const t = b |= hamon::bitset<9>("010101010");
		VERIFY(b == hamon::bitset<9>("111101011"));
		VERIFY(0x1EBu == b.to_ulong());
		VERIFY(7u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<15> b("111100001111000");
		auto const t = b |= hamon::bitset<15>("010101010101010");
		VERIFY(b == hamon::bitset<15>("111101011111010"));
		VERIFY(0x7AFAu == b.to_ulong());
		VERIFY(11u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<16> b("1111000011110000");
		auto const t = b |= hamon::bitset<16>("0101010101010101");
		VERIFY(b == hamon::bitset<16>("1111010111110101"));
		VERIFY(0xF5F5u == b.to_ulong());
		VERIFY(12u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<17> b("11110000111100001");
		auto const t = b |= hamon::bitset<17>("01010101010101010");
		VERIFY(b == hamon::bitset<17>("11110101111101011"));
		VERIFY(0x1EBEBu == b.to_ulong());
		VERIFY(13u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<31> b("1111000011110000111100001111000");
		auto const t = b |= hamon::bitset<31>("0101010101010101010101010101010");
		VERIFY(b == hamon::bitset<31>("1111010111110101111101011111010"));
		VERIFY(0x7AFAFAFAu == b.to_ullong());
		VERIFY(23u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<32> b("11110000111100001111000011110000");
		auto const t = b |= hamon::bitset<32>("01010101010101010101010101010101");
		VERIFY(b == hamon::bitset<32>("11110101111101011111010111110101"));
		VERIFY(0xF5F5F5F5u == b.to_ullong());
		VERIFY(24u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<33> b("111100001111000011110000111100001");
		auto const t = b |= hamon::bitset<33>("010101010101010101010101010101010");
		VERIFY(b == hamon::bitset<33>("111101011111010111110101111101011"));
		VERIFY(0x1EBEBEBEBu == b.to_ullong());
		VERIFY(25u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<63> b("111000011110000111100001111000011110000111100001111000011110000");
		auto const t = b |= hamon::bitset<63>("101010101010101010101010101010101010101010101010101010101010101");
		VERIFY(b == hamon::bitset<63>("111010111110101111101011111010111110101111101011111010111110101"));
		VERIFY(0x75F5F5F5F5F5F5F5u == b.to_ullong());
		VERIFY(47u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<64> b("1111000011110000111100001111000011110000111100001111000011110000");
		auto const t = b |= hamon::bitset<64>("0101010101010101010101010101010101010101010101010101010101010101");
		VERIFY(b == hamon::bitset<64>("1111010111110101111101011111010111110101111101011111010111110101"));
		VERIFY(0xF5F5F5F5F5F5F5F5u == b.to_ullong());
		VERIFY(48u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<65> b("01111000011110000111100001111000011110000111100001111000011110000");
		auto const t = b |= hamon::bitset<65>("10101010101010101010101010101010101010101010101010101010101010101");
		VERIFY(b == hamon::bitset<65>("11111010111110101111101011111010111110101111101011111010111110101"));
		VERIFY(49u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<127> b("1110000111100001111000011110000111100001111000011110000111100001111000011110000111100001111000011110000111100001111000011110000");
		auto const t = b |= hamon::bitset<127>("1010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101");
		VERIFY(b == hamon::bitset<127>("1110101111101011111010111110101111101011111010111110101111101011111010111110101111101011111010111110101111101011111010111110101"));
		VERIFY(95u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<128> b("11110000111100001111000011110000111100001111000011110000111100001111000011110000111100001111000011110000111100001111000011110000");
		auto const t = b |= hamon::bitset<128>("01010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101");
		VERIFY(b == hamon::bitset<128>("11110101111101011111010111110101111101011111010111110101111101011111010111110101111101011111010111110101111101011111010111110101"));
		VERIFY(96u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<129> b("011110000111100001111000011110000111100001111000011110000111100001111000011110000111100001111000011110000111100001111000011110000");
		auto const t = b |= hamon::bitset<129>("101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101");
		VERIFY(b == hamon::bitset<129>("111110101111101011111010111110101111101011111010111110101111101011111010111110101111101011111010111110101111101011111010111110101"));
		VERIFY(97u == b.count());
		VERIFY(b == t);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(BitsetTest, OrEqualTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace or_equal_test

}	// namespace hamon_bitset_test
