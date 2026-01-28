/**
 *	@file	unit_test_bigint_ctor_string.cpp
 *
 *	@brief	文字列を引数に取るコンストラクタのテスト
 */

#include <hamon/bigint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_ctor_string_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
CtorStringTest()
{
	{
		BigInt x{""};
		VERIFY(x == BigInt{0});
	}
	{
		BigInt x{"0"};
		VERIFY(x == BigInt{0});
	}
	{
		BigInt x{"+0"};
		VERIFY(x == BigInt{+0});
	}
	{
		BigInt x{"-0"};
		VERIFY(x == BigInt{-0});
	}
	{
		BigInt x{"1"};
		VERIFY(x == BigInt{1});
	}
	{
		BigInt x{"+1"};
		VERIFY(x == BigInt{+1});
	}
	{
		BigInt x{"-1"};
		VERIFY(x == BigInt{-1});
	}
	{
		BigInt x{"123"};
		VERIFY(x == BigInt{123});
	}
	{
		BigInt x{"+123"};
		VERIFY(x == BigInt{+123});
	}
	{
		BigInt x{"-123"};
		VERIFY(x == BigInt{-123});
	}
	{
		BigInt x{"987654321"};
		VERIFY(x == BigInt{987654321});
	}
	{
		BigInt x{"+987654321"};
		VERIFY(x == BigInt{+987654321});
	}
	{
		BigInt x{"-987654321"};
		VERIFY(x == BigInt{-987654321});
	}

	// binary
	{
		BigInt x{"0b1111011"};
//		VERIFY(x == BigInt{0b1111011});
		VERIFY(x == BigInt{123});
	}
	{
		BigInt x{"-0B1111011"};
//		VERIFY(x == BigInt{-0B1111011});
		VERIFY(x == BigInt{-123});
	}

	// hex
	{
		BigInt x{"0x0123456789ABCDEF"};
		VERIFY(x == BigInt{0x0123456789ABCDEF});
		VERIFY(x == BigInt{81985529216486895});
	}
	{
		BigInt x{"0Xffffffff"};
		VERIFY(x == BigInt{0Xffffffff});
		VERIFY(x == BigInt{4294967295});
	}
	{
		BigInt x{"-0x007f"};
		VERIFY(x == BigInt{-0x007f});
		VERIFY(x == BigInt{-127});
	}

	// oct
	{
		BigInt x {"02322"};
		VERIFY(x == BigInt{02322});
		VERIFY(x == BigInt{1234});
	}
	{
		BigInt x {"-02322"};
		VERIFY(x == BigInt{-02322});
		VERIFY(x == BigInt{-1234});
	}
	return true;
}

GTEST_TEST(BigIntTest, CtorStringTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(CtorStringTest<hamon::bigint>());

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(CtorStringTest<hamon::inplace_bigint<128>>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(CtorStringTest<hamon::inplace_bigint<256>>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(CtorStringTest<hamon::inplace_bigint<512>>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorStringTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorStringTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorStringTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorStringTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorStringTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorStringTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorStringTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CtorStringTest<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorStringTest<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(CtorStringTest<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_ctor_string_test

}	// namespace hamon_bigint_test
