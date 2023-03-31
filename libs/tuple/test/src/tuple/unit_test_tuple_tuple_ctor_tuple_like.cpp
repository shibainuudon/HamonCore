/**
 *	@file	unit_test_tuple_tuple_ctor_tuple_like.cpp
 *
 *	@brief	tuple-likeなオブジェクトからのコンストラクタのテスト
 *
 *	template<tuple-like UTuple> constexpr explicit(see below) tuple(UTuple&& u);
 */

#include <hamon/tuple/tuple.hpp>
#include <hamon/tuple/get.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace ctor_tuple_like_test
{

GTEST_TEST(TupleTest, CtorTupleLikeTest)
{
	// TODO
}

}	// namespace ctor_tuple_like_test

}	// namespace hamon_tuple_test
