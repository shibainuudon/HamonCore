/**
 *	@file	unit_test_bigint_div.cpp
 *
 *	@brief	operator/のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_div_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
UnsignedDivTest()
{
	{
		auto x = BigInt( 6) / BigInt( 1);
		VERIFY(x == BigInt(6));
	}
	{
		auto x = BigInt( 6) / BigInt( 2);
		VERIFY(x == BigInt(3));
	}
	{
		auto x = BigInt( 6) / BigInt( 4);
		VERIFY(x == BigInt(1));
	}
	{
		auto x = BigInt( 6) / BigInt( 6);
		VERIFY(x == BigInt(1));
	}
	{
		auto x = BigInt( 6) / BigInt( 7);
		VERIFY(x == BigInt(0));
	}
	{
		auto x = BigInt{0x10000} / BigInt{2};
		VERIFY(x == BigInt(0x8000));
	}
	{
		auto x = BigInt{0xffff} / BigInt{2};
		VERIFY(x == BigInt(0x7fff));
	}
	{
		auto x = BigInt{999999} / BigInt{7777};
		VERIFY(x == BigInt(128));
	}
	{
		auto x = BigInt{999999999} / BigInt{999999};
		VERIFY(x == BigInt(1000));
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
SignedDivTest()
{
	{
		auto x = BigInt( 6) / BigInt( 3);
		VERIFY(x == BigInt(2));
	}
	{
		auto x = BigInt( 6) / BigInt(-3);
		VERIFY(x == BigInt(-2));
	}
	{
		auto x = BigInt(-6) / BigInt( 3);
		VERIFY(x == BigInt(-2));
	}
	{
		auto x = BigInt(-6) / BigInt(-3);
		VERIFY(x == BigInt(2));
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
UnsignedDivTest2()
{
	{
		auto x =
			BigInt{"8634445089577309591046007474873433396354"} /
			BigInt{"9509431914"};
		VERIFY(x == BigInt{"907987476819249835058654742987"});
	}
	{
		auto x =
			BigInt{"1310755439459119173246996027623904894831"} /
			BigInt{"84526411745918709879"};
		VERIFY(x == BigInt{"15507051729572655735"});
	}
	{
		auto x =
			BigInt{"38533568648101411188584683464222001686976831106787"} /
			BigInt{"504164348379621718380998627378"};
		VERIFY(x == BigInt{"76430570253425985552"});
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
SignedDivTest2()
{
	{
		auto x =
			BigInt{"8634445089577309591046007474873433396354"} /
			-BigInt{"9509431914"};
		VERIFY(x == BigInt{"-907987476819249835058654742987"});
	}
	{
		auto x =
			-BigInt{"1310755439459119173246996027623904894831"} /
			BigInt{"84526411745918709879"};
		VERIFY(x == BigInt{"-15507051729572655735"});
	}
	{
		auto x =
			-BigInt{"38533568648101411188584683464222001686976831106787"} /
			-BigInt{"504164348379621718380998627378"};
		VERIFY(x == BigInt{"76430570253425985552"});
	}
	return true;
}

GTEST_TEST(BigIntTest, DivTest)
{
	EXPECT_TRUE(UnsignedDivTest<hamon::bigint>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnsignedDivTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnsignedDivTest<hamon::int2048_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnsignedDivTest<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnsignedDivTest<hamon::uint2048_t>());

	EXPECT_TRUE(SignedDivTest<hamon::bigint>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SignedDivTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SignedDivTest<hamon::int2048_t>());

	EXPECT_TRUE(UnsignedDivTest2<hamon::bigint>());
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest2<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnsignedDivTest2<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnsignedDivTest2<hamon::int2048_t>());
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest2<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnsignedDivTest2<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnsignedDivTest2<hamon::uint2048_t>());

	EXPECT_TRUE(SignedDivTest2<hamon::bigint>());
	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivTest2<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SignedDivTest2<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SignedDivTest2<hamon::int2048_t>());
}

#undef VERIFY

}	// namespace bigint_div_test

}	// namespace hamon_bigint_test
