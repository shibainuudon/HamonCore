/**
 *	@file	unit_test_iterator_back_inserter.cpp
 *
 *	@brief	back_inserter のテスト
 */

#include <hamon/iterator/back_inserter.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/vector.hpp>
#include <hamon/list.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_iterator_test {
namespace back_inserter_test {

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Container>
HAMON_CXX14_CONSTEXPR bool test()
{
	Container c;
	auto it = hamon::back_inserter(c);
	static_assert(hamon::is_same<decltype(it), hamon::back_insert_iterator<Container>>::value, "");
	VERIFY(0 == c.size());
	it = 42;
	VERIFY(1 == c.size());
	VERIFY(42 == c.front());
	return true;
}

#undef VERIFY

GTEST_TEST(IteratorTest, BackInserterTest)
{
	EXPECT_TRUE(test<hamon::vector<int>>());
	EXPECT_TRUE(test<hamon::list<long>>());
}

}	// namespace back_inserter_test
}	// namespace hamon_iterator_test
