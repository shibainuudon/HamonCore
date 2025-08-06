/**
 *	@file	unit_test_hive_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	void swap(hive&) noexcept(see below);
 *
 *	template<class T, class Allocator>
 *	void swap(hive<T, Allocator>& x, hive<T, Allocator>& y)
 *		noexcept(noexcept(x.swap(y)));
 */

#include <hamon/hive.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/numeric/accumulate.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace swap_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive&>().swap(hamon::declval<Hive&>())), void>::value, "");
	static_assert(noexcept(hamon::declval<Hive&>().swap(hamon::declval<Hive&>())), "");

	static_assert(hamon::is_same<decltype(swap(hamon::declval<Hive&>(), hamon::declval<Hive&>())), void>::value, "");
	static_assert(noexcept(swap(hamon::declval<Hive&>(), hamon::declval<Hive&>())), "");

	{
		Hive v1{1,2,3};
		Hive v2{4,5};
		VERIFY(v1.size() == 3);
		VERIFY(v2.size() == 2);
		VERIFY(hamon::accumulate(v1.begin(), v1.end(), T{}, hamon::plus<T>{}) == T{6});
		VERIFY(hamon::accumulate(v2.begin(), v2.end(), T{}, hamon::plus<T>{}) == T{9});

		v1.swap(v2);
		VERIFY(v1.size() == 2);
		VERIFY(v2.size() == 3);
		VERIFY(hamon::accumulate(v1.begin(), v1.end(), T{}, hamon::plus<T>{}) == T{9});
		VERIFY(hamon::accumulate(v2.begin(), v2.end(), T{}, hamon::plus<T>{}) == T{6});

		swap(v1, v2);
		VERIFY(v1.size() == 3);
		VERIFY(v2.size() == 2);
		VERIFY(hamon::accumulate(v1.begin(), v1.end(), T{}, hamon::plus<T>{}) == T{6});
		VERIFY(hamon::accumulate(v2.begin(), v2.end(), T{}, hamon::plus<T>{}) == T{9});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, SwapTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace swap_test

}	// namespace hamon_hive_test
