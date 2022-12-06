/**
 *	@file	unit_test_bitflags_set.cpp
 *
 *	@brief	set関数のテスト
 */

#include <hamon/bitflags.hpp>
#include <hamon/type_traits/is_detected.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "bitflags_test.hpp"

namespace hamon_bitflags_test
{

namespace set_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T, typename... U>
using invoke_set = decltype(std::declval<T>().set(std::declval<U>()...));

static_assert( hamon::is_detected<invoke_set, Bitflag1&, Enum1>::value, "");
static_assert(!hamon::is_detected<invoke_set, Bitflag1&, Enum2>::value, "");
static_assert(!hamon::is_detected<invoke_set, Bitflag1&, Enum3>::value, "");
static_assert(!hamon::is_detected<invoke_set, Bitflag1&, int>::value, "");
static_assert(!hamon::is_detected<invoke_set, Bitflag2&, Enum1>::value, "");
static_assert( hamon::is_detected<invoke_set, Bitflag2&, Enum2>::value, "");
static_assert(!hamon::is_detected<invoke_set, Bitflag2&, Enum3>::value, "");
static_assert(!hamon::is_detected<invoke_set, Bitflag2&, int>::value, "");
static_assert(!hamon::is_detected<invoke_set, Bitflag3&, Enum1>::value, "");
static_assert(!hamon::is_detected<invoke_set, Bitflag3&, Enum2>::value, "");
static_assert( hamon::is_detected<invoke_set, Bitflag3&, Enum3>::value, "");
static_assert(!hamon::is_detected<invoke_set, Bitflag3&, int>::value, "");

static_assert(!hamon::is_detected<invoke_set, Bitflag1 const&, Enum1>::value, "");
static_assert(!hamon::is_detected<invoke_set, Bitflag1 const&, Enum2>::value, "");
static_assert(!hamon::is_detected<invoke_set, Bitflag1 const&, Enum3>::value, "");
static_assert(!hamon::is_detected<invoke_set, Bitflag1 const&, int>::value, "");
static_assert(!hamon::is_detected<invoke_set, Bitflag2 const&, Enum1>::value, "");
static_assert(!hamon::is_detected<invoke_set, Bitflag2 const&, Enum2>::value, "");
static_assert(!hamon::is_detected<invoke_set, Bitflag2 const&, Enum3>::value, "");
static_assert(!hamon::is_detected<invoke_set, Bitflag2 const&, int>::value, "");
static_assert(!hamon::is_detected<invoke_set, Bitflag3 const&, Enum1>::value, "");
static_assert(!hamon::is_detected<invoke_set, Bitflag3 const&, Enum2>::value, "");
static_assert(!hamon::is_detected<invoke_set, Bitflag3 const&, Enum3>::value, "");
static_assert(!hamon::is_detected<invoke_set, Bitflag3 const&, int>::value, "");

// set() はDenseがtrueのときのみ定義される
static_assert(!hamon::is_detected<invoke_set, Bitflag1&>::value, "");
static_assert( hamon::is_detected<invoke_set, Bitflag2&>::value, "");
static_assert(!hamon::is_detected<invoke_set, Bitflag3&>::value, "");

static_assert(!hamon::is_detected<invoke_set, Bitflag1 const&>::value, "");
static_assert(!hamon::is_detected<invoke_set, Bitflag2 const&>::value, "");
static_assert(!hamon::is_detected<invoke_set, Bitflag3 const&>::value, "");

inline HAMON_CXX14_CONSTEXPR bool SetTest()
{
	{
		Bitflag1 b;
		VERIFY(b.to_ulong() == 0u);

		b.set(kOption1);
		VERIFY(b.to_ulong() == 1u);

		b.set(kOption1);
		VERIFY(b.to_ulong() == 1u);

		b.set(kOption3);
		VERIFY(b.to_ulong() == 5u);

		b.set(kOption2);
		VERIFY(b.to_ulong() == 7u);
	}
	{
		Bitflag2 b;
		VERIFY(b.to_ulong() == 0u);

		b.set(Enum2::kOption8);
		VERIFY(b.to_ulong() == 16u);

		b.set(Enum2::kOption6);
		VERIFY(b.to_ulong() == 20u);

		b.set(Enum2::kOption6);
		VERIFY(b.to_ulong() == 20u);

		b.set(Enum2::kOption4);
		VERIFY(b.to_ulong() == 21u);

		b.set();
		VERIFY(b.to_ulong() == 31u);
	}
	{
		Bitflag3 b;
		VERIFY(b.to_ulong() == 0u);

		b.set(Enum3::kOption7).set(Enum3::kOption8).set(Enum3::kOption9);
		VERIFY(b.to_ulong() == 50u);

		b.set(Enum3::kOption7);
		VERIFY(b.to_ulong() == 50u);
	}

	return true;
}

GTEST_TEST(BitflagsTest, SetTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(SetTest());

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_GCC("-Wconversion")

	{
		Bitflag1 b{};
		EXPECT_THROW   ((void)b.set((Enum1)-1), std::out_of_range);
		EXPECT_NO_THROW((void)b.set((Enum1)0));
		EXPECT_NO_THROW((void)b.set((Enum1)31));
		EXPECT_THROW   ((void)b.set((Enum1)32), std::out_of_range);
	}
	{
		Bitflag2 b{};
		EXPECT_THROW   ((void)b.set((Enum2)-1), std::out_of_range);
		EXPECT_NO_THROW((void)b.set((Enum2)0));
		EXPECT_NO_THROW((void)b.set((Enum2)4));
		EXPECT_THROW   ((void)b.set((Enum2)5), std::out_of_range);
	}
	{
		Bitflag3 b{};
		EXPECT_THROW   ((void)b.set((Enum3)-1), std::out_of_range);
		EXPECT_NO_THROW((void)b.set((Enum3)0));
		EXPECT_NO_THROW((void)b.set((Enum3)15));
		EXPECT_THROW   ((void)b.set((Enum3)16), std::out_of_range);
	}

HAMON_WARNING_POP()
}

#undef VERIFY

}	// namespace set_test

}	// namespace hamon_bitflags_test
