/**
 *	@file	unit_test_flat_map_contains.cpp
 *
 *	@brief	contains のテスト
 *
 *	constexpr bool contains(const key_type& x) const;
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
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_map_test_helper.hpp"

namespace hamon_flat_map_test
{

namespace contains_test
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
	using Map = hamon::flat_map<Key, T, hamon::less<Key>, KeyContainer, MappedContainer>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().contains(hamon::declval<Key const&>())), bool>::value, "");
	static_assert(!noexcept(hamon::declval<Map const&>().contains(hamon::declval<Key const&>())), "");

	Map const v
	{
		{Key{3}, T{10}},
		{Key{1}, T{20}},
		{Key{4}, T{30}},
		{Key{1}, T{40}},
		{Key{4}, T{50}},
		{Key{4}, T{60}},
	};
	VERIFY(!v.contains(Key{0}));
	VERIFY( v.contains(Key{1}));
	VERIFY(!v.contains(Key{2}));
	VERIFY( v.contains(Key{3}));
	VERIFY( v.contains(Key{4}));
	VERIFY(!v.contains(Key{5}));

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMapTest, ContainsTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<int>>()));

	{
		hamon::flat_map<hamon::string, int> fm =
		{
			{"Alice", 3},
			{"Bob",   1},
			{"Carol", 4},
			{"Alice", 2},
		};

		EXPECT_TRUE (fm.contains("Alice"));
		EXPECT_TRUE (fm.contains("Bob"));
		EXPECT_FALSE(fm.contains("Eve"));
	}
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace contains_test

}	// namespace hamon_flat_map_test
