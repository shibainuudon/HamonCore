/**
 *	@file	unit_test_unexpected_op_assign_move.cpp
 *
 *	@brief	ムーブ代入演算子のテスト
 *
 *	constexpr unexpected& operator=(unexpected&&) = default;
 */

#include <hamon/expected/unexpected.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unexpected_test
{

namespace op_assign_move_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	hamon::unexpected<E> dst{E{5}};
	hamon::unexpected<E> src{E{10}};
	dst = hamon::move(src);
	VERIFY(dst.error() == E{10});
	return true;
}

#undef VERIFY

GTEST_TEST(UnexpectedTest, OpAssignMoveTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace op_assign_move_test

}	// namespace hamon_unexpected_test
