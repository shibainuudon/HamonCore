/**
 *	@file	unit_test_bigint_algo_to_chars_length.cpp
 *
 *	@brief	bigint_algo::to_chars_length のテスト
 */

#include <hamon/bigint/bigint_algo/to_chars_length.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/inplace_vector.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "bigint_algo_test_helper.hpp"

namespace hamon_bigint_test
{

namespace bigint_algo_to_chars_length_test
{

GTEST_TEST(BigIntAlgoTest, ToCharsLengthTest)
{
	// vector
	{
		using Vector = hamon::vector<hamon::uint8_t>;
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(8u, hamon::bigint_algo::to_chars_length(Vector{0},  2));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(6u, hamon::bigint_algo::to_chars_length(Vector{0},  3));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(4u, hamon::bigint_algo::to_chars_length(Vector{0},  4));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(4u, hamon::bigint_algo::to_chars_length(Vector{0},  5));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(4u, hamon::bigint_algo::to_chars_length(Vector{0},  6));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(3u, hamon::bigint_algo::to_chars_length(Vector{0},  7));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(3u, hamon::bigint_algo::to_chars_length(Vector{0},  8));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(3u, hamon::bigint_algo::to_chars_length(Vector{0},  9));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(3u, hamon::bigint_algo::to_chars_length(Vector{0}, 10));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(3u, hamon::bigint_algo::to_chars_length(Vector{0}, 11));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(3u, hamon::bigint_algo::to_chars_length(Vector{0}, 12));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(3u, hamon::bigint_algo::to_chars_length(Vector{0}, 13));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(3u, hamon::bigint_algo::to_chars_length(Vector{0}, 14));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(3u, hamon::bigint_algo::to_chars_length(Vector{0}, 15));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(Vector{0}, 16));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(Vector{0}, 17));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(Vector{0}, 18));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(Vector{0}, 19));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(Vector{0}, 20));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(Vector{0}, 21));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(Vector{0}, 22));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(Vector{0}, 23));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(Vector{0}, 24));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(Vector{0}, 25));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(Vector{0}, 26));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(Vector{0}, 27));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(Vector{0}, 28));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(Vector{0}, 29));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(Vector{0}, 30));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(Vector{0}, 31));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(Vector{0}, 32));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(Vector{0}, 33));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(Vector{0}, 34));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(Vector{0}, 35));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(2u, hamon::bigint_algo::to_chars_length(Vector{0}, 36));
	}
	{
		using Vector = hamon::vector<hamon::uint8_t>;
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(16u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF},  2));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(11u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF},  3));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF},  4));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF},  5));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF},  6));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF},  7));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF},  8));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF},  9));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 10));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 11));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 12));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 13));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 14));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 15));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 16));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 17));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 18));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 19));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 20));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 21));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 22));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 23));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 24));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 25));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 26));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 27));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 28));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 29));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 30));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 31));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 32));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 33));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 34));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 35));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 36));
	}
	{
		using Vector = hamon::vector<hamon::uint16_t>;
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(16u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF},  2));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(11u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF},  3));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF},  4));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF},  5));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF},  6));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF},  7));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF},  8));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF},  9));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 10));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 11));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 12));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 13));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 14));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 15));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 16));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 17));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 18));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 19));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 20));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 21));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 22));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 23));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 24));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 25));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 26));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 27));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 28));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 29));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 30));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 31));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 32));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 33));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 34));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 35));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF}, 36));
	}
	{
		using Vector = hamon::vector<hamon::uint16_t>;
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(32u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF},  2));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(21u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF},  3));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(16u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF},  4));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(14u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF},  5));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(13u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF},  6));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(12u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF},  7));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(11u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF},  8));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(11u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF},  9));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(10u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 10));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(10u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 11));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 9u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 12));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 9u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 13));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 9u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 14));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 9u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 15));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 16));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 17));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 18));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 19));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 20));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 21));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 22));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 23));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 24));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 25));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 26));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 27));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 28));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 29));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 30));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 31));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 32));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 33));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 34));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 35));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(Vector{0xFFFF, 0xFFFF}, 36));
	}
	{
		using Vector = hamon::vector<hamon::uint32_t>;
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(96u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},  2));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(61u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},  3));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(48u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},  4));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(42u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},  5));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(38u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},  6));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(35u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},  7));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(32u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},  8));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(31u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},  9));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(29u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 10));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(28u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 11));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(27u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 12));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(26u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 13));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(26u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 14));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(25u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 15));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(24u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 16));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(24u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 17));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(24u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 18));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(23u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 19));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(23u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 20));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(22u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 21));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(22u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 22));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(22u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 23));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(21u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 24));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(21u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 25));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(21u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 26));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(21u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 27));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(20u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 28));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(20u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 29));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(20u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 30));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(20u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 31));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(20u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 32));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(20u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 33));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(19u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 34));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(19u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 35));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(19u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 36));
	}
	{
		using Vector = hamon::vector<hamon::uint64_t>;
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(256u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1},  2));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(162u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1},  3));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(128u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1},  4));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(111u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1},  5));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ(100u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1},  6));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 92u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1},  7));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 86u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1},  8));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 81u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1},  9));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 78u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 10));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 75u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 11));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 72u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 12));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 70u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 13));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 68u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 14));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 66u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 15));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 64u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 16));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 63u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 17));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 62u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 18));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 61u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 19));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 60u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 20));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 59u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 21));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 58u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 22));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 57u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 23));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 56u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 24));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 56u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 25));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 55u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 26));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 54u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 27));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 54u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 28));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 53u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 29));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 53u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 30));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 52u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 31));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 52u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 32));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 51u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 33));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 51u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 34));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 50u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 35));
		HAMON_CXX20_CONSTEXPR_EXPECT_EQ( 50u, hamon::bigint_algo::to_chars_length(Vector{0, 0, 0, 1}, 36));
	}

	// inplace_vector
	{
		using Vector = hamon::inplace_vector<hamon::uint8_t, 7>;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(16u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF},  2));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(11u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF},  3));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF},  4));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF},  5));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF},  6));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF},  7));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF},  8));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF},  9));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 10));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 11));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 12));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 13));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 14));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 15));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 16));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 17));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 18));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 19));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 20));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 21));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 22));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 23));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 24));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 25));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 26));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 27));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 28));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 29));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 30));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 31));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 32));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 33));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 34));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 35));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 36));
	}
	{
		using Vector = hamon::inplace_vector<hamon::uint32_t, 4>;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(96u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},  2));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(61u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},  3));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(48u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},  4));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(42u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},  5));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(38u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},  6));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(35u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},  7));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(32u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},  8));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(31u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},  9));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(29u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 10));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(28u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 11));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(27u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 12));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(26u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 13));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(26u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 14));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(25u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 15));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(24u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 16));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(24u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 17));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(24u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 18));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(23u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 19));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(23u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 20));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(22u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 21));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(22u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 22));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(22u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 23));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(21u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 24));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(21u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 25));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(21u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 26));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(21u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 27));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 28));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 29));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 30));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 31));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 32));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 33));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(19u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 34));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(19u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 35));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(19u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 36));
	}

	// array
	{
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint8_t, 8> const a{0, 0, 1};
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
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint16_t, 3> const a{0, 1};
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
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint32_t, 1> const a{0};
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
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint64_t, 3> const a{0, 0, 1};
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

	// MyVector
	{
		using Vector = MyVector<hamon::uint8_t, 7>;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(16u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF},  2));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(11u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF},  3));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 8u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF},  4));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF},  5));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF},  6));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF},  7));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF},  8));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 6u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF},  9));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 10));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 11));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 12));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 13));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 14));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 5u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 15));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 16));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 17));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 18));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 19));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 20));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 21));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 22));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 23));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 24));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 25));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 26));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 27));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 28));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 29));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 30));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 31));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 32));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 33));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 34));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 35));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4u, hamon::bigint_algo::to_chars_length(Vector{0xFF, 0xFF}, 36));
	}
	{
		using Vector = MyVector<hamon::uint32_t, 4>;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(96u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},  2));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(61u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},  3));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(48u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},  4));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(42u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},  5));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(38u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},  6));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(35u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},  7));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(32u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},  8));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(31u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},  9));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(29u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 10));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(28u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 11));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(27u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 12));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(26u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 13));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(26u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 14));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(25u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 15));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(24u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 16));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(24u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 17));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(24u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 18));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(23u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 19));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(23u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 20));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(22u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 21));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(22u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 22));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(22u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 23));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(21u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 24));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(21u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 25));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(21u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 26));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(21u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 27));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 28));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 29));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 30));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 31));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 32));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 33));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(19u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 34));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(19u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 35));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(19u, hamon::bigint_algo::to_chars_length(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, 36));
	}
}

}	// namespace bigint_algo_to_chars_length_test

}	// namespace hamon_bigint_test
