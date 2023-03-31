/**
 *	@file	unit_test_tuple_tuple_rel_op_tuple_like.cpp
 *
 *	@brief	比較演算子のテスト
 *
 *	template<class... TTypes, tuple-like UTuple>
 *	constexpr bool operator==(const tuple<TTypes...>& t, const UTuple& u);
 *
 *	template<class... TTypes, tuple-like UTuple>
 *	constexpr common_comparison_category_t<synth-three-way-result<TTypes, Elems>...>
 *	operator<=>(const tuple<TTypes...>& t, const UTuple& u);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/get.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace rel_op_tuple_like_test
{

GTEST_TEST(TupleTest, RelOpTupleLikeTest)
{
	// TODO
}

}	// namespace rel_op_tuple_like_test

}	// namespace hamon_tuple_test
