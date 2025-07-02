/**
 *	@file	unit_test_ratio_ratio_less.cpp
 *
 *	@brief	ratio_less のテスト
 */

#include <hamon/ratio/ratio_less.hpp>
#include <hamon/ratio/ratio.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

#define HAMON_RATIO_LESS_TEST(b, R1, R2)	\
	static_assert(hamon::ratio_less_v<R1, R2>      == b, "");	\
	static_assert(hamon::ratio_less<R1, R2>::value == b, "");	\
	static_assert(hamon::ratio_less<R1, R2>{}()    == b, "");	\
	static_assert(hamon::ratio_less<R1, R2>{}      == b, "")

#else

#define HAMON_RATIO_LESS_TEST(b, R1, R2)	\
	static_assert(hamon::ratio_less<R1, R2>::value == b, "");	\
	static_assert(hamon::ratio_less<R1, R2>{}      == b, "")

#endif

GTEST_TEST(RatioTest, RatioLessTest)
{
	{
		using r1 = hamon::ratio<3, 5>;
		using r2 = hamon::ratio<2, 5>;
		HAMON_RATIO_LESS_TEST(false, r1, r2);
	}
	{
		using r1 = hamon::ratio<2, 5>;
		using r2 = hamon::ratio<2, 5>;
		HAMON_RATIO_LESS_TEST(false, r1, r2);
	}
	{
		using r1 = hamon::ratio<1, 5>;
		using r2 = hamon::ratio<2, 5>;
		HAMON_RATIO_LESS_TEST(true, r1, r2);
	}
	{
		using r1 = hamon::ratio<1, 2>;
		using r2 = hamon::ratio<1, 3>;
		HAMON_RATIO_LESS_TEST(false, r1, r2);
	}
	{
		using r1 = hamon::ratio<4, 7>;
		using r2 = hamon::ratio<5, 8>;
		HAMON_RATIO_LESS_TEST(true, r1, r2);
	}
	{
		using r1 = hamon::ratio<4, 7>;
		using r2 = hamon::ratio<-5, 8>;
		HAMON_RATIO_LESS_TEST(false, r1, r2);
	}
	{
		using r1 = hamon::ratio<1, 1>;
		using r2 = hamon::ratio<1, -1>;
		HAMON_RATIO_LESS_TEST(false, r1, r2);
	}
	{
		using r1 = hamon::ratio<0x7FFFFFFFFFFFFFFFLL, 1>;
		using r2 = hamon::ratio<0x7FFFFFFFFFFFFFFFLL, 1>;
		HAMON_RATIO_LESS_TEST(false, r1, r2);
	}
	{
		using r1 = hamon::ratio<-0x7FFFFFFFFFFFFFFFLL, 1>;
		using r2 = hamon::ratio<0x7FFFFFFFFFFFFFFFLL, 1>;
		HAMON_RATIO_LESS_TEST(true, r1, r2);
	}
	{
		using r1 = hamon::ratio<0x7FFFFFFFFFFFFFFFLL, 1>;
		using r2 = hamon::ratio<-0x7FFFFFFFFFFFFFFFLL, 1>;
		HAMON_RATIO_LESS_TEST(false, r1, r2);
	}
	{
		using r1 = hamon::ratio<0x7FFFFFFFFFFFFFFELL, 1>;
		using r2 = hamon::ratio<0x7FFFFFFFFFFFFFFFLL, 1>;
		HAMON_RATIO_LESS_TEST(true, r1, r2);
	}
	{
		using r1 = hamon::ratio<0x7FFFFFFFFFFFFFFFLL, 1>;
		using r2 = hamon::ratio<0x7FFFFFFFFFFFFFFELL, 1>;
		HAMON_RATIO_LESS_TEST(false, r1, r2);
	}
	{
		using r1 = hamon::ratio<1, 0x7FFFFFFFFFFFFFFFLL>;
		using r2 = hamon::ratio<1, 0x7FFFFFFFFFFFFFFFLL>;
		HAMON_RATIO_LESS_TEST(false, r1, r2);
	}
	{
		using r1 = hamon::ratio<1, 0x7FFFFFFFFFFFFFFELL>;
		using r2 = hamon::ratio<1, 0x7FFFFFFFFFFFFFFFLL>;
		HAMON_RATIO_LESS_TEST(false, r1, r2);
	}
	{
		using r1 = hamon::ratio<1, 0x7FFFFFFFFFFFFFFFLL>;
		using r2 = hamon::ratio<1, 0x7FFFFFFFFFFFFFFELL>;
		HAMON_RATIO_LESS_TEST(true, r1, r2);
	}
	{
		using r1 = hamon::ratio<0x7FFFFFFFFFFFFFFFLL, 0x7FFFFFFFFFFFFFFELL>;
		using r2 = hamon::ratio<0x7FFFFFFFFFFFFFFDLL, 0x7FFFFFFFFFFFFFFCLL>;
		HAMON_RATIO_LESS_TEST(true, r1, r2);
	}
	{
		using r1 = hamon::ratio<0x7FFFFFFFFFFFFFFDLL, 0x7FFFFFFFFFFFFFFCLL>;
		using r2 = hamon::ratio<0x7FFFFFFFFFFFFFFFLL, 0x7FFFFFFFFFFFFFFELL>;
		HAMON_RATIO_LESS_TEST(false, r1, r2);
	}
	{
		using r1 = hamon::ratio<-0x7FFFFFFFFFFFFFFDLL, 0x7FFFFFFFFFFFFFFCLL>;
		using r2 = hamon::ratio<-0x7FFFFFFFFFFFFFFFLL, 0x7FFFFFFFFFFFFFFELL>;
		HAMON_RATIO_LESS_TEST(true, r1, r2);
	}
	{
		using r1 = hamon::ratio<0x7FFFFFFFFFFFFFFFLL, 0x7FFFFFFFFFFFFFFELL>;
		using r2 = hamon::ratio<0x7FFFFFFFFFFFFFFELL, 0x7FFFFFFFFFFFFFFDLL>;
		HAMON_RATIO_LESS_TEST(true, r1, r2);
	}
	{
		using r1 = hamon::ratio<641981, 1339063>;
		using r2 = hamon::ratio<1291640, 2694141LL>;
		HAMON_RATIO_LESS_TEST(false, r1, r2);
	}
	{
		using r1 = hamon::ratio<1291640, 2694141LL>;
		using r2 = hamon::ratio<641981, 1339063>;
		HAMON_RATIO_LESS_TEST(true, r1, r2);
	}
}

#undef HAMON_RATIO_LESS_TEST
