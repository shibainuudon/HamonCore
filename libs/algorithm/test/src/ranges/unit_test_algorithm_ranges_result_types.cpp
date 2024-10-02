/**
 *	@file	unit_test_algorithm_ranges_result_types.cpp
 *
 *	@brief	27.5 Algorithm result types のテスト
 */

#include <hamon/algorithm/ranges/in_fun_result.hpp>
#include <hamon/algorithm/ranges/in_in_result.hpp>
#include <hamon/algorithm/ranges/in_out_result.hpp>
#include <hamon/algorithm/ranges/in_in_out_result.hpp>
#include <hamon/algorithm/ranges/in_out_out_result.hpp>
#include <hamon/algorithm/ranges/min_max_result.hpp>
#include <hamon/algorithm/ranges/in_found_result.hpp>
#include <hamon/algorithm/ranges/in_value_result.hpp>
#include <hamon/algorithm/ranges/out_value_result.hpp>
#include <hamon/type_traits/is_convertible.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_algorithm_test
{

namespace ranges_result_types_test
{

GTEST_TEST(AlgorithmTest, RangesResultTypesTest)
{
	{
		using hamon::ranges::in_fun_result;
		static_assert( hamon::is_convertible<in_fun_result<int, float> const, in_fun_result<int, float>>::value, "");
		static_assert(!hamon::is_convertible<in_fun_result<int, float> const, in_fun_result<int*, float>>::value, "");
		static_assert(!hamon::is_convertible<in_fun_result<int, float> const, in_fun_result<int, float*>>::value, "");
		static_assert( hamon::is_convertible<in_fun_result<int, float> const, in_fun_result<long, double>>::value, "");

		static_assert( hamon::is_convertible<in_fun_result<int, float>, in_fun_result<int, float>>::value, "");
		static_assert(!hamon::is_convertible<in_fun_result<int, float>, in_fun_result<int*, float>>::value, "");
		static_assert(!hamon::is_convertible<in_fun_result<int, float>, in_fun_result<int, float*>>::value, "");
		static_assert( hamon::is_convertible<in_fun_result<int, float>, in_fun_result<char, double>>::value, "");

		HAMON_CXX14_CONSTEXPR in_fun_result<int, float> r{10, 20};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r.in);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, r.fun);

		HAMON_CXX14_CONSTEXPR in_fun_result<long, double> r2 = r;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r2.in);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, r2.fun);

		HAMON_CXX14_CONSTEXPR in_fun_result<long, double> r3 = hamon::move(r);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r3.in);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, r3.fun);
	}
	{
		using hamon::ranges::in_in_result;
		static_assert( hamon::is_convertible<in_in_result<int, float> const, in_in_result<int, float>>::value, "");
		static_assert(!hamon::is_convertible<in_in_result<int, float> const, in_in_result<int*, float>>::value, "");
		static_assert(!hamon::is_convertible<in_in_result<int, float> const, in_in_result<int, float*>>::value, "");
		static_assert( hamon::is_convertible<in_in_result<int, float> const, in_in_result<long, double>>::value, "");

		static_assert( hamon::is_convertible<in_in_result<int, float>, in_in_result<int, float>>::value, "");
		static_assert(!hamon::is_convertible<in_in_result<int, float>, in_in_result<int*, float>>::value, "");
		static_assert(!hamon::is_convertible<in_in_result<int, float>, in_in_result<int, float*>>::value, "");
		static_assert( hamon::is_convertible<in_in_result<int, float>, in_in_result<char, double>>::value, "");

		HAMON_CXX14_CONSTEXPR in_in_result<int, float> r{10, 20};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r.in1);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, r.in2);

		HAMON_CXX14_CONSTEXPR in_in_result<long, double> r2 = r;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r2.in1);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, r2.in2);

		HAMON_CXX14_CONSTEXPR in_in_result<long, double> r3 = hamon::move(r);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r3.in1);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, r3.in2);
	}
	{
		using hamon::ranges::in_out_result;
		static_assert( hamon::is_convertible<in_out_result<int, float> const, in_out_result<int, float>>::value, "");
		static_assert(!hamon::is_convertible<in_out_result<int, float> const, in_out_result<int*, float>>::value, "");
		static_assert(!hamon::is_convertible<in_out_result<int, float> const, in_out_result<int, float*>>::value, "");
		static_assert( hamon::is_convertible<in_out_result<int, float> const, in_out_result<long, double>>::value, "");

		static_assert( hamon::is_convertible<in_out_result<int, float>, in_out_result<int, float>>::value, "");
		static_assert(!hamon::is_convertible<in_out_result<int, float>, in_out_result<int*, float>>::value, "");
		static_assert(!hamon::is_convertible<in_out_result<int, float>, in_out_result<int, float*>>::value, "");
		static_assert( hamon::is_convertible<in_out_result<int, float>, in_out_result<char, double>>::value, "");

		HAMON_CXX14_CONSTEXPR in_out_result<int, float> r{10, 20};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r.in);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, r.out);

		HAMON_CXX14_CONSTEXPR in_out_result<long, double> r2 = r;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r2.in);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, r2.out);

		HAMON_CXX14_CONSTEXPR in_out_result<long, double> r3 = hamon::move(r);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r3.in);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, r3.out);
	}
	{
		using hamon::ranges::in_in_out_result;
		static_assert( hamon::is_convertible<in_in_out_result<int, float, long> const, in_in_out_result<int, float, long>>::value, "");
		static_assert(!hamon::is_convertible<in_in_out_result<int, float, long> const, in_in_out_result<int*, float, long>>::value, "");
		static_assert(!hamon::is_convertible<in_in_out_result<int, float, long> const, in_in_out_result<int, float*, long>>::value, "");
		static_assert(!hamon::is_convertible<in_in_out_result<int, float, long> const, in_in_out_result<int, float, long*>>::value, "");
		static_assert( hamon::is_convertible<in_in_out_result<int, float, long> const, in_in_out_result<long, double, long>>::value, "");

		static_assert( hamon::is_convertible<in_in_out_result<int, float, long>, in_in_out_result<int, float, long>>::value, "");
		static_assert(!hamon::is_convertible<in_in_out_result<int, float, long>, in_in_out_result<int*, float, long>>::value, "");
		static_assert(!hamon::is_convertible<in_in_out_result<int, float, long>, in_in_out_result<int, float*, long>>::value, "");
		static_assert(!hamon::is_convertible<in_in_out_result<int, float, long>, in_in_out_result<int, float, long*>>::value, "");
		static_assert( hamon::is_convertible<in_in_out_result<int, float, long>, in_in_out_result<long, double, long>>::value, "");

		HAMON_CXX14_CONSTEXPR in_in_out_result<int, float, long> r{10, 20, 30};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r.in1);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, r.in2);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(30, r.out);

		HAMON_CXX14_CONSTEXPR in_in_out_result<long, double, long> r2 = r;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r2.in1);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, r2.in2);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(30, r2.out);

		HAMON_CXX14_CONSTEXPR in_in_out_result<long, double, long> r3 = hamon::move(r);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r3.in1);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, r3.in2);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(30, r3.out);
	}
	{
		using hamon::ranges::in_out_out_result;
		static_assert( hamon::is_convertible<in_out_out_result<int, float, long> const, in_out_out_result<int, float, long>>::value, "");
		static_assert(!hamon::is_convertible<in_out_out_result<int, float, long> const, in_out_out_result<int*, float, long>>::value, "");
		static_assert(!hamon::is_convertible<in_out_out_result<int, float, long> const, in_out_out_result<int, float*, long>>::value, "");
		static_assert(!hamon::is_convertible<in_out_out_result<int, float, long> const, in_out_out_result<int, float, long*>>::value, "");
		static_assert( hamon::is_convertible<in_out_out_result<int, float, long> const, in_out_out_result<long, double, long>>::value, "");

		static_assert( hamon::is_convertible<in_out_out_result<int, float, long>, in_out_out_result<int, float, long>>::value, "");
		static_assert(!hamon::is_convertible<in_out_out_result<int, float, long>, in_out_out_result<int*, float, long>>::value, "");
		static_assert(!hamon::is_convertible<in_out_out_result<int, float, long>, in_out_out_result<int, float*, long>>::value, "");
		static_assert(!hamon::is_convertible<in_out_out_result<int, float, long>, in_out_out_result<int, float, long*>>::value, "");
		static_assert( hamon::is_convertible<in_out_out_result<int, float, long>, in_out_out_result<long, double, long>>::value, "");

		HAMON_CXX14_CONSTEXPR in_out_out_result<int, float, long> r{10, 20, 30};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r.in);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, r.out1);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(30, r.out2);

		HAMON_CXX14_CONSTEXPR in_out_out_result<long, double, long> r2 = r;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r2.in);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, r2.out1);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(30, r2.out2);

		HAMON_CXX14_CONSTEXPR in_out_out_result<long, double, long> r3 = hamon::move(r);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r3.in);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, r3.out1);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(30, r3.out2);
	}
	{
		using hamon::ranges::min_max_result;
		static_assert( hamon::is_convertible<min_max_result<int> const, min_max_result<int>>::value, "");
		static_assert(!hamon::is_convertible<min_max_result<int> const, min_max_result<int*>>::value, "");
		static_assert( hamon::is_convertible<min_max_result<int> const, min_max_result<long>>::value, "");

		static_assert( hamon::is_convertible<min_max_result<int>, min_max_result<int>>::value, "");
		static_assert(!hamon::is_convertible<min_max_result<int>, min_max_result<int*>>::value, "");
		static_assert( hamon::is_convertible<min_max_result<int>, min_max_result<char>>::value, "");

		HAMON_CXX14_CONSTEXPR min_max_result<int> r{10, 20};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r.min);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, r.max);

		HAMON_CXX14_CONSTEXPR min_max_result<long> r2 = r;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r2.min);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, r2.max);

		HAMON_CXX14_CONSTEXPR min_max_result<long> r3 = hamon::move(r);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r3.min);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, r3.max);
	}
	{
		using hamon::ranges::in_found_result;
		static_assert( hamon::is_convertible<in_found_result<int> const, in_found_result<int>>::value, "");
		static_assert(!hamon::is_convertible<in_found_result<int> const, in_found_result<int*>>::value, "");
		static_assert( hamon::is_convertible<in_found_result<int> const, in_found_result<long>>::value, "");

		static_assert( hamon::is_convertible<in_found_result<int>, in_found_result<int>>::value, "");
		static_assert(!hamon::is_convertible<in_found_result<int>, in_found_result<int*>>::value, "");
		static_assert( hamon::is_convertible<in_found_result<int>, in_found_result<char>>::value, "");

		HAMON_CXX14_CONSTEXPR in_found_result<int> r{10, true};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r.in);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(true, r.found);

		HAMON_CXX14_CONSTEXPR in_found_result<long> r2 = r;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r2.in);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(true, r2.found);

		HAMON_CXX14_CONSTEXPR in_found_result<long> r3 = hamon::move(r);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r3.in);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(true, r3.found);
	}
	{
		using hamon::ranges::in_value_result;
		static_assert( hamon::is_convertible<in_value_result<int, float> const, in_value_result<int, float>>::value, "");
		static_assert(!hamon::is_convertible<in_value_result<int, float> const, in_value_result<int*, float>>::value, "");
		static_assert(!hamon::is_convertible<in_value_result<int, float> const, in_value_result<int, float*>>::value, "");
		static_assert( hamon::is_convertible<in_value_result<int, float> const, in_value_result<long, double>>::value, "");

		static_assert( hamon::is_convertible<in_value_result<int, float>, in_value_result<int, float>>::value, "");
		static_assert(!hamon::is_convertible<in_value_result<int, float>, in_value_result<int*, float>>::value, "");
		static_assert(!hamon::is_convertible<in_value_result<int, float>, in_value_result<int, float*>>::value, "");
		static_assert( hamon::is_convertible<in_value_result<int, float>, in_value_result<char, double>>::value, "");

		HAMON_CXX14_CONSTEXPR in_value_result<int, float> r{10, 20};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r.in);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, r.value);

		HAMON_CXX14_CONSTEXPR in_value_result<long, double> r2 = r;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r2.in);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, r2.value);

		HAMON_CXX14_CONSTEXPR in_value_result<long, double> r3 = hamon::move(r);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r3.in);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, r3.value);
	}
	{
		using hamon::ranges::out_value_result;
		static_assert( hamon::is_convertible<out_value_result<int, float> const, out_value_result<int, float>>::value, "");
		static_assert(!hamon::is_convertible<out_value_result<int, float> const, out_value_result<int*, float>>::value, "");
		static_assert(!hamon::is_convertible<out_value_result<int, float> const, out_value_result<int, float*>>::value, "");
		static_assert( hamon::is_convertible<out_value_result<int, float> const, out_value_result<long, double>>::value, "");

		static_assert( hamon::is_convertible<out_value_result<int, float>, out_value_result<int, float>>::value, "");
		static_assert(!hamon::is_convertible<out_value_result<int, float>, out_value_result<int*, float>>::value, "");
		static_assert(!hamon::is_convertible<out_value_result<int, float>, out_value_result<int, float*>>::value, "");
		static_assert( hamon::is_convertible<out_value_result<int, float>, out_value_result<char, double>>::value, "");

		HAMON_CXX14_CONSTEXPR out_value_result<int, float> r{10, 20};
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r.out);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, r.value);

		HAMON_CXX14_CONSTEXPR out_value_result<long, double> r2 = r;
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r2.out);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, r2.value);

		HAMON_CXX14_CONSTEXPR out_value_result<long, double> r3 = hamon::move(r);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(10, r3.out);
		HAMON_CXX14_CONSTEXPR_EXPECT_EQ(20, r3.value);
	}
}

}	// namespace ranges_result_types_test

}	// namespace hamon_algorithm_test
