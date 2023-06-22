/**
 *	@file	unit_test_bitset_shift_left_equal.cpp
 *
 *	@brief	operator<<= のテスト
 *
 *	constexpr bitset& operator<<=(size_t pos) noexcept;
 */

#include <hamon/bitset.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bitset_test
{

namespace shift_left_equal_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::bitset<0> b;
		auto t0 = b <<= 0;
		VERIFY(b == hamon::bitset<0>(""));
		VERIFY(b == t0);
		t0 = b <<= 1;
		VERIFY(b == hamon::bitset<0>(""));
		VERIFY(b == t0);
		t0 = b <<= 2;
		VERIFY(b == hamon::bitset<0>(""));
		VERIFY(0u == b.to_ulong());
		VERIFY(b == t0);
	}
	{
		hamon::bitset<8> b("01001011");
		auto t0 = b <<= 1;
		VERIFY(b == hamon::bitset<8>("10010110"));
		VERIFY(0x96u == b.to_ulong());
		VERIFY(b == t0);
		t0 = b <<= 2;
		VERIFY(b == hamon::bitset<8>("01011000"));
		VERIFY(0x58u == b.to_ulong());
		VERIFY(b == t0);
		t0 = b <<= 4;
		VERIFY(b == hamon::bitset<8>("10000000"));
		VERIFY(0x80u == b.to_ulong());
		VERIFY(b == t0);
		t0 = b <<= 9;
		VERIFY(b == hamon::bitset<8>("00000000"));
		VERIFY(0x00u == b.to_ulong());
		VERIFY(b == t0);
	}
	{
		hamon::bitset<31> b = ~hamon::bitset<31>{};
		b <<= 1;
		VERIFY(b == hamon::bitset<31>("1111111111111111111111111111110"));
		VERIFY(b.count() == 30u);
		b <<= 29;
		VERIFY(b == hamon::bitset<31>("1000000000000000000000000000000"));
		VERIFY(b.count() == 1u);
		b <<= 2;
		VERIFY(b == hamon::bitset<31>("0000000000000000000000000000000"));
		VERIFY(b.count() == 0u);
	}
	{
		hamon::bitset<64> b("0101111101011111010111110101111101011111010111110101111101011111");
		auto t0 = b <<= 0;
		VERIFY(b == hamon::bitset<64>("0101111101011111010111110101111101011111010111110101111101011111"));
		VERIFY(0x5F5F5F5F5F5F5F5Fu == b.to_ullong());
		VERIFY(b == t0);
		t0 = b <<= 1;
		VERIFY(b == hamon::bitset<64>("1011111010111110101111101011111010111110101111101011111010111110"));
		VERIFY(0xBEBEBEBEBEBEBEBEu == b.to_ullong());
		VERIFY(b == t0);
		t0 = b <<= 2;
		VERIFY(b == hamon::bitset<64>("1111101011111010111110101111101011111010111110101111101011111000"));
		VERIFY(0xFAFAFAFAFAFAFAF8u == b.to_ullong());
		VERIFY(b == t0);
		t0 = b <<= 3;
		VERIFY(b == hamon::bitset<64>("1101011111010111110101111101011111010111110101111101011111000000"));
		VERIFY(0xD7D7D7D7D7D7D7C0u == b.to_ullong());
		VERIFY(b == t0);
		t0 = b <<= 64;
		VERIFY(b == hamon::bitset<64>("0000000000000000000000000000000000000000000000000000000000000000"));
		VERIFY(b == t0);
		VERIFY(0x0000000000000000u == b.to_ullong());
	}
	{
		auto b = hamon::bitset<128>("1");
		auto const t1 = b <<= 0;
		auto const t2 = b <<= 1;
		auto const t3 = b <<= 2;
		auto const t4 = b <<= 3;
		auto const t5 = b <<= 120;
		VERIFY(t1 == hamon::bitset<128>("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"));
		VERIFY(t2 == hamon::bitset<128>("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010"));
		VERIFY(t3 == hamon::bitset<128>("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000"));
		VERIFY(t4 == hamon::bitset<128>("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001000000"));
		VERIFY(t5 == hamon::bitset<128>("01000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));
		VERIFY(b == t5);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(BitsetTest, ShiftLeftEqualTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace shift_left_equal_test

}	// namespace hamon_bitset_test
