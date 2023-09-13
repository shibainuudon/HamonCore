/**
 *	@file	unit_test_bitflags_test.cpp
 *
 *	@brief	test関数のテスト
 */

#include <hamon/bitflags.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
#include <hamon/type_traits/is_detected.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "bitflags_test.hpp"

namespace hamon_bitflags_test
{

namespace test_test
{

template <typename T, typename U>
using invoke_test = decltype(hamon::declval<T>().test(hamon::declval<U>()));

static_assert( hamon::is_detected<invoke_test, Bitflag1&, Enum1>::value, "");
static_assert(!hamon::is_detected<invoke_test, Bitflag1&, Enum2>::value, "");
static_assert(!hamon::is_detected<invoke_test, Bitflag1&, Enum3>::value, "");
static_assert(!hamon::is_detected<invoke_test, Bitflag1&, int>::value, "");
static_assert(!hamon::is_detected<invoke_test, Bitflag2&, Enum1>::value, "");
static_assert( hamon::is_detected<invoke_test, Bitflag2&, Enum2>::value, "");
static_assert(!hamon::is_detected<invoke_test, Bitflag2&, Enum3>::value, "");
static_assert(!hamon::is_detected<invoke_test, Bitflag2&, int>::value, "");
static_assert(!hamon::is_detected<invoke_test, Bitflag3&, Enum1>::value, "");
static_assert(!hamon::is_detected<invoke_test, Bitflag3&, Enum2>::value, "");
static_assert( hamon::is_detected<invoke_test, Bitflag3&, Enum3>::value, "");
static_assert(!hamon::is_detected<invoke_test, Bitflag3&, int>::value, "");

static_assert( hamon::is_detected<invoke_test, Bitflag1 const&, Enum1>::value, "");
static_assert(!hamon::is_detected<invoke_test, Bitflag1 const&, Enum2>::value, "");
static_assert(!hamon::is_detected<invoke_test, Bitflag1 const&, Enum3>::value, "");
static_assert(!hamon::is_detected<invoke_test, Bitflag1 const&, int>::value, "");
static_assert(!hamon::is_detected<invoke_test, Bitflag2 const&, Enum1>::value, "");
static_assert( hamon::is_detected<invoke_test, Bitflag2 const&, Enum2>::value, "");
static_assert(!hamon::is_detected<invoke_test, Bitflag2 const&, Enum3>::value, "");
static_assert(!hamon::is_detected<invoke_test, Bitflag2 const&, int>::value, "");
static_assert(!hamon::is_detected<invoke_test, Bitflag3 const&, Enum1>::value, "");
static_assert(!hamon::is_detected<invoke_test, Bitflag3 const&, Enum2>::value, "");
static_assert( hamon::is_detected<invoke_test, Bitflag3 const&, Enum3>::value, "");
static_assert(!hamon::is_detected<invoke_test, Bitflag3 const&, int>::value, "");

GTEST_TEST(BitflagsTest, TestTest)
{
	{
		HAMON_CONSTEXPR Bitflag1 const b;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.test(kOption1));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.test(kOption2));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.test(kOption3));
	}
	{
		HAMON_CONSTEXPR Bitflag1 const b =
			Bitflag1(kOption1) |
			Bitflag1(kOption3);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(kOption1));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.test(kOption2));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(kOption3));
	}
	{
		HAMON_CONSTEXPR Bitflag2 const b =
			Bitflag2(Enum2::kOption4) |
			Bitflag2(Enum2::kOption5) |
			Bitflag2(Enum2::kOption8);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(Enum2::kOption4));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(Enum2::kOption5));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.test(Enum2::kOption6));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.test(Enum2::kOption7));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(Enum2::kOption8));
	}
	{
		HAMON_CONSTEXPR Bitflag2 const b =
			Bitflag2(Enum2::kOption4) |
			Bitflag2(Enum2::kOption5) |
			Bitflag2(Enum2::kOption6) |
			Bitflag2(Enum2::kOption7) |
			Bitflag2(Enum2::kOption8);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(b.test(Enum2::kOption4));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(b.test(Enum2::kOption5));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(b.test(Enum2::kOption6));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(b.test(Enum2::kOption7));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(b.test(Enum2::kOption8));
	}
	{
		HAMON_CONSTEXPR Bitflag3 const b;
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.test(Enum3::kOption7));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.test(Enum3::kOption8));
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.test(Enum3::kOption9));
	}
	{
		HAMON_CONSTEXPR Bitflag3 const b =
			Bitflag3(Enum3::kOption8) |
			Bitflag3(Enum3::kOption9);
		HAMON_CXX11_CONSTEXPR_EXPECT_FALSE(b.test(Enum3::kOption7));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(Enum3::kOption8));
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE (b.test(Enum3::kOption9));
	}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_GCC("-Wconversion")

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		Bitflag1 b{};
		EXPECT_THROW   ((void)b.test((Enum1)-1), hamon::out_of_range);
		EXPECT_NO_THROW((void)b.test((Enum1)0));
		EXPECT_NO_THROW((void)b.test((Enum1)31));
		EXPECT_THROW   ((void)b.test((Enum1)32), hamon::out_of_range);
	}
	{
		Bitflag2 b{};
		EXPECT_THROW   ((void)b.test((Enum2)-1), hamon::out_of_range);
		EXPECT_NO_THROW((void)b.test((Enum2)0));
		EXPECT_NO_THROW((void)b.test((Enum2)4));
		EXPECT_THROW   ((void)b.test((Enum2)5), hamon::out_of_range);
	}
	{
		Bitflag3 b{};
		EXPECT_THROW   ((void)b.test((Enum3)-1), hamon::out_of_range);
		EXPECT_NO_THROW((void)b.test((Enum3)0));
		EXPECT_NO_THROW((void)b.test((Enum3)15));
		EXPECT_THROW   ((void)b.test((Enum3)16), hamon::out_of_range);
	}
#endif

HAMON_WARNING_POP()
}

}	// namespace test_test

}	// namespace hamon_bitflags_test
