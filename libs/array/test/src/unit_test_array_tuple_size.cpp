/**
 *	@file	unit_test_array_tuple_size.cpp
 *
 *	@brief	tuple_size<array> のテスト
 */

#include <hamon/array/array.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <gtest/gtest.h>
#include <array>
#include <tuple>

namespace hamon_array_test
{

namespace tuple_size_test
{

template <template <typename, hamon::size_t> class Array>
void TupleSizeTest()
{
	static_assert(std::tuple_size<Array<int, 0>>::value == 0, "");
	static_assert(std::tuple_size<Array<int, 1>>::value == 1, "");
	static_assert(std::tuple_size<Array<int, 2>>::value == 2, "");
	static_assert(std::tuple_size<Array<int, 3>>::value == 3, "");

	static_assert(std::tuple_size<Array<char, 0> const>::value == 0, "");
	static_assert(std::tuple_size<Array<char, 1> const>::value == 1, "");
	static_assert(std::tuple_size<Array<char, 2> const>::value == 2, "");
	static_assert(std::tuple_size<Array<char, 3> const>::value == 3, "");

	static_assert(std::tuple_size<Array<float, 4>>::value == 4, "");
	static_assert(std::tuple_size<Array<float, 5>>::value == 5, "");
	static_assert(std::tuple_size<Array<float, 6>>::value == 6, "");
	static_assert(std::tuple_size<Array<float, 7>>::value == 7, "");
}

GTEST_TEST(ArrayTest, TupleSizeTest)
{
	TupleSizeTest<hamon::array>();
	TupleSizeTest<std::array>();
}

}	// namespace tuple_size_test

}	// namespace hamon_array_test
