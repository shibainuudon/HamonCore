/**
 *	@file	unit_test_bitset_set.cpp
 *
 *	@brief	set関数のテスト
 *
 *	constexpr bitset& set() noexcept;
 *	constexpr bitset& set(size_t pos, bool val = true);
 */

#include <hamon/bitset.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bitset_test
{

namespace set_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test()
{
	{
		hamon::bitset<0> b;
		b.set();
		VERIFY(b == hamon::bitset<0>(""));
		VERIFY(0x00u == b.to_ulong());
		VERIFY(0u == b.count());
	}
	{
		hamon::bitset<1> b{};
		b.set();
		VERIFY(b == hamon::bitset<1>("1"));
		VERIFY(0x01u == b.to_ulong());
		VERIFY(1u == b.count());
	}
	{
		hamon::bitset<1> b{};
		b.set(0);
		VERIFY(b == hamon::bitset<1>("1"));
		VERIFY(0x01u == b.to_ulong());
		VERIFY(1u == b.count());
	}
	{
		hamon::bitset<7> b{};

		auto const t0 = b.set(2);
		VERIFY(b == hamon::bitset<7>("0000100"));
		VERIFY(0x04u == b.to_ulong());
		VERIFY(1u == b.count());
		VERIFY(b == t0);

		auto const t1 = b.set(6);
		VERIFY(b == hamon::bitset<7>("1000100"));
		VERIFY(0x44u == b.to_ulong());
		VERIFY(2u == b.count());
		VERIFY(b == t1);

		b.set(2);
		VERIFY(b == hamon::bitset<7>("1000100"));
		VERIFY(0x44u == b.to_ulong());
		VERIFY(2u == b.count());

		b.set(6, false);
		VERIFY(b == hamon::bitset<7>("0000100"));
		VERIFY(0x04u == b.to_ulong());
		VERIFY(1u == b.count());

		auto const t2 = b.set();
		VERIFY(b == hamon::bitset<7>("1111111"));
		VERIFY(0x7Fu == b.to_ulong());
		VERIFY(7u == b.count());
		VERIFY(b == t2);
	}
	{
		hamon::bitset<8> b;
		auto const t0 = b.set();
		VERIFY(b == hamon::bitset<8>("11111111"));
		VERIFY(0xFFu == b.to_ulong());
		VERIFY(8u == b.count());
		VERIFY(b == t0);
	}
	{
		hamon::bitset<8> b;
		auto const t1 = b.set(0);
		VERIFY(b == hamon::bitset<8>("00000001"));
		VERIFY(0x01u == b.to_ulong());
		VERIFY(1u == b.count());
		VERIFY(b == t1);
		b.set(2);
		VERIFY(b == hamon::bitset<8>("00000101"));
		VERIFY(0x05u == b.to_ulong());
		VERIFY(2u == b.count());
		b.set(6);
		VERIFY(b == hamon::bitset<8>("01000101"));
		VERIFY(0x45u == b.to_ulong());
		VERIFY(3u == b.count());
		b.set(2, false);
		VERIFY(b == hamon::bitset<8>("01000001"));
		VERIFY(0x41u == b.to_ulong());
		VERIFY(2u == b.count());
	}
	{
		hamon::bitset<63> b{};

		auto const t0 = b.set(0);
		VERIFY(b == hamon::bitset<63>("000000000000000000000000000000000000000000000000000000000000001"));
		VERIFY(1u == b.count());
		VERIFY(b == t0);

		auto const t1 = b.set(62);
		VERIFY(b == hamon::bitset<63>("100000000000000000000000000000000000000000000000000000000000001"));
		VERIFY(2u == b.count());
		VERIFY(b == t1);

		b.set(0);
		VERIFY(b == hamon::bitset<63>("100000000000000000000000000000000000000000000000000000000000001"));
		VERIFY(2u == b.count());

		b.set(62, false);
		VERIFY(b == hamon::bitset<63>("000000000000000000000000000000000000000000000000000000000000001"));
		VERIFY(1u == b.count());

		auto const t2 = b.set();
		VERIFY(b == hamon::bitset<63>("111111111111111111111111111111111111111111111111111111111111111"));
		VERIFY(63u == b.count());
		VERIFY(b == t2);
	}
	{
		hamon::bitset<127> b;
		b.set();
		VERIFY(b == hamon::bitset<127>("1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"));
		VERIFY(127u == b.count());
	}
	{
		hamon::bitset<128> b;
		b.set();
		VERIFY(b == hamon::bitset<128>("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"));
		VERIFY(128u == b.count());
	}
	{
		hamon::bitset<129> b;
		b.set();
		VERIFY(b == hamon::bitset<129>("111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"));
		VERIFY(129u == b.count());
	}
	{
		hamon::bitset<128> b;
		b.set(0);
		VERIFY(b == hamon::bitset<128>("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001"));
		VERIFY(0x01u == b.to_ullong());
		b.set(1);
		VERIFY(b == hamon::bitset<128>("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011"));
		VERIFY(0x03u == b.to_ullong());
		b.set(3);
		VERIFY(b == hamon::bitset<128>("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001011"));
		VERIFY(0x0Bu == b.to_ullong());
		b.set(31);
		VERIFY(b == hamon::bitset<128>("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010000000000000000000000000001011"));
		VERIFY(0x8000000Bu == b.to_ullong());
		b.set(32);
		VERIFY(b == hamon::bitset<128>("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000110000000000000000000000000001011"));
		VERIFY(0x18000000Bu == b.to_ullong());
		b.set(33);
		VERIFY(b == hamon::bitset<128>("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001110000000000000000000000000001011"));
		VERIFY(0x38000000Bu == b.to_ullong());
		b.set(63);
		VERIFY(b == hamon::bitset<128>("00000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000001110000000000000000000000000001011"));
		VERIFY(0x800000038000000Bu == b.to_ullong());
		b.set(64);
		VERIFY(b == hamon::bitset<128>("00000000000000000000000000000000000000000000000000000000000000011000000000000000000000000000001110000000000000000000000000001011"));
		b.set(64, false);
		VERIFY(b == hamon::bitset<128>("00000000000000000000000000000000000000000000000000000000000000001000000000000000000000000000001110000000000000000000000000001011"));
		b.set(65);
		VERIFY(b == hamon::bitset<128>("00000000000000000000000000000000000000000000000000000000000000101000000000000000000000000000001110000000000000000000000000001011"));
		b.set(127);
		VERIFY(b == hamon::bitset<128>("10000000000000000000000000000000000000000000000000000000000000101000000000000000000000000000001110000000000000000000000000001011"));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(BitsetTest, SetTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test());

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::bitset<0> b(1);
		EXPECT_NO_THROW(b.set());
		EXPECT_THROW(b.set(0), hamon::out_of_range);
		EXPECT_THROW(b.set(0, true), hamon::out_of_range);
		EXPECT_THROW(b.set(0, false), hamon::out_of_range);
	}
	{
		hamon::bitset<1> b(1);
		EXPECT_NO_THROW(b.set(0));
		EXPECT_NO_THROW(b.set(0, true));
		EXPECT_NO_THROW(b.set(0, false));
		EXPECT_THROW(b.set(1), hamon::out_of_range);
		EXPECT_THROW(b.set(1, true), hamon::out_of_range);
		EXPECT_THROW(b.set(1, false), hamon::out_of_range);
	}
	{
		hamon::bitset<7> b(1);
		EXPECT_NO_THROW(b.set(6));
		EXPECT_NO_THROW(b.set(6, true));
		EXPECT_NO_THROW(b.set(6, false));
		EXPECT_THROW(b.set(7), hamon::out_of_range);
		EXPECT_THROW(b.set(7, true), hamon::out_of_range);
		EXPECT_THROW(b.set(7, false), hamon::out_of_range);
	}
	{
		hamon::bitset<8> b(1);
		EXPECT_NO_THROW(b.set(7));
		EXPECT_NO_THROW(b.set(7, true));
		EXPECT_NO_THROW(b.set(7, false));
		EXPECT_THROW(b.set(8), hamon::out_of_range);
		EXPECT_THROW(b.set(8, true), hamon::out_of_range);
		EXPECT_THROW(b.set(8, false), hamon::out_of_range);
	}
	{
		hamon::bitset<13> b(1);
		EXPECT_NO_THROW(b.set(12));
		EXPECT_NO_THROW(b.set(12, true));
		EXPECT_NO_THROW(b.set(12, false));
		EXPECT_THROW(b.set(13), hamon::out_of_range);
		EXPECT_THROW(b.set(13, true), hamon::out_of_range);
		EXPECT_THROW(b.set(13, false), hamon::out_of_range);
	}
	{
		hamon::bitset<63> b(1);
		EXPECT_NO_THROW(b.set(62));
		EXPECT_NO_THROW(b.set(62, true));
		EXPECT_NO_THROW(b.set(62, false));
		EXPECT_THROW(b.set(63), hamon::out_of_range);
		EXPECT_THROW(b.set(63, true), hamon::out_of_range);
		EXPECT_THROW(b.set(63, false), hamon::out_of_range);
	}
	{
		hamon::bitset<128> b(1);
		EXPECT_NO_THROW(b.set(127));
		EXPECT_NO_THROW(b.set(127, true));
		EXPECT_NO_THROW(b.set(127, false));
		EXPECT_THROW(b.set(128), hamon::out_of_range);
		EXPECT_THROW(b.set(128, true), hamon::out_of_range);
		EXPECT_THROW(b.set(128, false), hamon::out_of_range);
	}
#endif
}

}	// namespace set_test

}	// namespace hamon_bitset_test
