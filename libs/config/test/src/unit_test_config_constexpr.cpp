/**
 *	@file	unit_test_config_constexpr.cpp
 *
 *	@brief
 */

#include <hamon/config.hpp>
#include <gtest/gtest.h>

namespace hamon_config_constexpr_test
{

HAMON_CONSTEXPR int func1(int x)
{
	return x * 2;
}

HAMON_CXX14_CONSTEXPR int func2(int x)
{
	x = x * 3;
	return x;
}

HAMON_CXX17_CONSTEXPR int func3(int x)
{
	return x * 4;
}

HAMON_CXX20_CONSTEXPR int func4(int x)
{
	return x * 5;
}

HAMON_CXX23_CONSTEXPR int func5(int x)
{
	return x + 6;
}

GTEST_TEST(ConfigTest, ConstexprTest)
{
	HAMON_CONSTEXPR					int a = 1;
	HAMON_CONSTEXPR_OR_CONST		int b = 2;
	HAMON_STATIC_CONSTEXPR			int c = 3;
	HAMON_CONSTEXPR_OR_CONST		int d = func1(4);
	HAMON_CXX14_CONSTEXPR			int e = 5;
	HAMON_CXX14_CONSTEXPR_OR_CONST	int f = func2(6);
	HAMON_CXX14_STATIC_CONSTEXPR	int g = func2(7);
	HAMON_CXX17_CONSTEXPR_OR_CONST	int h = func3(8);
	HAMON_CXX17_STATIC_CONSTEXPR	int i = func3(9);
	HAMON_CXX20_CONSTEXPR_OR_CONST	int j = func4(10);
	HAMON_CXX20_STATIC_CONSTEXPR	int k = func4(11);
	HAMON_CXX23_CONSTEXPR_OR_CONST	int l = func5(12);
	HAMON_CXX23_STATIC_CONSTEXPR	int m = func5(13);

	EXPECT_EQ(1, a);
	EXPECT_EQ(2, b);
	EXPECT_EQ(3, c);
	EXPECT_EQ(8, d);
	EXPECT_EQ(5, e);
	EXPECT_EQ(18, f);
	EXPECT_EQ(21, g);
	EXPECT_EQ(32, h);
	EXPECT_EQ(36, i);
	EXPECT_EQ(50, j);
	EXPECT_EQ(55, k);
	EXPECT_EQ(18, l);
	EXPECT_EQ(19, m);

	static_assert(b == 2, "");
	static_assert(c == 3, "");

	char arr2[b];
	char arr3[c];
	(void)arr2;
	(void)arr3;

	static_assert(sizeof(arr2) == 2, "");
	static_assert(sizeof(arr3) == 3, "");

#if defined(HAMON_HAS_CXX11_CONSTEXPR)
	static_assert(a == 1, "");
	static_assert(d == 8, "");

	char arr1[a];
	char arr4[d];
	(void)arr1;
	(void)arr4;

	static_assert(sizeof(arr1) == 1, "");
	static_assert(sizeof(arr4) == 8, "");
#endif

#if defined(HAMON_HAS_CXX14_CONSTEXPR)
	static_assert(e == 5, "");
	static_assert(f == 18, "");
	static_assert(g == 21, "");

	char arr5[e];
	char arr6[f];
	char arr7[g];
	(void)arr5;
	(void)arr6;
	(void)arr7;

	static_assert(sizeof(arr5) == 5, "");
	static_assert(sizeof(arr6) == 18, "");
	static_assert(sizeof(arr7) == 21, "");
#endif

#if defined(HAMON_HAS_CXX17_CONSTEXPR)
	static_assert(h == 32, "");
	static_assert(i == 36, "");
#endif

#if defined(HAMON_HAS_CXX20_CONSTEXPR)
	static_assert(j == 50, "");
	static_assert(k == 55, "");
#endif

#if defined(HAMON_HAS_CXX23_CONSTEXPR)
	static_assert(l == 18, "");
	static_assert(m == 19, "");
#endif
}

}	// namespace hamon_config_constexpr_test
