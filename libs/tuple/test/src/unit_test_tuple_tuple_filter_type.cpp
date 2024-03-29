﻿/**
 *	@file	unit_test_tuple_tuple_filter_type.cpp
 *
 *	@brief	tuple_filter_type のテスト
 */

#include <hamon/tuple/tuple_filter_type.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_floating_point.hpp>
#include <hamon/type_traits/is_unsigned.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include "my_tuple.hpp"

namespace hamon_tuple_test
{

namespace tuple_filter_type_test
{

struct IsUnsigned
{
	template <typename T>
	using type = hamon::is_unsigned<T>;
};

struct IsFloatingPoint
{
	template <typename T>
	using type = hamon::is_floating_point<T>;
};

template <template <typename...> class Tuple>
void TupleInitTypeTest()
{
	{
		using t1 = Tuple<signed char, unsigned char, int, unsigned int, float, double>;
		using t2 = hamon::tuple_filter_type_t<t1, IsUnsigned>;
		using t3 = hamon::tuple_filter_type_t<t1, IsFloatingPoint>;

		static_assert(hamon::is_same<t2, Tuple<unsigned char, unsigned int>>::value, "");
		static_assert(hamon::is_same<t3, Tuple<float, double>>::value, "");
	}
}

GTEST_TEST(TupleTest, TupleInitTypeTest)
{
	TupleInitTypeTest<std::tuple>();
	TupleInitTypeTest<MyTuple>();
}

}	// namespace tuple_filter_type_test

}	// namespace hamon_tuple_test
