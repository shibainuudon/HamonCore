/**
 *	@file	unit_test_cmath_modf.cpp
 *
 *	@brief	modf のテスト
 */

#include <hamon/cmath/modf.hpp>
#include <hamon/cmath/isnan.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <limits>
#include "constexpr_test.hpp"

namespace hamon_cmath_test
{

namespace floor_test
{

static_assert(hamon::is_same<float,       decltype(hamon::modf(0.0f,  (float*)nullptr))>::value, "");
static_assert(hamon::is_same<float,       decltype(hamon::modff(0.0f, (float*)nullptr))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::modf(0.0,   (double*)nullptr))>::value, "");
static_assert(hamon::is_same<double,      decltype(hamon::modf(0,     (double*)nullptr))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::modf(0.0l,  (long double*)nullptr))>::value, "");
static_assert(hamon::is_same<long double, decltype(hamon::modfl(0.0l, (long double*)nullptr))>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool ModfTestFloat(void)
{
	HAMON_CXX11_CONSTEXPR auto nan = std::numeric_limits<T>::quiet_NaN();
	HAMON_CXX11_CONSTEXPR auto inf = std::numeric_limits<T>::infinity();

	{
		T i = 0;
		auto x = hamon::modf(T(123.5), &i);
		VERIFY(T(123.0) == i);
		VERIFY(T(  0.5) == x);
	}
	{
		T i = 0;
		auto x = hamon::modf(T(1.0), &i);
		VERIFY(T( 1.0) == i);
		VERIFY(T( 0.0) == x);
	}
	{
		T i = 0;
		auto x = hamon::modf(T(1.125), &i);
		VERIFY(T( 1.0) == i);
		VERIFY(T( 0.125) == x);
	}
	{
		T i = 0;
		auto x = hamon::modf(T(1.875), &i);
		VERIFY(T( 1.0) == i);
		VERIFY(T( 0.875) == x);
	}
	{
		T i = 0;
		auto x = hamon::modf(T(-1.0), &i);
		VERIFY(T(-1.0) == i);
		VERIFY(T( 0.0) == x);
	}
	{
		T i = 0;
		auto x = hamon::modf(T(-1.875), &i);
		VERIFY(T(-1.0) == i);
		VERIFY(T(-0.875) == x);
	}
	{
		T i = 0;
		auto x = hamon::modf(T(-1.25), &i);
		VERIFY(T(-1.0)  == i);
		VERIFY(T(-0.25) == x);
	}
	{
		T i = 0;
		auto x = hamon::modf(T(+0.0), &i);
		VERIFY(T(+0.0) == i);
		VERIFY(T(+0.0) == x);
	}
	{
		T i = 0;
		auto x = hamon::modf(T(-0.0), &i);
		VERIFY(T(-0.0) == i);
		VERIFY(T(-0.0) == x);
	}
	{
		T i = 0;
		auto x = hamon::modf(T(+inf), &i);
		VERIFY(T(+inf) == i);
		VERIFY(T(+0.0) == x);
	}
	{
		T i = 0;
		auto x = hamon::modf(T(-inf), &i);
		VERIFY(T(-inf) == i);
		VERIFY(T(-0.0) == x);
	}
	{
		T i = 0;
		auto x = hamon::modf(T(+nan), &i);
		VERIFY(hamon::isnan(i));
		VERIFY(hamon::isnan(x));
	}
	{
		T i = 0;
		auto x = hamon::modf(T(-nan), &i);
		VERIFY(hamon::isnan(i));
		VERIFY(hamon::isnan(x));
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool ModfTestSignedInt(void)
{
	{
		double i = 0;
		auto x = hamon::modf(T(0), &i);
		VERIFY(0 == i);
		VERIFY(0 == x);
	}
	{
		double i = 0;
		auto x = hamon::modf(T(-1), &i);
		VERIFY(-1 == i);
		VERIFY(0 == x);
	}
	{
		double i = 0;
		auto x = hamon::modf(T(13), &i);
		VERIFY(13 == i);
		VERIFY(0 == x);
	}
	{
		double i = 0;
		auto x = hamon::modf(T(-42), &i);
		VERIFY(-42 == i);
		VERIFY(0 == x);
	}

	return true;
}

template <typename T>
inline HAMON_CXX14_CONSTEXPR bool ModfTestUnsignedInt(void)
{
	{
		double i = 0;
		auto x = hamon::modf(T(0), &i);
		VERIFY(0 == i);
		VERIFY(0 == x);
	}
	{
		double i = 0;
		auto x = hamon::modf(T(1), &i);
		VERIFY(1 == i);
		VERIFY(0 == x);
	}
	{
		double i = 0;
		auto x = hamon::modf(T(42), &i);
		VERIFY(42 == i);
		VERIFY(0 == x);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(CMathTest, ModfTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ModfTestFloat<float>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ModfTestFloat<double>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ModfTestFloat<long double>());

//	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ModfTestSignedInt<int>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ModfTestSignedInt<signed char>());
//	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ModfTestSignedInt<short>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ModfTestSignedInt<long>());
//	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ModfTestSignedInt<long long>());

	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ModfTestUnsignedInt<unsigned int>());
//	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ModfTestUnsignedInt<unsigned char>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ModfTestUnsignedInt<unsigned short>());
//	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ModfTestUnsignedInt<unsigned long>());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(ModfTestUnsignedInt<unsigned long long>());
}

}	// namespace floor_test

}	// namespace hamon_cmath_test
