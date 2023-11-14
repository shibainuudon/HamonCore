/**
 *	@file	unit_test_basic_const_iterator_increment.cpp
 *
 *	@brief	インクリメントのテスト
 * 
 *	constexpr basic_const_iterator& operator++();
 *	constexpr void operator++(int);
 *	constexpr basic_const_iterator operator++(int) requires forward_iterator<Iterator>;
 */

#include <hamon/iterator/basic_const_iterator.hpp>
#include <hamon/iterator/concepts.hpp>
#include <hamon/config.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "iterator_test.hpp"

namespace hamon_iterator_test
{

namespace basic_const_iterator_test
{

namespace increment_test
{

static_assert( hamon::weakly_incrementable_t<hamon::basic_const_iterator<input_iterator_wrapper<int>>>::value, "");
static_assert( hamon::weakly_incrementable_t<hamon::basic_const_iterator<forward_iterator_wrapper<int>>>::value, "");
static_assert( hamon::weakly_incrementable_t<hamon::basic_const_iterator<bidirectional_iterator_wrapper<int>>>::value, "");
static_assert( hamon::weakly_incrementable_t<hamon::basic_const_iterator<random_access_iterator_wrapper<int>>>::value, "");
static_assert( hamon::weakly_incrementable_t<hamon::basic_const_iterator<contiguous_iterator_wrapper<int>>>::value, "");
static_assert(!hamon::incrementable_t<hamon::basic_const_iterator<input_iterator_wrapper<int>>>::value, "");
static_assert( hamon::incrementable_t<hamon::basic_const_iterator<forward_iterator_wrapper<int>>>::value, "");
static_assert( hamon::incrementable_t<hamon::basic_const_iterator<bidirectional_iterator_wrapper<int>>>::value, "");
static_assert( hamon::incrementable_t<hamon::basic_const_iterator<random_access_iterator_wrapper<int>>>::value, "");
static_assert( hamon::incrementable_t<hamon::basic_const_iterator<contiguous_iterator_wrapper<int>>>::value, "");

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

HAMON_CXX14_CONSTEXPR bool test01()
{
	using Iter = forward_iterator_wrapper<int>;
	int a[3] = {3, 1, 4};
	hamon::basic_const_iterator<Iter> ci{Iter{a}};

	VERIFY(3 == *ci);

	auto t1 = ++ci;

	VERIFY(1 == *ci);
	VERIFY(1 == *t1);

	auto t2 = ci++;

	VERIFY(4 == *ci);
	VERIFY(1 == *t2);

	return true;
}

HAMON_CXX14_CONSTEXPR bool test02()
{
	using Iter = input_iterator_wrapper<int>;
	int a[3] = {3, 1, 4};
	hamon::basic_const_iterator<Iter> ci{Iter{a}};

	VERIFY(3 == *ci);

	auto t1 = ++ci;

	VERIFY(1 == *ci);
	VERIFY(1 == *t1);

	ci++;

	VERIFY(4 == *ci);

	return true;
}

#undef VERIFY

GTEST_TEST(BasicConstIteratorTest, IncrementTest)
{
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test01());
	HAMON_CXX14_CONSTEXPR_EXPECT_TRUE(test02());
}

}	// namespace increment_test

}	// namespace basic_const_iterator_test

}	// namespace hamon_iterator_test
