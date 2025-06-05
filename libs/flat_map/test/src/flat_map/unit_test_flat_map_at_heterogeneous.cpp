/**
 *	@file	unit_test_flat_map_at_heterogeneous.cpp
 *
 *	@brief	at のテスト
 *
 *	template<class K> constexpr mapped_type& at(const K& x);
 *	template<class K> constexpr const mapped_type& at(const K& x) const;
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

namespace at_heterogeneous_test
{

#if !defined(HAMON_USE_STD_FLAT_MAP)
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Map, typename K, typename = void>
struct is_at_invocable
	: public hamon::false_type {};

template <typename Map, typename K>
struct is_at_invocable<Map, K, hamon::void_t<decltype(hamon::declval<Map>().at(hamon::declval<K>()))>>
	: public hamon::true_type {};

template <typename KeyContainer, typename MappedContainer>
FLAT_MAP_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;
	using Map1 = hamon::flat_map<Key, T, hamon::less<>, KeyContainer, MappedContainer>;
	using Map2 = hamon::flat_map<Key, T, hamon::less<Key>, KeyContainer, MappedContainer>;
	using Map3 = hamon::flat_map<Key, T, hamon::greater<>, KeyContainer, MappedContainer>;
	using Map4 = hamon::flat_map<Key, T, hamon::greater<Key>, KeyContainer, MappedContainer>;

	static_assert( is_at_invocable<Map1&, int>::value, "");
	static_assert(!is_at_invocable<Map2&, int>::value, "");
	static_assert( is_at_invocable<Map3&, int>::value, "");
	static_assert(!is_at_invocable<Map4&, int>::value, "");

	static_assert( is_at_invocable<Map1 const&, int>::value, "");
	static_assert(!is_at_invocable<Map2 const&, int>::value, "");
	static_assert( is_at_invocable<Map3 const&, int>::value, "");
	static_assert(!is_at_invocable<Map4 const&, int>::value, "");

	using Map = Map1;
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().at(hamon::declval<int>())), T&>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().at(hamon::declval<int>())), T const&>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().at(hamon::declval<int>())), "");
	static_assert(!noexcept(hamon::declval<Map const&>().at(hamon::declval<int>())), "");

	{
		Map v
		{
			{Key{2}, T{10}},
			{Key{1}, T{20}},
			{Key{3}, T{30}},
		};

		VERIFY(check_invariant(v));
		VERIFY(v.at(1) == T{20});
		VERIFY(v.at(2) == T{10});
		VERIFY(v.at(3) == T{30});

		v.at(2) = T{40};

		VERIFY(check_invariant(v));
		VERIFY(v.at(1) == T{20});
		VERIFY(v.at(2) == T{40});
		VERIFY(v.at(3) == T{30});
	}
	{
		Map const v
		{
			{Key{3}, T{10}},
			{Key{1}, T{20}},
			{Key{4}, T{30}},
		};

		VERIFY(check_invariant(v));
		VERIFY(v.at(1) == T{20});
		VERIFY(v.at(3) == T{10});
		VERIFY(v.at(4) == T{30});
	}

	return true;
}

#undef VERIFY

void exceptions_test()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	using Key = TransparentKey;
	{
		hamon::flat_map<Key, float, hamon::less<>> v
		{
			{ Key{1}, 0.5f },
			{ Key{7}, 1.5f },
			{ Key{3}, 2.5f },
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
		hamon::flat_map<Key, float, hamon::less<>> const v
		{
			{ Key{2}, 0.5f },
			{ Key{0}, 1.5f },
			{ Key{3}, 2.5f },
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

GTEST_TEST(FlatMapTest, AtHeterogeneousTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<TransparentKey>, hamon::vector<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<TransparentKey>, hamon::deque<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<TransparentKey>, hamon::vector<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<TransparentKey>, hamon::deque<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<TransparentKey>, MinSequenceContainer<char>>()));

	exceptions_test();
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace at_heterogeneous_test

}	// namespace hamon_flat_map_test
