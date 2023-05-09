/**
 *	@file	unit_test_pair_assign_pair_like_copy.cpp
 *
 *	@brief	pair-likeなオブジェクトからのコピー代入のテスト
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

namespace assign_pair_like_copy_test
{

GTEST_TEST(PairTest, AssignPairLikeCopyTest)
{
	// TODO
}

}	// namespace assign_pair_like_copy_test

}	// namespace hamon_pair_test
