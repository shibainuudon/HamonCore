/**
 *	@file	unit_test_bigint_add_equal.cpp
 *
 *	@brief	operator+=のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4146)	// 符号付きの値を代入する変数は、符号付き型にキャストしなければなりません。

namespace hamon_bigint_test
{

namespace bigint_add_equal_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
AddEqualTest()
{
	BigInt x{};
	VERIFY(x == 0);

	x += 0;
	VERIFY(x == 0);

	x += 1;
	VERIFY(x == 1);

	x += BigInt(-2);
	VERIFY(x == BigInt(-1));

	x += 12345;
	VERIFY(x == 12344);

	x += BigInt(656);
	VERIFY(x == 13000);

	x += BigInt(-123456789);
	VERIFY(x == BigInt(-123443789));

	x += x;
	VERIFY(x == BigInt(-246887578));

	x += -x;
	VERIFY(x == 0);

	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
AddEqualTest2()
{
	BigInt x{};

	x += BigInt{"3565257399734975859457283787877529836964"};
	VERIFY(x == BigInt{"3565257399734975859457283787877529836964"});

	x += BigInt{"7966969762968552357477389456772596794377"};
	VERIFY(x == BigInt{"11532227162703528216934673244650126631341"});

	x += BigInt{"-98798175978292719871501283740710298751098"};
	VERIFY(x == BigInt{"-87265948815589191654566610496060172119757"});

	return true;
}

GTEST_TEST(BigIntTest, AddEqualTest)
{
	EXPECT_TRUE(AddEqualTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddEqualTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddEqualTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddEqualTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddEqualTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddEqualTest<hamon::int512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddEqualTest<hamon::int1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddEqualTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddEqualTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddEqualTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddEqualTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddEqualTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddEqualTest<hamon::uint512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddEqualTest<hamon::uint1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddEqualTest<hamon::uint2048_t>());

	EXPECT_TRUE(AddEqualTest2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddEqualTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddEqualTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddEqualTest2<hamon::int512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddEqualTest2<hamon::int1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddEqualTest2<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddEqualTest2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddEqualTest2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddEqualTest2<hamon::uint512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddEqualTest2<hamon::uint1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(AddEqualTest2<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_add_equal_test

}	// namespace hamon_bigint_test

HAMON_WARNING_POP()
