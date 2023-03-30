/**
 *	@file	unit_test_pair_assign_pair_like.cpp
 *
 *	@brief	pair-likeなオブジェクトからの代入のテスト
 * 
 *	template<pair-like P>
 *	constexpr pair& operator=(P&& p);
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

namespace assign_pair_like_test
{

GTEST_TEST(PairTest, AssignPairLikeTest)
{
	// TODO
}

}	// namespace assign_pair_like_test

}	// namespace hamon_pair_test
