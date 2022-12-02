/**
 *	@file	unit_test_bitflags_ctor_enum.cpp
 *
 *	@brief	enumからのコンストラクタのテスト
 */

#include <hamon/bitflags.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "bitflags_test.hpp"

namespace hamon_bitflags_test
{

GTEST_TEST(BitflagsTest, CtorEnumTest)
{
	HAMON_CONSTEXPR Bitflag1 const b1_1{kOption1};
	HAMON_CONSTEXPR Bitflag1 const b1_2{kOption2};
	HAMON_CONSTEXPR Bitflag1 const b1_3{kOption3};
	HAMON_CONSTEXPR Bitflag2 const b2_1{Enum2::kOption4};
	HAMON_CONSTEXPR Bitflag2 const b2_2{Enum2::kOption5};
	HAMON_CONSTEXPR Bitflag2 const b2_3{Enum2::kOption6};
	HAMON_CONSTEXPR Bitflag2 const b2_4{Enum2::kOption7};
	HAMON_CONSTEXPR Bitflag2 const b2_5{Enum2::kOption8};
	HAMON_CONSTEXPR Bitflag3 const b3_1{Enum3::kOption7};
	HAMON_CONSTEXPR Bitflag3 const b3_2{Enum3::kOption8};
	HAMON_CONSTEXPR Bitflag3 const b3_3{Enum3::kOption9};

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b1_1.to_ulong(),  1u);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b1_2.to_ulong(),  2u);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b1_3.to_ulong(),  4u);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b2_1.to_ulong(),  1u);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b2_2.to_ulong(),  2u);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b2_3.to_ulong(),  4u);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b2_4.to_ulong(),  8u);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b2_5.to_ulong(), 16u);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b3_1.to_ulong(),  2u);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b3_2.to_ulong(), 16u);
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ(b3_3.to_ulong(), 32u);

HAMON_WARNING_PUSH();
HAMON_WARNING_DISABLE_GCC("-Wconversion");

	EXPECT_THROW   (Bitflag1 b{(Enum1)-1}; (void)b, std::out_of_range);
	EXPECT_NO_THROW(Bitflag1 b{(Enum1) 0}; (void)b);
	EXPECT_NO_THROW(Bitflag1 b{(Enum1)31}; (void)b);
	EXPECT_THROW   (Bitflag1 b{(Enum1)32}; (void)b, std::out_of_range);

	EXPECT_THROW   (Bitflag2 b{(Enum2)-1}; (void)b, std::out_of_range);
	EXPECT_NO_THROW(Bitflag2 b{(Enum2) 0}; (void)b);
	EXPECT_NO_THROW(Bitflag2 b{(Enum2) 4}; (void)b);
	EXPECT_THROW   (Bitflag2 b{(Enum2) 5}; (void)b, std::out_of_range);

	EXPECT_THROW   (Bitflag3 b{(Enum3)-1}; (void)b, std::out_of_range);
	EXPECT_NO_THROW(Bitflag3 b{(Enum3) 0}; (void)b);
	EXPECT_NO_THROW(Bitflag3 b{(Enum3)15}; (void)b);
	EXPECT_THROW   (Bitflag3 b{(Enum3)16}; (void)b, std::out_of_range);

HAMON_WARNING_POP();
}

}	// namespace hamon_bitflags_test
