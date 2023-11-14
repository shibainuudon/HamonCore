/**
 *	@file	unit_test_basic_const_iterator_dereference.cpp
 *
 *	@brief	operator* のテスト
 * 
 *	constexpr reference operator*() const;
 */

#include <hamon/iterator/basic_const_iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test
{

namespace basic_const_iterator_test
{

namespace dereference_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test01()
{
	using Iter = input_iterator_wrapper<int>;
	int a[3] = {1, 2, 3};
	hamon::basic_const_iterator<Iter> ci{Iter{a}};
	VERIFY(*ci == 1);

	static_assert(hamon::is_same<decltype(*ci), int const&>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(BasicConstIteratorTest, DereferenceTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
}

}	// namespace dereference_test

}	// namespace basic_const_iterator_test

}	// namespace hamon_iterator_test
