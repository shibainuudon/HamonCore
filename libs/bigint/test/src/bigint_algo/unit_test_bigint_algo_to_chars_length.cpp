﻿/**
 *	@file	unit_test_bigint_algo_to_chars_length.cpp
 *
 *	@brief	bigint_algo::to_chars_length のテスト
 */

#include <hamon/bigint/bigint_algo/to_chars_length.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(BigIntAlgoTest, ToCharsLengthTest)
{
	{
		hamon::vector<hamon::uint8_t> const a{0};
		EXPECT_EQ(8u, hamon::bigint_algo::to_chars_length(a,  2));
		EXPECT_EQ(6u, hamon::bigint_algo::to_chars_length(a,  3));
		EXPECT_EQ(4u, hamon::bigint_algo::to_chars_length(a,  4));
		EXPECT_EQ(4u, hamon::bigint_algo::to_chars_length(a,  5));
		EXPECT_EQ(4u, hamon::bigint_algo::to_chars_length(a,  6));
		EXPECT_EQ(3u, hamon::bigint_algo::to_chars_length(a,  7));
		EXPECT_EQ(3u, hamon::bigint_algo::to_chars_length(a,  8));
		EXPECT_EQ(3u, hamon::bigint_algo::to_chars_length(a,  9));
		EXPECT_EQ(3u, hamon::bigint_algo::to_chars_length(a, 10));
		EXPECT_EQ(3u, hamon::bigint_algo::to_chars_length(a, 11));
		EXPECT_EQ(3u, hamon::bigint_algo::to_chars_length(a, 12));
		EXPECT_EQ(3u, hamon::bigint_algo::to_chars_length(a, 13));
		EXPECT_EQ(3u, hamon::bigint_algo::to_chars_length(a, 14));
		EXPECT_EQ(3u, hamon::bigint_algo::to_chars_length(a, 15));
		EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(a, 16));
		EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(a, 17));
		EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(a, 18));
		EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(a, 19));
		EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(a, 20));
		EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(a, 21));
		EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(a, 22));
		EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(a, 23));
		EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(a, 24));
		EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(a, 25));
		EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(a, 26));
		EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(a, 27));
		EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(a, 28));
		EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(a, 29));
		EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(a, 30));
		EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(a, 31));
		EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(a, 32));
		EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(a, 33));
		EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(a, 34));
		EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(a, 35));
		EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(a, 36));
	}
	{
		hamon::vector<hamon::uint8_t> const a{0xFF, 0xFF};
		EXPECT_EQ(16u, hamon::bigint_algo::to_chars_length(a,  2));
		EXPECT_EQ(11u, hamon::bigint_algo::to_chars_length(a,  3));
		EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a,  4));
		EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a,  5));
		EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a,  6));
		EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(a,  7));
		EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(a,  8));
		EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(a,  9));
		EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(a, 10));
		EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(a, 11));
		EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(a, 12));
		EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(a, 13));
		EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(a, 14));
		EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(a, 15));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 16));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 17));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 18));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 19));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 20));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 21));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 22));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 23));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 24));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 25));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 26));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 27));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 28));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 29));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 30));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 31));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 32));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 33));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 34));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 35));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 36));
	}
	{
		hamon::vector<hamon::uint16_t> const a{0xFFFF};
		EXPECT_EQ(16u, hamon::bigint_algo::to_chars_length(a,  2));
		EXPECT_EQ(11u, hamon::bigint_algo::to_chars_length(a,  3));
		EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a,  4));
		EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a,  5));
		EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a,  6));
		EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(a,  7));
		EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(a,  8));
		EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(a,  9));
		EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(a, 10));
		EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(a, 11));
		EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(a, 12));
		EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(a, 13));
		EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(a, 14));
		EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(a, 15));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 16));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 17));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 18));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 19));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 20));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 21));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 22));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 23));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 24));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 25));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 26));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 27));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 28));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 29));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 30));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 31));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 32));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 33));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 34));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 35));
		EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(a, 36));
	}
	{
		hamon::vector<hamon::uint16_t> const a{0xFFFF, 0xFFFF};
		EXPECT_EQ(32u, hamon::bigint_algo::to_chars_length(a,  2));
		EXPECT_EQ(21u, hamon::bigint_algo::to_chars_length(a,  3));
		EXPECT_EQ(16u, hamon::bigint_algo::to_chars_length(a,  4));
		EXPECT_EQ(14u, hamon::bigint_algo::to_chars_length(a,  5));
		EXPECT_EQ(13u, hamon::bigint_algo::to_chars_length(a,  6));
		EXPECT_EQ(12u, hamon::bigint_algo::to_chars_length(a,  7));
		EXPECT_EQ(11u, hamon::bigint_algo::to_chars_length(a,  8));
		EXPECT_EQ(11u, hamon::bigint_algo::to_chars_length(a,  9));
		EXPECT_EQ(10u, hamon::bigint_algo::to_chars_length(a, 10));
		EXPECT_EQ(10u, hamon::bigint_algo::to_chars_length(a, 11));
		EXPECT_EQ( 9u, hamon::bigint_algo::to_chars_length(a, 12));
		EXPECT_EQ( 9u, hamon::bigint_algo::to_chars_length(a, 13));
		EXPECT_EQ( 9u, hamon::bigint_algo::to_chars_length(a, 14));
		EXPECT_EQ( 9u, hamon::bigint_algo::to_chars_length(a, 15));
		EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a, 16));
		EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a, 17));
		EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a, 18));
		EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a, 19));
		EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a, 20));
		EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a, 21));
		EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a, 22));
		EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a, 23));
		EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 24));
		EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 25));
		EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 26));
		EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 27));
		EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 28));
		EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 29));
		EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 30));
		EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 31));
		EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 32));
		EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 33));
		EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 34));
		EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 35));
		EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 36));
	}
	{
		hamon::vector<hamon::uint32_t> const a{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
		EXPECT_EQ(96u, hamon::bigint_algo::to_chars_length(a,  2));
		EXPECT_EQ(61u, hamon::bigint_algo::to_chars_length(a,  3));
		EXPECT_EQ(48u, hamon::bigint_algo::to_chars_length(a,  4));
		EXPECT_EQ(42u, hamon::bigint_algo::to_chars_length(a,  5));
		EXPECT_EQ(38u, hamon::bigint_algo::to_chars_length(a,  6));
		EXPECT_EQ(35u, hamon::bigint_algo::to_chars_length(a,  7));
		EXPECT_EQ(32u, hamon::bigint_algo::to_chars_length(a,  8));
		EXPECT_EQ(31u, hamon::bigint_algo::to_chars_length(a,  9));
		EXPECT_EQ(29u, hamon::bigint_algo::to_chars_length(a, 10));
		EXPECT_EQ(28u, hamon::bigint_algo::to_chars_length(a, 11));
		EXPECT_EQ(27u, hamon::bigint_algo::to_chars_length(a, 12));
		EXPECT_EQ(26u, hamon::bigint_algo::to_chars_length(a, 13));
		EXPECT_EQ(26u, hamon::bigint_algo::to_chars_length(a, 14));
		EXPECT_EQ(25u, hamon::bigint_algo::to_chars_length(a, 15));
		EXPECT_EQ(24u, hamon::bigint_algo::to_chars_length(a, 16));
		EXPECT_EQ(24u, hamon::bigint_algo::to_chars_length(a, 17));
		EXPECT_EQ(24u, hamon::bigint_algo::to_chars_length(a, 18));
		EXPECT_EQ(23u, hamon::bigint_algo::to_chars_length(a, 19));
		EXPECT_EQ(23u, hamon::bigint_algo::to_chars_length(a, 20));
		EXPECT_EQ(22u, hamon::bigint_algo::to_chars_length(a, 21));
		EXPECT_EQ(22u, hamon::bigint_algo::to_chars_length(a, 22));
		EXPECT_EQ(22u, hamon::bigint_algo::to_chars_length(a, 23));
		EXPECT_EQ(21u, hamon::bigint_algo::to_chars_length(a, 24));
		EXPECT_EQ(21u, hamon::bigint_algo::to_chars_length(a, 25));
		EXPECT_EQ(21u, hamon::bigint_algo::to_chars_length(a, 26));
		EXPECT_EQ(21u, hamon::bigint_algo::to_chars_length(a, 27));
		EXPECT_EQ(20u, hamon::bigint_algo::to_chars_length(a, 28));
		EXPECT_EQ(20u, hamon::bigint_algo::to_chars_length(a, 29));
		EXPECT_EQ(20u, hamon::bigint_algo::to_chars_length(a, 30));
		EXPECT_EQ(20u, hamon::bigint_algo::to_chars_length(a, 31));
		EXPECT_EQ(20u, hamon::bigint_algo::to_chars_length(a, 32));
		EXPECT_EQ(20u, hamon::bigint_algo::to_chars_length(a, 33));
		EXPECT_EQ(19u, hamon::bigint_algo::to_chars_length(a, 34));
		EXPECT_EQ(19u, hamon::bigint_algo::to_chars_length(a, 35));
		EXPECT_EQ(19u, hamon::bigint_algo::to_chars_length(a, 36));
	}
	{
		hamon::vector<hamon::uint64_t> const a{0, 0, 0, 1};
		EXPECT_EQ(256u, hamon::bigint_algo::to_chars_length(a,  2));
		EXPECT_EQ(162u, hamon::bigint_algo::to_chars_length(a,  3));
		EXPECT_EQ(128u, hamon::bigint_algo::to_chars_length(a,  4));
		EXPECT_EQ(111u, hamon::bigint_algo::to_chars_length(a,  5));
		EXPECT_EQ(100u, hamon::bigint_algo::to_chars_length(a,  6));
		EXPECT_EQ( 92u, hamon::bigint_algo::to_chars_length(a,  7));
		EXPECT_EQ( 86u, hamon::bigint_algo::to_chars_length(a,  8));
		EXPECT_EQ( 81u, hamon::bigint_algo::to_chars_length(a,  9));
		EXPECT_EQ( 78u, hamon::bigint_algo::to_chars_length(a, 10));
		EXPECT_EQ( 75u, hamon::bigint_algo::to_chars_length(a, 11));
		EXPECT_EQ( 72u, hamon::bigint_algo::to_chars_length(a, 12));
		EXPECT_EQ( 70u, hamon::bigint_algo::to_chars_length(a, 13));
		EXPECT_EQ( 68u, hamon::bigint_algo::to_chars_length(a, 14));
		EXPECT_EQ( 66u, hamon::bigint_algo::to_chars_length(a, 15));
		EXPECT_EQ( 64u, hamon::bigint_algo::to_chars_length(a, 16));
		EXPECT_EQ( 63u, hamon::bigint_algo::to_chars_length(a, 17));
		EXPECT_EQ( 62u, hamon::bigint_algo::to_chars_length(a, 18));
		EXPECT_EQ( 61u, hamon::bigint_algo::to_chars_length(a, 19));
		EXPECT_EQ( 60u, hamon::bigint_algo::to_chars_length(a, 20));
		EXPECT_EQ( 59u, hamon::bigint_algo::to_chars_length(a, 21));
		EXPECT_EQ( 58u, hamon::bigint_algo::to_chars_length(a, 22));
		EXPECT_EQ( 57u, hamon::bigint_algo::to_chars_length(a, 23));
		EXPECT_EQ( 56u, hamon::bigint_algo::to_chars_length(a, 24));
		EXPECT_EQ( 56u, hamon::bigint_algo::to_chars_length(a, 25));
		EXPECT_EQ( 55u, hamon::bigint_algo::to_chars_length(a, 26));
		EXPECT_EQ( 54u, hamon::bigint_algo::to_chars_length(a, 27));
		EXPECT_EQ( 54u, hamon::bigint_algo::to_chars_length(a, 28));
		EXPECT_EQ( 53u, hamon::bigint_algo::to_chars_length(a, 29));
		EXPECT_EQ( 53u, hamon::bigint_algo::to_chars_length(a, 30));
		EXPECT_EQ( 52u, hamon::bigint_algo::to_chars_length(a, 31));
		EXPECT_EQ( 52u, hamon::bigint_algo::to_chars_length(a, 32));
		EXPECT_EQ( 51u, hamon::bigint_algo::to_chars_length(a, 33));
		EXPECT_EQ( 51u, hamon::bigint_algo::to_chars_length(a, 34));
		EXPECT_EQ( 50u, hamon::bigint_algo::to_chars_length(a, 35));
		EXPECT_EQ( 50u, hamon::bigint_algo::to_chars_length(a, 36));
	}
	{
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint8_t, 3> const a{};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(24u, hamon::bigint_algo::to_chars_length(a,  2));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(16u, hamon::bigint_algo::to_chars_length(a,  3));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(12u, hamon::bigint_algo::to_chars_length(a,  4));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(11u, hamon::bigint_algo::to_chars_length(a,  5));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10u, hamon::bigint_algo::to_chars_length(a,  6));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 9u, hamon::bigint_algo::to_chars_length(a,  7));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a,  8));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a,  9));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a, 10));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 11));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 12));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 13));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 14));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 15));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(a, 16));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(a, 17));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(a, 18));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(a, 19));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(a, 20));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(a, 21));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(a, 22));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(a, 23));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(a, 24));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(a, 25));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(a, 26));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(a, 27));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(a, 28));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(a, 29));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(a, 30));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(a, 31));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(a, 32));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(a, 33));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(a, 34));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(a, 35));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(a, 36));
	}
	{
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint16_t, 2> const a{};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(32u, hamon::bigint_algo::to_chars_length(a,  2));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(21u, hamon::bigint_algo::to_chars_length(a,  3));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(16u, hamon::bigint_algo::to_chars_length(a,  4));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(14u, hamon::bigint_algo::to_chars_length(a,  5));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(13u, hamon::bigint_algo::to_chars_length(a,  6));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(12u, hamon::bigint_algo::to_chars_length(a,  7));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(11u, hamon::bigint_algo::to_chars_length(a,  8));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(11u, hamon::bigint_algo::to_chars_length(a,  9));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10u, hamon::bigint_algo::to_chars_length(a, 10));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10u, hamon::bigint_algo::to_chars_length(a, 11));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 9u, hamon::bigint_algo::to_chars_length(a, 12));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 9u, hamon::bigint_algo::to_chars_length(a, 13));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 9u, hamon::bigint_algo::to_chars_length(a, 14));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 9u, hamon::bigint_algo::to_chars_length(a, 15));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a, 16));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a, 17));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a, 18));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a, 19));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a, 20));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a, 21));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a, 22));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a, 23));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 24));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 25));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 26));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 27));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 28));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 29));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 30));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 31));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 32));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 33));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 34));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 35));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 36));
	}
	{
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint32_t, 1> const a{};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(32u, hamon::bigint_algo::to_chars_length(a,  2));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(21u, hamon::bigint_algo::to_chars_length(a,  3));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(16u, hamon::bigint_algo::to_chars_length(a,  4));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(14u, hamon::bigint_algo::to_chars_length(a,  5));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(13u, hamon::bigint_algo::to_chars_length(a,  6));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(12u, hamon::bigint_algo::to_chars_length(a,  7));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(11u, hamon::bigint_algo::to_chars_length(a,  8));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(11u, hamon::bigint_algo::to_chars_length(a,  9));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10u, hamon::bigint_algo::to_chars_length(a, 10));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10u, hamon::bigint_algo::to_chars_length(a, 11));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 9u, hamon::bigint_algo::to_chars_length(a, 12));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 9u, hamon::bigint_algo::to_chars_length(a, 13));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 9u, hamon::bigint_algo::to_chars_length(a, 14));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 9u, hamon::bigint_algo::to_chars_length(a, 15));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a, 16));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a, 17));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a, 18));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a, 19));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a, 20));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a, 21));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a, 22));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(a, 23));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 24));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 25));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 26));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 27));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 28));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 29));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 30));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 31));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 32));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 33));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 34));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 35));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(a, 36));
	}
	{
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint64_t, 3> const a{};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(192u, hamon::bigint_algo::to_chars_length(a,  2));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(122u, hamon::bigint_algo::to_chars_length(a,  3));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 96u, hamon::bigint_algo::to_chars_length(a,  4));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 83u, hamon::bigint_algo::to_chars_length(a,  5));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 75u, hamon::bigint_algo::to_chars_length(a,  6));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 69u, hamon::bigint_algo::to_chars_length(a,  7));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 64u, hamon::bigint_algo::to_chars_length(a,  8));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 61u, hamon::bigint_algo::to_chars_length(a,  9));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 58u, hamon::bigint_algo::to_chars_length(a, 10));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 56u, hamon::bigint_algo::to_chars_length(a, 11));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 54u, hamon::bigint_algo::to_chars_length(a, 12));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 52u, hamon::bigint_algo::to_chars_length(a, 13));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 51u, hamon::bigint_algo::to_chars_length(a, 14));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 50u, hamon::bigint_algo::to_chars_length(a, 15));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 48u, hamon::bigint_algo::to_chars_length(a, 16));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 47u, hamon::bigint_algo::to_chars_length(a, 17));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 47u, hamon::bigint_algo::to_chars_length(a, 18));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 46u, hamon::bigint_algo::to_chars_length(a, 19));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 45u, hamon::bigint_algo::to_chars_length(a, 20));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 44u, hamon::bigint_algo::to_chars_length(a, 21));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 44u, hamon::bigint_algo::to_chars_length(a, 22));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 43u, hamon::bigint_algo::to_chars_length(a, 23));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 42u, hamon::bigint_algo::to_chars_length(a, 24));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 42u, hamon::bigint_algo::to_chars_length(a, 25));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 41u, hamon::bigint_algo::to_chars_length(a, 26));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 41u, hamon::bigint_algo::to_chars_length(a, 27));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 40u, hamon::bigint_algo::to_chars_length(a, 28));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 40u, hamon::bigint_algo::to_chars_length(a, 29));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 40u, hamon::bigint_algo::to_chars_length(a, 30));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 39u, hamon::bigint_algo::to_chars_length(a, 31));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 39u, hamon::bigint_algo::to_chars_length(a, 32));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 39u, hamon::bigint_algo::to_chars_length(a, 33));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 38u, hamon::bigint_algo::to_chars_length(a, 34));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 38u, hamon::bigint_algo::to_chars_length(a, 35));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 38u, hamon::bigint_algo::to_chars_length(a, 36));
	}
}
