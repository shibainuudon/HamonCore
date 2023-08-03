/**
 *	@file	unit_test_bigint_ctor_integral.cpp
 *
 *	@brief	整数を引数に取るコンストラクタのテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_ctor_integral_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
CtorIntegralTest()
{
	{
		BigInt x{0};
		VERIFY(x == BigInt{"0"});
	}
	{
		BigInt x{-2};
		VERIFY(x == BigInt{"-2"});
	}
	{
		BigInt x{3};
		VERIFY(x == BigInt{"3"});
	}
	{
		BigInt x{std::numeric_limits<hamon::int8_t>::min()};
		VERIFY(x == BigInt{"-128"});
	}
	{
		BigInt x{std::numeric_limits<hamon::int8_t>::max()};
		VERIFY(x == BigInt{"127"});
	}
	{
		BigInt x{std::numeric_limits<hamon::int16_t>::min()};
		VERIFY(x == BigInt{"-32768"});
	}
	{
		BigInt x{std::numeric_limits<hamon::int16_t>::max()};
		VERIFY(x == BigInt{"32767"});
	}
	{
		BigInt x{std::numeric_limits<hamon::int32_t>::min()};
		VERIFY(x == BigInt{"-2147483648"});
	}
	{
		BigInt x{std::numeric_limits<hamon::int32_t>::max()};
		VERIFY(x == BigInt{"2147483647"});
	}
	{
		BigInt x{std::numeric_limits<hamon::int64_t>::min()};
		VERIFY(x == BigInt{"-9223372036854775808"});
	}
	{
		BigInt x{std::numeric_limits<hamon::int64_t>::max()};
		VERIFY(x == BigInt{"9223372036854775807"});
	}
	{
		BigInt x{std::numeric_limits<hamon::uint8_t>::min()};
		VERIFY(x == BigInt{"0"});
	}
	{
		BigInt x{std::numeric_limits<hamon::uint8_t>::max()};
		VERIFY(x == BigInt{"255"});
	}
	{
		BigInt x{std::numeric_limits<hamon::uint16_t>::min()};
		VERIFY(x == BigInt{"0"});
	}
	{
		BigInt x{std::numeric_limits<hamon::uint16_t>::max()};
		VERIFY(x == BigInt{"65535"});
	}
	{
		BigInt x{std::numeric_limits<hamon::uint32_t>::min()};
		VERIFY(x == BigInt{"0"});
	}
	{
		BigInt x{std::numeric_limits<hamon::uint32_t>::max()};
		VERIFY(x == BigInt{"4294967295"});
	}
	{
		BigInt x{std::numeric_limits<hamon::uint64_t>::min()};
		VERIFY(x == BigInt{"0"});
	}
	{
		BigInt x{std::numeric_limits<hamon::uint64_t>::max()};
		VERIFY(x == BigInt{"18446744073709551615"});
	}
	return true;
}

GTEST_TEST(BigIntTest, CtorIntegralTest)
{
	EXPECT_TRUE(CtorIntegralTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIntegralTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIntegralTest<hamon::int256_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorIntegralTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorIntegralTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorIntegralTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIntegralTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorIntegralTest<hamon::uint256_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorIntegralTest<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorIntegralTest<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorIntegralTest<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_ctor_integral_test

}	// namespace hamon_bigint_test
