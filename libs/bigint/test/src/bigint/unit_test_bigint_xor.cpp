/**
 *	@file	unit_test_bigint_xor.cpp
 *
 *	@brief	operator^のテスト
 */

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
		VERIFY((BigInt{0xFA} ^ BigInt{0x47}) == BigInt{0xBD});
		VERIFY((BigInt{0x35} ^ BigInt{0xF0}) == BigInt{0xC5});
		VERIFY((BigInt{0x73} ^ BigInt{0x20}) == BigInt{0x53});
		VERIFY((BigInt{0x73} ^ BigInt{0x0C}) == BigInt{0x7F});
		VERIFY((BigInt{0x123456} ^ BigInt{0xf00000}) == BigInt{0xE23456});
		VERIFY((BigInt{0x123456} ^ BigInt{0x0f0000}) == BigInt{0x1D3456});
		VERIFY((BigInt{0x123456} ^ BigInt{0x00000f}) == BigInt{0x123459});
		VERIFY((BigInt{0x123456} ^ BigInt{0xf0f0f0}) == BigInt{0xE2C4A6});
	}
	{
		VERIFY((BigInt{0xFA} ^ hamon::uint8_t{0x47}) == BigInt{0xBD});
		VERIFY((BigInt{0x35} ^ hamon::uint8_t{0xF0}) == BigInt{0xC5});
		VERIFY((BigInt{0x73} ^ hamon::uint16_t{0x20}) == BigInt{0x53});
		VERIFY((BigInt{0x73} ^ hamon::uint16_t{0x0C}) == BigInt{0x7F});
		VERIFY((BigInt{0x123456} ^ hamon::uint32_t{0xf00000}) == BigInt{0xE23456});
		VERIFY((BigInt{0x123456} ^ hamon::uint32_t{0x0f0000}) == BigInt{0x1D3456});
		VERIFY((BigInt{0x123456} ^ hamon::uint64_t{0x00000f}) == BigInt{0x123459});
		VERIFY((BigInt{0x123456} ^ hamon::uint64_t{0xf0f0f0}) == BigInt{0xE2C4A6});
	}
	{
		VERIFY((hamon::uint8_t{0xFA} ^ BigInt{0x47}) == BigInt{0xBD});
		VERIFY((hamon::uint8_t{0x35} ^ BigInt{0xF0}) == BigInt{0xC5});
		VERIFY((hamon::uint16_t{0x73} ^ BigInt{0x20}) == BigInt{0x53});
		VERIFY((hamon::uint16_t{0x73} ^ BigInt{0x0C}) == BigInt{0x7F});
		VERIFY((hamon::uint32_t{0x123456} ^ BigInt{0xf00000}) == BigInt{0xE23456});
		VERIFY((hamon::uint32_t{0x123456} ^ BigInt{0x0f0000}) == BigInt{0x1D3456});
		VERIFY((hamon::uint64_t{0x123456} ^ BigInt{0x00000f}) == BigInt{0x123459});
		VERIFY((hamon::uint64_t{0x123456} ^ BigInt{0xf0f0f0}) == BigInt{0xE2C4A6});
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
		VERIFY(x == BigInt{0});
	}
	return true;
}

#undef VERIFY

GTEST_TEST(BigIntTest, XorTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(XorTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest<hamon::inplace_bigint<128>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest<hamon::inplace_bigint<256>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest<hamon::inplace_bigint<512>>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(XorTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(XorTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(XorTest<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(XorTest<hamon::uint2048_t>());

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(XorTest2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest2<hamon::inplace_bigint<128>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest2<hamon::inplace_bigint<256>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest2<hamon::inplace_bigint<512>>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest2<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(XorTest2<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(XorTest2<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(XorTest2<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(XorTest2<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(XorTest2<hamon::uint2048_t>());
}

}	// namespace bigint_xor_test

}	// namespace hamon_bigint_test
