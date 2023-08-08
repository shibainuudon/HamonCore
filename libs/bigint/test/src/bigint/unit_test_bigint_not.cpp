/**
 *	@file	unit_test_bigint_not.cpp
 *
 *	@brief	operator~のテスト
 */

#include <hamon/bigint/bigint.hpp>
#include <gtest/gtest.h>

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_not_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
NotTest()
{
	{
		auto x = ~BigInt(0);
		VERIFY(x == BigInt(-1));
	}
	{
		auto x = ~BigInt(1);
		VERIFY(x == BigInt(-2));
	}
	{
		auto x = ~BigInt(2);
		VERIFY(x == BigInt(-3));
	}
	{
		auto x = ~BigInt(-1);
		VERIFY(x == BigInt(0));
	}
	{
		auto x = ~BigInt(-2);
		VERIFY(x == BigInt(1));
	}
	{
		auto x = ~BigInt(0xFFFF);
		VERIFY(x == BigInt(-0x10000));
	}
	{
		auto x = ~BigInt(-0xFFFF);
		VERIFY(x == BigInt(0xFFFE));
	}
	{
		auto x = ~BigInt(0x12345678);
		VERIFY(x == BigInt(-0x12345679));
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
NotTest2()
{
	{
		auto x = ~BigInt("0xFFFFFFFFFFFFFFFF");
		VERIFY(x == BigInt("-0x10000000000000000"));
	}
	{
		auto x = ~BigInt("0x1234567890ABCDEF01234");
		VERIFY(x == -BigInt("0x1234567890ABCDEF01235"));
	}
	return true;
}

GTEST_TEST(BigIntTest, NotTest)
{
	EXPECT_TRUE(NotTest<hamon::bigint>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NotTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NotTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NotTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NotTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NotTest<hamon::int512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NotTest<hamon::int1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NotTest<hamon::int2048_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NotTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NotTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NotTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NotTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NotTest<hamon::uint512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NotTest<hamon::uint1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NotTest<hamon::uint2048_t>());

	EXPECT_TRUE(NotTest2<hamon::bigint>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NotTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NotTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NotTest2<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(NotTest2<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(NotTest2<hamon::int2048_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NotTest2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NotTest2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(NotTest2<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(NotTest2<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(NotTest2<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_not_test

}	// namespace hamon_bigint_test
