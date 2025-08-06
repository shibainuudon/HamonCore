/**
 *	@file	unit_test_hive_assign_initializer_list.cpp
 *
 *	@brief	assign のテスト
 *
 *	void assign(initializer_list<T>);
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

namespace assign_initializer_list_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().assign(hamon::declval<std::initializer_list<T>>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Hive>().assign(hamon::declval<std::initializer_list<T>>())), "");

	Hive v;

	{
		v.assign({10,20,30});
		VERIFY(v.size() == 3u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{60});
	}
	{
		v.assign({5,4,3,2,1});
		VERIFY(v.size() == 5u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{15});
	}
	{
		v.assign({42});
		VERIFY(v.size() == 1u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{42});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, AssignInitializerListTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace assign_initializer_list_test

}	// namespace hamon_hive_test
