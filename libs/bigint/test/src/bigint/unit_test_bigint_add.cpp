/**
 *	@file	unit_test_bigint_add.cpp
 *
 *	@brief	operator+のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4310)	// キャストによって定数値が切り捨てられました。

namespace hamon_bigint_test
{

namespace bigint_add_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
AddTest()
{
	{
		auto x = BigInt(0) + BigInt(0);
		VERIFY(x == BigInt(0));
	}
	{
		auto x = BigInt(1) + BigInt(0);
		VERIFY(x == BigInt(1));
	}
	{
		auto x = BigInt(2) + BigInt(3);
		VERIFY(x == BigInt(5));
	}
	{
		auto x = BigInt(2) + BigInt(-3);
		VERIFY(x == BigInt(-1));
	}
	{
		auto x = BigInt(-2) + BigInt(3);
		VERIFY(x == BigInt(1));
	}
	{
		auto x = BigInt(-2) + BigInt(-3);
		VERIFY(x == BigInt(-5));
	}
	{
		auto x = BigInt(1) + BigInt(999);
		VERIFY(x == BigInt(1000));
	}
	{
		auto x = BigInt(-10) + BigInt(1000);
		VERIFY(x == BigInt(990));
	}
	{
		auto x = BigInt(255) + BigInt(1);
		VERIFY(x == BigInt(256));
	}
	{
		auto x = BigInt(256) + BigInt(-1);
		VERIFY(x == BigInt(255));
	}
	{
		auto x = BigInt(255) + BigInt(255);
		VERIFY(x == BigInt(510));
	}
	{
		auto x = BigInt(255) + BigInt(256);
		VERIFY(x == BigInt(511));
	}
	{
		auto x = BigInt(0xffff) + BigInt(1);
		VERIFY(x == BigInt(0x10000));
	}
	{
		auto x = BigInt(1) + BigInt(0xffffff);
		VERIFY(x == BigInt(0x1000000));
	}
	{
		auto x = BigInt(0xffffffff) + BigInt(0xffffffff);
		VERIFY(x == BigInt(0x1fffffffe));
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
AddTest2()
{
	{
		auto x =
			BigInt{"3565257399734975859457283787877529836964"} +
			BigInt{"7966969762968552357477389456772596794377"};
		VERIFY(x == BigInt{"11532227162703528216934673244650126631341"});
	}
	{
		auto x =
			BigInt{"3565257399734975859457283787877529836964"} +
			BigInt{"-7966969762968552357477389456772596794377"};
		VERIFY(x == BigInt{"-4401712363233576498020105668895066957413"});
	}
	{
		auto x =
			BigInt{"99999999999999999999999999999999999999"} +
			BigInt(1);
		VERIFY(x == BigInt{"100000000000000000000000000000000000000"});
	}
	return true;
}

GTEST_TEST(BigIntTest, AddTest)
{
	EXPECT_TRUE(AddTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<hamon::int512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<hamon::int1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<hamon::uint512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<hamon::uint1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest<hamon::uint2048_t>());

	EXPECT_TRUE(AddTest2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest2<hamon::int512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest2<hamon::int1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest2<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest2<hamon::uint512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest2<hamon::uint1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddTest2<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_add_test

}	// namespace hamon_bigint_test

HAMON_WARNING_POP()
