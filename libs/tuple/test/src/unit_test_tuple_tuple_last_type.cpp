/**
 *	@file	unit_test_tuple_tuple_last_type.cpp
 *
 *	@brief	tuple_last_type のテスト
 */

#include <hamon/tuple/tuple_last_type.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include "my_tuple.hpp"

namespace hamon_tuple_test
{

namespace tuple_last_type_test
{

template <template <typename...> class Tuple>
void TupleLastTypeTest()
{
	static_assert(hamon::is_same<long,   hamon::tuple_last_type_t<Tuple<int, float, double, long>>>::value, "");
	static_assert(hamon::is_same<int,    hamon::tuple_last_type_t<Tuple<int, float, double, int> const>>::value, "");
	static_assert(hamon::is_same<double, hamon::tuple_last_type_t<Tuple<int, float, double> volatile>>::value, "");
	static_assert(hamon::is_same<float,  hamon::tuple_last_type_t<Tuple<int, float, float> const volatile>>::value, "");
	static_assert(hamon::is_same<float,  hamon::tuple_last_type_t<Tuple<int, float>>>::value, "");
	static_assert(hamon::is_same<int,    hamon::tuple_last_type_t<Tuple<float, int>>>::value, "");
	static_assert(hamon::is_same<int,    hamon::tuple_last_type_t<Tuple<int>>>::value, "");
	static_assert(hamon::is_same<char,   hamon::tuple_last_type_t<Tuple<char>>>::value, "");
}

GTEST_TEST(TupleTest, TupleLastTypeTest)
{
	TupleLastTypeTest<std::tuple>();
	TupleLastTypeTest<MyTuple>();
}

}	// namespace tuple_last_type_test

}	// namespace hamon_tuple_test
