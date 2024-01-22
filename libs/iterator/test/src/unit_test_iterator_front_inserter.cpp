/**
 *	@file	unit_test_iterator_front_inserter.cpp
 *
 *	@brief	front_inserter のテスト
 */

#include <hamon/iterator/front_inserter.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/list.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_iterator_test {
namespace front_inserter_test {

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Container>
HAMON_CXX14_CONSTEXPR bool test()
{
	Container c;
	auto it = hamon::front_inserter(c);
	static_assert(hamon::is_same<decltype(it), hamon::front_insert_iterator<Container>>::value, "");
	VERIFY(0 == c.size());
	it = 42;
	VERIFY(1 == c.size());
	VERIFY(42 == c.front());
	return true;
}

#undef VERIFY

GTEST_TEST(IteratorTest, FrontInserterTest)
{
	EXPECT_TRUE(test<hamon::list<long>>());
}

}	// namespace front_inserter_test
}	// namespace hamon_iterator_test
