/**
 *	@file	unit_test_bigint_div.cpp
 *
 *	@brief	operator/のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

//#include <chrono>

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
		VERIFY(BigInt( 6) / BigInt( 1) == BigInt(6));
		VERIFY(BigInt( 6) / BigInt( 2) == BigInt(3));
		VERIFY(BigInt( 6) / BigInt( 4) == BigInt(1));
		VERIFY(BigInt( 6) / BigInt( 6) == BigInt(1));
		VERIFY(BigInt( 6) / BigInt( 7) == BigInt(0));
		VERIFY(BigInt{0x10000} / BigInt{2} == BigInt(0x8000));
		VERIFY(BigInt{0xffff} / BigInt{2} == BigInt(0x7fff));
		VERIFY(BigInt{999999} / BigInt{7777} == BigInt(128));
		VERIFY(BigInt{999999999} / BigInt{999999} == BigInt(1000));
	}
	{
		VERIFY(BigInt( 6) / hamon::uint8_t( 1) == BigInt(6));
		VERIFY(BigInt( 6) / hamon::uint16_t( 2) == BigInt(3));
		VERIFY(BigInt( 6) / hamon::uint32_t( 4) == BigInt(1));
		VERIFY(BigInt( 6) / hamon::uint64_t( 6) == BigInt(1));
		VERIFY(BigInt( 6) / hamon::uint8_t( 7) == BigInt(0));
		VERIFY(BigInt{0x10000} / hamon::uint8_t{2} == BigInt(0x8000));
		VERIFY(BigInt{0xffff} / hamon::uint16_t{2} == BigInt(0x7fff));
		VERIFY(BigInt{999999} / hamon::uint32_t{7777} == BigInt(128));
		VERIFY(BigInt{999999999} / hamon::uint64_t{999999} == BigInt(1000));
	}
	{
		VERIFY(hamon::uint8_t ( 6) / BigInt( 1) == BigInt(6));
		VERIFY(hamon::uint16_t( 6) / BigInt( 2) == BigInt(3));
		VERIFY(hamon::uint32_t( 6) / BigInt( 4) == BigInt(1));
		VERIFY(hamon::uint64_t( 6) / BigInt( 6) == BigInt(1));
		VERIFY(hamon::uint8_t ( 6) / BigInt( 7) == BigInt(0));
		VERIFY(hamon::uint32_t{0x10000} / BigInt{2} == BigInt(0x8000));
		VERIFY(hamon::uint16_t{0xffff} / BigInt{2} == BigInt(0x7fff));
		VERIFY(hamon::uint32_t{999999} / BigInt{7777} == BigInt(128));
		VERIFY(hamon::uint64_t{999999999} / BigInt{999999} == BigInt(1000));
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
SignedDivTest()
{
	{
		VERIFY(BigInt( 6) / BigInt( 3) == BigInt(2));
		VERIFY(BigInt( 6) / BigInt(-3) == BigInt(-2));
		VERIFY(BigInt(-6) / BigInt( 3) == BigInt(-2));
		VERIFY(BigInt(-6) / BigInt(-3) == BigInt(2));
	}
	{
		VERIFY(BigInt( 6) / hamon::int8_t ( 3) == BigInt(2));
		VERIFY(BigInt( 6) / hamon::int16_t(-3) == BigInt(-2));
		VERIFY(BigInt(-6) / hamon::int32_t( 3) == BigInt(-2));
		VERIFY(BigInt(-6) / hamon::int64_t(-3) == BigInt(2));
	}
	{
		VERIFY(hamon::int8_t ( 6) / BigInt( 3) == BigInt(2));
		VERIFY(hamon::int16_t( 6) / BigInt(-3) == BigInt(-2));
		VERIFY(hamon::int32_t(-6) / BigInt( 3) == BigInt(-2));
		VERIFY(hamon::int64_t(-6) / BigInt(-3) == BigInt(2));
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

#undef VERIFY

GTEST_TEST(BigIntTest, DivTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest<hamon::inplace_bigint<128>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest<hamon::inplace_bigint<512>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest<hamon::inplace_bigint<2048>>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnsignedDivTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnsignedDivTest<hamon::int2048_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnsignedDivTest<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnsignedDivTest<hamon::uint2048_t>());

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(SignedDivTest<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivTest<hamon::inplace_bigint<128>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivTest<hamon::inplace_bigint<512>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivTest<hamon::inplace_bigint<2048>>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SignedDivTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SignedDivTest<hamon::int2048_t>());

	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(UnsignedDivTest2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest2<hamon::inplace_bigint<255>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest2<hamon::inplace_bigint<999>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedDivTest2<hamon::inplace_bigint<1033>>());

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

	/*HAMON_CXX20_CONSTEXPR_*/EXPECT_TRUE(SignedDivTest2<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivTest2<hamon::inplace_bigint<256>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivTest2<hamon::inplace_bigint<512>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivTest2<hamon::inplace_bigint<2048>>());

	//HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedDivTest2<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SignedDivTest2<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SignedDivTest2<hamon::int2048_t>());

	{
		using BigInt = hamon::inplace_bigint<4000>;

		{
			auto x = BigInt{"99999999999999999"} << 47;

			BigInt y{};
			hamon::pow_n(y, BigInt{5}, 17);

			auto t = x / y;
			EXPECT_EQ(t, BigInt{"18446744073709551431"});
		}
		{
			auto x = BigInt{"4940656458412"} << 802;

			BigInt y{};
			hamon::pow_n(y, BigInt{5}, 336);

			auto t = x / y;
			EXPECT_EQ(t, BigInt{"18446744073707813813"});
		}
		{
			auto x = BigInt{"70064923216240853546186479164495806564013097093825"} << 119;

			BigInt y{};
			hamon::pow_n(y, BigInt{5}, 95);

			auto t = x / y;
			EXPECT_EQ(t, BigInt{"18446744073709551615"});
		}
	}

#if 0
	{
		auto t0 = std::chrono::high_resolution_clock::now();
		{
			using BigInt = hamon::inplace_bigint<4000>;

			BigInt x{
				"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
				"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
				"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
				"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
				"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
				"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
				"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
				"1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
			};

			for (int i = 0; i < 10; ++i)
			{
				BigInt y{10};
				for (int j = 0; j < 800; ++j)
				{
					BigInt q = x / y;
					(void)q;
					y *= 10;
				}
			}
		}

		auto t1 = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
		std::cout << elapsed.count() << " ms" << std::endl;
	}
	// 最適化前
	// Debug:   2052 ms
	// Release:  331 ms

	// div_modで使っているbigint_algo::multiplyを最適化
	// Debug:   1899 ms
	// Release:  339 ms

	// div_modを最適化
	// Debug:   496 ms
	// Release:  52 ms
#endif
}

}	// namespace bigint_div_test

}	// namespace hamon_bigint_test
