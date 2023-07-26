/**
 *	@file	unit_test_bigint_algo_multiply.cpp
 *
 *	@brief	bigint_algo::multiply のテスト
 */

#include <hamon/bigint/bigint_algo/multiply.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "constexpr_test.hpp"

GTEST_TEST(BigIntAlgoTest, MultiplyTest)
{
	{
		std::vector<hamon::uint8_t> const a{0};
		std::vector<hamon::uint8_t> const b{0};
		auto const c1 = hamon::bigint_algo::multiply(a, b);
		auto const c2 = hamon::bigint_algo::multiply(b, a);
		std::vector<hamon::uint8_t> const expected{0};
		EXPECT_EQ(c1.value, expected);
		EXPECT_EQ(c2.value, expected);
	}
	{
		std::vector<hamon::uint8_t> const a{2};
		std::vector<hamon::uint8_t> const b{3};
		auto const c1 = hamon::bigint_algo::multiply(a, b);
		auto const c2 = hamon::bigint_algo::multiply(b, a);
		std::vector<hamon::uint8_t> const expected{6};
		EXPECT_EQ(c1.value, expected);
		EXPECT_EQ(c2.value, expected);
	}
	{
		std::vector<hamon::uint8_t> const a{123};
		std::vector<hamon::uint8_t> const b{45};
		auto const c1 = hamon::bigint_algo::multiply(a, b);
		auto const c2 = hamon::bigint_algo::multiply(b, a);
		std::vector<hamon::uint8_t> const expected{0x9F, 0x15};	// 5535
		EXPECT_EQ(c1.value, expected);
		EXPECT_EQ(c2.value, expected);
	}
	{
		std::vector<hamon::uint8_t> const a{0x20, 0x10};
		std::vector<hamon::uint8_t> const b{0x40, 0x30};
		auto const c1 = hamon::bigint_algo::multiply(a, b);
		auto const c2 = hamon::bigint_algo::multiply(b, a);
		std::vector<hamon::uint8_t> const expected{0x00, 0x08, 0x0A, 0x03};
		EXPECT_EQ(c1.value, expected);
		EXPECT_EQ(c2.value, expected);
	}
	{
		std::vector<hamon::uint8_t> const a{0xB1, 0x68, 0xDE, 0x3A};	// 987654321
		std::vector<hamon::uint8_t> const b{3};
		auto const c1 = hamon::bigint_algo::multiply(a, b);
		auto const c2 = hamon::bigint_algo::multiply(b, a);
		std::vector<hamon::uint8_t> const expected{0x13, 0x3A, 0x9B, 0xB0};	// 2962962963
		EXPECT_EQ(c1.value, expected);
		EXPECT_EQ(c2.value, expected);
	}
	{
		std::vector<hamon::uint8_t> const a{0};
		std::vector<hamon::uint8_t> const b{0x10, 0x20, 0x30};
		auto const c1 = hamon::bigint_algo::multiply(a, b);
		auto const c2 = hamon::bigint_algo::multiply(b, a);
		std::vector<hamon::uint8_t> const expected{0x00};
		EXPECT_EQ(c1.value, expected);
		EXPECT_EQ(c2.value, expected);
	}
	{
		std::vector<hamon::uint8_t> const a{0xFF, 0xFF, 0xFF, 0xFF};
		std::vector<hamon::uint8_t> const b{2};
		auto const c1 = hamon::bigint_algo::multiply(a, b);
		auto const c2 = hamon::bigint_algo::multiply(b, a);
		std::vector<hamon::uint8_t> const expected{0xFE, 0xFF, 0xFF, 0xFF, 0x01};
		EXPECT_EQ(c1.value, expected);
		EXPECT_EQ(c2.value, expected);
	}
	{
		std::vector<hamon::uint8_t> const a{0x07, 0xFF, 0x88, 0x50, 0x07};	// 31415926535
		std::vector<hamon::uint8_t> const b{0xEC, 0xE3, 0x38, 0x54, 0x06};	// 27182818284
		auto const c1 = hamon::bigint_algo::multiply(a, b);
		auto const c2 = hamon::bigint_algo::multiply(b, a);
		std::vector<hamon::uint8_t> const expected{0x74, 0x4F, 0xF6, 0xCD, 0xF7, 0x0E, 0x43, 0x4B, 0x2E};	// 853973422224398765940
		EXPECT_EQ(c1.value, expected);
		EXPECT_EQ(c2.value, expected);
	}
	{
		std::vector<hamon::uint16_t> const a{0xFF07, 0x5088, 0x0007};	// 31415926535
		std::vector<hamon::uint16_t> const b{0xE3EC, 0x5438, 0x0006};	// 27182818284
		auto const c1 = hamon::bigint_algo::multiply(a, b);
		auto const c2 = hamon::bigint_algo::multiply(b, a);
		std::vector<hamon::uint16_t> const expected{0x4F74, 0xCDF6, 0x0EF7, 0x4B43, 0x002E};	// 853973422224398765940
		EXPECT_EQ(c1.value, expected);
		EXPECT_EQ(c2.value, expected);
	}
	{
		std::vector<hamon::uint32_t> const a{0x5088FF07, 0x00000007};	// 31415926535
		std::vector<hamon::uint32_t> const b{0x5438E3EC, 0x00000006};	// 27182818284
		auto const c1 = hamon::bigint_algo::multiply(a, b);
		auto const c2 = hamon::bigint_algo::multiply(b, a);
		std::vector<hamon::uint32_t> const expected{0xCDF64F74, 0x4B430EF7, 0x0000002E};	// 853973422224398765940
		EXPECT_EQ(c1.value, expected);
		EXPECT_EQ(c2.value, expected);
	}
	{
		std::vector<hamon::uint64_t> const a{0x000000075088FF07};	// 31415926535
		std::vector<hamon::uint64_t> const b{0x000000065438E3EC};	// 27182818284
		auto const c1 = hamon::bigint_algo::multiply(a, b);
		auto const c2 = hamon::bigint_algo::multiply(b, a);
		std::vector<hamon::uint64_t> const expected{0x4B430EF7CDF64F74, 0x000000000000002E};	// 853973422224398765940
		EXPECT_EQ(c1.value, expected);
		EXPECT_EQ(c2.value, expected);
	}
	{
		std::vector<hamon::uint64_t> const a{0x07D5EB5B5BA4D7C6, 0x11};	// 314159265358979323846
		std::vector<hamon::uint64_t> const b{0x000000065438E3EC};	// 27182818284
		auto const c1 = hamon::bigint_algo::multiply(a, b);
		auto const c2 = hamon::bigint_algo::multiply(b, a);
		std::vector<hamon::uint64_t> const expected{0x84D22BFBD29B7C88, 0x6BC95E95CF};	// 853973422224398765940
		EXPECT_EQ(c1.value, expected);
		EXPECT_EQ(c2.value, expected);
	}
	{
		std::vector<hamon::uint64_t> const a{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF};
		std::vector<hamon::uint64_t> const b{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF};
		auto const c1 = hamon::bigint_algo::multiply(a, b);
		auto const c2 = hamon::bigint_algo::multiply(b, a);
		std::vector<hamon::uint64_t> const expected{1, 0, 0xFFFFFFFFFFFFFFFE, 0xFFFFFFFFFFFFFFFF};
		EXPECT_EQ(c1.value, expected);
		EXPECT_EQ(c2.value, expected);
	}

	{
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint8_t, 1> a{2};
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint8_t, 1> b{3};
		HAMON_CXX14_CONSTEXPR auto c1 = hamon::bigint_algo::multiply(a, b);
		HAMON_CXX14_CONSTEXPR auto c2 = hamon::bigint_algo::multiply(b, a);
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint8_t, 1> expected{6};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(c1.value, expected);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(c2.value, expected);
	}
	{
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint8_t, 2> a{123};
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint8_t, 2> b{45};
		HAMON_CXX14_CONSTEXPR auto c1 = hamon::bigint_algo::multiply(a, b);
		HAMON_CXX14_CONSTEXPR auto c2 = hamon::bigint_algo::multiply(b, a);
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint8_t, 2> expected{0x9F, 0x15};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(c1.value, expected);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(c2.value, expected);
	}
	{
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint8_t, 2> a{0x20, 0x10};
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint8_t, 2> b{0x40, 0x30};
		HAMON_CXX14_CONSTEXPR auto c1 = hamon::bigint_algo::multiply(a, b);
		HAMON_CXX14_CONSTEXPR auto c2 = hamon::bigint_algo::multiply(b, a);
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint8_t, 2> expected{0x00, 0x08};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(c1.value, expected);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(c2.value, expected);
	}
	{
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint8_t, 4> a{0x20, 0x10};
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint8_t, 4> b{0x40, 0x30};
		HAMON_CXX14_CONSTEXPR auto c1 = hamon::bigint_algo::multiply(a, b);
		HAMON_CXX14_CONSTEXPR auto c2 = hamon::bigint_algo::multiply(b, a);
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint8_t, 4> expected{0x00, 0x08, 0x0A, 0x03};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(c1.value, expected);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(c2.value, expected);
	}
	{
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint16_t, 4> a{0x68B1, 0x3ADE};
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint16_t, 4> b{0x0003, 0x0000};
		HAMON_CXX14_CONSTEXPR auto c1 = hamon::bigint_algo::multiply(a, b);
		HAMON_CXX14_CONSTEXPR auto c2 = hamon::bigint_algo::multiply(b, a);
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint16_t, 4> expected{0x3A13, 0xB09B};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(c1.value, expected);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(c2.value, expected);
	}
	{
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint16_t, 4> a{0xFF07, 0x5088, 0x0007};
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint16_t, 4> b{0xE3EC, 0x5438, 0x0006};
		HAMON_CXX14_CONSTEXPR auto c1 = hamon::bigint_algo::multiply(a, b);
		HAMON_CXX14_CONSTEXPR auto c2 = hamon::bigint_algo::multiply(b, a);
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint16_t, 4> expected{0x4F74, 0xCDF6, 0x0EF7, 0x4B43};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(c1.value, expected);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(c2.value, expected);
	}
	{
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint32_t, 4> a{0x5088FF07, 0x00000007};
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint32_t, 4> b{0x5438E3EC, 0x00000006};
		HAMON_CXX14_CONSTEXPR auto c1 = hamon::bigint_algo::multiply(a, b);
		HAMON_CXX14_CONSTEXPR auto c2 = hamon::bigint_algo::multiply(b, a);
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint32_t, 4> expected{0xCDF64F74, 0x4B430EF7, 0x0000002E};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(c1.value, expected);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(c2.value, expected);
	}
	{
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint64_t, 4> a{0x000000075088FF07};
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint64_t, 4> b{0x000000065438E3EC};
		HAMON_CXX14_CONSTEXPR auto c1 = hamon::bigint_algo::multiply(a, b);
		HAMON_CXX14_CONSTEXPR auto c2 = hamon::bigint_algo::multiply(b, a);
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint64_t, 4> expected{0x4B430EF7CDF64F74, 0x000000000000002E};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(c1.value, expected);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(c2.value, expected);
	}
	{
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint64_t, 4> a{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF};
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint64_t, 4> b{0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF};
		HAMON_CXX14_CONSTEXPR auto c1 = hamon::bigint_algo::multiply(a, b);
		HAMON_CXX14_CONSTEXPR auto c2 = hamon::bigint_algo::multiply(b, a);
		HAMON_CXX14_CONSTEXPR hamon::array<hamon::uint64_t, 4> expected{0x0000000000000001, 0x0000000000000000, 0xFFFFFFFFFFFFFFFE, 0xFFFFFFFFFFFFFFFF};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(c1.value, expected);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(c2.value, expected);
	}
}
