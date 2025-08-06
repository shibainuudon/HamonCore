/**
 *	@file	unit_test_hive_unique.cpp
 *
 *	@brief	unique のテスト
 *
 *	template<class BinaryPredicate = equal_to<T>>
 *	size_type unique(BinaryPredicate binary_pred = BinaryPredicate());
 */

#include <hamon/hive.hpp>
#include <hamon/functional/plus.hpp>
#include <hamon/functional/ranges/equal_to.hpp>
#include <hamon/numeric/accumulate.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_hive_test
{

namespace unique_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;
	using SizeType = typename Hive::size_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().unique()), SizeType>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().unique(hamon::ranges::equal_to{})), SizeType>::value, "");
	static_assert(!noexcept(hamon::declval<Hive>().unique()), "");
	static_assert(!noexcept(hamon::declval<Hive>().unique(hamon::ranges::equal_to{})), "");

	{
		Hive v;
		auto r = v.unique();
		VERIFY(r == 0u);
		VERIFY(v.size() == 0u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{0});
	}
	{
		Hive v{42};
		auto r = v.unique();
		VERIFY(r == 0u);
		VERIFY(v.size() == 1u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{42});
	}
	{
		Hive v{0,1,1,2,3,3,3,4,4,5};
		auto r = v.unique();
		VERIFY(r == 4u);
		VERIFY(v.size() == 6u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{15});
	}
	{
		Hive v{3,1,4,1,5,9,2,6,5,3,5};
		auto r = v.unique();
		VERIFY(r == 0u);
		VERIFY(v.size() == 11u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{44});
	}
	{
		Hive v(100u, T{13});
		auto r = v.unique();
		VERIFY(r == 99u);
		VERIFY(v.size() == 1u);
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{13});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, UniqueTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace unique_test

}	// namespace hamon_hive_test
