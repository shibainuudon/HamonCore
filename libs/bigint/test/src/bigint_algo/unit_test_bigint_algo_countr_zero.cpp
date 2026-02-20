/**
 *	@file	unit_test_bigint_algo_countr_zero.cpp
 *
 *	@brief	bigint_algo::countr_zero のテスト
 */

#include <hamon/bigint/bigint_algo/countr_zero.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/inplace_vector.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

GTEST_TEST(BigIntAlgoTest, CountRZeroTest)
{
	using hamon::bigint_algo::countr_zero;

	{
		using Vector = hamon::array<hamon::uint8_t, 2>;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(16, countr_zero(Vector{0x00, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 0, countr_zero(Vector{0x01, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 1, countr_zero(Vector{0x02, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 2, countr_zero(Vector{0x04, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 3, countr_zero(Vector{0x08, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4, countr_zero(Vector{0x10, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 5, countr_zero(Vector{0x20, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 6, countr_zero(Vector{0x40, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7, countr_zero(Vector{0x80, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 8, countr_zero(Vector{0x00, 0x01}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 9, countr_zero(Vector{0x00, 0x02}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, countr_zero(Vector{0x00, 0x04}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(11, countr_zero(Vector{0x00, 0x08}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(12, countr_zero(Vector{0x00, 0x10}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(13, countr_zero(Vector{0x00, 0x20}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(14, countr_zero(Vector{0x00, 0x40}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(15, countr_zero(Vector{0x00, 0x80}));
	}
	{
		using Vector = hamon::array<hamon::uint16_t, 3>;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 0, countr_zero(Vector{0xffff, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 1, countr_zero(Vector{0xfffe, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 2, countr_zero(Vector{0xfffc, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 3, countr_zero(Vector{0xfff8, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4, countr_zero(Vector{0xfff0, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 5, countr_zero(Vector{0xffe0, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 6, countr_zero(Vector{0xffc0, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7, countr_zero(Vector{0xff80, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 8, countr_zero(Vector{0xff00, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 9, countr_zero(Vector{0xfe00, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, countr_zero(Vector{0xfc00, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(11, countr_zero(Vector{0xf800, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(12, countr_zero(Vector{0xf000, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(13, countr_zero(Vector{0xe000, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(14, countr_zero(Vector{0xc000, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(15, countr_zero(Vector{0x8000, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(16, countr_zero(Vector{0x0000, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(17, countr_zero(Vector{0x0000, 0xfffe, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(18, countr_zero(Vector{0x0000, 0xfffc, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(19, countr_zero(Vector{0x0000, 0xfff8, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, countr_zero(Vector{0x0000, 0xfff0, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(21, countr_zero(Vector{0x0000, 0xffe0, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(22, countr_zero(Vector{0x0000, 0xffc0, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(23, countr_zero(Vector{0x0000, 0xff80, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(24, countr_zero(Vector{0x0000, 0xff00, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(25, countr_zero(Vector{0x0000, 0xfe00, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(26, countr_zero(Vector{0x0000, 0xfc00, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(27, countr_zero(Vector{0x0000, 0xf800, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(28, countr_zero(Vector{0x0000, 0xf000, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(29, countr_zero(Vector{0x0000, 0xe000, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(30, countr_zero(Vector{0x0000, 0xc000, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(31, countr_zero(Vector{0x0000, 0x8000, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(32, countr_zero(Vector{0x0000, 0x0000, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(33, countr_zero(Vector{0x0000, 0x0000, 0xfffe}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(34, countr_zero(Vector{0x0000, 0x0000, 0xfffc}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(35, countr_zero(Vector{0x0000, 0x0000, 0xfff8}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(36, countr_zero(Vector{0x0000, 0x0000, 0xfff0}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(37, countr_zero(Vector{0x0000, 0x0000, 0xffe0}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(38, countr_zero(Vector{0x0000, 0x0000, 0xffc0}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(39, countr_zero(Vector{0x0000, 0x0000, 0xff80}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(40, countr_zero(Vector{0x0000, 0x0000, 0xff00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(41, countr_zero(Vector{0x0000, 0x0000, 0xfe00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(42, countr_zero(Vector{0x0000, 0x0000, 0xfc00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(43, countr_zero(Vector{0x0000, 0x0000, 0xf800}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(44, countr_zero(Vector{0x0000, 0x0000, 0xf000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(45, countr_zero(Vector{0x0000, 0x0000, 0xe000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(46, countr_zero(Vector{0x0000, 0x0000, 0xc000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(47, countr_zero(Vector{0x0000, 0x0000, 0x8000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(48, countr_zero(Vector{0x0000, 0x0000, 0x0000}));
	}
	{
		using Vector = hamon::array<hamon::uint32_t, 4>;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(  0, countr_zero(Vector{0x00000001, 0x00000000, 0x00000000, 0x00000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 31, countr_zero(Vector{0x80000000, 0x00000000, 0x00000000, 0x00000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 32, countr_zero(Vector{0x00000000, 0x00000001, 0x00000000, 0x00000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 63, countr_zero(Vector{0x00000000, 0x80000000, 0x00000000, 0x00000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 64, countr_zero(Vector{0x00000000, 0x00000000, 0x00000001, 0x00000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 95, countr_zero(Vector{0x00000000, 0x00000000, 0x80000000, 0x00000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 96, countr_zero(Vector{0x00000000, 0x00000000, 0x00000000, 0x00000001}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(127, countr_zero(Vector{0x00000000, 0x00000000, 0x00000000, 0x80000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(128, countr_zero(Vector{0x00000000, 0x00000000, 0x00000000, 0x00000000}));
	}

	{
		using Vector = hamon::inplace_vector<hamon::uint8_t, 4>;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(32, countr_zero(Vector{0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 0, countr_zero(Vector{0x01}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 1, countr_zero(Vector{0x02}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 2, countr_zero(Vector{0x04}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 3, countr_zero(Vector{0x08}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4, countr_zero(Vector{0x10}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 5, countr_zero(Vector{0x20}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 6, countr_zero(Vector{0x40}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7, countr_zero(Vector{0x80}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 8, countr_zero(Vector{0x00, 0x01}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 9, countr_zero(Vector{0x00, 0x02}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, countr_zero(Vector{0x00, 0x04}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(11, countr_zero(Vector{0x00, 0x08}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(12, countr_zero(Vector{0x00, 0x10}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(13, countr_zero(Vector{0x00, 0x20}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(14, countr_zero(Vector{0x00, 0x40}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(15, countr_zero(Vector{0x00, 0x80}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(16, countr_zero(Vector{0x00, 0x00, 0x01}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(17, countr_zero(Vector{0x00, 0x00, 0x02}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(18, countr_zero(Vector{0x00, 0x00, 0x04}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(19, countr_zero(Vector{0x00, 0x00, 0x08}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, countr_zero(Vector{0x00, 0x00, 0x10}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(21, countr_zero(Vector{0x00, 0x00, 0x20}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(22, countr_zero(Vector{0x00, 0x00, 0x40}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(23, countr_zero(Vector{0x00, 0x00, 0x80}));
	}
	{
		using Vector = hamon::inplace_vector<hamon::uint16_t, 8>;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(128, countr_zero(Vector{0x0000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 0, countr_zero(Vector{0xffff, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 1, countr_zero(Vector{0xfffe, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 2, countr_zero(Vector{0xfffc, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 3, countr_zero(Vector{0xfff8, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 4, countr_zero(Vector{0xfff0, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 5, countr_zero(Vector{0xffe0, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 6, countr_zero(Vector{0xffc0, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 7, countr_zero(Vector{0xff80, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 8, countr_zero(Vector{0xff00, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 9, countr_zero(Vector{0xfe00, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, countr_zero(Vector{0xfc00, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(11, countr_zero(Vector{0xf800, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(12, countr_zero(Vector{0xf000, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(13, countr_zero(Vector{0xe000, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(14, countr_zero(Vector{0xc000, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(15, countr_zero(Vector{0x8000, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(16, countr_zero(Vector{0x0000, 0xffff, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(17, countr_zero(Vector{0x0000, 0xfffe, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(18, countr_zero(Vector{0x0000, 0xfffc, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(19, countr_zero(Vector{0x0000, 0xfff8, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, countr_zero(Vector{0x0000, 0xfff0, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(21, countr_zero(Vector{0x0000, 0xffe0, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(22, countr_zero(Vector{0x0000, 0xffc0, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(23, countr_zero(Vector{0x0000, 0xff80, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(24, countr_zero(Vector{0x0000, 0xff00, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(25, countr_zero(Vector{0x0000, 0xfe00, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(26, countr_zero(Vector{0x0000, 0xfc00, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(27, countr_zero(Vector{0x0000, 0xf800, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(28, countr_zero(Vector{0x0000, 0xf000, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(29, countr_zero(Vector{0x0000, 0xe000, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(30, countr_zero(Vector{0x0000, 0xc000, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(31, countr_zero(Vector{0x0000, 0x8000, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(32, countr_zero(Vector{0x0000, 0x0000, 0xffff}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(33, countr_zero(Vector{0x0000, 0x0000, 0xfffe}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(34, countr_zero(Vector{0x0000, 0x0000, 0xfffc}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(35, countr_zero(Vector{0x0000, 0x0000, 0xfff8}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(36, countr_zero(Vector{0x0000, 0x0000, 0xfff0}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(37, countr_zero(Vector{0x0000, 0x0000, 0xffe0}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(38, countr_zero(Vector{0x0000, 0x0000, 0xffc0}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(39, countr_zero(Vector{0x0000, 0x0000, 0xff80}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(40, countr_zero(Vector{0x0000, 0x0000, 0xff00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(41, countr_zero(Vector{0x0000, 0x0000, 0xfe00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(42, countr_zero(Vector{0x0000, 0x0000, 0xfc00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(43, countr_zero(Vector{0x0000, 0x0000, 0xf800}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(44, countr_zero(Vector{0x0000, 0x0000, 0xf000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(45, countr_zero(Vector{0x0000, 0x0000, 0xe000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(46, countr_zero(Vector{0x0000, 0x0000, 0xc000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(47, countr_zero(Vector{0x0000, 0x0000, 0x8000}));
	}

	{
		using Vector = hamon::inplace_vector<hamon::uint32_t, 4>;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(128, countr_zero(Vector{0x00000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(  0, countr_zero(Vector{0x00000001}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 31, countr_zero(Vector{0x80000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 32, countr_zero(Vector{0x00000000, 0x00000001}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 63, countr_zero(Vector{0x00000000, 0x80000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 64, countr_zero(Vector{0x00000000, 0x00000000, 0x00000001}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 95, countr_zero(Vector{0x00000000, 0x00000000, 0x80000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 96, countr_zero(Vector{0x00000000, 0x00000000, 0x00000000, 0x00000001}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(127, countr_zero(Vector{0x00000000, 0x00000000, 0x00000000, 0x80000000}));
	}
	{
		using Vector = hamon::inplace_vector<hamon::uint64_t, 5>;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(320, countr_zero(Vector{0}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(  0, countr_zero(Vector{1}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(  0, countr_zero(Vector{123}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(  0, countr_zero(Vector{1, 1}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(  1, countr_zero(Vector{2, 1}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ( 65, countr_zero(Vector{0, 2}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(128, countr_zero(Vector{0, 0, 1}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(195, countr_zero(Vector{0, 0, 0, 8}));
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(260, countr_zero(Vector{0, 0, 0, 0, 16}));
	}
}
