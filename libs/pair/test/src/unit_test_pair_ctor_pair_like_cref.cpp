/**
 *	@file	unit_test_pair_ctor_pair_like_cref.cpp
 *
 *	@brief	pair-likeなオブジェクトからのコンストラクタのテスト
 * 
 *  template<pair-like P>
 *	constexpr explicit(see below) pair(P&& p);
 */

#include <hamon/pair.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_pair_test
{

namespace ctor_pair_like_cref_test
{

GTEST_TEST(PairTest, CtorPairLikeCRefTest)
{
	// TODO
}

}	// namespace ctor_pair_like_cref_test

}	// namespace hamon_pair_test
