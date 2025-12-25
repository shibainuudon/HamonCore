/**
 *	@file	unit_test_cstring_memset.cpp
 *
 *	@brief	memsetのテスト
 */

#include <hamon/cstring/memset.hpp>
#include <hamon/cstdint/uint32_t.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cstring_test
{

namespace memset_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool constexpr_test()
{
	{
		char a[3]{1,2,3};
		auto p = hamon::ct::memset(a, 0, sizeof(a));

		VERIFY(0 == a[0]);
		VERIFY(0 == a[1]);
		VERIFY(0 == a[2]);
		VERIFY(p == a);
	}
	{
		char a[5] = {};
		auto p = hamon::ct::memset(a, 42, sizeof(char) * 3);

		VERIFY(42 == a[0]);
		VERIFY(42 == a[1]);
		VERIFY(42 == a[2]);
		VERIFY( 0 == a[3]);
		VERIFY( 0 == a[4]);
		VERIFY( p == a);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(CStringTest, MemSetTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(constexpr_test());

	{
		hamon::uint32_t a[4];
		auto p = hamon::memset(a, 0x12, sizeof(a));

		EXPECT_EQ(0x12121212UL, a[0]);
		EXPECT_EQ(0x12121212UL, a[1]);
		EXPECT_EQ(0x12121212UL, a[2]);
		EXPECT_EQ(0x12121212UL, a[3]);
		EXPECT_EQ(p, a);
	}
	{
		float f;
		auto p = hamon::memset(&f, 0, sizeof(f));

		EXPECT_EQ(0, f);
		EXPECT_EQ(p, &f);
	}
}

}	// namespace memset_test

}	// namespace hamon_cstring_test
