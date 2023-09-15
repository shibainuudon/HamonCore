/**
 *	@file	unit_test_algorithm_max.cpp
 *
 *	@brief	max のテスト
 */

#include <hamon/algorithm/max.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace max_test
{

template <typename T>
void MaxTestUnsigned(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  0, hamon::max((T)  0, (T)  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  1, hamon::max((T)  0, (T)  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  1, hamon::max((T)  1, (T)  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  1, hamon::max((T)  1, (T)  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)100, hamon::max((T)100, (T)100));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)101, hamon::max((T)100, (T)101));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)101, hamon::max((T)101, (T)100));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)101, hamon::max((T)101, (T)101));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)3, hamon::max((T)2, (T)3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)3, hamon::max((T)2, (T)3, hamon::less<>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)2, hamon::max((T)2, (T)3, hamon::greater<>()));

	EXPECT_EQ((T)3, hamon::max({(T)3}));
	EXPECT_EQ((T)3, hamon::max({(T)3, (T)1}));
	EXPECT_EQ((T)4, hamon::max({(T)3, (T)1, (T)4}));
	EXPECT_EQ((T)4, hamon::max({(T)3, (T)1, (T)4, (T)1}));
	EXPECT_EQ((T)5, hamon::max({(T)3, (T)1, (T)4, (T)1, (T)5}));
	EXPECT_EQ((T)5, hamon::max({(T)3, (T)1, (T)4, (T)1, (T)5}, hamon::less<>()));
	EXPECT_EQ((T)1, hamon::max({(T)3, (T)1, (T)4, (T)1, (T)5}, hamon::greater<>()));
}

template <typename T>
void MaxTestSigned(void)
{
	MaxTestUnsigned<T>();
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  -1, hamon::max((T)  -1, (T)  -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  -1, hamon::max((T)  -1, (T)  -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  -1, hamon::max((T)  -2, (T)  -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  -2, hamon::max((T)  -2, (T)  -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-100, hamon::max((T)-100, (T)-100));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-100, hamon::max((T)-100, (T)-101));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-100, hamon::max((T)-101, (T)-100));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-101, hamon::max((T)-101, (T)-101));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-2, hamon::max((T)-2, (T)-3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-2, hamon::max((T)-2, (T)-3, hamon::less<>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-3, hamon::max((T)-2, (T)-3, hamon::greater<>()));

	EXPECT_EQ((T)-3, hamon::max({(T)-3}));
	EXPECT_EQ((T)-1, hamon::max({(T)-3, (T)-1}));
	EXPECT_EQ((T)-1, hamon::max({(T)-3, (T)-1, (T)-4}));
	EXPECT_EQ((T)-1, hamon::max({(T)-3, (T)-1, (T)-4, (T)-1}));
	EXPECT_EQ((T)-1, hamon::max({(T)-3, (T)-1, (T)-4, (T)-1, (T)-5}));
	EXPECT_EQ((T)-1, hamon::max({(T)-3, (T)-1, (T)-4, (T)-1, (T)-5}, hamon::less<>()));
	EXPECT_EQ((T)-5, hamon::max({(T)-3, (T)-1, (T)-4, (T)-1, (T)-5}, hamon::greater<>()));
}

template <typename T>
void MaxTestFloat(void)
{
	MaxTestSigned<T>();
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 0.00, hamon::max((T) 0.00, (T) 0.00));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 0.75, hamon::max((T) 0.50, (T) 0.75));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 0.50, hamon::max((T) 0.50, (T) 0.25));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-0.50, hamon::max((T)-0.50, (T)-0.75));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-0.25, hamon::max((T)-0.50, (T)-0.25));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 2.5, hamon::max((T) 1.5, (T) 2.5, hamon::less<>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-1.5, hamon::max((T)-1.5, (T)-2.5, hamon::less<>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 1.5, hamon::max((T) 1.5, (T) 2.5, hamon::greater<>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-2.5, hamon::max((T)-1.5, (T)-2.5, hamon::greater<>()));

	EXPECT_EQ((T)-3.5, hamon::max({(T)-3.5}));
	EXPECT_EQ((T) 1.5, hamon::max({(T)-3.5, (T)1.5}));
	EXPECT_EQ((T) 4.5, hamon::max({(T)-3.5, (T)1.5, (T)4.5}));
	EXPECT_EQ((T) 4.5, hamon::max({(T)-3.5, (T)1.5, (T)4.5, (T)-1.5}));
	EXPECT_EQ((T) 5.5, hamon::max({(T)-3.5, (T)1.5, (T)4.5, (T)-1.5, (T)5.5}));
	EXPECT_EQ((T) 5.5, hamon::max({(T)-3.5, (T)1.5, (T)4.5, (T)-1.5, (T)5.5}, hamon::less<>()));
	EXPECT_EQ((T)-3.5, hamon::max({(T)-3.5, (T)1.5, (T)4.5, (T)-1.5, (T)5.5}, hamon::greater<>()));
}

GTEST_TEST(AlgorithmTest, MaxTest)
{
	MaxTestUnsigned<unsigned char>();
	MaxTestUnsigned<unsigned short>();
	MaxTestUnsigned<unsigned int>();
	MaxTestUnsigned<unsigned long>();
	MaxTestUnsigned<unsigned long long>();

	MaxTestSigned<signed char>();
	MaxTestSigned<signed short>();
	MaxTestSigned<signed int>();
	MaxTestSigned<signed long>();
	MaxTestSigned<signed long long>();

	MaxTestFloat<float>();
	MaxTestFloat<double>();
	MaxTestFloat<long double>();

	EXPECT_EQ('a', hamon::max({'a'}));
	EXPECT_EQ('z', hamon::max({'a', 'z'}));
	EXPECT_EQ('c', hamon::max({'a', 'c', 'b'}));
	EXPECT_EQ("hoge", hamon::max(hamon::string("foo"), hamon::string("hoge")));
	EXPECT_EQ("zzzz", hamon::max({hamon::string("abc"), hamon::string("ABC"), hamon::string("zzzz")}));
}

}	// namespace max_test

}	// namespace hamon_algorithm_test
