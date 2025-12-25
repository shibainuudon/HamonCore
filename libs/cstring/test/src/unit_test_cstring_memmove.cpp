/**
 *	@file	unit_test_cstring_memmove.cpp
 *
 *	@brief	memmoveのテスト
 */

#include <hamon/cstring/memmove.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cstring_test
{

namespace memmove_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

inline HAMON_CXX14_CONSTEXPR bool constexpr_test()
{
	{
		int a1[] = { 0, 1, 2, 3, 4, 5, };

		auto p = hamon::ct::memmove(&a1[0], &a1[2], sizeof(int) * 3);

		VERIFY(2 == a1[0]);
		VERIFY(3 == a1[1]);
		VERIFY(4 == a1[2]);
		VERIFY(3 == a1[3]);
		VERIFY(4 == a1[4]);
		VERIFY(5 == a1[5]);

		VERIFY(p == &a1[0]);
	}
	{
		char a1[] = { 0, 1, 2, 3, 4, 5, };

		auto p = hamon::ct::memmove(&a1[2], &a1[0], sizeof(char) * 3);

		VERIFY(0 == a1[0]);
		VERIFY(1 == a1[1]);
		VERIFY(0 == a1[2]);
		VERIFY(1 == a1[3]);
		VERIFY(2 == a1[4]);
		VERIFY(5 == a1[5]);

		VERIFY(p == &a1[2]);
	}
	{
		short a1[] = { 0, 1, 2, 3, 4, 5, };

		auto p = hamon::ct::memmove(&a1[1], &a1[3], sizeof(short) * 3);

		VERIFY(0 == a1[0]);
		VERIFY(3 == a1[1]);
		VERIFY(4 == a1[2]);
		VERIFY(5 == a1[3]);
		VERIFY(4 == a1[4]);
		VERIFY(5 == a1[5]);

		VERIFY(p == &a1[1]);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(CStringTest, MemMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(constexpr_test());

	{
		float f = 1532.625f;	// 0x44bf9400
		unsigned char c[4];
		auto p = hamon::memmove(c, &f, sizeof(f));
		EXPECT_EQ(0x00, c[0]);
		EXPECT_EQ(0x94, c[1]);
		EXPECT_EQ(0xbf, c[2]);
		EXPECT_EQ(0x44, c[3]);

		EXPECT_EQ(p, c);
	}
	{
		const char a1[] = { 1,2,3 };
		char a2[3]{};

		auto p = hamon::memmove(a2, a1, sizeof(a1));

		EXPECT_EQ(1, a2[0]);
		EXPECT_EQ(2, a2[1]);
		EXPECT_EQ(3, a2[2]);

		EXPECT_EQ(p, a2);
	}
	{
		char a1[] = { 0, 1, 2, 3, 4, 5, };

		auto p = hamon::memmove(&a1[0], &a1[2], sizeof(char) * 3);

		EXPECT_EQ(2, a1[0]);
		EXPECT_EQ(3, a1[1]);
		EXPECT_EQ(4, a1[2]);
		EXPECT_EQ(3, a1[3]);
		EXPECT_EQ(4, a1[4]);
		EXPECT_EQ(5, a1[5]);

		EXPECT_EQ(p, &a1[0]);
	}
	{
		int a1[] = { 0, 1, 2, 3, 4, 5, };

		auto p = hamon::memmove(&a1[2], &a1[0], sizeof(int) * 4);

		EXPECT_EQ(0, a1[0]);
		EXPECT_EQ(1, a1[1]);
		EXPECT_EQ(0, a1[2]);
		EXPECT_EQ(1, a1[3]);
		EXPECT_EQ(2, a1[4]);
		EXPECT_EQ(3, a1[5]);

		EXPECT_EQ(p, &a1[2]);
	}
	{
		short a1[] = { 0, 1, 2, 3, 4, 5, };

		auto p = hamon::ct::memmove(&a1[1], &a1[3], sizeof(short) * 3);

		EXPECT_EQ(0, a1[0]);
		EXPECT_EQ(3, a1[1]);
		EXPECT_EQ(4, a1[2]);
		EXPECT_EQ(5, a1[3]);
		EXPECT_EQ(4, a1[4]);
		EXPECT_EQ(5, a1[5]);

		EXPECT_EQ(p, &a1[1]);
	}
}

}	// namespace memmove_test

}	// namespace hamon_cstring_test
