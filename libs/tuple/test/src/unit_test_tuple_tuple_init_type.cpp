/**
 *	@file	unit_test_tuple_tuple_init_type.cpp
 *
 *	@brief	tuple_init_type のテスト
 */

#include <hamon/tuple/tuple_init_type.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include "my_tuple.hpp"

namespace hamon_tuple_test
{

namespace tuple_init_type_test
{

template <template <typename...> class Tuple>
void TupleInitTypeTest()
{
	{
		using t1 = Tuple<int, float, double, long>;
		using t2 = hamon::tuple_init_type_t<t1>;
		using t3 = hamon::tuple_init_type_t<t2 const>;
		using t4 = hamon::tuple_init_type_t<t3 volatile>;
		using t5 = hamon::tuple_init_type_t<t4 const volatile>;
		using t6 = hamon::tuple_init_type_t<t5>;

		static_assert(hamon::is_same<t1, Tuple<int, float, double, long>>::value, "");
		static_assert(hamon::is_same<t2, Tuple<int, float, double      >>::value, "");
		static_assert(hamon::is_same<t3, Tuple<int, float              >>::value, "");
		static_assert(hamon::is_same<t4, Tuple<int                     >>::value, "");
		static_assert(hamon::is_same<t5, Tuple<                        >>::value, "");
		static_assert(hamon::is_same<t6, Tuple<                        >>::value, "");
	}
	{
		using t1 = Tuple<int, int, int>;
		using t2 = hamon::tuple_init_type_t<t1>;
		using t3 = hamon::tuple_init_type_t<t2>;
		using t4 = hamon::tuple_init_type_t<t3>;
		using t5 = hamon::tuple_init_type_t<t4>;

		static_assert(hamon::is_same<t1, Tuple<int, int, int>>::value, "");
		static_assert(hamon::is_same<t2, Tuple<int, int     >>::value, "");
		static_assert(hamon::is_same<t3, Tuple<int          >>::value, "");
		static_assert(hamon::is_same<t4, Tuple<             >>::value, "");
		static_assert(hamon::is_same<t5, Tuple<             >>::value, "");
	}
	{
		using t1 = Tuple<>;
		using t2 = hamon::tuple_init_type_t<t1>;
		using t3 = hamon::tuple_init_type_t<t2>;

		static_assert(hamon::is_same<t1, Tuple<>>::value, "");
		static_assert(hamon::is_same<t2, Tuple<>>::value, "");
		static_assert(hamon::is_same<t3, Tuple<>>::value, "");
	}
}

GTEST_TEST(TupleTest, TupleInitTypeTest)
{
	TupleInitTypeTest<std::tuple>();
	TupleInitTypeTest<MyTuple>();
}

}	// namespace tuple_init_type_test

}	// namespace hamon_tuple_test
