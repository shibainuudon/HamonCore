/**
 *	@file	unit_test_bigint_compare.cpp
 *
 *	@brief	比較演算子のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

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
		VERIFY((BigInt{-2} == BigInt{-1}) == false);
		VERIFY((BigInt{-2} == BigInt{-2}) == true);
		VERIFY((BigInt{-2} == BigInt{-3}) == false);

		VERIFY((BigInt{-2} != BigInt{-1}) == true);
		VERIFY((BigInt{-2} != BigInt{-2}) == false);
		VERIFY((BigInt{-2} != BigInt{-3}) == true);

		VERIFY((BigInt{-2} <  BigInt{-1}) == true);
		VERIFY((BigInt{-2} <  BigInt{-2}) == false);
		VERIFY((BigInt{-2} <  BigInt{-3}) == false);

		VERIFY((BigInt{-2} >  BigInt{-1}) == false);
		VERIFY((BigInt{-2} >  BigInt{-2}) == false);
		VERIFY((BigInt{-2} >  BigInt{-3}) == true);

		VERIFY((BigInt{-2} <= BigInt{-1}) == true);
		VERIFY((BigInt{-2} <= BigInt{-2}) == true);
		VERIFY((BigInt{-2} <= BigInt{-3}) == false);

		VERIFY((BigInt{-2} >= BigInt{-1}) == false);
		VERIFY((BigInt{-2} >= BigInt{-2}) == true);
		VERIFY((BigInt{-2} >= BigInt{-3}) == true);
	}
	{
		VERIFY((BigInt{-2} == hamon::int8_t {-1}) == false);
		VERIFY((BigInt{-2} == hamon::int16_t{-2}) == true);
		VERIFY((BigInt{-2} == hamon::int32_t{-3}) == false);

		VERIFY((BigInt{-2} != hamon::int64_t{-1}) == true);
		VERIFY((BigInt{-2} != hamon::int8_t {-2}) == false);
		VERIFY((BigInt{-2} != hamon::int16_t{-3}) == true);

		VERIFY((BigInt{-2} <  hamon::int32_t{-1}) == true);
		VERIFY((BigInt{-2} <  hamon::int64_t{-2}) == false);
		VERIFY((BigInt{-2} <  hamon::int8_t {-3}) == false);

		VERIFY((BigInt{-2} >  hamon::int16_t{-1}) == false);
		VERIFY((BigInt{-2} >  hamon::int32_t{-2}) == false);
		VERIFY((BigInt{-2} >  hamon::int64_t{-3}) == true);

		VERIFY((BigInt{-2} <= hamon::int8_t {-1}) == true);
		VERIFY((BigInt{-2} <= hamon::int16_t{-2}) == true);
		VERIFY((BigInt{-2} <= hamon::int32_t{-3}) == false);

		VERIFY((BigInt{-2} >= hamon::int64_t{-1}) == false);
		VERIFY((BigInt{-2} >= hamon::int8_t {-2}) == true);
		VERIFY((BigInt{-2} >= hamon::int16_t{-3}) == true);
	}
	{
		VERIFY((hamon::int8_t {-2} == BigInt{-1}) == false);
		VERIFY((hamon::int16_t{-2} == BigInt{-2}) == true);
		VERIFY((hamon::int32_t{-2} == BigInt{-3}) == false);

		VERIFY((hamon::int64_t{-2} != BigInt{-1}) == true);
		VERIFY((hamon::int8_t {-2} != BigInt{-2}) == false);
		VERIFY((hamon::int16_t{-2} != BigInt{-3}) == true);

		VERIFY((hamon::int32_t{-2} <  BigInt{-1}) == true);
		VERIFY((hamon::int64_t{-2} <  BigInt{-2}) == false);
		VERIFY((hamon::int8_t {-2} <  BigInt{-3}) == false);

		VERIFY((hamon::int16_t{-2} >  BigInt{-1}) == false);
		VERIFY((hamon::int32_t{-2} >  BigInt{-2}) == false);
		VERIFY((hamon::int64_t{-2} >  BigInt{-3}) == true);

		VERIFY((hamon::int8_t {-2} <= BigInt{-1}) == true);
		VERIFY((hamon::int16_t{-2} <= BigInt{-2}) == true);
		VERIFY((hamon::int32_t{-2} <= BigInt{-3}) == false);

		VERIFY((hamon::int64_t{-2} >= BigInt{-1}) == false);
		VERIFY((hamon::int8_t {-2} >= BigInt{-2}) == true);
		VERIFY((hamon::int16_t{-2} >= BigInt{-3}) == true);
	}
	{
		VERIFY((BigInt{0} == BigInt{-1}) == false);
		VERIFY((BigInt{0} == BigInt{ 0}) == true);
		VERIFY((BigInt{0} == BigInt{ 1}) == false);

		VERIFY((BigInt{0} != BigInt{-1}) == true);
		VERIFY((BigInt{0} != BigInt{ 0}) == false);
		VERIFY((BigInt{0} != BigInt{ 1}) == true);

		VERIFY((BigInt{0} <  BigInt{-1}) == false);
		VERIFY((BigInt{0} <  BigInt{ 0}) == false);
		VERIFY((BigInt{0} <  BigInt{ 1}) == true);

		VERIFY((BigInt{0} >  BigInt{-1}) == true);
		VERIFY((BigInt{0} >  BigInt{ 0}) == false);
		VERIFY((BigInt{0} >  BigInt{ 1}) == false);

		VERIFY((BigInt{0} <= BigInt{-1}) == false);
		VERIFY((BigInt{0} <= BigInt{ 0}) == true);
		VERIFY((BigInt{0} <= BigInt{ 1}) == true);

		VERIFY((BigInt{0} >= BigInt{-1}) == true);
		VERIFY((BigInt{0} >= BigInt{ 0}) == true);
		VERIFY((BigInt{0} >= BigInt{ 1}) == false);
	}
	{
		VERIFY((BigInt{0} == hamon::int8_t{-1}) == false);
		VERIFY((BigInt{0} == hamon::int8_t{ 0}) == true);
		VERIFY((BigInt{0} == hamon::int8_t{ 1}) == false);

		VERIFY((BigInt{0} != hamon::int8_t{-1}) == true);
		VERIFY((BigInt{0} != hamon::int8_t{ 0}) == false);
		VERIFY((BigInt{0} != hamon::int8_t{ 1}) == true);

		VERIFY((BigInt{0} <  hamon::int8_t{-1}) == false);
		VERIFY((BigInt{0} <  hamon::int8_t{ 0}) == false);
		VERIFY((BigInt{0} <  hamon::int8_t{ 1}) == true);

		VERIFY((BigInt{0} >  hamon::int8_t{-1}) == true);
		VERIFY((BigInt{0} >  hamon::int8_t{ 0}) == false);
		VERIFY((BigInt{0} >  hamon::int8_t{ 1}) == false);

		VERIFY((BigInt{0} <= hamon::int8_t{-1}) == false);
		VERIFY((BigInt{0} <= hamon::int8_t{ 0}) == true);
		VERIFY((BigInt{0} <= hamon::int8_t{ 1}) == true);

		VERIFY((BigInt{0} >= hamon::int8_t{-1}) == true);
		VERIFY((BigInt{0} >= hamon::int8_t{ 0}) == true);
		VERIFY((BigInt{0} >= hamon::int8_t{ 1}) == false);
	}
	{
		VERIFY((hamon::int8_t{0} == BigInt{-1}) == false);
		VERIFY((hamon::int8_t{0} == BigInt{ 0}) == true);
		VERIFY((hamon::int8_t{0} == BigInt{ 1}) == false);

		VERIFY((hamon::int8_t{0} != BigInt{-1}) == true);
		VERIFY((hamon::int8_t{0} != BigInt{ 0}) == false);
		VERIFY((hamon::int8_t{0} != BigInt{ 1}) == true);

		VERIFY((hamon::int8_t{0} <  BigInt{-1}) == false);
		VERIFY((hamon::int8_t{0} <  BigInt{ 0}) == false);
		VERIFY((hamon::int8_t{0} <  BigInt{ 1}) == true);

		VERIFY((hamon::int8_t{0} >  BigInt{-1}) == true);
		VERIFY((hamon::int8_t{0} >  BigInt{ 0}) == false);
		VERIFY((hamon::int8_t{0} >  BigInt{ 1}) == false);

		VERIFY((hamon::int8_t{0} <= BigInt{-1}) == false);
		VERIFY((hamon::int8_t{0} <= BigInt{ 0}) == true);
		VERIFY((hamon::int8_t{0} <= BigInt{ 1}) == true);

		VERIFY((hamon::int8_t{0} >= BigInt{-1}) == true);
		VERIFY((hamon::int8_t{0} >= BigInt{ 0}) == true);
		VERIFY((hamon::int8_t{0} >= BigInt{ 1}) == false);
	}
	{
		VERIFY((BigInt{2} == BigInt{1}) == false);
		VERIFY((BigInt{2} == BigInt{2}) == true);
		VERIFY((BigInt{2} == BigInt{3}) == false);

		VERIFY((BigInt{2} != BigInt{1}) == true);
		VERIFY((BigInt{2} != BigInt{2}) == false);
		VERIFY((BigInt{2} != BigInt{3}) == true);

		VERIFY((BigInt{2} <  BigInt{1}) == false);
		VERIFY((BigInt{2} <  BigInt{2}) == false);
		VERIFY((BigInt{2} <  BigInt{3}) == true);

		VERIFY((BigInt{2} >  BigInt{1}) == true);
		VERIFY((BigInt{2} >  BigInt{2}) == false);
		VERIFY((BigInt{2} >  BigInt{3}) == false);

		VERIFY((BigInt{2} <= BigInt{1}) == false);
		VERIFY((BigInt{2} <= BigInt{2}) == true);
		VERIFY((BigInt{2} <= BigInt{3}) == true);

		VERIFY((BigInt{2} >= BigInt{1}) == true);
		VERIFY((BigInt{2} >= BigInt{2}) == true);
		VERIFY((BigInt{2} >= BigInt{3}) == false);
	}
	{
		VERIFY((BigInt{2} == hamon::uint8_t {1}) == false);
		VERIFY((BigInt{2} == hamon::uint16_t{2}) == true);
		VERIFY((BigInt{2} == hamon::uint32_t{3}) == false);

		VERIFY((BigInt{2} != hamon::uint64_t{1}) == true);
		VERIFY((BigInt{2} != hamon::uint8_t {2}) == false);
		VERIFY((BigInt{2} != hamon::uint16_t{3}) == true);

		VERIFY((BigInt{2} <  hamon::uint32_t{1}) == false);
		VERIFY((BigInt{2} <  hamon::uint64_t{2}) == false);
		VERIFY((BigInt{2} <  hamon::uint8_t {3}) == true);

		VERIFY((BigInt{2} >  hamon::uint16_t{1}) == true);
		VERIFY((BigInt{2} >  hamon::uint32_t{2}) == false);
		VERIFY((BigInt{2} >  hamon::uint64_t{3}) == false);

		VERIFY((BigInt{2} <= hamon::uint8_t {1}) == false);
		VERIFY((BigInt{2} <= hamon::uint16_t{2}) == true);
		VERIFY((BigInt{2} <= hamon::uint32_t{3}) == true);

		VERIFY((BigInt{2} >= hamon::uint64_t{1}) == true);
		VERIFY((BigInt{2} >= hamon::uint8_t {2}) == true);
		VERIFY((BigInt{2} >= hamon::uint16_t{3}) == false);
	}
	{
		VERIFY((hamon::uint8_t {2} == BigInt{1}) == false);
		VERIFY((hamon::uint16_t{2} == BigInt{2}) == true);
		VERIFY((hamon::uint32_t{2} == BigInt{3}) == false);

		VERIFY((hamon::uint64_t{2} != BigInt{1}) == true);
		VERIFY((hamon::uint8_t {2} != BigInt{2}) == false);
		VERIFY((hamon::uint16_t{2} != BigInt{3}) == true);

		VERIFY((hamon::uint32_t{2} <  BigInt{1}) == false);
		VERIFY((hamon::uint64_t{2} <  BigInt{2}) == false);
		VERIFY((hamon::uint8_t {2} <  BigInt{3}) == true);

		VERIFY((hamon::uint16_t{2} >  BigInt{1}) == true);
		VERIFY((hamon::uint32_t{2} >  BigInt{2}) == false);
		VERIFY((hamon::uint64_t{2} >  BigInt{3}) == false);

		VERIFY((hamon::uint8_t {2} <= BigInt{1}) == false);
		VERIFY((hamon::uint16_t{2} <= BigInt{2}) == true);
		VERIFY((hamon::uint32_t{2} <= BigInt{3}) == true);

		VERIFY((hamon::uint64_t{2} >= BigInt{1}) == true);
		VERIFY((hamon::uint8_t {2} >= BigInt{2}) == true);
		VERIFY((hamon::uint16_t{2} >= BigInt{3}) == false);
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
		VERIFY((BigInt{-1} < BigInt{-2}) == false);
		VERIFY((BigInt{-1} < BigInt{-1}) == false);
		VERIFY((BigInt{-1} < BigInt{ 0}) == true);
		VERIFY((BigInt{-1} < BigInt{ 1}) == true);
		VERIFY((BigInt{-1} < BigInt{ 2}) == true);
	}
	{
		VERIFY((BigInt{1} == BigInt{-2}) == false);
		VERIFY((BigInt{1} == BigInt{-1}) == false);
		VERIFY((BigInt{1} == BigInt{ 0}) == false);
		VERIFY((BigInt{1} == BigInt{ 1}) == true);
		VERIFY((BigInt{1} == BigInt{ 2}) == false);

		VERIFY((BigInt{1} != BigInt{-2}) == true);
		VERIFY((BigInt{1} != BigInt{-1}) == true);
		VERIFY((BigInt{1} != BigInt{ 0}) == true);
		VERIFY((BigInt{1} != BigInt{ 1}) == false);
		VERIFY((BigInt{1} != BigInt{ 2}) == true);

		VERIFY((BigInt{1} <  BigInt{-2}) == false);
		VERIFY((BigInt{1} <  BigInt{-1}) == false);
		VERIFY((BigInt{1} <  BigInt{ 0}) == false);
		VERIFY((BigInt{1} <  BigInt{ 1}) == false);
		VERIFY((BigInt{1} <  BigInt{ 2}) == true);

		VERIFY((BigInt{1} >  BigInt{-2}) == true);
		VERIFY((BigInt{1} >  BigInt{-1}) == true);
		VERIFY((BigInt{1} >  BigInt{ 0}) == true);
		VERIFY((BigInt{1} >  BigInt{ 1}) == false);
		VERIFY((BigInt{1} >  BigInt{ 2}) == false);

		VERIFY((BigInt{1} <= BigInt{-2}) == false);
		VERIFY((BigInt{1} <= BigInt{-1}) == false);
		VERIFY((BigInt{1} <= BigInt{ 0}) == false);
		VERIFY((BigInt{1} <= BigInt{ 1}) == true);
		VERIFY((BigInt{1} <= BigInt{ 2}) == true);

		VERIFY((BigInt{1} >= BigInt{-2}) == true);
		VERIFY((BigInt{1} >= BigInt{-1}) == true);
		VERIFY((BigInt{1} >= BigInt{ 0}) == true);
		VERIFY((BigInt{1} >= BigInt{ 1}) == true);
		VERIFY((BigInt{1} >= BigInt{ 2}) == false);
	}
	{
		VERIFY((hamon::uint8_t {1} == BigInt{-2}) == false);
		VERIFY((hamon::uint16_t{1} == BigInt{-1}) == false);
		VERIFY((hamon::uint32_t{1} == BigInt{ 0}) == false);
		VERIFY((hamon::uint64_t{1} == BigInt{ 1}) == true);
		VERIFY((hamon::uint8_t {1} == BigInt{ 2}) == false);

		VERIFY((hamon::uint16_t{1} != BigInt{-2}) == true);
		VERIFY((hamon::uint32_t{1} != BigInt{-1}) == true);
		VERIFY((hamon::uint64_t{1} != BigInt{ 0}) == true);
		VERIFY((hamon::uint8_t {1} != BigInt{ 1}) == false);
		VERIFY((hamon::uint16_t{1} != BigInt{ 2}) == true);

		VERIFY((hamon::uint32_t{1} <  BigInt{-2}) == false);
		VERIFY((hamon::uint64_t{1} <  BigInt{-1}) == false);
		VERIFY((hamon::uint8_t {1} <  BigInt{ 0}) == false);
		VERIFY((hamon::uint16_t{1} <  BigInt{ 1}) == false);
		VERIFY((hamon::uint32_t{1} <  BigInt{ 2}) == true);

		VERIFY((hamon::uint64_t{1} >  BigInt{-2}) == true);
		VERIFY((hamon::uint8_t {1} >  BigInt{-1}) == true);
		VERIFY((hamon::uint16_t{1} >  BigInt{ 0}) == true);
		VERIFY((hamon::uint32_t{1} >  BigInt{ 1}) == false);
		VERIFY((hamon::uint64_t{1} >  BigInt{ 2}) == false);

		VERIFY((hamon::uint8_t {1} <= BigInt{-2}) == false);
		VERIFY((hamon::uint16_t{1} <= BigInt{-1}) == false);
		VERIFY((hamon::uint32_t{1} <= BigInt{ 0}) == false);
		VERIFY((hamon::uint64_t{1} <= BigInt{ 1}) == true);
		VERIFY((hamon::uint8_t {1} <= BigInt{ 2}) == true);

		VERIFY((hamon::uint16_t{1} >= BigInt{-2}) == true);
		VERIFY((hamon::uint32_t{1} >= BigInt{-1}) == true);
		VERIFY((hamon::uint64_t{1} >= BigInt{ 0}) == true);
		VERIFY((hamon::uint8_t {1} >= BigInt{ 1}) == true);
		VERIFY((hamon::uint16_t{1} >= BigInt{ 2}) == false);
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

		VERIFY((x1 == BigInt{1}) == false);
		VERIFY((x1 == BigInt{2}) == true);
		VERIFY((x1 == BigInt{3}) == false);

		VERIFY((x1 != BigInt{1}) == true);
		VERIFY((x1 != BigInt{2}) == false);
		VERIFY((x1 != BigInt{3}) == true);

		VERIFY((x1 <  BigInt{1}) == false);
		VERIFY((x1 <  BigInt{2}) == false);
		VERIFY((x1 <  BigInt{3}) == true);

		VERIFY((x1 >  BigInt{1}) == true);
		VERIFY((x1 >  BigInt{2}) == false);
		VERIFY((x1 >  BigInt{3}) == false);

		VERIFY((x1 <= BigInt{1}) == false);
		VERIFY((x1 <= BigInt{2}) == true);
		VERIFY((x1 <= BigInt{3}) == true);

		VERIFY((x1 >= BigInt{1}) == true);
		VERIFY((x1 >= BigInt{2}) == true);
		VERIFY((x1 >= BigInt{3}) == false);
	}
	{
		VERIFY((BigInt(-1) < BigInt{0}) == false);
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

#undef VERIFY

GTEST_TEST(BigIntTest, CompareTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(CompareSignedTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareSignedTest<hamon::inplace_bigint<128>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareSignedTest<hamon::inplace_bigint<256>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareSignedTest<hamon::inplace_bigint<512>>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareSignedTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareSignedTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareSignedTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(CompareSignedTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(CompareSignedTest<hamon::int2048_t>());

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(CompareSignedTest2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareSignedTest2<hamon::inplace_bigint<256>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareSignedTest2<hamon::inplace_bigint<512>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareSignedTest2<hamon::inplace_bigint<1024>>());

//	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareSignedTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareSignedTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(CompareSignedTest2<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(CompareSignedTest2<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(CompareSignedTest2<hamon::int2048_t>());

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

}	// namespace bigint_compare_test

}	// namespace hamon_bigint_test
