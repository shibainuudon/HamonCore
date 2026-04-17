/**
 *	@file	unit_test_bigint_algo_div_mod.cpp
 *
 *	@brief	bigint_algo::div_mod のテスト
 */

#include <hamon/bigint/bigint_algo/div_mod.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/inplace_vector.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "bigint_algo_test_helper.hpp"

namespace hamon_bigint_test
{

namespace bigint_algo_div_mod_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename VectorType1, typename VectorType2, typename VectorType3>
inline HAMON_CXX14_CONSTEXPR bool
test(VectorType1 const& a, VectorType2 const& b, VectorType3 const& expected_quo, VectorType3 const& expected_rem)
{
	VectorType3 quo{};
	VectorType3 rem{};
	hamon::bigint_algo::div_mod(quo, rem, a, b);
	VERIFY(quo == expected_quo);
	VERIFY(rem == expected_rem);
	{
		// a = b * quo + rem
		VectorType3 x{};
		hamon::bigint_algo::multiply(x, b, quo);
		hamon::bigint_algo::add(x, rem);
		VERIFY(hamon::bigint_algo::compare(x, a) == 0);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(BigIntAlgoTest, DivModTest)
{
#if 0
	{
		hamon::vector<hamon::uint8_t> a{0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
		hamon::vector<hamon::uint8_t> b{0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54};
		for (hamon::size_t i = 0; i < 10000; ++i)
		{
			hamon::bigint_algo::div_mod(a, b);
		}
	}
	{
		hamon::array<hamon::uint8_t, 8> a{0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0};
		hamon::array<hamon::uint8_t, 8> b{0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54};
		for (hamon::size_t i = 0; i < 10000; ++i)
		{
			hamon::bigint_algo::div_mod(a, b);
		}
	}
#endif

	// vector
	{
		using Vector = hamon::vector<hamon::uint8_t>;
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{2}, Vector{3}, Vector{0}, Vector{2}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{3}, Vector{3}, Vector{1}, Vector{0}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{4}, Vector{3}, Vector{1}, Vector{1}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xFF, 0xFF, 0xFF},
			Vector{0xFF},
			Vector{0x01, 0x01, 0x01},
			Vector{0x00}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xFF, 0xFF, 0x00, 0xFF},
			Vector{0x01},
			Vector{0xFF, 0xFF, 0x00, 0xFF},
			Vector{0x00}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x00, 0xFD, 0xFE, 0xFF},
			Vector{0x00, 0x01},
			Vector{0xFD, 0xFE, 0xFF},
			Vector{0x00}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x00, 0xFD, 0xFE, 0xFF},
			Vector{0x02},
			Vector{0x80, 0x7E, 0xFF, 0x7F},
			Vector{0x00}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x00, 0xFD, 0xFE, 0xFF},
			Vector{0x03},
			Vector{0x00, 0xFF, 0x54, 0x55},
			Vector{0x00}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x00, 0xFD, 0xFE, 0xFF},
			Vector{0x07},
			Vector{0x24, 0x24, 0x92, 0x24},
			Vector{0x04}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x00, 0x00, 0x01},
			Vector{0x01},
			Vector{0x00, 0x00, 0x01},
			Vector{0x00}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x00, 0x00, 0x01},
			Vector{0x02},
			Vector{0x00, 0x80},
			Vector{0x00}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x00, 0x00, 0x01},
			Vector{0x03},
			Vector{0x55, 0x55},
			Vector{0x01}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x00, 0x00, 0x01},
			Vector{0x00, 0x01},
			Vector{0x00, 0x01},
			Vector{0x00}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x00, 0x00, 0x01},
			Vector{0x00, 0x02},
			Vector{0x80},
			Vector{0x00}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x00, 0x00, 0x01},
			Vector{0x00, 0x03},
			Vector{0x55},
			Vector{0x00, 0x01}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xD2, 0x02, 0x96, 0x49},
			Vector{0x82, 0x09},
			Vector{0x51, 0xBD, 0x07},
			Vector{0xB0, 0x06}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x8E, 0x1F, 0x24, 0xF3, 0xF5, 0x10, 0x22, 0x11},
			Vector{0xDC, 0x73, 0x61, 0x08},
			Vector{0xEA, 0xD5, 0x5A, 0x0B, 0x02},
			Vector{0x76, 0x2C, 0x52, 0x05}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F},
			Vector{0x13},
			Vector{0x1A, 0xCA, 0x6B, 0x28, 0xAF, 0xA1, 0xBC, 0x06},
			Vector{0x11}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x46, 0x42, 0x29, 0xA2, 0xDF, 0x2D, 0x99, 0x2B},
			Vector{0x75, 0x49, 0xA0, 0x30, 0x17},
			Vector{0x3C, 0x4B, 0xE1, 0x01},
			Vector{0xDA, 0xC3, 0x3D, 0x42, 0x07}));
	}
	{
		using Vector = hamon::vector<hamon::uint16_t>;
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{2}, Vector{3}, Vector{0}, Vector{2}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{3}, Vector{3}, Vector{1}, Vector{0}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{4}, Vector{3}, Vector{1}, Vector{1}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xFFFF, 0x00FF},
			Vector{0x00FF},
			Vector{0x0101, 0x0001},
			Vector{0x0000}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x1F8E, 0xF324, 0x10F5, 0x1122},
			Vector{0x73DC, 0x0861},
			Vector{0xD5EA, 0x0B5A, 0x0002},
			Vector{0x2C76, 0x0552}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xFFFF, 0xFFFF, 0xFFFF, 0x7FFF},
			Vector{0x0013},
			Vector{0xCA1A, 0x286B, 0xA1AF, 0x06BC},
			Vector{0x0011}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x4246, 0xA229, 0x2DDF, 0x2B99},
			Vector{0x4975, 0x30A0, 0x0017},
			Vector{0x4B3C, 0x01E1},
			Vector{0xC3DA, 0x423D, 0x0007}));
	}
	{
		using Vector = hamon::vector<hamon::uint32_t>;
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{2}, Vector{3}, Vector{0}, Vector{2}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{3}, Vector{3}, Vector{1}, Vector{0}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{4}, Vector{3}, Vector{1}, Vector{1}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xF3241F8E, 0x112210F5},
			Vector{0x086173DC},
			Vector{0x0B5AD5EA, 0x00000002},
			Vector{0x05522C76}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xFFFFFFFF, 0x7FFFFFFF},
			Vector{0x00000013},
			Vector{0x286BCA1A, 0x06BCA1AF},
			Vector{0x00000011}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xA2294246, 0x2B992DDF},
			Vector{0x30A04975, 0x00000017},
			Vector{0x01E14B3C},
			Vector{0x423DC3DA, 0x00000007}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
			Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
			Vector{0x00000001},
			Vector{0x00000000}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
			Vector{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF},
			Vector{0x00000001},
			Vector{0x00000001}));
	}
	{
		using Vector = hamon::vector<hamon::uint64_t>;
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{2}, Vector{3}, Vector{0}, Vector{2}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{3}, Vector{3}, Vector{1}, Vector{0}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector{4}, Vector{3}, Vector{1}, Vector{1}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x112210F5F3241F8E},
			Vector{0x00000000086173DC},
			Vector{0x000000020B5AD5EA},
			Vector{0x0000000005522C76}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x7FFFFFFFFFFFFFFF},
			Vector{0x0000000000000013},
			Vector{0x06BCA1AF286BCA1A},
			Vector{0x0000000000000011}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x2B992DDFA2294246},
			Vector{0x0000001730A04975},
			Vector{0x0000000001E14B3C},
			Vector{0x00000007423DC3DA}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x123456789ABCDEF0},
			Vector{0x0000000000000011},
			Vector{0x0112233445566777},
			Vector{0x0000000000000009}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF},
			Vector{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF},
			Vector{0x0000000000000001},
			Vector{0x0000000000000000}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF},
			Vector{0xFFFFFFFFFFFFFFFE, 0xFFFFFFFFFFFFFFFF},
			Vector{0x0000000000000001},
			Vector{0x0000000000000001}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF},
			Vector{0x0000000000000001},
			Vector{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF},
			Vector{0x0000000000000000}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xFFFFFFFFFFFFFFFE, 0xFFFFFFFFFFFFFFFF},
			Vector{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF},
			Vector{0x0000000000000000},
			Vector{0xFFFFFFFFFFFFFFFE, 0xFFFFFFFFFFFFFFFF}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x5ed0000040000000, 0x000002a5a058fc29},
			Vector{0x000878678326eac9},
			Vector{0x0050000000000000},
			Vector{0x0000000040000000}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xdaff78c1038e38e3, 0x55e92943d6c1640e, 0x0000000000947ca7},
			Vector{0x140c16b7c528f679, 0x00000002deaf189c},
			Vector{0x0033bd7a038e38e3},
			Vector{0x60787e6618333398, 0x0000000198286301}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x46b3d70b81c71c71, 0x051a1ad66ace4e61},
			Vector{0x140c16b7c528f679, 0x00000002deaf189c},
			Vector{0x0000000001c71c71},
			Vector{0xba424a8eeeae1508, 0x000000023b6bbdce}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x1000000000000000, 0x0000000000000002},
			Vector{0x0000000000000c35},
			Vector{0x002b40f66a550870},
			Vector{0x00000000000000d0}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x0000000000000000, 0x0352f60000000000, 0x000000000000000e},
			Vector{0xf18376a85901bd69, 0x00000701a97b150c},
			Vector{0x0000000001ffffff},
			Vector{0xa0d1732d8701bd69, 0x000006d78f980e1f}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x0000000000000000, 0x0000000000000000, 0x0000000000000002},
			Vector{0xc9e717bb45005915, 0x00000166bb7f0435},
			Vector{0x00000000016d601a},
			Vector{0xff9ffb9bd99e13de, 0x0000012852d48855}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x9e3779b97f4a7c15, 0xbf58476d1ce4e5b9, 0x94d049bb133111eb},
			Vector{0x0000000000000123},
			Vector{0x6afd8d2c9faaec31, 0x1321bba07c23f9c0, 0x0082ea429f4bd332},
			Vector{0x0000000000000062}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x3acfa029e3cc6041, 0xf5b6515bf2ee419c, 0x1259635894a29b61, 0x0b6ae75395f8ebd6, 0x225622285ce302e2},
			Vector{0xffffffffffffffff, 0x0000000000000001},
			Vector{0xc3044091172d154f, 0x90522fc63b6be902, 0xe4afc33e23536a3, 0x112b11142e718171},
			Vector{0xfdd3e0bafaf97590}));
	}

	// inplace_vector
	{
		using Vector = hamon::inplace_vector<hamon::uint8_t, 8>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{2}, Vector{3}, Vector{0}, Vector{2}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{3}, Vector{3}, Vector{1}, Vector{0}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{4}, Vector{3}, Vector{1}, Vector{1}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xFF, 0xFF, 0xFF},
			Vector{0xFF},
			Vector{0x01, 0x01, 0x01},
			Vector{0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xFF, 0xFF, 0x00, 0xFF},
			Vector{0x01},
			Vector{0xFF, 0xFF, 0x00, 0xFF},
			Vector{0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x00, 0xFD, 0xFE, 0xFF},
			Vector{0x00, 0x01},
			Vector{0xFD, 0xFE, 0xFF},
			Vector{0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x00, 0xFD, 0xFE, 0xFF},
			Vector{0x02},
			Vector{0x80, 0x7E, 0xFF, 0x7F},
			Vector{0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x00, 0xFD, 0xFE, 0xFF},
			Vector{0x03},
			Vector{0x00, 0xFF, 0x54, 0x55},
			Vector{0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x00, 0xFD, 0xFE, 0xFF},
			Vector{0x07},
			Vector{0x24, 0x24, 0x92, 0x24},
			Vector{0x04}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x00, 0x00, 0x01},
			Vector{0x01},
			Vector{0x00, 0x00, 0x01},
			Vector{0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x00, 0x00, 0x01},
			Vector{0x02},
			Vector{0x00, 0x80},
			Vector{0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x00, 0x00, 0x01},
			Vector{0x03},
			Vector{0x55, 0x55},
			Vector{0x01}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x00, 0x00, 0x01},
			Vector{0x00, 0x01},
			Vector{0x00, 0x01},
			Vector{0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x00, 0x00, 0x01},
			Vector{0x00, 0x02},
			Vector{0x80},
			Vector{0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x00, 0x00, 0x01},
			Vector{0x00, 0x03},
			Vector{0x55},
			Vector{0x00, 0x01}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xD2, 0x02, 0x96, 0x49},
			Vector{0x82, 0x09},
			Vector{0x51, 0xBD, 0x07},
			Vector{0xB0, 0x06}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x8E, 0x1F, 0x24, 0xF3, 0xF5, 0x10, 0x22, 0x11},
			Vector{0xDC, 0x73, 0x61, 0x08},
			Vector{0xEA, 0xD5, 0x5A, 0x0B, 0x02},
			Vector{0x76, 0x2C, 0x52, 0x05}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F},
			Vector{0x13},
			Vector{0x1A, 0xCA, 0x6B, 0x28, 0xAF, 0xA1, 0xBC, 0x06},
			Vector{0x11}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x46, 0x42, 0x29, 0xA2, 0xDF, 0x2D, 0x99, 0x2B},
			Vector{0x75, 0x49, 0xA0, 0x30, 0x17},
			Vector{0x3C, 0x4B, 0xE1, 0x01},
			Vector{0xDA, 0xC3, 0x3D, 0x42, 0x07}));
	}
	{
		using Vector = hamon::inplace_vector<hamon::uint16_t, 4>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{2}, Vector{3}, Vector{0}, Vector{2}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{3}, Vector{3}, Vector{1}, Vector{0}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{4}, Vector{3}, Vector{1}, Vector{1}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xFFFF, 0x00FF},
			Vector{0x00FF},
			Vector{0x0101, 0x0001},
			Vector{0x0000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x1F8E, 0xF324, 0x10F5, 0x1122},
			Vector{0x73DC, 0x0861},
			Vector{0xD5EA, 0x0B5A, 0x0002},
			Vector{0x2C76, 0x0552}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xFFFF, 0xFFFF, 0xFFFF, 0x7FFF},
			Vector{0x0013},
			Vector{0xCA1A, 0x286B, 0xA1AF, 0x06BC},
			Vector{0x0011}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x4246, 0xA229, 0x2DDF, 0x2B99},
			Vector{0x4975, 0x30A0, 0x0017},
			Vector{0x4B3C, 0x01E1},
			Vector{0xC3DA, 0x423D, 0x0007}));
	}
	{
		using Vector = hamon::inplace_vector<hamon::uint32_t, 3>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{2}, Vector{3}, Vector{0}, Vector{2}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{3}, Vector{3}, Vector{1}, Vector{0}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{4}, Vector{3}, Vector{1}, Vector{1}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xF3241F8E, 0x112210F5},
			Vector{0x086173DC},
			Vector{0x0B5AD5EA, 0x00000002},
			Vector{0x05522C76}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xFFFFFFFF, 0x7FFFFFFF},
			Vector{0x00000013},
			Vector{0x286BCA1A, 0x06BCA1AF},
			Vector{0x00000011}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xA2294246, 0x2B992DDF},
			Vector{0x30A04975, 0x00000017},
			Vector{0x01E14B3C},
			Vector{0x423DC3DA, 0x00000007}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
			Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
			Vector{0x00000001},
			Vector{0x00000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
			Vector{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF},
			Vector{0x00000001},
			Vector{0x00000001}));
	}

	// array
	{
		using VectorType = hamon::array<hamon::uint32_t, 2>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			VectorType{0xA2294246, 0x2B992DDF},
			VectorType{0x30A04975, 0x00000017},
			VectorType{0x01E14B3C},
			VectorType{0x423DC3DA, 0x00000007}));
	}
	{
		using VectorType = hamon::array<hamon::uint32_t, 2>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			VectorType{0xFFFFFFFF, 0xFFFFFFFF},
			VectorType{0xFFFFFFFF, 0xFFFFFFFF},
			VectorType{0x00000001},
			VectorType{0x00000000}));
	}
	{
		using VectorType = hamon::array<hamon::uint32_t, 2>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			VectorType{0xFFFFFFFF, 0xFFFFFFFF},
			VectorType{0xFFFFFFFE, 0xFFFFFFFF},
			VectorType{0x00000001},
			VectorType{0x00000001}));
	}
	{
		using VectorType = hamon::array<hamon::uint32_t, 2>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			VectorType{0xFFFFFFFF, 0xFFFFFFFF},
			VectorType{0x00000001},
			VectorType{0xFFFFFFFF, 0xFFFFFFFF},
			VectorType{0x00000000}));
	}
	{
		using VectorType = hamon::array<hamon::uint32_t, 2>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			VectorType{0xFFFFFFFF, 0xFFFFFFFF},
			VectorType{0x00000002},
			VectorType{0xFFFFFFFF, 0x7FFFFFFF},
			VectorType{0x00000001}));
	}
	{
		using VectorType = hamon::array<hamon::uint32_t, 2>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			VectorType{0xFFFFFFFF, 0x0FFFFFFF},
			VectorType{0x00000000, 0x10000000},
			VectorType{0x00000000},
			VectorType{0xFFFFFFFF, 0x0FFFFFFF}));
	}

	{
		using VectorType = hamon::array<hamon::uint64_t, 2>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			VectorType{0x2B992DDFA2294246},
			VectorType{0x0000001730A04975},
			VectorType{0x0000000001E14B3C},
			VectorType{0x00000007423DC3DA}));
	}
	{
		using VectorType = hamon::array<hamon::uint64_t, 2>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			VectorType{0xFFFFFFFFFFFFFFFF},
			VectorType{0xFFFFFFFFFFFFFFFF},
			VectorType{0x0000000000000001},
			VectorType{0x0000000000000000}));
	}
	{
		using VectorType = hamon::array<hamon::uint64_t, 2>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			VectorType{0xFFFFFFFFFFFFFFFF},
			VectorType{0x0000000000000001},
			VectorType{0xFFFFFFFFFFFFFFFF},
			VectorType{0x0000000000000000}));
	}
	{
		using VectorType = hamon::array<hamon::uint64_t, 2>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			VectorType{0xFFFFFFFFFFFFFFFF},
			VectorType{0x0000000000000002},
			VectorType{0x7FFFFFFFFFFFFFFF},
			VectorType{0x0000000000000001}));
	}
	{
		using VectorType = hamon::array<hamon::uint64_t, 3>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			VectorType{0x0FFFFFFFFFFFFFFF},
			VectorType{0x1000000000000000},
			VectorType{0x0000000000000000},
			VectorType{0x0FFFFFFFFFFFFFFF}));
	}
	{
		using VectorType = hamon::array<hamon::uint64_t, 1>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			VectorType{0x123456789ABCDEF0},
			VectorType{0x0000000000000011},
			VectorType{0x0112233445566777},
			VectorType{0x0000000000000009}));
	}

	{
		using Vector1 = hamon::vector<hamon::uint8_t>;
		using Vector2 = hamon::inplace_vector<hamon::uint8_t, 8>;
		using Vector3 = hamon::array<hamon::uint8_t, 8>;

		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector1{2}, Vector2{3}, Vector3{0}, Vector3{2}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector1{3}, Vector2{3}, Vector3{1}, Vector3{0}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector1{4}, Vector2{3}, Vector3{1}, Vector3{1}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector1{0xFF, 0xFF, 0xFF},
			Vector2{0xFF},
			Vector3{0x01, 0x01, 0x01},
			Vector3{0x00}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector1{0x46, 0x42, 0x29, 0xA2, 0xDF, 0x2D, 0x99, 0x2B},
			Vector2{0x75, 0x49, 0xA0, 0x30, 0x17},
			Vector3{0x3C, 0x4B, 0xE1, 0x01},
			Vector3{0xDA, 0xC3, 0x3D, 0x42, 0x07}));
	}
	{
		using Vector1 = hamon::inplace_vector<hamon::uint16_t, 4>;
		using Vector2 = hamon::array<hamon::uint16_t, 7>;
		using Vector3 = hamon::vector<hamon::uint16_t>;
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector1{2}, Vector2{3}, Vector3{0}, Vector3{2}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector1{3}, Vector2{3}, Vector3{1}, Vector3{0}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector1{4}, Vector2{3}, Vector3{1}, Vector3{1}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector1{0xFFFF, 0x00FF},
			Vector2{0x00FF},
			Vector3{0x0101, 0x0001},
			Vector3{0x0000}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector1{0x1F8E, 0xF324, 0x10F5, 0x1122},
			Vector2{0x73DC, 0x0861},
			Vector3{0xD5EA, 0x0B5A, 0x0002},
			Vector3{0x2C76, 0x0552}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector1{0xFFFF, 0xFFFF, 0xFFFF, 0x7FFF},
			Vector2{0x0013},
			Vector3{0xCA1A, 0x286B, 0xA1AF, 0x06BC},
			Vector3{0x0011}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector1{0x4246, 0xA229, 0x2DDF, 0x2B99},
			Vector2{0x4975, 0x30A0, 0x0017},
			Vector3{0x4B3C, 0x01E1},
			Vector3{0xC3DA, 0x423D, 0x0007}));
	}
	{
		using Vector1 = hamon::array<hamon::uint32_t, 3>;
		using Vector2 = hamon::vector<hamon::uint32_t>;
		using Vector3 = hamon::inplace_vector<hamon::uint32_t, 3>;
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector1{2}, Vector2{3}, Vector3{0}, Vector3{2}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector1{3}, Vector2{3}, Vector3{1}, Vector3{0}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(Vector1{4}, Vector2{3}, Vector3{1}, Vector3{1}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector1{0xF3241F8E, 0x112210F5},
			Vector2{0x086173DC},
			Vector3{0x0B5AD5EA, 0x00000002},
			Vector3{0x05522C76}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector1{0xFFFFFFFF, 0x7FFFFFFF},
			Vector2{0x00000013},
			Vector3{0x286BCA1A, 0x06BCA1AF},
			Vector3{0x00000011}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector1{0xA2294246, 0x2B992DDF},
			Vector2{0x30A04975, 0x00000017},
			Vector3{0x01E14B3C},
			Vector3{0x423DC3DA, 0x00000007}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector1{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
			Vector2{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
			Vector3{0x00000001},
			Vector3{0x00000000}));
		HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test(
			Vector1{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
			Vector2{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF},
			Vector3{0x00000001},
			Vector3{0x00000001}));
	}

	// MyVector
	{
		using Vector = MyVector<hamon::uint16_t, 4>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{2}, Vector{3}, Vector{0}, Vector{2}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{3}, Vector{3}, Vector{1}, Vector{0}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{4}, Vector{3}, Vector{1}, Vector{1}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xFFFF, 0x00FF},
			Vector{0x00FF},
			Vector{0x0101, 0x0001},
			Vector{0x0000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x1F8E, 0xF324, 0x10F5, 0x1122},
			Vector{0x73DC, 0x0861},
			Vector{0xD5EA, 0x0B5A, 0x0002},
			Vector{0x2C76, 0x0552}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xFFFF, 0xFFFF, 0xFFFF, 0x7FFF},
			Vector{0x0013},
			Vector{0xCA1A, 0x286B, 0xA1AF, 0x06BC},
			Vector{0x0011}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0x4246, 0xA229, 0x2DDF, 0x2B99},
			Vector{0x4975, 0x30A0, 0x0017},
			Vector{0x4B3C, 0x01E1},
			Vector{0xC3DA, 0x423D, 0x0007}));
	}
	{
		using Vector = MyVector<hamon::uint32_t, 10>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{2}, Vector{3}, Vector{0}, Vector{2}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{3}, Vector{3}, Vector{1}, Vector{0}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(Vector{4}, Vector{3}, Vector{1}, Vector{1}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xF3241F8E, 0x112210F5},
			Vector{0x086173DC},
			Vector{0x0B5AD5EA, 0x00000002},
			Vector{0x05522C76}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xFFFFFFFF, 0x7FFFFFFF},
			Vector{0x00000013},
			Vector{0x286BCA1A, 0x06BCA1AF},
			Vector{0x00000011}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xA2294246, 0x2B992DDF},
			Vector{0x30A04975, 0x00000017},
			Vector{0x01E14B3C},
			Vector{0x423DC3DA, 0x00000007}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
			Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
			Vector{0x00000001},
			Vector{0x00000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test(
			Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF},
			Vector{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF},
			Vector{0x00000001},
			Vector{0x00000001}));
	}
}

}	// namespace bigint_algo_div_mod_test

}	// namespace hamon_bigint_test
