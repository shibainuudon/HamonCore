/**
 *	@file	unit_test_tuple_tuple_assign_tuple_like.cpp
 *
 *	@brief	tuple-likeなオブジェクトの代入のテスト
 *
 *	template<tuple-like UTuple> constexpr tuple& operator=(UTuple&& u);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/get.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace assign_tuple_like_test
{

GTEST_TEST(TupleTest, AssignTupleLikeTest)
{
	// TODO
}

}	// namespace assign_tuple_like_test

}	// namespace hamon_tuple_test
