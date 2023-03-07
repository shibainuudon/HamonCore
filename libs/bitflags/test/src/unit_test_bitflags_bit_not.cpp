/**
 *	@file	unit_test_bitflags_bit_not.cpp
 *
 *	@brief	operator~のテスト
 */

#include <hamon/bitflags.hpp>
#include <hamon/type_traits/is_detected.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "bitflags_test.hpp"

namespace hamon_bitflags_test
{

namespace bit_not_test
{

template <typename T>
using invoke_bit_not = decltype(~hamon::declval<T>());

// operator~ はDenseがtrueのときのみ定義される
static_assert(!hamon::is_detected<invoke_bit_not, Bitflag1 const&>::value, "");
static_assert( hamon::is_detected<invoke_bit_not, Bitflag2 const&>::value, "");
static_assert(!hamon::is_detected<invoke_bit_not, Bitflag3 const&>::value, "");

GTEST_TEST(BitflagsTest, BitNotTest)
{
	{
		HAMON_CONSTEXPR Bitflag2 const b{};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(
			Bitflag2{Enum2::kOption4} |
			Bitflag2{Enum2::kOption5} |
			Bitflag2{Enum2::kOption6} |
			Bitflag2{Enum2::kOption7} |
			Bitflag2{Enum2::kOption8}, ~b);
	}
	{
		HAMON_CONSTEXPR Bitflag2 const b =
			Bitflag2(Enum2::kOption4) |
			Bitflag2(Enum2::kOption5);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(
			Bitflag2{Enum2::kOption6} |
			Bitflag2{Enum2::kOption7} |
			Bitflag2{Enum2::kOption8}, ~b);
	}
	{
		HAMON_CONSTEXPR Bitflag2 const b =
			Bitflag2(Enum2::kOption4) |
			Bitflag2(Enum2::kOption6) |
			Bitflag2(Enum2::kOption8);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(
			Bitflag2{Enum2::kOption5} |
			Bitflag2{Enum2::kOption7}, ~b);
	}
	{
		HAMON_CONSTEXPR Bitflag2 const b =
			Bitflag2(Enum2::kOption4) |
			Bitflag2(Enum2::kOption5) |
			Bitflag2(Enum2::kOption6) |
			Bitflag2(Enum2::kOption7) |
			Bitflag2(Enum2::kOption8);
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(
			Bitflag2{}, ~b);
	}
}

}	// namespace bit_not_test

}	// namespace hamon_bitflags_test
