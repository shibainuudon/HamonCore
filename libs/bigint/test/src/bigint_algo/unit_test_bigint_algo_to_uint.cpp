/**
 *	@file	unit_test_bigint_algo_to_uint.cpp
 *
 *	@brief	bigint_algo::to_uint のテスト
 */

#include <hamon/bigint/bigint_algo/to_uint.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_algo_to_uint_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename VectorType, typename UInt>
inline HAMON_CXX14_CONSTEXPR bool
ToUIntTest(VectorType const& vec, UInt expected)
{
	UInt value{0xCC};
	auto ret = hamon::bigint_algo::to_uint(value, vec);
	VERIFY(value == expected);
	VERIFY(ret.ec == std::errc{});
	return true;
}

template <typename UInt, typename VectorType>
inline HAMON_CXX14_CONSTEXPR bool
ToUIntErrorCodeTest(VectorType const& vec, std::errc ec)
{
	UInt value{0xCC};
	auto ret = hamon::bigint_algo::to_uint(value, vec);
	VERIFY(ret.ec == ec);
	return true;
}

GTEST_TEST(BigIntAlgoTest, ToUIntTest)
{
	{
		using Vector = hamon::vector<hamon::uint8_t>;
		EXPECT_TRUE(ToUIntTest(Vector{0x00},                                           hamon::uint8_t{0x00}));
		EXPECT_TRUE(ToUIntTest(Vector{0x12},                                           hamon::uint8_t{0x12}));
		EXPECT_TRUE(ToUIntTest(Vector{0x00},                                           hamon::uint16_t{0x0000}));
		EXPECT_TRUE(ToUIntTest(Vector{0x34, 0x12},                                     hamon::uint16_t{0x1234}));
		EXPECT_TRUE(ToUIntTest(Vector{0x00},                                           hamon::uint32_t{0x00000000}));
		EXPECT_TRUE(ToUIntTest(Vector{0x78, 0x56, 0x34, 0x12},                         hamon::uint32_t{0x12345678}));
		EXPECT_TRUE(ToUIntTest(Vector{0x00},                                           hamon::uint64_t{0x0000000000000000}));
		EXPECT_TRUE(ToUIntTest(Vector{0xF0, 0xDE, 0xBC, 0x9A, 0x78, 0x56, 0x34, 0x12}, hamon::uint64_t{0x123456789ABCDEF0}));
		EXPECT_TRUE(ToUIntTest(Vector{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, hamon::uint64_t{0xFFFFFFFFFFFFFFFF}));
	}
	{
		using Vector = hamon::vector<hamon::uint16_t>;
		EXPECT_TRUE(ToUIntTest(Vector{0x0000},                         hamon::uint8_t{0x00}));
		EXPECT_TRUE(ToUIntTest(Vector{0x0012},                         hamon::uint8_t{0x12}));
		EXPECT_TRUE(ToUIntTest(Vector{0x0000},                         hamon::uint16_t{0x0000}));
		EXPECT_TRUE(ToUIntTest(Vector{0x1234},                         hamon::uint16_t{0x1234}));
		EXPECT_TRUE(ToUIntTest(Vector{0x0000},                         hamon::uint32_t{0x00000000}));
		EXPECT_TRUE(ToUIntTest(Vector{0x5678, 0x1234},                 hamon::uint32_t{0x12345678}));
		EXPECT_TRUE(ToUIntTest(Vector{0x0000},                         hamon::uint64_t{0x0000000000000000}));
		EXPECT_TRUE(ToUIntTest(Vector{0xDEF0, 0x9ABC, 0x5678, 0x1234}, hamon::uint64_t{0x123456789ABCDEF0}));
		EXPECT_TRUE(ToUIntTest(Vector{0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF}, hamon::uint64_t{0xFFFFFFFFFFFFFFFF}));
	}
	{
		using Vector = hamon::vector<hamon::uint32_t>;
		EXPECT_TRUE(ToUIntTest(Vector{0x00000000},             hamon::uint8_t{0x00}));
		EXPECT_TRUE(ToUIntTest(Vector{0x00000012},             hamon::uint8_t{0x12}));
		EXPECT_TRUE(ToUIntTest(Vector{0x00000000},             hamon::uint16_t{0x0000}));
		EXPECT_TRUE(ToUIntTest(Vector{0x00001234},             hamon::uint16_t{0x1234}));
		EXPECT_TRUE(ToUIntTest(Vector{0x00000000},             hamon::uint32_t{0x00000000}));
		EXPECT_TRUE(ToUIntTest(Vector{0x12345678},             hamon::uint32_t{0x12345678}));
		EXPECT_TRUE(ToUIntTest(Vector{0x00000000},             hamon::uint64_t{0x0000000000000000}));
		EXPECT_TRUE(ToUIntTest(Vector{0x9ABCDEF0, 0x12345678}, hamon::uint64_t{0x123456789ABCDEF0}));
		EXPECT_TRUE(ToUIntTest(Vector{0xFFFFFFFF, 0xFFFFFFFF}, hamon::uint64_t{0xFFFFFFFFFFFFFFFF}));
	}
	{
		using Vector = hamon::vector<hamon::uint64_t>;
		EXPECT_TRUE(ToUIntTest(Vector{0x0000000000000000}, hamon::uint8_t{0x00}));
		EXPECT_TRUE(ToUIntTest(Vector{0x0000000000000012}, hamon::uint8_t{0x12}));
		EXPECT_TRUE(ToUIntTest(Vector{0x0000000000000000}, hamon::uint16_t{0x0000}));
		EXPECT_TRUE(ToUIntTest(Vector{0x0000000000001234}, hamon::uint16_t{0x1234}));
		EXPECT_TRUE(ToUIntTest(Vector{0x0000000000000000}, hamon::uint32_t{0x00000000}));
		EXPECT_TRUE(ToUIntTest(Vector{0x0000000012345678}, hamon::uint32_t{0x12345678}));
		EXPECT_TRUE(ToUIntTest(Vector{0x0000000000000000}, hamon::uint64_t{0x0000000000000000}));
		EXPECT_TRUE(ToUIntTest(Vector{0x123456789ABCDEF0}, hamon::uint64_t{0x123456789ABCDEF0}));
		EXPECT_TRUE(ToUIntTest(Vector{0xFFFFFFFFFFFFFFFF}, hamon::uint64_t{0xFFFFFFFFFFFFFFFF}));
	}

	{
		using Vector = hamon::array<hamon::uint8_t, 8>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, hamon::uint8_t{0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, hamon::uint8_t{0x12}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, hamon::uint16_t{0x0000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x34, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, hamon::uint16_t{0x1234}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, hamon::uint32_t{0x00000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x78, 0x56, 0x34, 0x12, 0x00, 0x00, 0x00, 0x00}, hamon::uint32_t{0x12345678}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, hamon::uint64_t{0x0000000000000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0xF0, 0xDE, 0xBC, 0x9A, 0x78, 0x56, 0x34, 0x12}, hamon::uint64_t{0x123456789ABCDEF0}));
	}
	{
		using Vector = hamon::array<hamon::uint16_t, 4>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x0000, 0x0000, 0x0000, 0x0000}, hamon::uint8_t{0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x0012, 0x0000, 0x0000, 0x0000}, hamon::uint8_t{0x12}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x0000, 0x0000, 0x0000, 0x0000}, hamon::uint16_t{0x0000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x1234, 0x0000, 0x0000, 0x0000}, hamon::uint16_t{0x1234}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x0000, 0x0000, 0x0000, 0x0000}, hamon::uint32_t{0x00000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x5678, 0x1234, 0x0000, 0x0000}, hamon::uint32_t{0x12345678}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x0000, 0x0000, 0x0000, 0x0000}, hamon::uint64_t{0x0000000000000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0xDEF0, 0x9ABC, 0x5678, 0x1234}, hamon::uint64_t{0x123456789ABCDEF0}));
	}
	{
		using Vector = hamon::array<hamon::uint32_t, 2>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x00000000, 0x00000000}, hamon::uint8_t{0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x00000012, 0x00000000}, hamon::uint8_t{0x12}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x00000000, 0x00000000}, hamon::uint16_t{0x0000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x00001234, 0x00000000}, hamon::uint16_t{0x1234}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x00000000, 0x00000000}, hamon::uint32_t{0x00000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x12345678, 0x00000000}, hamon::uint32_t{0x12345678}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x00000000, 0x00000000}, hamon::uint64_t{0x0000000000000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x9ABCDEF0, 0x12345678}, hamon::uint64_t{0x123456789ABCDEF0}));
	}
	{
		using Vector = hamon::array<hamon::uint64_t, 2>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x0000000000000000, 0x0000000000000000}, hamon::uint8_t{0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x0000000000000012, 0x0000000000000000}, hamon::uint8_t{0x12}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x0000000000000000, 0x0000000000000000}, hamon::uint16_t{0x0000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x0000000000001234, 0x0000000000000000}, hamon::uint16_t{0x1234}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x0000000000000000, 0x0000000000000000}, hamon::uint32_t{0x00000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x0000000012345678, 0x0000000000000000}, hamon::uint32_t{0x12345678}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x0000000000000000, 0x0000000000000000}, hamon::uint64_t{0x0000000000000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntTest(Vector{0x123456789ABCDEF0, 0x0000000000000000}, hamon::uint64_t{0x123456789ABCDEF0}));
	}

	{
		using Vector = hamon::vector<hamon::uint8_t>;
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0x00}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0xFF}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0x00, 0x01}, std::errc::value_too_large));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint16_t>(Vector{0x00, 0x01}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint16_t>(Vector{0xFF, 0xFF, }, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint16_t>(Vector{0x00, 0x00, 0x01}, std::errc::value_too_large));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint32_t>(Vector{0x00, 0x00, 0x01}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint32_t>(Vector{0xFF, 0xFF, 0xFF, 0xFF}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint32_t>(Vector{0x00, 0x00, 0x00, 0x00, 0x01}, std::errc::value_too_large));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint64_t>(Vector{0x00, 0x00, 0x00, 0x00, 0x01}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint64_t>(Vector{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint64_t>(Vector{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01}, std::errc::value_too_large));
	}
	{
		using Vector = hamon::vector<hamon::uint16_t>;
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0x0000}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0x00FF}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0x0100}, std::errc::value_too_large));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint16_t>(Vector{0x0100}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint16_t>(Vector{0xFFFF}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint16_t>(Vector{0x0000, 0x0001}, std::errc::value_too_large));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint32_t>(Vector{0x0000, 0x0001}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint32_t>(Vector{0xFFFF, 0xFFFF}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint32_t>(Vector{0x0000, 0x0000, 0x0001}, std::errc::value_too_large));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint64_t>(Vector{0x0000, 0x0000, 0x0001}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint64_t>(Vector{0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint64_t>(Vector{0x0000, 0x0000, 0x0000, 0x0000, 0x0001}, std::errc::value_too_large));
	}
	{
		using Vector = hamon::vector<hamon::uint32_t>;
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0x00000000}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0x000000FF}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0x00000100}, std::errc::value_too_large));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint16_t>(Vector{0x00000100}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint16_t>(Vector{0x0000FFFF}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint16_t>(Vector{0x00010000}, std::errc::value_too_large));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint32_t>(Vector{0x00010000}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint32_t>(Vector{0xFFFFFFFF}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint32_t>(Vector{0x00000000, 0x00000001}, std::errc::value_too_large));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint64_t>(Vector{0x00000000, 0x00000001}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint64_t>(Vector{0xFFFFFFFF, 0xFFFFFFFF}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint64_t>(Vector{0x00000000, 0x00000000, 0x00000001}, std::errc::value_too_large));
	}
	{
		using Vector = hamon::vector<hamon::uint64_t>;
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0x0000000000000000}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0x00000000000000FF}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0x0000000000000100}, std::errc::value_too_large));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0x123456789ABCDEF0}, std::errc::value_too_large));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint16_t>(Vector{0x0000000000000100}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint16_t>(Vector{0x000000000000FFFF}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint16_t>(Vector{0x0000000000010000}, std::errc::value_too_large));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint32_t>(Vector{0x0000000000010000}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint32_t>(Vector{0x00000000FFFFFFFF}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint32_t>(Vector{0x0000000100000000}, std::errc::value_too_large));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint64_t>(Vector{0x0000000100000000}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint64_t>(Vector{0xFFFFFFFFFFFFFFFF}, std::errc{}));
		EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint64_t>(Vector{0x0000000000000000, 0x0000000000000001}, std::errc::value_too_large));
	}
	{
		using Vector = hamon::array<hamon::uint8_t, 9>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, std::errc::value_too_large));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, std::errc::value_too_large));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint16_t>(Vector{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint16_t>(Vector{0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint16_t>(Vector{0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, std::errc::value_too_large));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint32_t>(Vector{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint32_t>(Vector{0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint32_t>(Vector{0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00}, std::errc::value_too_large));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint64_t>(Vector{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint64_t>(Vector{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint64_t>(Vector{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01}, std::errc::value_too_large));
	}
	{
		using Vector = hamon::array<hamon::uint16_t, 5>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0x0000, 0x0000, 0x0000, 0x0000, 0x0000}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0x00FF, 0x0000, 0x0000, 0x0000, 0x0000}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0x0100, 0x0000, 0x0000, 0x0000, 0x0000}, std::errc::value_too_large));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF}, std::errc::value_too_large));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint16_t>(Vector{0x0000, 0x0000, 0x0000, 0x0000, 0x0000}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint16_t>(Vector{0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint16_t>(Vector{0x0000, 0x0001, 0x0000, 0x0000, 0x0000}, std::errc::value_too_large));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint32_t>(Vector{0x0000, 0x0000, 0x0000, 0x0000, 0x0000}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint32_t>(Vector{0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint32_t>(Vector{0x0000, 0x0000, 0x0001, 0x0000, 0x0000}, std::errc::value_too_large));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint64_t>(Vector{0x0000, 0x0000, 0x0000, 0x0000, 0x0000}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint64_t>(Vector{0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint64_t>(Vector{0x0000, 0x0000, 0x0000, 0x0000, 0x0001}, std::errc::value_too_large));
	}
	{
		using Vector = hamon::array<hamon::uint32_t, 3>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0x00000000, 0x00000000, 0x00000000}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0x000000FF, 0x00000000, 0x00000000}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0x00000100, 0x00000000, 0x00000000}, std::errc::value_too_large));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}, std::errc::value_too_large));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint16_t>(Vector{0x00000000, 0x00000000, 0x00000000}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint16_t>(Vector{0x0000FFFF, 0x00000000, 0x00000000}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint16_t>(Vector{0x00010000, 0x00000000, 0x00000000}, std::errc::value_too_large));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint32_t>(Vector{0x00000000, 0x00000000, 0x00000000}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint32_t>(Vector{0xFFFFFFFF, 0x00000000, 0x00000000}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint32_t>(Vector{0x00000000, 0x00000001, 0x00000000}, std::errc::value_too_large));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint64_t>(Vector{0x00000000, 0x00000000, 0x00000000}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint64_t>(Vector{0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint64_t>(Vector{0x00000000, 0x00000000, 0x00000001}, std::errc::value_too_large));
	}
	{
		using Vector = hamon::array<hamon::uint64_t, 2>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0x0000000000000000, 0x0000000000000000}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0x00000000000000FF, 0x0000000000000000}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0x0000000000000100, 0x0000000000000000}, std::errc::value_too_large));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint8_t>(Vector{0x0000000000000000, 0x0000000000000001}, std::errc::value_too_large));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint16_t>(Vector{0x0000000000000000, 0x0000000000000000}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint16_t>(Vector{0x000000000000FFFF, 0x0000000000000000}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint16_t>(Vector{0x0000000000010000, 0x0000000000000000}, std::errc::value_too_large));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint32_t>(Vector{0x0000000000000000, 0x0000000000000000}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint32_t>(Vector{0x00000000FFFFFFFF, 0x0000000000000000}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint32_t>(Vector{0x0000000100000000, 0x0000000000000000}, std::errc::value_too_large));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint64_t>(Vector{0x0000000000000000, 0x0000000000000000}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint64_t>(Vector{0xFFFFFFFFFFFFFFFF, 0x0000000000000000}, std::errc{}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToUIntErrorCodeTest<hamon::uint64_t>(Vector{0x0000000000000000, 0x0000000000000001}, std::errc::value_too_large));
	}
}

#undef VERIFY

}	// namespace bigint_algo_to_uint_test

}	// namespace hamon_bigint_test
