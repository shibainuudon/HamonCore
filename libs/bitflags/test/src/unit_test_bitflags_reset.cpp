/**
 *	@file	unit_test_bitflags_reset.cpp
 *
 *	@brief	reset関数のテスト
 */

#include <hamon/bitflags.hpp>
#include <hamon/type_traits/is_detected.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "bitflags_test.hpp"

namespace hamon_bitflags_test
{

namespace reset_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename... U>
using invoke_reset = decltype(std::declval<T>().reset(std::declval<U>()...));

static_assert( hamon::is_detected<invoke_reset, Bitflag1&, Enum1>::value, "");
static_assert(!hamon::is_detected<invoke_reset, Bitflag1&, Enum2>::value, "");
static_assert(!hamon::is_detected<invoke_reset, Bitflag1&, Enum3>::value, "");
static_assert(!hamon::is_detected<invoke_reset, Bitflag1&, int>::value, "");
static_assert(!hamon::is_detected<invoke_reset, Bitflag2&, Enum1>::value, "");
static_assert( hamon::is_detected<invoke_reset, Bitflag2&, Enum2>::value, "");
static_assert(!hamon::is_detected<invoke_reset, Bitflag2&, Enum3>::value, "");
static_assert(!hamon::is_detected<invoke_reset, Bitflag2&, int>::value, "");
static_assert(!hamon::is_detected<invoke_reset, Bitflag3&, Enum1>::value, "");
static_assert(!hamon::is_detected<invoke_reset, Bitflag3&, Enum2>::value, "");
static_assert( hamon::is_detected<invoke_reset, Bitflag3&, Enum3>::value, "");
static_assert(!hamon::is_detected<invoke_reset, Bitflag3&, int>::value, "");

static_assert(!hamon::is_detected<invoke_reset, Bitflag1 const&, Enum1>::value, "");
static_assert(!hamon::is_detected<invoke_reset, Bitflag1 const&, Enum2>::value, "");
static_assert(!hamon::is_detected<invoke_reset, Bitflag1 const&, Enum3>::value, "");
static_assert(!hamon::is_detected<invoke_reset, Bitflag1 const&, int>::value, "");
static_assert(!hamon::is_detected<invoke_reset, Bitflag2 const&, Enum1>::value, "");
static_assert(!hamon::is_detected<invoke_reset, Bitflag2 const&, Enum2>::value, "");
static_assert(!hamon::is_detected<invoke_reset, Bitflag2 const&, Enum3>::value, "");
static_assert(!hamon::is_detected<invoke_reset, Bitflag2 const&, int>::value, "");
static_assert(!hamon::is_detected<invoke_reset, Bitflag3 const&, Enum1>::value, "");
static_assert(!hamon::is_detected<invoke_reset, Bitflag3 const&, Enum2>::value, "");
static_assert(!hamon::is_detected<invoke_reset, Bitflag3 const&, Enum3>::value, "");
static_assert(!hamon::is_detected<invoke_reset, Bitflag3 const&, int>::value, "");

// set() はDenseにかかわらず定義される
static_assert( hamon::is_detected<invoke_reset, Bitflag1&>::value, "");
static_assert( hamon::is_detected<invoke_reset, Bitflag2&>::value, "");
static_assert( hamon::is_detected<invoke_reset, Bitflag3&>::value, "");

static_assert(!hamon::is_detected<invoke_reset, Bitflag1 const&>::value, "");
static_assert(!hamon::is_detected<invoke_reset, Bitflag2 const&>::value, "");
static_assert(!hamon::is_detected<invoke_reset, Bitflag3 const&>::value, "");

inline HAMON_CXX14_CONSTEXPR bool ResetTest()
{
	{
		Bitflag1 b =
			Bitflag1(kOption1) |
			Bitflag1(kOption2) |
			Bitflag1(kOption3);

		b.reset(kOption1);
		VERIFY(b == (Bitflag1{kOption2} | Bitflag1{kOption3}));

		b.reset(kOption3);
		VERIFY(b == Bitflag1{kOption2});

		b.reset(kOption3);
		VERIFY(b == Bitflag1{kOption2});

		b.reset(kOption2);
		VERIFY(b == Bitflag1{});

		b.reset(kOption1);
		VERIFY(b == Bitflag1{});
	}
	{
		Bitflag1 b =
			Bitflag1(kOption1) |
			Bitflag1(kOption2) |
			Bitflag1(kOption3);

		b.reset();
		VERIFY(b == Bitflag1{});
	}
	{
		Bitflag2 b =
			Bitflag2(Enum2::kOption4) |
			Bitflag2(Enum2::kOption5) |
			Bitflag2(Enum2::kOption6) |
			Bitflag2(Enum2::kOption7) |
			Bitflag2(Enum2::kOption8);

		b.reset(Enum2::kOption4);
		VERIFY(b == (
			Bitflag2(Enum2::kOption5) |
			Bitflag2(Enum2::kOption6) |
			Bitflag2(Enum2::kOption7) |
			Bitflag2(Enum2::kOption8)));

		b.reset(Enum2::kOption4);
		VERIFY(b == (
			Bitflag2(Enum2::kOption5) |
			Bitflag2(Enum2::kOption6) |
			Bitflag2(Enum2::kOption7) |
			Bitflag2(Enum2::kOption8)));

		b.reset(Enum2::kOption6);
		VERIFY(b == (
			Bitflag2(Enum2::kOption5) |
			Bitflag2(Enum2::kOption7) |
			Bitflag2(Enum2::kOption8)));

		b.reset(Enum2::kOption7);
		VERIFY(b == (
			Bitflag2(Enum2::kOption5) |
			Bitflag2(Enum2::kOption8)));

		b.reset();
		VERIFY(b == Bitflag2{});
	}
	{
		Bitflag3 b =
			Bitflag3(Enum3::kOption7) |
			Bitflag3(Enum3::kOption8) |
			Bitflag3(Enum3::kOption9);

		b.reset(Enum3::kOption7);
		VERIFY(b == (
			Bitflag3(Enum3::kOption8) |
			Bitflag3(Enum3::kOption9)));

		b.reset();
		VERIFY(b == Bitflag3{});
	}

	return true;
}

GTEST_TEST(BitflagsTest, ResetTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ResetTest());

	{
		Bitflag1 b{};
		EXPECT_THROW   ((void)b.reset((Enum1)-1), std::out_of_range);
		EXPECT_NO_THROW((void)b.reset((Enum1)0));
		EXPECT_NO_THROW((void)b.reset((Enum1)31));
		EXPECT_THROW   ((void)b.reset((Enum1)32), std::out_of_range);
	}
	{
		Bitflag2 b{};
		EXPECT_THROW   ((void)b.reset((Enum2)-1), std::out_of_range);
		EXPECT_NO_THROW((void)b.reset((Enum2)0));
		EXPECT_NO_THROW((void)b.reset((Enum2)4));
		EXPECT_THROW   ((void)b.reset((Enum2)5), std::out_of_range);
	}
	{
		Bitflag3 b{};
		EXPECT_THROW   ((void)b.reset((Enum3)-1), std::out_of_range);
		EXPECT_NO_THROW((void)b.reset((Enum3)0));
		EXPECT_NO_THROW((void)b.reset((Enum3)15));
		EXPECT_THROW   ((void)b.reset((Enum3)16), std::out_of_range);
	}
}

#undef VERIFY

}	// namespace reset_test

}	// namespace hamon_bitflags_test
