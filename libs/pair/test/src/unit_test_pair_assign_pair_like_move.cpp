/**
 *	@file	unit_test_pair_assign_pair_like_move.cpp
 *
 *	@brief	pair-likeなオブジェクトからのムーブ代入のテスト
 * 
 *	template<pair-like P>
 *	constexpr pair& operator=(P&& p);
 */

#include <hamon/pair.hpp>
#include <hamon/type_traits.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace assign_pair_like_move_test
{

GTEST_TEST(PairTest, AssignPairLikeMoveTest)
{
	// TODO
}

}	// namespace assign_pair_like_move_test

}	// namespace hamon_pair_test
