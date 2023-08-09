/**
 *	@file	unit_test_bigint_xor.cpp
 *
 *	@brief	operator^のテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <gtest/gtest.h>

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_xor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
XorTest()
{
	{
		auto x = BigInt{0xFA} ^ BigInt{0x47};
		VERIFY(x == 0xBD);
	}
	{
		auto x = BigInt{0x35} ^ BigInt{0xf0};
		VERIFY(x == 0xC5);
	}
	{
		auto x = BigInt{0x73} ^ BigInt{0x20};
		VERIFY(x == 0x53);
	}
	{
		auto x = BigInt{0x123456} ^ BigInt{0xf00000};
		VERIFY(x == 0xE23456);
	}
	{
		auto x = BigInt{0x123456} ^ BigInt{0x0f0000};
		VERIFY(x == 0x1D3456);
	}
	{
		auto x = BigInt{0x123456} ^ BigInt{0x00000f};
		VERIFY(x == 0x123459);
	}
	{
		auto x = BigInt{0x123456} ^ BigInt{0xf0f0f0};
		VERIFY(x == 0xE2C4A6);
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
XorTest2()
{
	{
		auto x =
			BigInt{"0x123456789ABCDEF0123456789ABCDEF"} ^
			BigInt{"0xFFFF0000FFFFF00000FF00F0F0FFF00"};
		VERIFY(x == BigInt{"0x0edcb567865432ef012cb56886a432ef"});
	}
	{
		auto x =
			BigInt{"0x123456789ABCDEF0123456789ABCDEF"} ^
			BigInt{"0x123456789ABCDEF0123456789ABCDEF"};
		VERIFY(x == 0);
	}
	return true;
}

GTEST_TEST(BigIntTest, XorTest)
{
	EXPECT_TRUE(XorTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest<hamon::int512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest<hamon::int1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest<hamon::uint512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest<hamon::uint1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest<hamon::uint2048_t>());

	EXPECT_TRUE(XorTest2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest2<hamon::int512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest2<hamon::int1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest2<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest2<hamon::uint512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest2<hamon::uint1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest2<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_xor_test

}	// namespace hamon_bigint_test
