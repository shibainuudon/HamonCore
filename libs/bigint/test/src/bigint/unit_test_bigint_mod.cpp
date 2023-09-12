/**
 *	@file	unit_test_bigint_mod.cpp
 *
 *	@brief	operator%のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_mod_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
UnsignedModTest()
{
	{
		auto x = BigInt{123} % BigInt{2};
		VERIFY(x == 1);
	}
	{
		auto x = BigInt{123} % BigInt{3};
		VERIFY(x == 0);
	}
	{
		auto x = BigInt{123} % BigInt{4};
		VERIFY(x == 3);
	}
	{
		auto x = BigInt{123} % BigInt{5};
		VERIFY(x == 3);
	}
	{
		auto x = BigInt{123} % BigInt{6};
		VERIFY(x == 3);
	}
	{
		auto x = BigInt{123} % BigInt{7};
		VERIFY(x == 4);
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
SignedModTest()
{
	{
		auto x = BigInt( 6) % BigInt( 3);
		VERIFY(x == 0);
	}
	{
		auto x = BigInt(-6) % BigInt( 3);
		VERIFY(x == 0);
	}
	{
		auto x = BigInt( 6) % BigInt(-3);
		VERIFY(x == 0);
	}
	{
		auto x = BigInt(-6) % BigInt(-3);
		VERIFY(x == 0);
	}
	{
		auto x = BigInt( 7) % BigInt( 3);
		VERIFY(x == 1);
	}
	{
		auto x = BigInt(-7) % BigInt( 3);
		VERIFY(x == -1);
	}
	{
		auto x = BigInt( 7) % BigInt(-3);
		VERIFY(x == 1);
	}
	{
		auto x = BigInt(-7) % BigInt(-3);
		VERIFY(x == -1);
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
UnsignedModTest2()
{
	{
		auto x =
			BigInt{"517232794887556900325139264240"} %
			BigInt{"97854840192602714242"};
		VERIFY(x == BigInt{"20300968082335090596"});
	}
	{
		auto x =
			BigInt{"8480533256755492072837759593696251541964"} %
			BigInt{"80317560221046790777589885826979837"};
		VERIFY(x == BigInt{"43025695824575004376318882931492645"});
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
SignedModTest2()
{
	{
		auto x =
			-BigInt{"517232794887556900325139264240"} %
			BigInt{"97854840192602714242"};
		VERIFY(x == -BigInt{"20300968082335090596"});
	}
	{
		auto x =
			BigInt{"517232794887556900325139264240"} %
			-BigInt{"97854840192602714242"};
		VERIFY(x == BigInt{"20300968082335090596"});
	}
	{
		auto x =
			-BigInt{"517232794887556900325139264240"} %
			-BigInt{"97854840192602714242"};
		VERIFY(x == -BigInt{"20300968082335090596"});
	}
	return true;
}

GTEST_TEST(BigIntTest, ModTest)
{
	EXPECT_TRUE(UnsignedModTest<hamon::bigint>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedModTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedModTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedModTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedModTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedModTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnsignedModTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnsignedModTest<hamon::int2048_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedModTest<hamon::uint32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedModTest<hamon::uint64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedModTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedModTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedModTest<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnsignedModTest<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnsignedModTest<hamon::uint2048_t>());

	EXPECT_TRUE(SignedModTest<hamon::bigint>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedModTest<hamon::int32_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedModTest<hamon::int64_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedModTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedModTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedModTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SignedModTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SignedModTest<hamon::int2048_t>());

	EXPECT_TRUE(UnsignedModTest2<hamon::bigint>());
//	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedModTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedModTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedModTest2<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnsignedModTest2<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnsignedModTest2<hamon::int2048_t>());
//	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedModTest2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedModTest2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(UnsignedModTest2<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnsignedModTest2<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(UnsignedModTest2<hamon::uint2048_t>());

	EXPECT_TRUE(SignedModTest2<hamon::bigint>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedModTest2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedModTest2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SignedModTest2<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SignedModTest2<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(SignedModTest2<hamon::int2048_t>());
}

#undef VERIFY

}	// namespace bigint_mod_test

}	// namespace hamon_bigint_test
