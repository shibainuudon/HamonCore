/**
 *	@file	unit_test_numeric_reduce.cpp
 *
 *	@brief	reduce のテスト
 */

#include <hamon/numeric/reduce.hpp>
#include <hamon/functional/multiplies.hpp>
#include <hamon/iterator/begin.hpp>
#include <hamon/iterator/end.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "ranges_test.hpp"

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)	// conversion from '...' to '...', possible loss of data

namespace hamon_numeric_test
{

namespace reduce_test
{

GTEST_TEST(NumericTest, ReduceTest)
{
	{
		HAMON_CXX11_CONSTEXPR int a[] = {42};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, hamon::reduce(hamon::begin(a), hamon::end(a)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(52, hamon::reduce(hamon::begin(a), hamon::end(a), 10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(42, hamon::reduce(hamon::begin(a), hamon::end(a), 1, hamon::multiplies<>{}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(84, hamon::reduce(hamon::begin(a), hamon::end(a), 2, hamon::multiplies<>{}));
	}
	{
		HAMON_CXX11_CONSTEXPR int a[] = {3, 4};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(7 , hamon::reduce(hamon::begin(a), hamon::end(a)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(17, hamon::reduce(hamon::begin(a), hamon::end(a), 10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, hamon::reduce(hamon::begin(a), hamon::end(a), 1, hamon::multiplies<>{}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(24, hamon::reduce(hamon::begin(a), hamon::end(a), 2, hamon::multiplies<>{}));
	}
	{
		HAMON_CXX11_CONSTEXPR int a[] = {1, 2, 3};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, hamon::reduce(hamon::begin(a), hamon::end(a)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(16, hamon::reduce(hamon::begin(a), hamon::end(a), 10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 6, hamon::reduce(hamon::begin(a), hamon::end(a), 1, hamon::multiplies<>{}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(12, hamon::reduce(hamon::begin(a), hamon::end(a), 2, hamon::multiplies<>{}));
	}
	{
		HAMON_CXX11_CONSTEXPR int a[] = {1, 2, 3, 4};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10, hamon::reduce(hamon::begin(a), hamon::end(a)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(20, hamon::reduce(hamon::begin(a), hamon::end(a), 10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(24, hamon::reduce(hamon::begin(a), hamon::end(a), 1, hamon::multiplies<>{}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(48, hamon::reduce(hamon::begin(a), hamon::end(a), 2, hamon::multiplies<>{}));
	}
	{
		HAMON_CXX11_CONSTEXPR int a[] = {1, 2, 3, 4, 5};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 15, hamon::reduce(hamon::begin(a), hamon::end(a)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 25, hamon::reduce(hamon::begin(a), hamon::end(a), 10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(120, hamon::reduce(hamon::begin(a), hamon::end(a), 1, hamon::multiplies<>{}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(240, hamon::reduce(hamon::begin(a), hamon::end(a), 2, hamon::multiplies<>{}));
	}
	{
		HAMON_CXX11_CONSTEXPR int a[] = {1, 2, 3, 4, 5, 6};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  21, hamon::reduce(hamon::begin(a), hamon::end(a)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(  31, hamon::reduce(hamon::begin(a), hamon::end(a), 10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 720, hamon::reduce(hamon::begin(a), hamon::end(a), 1, hamon::multiplies<>{}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(1440, hamon::reduce(hamon::begin(a), hamon::end(a), 2, hamon::multiplies<>{}));
	}
	{
		HAMON_CXX11_CONSTEXPR int a[] = {1, 2, 3, 4, 5, 6, 7};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(   28, hamon::reduce(hamon::begin(a), hamon::end(a)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(   38, hamon::reduce(hamon::begin(a), hamon::end(a), 10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 5040, hamon::reduce(hamon::begin(a), hamon::end(a), 1, hamon::multiplies<>{}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(10080, hamon::reduce(hamon::begin(a), hamon::end(a), 2, hamon::multiplies<>{}));
	}
	{
		HAMON_CXX11_CONSTEXPR int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(   36, hamon::reduce(hamon::begin(a), hamon::end(a)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(   46, hamon::reduce(hamon::begin(a), hamon::end(a), 10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(40320, hamon::reduce(hamon::begin(a), hamon::end(a), 1, hamon::multiplies<>{}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(80640, hamon::reduce(hamon::begin(a), hamon::end(a), 2, hamon::multiplies<>{}));
	}
	{
		HAMON_CXX11_CONSTEXPR int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 1};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(   37, hamon::reduce(hamon::begin(a), hamon::end(a)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(   47, hamon::reduce(hamon::begin(a), hamon::end(a), 10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(40320, hamon::reduce(hamon::begin(a), hamon::end(a), 1, hamon::multiplies<>{}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(80640, hamon::reduce(hamon::begin(a), hamon::end(a), 2, hamon::multiplies<>{}));
	}
	{
		HAMON_CXX11_CONSTEXPR int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 1, 2};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(    39, hamon::reduce(hamon::begin(a), hamon::end(a)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(    49, hamon::reduce(hamon::begin(a), hamon::end(a), 10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 80640, hamon::reduce(hamon::begin(a), hamon::end(a), 1, hamon::multiplies<>{}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(161280, hamon::reduce(hamon::begin(a), hamon::end(a), 2, hamon::multiplies<>{}));
	}
	{
		HAMON_CXX11_CONSTEXPR int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(    42, hamon::reduce(hamon::begin(a), hamon::end(a)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(    52, hamon::reduce(hamon::begin(a), hamon::end(a), 10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(241920, hamon::reduce(hamon::begin(a), hamon::end(a), 1, hamon::multiplies<>{}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(483840, hamon::reduce(hamon::begin(a), hamon::end(a), 2, hamon::multiplies<>{}));
	}
	{
		HAMON_CXX11_CONSTEXPR int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 2};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(    44, hamon::reduce(hamon::begin(a), hamon::end(a)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(    54, hamon::reduce(hamon::begin(a), hamon::end(a), 10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(483840, hamon::reduce(hamon::begin(a), hamon::end(a), 1, hamon::multiplies<>{}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(967680, hamon::reduce(hamon::begin(a), hamon::end(a), 2, hamon::multiplies<>{}));
	}
	{
		HAMON_CXX11_CONSTEXPR int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 2, 5};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(     49, hamon::reduce(hamon::begin(a), hamon::end(a)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(     59, hamon::reduce(hamon::begin(a), hamon::end(a), 10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(2419200, hamon::reduce(hamon::begin(a), hamon::end(a), 1, hamon::multiplies<>{}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(4838400, hamon::reduce(hamon::begin(a), hamon::end(a), 2, hamon::multiplies<>{}));
	}
	{
		HAMON_CXX11_CONSTEXPR int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 2, 5, 8};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(      57, hamon::reduce(hamon::begin(a), hamon::end(a)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(      67, hamon::reduce(hamon::begin(a), hamon::end(a), 10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(19353600, hamon::reduce(hamon::begin(a), hamon::end(a), 1, hamon::multiplies<>{}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(38707200, hamon::reduce(hamon::begin(a), hamon::end(a), 2, hamon::multiplies<>{}));
	}
	{
		HAMON_CXX11_CONSTEXPR int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 2, 5, 8, 4};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(      61, hamon::reduce(hamon::begin(a), hamon::end(a)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(      71, hamon::reduce(hamon::begin(a), hamon::end(a), 10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(77414400, hamon::reduce(hamon::begin(a), hamon::end(a), 1, hamon::multiplies<>{}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(       0, hamon::reduce(hamon::begin(a), hamon::end(a), 0, hamon::multiplies<>{}));
	}
	{
		HAMON_CXX11_CONSTEXPR int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 2, 5, 8, 4, 0};
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(61, hamon::reduce(hamon::begin(a), hamon::end(a)));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ(71, hamon::reduce(hamon::begin(a), hamon::end(a), 10));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::reduce(hamon::begin(a), hamon::end(a), 1, hamon::multiplies<>{}));
		HAMON_CXX11_CONSTEXPR_EXPECT_EQ( 0, hamon::reduce(hamon::begin(a), hamon::end(a), 2, hamon::multiplies<>{}));
	}
	{
		int a[5] = {1, 2, 3, 4, 5};
		int res = hamon::reduce(hamon::begin(a), hamon::end(a));
		EXPECT_TRUE(res == 15);
	}
	{
		int a[5] = {1, 2, 3, 4, 5};
		test_container<int, input_iterator_wrapper<int>> con(a);
		int res = hamon::reduce(con.begin(), con.end());
		EXPECT_TRUE(res == 15);
	}
	{
		HAMON_CXX11_CONSTEXPR bool b[] = {true, false, true, true, false, true, false, true, true, false};
		HAMON_CXX11_CONSTEXPR int res = hamon::reduce(hamon::begin(b), hamon::end(b), 100);
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(res == 106);
	}
	{
		bool b[] = {true, false, true, true, false, true, false, true, true, false};
		int res = hamon::reduce(hamon::begin(b), hamon::end(b), 100);
		EXPECT_TRUE(res == 106);
	}
	{
		HAMON_CXX11_CONSTEXPR int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

		HAMON_CXX11_CONSTEXPR auto res = hamon::reduce(hamon::begin(a), hamon::end(a), (short)11);
		static_assert(hamon::is_same<decltype(res), short const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(res == 66);

		HAMON_CXX11_CONSTEXPR auto res2 = hamon::reduce(hamon::begin(a), hamon::end(a), -1l, hamon::multiplies<>{});
		static_assert(hamon::is_same<decltype(res2), long const>::value, "");
		HAMON_CXX11_CONSTEXPR_EXPECT_TRUE(res2 == -3628800);
	}
}

}	// namespace reduce_test

}	// namespace hamon_numeric_test

HAMON_WARNING_POP()
