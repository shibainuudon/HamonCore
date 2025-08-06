/**
 *	@file	unit_test_hive_insert_initializer_list.cpp
 *
 *	@brief	insert のテスト
 *
 *	void insert(initializer_list<T> il);
 */

#include <hamon/hive.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/numeric/accumulate.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include <initializer_list>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace insert_initializer_list_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().insert(hamon::declval<std::initializer_list<T>>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Hive>().insert(hamon::declval<std::initializer_list<T>>())), "");

	Hive v;
	VERIFY(v.empty());
	VERIFY(v.size() == 0u);
	{
		v.insert({T{1}, T{2}});
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{3});
	}
	VERIFY(v.size() == 2u);
	{
		v.insert({T{3}, T{4}, T{5}});
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{15});
	}
	VERIFY(v.size() == 5u);

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, InsertInitializerListTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace insert_initializer_list_test

}	// namespace hamon_hive_test
