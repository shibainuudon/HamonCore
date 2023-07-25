/**
 *	@file	unit_test_bigint_algo_bit_shift_left.cpp
 *
 *	@brief	bigint_algo::bit_shift_left のテスト
 */

#include <hamon/bigint/bigint_algo/bit_shift_left.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

GTEST_TEST(BigIntAlgoTest, BitShiftLeftTest)
{
	{
		std::vector<hamon::uint8_t> const a{0};
		EXPECT_EQ((std::vector<hamon::uint8_t>{0}), hamon::bigint_algo::bit_shift_left(a, 0).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{0}), hamon::bigint_algo::bit_shift_left(a, 1).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{0}), hamon::bigint_algo::bit_shift_left(a, 2).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{0}), hamon::bigint_algo::bit_shift_left(a, 3).value);
	}
	{
		std::vector<hamon::uint8_t> const a{1};
		EXPECT_EQ((std::vector<hamon::uint8_t>{1}), hamon::bigint_algo::bit_shift_left(a, 0).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{2}), hamon::bigint_algo::bit_shift_left(a, 1).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{4}), hamon::bigint_algo::bit_shift_left(a, 2).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{8}), hamon::bigint_algo::bit_shift_left(a, 3).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x80}), hamon::bigint_algo::bit_shift_left(a, 7).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x01}), hamon::bigint_algo::bit_shift_left(a, 8).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x02}), hamon::bigint_algo::bit_shift_left(a, 9).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x80}), hamon::bigint_algo::bit_shift_left(a, 15).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x00, 0x01}), hamon::bigint_algo::bit_shift_left(a, 16).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x00, 0x02}), hamon::bigint_algo::bit_shift_left(a, 17).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x00, 0x80}), hamon::bigint_algo::bit_shift_left(a, 23).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x00, 0x00, 0x01}), hamon::bigint_algo::bit_shift_left(a, 24).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x00, 0x00, 0x02}), hamon::bigint_algo::bit_shift_left(a, 25).value);
	}
	{
		std::vector<hamon::uint8_t> const a{0xFF, 0xFF};
		EXPECT_EQ((std::vector<hamon::uint8_t>{0xFF, 0xFF}), hamon::bigint_algo::bit_shift_left(a, 0).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{0xFE, 0xFF, 0x01}), hamon::bigint_algo::bit_shift_left(a, 1).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{0xFC, 0xFF, 0x03}), hamon::bigint_algo::bit_shift_left(a, 2).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{0xF8, 0xFF, 0x07}), hamon::bigint_algo::bit_shift_left(a, 3).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x80, 0xFF, 0x7F}), hamon::bigint_algo::bit_shift_left(a, 7).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0xFF, 0xFF}), hamon::bigint_algo::bit_shift_left(a, 8).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0xFE, 0xFF, 0x01}), hamon::bigint_algo::bit_shift_left(a, 9).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x80, 0xFF, 0x7F}), hamon::bigint_algo::bit_shift_left(a, 15).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x00, 0xFF, 0xFF}), hamon::bigint_algo::bit_shift_left(a, 16).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x00, 0xFE, 0xFF, 0x01}), hamon::bigint_algo::bit_shift_left(a, 17).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x00, 0x80, 0xFF, 0x7F}), hamon::bigint_algo::bit_shift_left(a, 23).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x00, 0x00, 0xFF, 0xFF}), hamon::bigint_algo::bit_shift_left(a, 24).value);
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x00, 0x00, 0xFE, 0xFF, 0x01}), hamon::bigint_algo::bit_shift_left(a, 25).value);
	}
	{
		std::vector<hamon::uint64_t> const a{0xFFFFFFFFFFFFFFFF};
		EXPECT_EQ((std::vector<hamon::uint64_t>{0xFFFFFFFFFFFFFFFF}), hamon::bigint_algo::bit_shift_left(a, 0).value);
		EXPECT_EQ((std::vector<hamon::uint64_t>{0xFFFFFFFFFFFFFFFE, 0x0000000000000001}), hamon::bigint_algo::bit_shift_left(a, 1).value);
		EXPECT_EQ((std::vector<hamon::uint64_t>{0x8000000000000000, 0x7FFFFFFFFFFFFFFF}), hamon::bigint_algo::bit_shift_left(a, 63).value);
		EXPECT_EQ((std::vector<hamon::uint64_t>{0x0000000000000000, 0xFFFFFFFFFFFFFFFF}), hamon::bigint_algo::bit_shift_left(a, 64).value);
		EXPECT_EQ((std::vector<hamon::uint64_t>{0x0000000000000000, 0xFFFFFFFFFFFFFFFE, 0x0000000000000001}), hamon::bigint_algo::bit_shift_left(a, 65).value);
		EXPECT_EQ((std::vector<hamon::uint64_t>{0x0000000000000000, 0x8000000000000000, 0x7FFFFFFFFFFFFFFF}), hamon::bigint_algo::bit_shift_left(a, 127).value);
		EXPECT_EQ((std::vector<hamon::uint64_t>{0x0000000000000000, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF}), hamon::bigint_algo::bit_shift_left(a, 128).value);
		EXPECT_EQ((std::vector<hamon::uint64_t>{0x0000000000000000, 0x0000000000000000, 0xFFFFFFFFFFFFFFFE, 0x0000000000000001}), hamon::bigint_algo::bit_shift_left(a, 129).value);
	}
	{
		std::vector<hamon::uint8_t> const a{0xFF, 0xFF, 0xFF};
		EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 0).overflow);
		EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 1).overflow);
		EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 24).overflow);
	}
	{
		std::vector<hamon::uint8_t> const a{0xFF, 0xFF, 0x7F};
		EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 0).overflow);
		EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 1).overflow);
		EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 2).overflow);
		EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 24).overflow);
	}
	{
		std::vector<hamon::uint8_t> const a{0xFF, 0xFF, 0x01};
		EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 0).overflow);
		EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 7).overflow);
		EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 8).overflow);
		EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 24).overflow);
	}
	{
		std::vector<hamon::uint8_t> const a{0xFF, 0xFF, 0x00};
		EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 0).overflow);
		EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 8).overflow);
		EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 9).overflow);
		EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 24).overflow);
	}
	{
		std::vector<hamon::uint8_t> const a{0xFF, 0x7F, 0x00};
		EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 0).overflow);
		EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 9).overflow);
		EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 10).overflow);
		EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 24).overflow);
	}
	{
		std::vector<hamon::uint8_t> const a{0x01, 0x00, 0x00};
		EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 0).overflow);
		EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 23).overflow);
		EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 24).overflow);
	}
	{
		std::vector<hamon::uint8_t> const a{0x00, 0x00, 0x00};
		EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 0).overflow);
		EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 24).overflow);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 3> const a{0xFF, 0x7F, 0x00};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint8_t, 3>{0xFF, 0x7F, 0x00}), hamon::bigint_algo::bit_shift_left(a, 0).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint8_t, 3>{0xFE, 0xFF, 0x00}), hamon::bigint_algo::bit_shift_left(a, 1).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint8_t, 3>{0xFC, 0xFF, 0x01}), hamon::bigint_algo::bit_shift_left(a, 2).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint8_t, 3>{0x80, 0xFF, 0x3F}), hamon::bigint_algo::bit_shift_left(a, 7).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint8_t, 3>{0x00, 0xFF, 0x7F}), hamon::bigint_algo::bit_shift_left(a, 8).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint8_t, 3>{0x00, 0xFE, 0xFF}), hamon::bigint_algo::bit_shift_left(a, 9).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint8_t, 3>{0x00, 0x80, 0xFF}), hamon::bigint_algo::bit_shift_left(a, 15).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint8_t, 3>{0x00, 0x00, 0xFF}), hamon::bigint_algo::bit_shift_left(a, 16).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint8_t, 3>{0x00, 0x00, 0xFE}), hamon::bigint_algo::bit_shift_left(a, 17).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint8_t, 3>{0x00, 0x00, 0xC0}), hamon::bigint_algo::bit_shift_left(a, 22).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint8_t, 3>{0x00, 0x00, 0x80}), hamon::bigint_algo::bit_shift_left(a, 23).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint8_t, 3>{0x00, 0x00, 0x00}), hamon::bigint_algo::bit_shift_left(a, 24).value);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 3> const a{0xFF, 0xFF, 0xFF};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 0).overflow);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  hamon::bigint_algo::bit_shift_left(a, 1).overflow);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  hamon::bigint_algo::bit_shift_left(a, 24).overflow);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 3> const a{0xFF, 0xFF, 0x7F};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 0).overflow);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 1).overflow);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  hamon::bigint_algo::bit_shift_left(a, 2).overflow);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  hamon::bigint_algo::bit_shift_left(a, 24).overflow);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 3> const a{0xFF, 0xFF, 0x01};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 0).overflow);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 7).overflow);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  hamon::bigint_algo::bit_shift_left(a, 8).overflow);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  hamon::bigint_algo::bit_shift_left(a, 24).overflow);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 3> const a{0xFF, 0xFF, 0x00};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 0).overflow);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 8).overflow);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  hamon::bigint_algo::bit_shift_left(a, 9).overflow);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  hamon::bigint_algo::bit_shift_left(a, 24).overflow);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 3> const a{0xFF, 0x7F, 0x00};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 0).overflow);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 9).overflow);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  hamon::bigint_algo::bit_shift_left(a, 10).overflow);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  hamon::bigint_algo::bit_shift_left(a, 24).overflow);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 3> const a{0x01, 0x00, 0x00};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 0).overflow);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 23).overflow);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(true,  hamon::bigint_algo::bit_shift_left(a, 24).overflow);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 3> const a{0x00, 0x00, 0x00};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 0).overflow);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(false, hamon::bigint_algo::bit_shift_left(a, 24).overflow);
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint64_t, 2> const a{0x0123456789ABCDEF, 0x00};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0123456789ABCDEF, 0x0000000000000000}), hamon::bigint_algo::bit_shift_left(a, 0).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x02468ACF13579BDE, 0x0000000000000000}), hamon::bigint_algo::bit_shift_left(a, 1).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x048D159E26AF37BC, 0x0000000000000000}), hamon::bigint_algo::bit_shift_left(a, 2).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x091A2B3C4D5E6F78, 0x0000000000000000}), hamon::bigint_algo::bit_shift_left(a, 3).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x123456789ABCDEF0, 0x0000000000000000}), hamon::bigint_algo::bit_shift_left(a, 4).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x2468ACF13579BDE0, 0x0000000000000000}), hamon::bigint_algo::bit_shift_left(a, 5).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x48D159E26AF37BC0, 0x0000000000000000}), hamon::bigint_algo::bit_shift_left(a, 6).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x91A2B3C4D5E6F780, 0x0000000000000000}), hamon::bigint_algo::bit_shift_left(a, 7).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x23456789ABCDEF00, 0x0000000000000001}), hamon::bigint_algo::bit_shift_left(a, 8).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x468ACF13579BDE00, 0x0000000000000002}), hamon::bigint_algo::bit_shift_left(a, 9).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x8D159E26AF37BC00, 0x0000000000000004}), hamon::bigint_algo::bit_shift_left(a, 10).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x1A2B3C4D5E6F7800, 0x0000000000000009}), hamon::bigint_algo::bit_shift_left(a, 11).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x8000000000000000, 0x0091A2B3C4D5E6F7}), hamon::bigint_algo::bit_shift_left(a, 63).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x0123456789ABCDEF}), hamon::bigint_algo::bit_shift_left(a, 64).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x02468ACF13579BDE}), hamon::bigint_algo::bit_shift_left(a, 65).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x048D159E26AF37BC}), hamon::bigint_algo::bit_shift_left(a, 66).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x091A2B3C4D5E6F78}), hamon::bigint_algo::bit_shift_left(a, 67).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x123456789ABCDEF0}), hamon::bigint_algo::bit_shift_left(a, 68).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x2468ACF13579BDE0}), hamon::bigint_algo::bit_shift_left(a, 69).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x48D159E26AF37BC0}), hamon::bigint_algo::bit_shift_left(a, 70).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x91A2B3C4D5E6F780}), hamon::bigint_algo::bit_shift_left(a, 71).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x23456789ABCDEF00}), hamon::bigint_algo::bit_shift_left(a, 72).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x468ACF13579BDE00}), hamon::bigint_algo::bit_shift_left(a, 73).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x8D159E26AF37BC00}), hamon::bigint_algo::bit_shift_left(a, 74).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x1A2B3C4D5E6F7800}), hamon::bigint_algo::bit_shift_left(a, 75).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0xC000000000000000}), hamon::bigint_algo::bit_shift_left(a, 126).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x8000000000000000}), hamon::bigint_algo::bit_shift_left(a, 127).value);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x0000000000000000}), hamon::bigint_algo::bit_shift_left(a, 128).value);
	}
}
