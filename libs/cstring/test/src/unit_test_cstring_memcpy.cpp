/**
 *	@file	unit_test_cstring_memcpy.cpp
 *
 *	@brief	memcpyのテスト
 */

#include <hamon/cstring/memcpy.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cstring_test
{

namespace memcpy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool constexpr_test()
{
	{
		const char a1[] = { 1,2,3 };
		char a2[3]{};

		auto p = hamon::ct::memcpy(a2, a1, sizeof(a1));

		VERIFY(1 == a2[0]);
		VERIFY(2 == a2[1]);
		VERIFY(3 == a2[2]);

		VERIFY(p == a2);
	}
	{
		const double a1[] = { 10,11,12,13,14 };
		double a2[5]{};

		auto p = hamon::ct::memcpy(a2, a1, sizeof(a1));

		VERIFY(10 == a2[0]);
		VERIFY(11 == a2[1]);
		VERIFY(12 == a2[2]);
		VERIFY(13 == a2[3]);
		VERIFY(14 == a2[4]);

		VERIFY(p == a2);
	}
	{
		const int a1[] = { 2, 1, 0, 3 };
		int a2[4]{};

		auto p = hamon::ct::memcpy(a2, a1, sizeof(a1));

		VERIFY(2 == a2[0]);
		VERIFY(1 == a2[1]);
		VERIFY(0 == a2[2]);
		VERIFY(3 == a2[3]);

		VERIFY(p == a2);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(CStringTest, MemCpyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(constexpr_test());

	{
		float f = 1532.625f;	// 0x44bf9400
		unsigned char c[4];
		auto p = hamon::memcpy(c, &f, sizeof(f));
		EXPECT_EQ(0x00, c[0]);
		EXPECT_EQ(0x94, c[1]);
		EXPECT_EQ(0xbf, c[2]);
		EXPECT_EQ(0x44, c[3]);

		EXPECT_EQ(p, c);
	}
}

}	// namespace memcpy_test

}	// namespace hamon_cstring_test
