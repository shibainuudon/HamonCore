/**
 *	@file	unit_test_algorithm_min.cpp
 *
 *	@brief	min のテスト
 */

#include <hamon/algorithm/min.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/functional/greater.hpp>
#include <gtest/gtest.h>
#include <string>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace min_test
{

template <typename T>
void MinTestUnsigned(void)
{
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  0, hamon::min((T)  0, (T)  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  0, hamon::min((T)  0, (T)  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  0, hamon::min((T)  1, (T)  0));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  1, hamon::min((T)  1, (T)  1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)100, hamon::min((T)100, (T)100));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)100, hamon::min((T)100, (T)101));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)100, hamon::min((T)101, (T)100));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)101, hamon::min((T)101, (T)101));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)2, hamon::min((T)2, (T)3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)2, hamon::min((T)2, (T)3, hamon::less<>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)3, hamon::min((T)2, (T)3, hamon::greater<>()));

	EXPECT_EQ((T)3, hamon::min({(T)3}));
	EXPECT_EQ((T)1, hamon::min({(T)3, (T)1}));
	EXPECT_EQ((T)1, hamon::min({(T)3, (T)1, (T)4}));
	EXPECT_EQ((T)1, hamon::min({(T)3, (T)1, (T)4, (T)1}));
	EXPECT_EQ((T)1, hamon::min({(T)3, (T)1, (T)4, (T)1, (T)5}));
	EXPECT_EQ((T)1, hamon::min({(T)3, (T)1, (T)4, (T)1, (T)5}, hamon::less<>()));
	EXPECT_EQ((T)5, hamon::min({(T)3, (T)1, (T)4, (T)1, (T)5}, hamon::greater<>()));
}

template <typename T>
void MinTestSigned(void)
{
	MinTestUnsigned<T>();
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  -1, hamon::min((T)  -1, (T)  -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  -2, hamon::min((T)  -1, (T)  -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  -2, hamon::min((T)  -2, (T)  -1));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)  -2, hamon::min((T)  -2, (T)  -2));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-100, hamon::min((T)-100, (T)-100));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-101, hamon::min((T)-100, (T)-101));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-101, hamon::min((T)-101, (T)-100));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-101, hamon::min((T)-101, (T)-101));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-3, hamon::min((T)-2, (T)-3));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-3, hamon::min((T)-2, (T)-3, hamon::less<>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-2, hamon::min((T)-2, (T)-3, hamon::greater<>()));

	EXPECT_EQ((T)-3, hamon::min({(T)-3}));
	EXPECT_EQ((T)-3, hamon::min({(T)-3, (T)-1}));
	EXPECT_EQ((T)-4, hamon::min({(T)-3, (T)-1, (T)-4}));
	EXPECT_EQ((T)-4, hamon::min({(T)-3, (T)-1, (T)-4, (T)-1}));
	EXPECT_EQ((T)-5, hamon::min({(T)-3, (T)-1, (T)-4, (T)-1, (T)-5}));
	EXPECT_EQ((T)-5, hamon::min({(T)-3, (T)-1, (T)-4, (T)-1, (T)-5}, hamon::less<>()));
	EXPECT_EQ((T)-1, hamon::min({(T)-3, (T)-1, (T)-4, (T)-1, (T)-5}, hamon::greater<>()));
}

template <typename T>
void MinTestFloat(void)
{
	MinTestSigned<T>();
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 0.00, hamon::min((T) 0.00, (T) 0.00));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 0.50, hamon::min((T) 0.50, (T) 0.75));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 0.25, hamon::min((T) 0.50, (T) 0.25));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-0.75, hamon::min((T)-0.50, (T)-0.75));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-0.50, hamon::min((T)-0.50, (T)-0.25));

	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 1.5, hamon::min((T) 1.5, (T) 2.5, hamon::less<>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-2.5, hamon::min((T)-1.5, (T)-2.5, hamon::less<>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T) 2.5, hamon::min((T) 1.5, (T) 2.5, hamon::greater<>()));
	HAMON_CXX11_CONSTEXPR_EXPECT_EQ((T)-1.5, hamon::min((T)-1.5, (T)-2.5, hamon::greater<>()));

	EXPECT_EQ((T)-3.5, hamon::min({(T)-3.5}));
	EXPECT_EQ((T)-3.5, hamon::min({(T)-3.5, (T)1.5}));
	EXPECT_EQ((T)-4.5, hamon::min({(T)-3.5, (T)1.5, (T)-4.5}));
	EXPECT_EQ((T)-4.5, hamon::min({(T)-3.5, (T)1.5, (T)-4.5, (T)-1.5}));
	EXPECT_EQ((T)-5.5, hamon::min({(T)-3.5, (T)1.5, (T)-4.5, (T)-1.5, (T)-5.5}));
	EXPECT_EQ((T)-5.5, hamon::min({(T)-3.5, (T)1.5, (T)-4.5, (T)-1.5, (T)-5.5}, hamon::less<>()));
	EXPECT_EQ((T) 1.5, hamon::min({(T)-3.5, (T)1.5, (T)-4.5, (T)-1.5, (T)-5.5}, hamon::greater<>()));
}

GTEST_TEST(AlgorithmTest, MinTest)
{
	MinTestUnsigned<unsigned char>();
	MinTestUnsigned<unsigned short>();
	MinTestUnsigned<unsigned int>();
	MinTestUnsigned<unsigned long>();
	MinTestUnsigned<unsigned long long>();

	MinTestSigned<signed char>();
	MinTestSigned<signed short>();
	MinTestSigned<signed int>();
	MinTestSigned<signed long>();
	MinTestSigned<signed long long>();

	MinTestFloat<float>();
	MinTestFloat<double>();
	MinTestFloat<long double>();

	EXPECT_EQ('a', hamon::min({'a'}));
	EXPECT_EQ('x', hamon::min({'x', 'y'}));
	EXPECT_EQ('a', hamon::min({'c', 'b', 'a'}));
	EXPECT_EQ("foo", hamon::min(std::string("foo"), std::string("hoge")));
	EXPECT_EQ("ABC", hamon::min({std::string("abc"), std::string("ABC"), std::string("zzzz")}));
}

}	// namespace min_test

}	// namespace hamon_algorithm_test
