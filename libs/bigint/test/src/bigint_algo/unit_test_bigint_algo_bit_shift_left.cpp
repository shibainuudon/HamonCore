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
		EXPECT_EQ((std::vector<hamon::uint8_t>{0}), hamon::detail::bigint_algo::bit_shift_left(a, 0));
		EXPECT_EQ((std::vector<hamon::uint8_t>{0}), hamon::detail::bigint_algo::bit_shift_left(a, 1));
		EXPECT_EQ((std::vector<hamon::uint8_t>{0}), hamon::detail::bigint_algo::bit_shift_left(a, 2));
		EXPECT_EQ((std::vector<hamon::uint8_t>{0}), hamon::detail::bigint_algo::bit_shift_left(a, 3));
	}
	{
		std::vector<hamon::uint8_t> const a{1};
		EXPECT_EQ((std::vector<hamon::uint8_t>{1}), hamon::detail::bigint_algo::bit_shift_left(a, 0));
		EXPECT_EQ((std::vector<hamon::uint8_t>{2}), hamon::detail::bigint_algo::bit_shift_left(a, 1));
		EXPECT_EQ((std::vector<hamon::uint8_t>{4}), hamon::detail::bigint_algo::bit_shift_left(a, 2));
		EXPECT_EQ((std::vector<hamon::uint8_t>{8}), hamon::detail::bigint_algo::bit_shift_left(a, 3));
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x80}), hamon::detail::bigint_algo::bit_shift_left(a, 7));
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x01}), hamon::detail::bigint_algo::bit_shift_left(a, 8));
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x02}), hamon::detail::bigint_algo::bit_shift_left(a, 9));
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x80}), hamon::detail::bigint_algo::bit_shift_left(a, 15));
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x00, 0x01}), hamon::detail::bigint_algo::bit_shift_left(a, 16));
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x00, 0x02}), hamon::detail::bigint_algo::bit_shift_left(a, 17));
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x00, 0x80}), hamon::detail::bigint_algo::bit_shift_left(a, 23));
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x00, 0x00, 0x01}), hamon::detail::bigint_algo::bit_shift_left(a, 24));
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x00, 0x00, 0x02}), hamon::detail::bigint_algo::bit_shift_left(a, 25));
	}
	{
		std::vector<hamon::uint8_t> const a{0xFF, 0xFF};
		EXPECT_EQ((std::vector<hamon::uint8_t>{0xFF, 0xFF}), hamon::detail::bigint_algo::bit_shift_left(a, 0));
		EXPECT_EQ((std::vector<hamon::uint8_t>{0xFE, 0xFF, 0x01}), hamon::detail::bigint_algo::bit_shift_left(a, 1));
		EXPECT_EQ((std::vector<hamon::uint8_t>{0xFC, 0xFF, 0x03}), hamon::detail::bigint_algo::bit_shift_left(a, 2));
		EXPECT_EQ((std::vector<hamon::uint8_t>{0xF8, 0xFF, 0x07}), hamon::detail::bigint_algo::bit_shift_left(a, 3));
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x80, 0xFF, 0x7F}), hamon::detail::bigint_algo::bit_shift_left(a, 7));
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0xFF, 0xFF}), hamon::detail::bigint_algo::bit_shift_left(a, 8));
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0xFE, 0xFF, 0x01}), hamon::detail::bigint_algo::bit_shift_left(a, 9));
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x80, 0xFF, 0x7F}), hamon::detail::bigint_algo::bit_shift_left(a, 15));
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x00, 0xFF, 0xFF}), hamon::detail::bigint_algo::bit_shift_left(a, 16));
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x00, 0xFE, 0xFF, 0x01}), hamon::detail::bigint_algo::bit_shift_left(a, 17));
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x00, 0x80, 0xFF, 0x7F}), hamon::detail::bigint_algo::bit_shift_left(a, 23));
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x00, 0x00, 0xFF, 0xFF}), hamon::detail::bigint_algo::bit_shift_left(a, 24));
		EXPECT_EQ((std::vector<hamon::uint8_t>{0x00, 0x00, 0x00, 0xFE, 0xFF, 0x01}), hamon::detail::bigint_algo::bit_shift_left(a, 25));
	}
	{
		std::vector<hamon::uint64_t> const a{0xFFFFFFFFFFFFFFFF};
		EXPECT_EQ((std::vector<hamon::uint64_t>{0xFFFFFFFFFFFFFFFF}), hamon::detail::bigint_algo::bit_shift_left(a, 0));
		EXPECT_EQ((std::vector<hamon::uint64_t>{0xFFFFFFFFFFFFFFFE, 0x0000000000000001}), hamon::detail::bigint_algo::bit_shift_left(a, 1));
		EXPECT_EQ((std::vector<hamon::uint64_t>{0x8000000000000000, 0x7FFFFFFFFFFFFFFF}), hamon::detail::bigint_algo::bit_shift_left(a, 63));
		EXPECT_EQ((std::vector<hamon::uint64_t>{0x0000000000000000, 0xFFFFFFFFFFFFFFFF}), hamon::detail::bigint_algo::bit_shift_left(a, 64));
		EXPECT_EQ((std::vector<hamon::uint64_t>{0x0000000000000000, 0xFFFFFFFFFFFFFFFE, 0x0000000000000001}), hamon::detail::bigint_algo::bit_shift_left(a, 65));
		EXPECT_EQ((std::vector<hamon::uint64_t>{0x0000000000000000, 0x8000000000000000, 0x7FFFFFFFFFFFFFFF}), hamon::detail::bigint_algo::bit_shift_left(a, 127));
		EXPECT_EQ((std::vector<hamon::uint64_t>{0x0000000000000000, 0x0000000000000000, 0xFFFFFFFFFFFFFFFF}), hamon::detail::bigint_algo::bit_shift_left(a, 128));
		EXPECT_EQ((std::vector<hamon::uint64_t>{0x0000000000000000, 0x0000000000000000, 0xFFFFFFFFFFFFFFFE, 0x0000000000000001}), hamon::detail::bigint_algo::bit_shift_left(a, 129));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint8_t, 3> const a{0xFF, 0x7F, 0x00};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint8_t, 3>{0xFF, 0x7F, 0x00}), hamon::detail::bigint_algo::bit_shift_left(a, 0));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint8_t, 3>{0xFE, 0xFF, 0x00}), hamon::detail::bigint_algo::bit_shift_left(a, 1));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint8_t, 3>{0xFC, 0xFF, 0x01}), hamon::detail::bigint_algo::bit_shift_left(a, 2));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint8_t, 3>{0x80, 0xFF, 0x3F}), hamon::detail::bigint_algo::bit_shift_left(a, 7));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint8_t, 3>{0x00, 0xFF, 0x7F}), hamon::detail::bigint_algo::bit_shift_left(a, 8));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint8_t, 3>{0x00, 0xFE, 0xFF}), hamon::detail::bigint_algo::bit_shift_left(a, 9));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint8_t, 3>{0x00, 0x80, 0xFF}), hamon::detail::bigint_algo::bit_shift_left(a, 15));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint8_t, 3>{0x00, 0x00, 0xFF}), hamon::detail::bigint_algo::bit_shift_left(a, 16));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint8_t, 3>{0x00, 0x00, 0xFE}), hamon::detail::bigint_algo::bit_shift_left(a, 17));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint8_t, 3>{0x00, 0x00, 0xC0}), hamon::detail::bigint_algo::bit_shift_left(a, 22));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint8_t, 3>{0x00, 0x00, 0x80}), hamon::detail::bigint_algo::bit_shift_left(a, 23));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint8_t, 3>{0x00, 0x00, 0x00}), hamon::detail::bigint_algo::bit_shift_left(a, 24));
	}
	{
		HAMON_CXX11_CONSTEXPR hamon::array<hamon::uint64_t, 2> const a{0x0123456789ABCDEF, 0x00};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0123456789ABCDEF, 0x0000000000000000}), hamon::detail::bigint_algo::bit_shift_left(a, 0));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x02468ACF13579BDE, 0x0000000000000000}), hamon::detail::bigint_algo::bit_shift_left(a, 1));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x048D159E26AF37BC, 0x0000000000000000}), hamon::detail::bigint_algo::bit_shift_left(a, 2));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x091A2B3C4D5E6F78, 0x0000000000000000}), hamon::detail::bigint_algo::bit_shift_left(a, 3));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x123456789ABCDEF0, 0x0000000000000000}), hamon::detail::bigint_algo::bit_shift_left(a, 4));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x2468ACF13579BDE0, 0x0000000000000000}), hamon::detail::bigint_algo::bit_shift_left(a, 5));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x48D159E26AF37BC0, 0x0000000000000000}), hamon::detail::bigint_algo::bit_shift_left(a, 6));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x91A2B3C4D5E6F780, 0x0000000000000000}), hamon::detail::bigint_algo::bit_shift_left(a, 7));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x23456789ABCDEF00, 0x0000000000000001}), hamon::detail::bigint_algo::bit_shift_left(a, 8));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x468ACF13579BDE00, 0x0000000000000002}), hamon::detail::bigint_algo::bit_shift_left(a, 9));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x8D159E26AF37BC00, 0x0000000000000004}), hamon::detail::bigint_algo::bit_shift_left(a, 10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x1A2B3C4D5E6F7800, 0x0000000000000009}), hamon::detail::bigint_algo::bit_shift_left(a, 11));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x8000000000000000, 0x0091A2B3C4D5E6F7}), hamon::detail::bigint_algo::bit_shift_left(a, 63));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x0123456789ABCDEF}), hamon::detail::bigint_algo::bit_shift_left(a, 64));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x02468ACF13579BDE}), hamon::detail::bigint_algo::bit_shift_left(a, 65));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x048D159E26AF37BC}), hamon::detail::bigint_algo::bit_shift_left(a, 66));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x091A2B3C4D5E6F78}), hamon::detail::bigint_algo::bit_shift_left(a, 67));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x123456789ABCDEF0}), hamon::detail::bigint_algo::bit_shift_left(a, 68));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x2468ACF13579BDE0}), hamon::detail::bigint_algo::bit_shift_left(a, 69));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x48D159E26AF37BC0}), hamon::detail::bigint_algo::bit_shift_left(a, 70));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x91A2B3C4D5E6F780}), hamon::detail::bigint_algo::bit_shift_left(a, 71));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x23456789ABCDEF00}), hamon::detail::bigint_algo::bit_shift_left(a, 72));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x468ACF13579BDE00}), hamon::detail::bigint_algo::bit_shift_left(a, 73));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x8D159E26AF37BC00}), hamon::detail::bigint_algo::bit_shift_left(a, 74));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x1A2B3C4D5E6F7800}), hamon::detail::bigint_algo::bit_shift_left(a, 75));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0xC000000000000000}), hamon::detail::bigint_algo::bit_shift_left(a, 126));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x8000000000000000}), hamon::detail::bigint_algo::bit_shift_left(a, 127));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ((hamon::array<hamon::uint64_t, 2>{0x0000000000000000, 0x0000000000000000}), hamon::detail::bigint_algo::bit_shift_left(a, 128));
	}
}
