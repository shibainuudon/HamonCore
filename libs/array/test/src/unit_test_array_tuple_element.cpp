/**
 *	@file	unit_test_array_tuple_element.cpp
 *
 *	@brief	tuple_element<array> のテスト
 */

#include <hamon/array/array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/tuple/tuple_element.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <array>

namespace hamon_array_test
{

namespace tuple_element_test
{

template <template <typename, hamon::size_t> class Array>
void TupleElementTest()
{
	static_assert(hamon::is_same<hamon::tuple_element_t<0, Array<int, 1>>, int>::value, "");

	static_assert(hamon::is_same<hamon::tuple_element_t<0, Array<int, 2>>, int>::value, "");
	static_assert(hamon::is_same<hamon::tuple_element_t<1, Array<int, 2>>, int>::value, "");

	static_assert(hamon::is_same<hamon::tuple_element_t<0, Array<int, 3>>, int>::value, "");
	static_assert(hamon::is_same<hamon::tuple_element_t<1, Array<int, 3>>, int>::value, "");
	static_assert(hamon::is_same<hamon::tuple_element_t<2, Array<int, 3>>, int>::value, "");

	static_assert(hamon::is_same<hamon::tuple_element_t<0, Array<char, 1>>, char>::value, "");

	static_assert(hamon::is_same<hamon::tuple_element_t<0, Array<float, 2>>, float>::value, "");
	static_assert(hamon::is_same<hamon::tuple_element_t<1, Array<float, 2>>, float>::value, "");

	static_assert(hamon::is_same<hamon::tuple_element_t<0, Array<long, 3>>, long>::value, "");
	static_assert(hamon::is_same<hamon::tuple_element_t<1, Array<long, 3>>, long>::value, "");
	static_assert(hamon::is_same<hamon::tuple_element_t<2, Array<long, 3>>, long>::value, "");
}

GTEST_TEST(ArrayTest, TupleElementTest)
{
	TupleElementTest<hamon::array>();
	TupleElementTest<std::array>();
}

}	// namespace tuple_element_test

}	// namespace hamon_array_test
