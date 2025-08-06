/**
 *	@file	unit_test_hive_trim_capacity_n.cpp
 *
 *	@brief	trim_capacity のテスト
 *
 *	void trim_capacity(size_type n) noexcept;
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

namespace trim_capacity_n_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;
	using SizeType = typename Hive::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().trim_capacity(hamon::declval<SizeType>())), void>::value, "");
	static_assert(noexcept(hamon::declval<Hive>().trim_capacity(hamon::declval<SizeType>())), "");

	{
		Hive v;
		v.reserve(500);
		VERIFY(v.capacity() >= 500u);

		auto capacity = v.capacity();

		v.trim_capacity(30);
		VERIFY(v.capacity() <= capacity);
		VERIFY(v.capacity() >= 30u);
	}
	{
		Hive v;
		for (T i = 0; i < 100; ++i)
		{
			v.emplace(i);
		}
		hamon::erase_if(v, [](T x){return x >= 10;});

		auto first = v.begin();
		auto last = v.end();
		auto capacity = v.capacity();

		v.trim_capacity(50);

		VERIFY(v.capacity() <= capacity);
		VERIFY(v.capacity() >= 50u);
		VERIFY(v.size() == 10u);
		VERIFY(hamon::accumulate(first, last, T{}, hamon::plus<T>{}) == T{45});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, TrimCapacityNTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace trim_capacity_n_test

}	// namespace hamon_hive_test
