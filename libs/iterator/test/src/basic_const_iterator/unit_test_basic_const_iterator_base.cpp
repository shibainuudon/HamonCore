/**
 *	@file	unit_test_basic_const_iterator_base.cpp
 *
 *	@brief	baseのテスト
 * 
 *	constexpr const Iterator& base() const & noexcept;
 *	constexpr Iterator base() &&;
 */

#include <hamon/iterator/basic_const_iterator.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test
{

namespace basic_const_iterator_test
{

namespace base_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test01()
{
	using Iter = input_iterator_wrapper<int>;
	int a[3] = {1, 2, 3};
	Iter it{a};
	hamon::basic_const_iterator<Iter> ci{it};
	VERIFY(ci.base() == it);
	VERIFY(hamon::move(ci).base() == it);
	return true;
}

#undef VERIFY

GTEST_TEST(BasicConstIteratorTest, BaseTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace base_test

}	// namespace basic_const_iterator_test

}	// namespace hamon_iterator_test
