/**
 *	@file	unit_test_bitflags_all.cpp
 *
 *	@brief	all関数のテスト
 */

#include <hamon/bitflags.hpp>
#include <hamon/type_traits/is_detected.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "bitflags_test.hpp"

namespace hamon_bitflags_test
{

namespace all_test
{

template <typename T>
using invoke_all = decltype(hamon::declval<T>().all());

// all() はDenseがtrueのときのみ定義される
static_assert(!hamon::is_detected<invoke_all, Bitflag1 const&>::value, "");
static_assert( hamon::is_detected<invoke_all, Bitflag2 const&>::value, "");
static_assert(!hamon::is_detected<invoke_all, Bitflag3 const&>::value, "");

GTEST_TEST(BitflagsTest, AllTest)
{
	{
		HAMON_CONSTEXPR Bitflag2 const b{};
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.all());
	}
	{
		HAMON_CONSTEXPR Bitflag2 const b{Enum2::kOption5};
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.all());
	}
	{
		HAMON_CONSTEXPR Bitflag2 const b{Enum2::kOption8};
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.all());
	}
	{
		HAMON_CONSTEXPR Bitflag2 const b =
			Bitflag2(Enum2::kOption4) |
			Bitflag2(Enum2::kOption6) |
			Bitflag2(Enum2::kOption8);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.all());
	}
	{
		HAMON_CONSTEXPR Bitflag2 const b =
			Bitflag2(Enum2::kOption4) |
			Bitflag2(Enum2::kOption5) |
			Bitflag2(Enum2::kOption6) |
			Bitflag2(Enum2::kOption7);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.all());
	}
	{
		HAMON_CONSTEXPR Bitflag2 const b =
			Bitflag2(Enum2::kOption4) |
			Bitflag2(Enum2::kOption5) |
			Bitflag2(Enum2::kOption6) |
			Bitflag2(Enum2::kOption7) |
			Bitflag2(Enum2::kOption8);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(b.all());
	}
}

}	// namespace all_test

}	// namespace hamon_bitflags_test
