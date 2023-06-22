﻿/**
 *	@file	unit_test_bitset_ctor_value.cpp
 *
 *	@brief	整数値を受け取るコンストラクタのテスト
 *
 *	constexpr bitset(unsigned long long val) noexcept;
 */

#include <hamon/bitset.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bitset_test
{

namespace ctor_value_test
{

GTEST_TEST(BitsetTest, CtorValueTest)
{
	{
		HAMON_CXX11_CONSTEXPR unsigned long long val = 0;
		HAMON_CXX11_CONSTEXPR hamon::bitset<  0> b1{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<  1> b2{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<  2> b3{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<  8> b4{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 16> b5{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 32> b6{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 64> b7{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<100> b8{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<128> b9{val};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b1.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b2.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b3.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b4.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b5.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b6.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b7.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b8.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b9.to_ullong());

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b1.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b2.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b3.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b4.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b5.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b6.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b7.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b8.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b9.count());

		EXPECT_EQ("", b1.to_string());
		EXPECT_EQ("0", b2.to_string());
		EXPECT_EQ("00", b3.to_string());
		EXPECT_EQ("00000000", b4.to_string());
		EXPECT_EQ("0000000000000000", b5.to_string());
		EXPECT_EQ("00000000000000000000000000000000", b6.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000000000", b7.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", b8.to_string());
		EXPECT_EQ("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", b9.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR unsigned long long val = 1;
		HAMON_CXX11_CONSTEXPR hamon::bitset<  0> b1{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<  1> b2{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<  2> b3{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<  8> b4{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 16> b5{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 32> b6{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 64> b7{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<100> b8{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<128> b9{val};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b1.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b2.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b3.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b4.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b5.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b6.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b7.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b8.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b9.to_ullong());

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b1.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b2.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b3.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b4.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b5.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b6.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b7.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b8.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b9.count());

		EXPECT_EQ("", b1.to_string());
		EXPECT_EQ("1", b2.to_string());
		EXPECT_EQ("01", b3.to_string());
		EXPECT_EQ("00000001", b4.to_string());
		EXPECT_EQ("0000000000000001", b5.to_string());
		EXPECT_EQ("00000000000000000000000000000001", b6.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000000001", b7.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001", b8.to_string());
		EXPECT_EQ("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001", b9.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR unsigned long long val = 75;
		HAMON_CXX11_CONSTEXPR hamon::bitset<  0> b1{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<  1> b2{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<  2> b3{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<  8> b4{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 16> b5{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 32> b6{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 64> b7{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<100> b8{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<128> b9{val};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b1.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b2.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, b3.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(75u, b4.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(75u, b5.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(75u, b6.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(75u, b7.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(75u, b8.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(75u, b9.to_ullong());

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b1.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b2.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, b3.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, b4.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, b5.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, b6.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, b7.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, b8.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4u, b9.count());

		EXPECT_EQ("", b1.to_string());
		EXPECT_EQ("1", b2.to_string());
		EXPECT_EQ("11", b3.to_string());
		EXPECT_EQ("01001011", b4.to_string());
		EXPECT_EQ("0000000001001011", b5.to_string());
		EXPECT_EQ("00000000000000000000000001001011", b6.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000001001011", b7.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001001011", b8.to_string());
		EXPECT_EQ("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001001011", b9.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR unsigned long long val = 53548;
		HAMON_CXX11_CONSTEXPR hamon::bitset<  0> b1{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<  1> b2{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<  2> b3{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<  8> b4{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 16> b5{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 32> b6{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 64> b7{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<100> b8{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<128> b9{val};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b1.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b2.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b3.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(44u, b4.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(53548u, b5.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(53548u, b6.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(53548u, b7.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(53548u, b8.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(53548u, b9.to_ullong());

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b1.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b2.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b3.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, b4.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7u, b5.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7u, b6.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7u, b7.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7u, b8.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7u, b9.count());

		EXPECT_EQ("", b1.to_string());
		EXPECT_EQ("0", b2.to_string());
		EXPECT_EQ("00", b3.to_string());
		EXPECT_EQ("00101100", b4.to_string());
		EXPECT_EQ("1101000100101100", b5.to_string());
		EXPECT_EQ("00000000000000001101000100101100", b6.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000001101000100101100", b7.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000000000000000000000000000000000000000000000000001101000100101100", b8.to_string());
		EXPECT_EQ("00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001101000100101100", b9.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR unsigned long long val = 0x7FFFFFFFFFFFFFFF;
		HAMON_CXX11_CONSTEXPR hamon::bitset<  0> b1{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<  1> b2{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<  2> b3{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<  8> b4{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 15> b5{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 16> b6{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 17> b7{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 31> b8{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 32> b9{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 33> b10{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 63> b11{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 64> b12{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 65> b13{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<100> b14{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<128> b15{val};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b1.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b2.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, b3.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(255u, b4.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(32767u, b5.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(65535u, b6.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(131071u, b7.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2147483647u, b8.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4294967295u, b9.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8589934591u, b10.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x7FFFFFFFFFFFFFFFu, b11.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x7FFFFFFFFFFFFFFFu, b12.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x7FFFFFFFFFFFFFFFu, b13.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x7FFFFFFFFFFFFFFFu, b14.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x7FFFFFFFFFFFFFFFu, b15.to_ullong());

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b1.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b2.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, b3.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8u, b4.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(15u, b5.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16u, b6.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(17u, b7.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(31u, b8.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(32u, b9.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(33u, b10.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(63u, b11.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(63u, b12.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(63u, b13.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(63u, b14.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(63u, b15.count());

		EXPECT_EQ("", b1.to_string());
		EXPECT_EQ("1", b2.to_string());
		EXPECT_EQ("11", b3.to_string());
		EXPECT_EQ("11111111", b4.to_string());
		EXPECT_EQ("111111111111111", b5.to_string());
		EXPECT_EQ("1111111111111111", b6.to_string());
		EXPECT_EQ("11111111111111111", b7.to_string());
		EXPECT_EQ("1111111111111111111111111111111", b8.to_string());
		EXPECT_EQ("11111111111111111111111111111111", b9.to_string());
		EXPECT_EQ("111111111111111111111111111111111", b10.to_string());
		EXPECT_EQ("111111111111111111111111111111111111111111111111111111111111111", b11.to_string());
		EXPECT_EQ("0111111111111111111111111111111111111111111111111111111111111111", b12.to_string());
		EXPECT_EQ("00111111111111111111111111111111111111111111111111111111111111111", b13.to_string());
		EXPECT_EQ("0000000000000000000000000000000000000111111111111111111111111111111111111111111111111111111111111111", b14.to_string());
		EXPECT_EQ("00000000000000000000000000000000000000000000000000000000000000000111111111111111111111111111111111111111111111111111111111111111", b15.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR unsigned long long val = 0xFFFFFFFFFFFFFFFF;
		HAMON_CXX11_CONSTEXPR hamon::bitset< 0> b1{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 1> b2{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 2> b3{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 8> b4{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<16> b5{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<32> b6{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<63> b7{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<64> b8{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<65> b9{val};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b1.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b2.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(3u, b3.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(255u, b4.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(65535u, b5.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4294967295u, b6.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0x7FFFFFFFFFFFFFFFu, b7.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFFFFFFFFFFFFFFFFu, b8.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFFFFFFFFFFFFFFFFu, b9.to_ullong());

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b1.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b2.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, b3.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(8u, b4.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16u, b5.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(32u, b6.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(63u, b7.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(64u, b8.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(64u, b9.count());

		EXPECT_EQ("", b1.to_string());
		EXPECT_EQ("1", b2.to_string());
		EXPECT_EQ("11", b3.to_string());
		EXPECT_EQ("11111111", b4.to_string());
		EXPECT_EQ("1111111111111111", b5.to_string());
		EXPECT_EQ("11111111111111111111111111111111", b6.to_string());
		EXPECT_EQ("111111111111111111111111111111111111111111111111111111111111111", b7.to_string());
		EXPECT_EQ("1111111111111111111111111111111111111111111111111111111111111111", b8.to_string());
		EXPECT_EQ("01111111111111111111111111111111111111111111111111111111111111111", b9.to_string());
	}
	{
		HAMON_CXX11_CONSTEXPR unsigned long long val = 0xFFFFFFFFFFFFFFFE;
		HAMON_CXX11_CONSTEXPR hamon::bitset<  0> b1{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<  1> b2{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<  2> b3{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<  8> b4{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 15> b5{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 32> b6{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset< 64> b7{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<100> b8{val};
		HAMON_CXX11_CONSTEXPR hamon::bitset<128> b9{val};

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b1.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b2.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2u, b3.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(254u, b4.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(32766u, b5.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4294967294u, b6.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFFFFFFFFFFFFFFFEu, b7.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFFFFFFFFFFFFFFFEu, b8.to_ullong());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0xFFFFFFFFFFFFFFFEu, b9.to_ullong());

		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b1.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(0u, b2.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1u, b3.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7u, b4.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(14u, b5.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(31u, b6.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(63u, b7.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(63u, b8.count());
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(63u, b9.count());

		EXPECT_EQ("", b1.to_string());
		EXPECT_EQ("0", b2.to_string());
		EXPECT_EQ("10", b3.to_string());
		EXPECT_EQ("11111110", b4.to_string());
		EXPECT_EQ("111111111111110", b5.to_string());
		EXPECT_EQ("11111111111111111111111111111110", b6.to_string());
		EXPECT_EQ("1111111111111111111111111111111111111111111111111111111111111110", b7.to_string());
		EXPECT_EQ("0000000000000000000000000000000000001111111111111111111111111111111111111111111111111111111111111110", b8.to_string());
		EXPECT_EQ("00000000000000000000000000000000000000000000000000000000000000001111111111111111111111111111111111111111111111111111111111111110", b9.to_string());
	}
}

}	// namespace ctor_value_test

}	// namespace hamon_bitset_test
