/**
 *	@file	unit_test_flat_multimap_equal_range.cpp
 *
 *	@brief	equal_range のテスト
 *
 *	constexpr pair<iterator, iterator> equal_range(const key_type& x);
 *	constexpr pair<const_iterator, const_iterator> equal_range(const key_type& x) const;
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
#include "constexpr_test.hpp"
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
{

namespace equal_range_test
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
		using Iterator = typename Map::iterator;
		using ConstIterator = typename Map::const_iterator;

#if defined(HAMON_USE_STD_FLAT_MAP)
		using Result = std::pair<Iterator, Iterator>;
		using ConstResult = std::pair<ConstIterator, ConstIterator>;
#else
		using Result = hamon::pair<Iterator, Iterator>;
		using ConstResult = hamon::pair<ConstIterator, ConstIterator>;
#endif
		static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().equal_range(hamon::declval<Key const&>())), ConstResult>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Map&>().equal_range(hamon::declval<Key const&>())), Result>::value, "");
		static_assert(!noexcept(hamon::declval<Map const&>().equal_range(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Map&>().equal_range(hamon::declval<Key const&>())), "");

		Map v
		{
			{Key{2}, T{10}},
			{Key{1}, T{20}},
			{Key{2}, T{30}},
			{Key{4}, T{40}},
		};

		VERIFY(v.equal_range(Key{0}) == Result{v.begin() + 0, v.begin() + 0});
		VERIFY(v.equal_range(Key{1}) == Result{v.begin() + 0, v.begin() + 1});
		VERIFY(v.equal_range(Key{2}) == Result{v.begin() + 1, v.begin() + 3});
		VERIFY(v.equal_range(Key{3}) == Result{v.begin() + 3, v.begin() + 3});
		VERIFY(v.equal_range(Key{4}) == Result{v.begin() + 3, v.end()});
		VERIFY(v.equal_range(Key{5}) == Result{v.end(), v.end()});

		auto const& cv = v;
		VERIFY(cv.equal_range(Key{0}) == ConstResult{cv.begin() + 0, cv.begin() + 0});
		VERIFY(cv.equal_range(Key{1}) == ConstResult{cv.begin() + 0, cv.begin() + 1});
		VERIFY(cv.equal_range(Key{2}) == ConstResult{cv.begin() + 1, cv.begin() + 3});
		VERIFY(cv.equal_range(Key{3}) == ConstResult{cv.begin() + 3, cv.begin() + 3});
		VERIFY(cv.equal_range(Key{4}) == ConstResult{cv.begin() + 3, cv.end()});
		VERIFY(cv.equal_range(Key{5}) == ConstResult{cv.end(), cv.end()});
	}
	{
		using Map = hamon::flat_multimap<Key, T, hamon::greater<Key>, KeyContainer, MappedContainer>;
		using Iterator = typename Map::iterator;
		using ConstIterator = typename Map::const_iterator;

#if defined(HAMON_USE_STD_FLAT_MAP)
		using Result = std::pair<Iterator, Iterator>;
		using ConstResult = std::pair<ConstIterator, ConstIterator>;
#else
		using Result = hamon::pair<Iterator, Iterator>;
		using ConstResult = hamon::pair<ConstIterator, ConstIterator>;
#endif
		static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().equal_range(hamon::declval<Key const&>())), ConstResult>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Map&>().equal_range(hamon::declval<Key const&>())), Result>::value, "");
		static_assert(!noexcept(hamon::declval<Map const&>().equal_range(hamon::declval<Key const&>())), "");
		static_assert(!noexcept(hamon::declval<Map&>().equal_range(hamon::declval<Key const&>())), "");

		Map v
		{
			{Key{2}, T{10}},
			{Key{4}, T{20}},
			{Key{1}, T{30}},
			{Key{4}, T{40}},
			{Key{1}, T{50}},
		};

		VERIFY(v.equal_range(Key{0}) == Result{v.end(), v.end()});
		VERIFY(v.equal_range(Key{1}) == Result{v.begin() + 3, v.end()});
		VERIFY(v.equal_range(Key{2}) == Result{v.begin() + 2, v.begin() + 3});
		VERIFY(v.equal_range(Key{3}) == Result{v.begin() + 2, v.begin() + 2});
		VERIFY(v.equal_range(Key{4}) == Result{v.begin() + 0, v.begin() + 2});
		VERIFY(v.equal_range(Key{5}) == Result{v.begin() + 0, v.begin() + 0});

		auto const& cv = v;
		VERIFY(cv.equal_range(Key{0}) == ConstResult{cv.end(), cv.end()});
		VERIFY(cv.equal_range(Key{1}) == ConstResult{cv.begin() + 3, cv.end()});
		VERIFY(cv.equal_range(Key{2}) == ConstResult{cv.begin() + 2, cv.begin() + 3});
		VERIFY(cv.equal_range(Key{3}) == ConstResult{cv.begin() + 2, cv.begin() + 2});
		VERIFY(cv.equal_range(Key{4}) == ConstResult{cv.begin() + 0, cv.begin() + 2});
		VERIFY(cv.equal_range(Key{5}) == ConstResult{cv.begin() + 0, cv.begin() + 0});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultimapTest, EqualRangeTest)
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
			{"B", 4},
			{"C", 5},
		};

		auto ret = fm.equal_range("B");
		auto it = ret.first;
		EXPECT_TRUE(it->first == "B");
		EXPECT_TRUE(it->second == 1);
		++it;
		EXPECT_TRUE(it->first == "B");
		EXPECT_TRUE(it->second == 4);
		++it;
		EXPECT_TRUE(it == ret.second);
	}
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace equal_range_test

}	// namespace hamon_flat_multimap_test
