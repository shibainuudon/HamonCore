/**
 *	@file	unit_test_complex_literals.cpp
 *
 *	@brief	ユーザー定義リテラルのテスト
 *
 *	constexpr complex<long double> operator""il(long double);
 *	constexpr complex<long double> operator""il(unsigned long long);
 *	constexpr complex<double> operator""i(long double);
 *	constexpr complex<double> operator""i(unsigned long long);
 *	constexpr complex<float> operator""if (long double);
 *	constexpr complex<float> operator""if (unsigned long long);
 */

#include <hamon/complex/complex.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_complex_test
{

namespace literals_test
{

template <typename T>
void test()
{
	{
		using namespace hamon::literals::complex_literals;
		static_assert(hamon::is_same<decltype(0.0_il), hamon::complex<long double>>::value, "");
		static_assert(hamon::is_same<decltype(1_il),   hamon::complex<long double>>::value, "");
		static_assert(hamon::is_same<decltype(2.0_i),  hamon::complex<double>>::value, "");
		static_assert(hamon::is_same<decltype(3_i),    hamon::complex<double>>::value, "");
		static_assert(hamon::is_same<decltype(4.0_if), hamon::complex<float>>::value, "");
		static_assert(hamon::is_same<decltype(5_if),   hamon::complex<float>>::value, "");

		{
			HAMON_CXX11_CONSTEXPR auto c1 = 1.0_il;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(c1, hamon::complex<long double>(0, 1.0));
			HAMON_CXX11_CONSTEXPR auto c2 = 1_il;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(c1, c2);
		}
		{
			HAMON_CXX11_CONSTEXPR auto c1 = 2.0_i;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(c1, hamon::complex<double>(0, 2.0));
			HAMON_CXX11_CONSTEXPR auto c2 = 2_i;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(c1, c2);
		}
		{
			HAMON_CXX11_CONSTEXPR auto c1 = 3.0_if;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(c1, hamon::complex<float>(0, 3.0));
			HAMON_CXX11_CONSTEXPR auto c2 = 3_if;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(c1, c2);
		}
		{
			HAMON_CXX11_CONSTEXPR auto c1 = 1.0 + 2.0_i;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(c1, hamon::complex<double>(1, 2.0));
			HAMON_CXX11_CONSTEXPR auto c2 = 1.0 + 2_i;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(c1, c2);
		}
	}
	{
		using namespace hamon::literals;
		static_assert(hamon::is_same<decltype(0.0_il), hamon::complex<long double>>::value, "");
		static_assert(hamon::is_same<decltype(1_il),   hamon::complex<long double>>::value, "");
		static_assert(hamon::is_same<decltype(2.0_i),  hamon::complex<double>>::value, "");
		static_assert(hamon::is_same<decltype(3_i),    hamon::complex<double>>::value, "");
		static_assert(hamon::is_same<decltype(4.0_if), hamon::complex<float>>::value, "");
		static_assert(hamon::is_same<decltype(5_if),   hamon::complex<float>>::value, "");

		{
			HAMON_CXX11_CONSTEXPR auto c1 = 1.0_il;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(c1, hamon::complex<long double>(0, 1.0));
			HAMON_CXX11_CONSTEXPR auto c2 = 1_il;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(c1, c2);
		}
		{
			HAMON_CXX11_CONSTEXPR auto c1 = 2.0_i;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(c1, hamon::complex<double>(0, 2.0));
			HAMON_CXX11_CONSTEXPR auto c2 = 2_i;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(c1, c2);
		}
		{
			HAMON_CXX11_CONSTEXPR auto c1 = 3.0_if;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(c1, hamon::complex<float>(0, 3.0));
			HAMON_CXX11_CONSTEXPR auto c2 = 3_if;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(c1, c2);
		}
		{
			HAMON_CXX11_CONSTEXPR auto c1 = 1.0 + 2.0_i;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(c1, hamon::complex<double>(1, 2.0));
			HAMON_CXX11_CONSTEXPR auto c2 = 1.0 + 2_i;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(c1, c2);
		}
	}
	{
		using namespace hamon;
		static_assert(hamon::is_same<decltype(0.0_il), hamon::complex<long double>>::value, "");
		static_assert(hamon::is_same<decltype(1_il),   hamon::complex<long double>>::value, "");
		static_assert(hamon::is_same<decltype(2.0_i),  hamon::complex<double>>::value, "");
		static_assert(hamon::is_same<decltype(3_i),    hamon::complex<double>>::value, "");
		static_assert(hamon::is_same<decltype(4.0_if), hamon::complex<float>>::value, "");
		static_assert(hamon::is_same<decltype(5_if),   hamon::complex<float>>::value, "");

		{
			HAMON_CXX11_CONSTEXPR auto c1 = 1.0_il;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(c1, hamon::complex<long double>(0, 1.0));
			HAMON_CXX11_CONSTEXPR auto c2 = 1_il;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(c1, c2);
		}
		{
			HAMON_CXX11_CONSTEXPR auto c1 = 2.0_i;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(c1, hamon::complex<double>(0, 2.0));
			HAMON_CXX11_CONSTEXPR auto c2 = 2_i;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(c1, c2);
		}
		{
			HAMON_CXX11_CONSTEXPR auto c1 = 3.0_if;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(c1, hamon::complex<float>(0, 3.0));
			HAMON_CXX11_CONSTEXPR auto c2 = 3_if;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(c1, c2);
		}
		{
			HAMON_CXX11_CONSTEXPR auto c1 = 1.0 + 2.0_i;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(c1, hamon::complex<double>(1, 2.0));
			HAMON_CXX11_CONSTEXPR auto c2 = 1.0 + 2_i;
			HAMON_CXX11_CONSTEXPR_EXPECT_EQ(c1, c2);
		}
	}
}

GTEST_TEST(ComplexTest, LiteralsTest)
{
	test<float>();
	test<double>();
	test<long double>();
}

}	// namespace literals_test

}	// namespace hamon_complex_test
