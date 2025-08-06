/**
 *	@file	unit_test_hive_shrink_to_fit.cpp
 *
 *	@brief	shrink_to_fit のテスト
 *
 *	void shrink_to_fit();
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

namespace shrink_to_fit_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().shrink_to_fit()), void>::value, "");
	static_assert(!noexcept(hamon::declval<Hive>().shrink_to_fit()), "");

	Hive v;
	for (T i = 0; i < 100; ++i)
	{
		v.emplace(i);
	}
	hamon::erase_if(v, [](T x){return x % 2 == 0;});

	VERIFY(v.size() == 50u);
	VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{2500});

	auto const capacity = v.capacity();

	v.shrink_to_fit();

	// [hive.capacity]/9
	// It does not increase capacity(), but may reduce capacity().
	VERIFY(v.capacity() <= capacity);

	VERIFY(v.size() == 50u);
	VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{2500});

	auto const capacity2 = v.capacity();
	v.shrink_to_fit();
	VERIFY(v.capacity() == capacity2);

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, ShrinkToFitTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<short>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<long>());
}

}	// namespace shrink_to_fit_test

}	// namespace hamon_hive_test
