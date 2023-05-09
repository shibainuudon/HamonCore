/**
 *	@file	unit_test_pair_assign_pair_like_copy_const.cpp
 *
 *	@brief	pair-likeなオブジェクトからのコピー代入(プロキシ参照版)のテスト
 * 
 *	template<pair-like P>
 *	constexpr const pair& operator=(P&& p) const;
 */

#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace assign_pair_like_copy_const_test
{

GTEST_TEST(PairTest, AssignPairLikeCopyConstTest)
{
	// TODO
}

}	// namespace assign_pair_like_copy_const_test

}	// namespace hamon_pair_test
