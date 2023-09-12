/**
 *	@file	unit_test_bigint_to_integral.cpp
 *
 *	@brief	整数型への変換のテスト
 */

#include <hamon/bigint.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_bigint_test
{

namespace bigint_to_integral_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename BigInt>
inline HAMON_CXX14_CONSTEXPR bool
ToIntegralTest()
{
	{
		BigInt const x = 0;
		hamon::int8_t   const a(x);
		hamon::int16_t  const b(x);
		hamon::int32_t  const c(x);
		hamon::int64_t  const d(x);
		hamon::uint8_t  const e(x);
		hamon::uint16_t const f(x);
		hamon::uint32_t const g(x);
		hamon::uint64_t const h(x);
		VERIFY(a == 0);
		VERIFY(b == 0);
		VERIFY(c == 0);
		VERIFY(d == 0);
		VERIFY(e == 0);
		VERIFY(f == 0);
		VERIFY(g == 0);
		VERIFY(h == 0);
	}
	{
		BigInt const x = 1;
		hamon::int8_t   const a(x);
		hamon::int16_t  const b(x);
		hamon::int32_t  const c(x);
		hamon::int64_t  const d(x);
		hamon::uint8_t  const e(x);
		hamon::uint16_t const f(x);
		hamon::uint32_t const g(x);
		hamon::uint64_t const h(x);
		VERIFY(a == static_cast<hamon::int8_t  >(1));
		VERIFY(b == static_cast<hamon::int16_t >(1));
		VERIFY(c == static_cast<hamon::int32_t >(1));
		VERIFY(d == static_cast<hamon::int64_t >(1));
		VERIFY(e == static_cast<hamon::uint8_t >(1));
		VERIFY(f == static_cast<hamon::uint16_t>(1));
		VERIFY(g == static_cast<hamon::uint32_t>(1));
		VERIFY(h == static_cast<hamon::uint64_t>(1));
	}
	{
		BigInt const x = -1;
		hamon::int8_t   const a(x);
		hamon::int16_t  const b(x);
		hamon::int32_t  const c(x);
		hamon::int64_t  const d(x);
		hamon::uint8_t  const e(x);
		hamon::uint16_t const f(x);
		hamon::uint32_t const g(x);
		hamon::uint64_t const h(x);
		VERIFY(a == static_cast<hamon::int8_t  >(-1));
		VERIFY(b == static_cast<hamon::int16_t >(-1));
		VERIFY(c == static_cast<hamon::int32_t >(-1));
		VERIFY(d == static_cast<hamon::int64_t >(-1));
		VERIFY(e == static_cast<hamon::uint8_t >(-1));
		VERIFY(f == static_cast<hamon::uint16_t>(-1));
		VERIFY(g == static_cast<hamon::uint32_t>(-1));
		VERIFY(h == static_cast<hamon::uint64_t>(-1));
	}
	{
		BigInt const x = 0xff;
		hamon::int8_t   const a(x);
		hamon::int16_t  const b(x);
		hamon::int32_t  const c(x);
		hamon::int64_t  const d(x);
		hamon::uint8_t  const e(x);
		hamon::uint16_t const f(x);
		hamon::uint32_t const g(x);
		hamon::uint64_t const h(x);
		VERIFY(a == static_cast<hamon::int8_t  >(0xff));
		VERIFY(b == static_cast<hamon::int16_t >(0xff));
		VERIFY(c == static_cast<hamon::int32_t >(0xff));
		VERIFY(d == static_cast<hamon::int64_t >(0xff));
		VERIFY(e == static_cast<hamon::uint8_t >(0xff));
		VERIFY(f == static_cast<hamon::uint16_t>(0xff));
		VERIFY(g == static_cast<hamon::uint32_t>(0xff));
		VERIFY(h == static_cast<hamon::uint64_t>(0xff));
	}
	{
		BigInt const x = -0xff;
		hamon::int8_t   const a(x);
		hamon::int16_t  const b(x);
		hamon::int32_t  const c(x);
		hamon::int64_t  const d(x);
		hamon::uint8_t  const e(x);
		hamon::uint16_t const f(x);
		hamon::uint32_t const g(x);
		hamon::uint64_t const h(x);
		VERIFY(a == static_cast<hamon::int8_t  >(-0xff));
		VERIFY(b == static_cast<hamon::int16_t >(-0xff));
		VERIFY(c == static_cast<hamon::int32_t >(-0xff));
		VERIFY(d == static_cast<hamon::int64_t >(-0xff));
		VERIFY(e == static_cast<hamon::uint8_t >(-0xff));
		VERIFY(f == static_cast<hamon::uint16_t>(-0xff));
		VERIFY(g == static_cast<hamon::uint32_t>(-0xff));
		VERIFY(h == static_cast<hamon::uint64_t>(-0xff));
	}
	{
		BigInt const x = 0xffff;
		hamon::int8_t   const a(x);
		hamon::int16_t  const b(x);
		hamon::int32_t  const c(x);
		hamon::int64_t  const d(x);
		hamon::uint8_t  const e(x);
		hamon::uint16_t const f(x);
		hamon::uint32_t const g(x);
		hamon::uint64_t const h(x);
		VERIFY(a == static_cast<hamon::int8_t  >(0xffff));
		VERIFY(b == static_cast<hamon::int16_t >(0xffff));
		VERIFY(c == static_cast<hamon::int32_t >(0xffff));
		VERIFY(d == static_cast<hamon::int64_t >(0xffff));
		VERIFY(e == static_cast<hamon::uint8_t >(0xffff));
		VERIFY(f == static_cast<hamon::uint16_t>(0xffff));
		VERIFY(g == static_cast<hamon::uint32_t>(0xffff));
		VERIFY(h == static_cast<hamon::uint64_t>(0xffff));
	}
	{
		BigInt const x = -0xffff;
		hamon::int8_t   const a(x);
		hamon::int16_t  const b(x);
		hamon::int32_t  const c(x);
		hamon::int64_t  const d(x);
		hamon::uint8_t  const e(x);
		hamon::uint16_t const f(x);
		hamon::uint32_t const g(x);
		hamon::uint64_t const h(x);
		VERIFY(a == static_cast<hamon::int8_t  >(-0xffff));
		VERIFY(b == static_cast<hamon::int16_t >(-0xffff));
		VERIFY(c == static_cast<hamon::int32_t >(-0xffff));
		VERIFY(d == static_cast<hamon::int64_t >(-0xffff));
		VERIFY(e == static_cast<hamon::uint8_t >(-0xffff));
		VERIFY(f == static_cast<hamon::uint16_t>(-0xffff));
		VERIFY(g == static_cast<hamon::uint32_t>(-0xffff));
		VERIFY(h == static_cast<hamon::uint64_t>(-0xffff));
	}
	{
		BigInt const x = 0x01234567;
		hamon::int8_t   const a(x);
		hamon::int16_t  const b(x);
		hamon::int32_t  const c(x);
		hamon::int64_t  const d(x);
		hamon::uint8_t  const e(x);
		hamon::uint16_t const f(x);
		hamon::uint32_t const g(x);
		hamon::uint64_t const h(x);
		VERIFY(a == static_cast<hamon::int8_t  >(0x67));
		VERIFY(b == static_cast<hamon::int16_t >(0x4567));
		VERIFY(c == static_cast<hamon::int32_t >(0x01234567));
		VERIFY(d == static_cast<hamon::int64_t >(0x01234567));
		VERIFY(e == static_cast<hamon::uint8_t >(0x67));
		VERIFY(f == static_cast<hamon::uint16_t>(0x4567));
		VERIFY(g == static_cast<hamon::uint32_t>(0x01234567));
		VERIFY(h == static_cast<hamon::uint64_t>(0x01234567));
	}
	{
		BigInt const x = 0xffffffff;
		hamon::int8_t   const a(x);
		hamon::int16_t  const b(x);
		hamon::int32_t  const c(x);
		hamon::int64_t  const d(x);
		hamon::uint8_t  const e(x);
		hamon::uint16_t const f(x);
		hamon::uint32_t const g(x);
		hamon::uint64_t const h(x);
		VERIFY(a == static_cast<hamon::int8_t  >(0xffffffff));
		VERIFY(b == static_cast<hamon::int16_t >(0xffffffff));
		VERIFY(c == static_cast<hamon::int32_t >(0xffffffff));
		VERIFY(d == static_cast<hamon::int64_t >(0xffffffff));
		VERIFY(e == static_cast<hamon::uint8_t >(0xffffffff));
		VERIFY(f == static_cast<hamon::uint16_t>(0xffffffff));
		VERIFY(g == static_cast<hamon::uint32_t>(0xffffffff));
		VERIFY(h == static_cast<hamon::uint64_t>(0xffffffff));
	}
	{
		BigInt const x {"0x123456789abcdef0"};
		hamon::int8_t   const a(x);
		hamon::int16_t  const b(x);
		hamon::int32_t  const c(x);
		hamon::int64_t  const d(x);
		hamon::uint8_t  const e(x);
		hamon::uint16_t const f(x);
		hamon::uint32_t const g(x);
		hamon::uint64_t const h(x);
		VERIFY(a == static_cast<hamon::int8_t  >(0xf0));
		VERIFY(b == static_cast<hamon::int16_t >(0xdef0));
		VERIFY(c == static_cast<hamon::int32_t >(0x9abcdef0));
		VERIFY(d == static_cast<hamon::int64_t >(0x123456789abcdef0));
		VERIFY(e == static_cast<hamon::uint8_t >(0xf0));
		VERIFY(f == static_cast<hamon::uint16_t>(0xdef0));
		VERIFY(g == static_cast<hamon::uint32_t>(0x9abcdef0));
		VERIFY(h == static_cast<hamon::uint64_t>(0x123456789abcdef0));
	}
	{
		BigInt const x {"-0xfcecdcccbcac9c8c7c6c5c4c3c2c1c0c"};
		hamon::int8_t   const a(x);
		hamon::int16_t  const b(x);
		hamon::int32_t  const c(x);
		hamon::int64_t  const d(x);
		hamon::uint8_t  const e(x);
		hamon::uint16_t const f(x);
		hamon::uint32_t const g(x);
		hamon::uint64_t const h(x);
		VERIFY(a == static_cast<hamon::int8_t  >(-0x0c));
		VERIFY(b == static_cast<hamon::int16_t >(-0x1c0c));
		VERIFY(c == static_cast<hamon::int32_t >(-0x3c2c1c0c));
		VERIFY(d == static_cast<hamon::int64_t >(-0x7c6c5c4c3c2c1c0c));
		VERIFY(e == static_cast<hamon::uint8_t >(-0x0c));
		VERIFY(f == static_cast<hamon::uint16_t>(-0x1c0c));
		VERIFY(g == static_cast<hamon::uint32_t>(-0x3c2c1c0c));
		VERIFY(h == static_cast<hamon::uint64_t>(-0x7c6c5c4c3c2c1c0c));
	}
	return true;
}

GTEST_TEST(BigIntTest, ToIntegralTest)
{
	EXPECT_TRUE(ToIntegralTest<hamon::bigint>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToIntegralTest<hamon::int128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToIntegralTest<hamon::int256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToIntegralTest<hamon::int512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(ToIntegralTest<hamon::int1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(ToIntegralTest<hamon::int2048_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToIntegralTest<hamon::uint128_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToIntegralTest<hamon::uint256_t>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ToIntegralTest<hamon::uint512_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(ToIntegralTest<hamon::uint1024_t>());
	/*HAMON_CXX14_CONSTEXPR_*/EXPECT_TRUE(ToIntegralTest<hamon::uint2048_t>());
}

#undef VERIFY

}	// namespace bigint_to_integral_test

}	// namespace hamon_bigint_test
