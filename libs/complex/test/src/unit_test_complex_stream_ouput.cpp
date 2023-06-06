/**
 *	@file	unit_test_complex_stream_ouput.cpp
 *
 *	@brief	ストリームへの出力のテスト
 *
 *	template <typename T, typename charT, typename traits>
 *	std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& os, complex<T> const& x);
 */

#include <hamon/complex/complex.hpp>
#include <gtest/gtest.h>
#include <sstream>

namespace hamon_complex_test
{

namespace stream_output_test
{

template <typename T>
void test()
{
	{
		hamon::complex<T> const c(1, 2);
		std::ostringstream os;
		os << c;
		EXPECT_EQ(os.str(), "(1,2)");
	}
	{
		hamon::complex<T> const c(-2, 1);
		std::ostringstream os;
		os << c;
		EXPECT_EQ(os.str(), "(-2,1)");
	}
	{
		hamon::complex<T> const c(12, -345);
		std::ostringstream os;
		os << c;
		EXPECT_EQ(os.str(), "(12,-345)");
	}
}

GTEST_TEST(ComplexTest, StreamOutputTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace stream_output_test

}	// namespace hamon_complex_test
