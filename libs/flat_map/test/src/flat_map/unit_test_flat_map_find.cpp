/**
 *	@file	unit_test_flat_map_find.cpp
 *
 *	@brief	find のテスト
 *
 *	constexpr iterator find(const key_type& x);
 *	constexpr const_iterator find(const key_type& x) const;
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

namespace find_test
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
		using Map = hamon::flat_map<Key, T, hamon::less<Key>, KeyContainer, MappedContainer>;

		static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().find(hamon::declval<Key const&>())), typename Map::const_iterator>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Map&>().find(hamon::declval<Key const&>())), typename Map::iterator>::value, "");
		static_assert(!noexcept(hamon::declval<Map const&>().find(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Map&>().find(hamon::declval<Key const&>())), "");

		Map v
		{
			{Key{3}, T{10}},
			{Key{6}, T{20}},
			{Key{1}, T{30}},
			{Key{4}, T{40}},
		};

		VERIFY(v.find(Key{0}) == v.end());
		VERIFY(v.find(Key{1}) == (v.begin() + 0));
		VERIFY(v.find(Key{2}) == v.end());
		VERIFY(v.find(Key{3}) == (v.begin() + 1));
		VERIFY(v.find(Key{4}) == (v.begin() + 2));
		VERIFY(v.find(Key{5}) == v.end());
		VERIFY(v.find(Key{6}) == (v.begin() + 3));
		VERIFY(v.find(Key{7}) == v.end());

		auto const& cv = v;
		VERIFY(cv.find(Key{0}) == cv.end());
		VERIFY(cv.find(Key{1}) == (cv.begin() + 0));
		VERIFY(cv.find(Key{2}) == cv.end());
		VERIFY(cv.find(Key{3}) == (cv.begin() + 1));
		VERIFY(cv.find(Key{4}) == (cv.begin() + 2));
		VERIFY(cv.find(Key{5}) == cv.end());
		VERIFY(cv.find(Key{6}) == (cv.begin() + 3));
		VERIFY(cv.find(Key{7}) == cv.end());
	}
	{
		using Map = hamon::flat_map<Key, T, hamon::greater<Key>, KeyContainer, MappedContainer>;

		static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().find(hamon::declval<Key const&>())), typename Map::const_iterator>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Map&>().find(hamon::declval<Key const&>())), typename Map::iterator>::value, "");
		static_assert(!noexcept(hamon::declval<Map const&>().find(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Map&>().find(hamon::declval<Key const&>())), "");

		Map v
		{
			{Key{3}, T{10}},
			{Key{6}, T{20}},
			{Key{1}, T{30}},
			{Key{4}, T{40}},
		};

		VERIFY(v.find(Key{0}) == v.end());
		VERIFY(v.find(Key{1}) == (v.begin() + 3));
		VERIFY(v.find(Key{2}) == v.end());
		VERIFY(v.find(Key{3}) == (v.begin() + 2));
		VERIFY(v.find(Key{4}) == (v.begin() + 1));
		VERIFY(v.find(Key{5}) == v.end());
		VERIFY(v.find(Key{6}) == (v.begin() + 0));
		VERIFY(v.find(Key{7}) == v.end());

		auto const& cv = v;
		VERIFY(cv.find(Key{0}) == cv.end());
		VERIFY(cv.find(Key{1}) == (cv.begin() + 3));
		VERIFY(cv.find(Key{2}) == cv.end());
		VERIFY(cv.find(Key{3}) == (cv.begin() + 2));
		VERIFY(cv.find(Key{4}) == (cv.begin() + 1));
		VERIFY(cv.find(Key{5}) == cv.end());
		VERIFY(cv.find(Key{6}) == (cv.begin() + 0));
		VERIFY(cv.find(Key{7}) == cv.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMapTest, FindTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>>()));

	{
		hamon::flat_map<hamon::string, int> fm =
		{
			{"Alice", 3},
			{"Bob",   1},
			{"Carol", 4},
		};

		auto it1 = fm.find("Bob");
		EXPECT_TRUE(it1 != fm.end());
		EXPECT_TRUE(it1->second == 1);

		auto it2 = fm.find("Eve");
		EXPECT_TRUE(it2 == fm.end());
	}
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace find_test

}	// namespace hamon_flat_map_test
