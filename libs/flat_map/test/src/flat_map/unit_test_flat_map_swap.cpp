/**
 *	@file	unit_test_flat_map_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	constexpr void swap(flat_map& y) noexcept;
 *	constexpr friend void swap(flat_map& x, flat_map& y) noexcept;
 */

#include <hamon/flat_map/flat_map.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_map_test_helper.hpp"

namespace hamon_flat_map_test
{

namespace swap_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer, typename Compare>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map = hamon::flat_map<Key, T, Compare, KeyContainer, MappedContainer>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().swap(hamon::declval<Map&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(swap(hamon::declval<Map&>(), hamon::declval<Map&>())), void>::value, "");
	static_assert(noexcept(hamon::declval<Map&>().swap(hamon::declval<Map&>())), "");
	static_assert(noexcept(swap(hamon::declval<Map&>(), hamon::declval<Map&>())), "");

	Map v1
	{
		{Key{2}, T{10}},
		{Key{3}, T{20}},
		{Key{1}, T{30}},
	};

	Map v2
	{
		{Key{1}, T{40}},
		{Key{2}, T{50}},
		{Key{5}, T{60}},
		{Key{4}, T{70}},
	};

	v1.swap(v2);

	VERIFY(check_invariant(v1));
	VERIFY(v1.size() == 4);
	VERIFY(v1[Key{1}] == T{40});
	VERIFY(v1[Key{2}] == T{50});
	VERIFY(v1[Key{4}] == T{70});
	VERIFY(v1[Key{5}] == T{60});
	VERIFY(check_invariant(v2));
	VERIFY(v2.size() == 3);
	VERIFY(v2[Key{1}] == T{30});
	VERIFY(v2[Key{2}] == T{10});
	VERIFY(v2[Key{3}] == T{20});

	swap(v1, v2);

	VERIFY(check_invariant(v1));
	VERIFY(v1.size() == 3);
	VERIFY(v1[Key{1}] == T{30});
	VERIFY(v1[Key{2}] == T{10});
	VERIFY(v1[Key{3}] == T{20});
	VERIFY(check_invariant(v2));
	VERIFY(v2.size() == 4);
	VERIFY(v2[Key{1}] == T{40});
	VERIFY(v2[Key{2}] == T{50});
	VERIFY(v2[Key{4}] == T{70});
	VERIFY(v2[Key{5}] == T{60});

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMapTest, SwapTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<>>()));
}

}	// namespace swap_test

}	// namespace hamon_flat_map_test
