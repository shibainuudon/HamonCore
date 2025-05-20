/**
 *	@file	unit_test_unexpected_op_assign_copy.cpp
 *
 *	@brief	コピー代入演算子のテスト
 *
 *	constexpr unexpected& operator=(const unexpected&) = default;
 */

#include <hamon/expected/unexpected.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unexpected_test
{

namespace op_assign_copy_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename E>
HAMON_CXX14_CONSTEXPR bool test()
{
	hamon::unexpected<E> dst{E{5}};
	hamon::unexpected<E> const src{E{10}};
	dst = src;
	VERIFY(dst.error() == E{10});
	return true;
}

#undef VERIFY

GTEST_TEST(UnexpectedTest, OpAssignCopyTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<int>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<char>()));
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

}	// namespace op_assign_copy_test

}	// namespace hamon_unexpected_test
