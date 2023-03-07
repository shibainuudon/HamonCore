/**
 *	@file	unit_test_bitflags_shift_left.cpp
 *
 *	@brief	operator<<のテスト
 */

#include <hamon/bitflags.hpp>
#include <hamon/type_traits/is_detected.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "bitflags_test.hpp"

namespace hamon_bitflags_test
{

namespace shift_left_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename U>
using invoke_shift_left = decltype(hamon::declval<T>() << hamon::declval<U>());

// operator<< はDenseがtrueのときのみ定義される
static_assert(!hamon::is_detected<invoke_shift_left, Bitflag1 const&, int>::value, "");
static_assert(!hamon::is_detected<invoke_shift_left, Bitflag1 const&, std::size_t>::value, "");
static_assert( hamon::is_detected<invoke_shift_left, Bitflag2 const&, int>::value, "");
static_assert( hamon::is_detected<invoke_shift_left, Bitflag2 const&, std::size_t>::value, "");
static_assert(!hamon::is_detected<invoke_shift_left, Bitflag3 const&, int>::value, "");
static_assert(!hamon::is_detected<invoke_shift_left, Bitflag3 const&, std::size_t>::value, "");

static_assert(!hamon::is_detected<invoke_shift_left, Bitflag2 const&, Bitflag2 const&>::value, "");
static_assert(!hamon::is_detected<invoke_shift_left, Bitflag2 const&, Enum2 const&>::value, "");

template <typename T, typename U>
using invoke_shift_left_assign = decltype(hamon::declval<T>() <<= hamon::declval<U>());

static_assert(!hamon::is_detected<invoke_shift_left_assign, Bitflag1&, int>::value, "");
static_assert(!hamon::is_detected<invoke_shift_left_assign, Bitflag1&, std::size_t>::value, "");
static_assert( hamon::is_detected<invoke_shift_left_assign, Bitflag2&, int>::value, "");
static_assert( hamon::is_detected<invoke_shift_left_assign, Bitflag2&, std::size_t>::value, "");
static_assert(!hamon::is_detected<invoke_shift_left_assign, Bitflag3&, int>::value, "");
static_assert(!hamon::is_detected<invoke_shift_left_assign, Bitflag3&, std::size_t>::value, "");

static_assert(!hamon::is_detected<invoke_shift_left_assign, Bitflag1 const&, int>::value, "");
static_assert(!hamon::is_detected<invoke_shift_left_assign, Bitflag1 const&, std::size_t>::value, "");
static_assert(!hamon::is_detected<invoke_shift_left_assign, Bitflag2 const&, int>::value, "");
static_assert(!hamon::is_detected<invoke_shift_left_assign, Bitflag2 const&, std::size_t>::value, "");
static_assert(!hamon::is_detected<invoke_shift_left_assign, Bitflag3 const&, int>::value, "");
static_assert(!hamon::is_detected<invoke_shift_left_assign, Bitflag3 const&, std::size_t>::value, "");

inline HAMON_CXX14_CONSTEXPR bool ShiftLeftAssignTest()
{
	{
		Bitflag2 b(Enum2::kOption4);

		b <<= 1;
		VERIFY(b == Bitflag2{Enum2::kOption5});

		b <<= 2;
		VERIFY(b == Bitflag2{Enum2::kOption7});

		b <<= 2;
		VERIFY(b == Bitflag2{});
	}
	{
		Bitflag2 b =
			Bitflag2(Enum2::kOption4) |
			Bitflag2(Enum2::kOption5) |
			Bitflag2(Enum2::kOption6) |
			Bitflag2(Enum2::kOption7) |
			Bitflag2(Enum2::kOption8);

		b <<= 1;
		VERIFY(b == (
			Bitflag2(Enum2::kOption5) |
			Bitflag2(Enum2::kOption6) |
			Bitflag2(Enum2::kOption7) |
			Bitflag2(Enum2::kOption8)));

		b <<= 3;
		VERIFY(b == (
			Bitflag2(Enum2::kOption8)));
	}
	return true;
}

GTEST_TEST(BitflagsTest, ShiftLeftTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ShiftLeftAssignTest());

	{
		HAMON_CONSTEXPR Bitflag2 const b{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(Bitflag2{}, b << 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(Bitflag2{}, b << 1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(Bitflag2{}, b << 2);
	}
	{
		HAMON_CONSTEXPR Bitflag2 const b{Enum2::kOption4};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(Bitflag2{Enum2::kOption4}, b << 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(Bitflag2{Enum2::kOption5}, b << 1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(Bitflag2{Enum2::kOption6}, b << 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(Bitflag2{Enum2::kOption7}, b << 3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(Bitflag2{Enum2::kOption8}, b << 4);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(Bitflag2{},                b << 5);
	}
	{
		HAMON_CONSTEXPR Bitflag2 const b =
			Bitflag2(Enum2::kOption5) |
			Bitflag2(Enum2::kOption7);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(
			Bitflag2{Enum2::kOption5} | Bitflag2{Enum2::kOption7}, b << 0);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(
			Bitflag2{Enum2::kOption6} | Bitflag2{Enum2::kOption8}, b << 1);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(
			Bitflag2{Enum2::kOption7}, b << 2);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(
			Bitflag2{Enum2::kOption8}, b << 3);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(
			Bitflag2{}, b << 4);
	}
}

#undef VERIFY

}	// namespace shift_left_test

}	// namespace hamon_bitflags_test
