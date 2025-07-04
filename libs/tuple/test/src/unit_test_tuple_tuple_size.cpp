/**
 *	@file	unit_test_tuple_tuple_size.cpp
 *
 *	@brief	tuple_size のテスト
 *
 *	template<class T> struct tuple_size;
 */

#include <hamon/tuple/tuple_size.hpp>
#include <hamon/tuple/tuple.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include "my_tuple.hpp"

namespace hamon_tuple_test
{

namespace tuple_size_test
{

template <template <typename...> class Tuple>
void TupleSizeTest()
{
	static_assert(hamon::tuple_size<Tuple<>      >::value == 0, "");
	static_assert(hamon::tuple_size<Tuple<> const>::value == 0, "");

	static_assert(hamon::tuple_size<Tuple<int>      >::value == 1, "");
	static_assert(hamon::tuple_size<Tuple<int> const>::value == 1, "");

	static_assert(hamon::tuple_size<Tuple<void>      >::value == 1, "");
	static_assert(hamon::tuple_size<Tuple<void> const>::value == 1, "");

	static_assert(hamon::tuple_size<Tuple<float, int&>      >::value == 2, "");
	static_assert(hamon::tuple_size<Tuple<float, int&> const>::value == 2, "");

	static_assert(hamon::tuple_size<Tuple<const float, int&, void>      >::value == 3, "");
	static_assert(hamon::tuple_size<Tuple<const float, int&, void> const>::value == 3, "");

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)
	static_assert(hamon::tuple_size_v<Tuple<>      > == 0, "");
	static_assert(hamon::tuple_size_v<Tuple<> const> == 0, "");

	static_assert(hamon::tuple_size_v<Tuple<int>      > == 1, "");
	static_assert(hamon::tuple_size_v<Tuple<int> const> == 1, "");

	static_assert(hamon::tuple_size_v<Tuple<void>      > == 1, "");
	static_assert(hamon::tuple_size_v<Tuple<void> const> == 1, "");

	static_assert(hamon::tuple_size_v<Tuple<float, int&>      > == 2, "");
	static_assert(hamon::tuple_size_v<Tuple<float, int&> const> == 2, "");

	static_assert(hamon::tuple_size_v<Tuple<const float, int&, void>      > == 3, "");
	static_assert(hamon::tuple_size_v<Tuple<const float, int&, void> const> == 3, "");
#endif
}

GTEST_TEST(TupleTest, TupleSizeTest)
{
	TupleSizeTest<std::tuple>();
	TupleSizeTest<hamon::tuple>();
	TupleSizeTest<MyTuple>();
}

}	// namespace tuple_size_test

}	// namespace hamon_tuple_test

