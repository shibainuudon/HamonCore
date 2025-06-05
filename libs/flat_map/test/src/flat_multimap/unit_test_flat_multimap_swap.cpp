/**
 *	@file	unit_test_flat_multimap_swap.cpp
 *
 *	@brief	swap のテスト
 *
 *	constexpr void swap(flat_multimap&) noexcept;
 *	constexpr friend void swap(flat_multimap& x, flat_multimap& y) noexcept;
 */

#include <hamon/flat_map/flat_multimap.hpp>
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
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
{

namespace swap_test
{

#if !defined(HAMON_USE_STD_FLAT_MAP)
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer, typename Compare>
FLAT_MAP_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map = hamon::flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().swap(hamon::declval<Map&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(swap(hamon::declval<Map&>(), hamon::declval<Map&>())), void>::value, "");
	static_assert(noexcept(hamon::declval<Map&>().swap(hamon::declval<Map&>())), "");
	static_assert(noexcept(swap(hamon::declval<Map&>(), hamon::declval<Map&>())), "");

	Map v1
	{
		{Key{2}, T{10}},
		{Key{3}, T{20}},
		{Key{3}, T{30}},
	};

	Map v2
	{
		{Key{1}, T{40}},
		{Key{2}, T{50}},
		{Key{1}, T{60}},
		{Key{3}, T{70}},
	};

	v1.swap(v2);

	VERIFY(check_invariant(v1));
	VERIFY(v1.size() == 4);
	VERIFY(v1.count(Key{1}) == 2);
	VERIFY(v1.count(Key{2}) == 1);
	VERIFY(v1.count(Key{3}) == 1);
	VERIFY(check_invariant(v2));
	VERIFY(v2.size() == 3);
	VERIFY(v2.count(Key{1}) == 0);
	VERIFY(v2.count(Key{2}) == 1);
	VERIFY(v2.count(Key{3}) == 2);

	swap(v1, v2);

	VERIFY(check_invariant(v1));
	VERIFY(v1.size() == 3);
	VERIFY(v1.count(Key{1}) == 0);
	VERIFY(v1.count(Key{2}) == 1);
	VERIFY(v1.count(Key{3}) == 2);
	VERIFY(check_invariant(v2));
	VERIFY(v2.size() == 4);
	VERIFY(v2.count(Key{1}) == 2);
	VERIFY(v2.count(Key{2}) == 1);
	VERIFY(v2.count(Key{3}) == 1);

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultimapTest, SwapTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<int>>()));
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace swap_test

}	// namespace hamon_flat_multimap_test
