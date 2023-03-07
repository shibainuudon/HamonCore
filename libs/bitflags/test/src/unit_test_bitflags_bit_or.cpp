/**
 *	@file	unit_test_bitflags_bit_or.cpp
 *
 *	@brief	operator|のテスト
 */

#include <hamon/bitflags.hpp>
#include <hamon/type_traits/is_detected.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "bitflags_test.hpp"

namespace hamon_bitflags_test
{

namespace bit_or_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename U>
using invoke_bit_or = decltype(hamon::declval<T>() | hamon::declval<U>());

static_assert( hamon::is_detected<invoke_bit_or, Bitflag1 const&, Bitflag1 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_or, Bitflag1 const&, Bitflag2 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_or, Bitflag1 const&, Bitflag3 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_or, Bitflag1 const&, Enum1 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_or, Bitflag1 const&, int>::value, "");
static_assert(!hamon::is_detected<invoke_bit_or, Bitflag2 const&, Bitflag1 const&>::value, "");
static_assert( hamon::is_detected<invoke_bit_or, Bitflag2 const&, Bitflag2 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_or, Bitflag2 const&, Bitflag3 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_or, Bitflag2 const&, Enum2 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_or, Bitflag2 const&, int>::value, "");
static_assert(!hamon::is_detected<invoke_bit_or, Bitflag3 const&, Bitflag1 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_or, Bitflag3 const&, Bitflag2 const&>::value, "");
static_assert( hamon::is_detected<invoke_bit_or, Bitflag3 const&, Bitflag3 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_or, Bitflag3 const&, Enum3 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_or, Bitflag3 const&, int>::value, "");

template <typename T, typename U>
using invoke_bit_or_assign = decltype(hamon::declval<T>() |= hamon::declval<U>());

static_assert( hamon::is_detected<invoke_bit_or_assign, Bitflag1&, Bitflag1 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_or_assign, Bitflag1&, Bitflag2 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_or_assign, Bitflag1&, Bitflag3 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_or_assign, Bitflag1&, Enum1 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_or_assign, Bitflag1&, int>::value, "");
static_assert(!hamon::is_detected<invoke_bit_or_assign, Bitflag2&, Bitflag1 const&>::value, "");
static_assert( hamon::is_detected<invoke_bit_or_assign, Bitflag2&, Bitflag2 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_or_assign, Bitflag2&, Bitflag3 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_or_assign, Bitflag2&, Enum2 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_or_assign, Bitflag2&, int>::value, "");
static_assert(!hamon::is_detected<invoke_bit_or_assign, Bitflag3&, Bitflag1 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_or_assign, Bitflag3&, Bitflag2 const&>::value, "");
static_assert( hamon::is_detected<invoke_bit_or_assign, Bitflag3&, Bitflag3 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_or_assign, Bitflag3&, Enum3 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_or_assign, Bitflag3&, int>::value, "");

static_assert(!hamon::is_detected<invoke_bit_or_assign, Bitflag1 const&, Bitflag1 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_or_assign, Bitflag2 const&, Bitflag2 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_or_assign, Bitflag3 const&, Bitflag3 const&>::value, "");

inline HAMON_CXX14_CONSTEXPR bool BitOrAssignTest()
{
	{
		Bitflag1 b;

		b |= Bitflag1(kOption1);
		VERIFY(b.to_ulong() == 1u);

		b |= Bitflag1(kOption1);
		VERIFY(b.to_ulong() == 1u);

		b |= Bitflag1(kOption2);
		VERIFY(b.to_ulong() == 3u);
	}
	{
		Bitflag2 b;
		VERIFY(b.to_ulong() == 0u);

		b |= Bitflag2(Enum2::kOption4);
		VERIFY(b.to_ulong() == 1u);

		b |= Bitflag2(Enum2::kOption4);
		VERIFY(b.to_ulong() == 1u);

		b |= Bitflag2(Enum2::kOption8);
		VERIFY(b.to_ulong() == 17u);
	}

	return true;
}

GTEST_TEST(BitflagsTest, BitOrTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitOrAssignTest());

	{
		HAMON_CONSTEXPR Bitflag1 const b1 =
			Bitflag1(kOption2) |
			Bitflag1(kOption3);
		HAMON_CONSTEXPR Bitflag1 const b2 =
			Bitflag1(kOption1) |
			Bitflag1(kOption2);
		HAMON_CONSTEXPR Bitflag1 const b3 = b1 | b2;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b3.to_ulong(), 7u);
	}
	{
		HAMON_CONSTEXPR Bitflag2 const b1 =
			Bitflag2(Enum2::kOption4) |
			Bitflag2(Enum2::kOption6) |
			Bitflag2(Enum2::kOption8);
		HAMON_CONSTEXPR Bitflag2 const b2 =
			Bitflag2(Enum2::kOption4) |
			Bitflag2(Enum2::kOption5) |
			Bitflag2(Enum2::kOption7) |
			Bitflag2(Enum2::kOption8);
		HAMON_CONSTEXPR Bitflag2 const b3 = b1 | b2;
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b3.to_ulong(), 31u);
	}
}

#undef VERIFY

}	// namespace bit_or_test

}	// namespace hamon_bitflags_test
