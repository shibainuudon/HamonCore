/**
 *	@file	unit_test_tuple_apply.cpp
 *
 *	@brief	apply のテスト
 *
 *	template<class F, tuple-like Tuple>
 *	constexpr decltype(auto)
 *	apply(F&& f, Tuple&& t) noexcept(see below);
 */

#include <hamon/tuple.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_tuple_test
{

namespace apply_test
{

GTEST_TEST(TupleTest, ApplyTest)
{
	// TODO
}

}	// namespace apply_test

}	// namespace hamon_tuple_test
