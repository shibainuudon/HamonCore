/**
 *	@file	unit_test_bitset_shift_right_equal.cpp
 *
 *	@brief	operator>>= のテスト
 *
 *	constexpr bitset& operator>>=(size_t pos) noexcept;
 */

#include <hamon/bitset.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bitset_test
{

namespace shift_right_equal_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::bitset<0> b;
		auto t0 = b >>= 0;
		VERIFY(b == hamon::bitset<0>(""));
		VERIFY(0x00u == b.to_ulong());
		VERIFY(b == t0);
		t0 = b >>= 1;
		VERIFY(b == hamon::bitset<0>(""));
		VERIFY(0x00u == b.to_ulong());
		VERIFY(b == t0);
		t0 = b >>= 2;
		VERIFY(b == hamon::bitset<0>(""));
		VERIFY(0x00u == b.to_ulong());
		VERIFY(b == t0);
	}
	{
		hamon::bitset<8> b("01001011");
		auto t0 = b >>= 1;
		VERIFY(b == hamon::bitset<8>("00100101"));
		VERIFY(0x25u == b.to_ulong());
		VERIFY(b == t0);
		t0 = b >>= 2;
		VERIFY(b == hamon::bitset<8>("00001001"));
		VERIFY(0x09u == b.to_ulong());
		VERIFY(b == t0);
		t0 = b >>= 4;
		VERIFY(b == hamon::bitset<8>("00000000"));
		VERIFY(0x00u == b.to_ulong());
		VERIFY(b == t0);
		t0 = b >>= 9;
		VERIFY(b == hamon::bitset<8>("00000000"));
		VERIFY(0x00u == b.to_ulong());
		VERIFY(b == t0);
	}
	{
		hamon::bitset<31> b = ~hamon::bitset<31>{};
		b >>= 1;
		VERIFY(b == hamon::bitset<31>("0111111111111111111111111111111"));
		VERIFY(b.count() == 30u);
		b >>= 29;
		VERIFY(b == hamon::bitset<31>("0000000000000000000000000000001"));
		VERIFY(b.count() == 1u);
		b >>= 2;
		VERIFY(b == hamon::bitset<31>("0000000000000000000000000000000"));
		VERIFY(b.count() == 0u);
	}
	{
		hamon::bitset<64> b("0101111101011111010111110101111101011111010111110101111101011111");
		auto t0 = b >>= 0;
		VERIFY(b == hamon::bitset<64>("0101111101011111010111110101111101011111010111110101111101011111"));
		VERIFY(0x5F5F5F5F5F5F5F5Fu == b.to_ullong());
		VERIFY(b == t0);
		t0 = b >>= 1;
		VERIFY(b == hamon::bitset<64>("0010111110101111101011111010111110101111101011111010111110101111"));
		VERIFY(0x2FAFAFAFAFAFAFAFu == b.to_ullong());
		VERIFY(b == t0);
		t0 = b >>= 2;
		VERIFY(b == hamon::bitset<64>("0000101111101011111010111110101111101011111010111110101111101011"));
		VERIFY(0x0BEBEBEBEBEBEBEBu == b.to_ullong());
		VERIFY(b == t0);
		t0 = b >>= 3;
		VERIFY(b == hamon::bitset<64>("0000000101111101011111010111110101111101011111010111110101111101"));
		VERIFY(0x017D7D7D7D7D7D7Du == b.to_ullong());
		VERIFY(b == t0);
		t0 = b >>= 64;
		VERIFY(b == hamon::bitset<64>("0000000000000000000000000000000000000000000000000000000000000000"));
		VERIFY(0x0000000000000000u == b.to_ullong());
		VERIFY(b == t0);
	}
	{
		auto b = hamon::bitset<128>("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
		auto const t1 = b >>= 0;
		auto const t2 = b >>= 1;
		auto const t3 = b >>= 2;
		auto const t4 = b >>= 3;
		auto const t5 = b >>= 120;
		VERIFY(t1 == hamon::bitset<128>("10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));
		VERIFY(t2 == hamon::bitset<128>("01000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));
		VERIFY(t3 == hamon::bitset<128>("00010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));
		VERIFY(t4 == hamon::bitset<128>("00000010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));
		VERIFY(t5 == hamon::bitset<128>("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010"));
		VERIFY(b == t5);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(BitsetTest, ShiftRightEqualTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace shift_right_equal_test

}	// namespace hamon_bitset_test
