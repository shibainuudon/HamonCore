/**
 *	@file	unit_test_bigint_mul.cpp
 *
 *	@brief	operator*のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_mul_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
MulTest()
{
	{
		VERIFY(BigInt(2) * BigInt(3) == BigInt(6));
		VERIFY(BigInt(2) * BigInt(-3) == BigInt(-6));
		VERIFY(BigInt(-2) * BigInt(3) == BigInt(-6));
		VERIFY(BigInt(-2) * BigInt(-3) == BigInt(6));
		VERIFY(BigInt(-3) * BigInt( 0) == BigInt(0));
		VERIFY(BigInt( 3) * BigInt( 0) == BigInt(0));
		VERIFY(BigInt( 0) * BigInt( 256) == BigInt(0));
		VERIFY(BigInt( 0) * BigInt(-256) == BigInt(0));
		VERIFY(BigInt{3} * BigInt{4} * BigInt{5} == BigInt(60));
		VERIFY(BigInt{123} * BigInt{0} == BigInt(0));
		VERIFY(BigInt{4824} * BigInt{31} == BigInt(149544));
		VERIFY(BigInt{123456} * BigInt{0xffffffff} == BigInt(530239482371520));
	}
	{
		VERIFY(BigInt(2) * hamon::uint8_t(3) == BigInt(6));
		VERIFY(BigInt(2) * hamon::int8_t(-3) == BigInt(-6));
		VERIFY(BigInt(-2) * hamon::uint16_t(3) == BigInt(-6));
		VERIFY(BigInt(-2) * hamon::int16_t(-3) == BigInt(6));
		VERIFY(BigInt(-3) * hamon::uint32_t( 0) == BigInt(0));
		VERIFY(BigInt( 3) * hamon::int32_t( 0) == BigInt(0));
		VERIFY(BigInt( 0) * hamon::uint64_t( 256) == BigInt(0));
		VERIFY(BigInt( 0) * hamon::int64_t(-256) == BigInt(0));
		VERIFY(BigInt{3} * int{4} * BigInt{5} == BigInt(60));
		VERIFY(BigInt{123} * short{0} == BigInt(0));
		VERIFY(BigInt{4824} * long{31} == BigInt(149544));
		VERIFY(BigInt{123456} * hamon::uint64_t{0xffffffff} == BigInt(530239482371520));
	}
	{
		VERIFY(hamon::uint8_t(2) * BigInt(3) == BigInt(6));
		VERIFY(hamon::uint16_t(2) * BigInt(-3) == BigInt(-6));
		VERIFY(hamon::int8_t(-2) * BigInt(3) == BigInt(-6));
		VERIFY(hamon::int16_t(-2) * BigInt(-3) == BigInt(6));
		VERIFY(hamon::int32_t(-3) * BigInt( 0) == BigInt(0));
		VERIFY(hamon::uint32_t( 3) * BigInt( 0) == BigInt(0));
		VERIFY(hamon::uint64_t( 0) * BigInt( 256) == BigInt(0));
		VERIFY(hamon::int64_t( 0) * BigInt(-256) == BigInt(0));
		VERIFY(int{3} * BigInt{4} * BigInt{5} == BigInt(60));
		VERIFY(short{123} * BigInt{0} == BigInt(0));
		VERIFY(long{4824} * BigInt{31} == BigInt(149544));
		VERIFY(hamon::uint64_t{123456} * BigInt{0xffffffff} == BigInt(530239482371520));
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
MulTest2()
{
	{
		auto x =
			BigInt{"49380"} *
			BigInt{"315921325115052764877243681807"};
		VERIFY(x == BigInt{"15600195034181305529638293007629660"});
	}
	{
		auto x =
			BigInt{"190512936091683569991370045758"} *
			BigInt{"36968175473499613142"};
		VERIFY(x == BigInt{"7042915651408975798024456175730948594979838151636"});
	}
	{
		auto x =
			-BigInt{"36968175473499613142"} *
			BigInt{"190512936091683569991370045758"};
		VERIFY(x == BigInt{"-7042915651408975798024456175730948594979838151636"});
	}
	{
		auto x =
			BigInt{"36968175473499613142"} *
			-BigInt{"190512936091683569991370045758"};
		VERIFY(x == BigInt{"-7042915651408975798024456175730948594979838151636"});
	}
	return true;
}

#undef VERIFY

GTEST_TEST(BigIntTest, MulTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(MulTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest<hamon::inplace_bigint<128>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest<hamon::inplace_bigint<256>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest<hamon::inplace_bigint<1024>>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(MulTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(MulTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(MulTest<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(MulTest<hamon::uint2048_t>());

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(MulTest2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest2<hamon::inplace_bigint<512>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest2<hamon::inplace_bigint<1024>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest2<hamon::inplace_bigint<2048>>());

//	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest2<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(MulTest2<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(MulTest2<hamon::int2048_t>());

//	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest2<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(MulTest2<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(MulTest2<hamon::uint2048_t>());
}

}	// namespace bigint_mul_test

}	// namespace hamon_bigint_test
