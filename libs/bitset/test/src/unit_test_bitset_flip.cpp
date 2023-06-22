/**
 *	@file	unit_test_bitset_flip.cpp
 *
 *	@brief	flip関数のテスト
 *
 *	constexpr bitset& flip() noexcept;
 *	constexpr bitset& flip(size_t pos);
 */

#include <hamon/bitset.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bitset_test
{

namespace flip_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::bitset<0> b;
		b.flip();
		VERIFY(b == hamon::bitset<0>{});
		VERIFY(0x00u == b.to_ulong());
		VERIFY(0u == b.count());
	}
	{
		hamon::bitset<8> b("10110001");
		auto const t0 = b.flip();
		VERIFY(b == hamon::bitset<8>("01001110"));
		VERIFY(0x4Eu == b.to_ulong());
		VERIFY(4u == b.count());
		VERIFY(b == t0);
	}
	{
		hamon::bitset<8> b("10110001");
		auto const t1 = b.flip(0);
		VERIFY(b == hamon::bitset<8>("10110000"));
		VERIFY(0xB0u == b.to_ulong());
		VERIFY(3u == b.count());
		VERIFY(b == t1);
		b.flip(1);
		VERIFY(b == hamon::bitset<8>("10110010"));
		VERIFY(0xB2u == b.to_ulong());
		VERIFY(4u == b.count());
		b.flip(7);
		VERIFY(b == hamon::bitset<8>("00110010"));
		VERIFY(0x32u == b.to_ulong());
		VERIFY(3u == b.count());
	}
	{
		hamon::bitset<33> b;
		auto t1 = b.flip(0);
		VERIFY(b == hamon::bitset<33>("000000000000000000000000000000001"));
		VERIFY(0x0001u == b.to_ulong());
		VERIFY(1u == b.count());
		VERIFY(b == t1);
		t1 = b.flip(3);
		VERIFY(b == hamon::bitset<33>("000000000000000000000000000001001"));
		VERIFY(0x0009u == b.to_ulong());
		VERIFY(2u == b.count());
		VERIFY(b == t1);
		t1 = b.flip(32);
		VERIFY(b == hamon::bitset<33>("100000000000000000000000000001001"));
		VERIFY(0x100000009u == b.to_ullong());
		VERIFY(3u == b.count());
		VERIFY(b == t1);
		t1 = b.flip(0);
		VERIFY(b == hamon::bitset<33>("100000000000000000000000000001000"));
		VERIFY(0x100000008u == b.to_ullong());
		VERIFY(2u == b.count());
		VERIFY(b == t1);
	}
	{
		hamon::bitset<128> b("01011111010111110101111101011111010111110101111101011111010111110101111101011111010111110101111101011111010111110101111101011111");
		VERIFY(96u == b.count());
		b.flip();
		VERIFY(b == hamon::bitset<128>("10100000101000001010000010100000101000001010000010100000101000001010000010100000101000001010000010100000101000001010000010100000"));
		VERIFY(32u == b.count());
	}
	{
		hamon::bitset<127> b{};
		VERIFY(0u == b.count());
		b.flip();
		VERIFY(127u == b.count());
		b.flip();
		VERIFY(0u == b.count());
	}
	{
		hamon::bitset<128> b("01011111010111110101111101011111010111110101111101011111010111110101111101011111010111110101111101011111010111110101111101011111");
		VERIFY(96u == b.count());
		b.flip(0);
		VERIFY(b == hamon::bitset<128>("01011111010111110101111101011111010111110101111101011111010111110101111101011111010111110101111101011111010111110101111101011110"));
		VERIFY(95u == b.count());
		b.flip(1);
		VERIFY(b == hamon::bitset<128>("01011111010111110101111101011111010111110101111101011111010111110101111101011111010111110101111101011111010111110101111101011100"));
		VERIFY(94u == b.count());
		b.flip(3);
		VERIFY(b == hamon::bitset<128>("01011111010111110101111101011111010111110101111101011111010111110101111101011111010111110101111101011111010111110101111101010100"));
		VERIFY(93u == b.count());
		b.flip(31);
		VERIFY(b == hamon::bitset<128>("01011111010111110101111101011111010111110101111101011111010111110101111101011111010111110101111111011111010111110101111101010100"));
		VERIFY(94u == b.count());
		b.flip(32);
		VERIFY(b == hamon::bitset<128>("01011111010111110101111101011111010111110101111101011111010111110101111101011111010111110101111011011111010111110101111101010100"));
		VERIFY(93u == b.count());
		b.flip(33);
		VERIFY(b == hamon::bitset<128>("01011111010111110101111101011111010111110101111101011111010111110101111101011111010111110101110011011111010111110101111101010100"));
		VERIFY(92u == b.count());
		b.flip(63);
		VERIFY(b == hamon::bitset<128>("01011111010111110101111101011111010111110101111101011111010111111101111101011111010111110101110011011111010111110101111101010100"));
		VERIFY(93u == b.count());
		b.flip(64);
		VERIFY(b == hamon::bitset<128>("01011111010111110101111101011111010111110101111101011111010111101101111101011111010111110101110011011111010111110101111101010100"));
		VERIFY(92u == b.count());
		b.flip(65);
		VERIFY(b == hamon::bitset<128>("01011111010111110101111101011111010111110101111101011111010111001101111101011111010111110101110011011111010111110101111101010100"));
		VERIFY(91u == b.count());
		b.flip(127);
		VERIFY(b == hamon::bitset<128>("11011111010111110101111101011111010111110101111101011111010111001101111101011111010111110101110011011111010111110101111101010100"));
		VERIFY(92u == b.count());
	}
	{
		hamon::bitset<129> b{};
		VERIFY(0u == b.count());
		b.flip();
		VERIFY(129u == b.count());
		b.flip();
		VERIFY(0u == b.count());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(BitsetTest, FlipTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::bitset<0> b;
		EXPECT_THROW(b.flip(0), std::out_of_range);
	}
	{
		hamon::bitset<7> b;
		EXPECT_NO_THROW(b.flip(6));
		EXPECT_THROW(b.flip(7), std::out_of_range);
	}
	{
		hamon::bitset<8> b;
		EXPECT_NO_THROW(b.flip(7));
		EXPECT_THROW(b.flip(8), std::out_of_range);
	}
	{
		hamon::bitset<31> b;
		EXPECT_NO_THROW(b.flip(30));
		EXPECT_THROW(b.flip(31), std::out_of_range);
	}
	{
		hamon::bitset<32> b;
		EXPECT_NO_THROW(b.flip(31));
		EXPECT_THROW(b.flip(32), std::out_of_range);
	}
	{
		hamon::bitset<33> b;
		EXPECT_NO_THROW(b.flip(32));
		EXPECT_THROW(b.flip(33), std::out_of_range);
	}
	{
		hamon::bitset<128> b;
		EXPECT_NO_THROW(b.flip(127));
		EXPECT_THROW(b.flip(128), std::out_of_range);
	}
#endif
}

}	// namespace flip_test

}	// namespace hamon_bitset_test
