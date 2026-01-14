/**
 *	@file	unit_test_bigint_algo_div_mod.cpp
 *
 *	@brief	bigint_algo::div_mod のテスト
 */

#include <hamon/bigint/bigint_algo/div_mod.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_algo_div_mod_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename VectorType>
inline HAMON_CXX14_CONSTEXPR bool
test(VectorType const& a, VectorType const& b, VectorType const& quo, VectorType const& rem)
{
	auto const c = hamon::bigint_algo::div_mod(a, b);
	VERIFY(quo == c.quo);
	VERIFY(rem == c.rem);
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
	}
	{
		using VectorType = hamon::array<hamon::uint32_t, 2>;
		HAMON_CXX14_CONSTEXPR VectorType a{0xA2294246, 0x2B992DDF};
		HAMON_CXX14_CONSTEXPR VectorType b{0x30A04975, 0x00000017};
		HAMON_CXX14_CONSTEXPR auto c = hamon::bigint_algo::div_mod(a, b);
		HAMON_CXX14_CONSTEXPR VectorType quo{0x01E14B3C};
		HAMON_CXX14_CONSTEXPR VectorType rem{0x423DC3DA, 0x00000007};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(quo, c.quo);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(rem, c.rem);
	}
	{
		using VectorType = hamon::array<hamon::uint32_t, 2>;
		HAMON_CXX14_CONSTEXPR VectorType a{0xFFFFFFFF, 0xFFFFFFFF};
		HAMON_CXX14_CONSTEXPR VectorType b{0xFFFFFFFF, 0xFFFFFFFF};
		HAMON_CXX14_CONSTEXPR auto c = hamon::bigint_algo::div_mod(a, b);
		HAMON_CXX14_CONSTEXPR VectorType quo{0x00000001};
		HAMON_CXX14_CONSTEXPR VectorType rem{0x00000000};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(quo, c.quo);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(rem, c.rem);
	}
	{
		using VectorType = hamon::array<hamon::uint32_t, 2>;
		HAMON_CXX14_CONSTEXPR VectorType a{0xFFFFFFFF, 0xFFFFFFFF};
		HAMON_CXX14_CONSTEXPR VectorType b{0xFFFFFFFE, 0xFFFFFFFF};
		HAMON_CXX14_CONSTEXPR auto c = hamon::bigint_algo::div_mod(a, b);
		HAMON_CXX14_CONSTEXPR VectorType quo{0x00000001};
		HAMON_CXX14_CONSTEXPR VectorType rem{0x00000001};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(quo, c.quo);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(rem, c.rem);
	}
	{
		using VectorType = hamon::array<hamon::uint32_t, 2>;
		HAMON_CXX14_CONSTEXPR VectorType a{0xFFFFFFFF, 0xFFFFFFFF};
		HAMON_CXX14_CONSTEXPR VectorType b{0x00000001};
		HAMON_CXX14_CONSTEXPR auto c = hamon::bigint_algo::div_mod(a, b);
		HAMON_CXX14_CONSTEXPR VectorType quo{0xFFFFFFFF, 0xFFFFFFFF};
		HAMON_CXX14_CONSTEXPR VectorType rem{0x00000000};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(quo, c.quo);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(rem, c.rem);
	}
	{
		using VectorType = hamon::array<hamon::uint32_t, 2>;
		HAMON_CXX14_CONSTEXPR VectorType a{0xFFFFFFFF, 0xFFFFFFFF};
		HAMON_CXX14_CONSTEXPR VectorType b{0x00000002};
		HAMON_CXX14_CONSTEXPR auto c = hamon::bigint_algo::div_mod(a, b);
		HAMON_CXX14_CONSTEXPR VectorType quo{0xFFFFFFFF, 0x7FFFFFFF};
		HAMON_CXX14_CONSTEXPR VectorType rem{0x00000001};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(quo, c.quo);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(rem, c.rem);
	}
	{
		using VectorType = hamon::array<hamon::uint32_t, 2>;
		HAMON_CXX14_CONSTEXPR VectorType a{0xFFFFFFFF, 0x0FFFFFFF};
		HAMON_CXX14_CONSTEXPR VectorType b{0x00000000, 0x10000000};
		HAMON_CXX14_CONSTEXPR auto c = hamon::bigint_algo::div_mod(a, b);
		HAMON_CXX14_CONSTEXPR VectorType quo{0x00000000};
		HAMON_CXX14_CONSTEXPR VectorType rem{0xFFFFFFFF, 0x0FFFFFFF};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(quo, c.quo);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(rem, c.rem);
	}

	{
		using VectorType = hamon::array<hamon::uint64_t, 2>;
		HAMON_CXX14_CONSTEXPR VectorType a{0x2B992DDFA2294246};
		HAMON_CXX14_CONSTEXPR VectorType b{0x0000001730A04975};
		HAMON_CXX14_CONSTEXPR auto c = hamon::bigint_algo::div_mod(a, b);
		HAMON_CXX14_CONSTEXPR VectorType quo{0x0000000001E14B3C};
		HAMON_CXX14_CONSTEXPR VectorType rem{0x00000007423DC3DA};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(quo, c.quo);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(rem, c.rem);
	}
	{
		using VectorType = hamon::array<hamon::uint64_t, 2>;
		HAMON_CXX14_CONSTEXPR VectorType a{0xFFFFFFFFFFFFFFFF};
		HAMON_CXX14_CONSTEXPR VectorType b{0xFFFFFFFFFFFFFFFF};
		HAMON_CXX14_CONSTEXPR auto c = hamon::bigint_algo::div_mod(a, b);
		HAMON_CXX14_CONSTEXPR VectorType quo{0x0000000000000001};
		HAMON_CXX14_CONSTEXPR VectorType rem{0x0000000000000000};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(quo, c.quo);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(rem, c.rem);
	}
	{
		using VectorType = hamon::array<hamon::uint64_t, 2>;
		HAMON_CXX14_CONSTEXPR VectorType a{0xFFFFFFFFFFFFFFFF};
		HAMON_CXX14_CONSTEXPR VectorType b{0x0000000000000001};
		HAMON_CXX14_CONSTEXPR auto c = hamon::bigint_algo::div_mod(a, b);
		HAMON_CXX14_CONSTEXPR VectorType quo{0xFFFFFFFFFFFFFFFF};
		HAMON_CXX14_CONSTEXPR VectorType rem{0x0000000000000000};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(quo, c.quo);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(rem, c.rem);
	}
	{
		using VectorType = hamon::array<hamon::uint64_t, 2>;
		HAMON_CXX14_CONSTEXPR VectorType a{0xFFFFFFFFFFFFFFFF};
		HAMON_CXX14_CONSTEXPR VectorType b{0x0000000000000002};
		HAMON_CXX14_CONSTEXPR auto c = hamon::bigint_algo::div_mod(a, b);
		HAMON_CXX14_CONSTEXPR VectorType quo{0x7FFFFFFFFFFFFFFF};
		HAMON_CXX14_CONSTEXPR VectorType rem{0x0000000000000001};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(quo, c.quo);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(rem, c.rem);
	}
	{
		using VectorType = hamon::array<hamon::uint64_t, 3>;
		HAMON_CXX14_CONSTEXPR VectorType a{0x0FFFFFFFFFFFFFFF};
		HAMON_CXX14_CONSTEXPR VectorType b{0x1000000000000000};
		HAMON_CXX14_CONSTEXPR auto c = hamon::bigint_algo::div_mod(a, b);
		HAMON_CXX14_CONSTEXPR VectorType quo{0x0000000000000000};
		HAMON_CXX14_CONSTEXPR VectorType rem{0x0FFFFFFFFFFFFFFF};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(quo, c.quo);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(rem, c.rem);
	}
	{
		using VectorType = hamon::array<hamon::uint64_t, 1>;
		HAMON_CXX14_CONSTEXPR VectorType a{0x123456789ABCDEF0};
		HAMON_CXX14_CONSTEXPR VectorType b{0x0000000000000011};
		HAMON_CXX14_CONSTEXPR auto c = hamon::bigint_algo::div_mod(a, b);
		HAMON_CXX14_CONSTEXPR VectorType quo{0x0112233445566777};
		HAMON_CXX14_CONSTEXPR VectorType rem{0x0000000000000009};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(quo, c.quo);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(rem, c.rem);
	}
}

}	// namespace bigint_algo_div_mod_test

}	// namespace hamon_bigint_test
