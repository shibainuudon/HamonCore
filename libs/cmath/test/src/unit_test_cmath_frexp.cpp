/**
 *	@file	unit_test_cmath_frexp.cpp
 *
 *	@brief	frexp のテスト
 */

#include <hamon/cmath/frexp.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/limits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace frexp_test
{

static_assert(hamon::is_same<float,       decltype(hamon::frexp(0.0f,  nullptr))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::frexpf(0.0f, nullptr))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::frexp(0.0,   nullptr))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::frexp(0,     nullptr))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::frexp(0.0l,  nullptr))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::frexpl(0.0l, nullptr))>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool FrexpTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan = hamon::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = hamon::numeric_limits<T>::infinity();

	{
		int exp = 0;
		auto x = hamon::frexp(T(0.125), &exp);
		VERIFY(x == T(0.5));
		VERIFY(exp == -2);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(0.25), &exp);
		VERIFY(x == T(0.5));
		VERIFY(exp == -1);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(0.5), &exp);
		VERIFY(x == T(0.5));
		VERIFY(exp == 0);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(1.0), &exp);
		VERIFY(x == T(0.5));
		VERIFY(exp == 1);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(1.5), &exp);
		VERIFY(x == T(0.75));
		VERIFY(exp == 1);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(2.0), &exp);
		VERIFY(x == T(0.5));
		VERIFY(exp == 2);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(2.5), &exp);
		VERIFY(x == T(0.625));
		VERIFY(exp == 2);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(3.0), &exp);
		VERIFY(x == T(0.75));
		VERIFY(exp == 2);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(4.0), &exp);
		VERIFY(x == T(0.5));
		VERIFY(exp == 3);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(5.0), &exp);
		VERIFY(x == T(0.625));
		VERIFY(exp == 3);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(-0.125), &exp);
		VERIFY(x == T(-0.5));
		VERIFY(exp == -2);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(-0.5), &exp);
		VERIFY(x == T(-0.5));
		VERIFY(exp == 0);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(-1.0), &exp);
		VERIFY(x == T(-0.5));
		VERIFY(exp == 1);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(-2.0), &exp);
		VERIFY(x == T(-0.5));
		VERIFY(exp == 2);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(-4.0), &exp);
		VERIFY(x == T(-0.5));
		VERIFY(exp == 3);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(+0.0), &exp);
		VERIFY(x == T(+0.0));
		VERIFY(exp == 0);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(-0.0), &exp);
		VERIFY(x == T(-0.0));
		VERIFY(exp == 0);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(+inf), &exp);
		VERIFY(x == T(+inf));
		//VERIFY(exp == 0);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(-inf), &exp);
		VERIFY(x == T(-inf));
		//VERIFY(exp == 0);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(+nan), &exp);
		VERIFY(hamon::isnan(x));
		//VERIFY(exp == 0);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(-nan), &exp);
		VERIFY(hamon::isnan(x));
		//VERIFY(exp == 0);
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool FrexpTestSignedInt(void)
{
	{
		int exp = 0;
		auto x = hamon::frexp(T(1), &exp);
		VERIFY(x == 0.5);
		VERIFY(exp == 1);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(2), &exp);
		VERIFY(x == 0.5);
		VERIFY(exp == 2);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(3), &exp);
		VERIFY(x == 0.75);
		VERIFY(exp == 2);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(4), &exp);
		VERIFY(x == 0.5);
		VERIFY(exp == 3);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(5), &exp);
		VERIFY(x == 0.625);
		VERIFY(exp == 3);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(-1), &exp);
		VERIFY(-x == 0.5);
		VERIFY(exp == 1);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(-2), &exp);
		VERIFY(-x == 0.5);
		VERIFY(exp == 2);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(-4), &exp);
		VERIFY(-x == 0.5);
		VERIFY(exp == 3);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(0), &exp);
		VERIFY(x == 0.0);
		VERIFY(exp == 0);
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool FrexpTestUnsignedInt(void)
{
	{
		int exp = 0;
		auto x = hamon::frexp(T(1), &exp);
		VERIFY(x == 0.5);
		VERIFY(exp == 1);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(2), &exp);
		VERIFY(x == 0.5);
		VERIFY(exp == 2);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(3), &exp);
		VERIFY(x == 0.75);
		VERIFY(exp == 2);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(4), &exp);
		VERIFY(x == 0.5);
		VERIFY(exp == 3);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(5), &exp);
		VERIFY(x == 0.625);
		VERIFY(exp == 3);
	}
	{
		int exp = 0;
		auto x = hamon::frexp(T(0), &exp);
		VERIFY(x == 0.0);
		VERIFY(exp == 0);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(CMathTest, FrexpTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FrexpTestFloat<float>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FrexpTestFloat<double>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FrexpTestFloat<long double>());

//	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FrexpTestSignedInt<int>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FrexpTestSignedInt<signed char>());
//	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FrexpTestSignedInt<short>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FrexpTestSignedInt<long>());
//	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FrexpTestSignedInt<long long>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FrexpTestUnsignedInt<unsigned int>());
//	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FrexpTestUnsignedInt<unsigned char>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FrexpTestUnsignedInt<unsigned short>());
//	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FrexpTestUnsignedInt<unsigned long>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(FrexpTestUnsignedInt<unsigned long long>());
}

}	// namespace frexp_test

}	// namespace hamon_cmath_test
