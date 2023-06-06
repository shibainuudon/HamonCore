/**
 *	@file	unit_test_complex_stream_ouput.cpp
 *
 *	@brief	ストリームからの入力のテスト
 *
 *	template <typename T, typename charT, typename traits>
 *	std::basic_istream<charT, traits>& operator>>(std::basic_istream<charT, traits>& is, complex<T>& x);
 */

#include <hamon/complex/complex.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace hamon_complex_test
{

namespace stream_input_test
{

template <typename T>
void test()
{
	{
		std::istringstream is("5");
		hamon::complex<T> c;
		is >> c;
		EXPECT_EQ(c, hamon::complex<T>(5, 0));
		EXPECT_TRUE(is.eof());
	}
	{
		std::istringstream is(" 5 ");
		hamon::complex<T> c;
		is >> c;
		EXPECT_EQ(c, hamon::complex<T>(5, 0));
		EXPECT_TRUE(is.good());
	}
	{
		std::istringstream is(" 5, ");
		hamon::complex<T> c;
		is >> c;
		EXPECT_EQ(c, hamon::complex<T>(5, 0));
		EXPECT_TRUE(is.good());
	}
	{
		std::istringstream is(" , 5, ");
		hamon::complex<T> c;
		is >> c;
		EXPECT_EQ(c, hamon::complex<T>(0, 0));
		EXPECT_TRUE(is.fail());
	}
	{
		std::istringstream is("5.5 ");
		hamon::complex<T> c;
		is >> c;
		EXPECT_EQ(c, hamon::complex<T>(5.5, 0));
		EXPECT_TRUE(is.good());
	}
	{
		std::istringstream is(" ( 5.5 ) ");
		hamon::complex<T> c;
		is >> c;
		EXPECT_EQ(c, hamon::complex<T>(5.5, 0));
		EXPECT_TRUE(is.good());
	}
	{
		std::istringstream is("  5.5)");
		hamon::complex<T> c;
		is >> c;
		EXPECT_EQ(c, hamon::complex<T>(5.5, 0));
		EXPECT_TRUE(is.good());
	}
	{
		std::istringstream is("(5.5 ");
		hamon::complex<T> c;
		is >> c;
		EXPECT_EQ(c, hamon::complex<T>(0, 0));
		EXPECT_TRUE(is.fail());
	}
	{
		std::istringstream is("(5.5,");
		hamon::complex<T> c;
		is >> c;
		EXPECT_EQ(c, hamon::complex<T>(0, 0));
		EXPECT_TRUE(is.fail());
	}
	{
		std::istringstream is("( -5.5 , -6.5 )");
		hamon::complex<T> c;
		is >> c;
		EXPECT_EQ(c, hamon::complex<T>(-5.5, -6.5));
		EXPECT_TRUE(!is.eof());
	}
	{
		std::istringstream is("(-5.5,-6.5)");
		hamon::complex<T> c;
		is >> c;
		EXPECT_EQ(c, hamon::complex<T>(-5.5, -6.5));
		EXPECT_TRUE(!is.eof());
	}
}

GTEST_TEST(ComplexTest, StreamInputTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace stream_input_test

}	// namespace hamon_complex_test
