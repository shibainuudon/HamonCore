/**
 *	@file	unit_test_bitflags_bool.cpp
 *
 *	@brief	operator bool のテスト
 */

#include <hamon/bitflags.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "bitflags_test.hpp"

namespace hamon_bitflags_test
{

GTEST_TEST(BitflagsTest, OperatorBoolTest)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((Bitflag1{}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (Bitflag1{kOption1}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (Bitflag1{kOption2}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (Bitflag1{kOption3}));
	HAMON_CXX11_CONSTEXPR_EXPECT_TRUE( (Bitflag1{kOption1} | Bitflag1{kOption2} | Bitflag1{kOption3}));

	{
		HAMON_CONSTEXPR Bitflag2 const b =
			Bitflag2(Enum2::kOption4) |
			Bitflag2(Enum2::kOption6) |
			Bitflag2(Enum2::kOption8);

		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((b & Bitflag2(Enum2::kOption4)));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((b & Bitflag2(Enum2::kOption5)));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((b & Bitflag2(Enum2::kOption6)));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((b & Bitflag2(Enum2::kOption7)));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((b & Bitflag2(Enum2::kOption8)));
	}
	{
		HAMON_CONSTEXPR Bitflag3 const b =
			Bitflag3(Enum3::kOption8) |
			Bitflag3(Enum3::kOption9);

		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE((b & Bitflag3(Enum3::kOption7)));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((b & Bitflag3(Enum3::kOption8)));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE ((b & Bitflag3(Enum3::kOption9)));
	}
}

}	// namespace hamon_bitflags_test
