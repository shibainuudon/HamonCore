/**
 *	@file	unit_test_cstring_memcpy.cpp
 *
 *	@brief	memcpyのテスト
 */

#include <hamon/cstring/memcpy.hpp>
#include <hamon/cstdint.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cstring_test
{

namespace memcpy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool test1()
{
	{
		const char a1[] = { 1,2,3 };
		char a2[3]{};

		auto p = hamon::memcpy(a2, a1, sizeof(a1));

		VERIFY(1 == a2[0]);
		VERIFY(2 == a2[1]);
		VERIFY(3 == a2[2]);

		VERIFY(p == a2);
	}
	{
		const double a1[] = { 10,11,12,13,14 };
		double a2[5]{};

		auto p = hamon::memcpy(a2, a1, sizeof(a1));

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

		auto p = hamon::memcpy(a2, a1, sizeof(a1));

		VERIFY(2 == a2[0]);
		VERIFY(1 == a2[1]);
		VERIFY(0 == a2[2]);
		VERIFY(3 == a2[3]);

		VERIFY(p == a2);
	}

	return true;
}

inline HAMON_CXX14_CONSTEXPR bool test2()
{
	{
		const float a1[] =
		{
			1532.625f,	// 0x44bf9400
			0.5f,		// 0x3f000000
			-0.1f,		// 0xbdcccccd
		};
		hamon::uint32_t a2[3]{};

		auto p = hamon::memcpy(a2, a1, sizeof(a1));

		VERIFY(a2[0] == 0x44bf9400);
		VERIFY(a2[1] == 0x3f000000);
		VERIFY(a2[2] == 0xbdcccccd);

		VERIFY(p == a2);
	}
	return true;
}

#undef VERIFY

GTEST_TEST(CStringTest, MemCpyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test1());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test2());

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
	{
		float f = 0.5f;			// 0x3f000000
		unsigned char c[4];
		auto p = hamon::memcpy(c, &f, sizeof(f));
		EXPECT_EQ(0x00, c[0]);
		EXPECT_EQ(0x00, c[1]);
		EXPECT_EQ(0x00, c[2]);
		EXPECT_EQ(0x3f, c[3]);

		EXPECT_EQ(p, c);
	}
	{
		float f = -0.1f;		// 0xbdcccccd
		unsigned char c[4];
		auto p = hamon::memcpy(c, &f, sizeof(f));
		EXPECT_EQ(0xcd, c[0]);
		EXPECT_EQ(0xcc, c[1]);
		EXPECT_EQ(0xcc, c[2]);
		EXPECT_EQ(0xbd, c[3]);

		EXPECT_EQ(p, c);
	}
}

}	// namespace memcpy_test

}	// namespace hamon_cstring_test
