/**
 *	@file	unit_test_hive_reshape.cpp
 *
 *	@brief	reshape のテスト
 *
 *	void reshape(hive_limits block_limits);
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

namespace reshape_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().reshape(hamon::declval<hamon::hive_limits>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Hive>().reshape(hamon::declval<hamon::hive_limits>())), "");

	Hive v{hamon::hive_limits{1, 200}};
	for (T i = 0; i < 100; ++i)
	{
		v.emplace(i);
	}
	hamon::erase_if(v, [](T x){return x % 2 == 0;});

	VERIFY(v.size() == 50u);
	VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{2500});

	v.reshape(hamon::hive_limits{8, 16});

	VERIFY(v.size() == 50u);
	VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{2500});

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, ReshapeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<short>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<long>());
}

}	// namespace reshape_test

}	// namespace hamon_hive_test
