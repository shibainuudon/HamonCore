/**
 *	@file	unit_test_flat_multimap_extract.cpp
 *
 *	@brief	extract のテスト
 *
 *	constexpr containers extract() &&;
 */

#include <hamon/flat_map/flat_multimap.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
{

namespace extract_test
{

#if !defined(HAMON_USE_STD_FLAT_MAP)
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define FLAT_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename KeyContainer, typename MappedContainer>
FLAT_MAP_TEST_CONSTEXPR bool test()
{
	using Key = typename KeyContainer::value_type;
	using T = typename MappedContainer::value_type;

	{
		using Map = hamon::flat_multimap<Key, T, hamon::less<Key>, KeyContainer, MappedContainer>;
		using Containers = typename Map::containers;

		static_assert(hamon::is_same<decltype(hamon::declval<Map&&>().extract()), Containers>::value, "");
		static_assert(!noexcept(hamon::declval<Map&&>().extract()), "");

		Map v
		{
			{Key{3}, T{10}},
			{Key{1}, T{20}},
			{Key{4}, T{30}},
		};

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 3);
		VERIFY(!v.empty());

		auto c = hamon::move(v).extract();

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 0);
		VERIFY(v.empty());

		VERIFY(c.keys.size() == 3);
		VERIFY(c.values.size() == 3);

		Key const keys_expected[] = {Key{1}, Key{3}, Key{4}};
		VERIFY(hamon::ranges::equal(c.keys, keys_expected));

		T const values_expected[] = {T{20}, T{10}, T{30}};
		VERIFY(hamon::ranges::equal(c.values, values_expected));
	}
	{
		using Map = hamon::flat_multimap<Key, T, hamon::greater<Key>, KeyContainer, MappedContainer>;
		using Containers = typename Map::containers;

		static_assert(hamon::is_same<decltype(hamon::declval<Map&&>().extract()), Containers>::value, "");
		static_assert(!noexcept(hamon::declval<Map&&>().extract()), "");

		Map v
		{
			{Key{3}, T{10}},
			{Key{1}, T{20}},
			{Key{4}, T{30}},
		};

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 3);
		VERIFY(!v.empty());

		auto c = hamon::move(v).extract();

		VERIFY(check_invariant(v));
		VERIFY(v.size() == 0);
		VERIFY(v.empty());

		VERIFY(c.keys.size() == 3);
		VERIFY(c.values.size() == 3);

		Key const keys_expected[] = {Key{4}, Key{3}, Key{1}};
		VERIFY(hamon::ranges::equal(c.keys, keys_expected));

		T const values_expected[] = {T{30}, T{10}, T{20}};
		VERIFY(hamon::ranges::equal(c.values, values_expected));
	}

	return true;
}

#undef VERIFY

template <template <typename...> class TKeyContainer, template <typename...> class TValueContainer>
void test_exceptions()
{
#if !defined(HAMON_NO_EXCEPTIONS)
	using Key = int;
	using T = int;
	using Comp = hamon::less<Key>;
	{
		using KeyContainer = ThrowOnMoveContainer<Key>;
		using ValueContainer = TValueContainer<T>;
		using Map = hamon::flat_multimap<Key, T, Comp, KeyContainer, ValueContainer>;

		Map v;
		v.emplace(1, 1);
		v.emplace(2, 2);
		EXPECT_THROW(hamon::move(v).extract(), int);
		EXPECT_TRUE(check_invariant(v));
	}
	{
		using KeyContainer = TKeyContainer<Key>;
		using ValueContainer = ThrowOnMoveContainer<T>;
		using Map = hamon::flat_multimap<Key, T, Comp, KeyContainer, ValueContainer>;

		Map v;
		v.emplace(1, 1);
		v.emplace(2, 2);
		EXPECT_THROW(hamon::move(v).extract(), int);
		EXPECT_TRUE(check_invariant(v));
	}
#endif
}

GTEST_TEST(FlatMultimapTest, ExtractTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>>()));

	test_exceptions<hamon::vector, hamon::vector>();
	test_exceptions<hamon::deque, hamon::deque>();

	{
		hamon::flat_multimap<hamon::string, int> fm =
		{
			{"Alice", 3},
			{"Carol", 4},
			{"Bob",   1},
		};

		EXPECT_TRUE(fm.size() == 3);

		auto c = hamon::move(fm).extract();

		EXPECT_TRUE(fm.size() == 0);

		EXPECT_TRUE(c.keys.size() == 3);
		EXPECT_TRUE(c.keys[0] == "Alice");
		EXPECT_TRUE(c.keys[1] == "Bob");
		EXPECT_TRUE(c.keys[2] == "Carol");
		EXPECT_TRUE(c.values.size() == 3);
		EXPECT_TRUE(c.values[0] == 3);
		EXPECT_TRUE(c.values[1] == 1);
		EXPECT_TRUE(c.values[2] == 4);
	}
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace extract_test

}	// namespace hamon_flat_multimap_test
