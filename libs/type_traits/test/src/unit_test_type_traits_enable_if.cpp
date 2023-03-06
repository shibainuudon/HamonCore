﻿/**
 *	@file	unit_test_type_traits_enable_if.cpp
 *
 *	@brief	enable_if のテスト
 */

#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_signed.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <gtest/gtest.h>
#include <string>
#include <vector>

namespace hamon_type_traits_test
{

namespace enable_if_test
{

template <typename T>
int func1(T, typename hamon::enable_if<hamon::is_signed<T>::value>::type* = 0)
{
	return 0;
}

template <typename T>
int func1(T, typename hamon::enable_if<!hamon::is_signed<T>::value>::type* = 0)
{
	return 1;
}

template <typename T>
int func2(T, hamon::enable_if_t<hamon::is_unsigned<T>::value>* = 0)
{
	return 0;
}

template <typename T>
int func2(T, hamon::enable_if_t<!hamon::is_unsigned<T>::value>* = 0)
{
	return 1;
}

struct A
{
};

GTEST_TEST(TypeTraitsTest, EnableIfTest)
{
	signed char sc = 0;
	unsigned char uc = 0;
	signed short ss = 0;
	unsigned short us = 0;
	signed int si = 0;
	unsigned int ui = 0;
	signed long sl = 0;
	unsigned long ul = 0;
	signed long long sll = 0;
	unsigned long long ull = 0;
	float f = 0;
	double d = 0;
	void* vp = 0;
	std::string str;
	std::vector<int> vec;
	A a;

	EXPECT_EQ(0, func1(sc));
	EXPECT_EQ(1, func1(uc));
	EXPECT_EQ(0, func1(ss));
	EXPECT_EQ(1, func1(us));
	EXPECT_EQ(0, func1(si));
	EXPECT_EQ(1, func1(ui));
	EXPECT_EQ(0, func1(sl));
	EXPECT_EQ(1, func1(ul));
	EXPECT_EQ(0, func1(sll));
	EXPECT_EQ(1, func1(ull));
	EXPECT_EQ(0, func1(f));
	EXPECT_EQ(0, func1(d));
	EXPECT_EQ(1, func1(vp));
	EXPECT_EQ(1, func1(str));
	EXPECT_EQ(1, func1(vec));
	EXPECT_EQ(1, func1(a));

	EXPECT_EQ(1, func2(sc));
	EXPECT_EQ(0, func2(uc));
	EXPECT_EQ(1, func2(ss));
	EXPECT_EQ(0, func2(us));
	EXPECT_EQ(1, func2(si));
	EXPECT_EQ(0, func2(ui));
	EXPECT_EQ(1, func2(sl));
	EXPECT_EQ(0, func2(ul));
	EXPECT_EQ(1, func2(sll));
	EXPECT_EQ(0, func2(ull));
	EXPECT_EQ(1, func2(f));
	EXPECT_EQ(1, func2(d));
	EXPECT_EQ(1, func2(vp));
	EXPECT_EQ(1, func2(str));
	EXPECT_EQ(1, func2(vec));
	EXPECT_EQ(1, func2(a));
}

}	// namespace enable_if_test

}	// namespace hamon_type_traits_test
