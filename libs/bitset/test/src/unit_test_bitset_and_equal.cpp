﻿/**
 *	@file	unit_test_bitset_and_equal.cpp
 *
 *	@brief	operator&= のテスト
 *
 *	constexpr bitset& operator&=(const bitset& rhs) noexcept;
 */

#include <hamon/bitset.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bitset_test
{

namespace and_equal_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::bitset<0> b;
		auto const t = b &= hamon::bitset<0>();
		VERIFY(hamon::bitset<0>("") == b);
		VERIFY(0x00u == b.to_ulong());
		VERIFY(0u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<7> b("1111000");
		auto const t = b &= hamon::bitset<7>("0101010");
		VERIFY(hamon::bitset<7>("0101000") == b);
		VERIFY(0x28u == b.to_ulong());
		VERIFY(2u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<8> b("11110000");
		auto const t = b &= hamon::bitset<8>("01010101");
		VERIFY(hamon::bitset<8>("01010000") == b);
		VERIFY(0x50u == b.to_ulong());
		VERIFY(2u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<9> b("111100000");
		auto const t = b &= hamon::bitset<9>("010101010");
		VERIFY(hamon::bitset<9>("010100000") == b);
		VERIFY(0xA0u == b.to_ulong());
		VERIFY(2u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<15> b("111000011110000");
		auto const t = b &= hamon::bitset<15>("101010101010101");
		VERIFY(hamon::bitset<15>("101000001010000") == b);
		VERIFY(0x5050u == b.to_ulong());
		VERIFY(4u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<16> b("1111000011110000");
		auto const t = b &= hamon::bitset<16>("0101010101010101");
		VERIFY(hamon::bitset<16>("0101000001010000") == b);
		VERIFY(0x5050u == b.to_ulong());
		VERIFY(4u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<17> b("11110000111100001");
		auto const t = b &= hamon::bitset<17>("01010101010101010");
		VERIFY(hamon::bitset<17>("01010000010100000") == b);
		VERIFY(0xA0A0u == b.to_ulong());
		VERIFY(4u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<31> b("1111000011110000111100001111000");
		auto const t = b &= hamon::bitset<31>("0101010101010101010101010101010");
		VERIFY(hamon::bitset<31>("0101000001010000010100000101000") == b);
		VERIFY(0x28282828u == b.to_ullong());
		VERIFY(8u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<32> b("11110000111100001111000011110000");
		auto const t = b &= hamon::bitset<32>("01010101010101010101010101010101");
		VERIFY(hamon::bitset<32>("01010000010100000101000001010000") == b);
		VERIFY(0x50505050u == b.to_ullong());
		VERIFY(8u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<33> b("111100001111000011110000111100001");
		auto const t = b &= hamon::bitset<33>("010101010101010101010101010101010");
		VERIFY(hamon::bitset<33>("010100000101000001010000010100000") == b);
		VERIFY(0xA0A0A0A0u == b.to_ullong());
		VERIFY(8u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<63> b("111100001111000011110000111100001111000011110000111100001111000");
		auto const t = b &= hamon::bitset<63>("010101010101010101010101010101010101010101010101010101010101010");
		VERIFY(hamon::bitset<63>("010100000101000001010000010100000101000001010000010100000101000") == b);
		VERIFY(0x2828282828282828u == b.to_ullong());
		VERIFY(16u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<64> b("1111000011110000111100001111000011110000111100001111000011110000");
		auto const t = b &= hamon::bitset<64>("0101010101010101010101010101010101010101010101010101010101010101");
		VERIFY(hamon::bitset<64>("0101000001010000010100000101000001010000010100000101000001010000") == b);
		VERIFY(0x5050505050505050u == b.to_ullong());
		VERIFY(16u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<65> b("11110000111100001111000011110000111100001111000011110000111100001");
		auto const t = b &= hamon::bitset<65>("01010101010101010101010101010101010101010101010101010101010101010");
		VERIFY(hamon::bitset<65>("01010000010100000101000001010000010100000101000001010000010100000") == b);
		VERIFY(0xA0A0A0A0A0A0A0A0u == b.to_ullong());
		VERIFY(16u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<127> b("1111000011110000111100001111000011110000111100001111000011110000111100001111000011110000111100001111000011110000111100001111000");
		auto const t = b &= hamon::bitset<127>("0101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010");
		VERIFY(hamon::bitset<127>("0101000001010000010100000101000001010000010100000101000001010000010100000101000001010000010100000101000001010000010100000101000") == b);
		VERIFY(32u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<128> b("11110000111100001111000011110000111100001111000011110000111100001111000011110000111100001111000011110000111100001111000011110000");
		auto const t = b &= hamon::bitset<128>("01010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101");
		VERIFY(hamon::bitset<128>("01010000010100000101000001010000010100000101000001010000010100000101000001010000010100000101000001010000010100000101000001010000") == b);
		VERIFY(32u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<128> b("11110000111100001111000011110000111100001111000011110000111100001111000011110000111100001111000011110000111100001111000011110001");
		auto const t = b &= hamon::bitset<128>("01010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101");
		VERIFY(hamon::bitset<128>("01010000010100000101000001010000010100000101000001010000010100000101000001010000010100000101000001010000010100000101000001010001") == b);
		VERIFY(33u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<129> b("111100001111000011110000111100001111000011110000111100001111000011110000111100001111000011110000111100001111000011110000111100001");
		auto const t = b &= hamon::bitset<129>("010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010");
		VERIFY(hamon::bitset<129>("010100000101000001010000010100000101000001010000010100000101000001010000010100000101000001010000010100000101000001010000010100000") == b);
		VERIFY(32u == b.count());
		VERIFY(b == t);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(BitsetTest, AndEqualTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace and_equal_test

}	// namespace hamon_bitset_test