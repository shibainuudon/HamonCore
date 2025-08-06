/**
 *	@file	unit_test_hive_op_assign_initializer_list.cpp
 *
 *	@brief	operator= のテスト
 *
 *	hive& operator=(initializer_list<T>);
 */

#include <hamon/hive.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/numeric/accumulate.hpp>
#include <hamon/type_traits/is_assignable.hpp>
#include <hamon/type_traits/is_nothrow_assignable.hpp>
#include <hamon/type_traits/is_trivially_assignable.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include <initializer_list>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace op_assign_initializer_list_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;

	static_assert( hamon::is_assignable          <Hive, std::initializer_list<T>>::value, "");
	static_assert(!hamon::is_nothrow_assignable  <Hive, std::initializer_list<T>>::value, "");
	static_assert(!hamon::is_trivially_assignable<Hive, std::initializer_list<T>>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Hive&>() = hamon::declval<std::initializer_list<T>>()), Hive&>::value, "");

	Hive v1;
	VERIFY(v1.empty());

	{
		auto& r = (v1 = {1,2,3});
		VERIFY(&r == &v1);
		VERIFY(v1.size() == 3u);
		VERIFY(hamon::accumulate(v1.begin(), v1.end(), T{}, hamon::plus<T>{}) == T{6});
	}
	{
		auto& r = (v1 = {});
		VERIFY(&r == &v1);
		VERIFY(v1.size() == 0u);
		VERIFY(hamon::accumulate(v1.begin(), v1.end(), T{}, hamon::plus<T>{}) == T{0});
	}
	{
		auto& r = (v1 = {5,4,3,2,1});
		VERIFY(&r == &v1);
		VERIFY(v1.size() == 5u);
		VERIFY(hamon::accumulate(v1.begin(), v1.end(), T{}, hamon::plus<T>{}) == T{15});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, OpAssignInitializerListTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace op_assign_initializer_list_test

}	// namespace hamon_hive_test
