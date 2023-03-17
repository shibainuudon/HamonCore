/**
 *	@file	unit_test_tuple_tuple_element.cpp
 *
 *	@brief	tuple_element のテスト
 */

#include <hamon/tuple/tuple_element.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include "my_tuple.hpp"

namespace hamon_tuple_test
{

namespace tuple_element_test
{

template <template <typename...> class Tuple>
void TupleElementTest()
{
	static_assert(hamon::is_same<hamon::tuple_element_t<0, Tuple<int>      >, int      >::value, "");
	static_assert(hamon::is_same<hamon::tuple_element_t<0, Tuple<int> const>, int const>::value, "");

	static_assert(hamon::is_same<hamon::tuple_element_t<0, Tuple<float, int>      >, float      >::value, "");
	static_assert(hamon::is_same<hamon::tuple_element_t<0, Tuple<float, int> const>, float const>::value, "");

	static_assert(hamon::is_same<hamon::tuple_element_t<1, Tuple<float, int>      >, int      >::value, "");
	static_assert(hamon::is_same<hamon::tuple_element_t<1, Tuple<float, int> const>, int const>::value, "");

	static_assert(hamon::is_same<hamon::tuple_element_t<0, Tuple<char, void*, long>>, char>::value, "");
	static_assert(hamon::is_same<hamon::tuple_element_t<1, Tuple<char, void*, long>>, void*>::value, "");
	static_assert(hamon::is_same<hamon::tuple_element_t<2, Tuple<char, void*, long>>, long>::value, "");
}

GTEST_TEST(TupleTest, TupleElementTest)
{
	TupleElementTest<std::tuple>();
	TupleElementTest<MyTuple>();
}

}	// namespace tuple_element_test

}	// namespace hamon_tuple_test
