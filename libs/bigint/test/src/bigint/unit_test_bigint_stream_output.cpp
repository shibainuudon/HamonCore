/**
 *	@file	unit_test_bigint_stream_output.cpp
 *
 *	@brief	ストリームへの出力のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <hamon/sstream/stringstream.hpp>
#include <gtest/gtest.h>

namespace hamon_bigint_test
{

namespace bigint_stream_output_test
{

template <typename BigInt>
inline void StreamOutputSignedTest()
{
	{
		BigInt const x = -123;
		hamon::stringstream ss;
		ss << x;
		EXPECT_EQ(ss.str(), "-123");
	}
	{
		BigInt const x = -629968538327;
		hamon::stringstream ss;
		ss << x;
		EXPECT_EQ(ss.str(), "-629968538327");
	}
}

template <typename BigInt>
inline void StreamOutputSignedTest2()
{
	{
		BigInt const x {"-385335686481014111885846834642220016869768311067870000000000"};
		hamon::stringstream ss;
		ss << x;
		EXPECT_EQ(ss.str(), "-385335686481014111885846834642220016869768311067870000000000");
	}
}

template <typename BigInt>
inline void StreamOutputUnignedTest()
{
	{
		BigInt const x = 0;
		hamon::stringstream ss;
		ss << x;
		EXPECT_EQ(ss.str(), "0");
	}
	{
		BigInt const x = 123;
		hamon::stringstream ss;
		ss << x;
		EXPECT_EQ(ss.str(), "123");
	}
	{
		BigInt const x = 629968538327;
		hamon::stringstream ss;
		ss << x;
		EXPECT_EQ(ss.str(), "629968538327");
	}
}

template <typename BigInt>
inline void StreamOutputUnignedTest2()
{
	{
		BigInt const x {"314159265358979323846264338327950288419716939937510"};
		hamon::stringstream ss;
		ss << x;
		EXPECT_EQ(ss.str(), "314159265358979323846264338327950288419716939937510");
	}
}

GTEST_TEST(BigIntTest, StreamOutputTest)
{
	StreamOutputSignedTest<hamon::bigint>();
	StreamOutputSignedTest<hamon::inplace_bigint<128>>();
	StreamOutputSignedTest<hamon::inplace_bigint<256>>();
	StreamOutputSignedTest<hamon::inplace_bigint<512>>();
	StreamOutputSignedTest<hamon::int64_t>();
	StreamOutputSignedTest<hamon::int128_t>();
	StreamOutputSignedTest<hamon::int256_t>();
	StreamOutputSignedTest<hamon::int512_t>();
	StreamOutputSignedTest<hamon::int1024_t>();
	StreamOutputSignedTest<hamon::int2048_t>();
	
	StreamOutputSignedTest2<hamon::bigint>();
	StreamOutputSignedTest2<hamon::inplace_bigint<256>>();
	StreamOutputSignedTest2<hamon::inplace_bigint<512>>();
	StreamOutputSignedTest2<hamon::inplace_bigint<1024>>();
//	StreamOutputSignedTest2<hamon::int128_t>();
	StreamOutputSignedTest2<hamon::int256_t>();
	StreamOutputSignedTest2<hamon::int512_t>();
	StreamOutputSignedTest2<hamon::int1024_t>();
	StreamOutputSignedTest2<hamon::int2048_t>();
	
	StreamOutputUnignedTest<hamon::bigint>();
	StreamOutputUnignedTest<hamon::inplace_bigint<128>>();
	StreamOutputUnignedTest<hamon::inplace_bigint<256>>();
	StreamOutputUnignedTest<hamon::inplace_bigint<512>>();
	StreamOutputUnignedTest<hamon::int64_t>();
	StreamOutputUnignedTest<hamon::int128_t>();
	StreamOutputUnignedTest<hamon::int256_t>();
	StreamOutputUnignedTest<hamon::int512_t>();
	StreamOutputUnignedTest<hamon::int1024_t>();
	StreamOutputUnignedTest<hamon::int2048_t>();
	StreamOutputUnignedTest<hamon::uint64_t>();
	StreamOutputUnignedTest<hamon::uint128_t>();
	StreamOutputUnignedTest<hamon::uint256_t>();
	StreamOutputUnignedTest<hamon::uint512_t>();
	StreamOutputUnignedTest<hamon::uint1024_t>();
	StreamOutputUnignedTest<hamon::uint2048_t>();

	StreamOutputUnignedTest2<hamon::bigint>();
	StreamOutputUnignedTest2<hamon::inplace_bigint<256>>();
	StreamOutputUnignedTest2<hamon::inplace_bigint<512>>();
	StreamOutputUnignedTest2<hamon::inplace_bigint<1024>>();
//	StreamOutputUnignedTest2<hamon::int128_t>();
	StreamOutputUnignedTest2<hamon::int256_t>();
	StreamOutputUnignedTest2<hamon::int512_t>();
	StreamOutputUnignedTest2<hamon::int1024_t>();
	StreamOutputUnignedTest2<hamon::int2048_t>();
//	StreamOutputUnignedTest2<hamon::uint128_t>();
	StreamOutputUnignedTest2<hamon::uint256_t>();
	StreamOutputUnignedTest2<hamon::uint512_t>();
	StreamOutputUnignedTest2<hamon::uint1024_t>();
	StreamOutputUnignedTest2<hamon::uint2048_t>();
}

}	// namespace bigint_stream_output_test

}	// namespace hamon_bigint_test
