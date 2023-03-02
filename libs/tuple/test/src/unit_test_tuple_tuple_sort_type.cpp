/**
 *	@file	unit_test_tuple_tuple_sort_type.cpp
 *
 *	@brief	tuple_sort_type のテスト
 */

#include <hamon/tuple/tuple_sort_type.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/integral_constant.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include <tuple>
#include "my_tuple.hpp"

namespace hamon_tuple_test
{

namespace tupe_sort_type_test
{

struct value_greater
{
	template <typename T1, typename T2>
	using type = hamon::bool_constant<(T1::value > T2::value)>;
};

struct size_greater
{
	template <typename T1, typename T2>
	using type = hamon::bool_constant<(sizeof(T1) > sizeof(T2))>;
};

template <template <typename...> class Tuple>
void TupleSortTypeTest()
{
	{
		using t = Tuple<
			hamon::integral_constant<int, 3>,
			hamon::integral_constant<int, 1>,
			hamon::integral_constant<int, 4>,
			hamon::integral_constant<int, 1>,
			hamon::integral_constant<int, 5>,
			hamon::integral_constant<int, 9>,
			hamon::integral_constant<int, 2>,
			hamon::integral_constant<int, 6>,
			hamon::integral_constant<int, 5>,
			hamon::integral_constant<int, 3>,
			hamon::integral_constant<int, 5>
		>;

		using t2 = hamon::tuple_sort_type_t<t>;

		using expected = Tuple<
			hamon::integral_constant<int, 1>,
			hamon::integral_constant<int, 1>,
			hamon::integral_constant<int, 2>,
			hamon::integral_constant<int, 3>,
			hamon::integral_constant<int, 3>,
			hamon::integral_constant<int, 4>,
			hamon::integral_constant<int, 5>,
			hamon::integral_constant<int, 5>,
			hamon::integral_constant<int, 5>,
			hamon::integral_constant<int, 6>,
			hamon::integral_constant<int, 9>
		>;

		static_assert(std::is_same<t2, expected>::value, "");
	}
	{
		using t = Tuple<
			hamon::integral_constant<int, 3>,
			hamon::integral_constant<int, 1>,
			hamon::integral_constant<int, 4>,
			hamon::integral_constant<int, 1>,
			hamon::integral_constant<int, 5>,
			hamon::integral_constant<int, 9>,
			hamon::integral_constant<int, 2>,
			hamon::integral_constant<int, 6>,
			hamon::integral_constant<int, 5>,
			hamon::integral_constant<int, 3>,
			hamon::integral_constant<int, 5>
		>;

		using t2 = hamon::tuple_sort_type_t<t const, value_greater>;

		using expected = Tuple<
			hamon::integral_constant<int, 9>,
			hamon::integral_constant<int, 6>,
			hamon::integral_constant<int, 5>,
			hamon::integral_constant<int, 5>,
			hamon::integral_constant<int, 5>,
			hamon::integral_constant<int, 4>,
			hamon::integral_constant<int, 3>,
			hamon::integral_constant<int, 3>,
			hamon::integral_constant<int, 2>,
			hamon::integral_constant<int, 1>,
			hamon::integral_constant<int, 1>
		>;

		static_assert(std::is_same<t2, expected>::value, "");
	}
	{
		using t = Tuple<
			hamon::integral_constant<int, 1>,
			hamon::integral_constant<int, 1>
		>;

		using t2 = hamon::tuple_sort_type_t<t volatile>;

		using expected = Tuple<
			hamon::integral_constant<int, 1>,
			hamon::integral_constant<int, 1>
		>;

		static_assert(std::is_same<t2, expected>::value, "");
	}
	{
		using t = Tuple<
			hamon::integral_constant<int, 3>
		>;

		using t2 = hamon::tuple_sort_type_t<t const volatile>;

		using expected = Tuple<
			hamon::integral_constant<int, 3>
		>;

		static_assert(std::is_same<t2, expected>::value, "");
	}
	{
		using t = Tuple<>;

		using t2 = hamon::tuple_sort_type_t<t>;

		using expected = Tuple<>;

		static_assert(std::is_same<t2, expected>::value, "");
	}
	{
		using t = Tuple<
			char[1],
			char[3],
			char[2],
			char[4],
			char[5]
		>;

		using t2 = hamon::tuple_sort_type_t<t, size_greater>;

		using expected = Tuple<
			char[5],
			char[4],
			char[3],
			char[2],
			char[1]
		>;

		static_assert(std::is_same<t2, expected>::value, "");
	}
}

GTEST_TEST(TupleTest, TupleSortTypeTest)
{
	TupleSortTypeTest<std::tuple>();
	TupleSortTypeTest<MyTuple>();
}

}	// namespace tupe_sort_type_test

}	// namespace hamon_tuple_test
