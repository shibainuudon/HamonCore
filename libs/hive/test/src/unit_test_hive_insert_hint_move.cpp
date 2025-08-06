/**
 *	@file	unit_test_hive_insert_hint_move.cpp
 *
 *	@brief	insert のテスト
 *
 *	iterator insert(const_iterator hint, T&& x);
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

namespace insert_hint_move_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Hive = hamon::hive<T>;
	using iterator       = typename Hive::iterator;
	using const_iterator = typename Hive::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Hive>().insert(hamon::declval<const_iterator>(), hamon::declval<T&&>())), iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Hive>().insert(hamon::declval<const_iterator>(), hamon::declval<T&&>())), "");

	Hive v;
	VERIFY(v.empty());
	VERIFY(v.size() == 0u);
	{
		T t{10};
		auto ret = v.insert(v.cend(), hamon::move(t));
		VERIFY(ret == v.begin());
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{10});
	}
	VERIFY(v.size() == 1u);
	{
		auto ret = v.insert(v.cbegin(), T{20});
		VERIFY(*ret == T{20});
		VERIFY(hamon::accumulate(v.begin(), v.end(), T{}, hamon::plus<T>{}) == T{30});
	}
	VERIFY(v.size() == 2u);

	return true;
}

#undef VERIFY

GTEST_TEST(HiveTest, InsertHintMoveTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<int>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<char>());
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE(test<float>());
}

}	// namespace insert_hint_move_test

}	// namespace hamon_hive_test
