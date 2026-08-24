/**
 *	@file	unit_test_flat_set_dtor.cpp
 *
 *	@brief	デストラクタのテスト
 */

#include <hamon/flat_set/flat_set.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/is_nothrow_destructible.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_set_test_helper.hpp"

namespace hamon_flat_set_test
{

namespace dtor_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename Compare>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using Set = hamon::flat_set<Key, Compare, KeyContainer>;

	static_assert(hamon::is_nothrow_destructible<Set>::value, "");

	return true;
}

#undef VERIFY

GTEST_TEST(FlatSetTest, DtorTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::less<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::greater<double>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<char>, hamon::less<>>()));
}

}	// namespace dtor_test

}	// namespace hamon_flat_set_test
