/**
 *	@file	unit_test_bigint_algo_from_uint.cpp
 *
 *	@brief	bigint_algo::from_uint のテスト
 */

#include <hamon/bigint/bigint_algo/from_uint.hpp>
#include <hamon/array.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/vector.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_algo_from_uint_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename UInt, typename T>
inline HAMON_CXX14_CONSTEXPR bool
FromUIntTest(UInt n, T const& expected, std::errc ec = {})
{
	T value{0};
	auto ret = hamon::bigint_algo::from_uint(n, value);
	VERIFY(value == expected);
	VERIFY(ret.ec == ec);
	return true;
}

GTEST_TEST(BigIntAlgoTest, FromUIntTest)
{
	{
		using Vector = hamon::vector<hamon::uint8_t>;
		EXPECT_TRUE(FromUIntTest(hamon::uint8_t{0x00},                Vector{0x00}));
		EXPECT_TRUE(FromUIntTest(hamon::uint8_t{0x12},                Vector{0x12}));
		EXPECT_TRUE(FromUIntTest(hamon::uint16_t{0x0000},             Vector{0x00}));
		EXPECT_TRUE(FromUIntTest(hamon::uint16_t{0x1234},             Vector{0x34, 0x12}));
		EXPECT_TRUE(FromUIntTest(hamon::uint32_t{0x00000000},         Vector{0x00}));
		EXPECT_TRUE(FromUIntTest(hamon::uint32_t{0x12345678},         Vector{0x78, 0x56, 0x34, 0x12}));
		EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x0000000000000000}, Vector{0x00}));
		EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x123456789ABCDEF0}, Vector{0xF0, 0xDE, 0xBC, 0x9A, 0x78, 0x56, 0x34, 0x12}));
		EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x0000000000000123}, Vector{0x23, 0x01}));
	}
	{
		using Vector = hamon::vector<hamon::uint16_t>;
		EXPECT_TRUE(FromUIntTest(hamon::uint8_t{0x00},                Vector{0x0000}));
		EXPECT_TRUE(FromUIntTest(hamon::uint8_t{0x12},                Vector{0x0012}));
		EXPECT_TRUE(FromUIntTest(hamon::uint16_t{0x0000},             Vector{0x0000}));
		EXPECT_TRUE(FromUIntTest(hamon::uint16_t{0x1234},             Vector{0x1234}));
		EXPECT_TRUE(FromUIntTest(hamon::uint32_t{0x00000000},         Vector{0x0000}));
		EXPECT_TRUE(FromUIntTest(hamon::uint32_t{0x12345678},         Vector{0x5678, 0x1234}));
		EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x0000000000000000}, Vector{0x0000}));
		EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x123456789ABCDEF0}, Vector{0xDEF0, 0x9ABC, 0x5678, 0x1234}));
		EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x0000000000000123}, Vector{0x0123}));
	}
	{
		using Vector = hamon::vector<hamon::uint32_t>;
		EXPECT_TRUE(FromUIntTest(hamon::uint8_t{0x00},                Vector{0x00000000}));
		EXPECT_TRUE(FromUIntTest(hamon::uint8_t{0x12},                Vector{0x00000012}));
		EXPECT_TRUE(FromUIntTest(hamon::uint16_t{0x0000},             Vector{0x00000000}));
		EXPECT_TRUE(FromUIntTest(hamon::uint16_t{0x1234},             Vector{0x00001234}));
		EXPECT_TRUE(FromUIntTest(hamon::uint32_t{0x00000000},         Vector{0x00000000}));
		EXPECT_TRUE(FromUIntTest(hamon::uint32_t{0x12345678},         Vector{0x12345678}));
		EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x0000000000000000}, Vector{0x00000000}));
		EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x123456789ABCDEF0}, Vector{0x9ABCDEF0, 0x12345678}));
	}
	{
		using Vector = hamon::vector<hamon::uint64_t>;
		EXPECT_TRUE(FromUIntTest(hamon::uint8_t{0x00},                Vector{0x0000000000000000}));
		EXPECT_TRUE(FromUIntTest(hamon::uint8_t{0x12},                Vector{0x0000000000000012}));
		EXPECT_TRUE(FromUIntTest(hamon::uint16_t{0x0000},             Vector{0x0000000000000000}));
		EXPECT_TRUE(FromUIntTest(hamon::uint16_t{0x1234},             Vector{0x0000000000001234}));
		EXPECT_TRUE(FromUIntTest(hamon::uint32_t{0x00000000},         Vector{0x0000000000000000}));
		EXPECT_TRUE(FromUIntTest(hamon::uint32_t{0x12345678},         Vector{0x0000000012345678}));
		EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x0000000000000000}, Vector{0x0000000000000000}));
		EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x123456789ABCDEF0}, Vector{0x123456789ABCDEF0}));
	}
	{
		using Vector = hamon::array<hamon::uint8_t, 8>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint8_t{0x00},                Vector{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint8_t{0x12},                Vector{0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint16_t{0x0000},             Vector{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint16_t{0x1234},             Vector{0x34, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint32_t{0x00000000},         Vector{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint32_t{0x12345678},         Vector{0x78, 0x56, 0x34, 0x12, 0x00, 0x00, 0x00, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x0000000000000000}, Vector{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x123456789ABCDEF0}, Vector{0xF0, 0xDE, 0xBC, 0x9A, 0x78, 0x56, 0x34, 0x12}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x0000000000000123}, Vector{0x23, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}));
	}
	{
		using Vector = hamon::array<hamon::uint8_t, 3>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint8_t{0x00},                Vector{0x00, 0x00, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint8_t{0x12},                Vector{0x12, 0x00, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint16_t{0x0000},             Vector{0x00, 0x00, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint16_t{0x1234},             Vector{0x34, 0x12, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint32_t{0x00000000},         Vector{0x00, 0x00, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint32_t{0x12345678},         Vector{0x78, 0x56, 0x34}, std::errc::result_out_of_range));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x0000000000000000}, Vector{0x00, 0x00, 0x00}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x123456789ABCDEF0}, Vector{0xF0, 0xDE, 0xBC}, std::errc::result_out_of_range));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x0000000000000123}, Vector{0x23, 0x01, 0x00}));
	}
	{
		using Vector = hamon::array<hamon::uint16_t, 4>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint8_t{0x00},                Vector{0x0000, 0x0000, 0x0000, 0x0000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint8_t{0x12},                Vector{0x0012, 0x0000, 0x0000, 0x0000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint16_t{0x0000},             Vector{0x0000, 0x0000, 0x0000, 0x0000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint16_t{0x1234},             Vector{0x1234, 0x0000, 0x0000, 0x0000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint32_t{0x00000000},         Vector{0x0000, 0x0000, 0x0000, 0x0000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint32_t{0x12345678},         Vector{0x5678, 0x1234, 0x0000, 0x0000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x0000000000000000}, Vector{0x0000, 0x0000, 0x0000, 0x0000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x123456789ABCDEF0}, Vector{0xDEF0, 0x9ABC, 0x5678, 0x1234}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x0000000000000123}, Vector{0x0123, 0x0000, 0x0000, 0x0000}));
	}
	{
		using Vector = hamon::array<hamon::uint16_t, 3>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint8_t{0x00},                Vector{0x0000, 0x0000, 0x0000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint8_t{0x12},                Vector{0x0012, 0x0000, 0x0000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint16_t{0x0000},             Vector{0x0000, 0x0000, 0x0000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint16_t{0x1234},             Vector{0x1234, 0x0000, 0x0000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint32_t{0x00000000},         Vector{0x0000, 0x0000, 0x0000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint32_t{0x12345678},         Vector{0x5678, 0x1234, 0x0000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x0000000000000000}, Vector{0x0000, 0x0000, 0x0000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x123456789ABCDEF0}, Vector{0xDEF0, 0x9ABC, 0x5678}, std::errc::result_out_of_range));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x0000000000000123}, Vector{0x0123, 0x0000, 0x0000}));
	}
	{
		using Vector = hamon::array<hamon::uint32_t, 2>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint8_t{0x00},                Vector{0x00000000, 0x00000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint8_t{0x12},                Vector{0x00000012, 0x00000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint16_t{0x0000},             Vector{0x00000000, 0x00000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint16_t{0x1234},             Vector{0x00001234, 0x00000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint32_t{0x00000000},         Vector{0x00000000, 0x00000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint32_t{0x12345678},         Vector{0x12345678, 0x00000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x0000000000000000}, Vector{0x00000000, 0x00000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x123456789ABCDEF0}, Vector{0x9ABCDEF0, 0x12345678}));
	}
	{
		using Vector = hamon::array<hamon::uint32_t, 1>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint8_t{0x00},                Vector{0x00000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint8_t{0x12},                Vector{0x00000012}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint16_t{0x0000},             Vector{0x00000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint16_t{0x1234},             Vector{0x00001234}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint32_t{0x00000000},         Vector{0x00000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint32_t{0x12345678},         Vector{0x12345678}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x0000000000000000}, Vector{0x00000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x123456789ABCDEF0}, Vector{0x9ABCDEF0}, std::errc::result_out_of_range));
	}
	{
		using Vector = hamon::array<hamon::uint64_t, 2>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint8_t{0x00},                Vector{0x0000000000000000, 0x0000000000000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint8_t{0x12},                Vector{0x0000000000000012, 0x0000000000000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint16_t{0x0000},             Vector{0x0000000000000000, 0x0000000000000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint16_t{0x1234},             Vector{0x0000000000001234, 0x0000000000000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint32_t{0x00000000},         Vector{0x0000000000000000, 0x0000000000000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint32_t{0x12345678},         Vector{0x0000000012345678, 0x0000000000000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x0000000000000000}, Vector{0x0000000000000000, 0x0000000000000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x123456789ABCDEF0}, Vector{0x123456789ABCDEF0, 0x0000000000000000}));
	}
	{
		using Vector = hamon::array<hamon::uint64_t, 1>;
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint8_t{0x00},                Vector{0x0000000000000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint8_t{0x12},                Vector{0x0000000000000012}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint16_t{0x0000},             Vector{0x0000000000000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint16_t{0x1234},             Vector{0x0000000000001234}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint32_t{0x00000000},         Vector{0x0000000000000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint32_t{0x12345678},         Vector{0x0000000012345678}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x0000000000000000}, Vector{0x0000000000000000}));
		HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FromUIntTest(hamon::uint64_t{0x123456789ABCDEF0}, Vector{0x123456789ABCDEF0}));
	}
}

#undef VERIFY

}	// namespace bigint_algo_from_uint_test

}	// namespace hamon_bigint_test
