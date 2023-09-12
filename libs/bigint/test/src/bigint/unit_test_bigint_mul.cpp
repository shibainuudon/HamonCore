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
		auto x = BigInt(2) * BigInt(3);
		VERIFY(x == BigInt(6));
	}
	{
		auto x = BigInt(2) * BigInt(-3);
		VERIFY(x == BigInt(-6));
	}
	{
		auto x = BigInt(-2) * BigInt(3);
		VERIFY(x == BigInt(-6));
	}
	{
		auto x = BigInt(-2) * BigInt(-3);
		VERIFY(x == BigInt(6));
	}
	{
		auto x = BigInt(-3) * BigInt( 0);
		VERIFY(x == BigInt(0));
	}
	{
		auto x = BigInt( 3) * BigInt( 0);
		VERIFY(x == BigInt(0));
	}
	{
		auto x = BigInt( 0) * BigInt( 256);
		VERIFY(x == BigInt(0));
	}
	{
		auto x = BigInt( 0) * BigInt(-256);
		VERIFY(x == BigInt(0));
	}
	{
		auto x = BigInt{3} * BigInt{4} * BigInt{5};
		VERIFY(x == BigInt(60));
	}
	{
		auto x = BigInt{123} * BigInt{0};
		VERIFY(x == BigInt(0));
	}
	{
		auto x = BigInt{4824} * BigInt{31};
		VERIFY(x == BigInt(149544));
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

GTEST_TEST(BigIntTest, MulTest)
{
	EXPECT_TRUE(MulTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(MulTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(MulTest<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(MulTest<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(MulTest<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(MulTest<hamon::uint2048_t>());

	EXPECT_TRUE(MulTest2<hamon::bigint>());

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

#undef VERIFY

}	// namespace bigint_mul_test

}	// namespace hamon_bigint_test
