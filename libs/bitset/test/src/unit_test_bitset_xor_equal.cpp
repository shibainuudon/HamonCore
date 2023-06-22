/**
 *	@file	unit_test_bitset_xor_equal.cpp
 *
 *	@brief	operator^= のテスト
 *
 *	constexpr bitset& operator^=(const bitset& rhs) noexcept;
 */

#include <hamon/bitset.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bitset_test
{

namespace xor_equal_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::bitset<0> b;
		auto const t = b ^= hamon::bitset<0>();
		VERIFY(b == hamon::bitset<0>(""));
		VERIFY(0x00u == b.to_ulong());
		VERIFY(0u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<8> b("11110000");
		auto const t = b ^= hamon::bitset<8>("01010101");
		VERIFY(b == hamon::bitset<8>("10100101"));
		VERIFY(0xA5u == b.to_ulong());
		VERIFY(4u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<16> b("1111000011110000");
		auto const t = b ^= hamon::bitset<16>("0101010101010101");
		VERIFY(b == hamon::bitset<16>("1010010110100101"));
		VERIFY(0xA5A5u == b.to_ulong());
		VERIFY(8u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<31> b = ~hamon::bitset<31>{};
		auto const t = b ^= hamon::bitset<31>("0000100110001111000011110000101");
		VERIFY(b == hamon::bitset<31>("1111011001110000111100001111010"));
		VERIFY(0x7B38787Au == b.to_ullong());
		VERIFY(18u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<32> b("11110000111100001111000011110000");
		auto const t = b ^= hamon::bitset<32>("01010101010101010101010101010101");
		VERIFY(b == hamon::bitset<32>("10100101101001011010010110100101"));
		VERIFY(0xA5A5A5A5u == b.to_ullong());
		VERIFY(16u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<64> b("1111000011110000111100001111000011110000111100001111000011110000");
		auto const t = b ^= hamon::bitset<64>("0101010101010101010101010101010101010101010101010101010101010101");
		VERIFY(b == hamon::bitset<64>("1010010110100101101001011010010110100101101001011010010110100101"));
		VERIFY(0xA5A5A5A5A5A5A5A5u == b.to_ullong());
		VERIFY(32u == b.count());
		VERIFY(b == t);
	}
	{
		hamon::bitset<128> b("11110000111100001111000011110000111100001111000011110000111100001111000011110000111100001111000011110000111100001111000011110000");
		auto const t = b ^= hamon::bitset<128>("00010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101");
		VERIFY(b == hamon::bitset<128>("11100101101001011010010110100101101001011010010110100101101001011010010110100101101001011010010110100101101001011010010110100101"));
		VERIFY(65u == b.count());
		VERIFY(b == t);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(BitsetTest, XorEqualTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());
}

}	// namespace xor_equal_test

}	// namespace hamon_bitset_test
