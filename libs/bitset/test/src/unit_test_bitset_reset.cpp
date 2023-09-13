/**
 *	@file	unit_test_bitset_reset.cpp
 *
 *	@brief	reset関数のテスト
 *
 *	constexpr bitset& reset() noexcept;
 *	constexpr bitset& reset(size_t pos);
 */

#include <hamon/bitset.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bitset_test
{

namespace reset_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::bitset<0> b;
		b.reset();
		VERIFY(b == hamon::bitset<0>(""));
		VERIFY(0x00u == b.to_ulong());
		VERIFY(0u == b.count());
	}
	{
		hamon::bitset<1> b(1);
		b.reset();
		VERIFY(b == hamon::bitset<1>("0"));
		VERIFY(0x00u == b.to_ulong());
		VERIFY(0u == b.count());
	}
	{
		hamon::bitset<1> b(1);
		b.reset(0);
		VERIFY(b == hamon::bitset<1>("0"));
		VERIFY(0x00u == b.to_ulong());
		VERIFY(0u == b.count());
	}
	{
		hamon::bitset<7> b = ~hamon::bitset<7>{};
		auto const t0 = b.reset();
		VERIFY(b == hamon::bitset<7>("0000000"));
		VERIFY(0x00u == b.to_ulong());
		VERIFY(0u == b.count());
		VERIFY(b == t0);
	}
	{
		hamon::bitset<7> b = ~hamon::bitset<7>{};

		auto const t0 = b.reset(1);
		VERIFY(b == hamon::bitset<7>("1111101"));
		VERIFY(0x7Du == b.to_ulong());
		VERIFY(6u == b.count());
		VERIFY(b == t0);

		auto const t1 = b.reset(6);
		VERIFY(b == hamon::bitset<7>("0111101"));
		VERIFY(0x3Du == b.to_ulong());
		VERIFY(5u == b.count());
		VERIFY(b == t1);

		b.reset(1);
		VERIFY(b == hamon::bitset<7>("0111101"));
		VERIFY(0x3Du == b.to_ulong());
		VERIFY(5u == b.count());
	}
	{
		hamon::bitset<8> b("11111111");
		auto const t0 = b.reset();
		VERIFY(b == hamon::bitset<8>("00000000"));
		VERIFY(0x00u == b.to_ulong());
		VERIFY(0u == b.count());
		VERIFY(b == t0);
	}
	{
		hamon::bitset<8> b("11111111");
		auto const t1 = b.reset(0);
		VERIFY(b == hamon::bitset<8>("11111110"));
		VERIFY(0xFEu == b.to_ulong());
		VERIFY(b == t1);
		b.reset(4);
		VERIFY(b == hamon::bitset<8>("11101110"));
		VERIFY(0xEEu == b.to_ulong());
	}
	{
		hamon::bitset<13> b("1111111111111");
		auto const t1 = b.reset(0);
		VERIFY(b == hamon::bitset<13>("1111111111110"));
		VERIFY(0x1FFEu == b.to_ulong());
		VERIFY(b == t1);
		b.reset(4);
		VERIFY(b == hamon::bitset<13>("1111111101110"));
		VERIFY(0x1FEEu == b.to_ulong());
	}
	{
		hamon::bitset<63> b = ~hamon::bitset<63>{};

		auto const t0 = b.reset(0);
		VERIFY(b == hamon::bitset<63>("111111111111111111111111111111111111111111111111111111111111110"));
		VERIFY(62u == b.count());
		VERIFY(b == t0);

		auto const t1 = b.reset(62);
		VERIFY(b == hamon::bitset<63>("011111111111111111111111111111111111111111111111111111111111110"));
		VERIFY(61u == b.count());
		VERIFY(b == t1);

		auto const t2 = b.reset();
		VERIFY(b == hamon::bitset<63>("000000000000000000000000000000000000000000000000000000000000000"));
		VERIFY(0u == b.count());
		VERIFY(b == t2);
	}
	{
		hamon::bitset<128> b("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
		b.reset();
		VERIFY(b == hamon::bitset<128>("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"));
		VERIFY(0x00u == b.to_ullong());
		VERIFY(0u == b.count());
	}
	{
		hamon::bitset<128> b("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
		b.reset(0);
		VERIFY(b == hamon::bitset<128>("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111110"));
		b.reset(1);
		VERIFY(b == hamon::bitset<128>("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111100"));
		b.reset(3);
		VERIFY(b == hamon::bitset<128>("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111110100"));
		b.reset(31);
		VERIFY(b == hamon::bitset<128>("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111101111111111111111111111111110100"));
		b.reset(32);
		VERIFY(b == hamon::bitset<128>("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111001111111111111111111111111110100"));
		b.reset(33);
		VERIFY(b == hamon::bitset<128>("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111110001111111111111111111111111110100"));
		b.reset(63);
		VERIFY(b == hamon::bitset<128>("11111111111111111111111111111111111111111111111111111111111111110111111111111111111111111111110001111111111111111111111111110100"));
		b.reset(64);
		VERIFY(b == hamon::bitset<128>("11111111111111111111111111111111111111111111111111111111111111100111111111111111111111111111110001111111111111111111111111110100"));
		b.reset(65);
		VERIFY(b == hamon::bitset<128>("11111111111111111111111111111111111111111111111111111111111111000111111111111111111111111111110001111111111111111111111111110100"));
		b.reset(127);
		VERIFY(b == hamon::bitset<128>("01111111111111111111111111111111111111111111111111111111111111000111111111111111111111111111110001111111111111111111111111110100"));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(BitsetTest, ResetTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::bitset<0> b;
		EXPECT_THROW(b.reset(0), hamon::out_of_range);
	}
	{
		hamon::bitset<1> b(1);
		EXPECT_NO_THROW(b.reset(0));
		EXPECT_THROW(b.reset(1), hamon::out_of_range);
	}
	{
		hamon::bitset<7> b = ~hamon::bitset<7>{};
		EXPECT_NO_THROW(b.reset(6));
		EXPECT_THROW(b.reset(7), hamon::out_of_range);
	}
	{
		hamon::bitset<8> b("11111111");
		EXPECT_NO_THROW(b.reset(7));
		EXPECT_THROW(b.reset(8), hamon::out_of_range);
	}
	{
		hamon::bitset<13> b("1111111111111");
		EXPECT_NO_THROW(b.reset(12));
		EXPECT_THROW(b.reset(13), hamon::out_of_range);
	}
	{
		hamon::bitset<63> b = ~hamon::bitset<63>{1};
		EXPECT_NO_THROW(b.reset(62));
		EXPECT_THROW(b.reset(63), hamon::out_of_range);
	}
	{
		hamon::bitset<128> b("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
		EXPECT_NO_THROW(b.reset(127));
		EXPECT_THROW(b.reset(128), hamon::out_of_range);
	}
#endif
}

}	// namespace reset_test

}	// namespace hamon_bitset_test
