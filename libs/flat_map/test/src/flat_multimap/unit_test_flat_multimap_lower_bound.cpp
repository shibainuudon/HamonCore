/**
 *	@file	unit_test_flat_multimap_lower_bound.cpp
 *
 *	@brief	lower_bound のテスト
 *
 *	constexpr iterator lower_bound(const key_type& x);
 *	constexpr const_iterator lower_bound(const key_type& x) const;
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
#include <hamon/string.hpp>
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
{

namespace lower_bound_test
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

		static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().lower_bound(hamon::declval<Key const&>())), typename Map::const_iterator>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Map&>().lower_bound(hamon::declval<Key const&>())), typename Map::iterator>::value, "");
		static_assert(!noexcept(hamon::declval<Map const&>().lower_bound(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Map&>().lower_bound(hamon::declval<Key const&>())), "");

		Map v
		{
			{Key{3}, T{10}},
			{Key{1}, T{20}},
			{Key{2}, T{30}},
			{Key{2}, T{40}},
			{Key{3}, T{50}},
			{Key{2}, T{60}},
		};
		// 1, 2, 2, 2, 3, 3

		VERIFY(v.lower_bound(Key{0}) == (v.begin() + 0));
		VERIFY(v.lower_bound(Key{1}) == (v.begin() + 0));
		VERIFY(v.lower_bound(Key{2}) == (v.begin() + 1));
		VERIFY(v.lower_bound(Key{3}) == (v.begin() + 4));
		VERIFY(v.lower_bound(Key{4}) == v.end());

		auto const& cv = v;
		VERIFY(cv.lower_bound(Key{0}) == (cv.begin() + 0));
		VERIFY(cv.lower_bound(Key{1}) == (cv.begin() + 0));
		VERIFY(cv.lower_bound(Key{2}) == (cv.begin() + 1));
		VERIFY(cv.lower_bound(Key{3}) == (cv.begin() + 4));
		VERIFY(cv.lower_bound(Key{4}) == cv.end());
	}
	{
		using Map = hamon::flat_multimap<Key, T, hamon::greater<Key>, KeyContainer, MappedContainer>;

		static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().lower_bound(hamon::declval<Key const&>())), typename Map::const_iterator>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Map&>().lower_bound(hamon::declval<Key const&>())), typename Map::iterator>::value, "");
		static_assert(!noexcept(hamon::declval<Map const&>().lower_bound(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Map&>().lower_bound(hamon::declval<Key const&>())), "");

		Map v
		{
			{Key{3}, T{10}},
			{Key{1}, T{20}},
			{Key{4}, T{30}},
			{Key{1}, T{40}},
			{Key{5}, T{50}},
			{Key{3}, T{60}},
		};
		// 5, 4, 3, 3, 1, 1

		VERIFY(v.lower_bound(Key{0}) == v.end());
		VERIFY(v.lower_bound(Key{1}) == (v.begin() + 4));
		VERIFY(v.lower_bound(Key{2}) == (v.begin() + 4));
		VERIFY(v.lower_bound(Key{3}) == (v.begin() + 2));
		VERIFY(v.lower_bound(Key{4}) == (v.begin() + 1));
		VERIFY(v.lower_bound(Key{5}) == (v.begin() + 0));
		VERIFY(v.lower_bound(Key{6}) == (v.begin() + 0));

		auto const& cv = v;
		VERIFY(cv.lower_bound(Key{0}) == cv.end());
		VERIFY(cv.lower_bound(Key{1}) == (cv.begin() + 4));
		VERIFY(cv.lower_bound(Key{2}) == (cv.begin() + 4));
		VERIFY(cv.lower_bound(Key{3}) == (cv.begin() + 2));
		VERIFY(cv.lower_bound(Key{4}) == (cv.begin() + 1));
		VERIFY(cv.lower_bound(Key{5}) == (cv.begin() + 0));
		VERIFY(cv.lower_bound(Key{6}) == (cv.begin() + 0));
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultimapTest, LowerBoundTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>>()));

	{
		hamon::flat_multimap<hamon::string, int> fm =
		{
			{"A", 3},
			{"B", 1},
			{"C", 4},
			{"D", 5},
		};

		auto it = fm.lower_bound("B");
		auto last = fm.upper_bound("D");

		std::stringstream ss;
		for (; it != last; ++it)
		{
			ss << it->first << ":" << it->second << ", ";
		}
		EXPECT_EQ("B:1, C:4, D:5, ", ss.str());
	}
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace lower_bound_test

}	// namespace hamon_flat_multimap_test
