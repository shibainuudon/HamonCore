/**
 *	@file	unit_test_bitflags_flip.cpp
 *
 *	@brief	flip関数のテスト
 */

#include <hamon/bitflags.hpp>
#include <hamon/type_traits/is_detected.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "bitflags_test.hpp"

namespace hamon_bitflags_test
{

namespace flip_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename... U>
using invoke_flip = decltype(hamon::declval<T>().flip(hamon::declval<U>()...));

static_assert( hamon::is_detected<invoke_flip, Bitflag1&, Enum1>::value, "");
static_assert(!hamon::is_detected<invoke_flip, Bitflag1&, Enum2>::value, "");
static_assert(!hamon::is_detected<invoke_flip, Bitflag1&, Enum3>::value, "");
static_assert(!hamon::is_detected<invoke_flip, Bitflag1&, int>::value, "");
static_assert(!hamon::is_detected<invoke_flip, Bitflag2&, Enum1>::value, "");
static_assert( hamon::is_detected<invoke_flip, Bitflag2&, Enum2>::value, "");
static_assert(!hamon::is_detected<invoke_flip, Bitflag2&, Enum3>::value, "");
static_assert(!hamon::is_detected<invoke_flip, Bitflag2&, int>::value, "");
static_assert(!hamon::is_detected<invoke_flip, Bitflag3&, Enum1>::value, "");
static_assert(!hamon::is_detected<invoke_flip, Bitflag3&, Enum2>::value, "");
static_assert( hamon::is_detected<invoke_flip, Bitflag3&, Enum3>::value, "");
static_assert(!hamon::is_detected<invoke_flip, Bitflag3&, int>::value, "");

static_assert(!hamon::is_detected<invoke_flip, Bitflag1 const&, Enum1>::value, "");
static_assert(!hamon::is_detected<invoke_flip, Bitflag1 const&, Enum2>::value, "");
static_assert(!hamon::is_detected<invoke_flip, Bitflag1 const&, Enum3>::value, "");
static_assert(!hamon::is_detected<invoke_flip, Bitflag1 const&, int>::value, "");
static_assert(!hamon::is_detected<invoke_flip, Bitflag2 const&, Enum1>::value, "");
static_assert(!hamon::is_detected<invoke_flip, Bitflag2 const&, Enum2>::value, "");
static_assert(!hamon::is_detected<invoke_flip, Bitflag2 const&, Enum3>::value, "");
static_assert(!hamon::is_detected<invoke_flip, Bitflag2 const&, int>::value, "");
static_assert(!hamon::is_detected<invoke_flip, Bitflag3 const&, Enum1>::value, "");
static_assert(!hamon::is_detected<invoke_flip, Bitflag3 const&, Enum2>::value, "");
static_assert(!hamon::is_detected<invoke_flip, Bitflag3 const&, Enum3>::value, "");
static_assert(!hamon::is_detected<invoke_flip, Bitflag3 const&, int>::value, "");

// flip() はDenseがtrueのときのみ定義される
static_assert(!hamon::is_detected<invoke_flip, Bitflag1&>::value, "");
static_assert( hamon::is_detected<invoke_flip, Bitflag2&>::value, "");
static_assert(!hamon::is_detected<invoke_flip, Bitflag3&>::value, "");
 
static_assert(!hamon::is_detected<invoke_flip, Bitflag1 const&>::value, "");
static_assert(!hamon::is_detected<invoke_flip, Bitflag2 const&>::value, "");
static_assert(!hamon::is_detected<invoke_flip, Bitflag3 const&>::value, "");

inline HAMON_CXX14_CONSTEXPR bool FlipTest()
{
	{
		Bitflag1 b =
			Bitflag1(kOption1) |
			Bitflag1(kOption2) |
			Bitflag1(kOption3);

		b.flip(kOption1);
		VERIFY(b == (Bitflag1(kOption2) | Bitflag1(kOption3)));

		b.flip(kOption1);
		VERIFY(b == (Bitflag1(kOption1) | Bitflag1(kOption2) | Bitflag1(kOption3)));

		b.flip(kOption2);
		VERIFY(b == (Bitflag1(kOption1) | Bitflag1(kOption3)));

		b.flip(kOption2);
		VERIFY(b == (Bitflag1(kOption1) | Bitflag1(kOption2) | Bitflag1(kOption3)));
	}
	{
		Bitflag2 b =
			Bitflag2(Enum2::kOption4) |
			Bitflag2(Enum2::kOption5) |
			Bitflag2(Enum2::kOption6) |
			Bitflag2(Enum2::kOption7) |
			Bitflag2(Enum2::kOption8);

		b.flip(Enum2::kOption4);
		VERIFY(b == (
			Bitflag2(Enum2::kOption5) |
			Bitflag2(Enum2::kOption6) |
			Bitflag2(Enum2::kOption7) |
			Bitflag2(Enum2::kOption8)));

		b.flip(Enum2::kOption4);
		VERIFY(b == (
			Bitflag2(Enum2::kOption4) |
			Bitflag2(Enum2::kOption5) |
			Bitflag2(Enum2::kOption6) |
			Bitflag2(Enum2::kOption7) |
			Bitflag2(Enum2::kOption8)));

		b.flip(Enum2::kOption5);
		VERIFY(b == (
			Bitflag2(Enum2::kOption4) |
			Bitflag2(Enum2::kOption6) |
			Bitflag2(Enum2::kOption7) |
			Bitflag2(Enum2::kOption8)));

		b.flip(Enum2::kOption6);
		VERIFY(b == (
			Bitflag2(Enum2::kOption4) |
			Bitflag2(Enum2::kOption7) |
			Bitflag2(Enum2::kOption8)));

		b.flip(Enum2::kOption6);
		VERIFY(b == (
			Bitflag2(Enum2::kOption4) |
			Bitflag2(Enum2::kOption6) |
			Bitflag2(Enum2::kOption7) |
			Bitflag2(Enum2::kOption8)));

		b.flip();
		VERIFY(b == (
			Bitflag2(Enum2::kOption5)));
	}
	{
		Bitflag3 b =
			Bitflag3(Enum3::kOption7) |
			Bitflag3(Enum3::kOption8) |
			Bitflag3(Enum3::kOption9);

		b.flip(Enum3::kOption7);
		VERIFY(b == (
			Bitflag3(Enum3::kOption8) |
			Bitflag3(Enum3::kOption9)));

		b.flip(Enum3::kOption9);
		VERIFY(b == Bitflag3(Enum3::kOption8));

		b.flip(Enum3::kOption8);
		VERIFY(b == Bitflag3{});

		b.flip(Enum3::kOption8);
		VERIFY(b == Bitflag3(Enum3::kOption8));

		b.flip(Enum3::kOption7);
		VERIFY(b == (
			Bitflag3(Enum3::kOption7) |
			Bitflag3(Enum3::kOption8)));
	}

	return true;
}

GTEST_TEST(BitflagsTest, FlipTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FlipTest());

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_GCC("-Wconversion")

#if !defined(HAMON_NO_EXCEPTIONS)
	{
		Bitflag1 b{};
		EXPECT_THROW   ((void)b.flip((Enum1)-1), std::out_of_range);
		EXPECT_NO_THROW((void)b.flip((Enum1)0));
		EXPECT_NO_THROW((void)b.flip((Enum1)31));
		EXPECT_THROW   ((void)b.flip((Enum1)32), std::out_of_range);
	}
	{
		Bitflag2 b{};
		EXPECT_THROW   ((void)b.flip((Enum2)-1), std::out_of_range);
		EXPECT_NO_THROW((void)b.flip((Enum2)0));
		EXPECT_NO_THROW((void)b.flip((Enum2)4));
		EXPECT_THROW   ((void)b.flip((Enum2)5), std::out_of_range);
	}
	{
		Bitflag3 b{};
		EXPECT_THROW   ((void)b.flip((Enum3)-1), std::out_of_range);
		EXPECT_NO_THROW((void)b.flip((Enum3)0));
		EXPECT_NO_THROW((void)b.flip((Enum3)15));
		EXPECT_THROW   ((void)b.flip((Enum3)16), std::out_of_range);
	}
#endif

HAMON_WARNING_POP()
}

#undef VERIFY

}	// namespace flip_test

}	// namespace hamon_bitflags_test
