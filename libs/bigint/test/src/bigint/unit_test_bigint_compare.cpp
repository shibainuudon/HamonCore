/**
 *	@file	unit_test_bigint_compare.cpp
 *
 *	@brief	比較演算子のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4127)	// 条件式が定数です。

namespace hamon_bigint_test
{

namespace bigint_compare_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
CompareSignedTest()
{
	{
		auto const x1 = BigInt(-2);

		VERIFY((x1 == -1) == false);
		VERIFY((x1 == -2) == true);
		VERIFY((x1 == -3) == false);

		VERIFY((x1 != -1) == true);
		VERIFY((x1 != -2) == false);
		VERIFY((x1 != -3) == true);

		VERIFY((x1 <  -1) == true);
		VERIFY((x1 <  -2) == false);
		VERIFY((x1 <  -3) == false);

		VERIFY((x1 >  -1) == false);
		VERIFY((x1 >  -2) == false);
		VERIFY((x1 >  -3) == true);

		VERIFY((x1 <= -1) == true);
		VERIFY((x1 <= -2) == true);
		VERIFY((x1 <= -3) == false);

		VERIFY((x1 >= -1) == false);
		VERIFY((x1 >= -2) == true);
		VERIFY((x1 >= -3) == true);
	}
	{
		auto const x1 = BigInt( -12345);
		auto const x2 = BigInt( -12345);
		auto const x3 = BigInt( -12340);
		auto const x4 = BigInt( -12346);
		auto const x5 = BigInt(   1234);
		auto const x6 = BigInt(-123456);

		VERIFY((x1 == x1) == true);
		VERIFY((x1 == x2) == true);
		VERIFY((x1 == x3) == false);
		VERIFY((x1 == x4) == false);
		VERIFY((x1 == x5) == false);
		VERIFY((x1 == x6) == false);

		VERIFY((x1 != x1) == false);
		VERIFY((x1 != x2) == false);
		VERIFY((x1 != x3) == true);
		VERIFY((x1 != x4) == true);
		VERIFY((x1 != x5) == true);
		VERIFY((x1 != x6) == true);

		VERIFY((x1 <  x1) == false);
		VERIFY((x1 <  x2) == false);
		VERIFY((x1 <  x3) == true);
		VERIFY((x1 <  x4) == false);
		VERIFY((x1 <  x5) == true);
		VERIFY((x1 <  x6) == false);

		VERIFY((x1 >  x1) == false);
		VERIFY((x1 >  x2) == false);
		VERIFY((x1 >  x3) == false);
		VERIFY((x1 >  x4) == true);
		VERIFY((x1 >  x5) == false);
		VERIFY((x1 >  x6) == true);

		VERIFY((x1 <= x1) == true);
		VERIFY((x1 <= x2) == true);
		VERIFY((x1 <= x3) == true);
		VERIFY((x1 <= x4) == false);
		VERIFY((x1 <= x5) == true);
		VERIFY((x1 <= x6) == false);

		VERIFY((x1 >= x1) == true);
		VERIFY((x1 >= x2) == true);
		VERIFY((x1 >= x3) == false);
		VERIFY((x1 >= x4) == true);
		VERIFY((x1 >= x5) == false);
		VERIFY((x1 >= x6) == true);
	}
	{
		auto const x1 = BigInt(-1);
		VERIFY((x1 < 0) == true);
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
CompareSignedTest2()
{
	{
		auto const x1 = BigInt{"314159265358979323846264338327950288419716939937510"};
		auto const x2 = BigInt{"314159265358979323846264338327950288419716939937510"};
		auto const x3 = BigInt{"414159265358979323846264338327950288419716939937510"};
		auto const x4 = BigInt{"-314159265358979323846264338327950288419716939937510"};
		auto const x5 = BigInt{"3141592653589793238462643383279502884197169399375101"};
		auto const x6 = BigInt{"-9999999999999999999999999999999999999999999999999999"};

		VERIFY((x1 == x1) == true);
		VERIFY((x1 == x2) == true);
		VERIFY((x1 == x3) == false);
		VERIFY((x1 == x4) == false);
		VERIFY((x1 == x5) == false);
		VERIFY((x1 == x6) == false);

		VERIFY((x1 != x1) == false);
		VERIFY((x1 != x2) == false);
		VERIFY((x1 != x3) == true);
		VERIFY((x1 != x4) == true);
		VERIFY((x1 != x5) == true);
		VERIFY((x1 != x6) == true);

		VERIFY((x1 <  x1) == false);
		VERIFY((x1 <  x2) == false);
		VERIFY((x1 <  x3) == true);
		VERIFY((x1 <  x4) == false);
		VERIFY((x1 <  x5) == true);
		VERIFY((x1 <  x6) == false);

		VERIFY((x1 >  x1) == false);
		VERIFY((x1 >  x2) == false);
		VERIFY((x1 >  x3) == false);
		VERIFY((x1 >  x4) == true);
		VERIFY((x1 >  x5) == false);
		VERIFY((x1 >  x6) == true);

		VERIFY((x1 <= x1) == true);
		VERIFY((x1 <= x2) == true);
		VERIFY((x1 <= x3) == true);
		VERIFY((x1 <= x4) == false);
		VERIFY((x1 <= x5) == true);
		VERIFY((x1 <= x6) == false);

		VERIFY((x1 >= x1) == true);
		VERIFY((x1 >= x2) == true);
		VERIFY((x1 >= x3) == false);
		VERIFY((x1 >= x4) == true);
		VERIFY((x1 >= x5) == false);
		VERIFY((x1 >= x6) == true);
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
CompareUnsignedTest()
{
	{
		auto const x1 = BigInt(2);

		VERIFY((x1 == 1) == false);
		VERIFY((x1 == 2) == true);
		VERIFY((x1 == 3) == false);

		VERIFY((x1 != 1) == true);
		VERIFY((x1 != 2) == false);
		VERIFY((x1 != 3) == true);

		VERIFY((x1 <  1) == false);
		VERIFY((x1 <  2) == false);
		VERIFY((x1 <  3) == true);

		VERIFY((x1 >  1) == true);
		VERIFY((x1 >  2) == false);
		VERIFY((x1 >  3) == false);

		VERIFY((x1 <= 1) == false);
		VERIFY((x1 <= 2) == true);
		VERIFY((x1 <= 3) == true);

		VERIFY((x1 >= 1) == true);
		VERIFY((x1 >= 2) == true);
		VERIFY((x1 >= 3) == false);
	}
	{
		auto const x1 = BigInt(-1);
		VERIFY((x1 < 0) == false);
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
CompareUnsignedTest2()
{
	{
		auto const x1 = BigInt{"123456789012345678"};
		auto const x2 = BigInt{"123456789012345678"};
		auto const x3 = BigInt{"123456789012345677"};
		auto const x4 = BigInt{"123456789012345679"};

		VERIFY((x1 == x1) == true);
		VERIFY((x1 == x2) == true);
		VERIFY((x1 == x3) == false);
		VERIFY((x1 == x4) == false);

		VERIFY((x1 != x1) == false);
		VERIFY((x1 != x2) == false);
		VERIFY((x1 != x3) == true);
		VERIFY((x1 != x4) == true);

		VERIFY((x1 < x1) == false);
		VERIFY((x1 < x2) == false);
		VERIFY((x1 < x3) == false);
		VERIFY((x1 < x4) == true);

		VERIFY((x1 > x1) == false);
		VERIFY((x1 > x2) == false);
		VERIFY((x1 > x3) == true);
		VERIFY((x1 > x4) == false);

		VERIFY((x1 <= x1) == true);
		VERIFY((x1 <= x2) == true);
		VERIFY((x1 <= x3) == false);
		VERIFY((x1 <= x4) == true);

		VERIFY((x1 >= x1) == true);
		VERIFY((x1 >= x2) == true);
		VERIFY((x1 >= x3) == true);
		VERIFY((x1 >= x4) == false);
	}
	return true;
}

GTEST_TEST(BigIntTest, CompareTest)
{
	EXPECT_TRUE(CompareSignedTest<hamon::bigint>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareSignedTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareSignedTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareSignedTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareSignedTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareSignedTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(CompareSignedTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(CompareSignedTest<hamon::int2048_t>());

//	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareSignedTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareSignedTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareSignedTest2<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(CompareSignedTest2<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(CompareSignedTest2<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareUnsignedTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareUnsignedTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareUnsignedTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareUnsignedTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareUnsignedTest<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(CompareUnsignedTest<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(CompareUnsignedTest<hamon::uint2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareUnsignedTest2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareUnsignedTest2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareUnsignedTest2<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(CompareUnsignedTest2<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(CompareUnsignedTest2<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_compare_test

}	// namespace hamon_bigint_test

HAMON_WARNING_POP()
