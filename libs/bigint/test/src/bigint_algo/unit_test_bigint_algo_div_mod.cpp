/**
 *	@file	unit_test_bigint_algo_div_mod.cpp
 *
 *	@brief	bigint_algo::div_mod のテスト
 */

#include <hamon/bigint/bigint_algo/div_mod.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

GTEST_TEST(BigIntAlgoTest, DivModTest)
{
	{
		std::vector<hamon::uint8_t> const a{2};
		std::vector<hamon::uint8_t> const b{3};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint8_t> const quo{0};
		std::vector<hamon::uint8_t> const rem{2};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint8_t> const a{3};
		std::vector<hamon::uint8_t> const b{3};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint8_t> const quo{1};
		std::vector<hamon::uint8_t> const rem{0};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint8_t> const a{4};
		std::vector<hamon::uint8_t> const b{3};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint8_t> const quo{1};
		std::vector<hamon::uint8_t> const rem{1};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint8_t> const a{0xFF, 0xFF, 0xFF};
		std::vector<hamon::uint8_t> const b{0xFF};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint8_t> const quo{0x01, 0x01, 0x01};
		std::vector<hamon::uint8_t> const rem{0x00};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint8_t> const a{0xFF, 0xFF, 0x00, 0xFF};
		std::vector<hamon::uint8_t> const b{0x01};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint8_t> const quo{0xFF, 0xFF, 0x00, 0xFF};
		std::vector<hamon::uint8_t> const rem{0x00};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint8_t> const a{0x00, 0xFD, 0xFE, 0xFF};
		std::vector<hamon::uint8_t> const b{0x00, 0x01};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint8_t> const quo{0xFD, 0xFE, 0xFF};
		std::vector<hamon::uint8_t> const rem{0x00};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint8_t> const a{0x00, 0xFD, 0xFE, 0xFF};
		std::vector<hamon::uint8_t> const b{0x02};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint8_t> const quo{0x80, 0x7E, 0xFF, 0x7F};
		std::vector<hamon::uint8_t> const rem{0x00};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint8_t> const a{0x00, 0xFD, 0xFE, 0xFF};
		std::vector<hamon::uint8_t> const b{0x03};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint8_t> const quo{0x00, 0xFF, 0x54, 0x55};
		std::vector<hamon::uint8_t> const rem{0x00};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint8_t> const a{0x00, 0xFD, 0xFE, 0xFF};
		std::vector<hamon::uint8_t> const b{0x07};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint8_t> const quo{0x24, 0x24, 0x92, 0x24};
		std::vector<hamon::uint8_t> const rem{0x04};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint8_t> const a{0x00, 0x00, 0x01};
		std::vector<hamon::uint8_t> const b{0x01};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint8_t> const quo{0x00, 0x00, 0x01};
		std::vector<hamon::uint8_t> const rem{0x00};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint8_t> const a{0x00, 0x00, 0x01};
		std::vector<hamon::uint8_t> const b{0x02};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint8_t> const quo{0x00, 0x80};
		std::vector<hamon::uint8_t> const rem{0x00};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint8_t> const a{0x00, 0x00, 0x01};
		std::vector<hamon::uint8_t> const b{0x03};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint8_t> const quo{0x55, 0x55};
		std::vector<hamon::uint8_t> const rem{0x01};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint8_t> const a{0x00, 0x00, 0x01};
		std::vector<hamon::uint8_t> const b{0x00, 0x01};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint8_t> const quo{0x00, 0x01};
		std::vector<hamon::uint8_t> const rem{0x00};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint8_t> const a{0x00, 0x00, 0x01};
		std::vector<hamon::uint8_t> const b{0x00, 0x02};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint8_t> const quo{0x80};
		std::vector<hamon::uint8_t> const rem{0x00};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint8_t> const a{0x00, 0x00, 0x01};
		std::vector<hamon::uint8_t> const b{0x00, 0x03};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint8_t> const quo{0x55};
		std::vector<hamon::uint8_t> const rem{0x00, 0x01};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint8_t> const a{0xD2, 0x02, 0x96, 0x49};
		std::vector<hamon::uint8_t> const b{0x82, 0x09};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint8_t> const quo{0x51, 0xBD, 0x07};
		std::vector<hamon::uint8_t> const rem{0xB0, 0x06};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint8_t> const a{0x8E, 0x1F, 0x24, 0xF3, 0xF5, 0x10, 0x22, 0x11};
		std::vector<hamon::uint8_t> const b{0xDC, 0x73, 0x61, 0x08};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint8_t> const quo{0xEA, 0xD5, 0x5A, 0x0B, 0x02};
		std::vector<hamon::uint8_t> const rem{0x76, 0x2C, 0x52, 0x05};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint8_t> const a{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F};
		std::vector<hamon::uint8_t> const b{0x13};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint8_t> const quo{0x1A, 0xCA, 0x6B, 0x28, 0xAF, 0xA1, 0xBC, 0x06};
		std::vector<hamon::uint8_t> const rem{0x11};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint8_t> const a{0x46, 0x42, 0x29, 0xA2, 0xDF, 0x2D, 0x99, 0x2B};
		std::vector<hamon::uint8_t> const b{0x75, 0x49, 0xA0, 0x30, 0x17};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint8_t> const quo{0x3C, 0x4B, 0xE1, 0x01};
		std::vector<hamon::uint8_t> const rem{0xDA, 0xC3, 0x3D, 0x42, 0x07};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint16_t> const a{2};
		std::vector<hamon::uint16_t> const b{3};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint16_t> const quo{0};
		std::vector<hamon::uint16_t> const rem{2};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint16_t> const a{3};
		std::vector<hamon::uint16_t> const b{3};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint16_t> const quo{1};
		std::vector<hamon::uint16_t> const rem{0};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint16_t> const a{4};
		std::vector<hamon::uint16_t> const b{3};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint16_t> const quo{1};
		std::vector<hamon::uint16_t> const rem{1};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint16_t> const a{0xFFFF, 0x00FF};
		std::vector<hamon::uint16_t> const b{0xFF};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint16_t> const quo{0x0101, 0x0001};
		std::vector<hamon::uint16_t> const rem{0x00};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint16_t> const a{0x1F8E, 0xF324, 0x10F5, 0x1122};
		std::vector<hamon::uint16_t> const b{0x73DC, 0x0861};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint16_t> const quo{0xD5EA, 0x0B5A, 0x0002};
		std::vector<hamon::uint16_t> const rem{0x2C76, 0x0552};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint16_t> const a{0xFFFF, 0xFFFF, 0xFFFF, 0x7FFF};
		std::vector<hamon::uint16_t> const b{0x0013};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint16_t> const quo{0xCA1A, 0x286B, 0xA1AF, 0x06BC};
		std::vector<hamon::uint16_t> const rem{0x0011};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint16_t> const a{0x4246, 0xA229, 0x2DDF, 0x2B99};
		std::vector<hamon::uint16_t> const b{0x4975, 0x30A0, 0x0017};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint16_t> const quo{0x4B3C, 0x01E1};
		std::vector<hamon::uint16_t> const rem{0xC3DA, 0x423D, 0x0007};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint32_t> const a{2};
		std::vector<hamon::uint32_t> const b{3};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint32_t> const quo{0};
		std::vector<hamon::uint32_t> const rem{2};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint32_t> const a{3};
		std::vector<hamon::uint32_t> const b{3};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint32_t> const quo{1};
		std::vector<hamon::uint32_t> const rem{0};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint32_t> const a{4};
		std::vector<hamon::uint32_t> const b{3};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint32_t> const quo{1};
		std::vector<hamon::uint32_t> const rem{1};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint32_t> const a{0xF3241F8E, 0x112210F5};
		std::vector<hamon::uint32_t> const b{0x086173DC};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint32_t> const quo{0x0B5AD5EA, 0x00000002};
		std::vector<hamon::uint32_t> const rem{0x05522C76};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint32_t> const a{0xFFFFFFFF, 0x7FFFFFFF};
		std::vector<hamon::uint32_t> const b{0x00000013};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint32_t> const quo{0x286BCA1A, 0x06BCA1AF};
		std::vector<hamon::uint32_t> const rem{0x00000011};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint32_t> const a{0xA2294246, 0x2B992DDF};
		std::vector<hamon::uint32_t> const b{0x30A04975, 0x00000017};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint32_t> const quo{0x01E14B3C};
		std::vector<hamon::uint32_t> const rem{0x423DC3DA, 0x00000007};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint32_t> const a{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
		std::vector<hamon::uint32_t> const b{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint32_t> const quo{0x00000001};
		std::vector<hamon::uint32_t> const rem{0x00000000};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint32_t> const a{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
		std::vector<hamon::uint32_t> const b{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint32_t> const quo{0x00000001};
		std::vector<hamon::uint32_t> const rem{0x00000001};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint64_t> const a{2};
		std::vector<hamon::uint64_t> const b{3};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint64_t> const quo{0};
		std::vector<hamon::uint64_t> const rem{2};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint64_t> const a{3};
		std::vector<hamon::uint64_t> const b{3};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint64_t> const quo{1};
		std::vector<hamon::uint64_t> const rem{0};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint64_t> const a{4};
		std::vector<hamon::uint64_t> const b{3};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint64_t> const quo{1};
		std::vector<hamon::uint64_t> const rem{1};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint64_t> const a{0x112210F5F3241F8E};
		std::vector<hamon::uint64_t> const b{0x00000000086173DC};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint64_t> const quo{0x000000020B5AD5EA};
		std::vector<hamon::uint64_t> const rem{0x0000000005522C76};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint64_t> const a{0x7FFFFFFFFFFFFFFF};
		std::vector<hamon::uint64_t> const b{0x0000000000000013};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint64_t> const quo{0x06BCA1AF286BCA1A};
		std::vector<hamon::uint64_t> const rem{0x0000000000000011};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		std::vector<hamon::uint64_t> const a{0x2B992DDFA2294246};
		std::vector<hamon::uint64_t> const b{0x0000001730A04975};
		auto const c = hamon::bigint_algo::div_mod(a, b);
		std::vector<hamon::uint64_t> const quo{0x0000000001E14B3C};
		std::vector<hamon::uint64_t> const rem{0x00000007423DC3DA};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}
	{
		using VectorType = std::vector<hamon::uint64_t>;
		VectorType const a{0x123456789ABCDEF0};
		VectorType const b{0x0000000000000011};
		auto c = hamon::bigint_algo::div_mod(a, b);
		VectorType const quo{0x0112233445566777};
		VectorType const rem{0x0000000000000009};
		EXPECT_EQ(quo, c.quo);
		EXPECT_EQ(rem, c.rem);
	}

	// TODO CXX11_CONSTEXPR

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
