/**
 *	@file	unit_test_tuple_tuple_assign_tuple_like_const.cpp
 *
 *	@brief	tuple-likeなオブジェクトの代入(プロキシ参照版)のテスト
 *
 *	template<tuple-like UTuple> constexpr const tuple& operator=(UTuple&& u) const;
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/get.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace assign_tuple_like_const_test
{

GTEST_TEST(TupleTest, AssignTupleLikeConstTest)
{
	// TODO
}

}	// namespace assign_tuple_like_const_test

}	// namespace hamon_tuple_test
