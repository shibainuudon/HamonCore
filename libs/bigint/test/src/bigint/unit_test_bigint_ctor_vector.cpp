/**
 *	@file	unit_test_bigint_ctor_vector.cpp
 *
 *	@brief	vector_typeを引数に取るコンストラクタのテスト
 */

#include <hamon/bigint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_ctor_vector_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool test1()
{
	using VectorType = typename BigInt::vector_type;
	{
		BigInt x{1, VectorType{0}};
		VERIFY(x == BigInt{0});
	}
	{
		BigInt x{1, VectorType{42}};
		VERIFY(x == BigInt{42});
	}
	{
		BigInt x{-1, VectorType{42}};
		VERIFY(x == BigInt{-42});
	}
	{
		BigInt x{"12345678901234567890"};
		BigInt y{x.sign(), x.magnitude()};
		VERIFY(y == BigInt{12345678901234567890ULL});
	}
	{
		BigInt x{1};
		for (int i = 0; i < 30; ++i)
		{
			x *= 10;
		}
		BigInt y{x.sign(), x.magnitude()};
		VERIFY(y == BigInt{"1000000000000000000000000000000"});
	}
	{
		BigInt x{1};
		x <<= 100;
		BigInt y{-1, x.magnitude()};
		VERIFY(y == BigInt{"-1267650600228229401496703205376"});
	}
	return true;
}

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool test2()
{
	using VectorType = typename BigInt::vector_type;
	{
		BigInt x{VectorType{0}};
		VERIFY(x == BigInt{0});
	}
	{
		BigInt x{VectorType{42}};
		VERIFY(x == BigInt{42});
	}
	{
		BigInt x{"12345678901234567890"};
		BigInt y{x.value()};
		VERIFY(y == BigInt{12345678901234567890ULL});
	}
	{
		BigInt x{1};
		for (int i = 0; i < 30; ++i)
		{
			x *= 10;
		}
		BigInt y{x.value()};
		VERIFY(y == BigInt{"1000000000000000000000000000000"});
	}
	{
		BigInt x{1};
		x <<= 100;
		BigInt y{x.value()};
		VERIFY(y == BigInt{"1267650600228229401496703205376"});
	}
	return true;
}

#undef VERIFY

GTEST_TEST(BigIntTest, CtorVectorTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test1<hamon::bigint>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test1<hamon::inplace_bigint<128>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test1<hamon::inplace_bigint<256>>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test1<hamon::inplace_bigint<512>>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2<hamon::int512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2<hamon::int1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2<hamon::int2048_t>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2<hamon::uint512_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2<hamon::uint1024_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2<hamon::uint2048_t>());
}

}	// namespace bigint_ctor_vector_test

}	// namespace hamon_bigint_test
