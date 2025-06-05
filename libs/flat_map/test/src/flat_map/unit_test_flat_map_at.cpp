/**
 *	@file	unit_test_flat_map_at.cpp
 *
 *	@brief	at のテスト
 *
 *	constexpr mapped_type& at(const key_type& x);
 *	constexpr const mapped_type& at(const key_type& x) const;
 */

#include <hamon/flat_map/flat_map.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_map_test_helper.hpp"

namespace hamon_flat_map_test
{

namespace at_test
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
	using Map = hamon::flat_map<Key, T, Compare, KeyContainer, MappedContainer>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().at(hamon::declval<Key const&>())), T&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().at(hamon::declval<Key const&>())), T const&>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().at(hamon::declval<Key const&>())), "");
	static_assert(!noexcept(hamon::declval<Map const&>().at(hamon::declval<Key const&>())), "");

	{
		Map v
		{
			{Key{2}, T{10}},
			{Key{1}, T{20}},
			{Key{3}, T{30}},
		};

		VERIFY(check_invariant(v));
		VERIFY(v.at(Key{1}) == T{20});
		VERIFY(v.at(Key{2}) == T{10});
		VERIFY(v.at(Key{3}) == T{30});

		v.at(Key{2}) = T{40};

		VERIFY(check_invariant(v));
		VERIFY(v.at(Key{1}) == T{20});
		VERIFY(v.at(Key{2}) == T{40});
		VERIFY(v.at(Key{3}) == T{30});
	}
	{
		Map const v
		{
			{Key{3}, T{10}},
			{Key{1}, T{20}},
			{Key{4}, T{30}},
		};

		VERIFY(check_invariant(v));
		VERIFY(v.at(Key{1}) == T{20});
		VERIFY(v.at(Key{3}) == T{10});
		VERIFY(v.at(Key{4}) == T{30});
	}

	return true;
}

#undef VERIFY

void exceptions_test()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	{
		hamon::flat_map<int, float> v
		{
			{ 1, 0.5f },
			{ 7, 1.5f },
			{ 3, 2.5f },
		};

		EXPECT_TRUE(check_invariant(v));
		EXPECT_THROW   ((void)v.at(0), hamon::out_of_range);
		EXPECT_NO_THROW((void)v.at(1));
		EXPECT_THROW   ((void)v.at(2), hamon::out_of_range);
		EXPECT_NO_THROW((void)v.at(3));
		EXPECT_TRUE(check_invariant(v));

		v[0] = 3.5f;

		EXPECT_TRUE(check_invariant(v));
		EXPECT_NO_THROW((void)v.at(0));
		EXPECT_NO_THROW((void)v.at(1));
		EXPECT_THROW   ((void)v.at(2), hamon::out_of_range);
		EXPECT_NO_THROW((void)v.at(3));
		EXPECT_TRUE(check_invariant(v));
	}
	{
		hamon::flat_map<int, float> const v
		{
			{ 2, 0.5f },
			{ 0, 1.5f },
			{ 3, 2.5f },
		};

		EXPECT_TRUE(check_invariant(v));
		EXPECT_NO_THROW((void)v.at(0));
		EXPECT_THROW   ((void)v.at(1), hamon::out_of_range);
		EXPECT_NO_THROW((void)v.at(2));
		EXPECT_NO_THROW((void)v.at(3));
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatMapTest, AtTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::greater<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::less<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<int>>()));

	exceptions_test();
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace at_test

}	// namespace hamon_flat_map_test
