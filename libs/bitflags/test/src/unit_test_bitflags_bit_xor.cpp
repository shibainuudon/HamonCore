/**
 *	@file	unit_test_bitflags_bit_xor.cpp
 *
 *	@brief	operator^のテスト
 */

#include <hamon/bitflags.hpp>
#include <hamon/type_traits/is_detected.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "bitflags_test.hpp"

namespace hamon_bitflags_test
{

namespace bit_xor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename U>
using invoke_bit_xor = decltype(hamon::declval<T>() ^ hamon::declval<U>());

static_assert( hamon::is_detected<invoke_bit_xor, Bitflag1 const&, Bitflag1 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_xor, Bitflag1 const&, Bitflag2 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_xor, Bitflag1 const&, Bitflag3 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_xor, Bitflag1 const&, Enum1 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_xor, Bitflag1 const&, int>::value, "");
static_assert(!hamon::is_detected<invoke_bit_xor, Bitflag2 const&, Bitflag1 const&>::value, "");
static_assert( hamon::is_detected<invoke_bit_xor, Bitflag2 const&, Bitflag2 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_xor, Bitflag2 const&, Bitflag3 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_xor, Bitflag2 const&, Enum2 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_xor, Bitflag2 const&, int>::value, "");
static_assert(!hamon::is_detected<invoke_bit_xor, Bitflag3 const&, Bitflag1 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_xor, Bitflag3 const&, Bitflag2 const&>::value, "");
static_assert( hamon::is_detected<invoke_bit_xor, Bitflag3 const&, Bitflag3 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_xor, Bitflag3 const&, Enum3 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_xor, Bitflag3 const&, int>::value, "");

template <typename T, typename U>
using invoke_bit_xor_assign = decltype(hamon::declval<T>() ^= hamon::declval<U>());

static_assert( hamon::is_detected<invoke_bit_xor_assign, Bitflag1&, Bitflag1 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_xor_assign, Bitflag1&, Bitflag2 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_xor_assign, Bitflag1&, Bitflag3 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_xor_assign, Bitflag1&, Enum1 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_xor_assign, Bitflag1&, int>::value, "");
static_assert(!hamon::is_detected<invoke_bit_xor_assign, Bitflag2&, Bitflag1 const&>::value, "");
static_assert( hamon::is_detected<invoke_bit_xor_assign, Bitflag2&, Bitflag2 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_xor_assign, Bitflag2&, Bitflag3 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_xor_assign, Bitflag2&, Enum2 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_xor_assign, Bitflag2&, int>::value, "");
static_assert(!hamon::is_detected<invoke_bit_xor_assign, Bitflag3&, Bitflag1 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_xor_assign, Bitflag3&, Bitflag2 const&>::value, "");
static_assert( hamon::is_detected<invoke_bit_xor_assign, Bitflag3&, Bitflag3 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_xor_assign, Bitflag3&, Enum3 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_xor_assign, Bitflag3&, int>::value, "");

static_assert(!hamon::is_detected<invoke_bit_xor_assign, Bitflag1 const&, Bitflag1 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_xor_assign, Bitflag2 const&, Bitflag2 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_xor_assign, Bitflag3 const&, Bitflag3 const&>::value, "");

inline HAMON_CXX14_CONSTEXPR bool BitXorAssignTest()
{
	{
		Bitflag1 b;
		VERIFY(b == Bitflag1{});

		b ^= Bitflag1(kOption1);
		VERIFY(b == Bitflag1{kOption1});

		b ^= Bitflag1(kOption1);
		VERIFY(b == Bitflag1{});

		b ^= Bitflag1(kOption2);
		VERIFY(b == Bitflag1{kOption2});
	}
	{
		Bitflag2 b;
		VERIFY(b == Bitflag2{});

		b ^= Bitflag2(Enum2::kOption5);
		VERIFY(b == Bitflag2{Enum2::kOption5});

		b ^= Bitflag2(Enum2::kOption5);
		VERIFY(b == Bitflag2{});

		b ^= Bitflag2(Enum2::kOption8);
		VERIFY(b == Bitflag2{Enum2::kOption8});

		b ^= Bitflag2(Enum2::kOption7);
		VERIFY(b == (Bitflag2{Enum2::kOption7} | Bitflag2{Enum2::kOption8}));
	}
	{
		Bitflag3 b =
			Bitflag3(Enum3::kOption7) |
			Bitflag3(Enum3::kOption8) |
			Bitflag3(Enum3::kOption9);

		b ^=Bitflag3(Enum3::kOption7) |
			Bitflag3(Enum3::kOption8);
		VERIFY(b == Bitflag3{Enum3::kOption9});

		b ^=Bitflag3(Enum3::kOption7) |
			Bitflag3(Enum3::kOption9);
		VERIFY(b == Bitflag3{Enum3::kOption7});

		b ^=Bitflag3(Enum3::kOption7) |
			Bitflag3(Enum3::kOption8) |
			Bitflag3(Enum3::kOption9);
		VERIFY(b == (Bitflag3{Enum3::kOption8} | Bitflag3{Enum3::kOption9}));
	}

	return true;
}

GTEST_TEST(BitflagsTest, BitXorTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(BitXorAssignTest());

	{
		HAMON_CONSTEXPR Bitflag1 const b1 =
			Bitflag1(kOption1) |
			Bitflag1(kOption3);
		HAMON_CONSTEXPR Bitflag1 const b2 =
			Bitflag1(kOption3) |
			Bitflag1(kOption2);
		HAMON_CONSTEXPR Bitflag1 const b3 =
			Bitflag1(kOption1) |
			Bitflag1(kOption2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b3, b1 ^ b2);
	}
	{
		HAMON_CONSTEXPR Bitflag1 const b1 =
			Bitflag1(kOption2) |
			Bitflag1(kOption3);
		HAMON_CONSTEXPR Bitflag1 const b2 =
			Bitflag1(kOption1) |
			Bitflag1(kOption2);
		HAMON_CONSTEXPR Bitflag1 const b3 =
			Bitflag1(kOption1) |
			Bitflag1(kOption3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b3, b1 ^ b2);
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
		HAMON_CONSTEXPR Bitflag2 const b3 =
			Bitflag2(Enum2::kOption5) |
			Bitflag2(Enum2::kOption6) |
			Bitflag2(Enum2::kOption7);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b3, b1 ^ b2);
	}
	{
		HAMON_CONSTEXPR Bitflag3 const b1 =
			Bitflag3(Enum3::kOption7) |
			Bitflag3(Enum3::kOption8) |
			Bitflag3(Enum3::kOption9);
		HAMON_CONSTEXPR Bitflag3 const b2 =
			Bitflag3(Enum3::kOption7) |
			Bitflag3(Enum3::kOption8) |
			Bitflag3(Enum3::kOption9);
		HAMON_CONSTEXPR Bitflag3 const b3{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b3, b1 ^ b2);
	}
	{
		HAMON_CONSTEXPR Bitflag3 const b1 =
			Bitflag3(Enum3::kOption7) |
			Bitflag3(Enum3::kOption8) |
			Bitflag3(Enum3::kOption9);
		HAMON_CONSTEXPR Bitflag3 const b2 =
			Bitflag3(Enum3::kOption8);
		HAMON_CONSTEXPR Bitflag3 const b3 =
			Bitflag3(Enum3::kOption7) |
			Bitflag3(Enum3::kOption9);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b3, b1 ^ b2);
	}
}

#undef VERIFY

}	// namespace bit_xor_test

}	// namespace hamon_bitflags_test
