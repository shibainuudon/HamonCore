/**
 *	@file	unit_test_tuple_tuple_cat.cpp
 *
 *	@brief	tuple_cat のテスト
 *
 *	template<tuple-like... Tuples>
 *	constexpr tuple<CTypes...> tuple_cat(Tuples&&... tpls);
 */

#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace tuple_cat_test
{

GTEST_TEST(TupleTest, TupleCatTest)
{
	// TODO
}

}	// namespace tuple_cat_test

}	// namespace hamon_tuple_test
