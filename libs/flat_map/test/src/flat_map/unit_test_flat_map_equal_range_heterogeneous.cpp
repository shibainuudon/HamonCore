/**
 *	@file	unit_test_flat_map_equal_range_heterogeneous.cpp
 *
 *	@brief	equal_range のテスト
 *
 *	template<class K>
 *	constexpr pair<iterator, iterator> equal_range(const K& x);
 *
 *	template<class K>
 *	constexpr pair<const_iterator, const_iterator> equal_range(const K& x) const;
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

namespace equal_range_heterogeneous_test
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
struct is_equal_range_invocable
	: public hamon::false_type {};

template <typename Map, typename K>
struct is_equal_range_invocable<Map, K, hamon::void_t<decltype(hamon::declval<Map>().equal_range(hamon::declval<K>()))>>
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

	static_assert( is_equal_range_invocable<Map1&, int>::value, "");
	static_assert(!is_equal_range_invocable<Map2&, int>::value, "");
	static_assert( is_equal_range_invocable<Map3&, int>::value, "");
	static_assert(!is_equal_range_invocable<Map4&, int>::value, "");

	static_assert( is_equal_range_invocable<Map1 const&, int>::value, "");
	static_assert(!is_equal_range_invocable<Map2 const&, int>::value, "");
	static_assert( is_equal_range_invocable<Map3 const&, int>::value, "");
	static_assert(!is_equal_range_invocable<Map4 const&, int>::value, "");

	{
		using Map = Map1;
		using Iterator = typename Map::iterator;
		using ConstIterator = typename Map::const_iterator;

#if defined(HAMON_USE_STD_FLAT_MAP)
		using Result = std::pair<Iterator, Iterator>;
		using ConstResult = std::pair<ConstIterator, ConstIterator>;
#else
		using Result = hamon::pair<Iterator, Iterator>;
		using ConstResult = hamon::pair<ConstIterator, ConstIterator>;
#endif
		static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().equal_range(hamon::declval<int const&>())), ConstResult>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Map&>().equal_range(hamon::declval<int const&>())), Result>::value, "");
		static_assert(!noexcept(hamon::declval<Map const&>().equal_range(hamon::declval<int const&>())), "");
		static_assert(!noexcept(hamon::declval<Map&>().equal_range(hamon::declval<int const&>())), "");

		Map v
		{
			{Key{1}, T{10}},
			{Key{2}, T{20}},
			{Key{1}, T{30}},
			{Key{4}, T{40}},
			{Key{1}, T{50}},
		};

		VERIFY(v.equal_range(0) == Result{v.begin() + 0, v.begin() + 0});
		VERIFY(v.equal_range(1) == Result{v.begin() + 0, v.begin() + 1});
		VERIFY(v.equal_range(2) == Result{v.begin() + 1, v.begin() + 2});
		VERIFY(v.equal_range(3) == Result{v.begin() + 2, v.begin() + 2});
		VERIFY(v.equal_range(4) == Result{v.begin() + 2, v.end()});
		VERIFY(v.equal_range(5) == Result{v.end(), v.end()});

		auto const& cv = v;
		VERIFY(cv.equal_range(0) == ConstResult{cv.begin() + 0, cv.begin() + 0});
		VERIFY(cv.equal_range(1) == ConstResult{cv.begin() + 0, cv.begin() + 1});
		VERIFY(cv.equal_range(2) == ConstResult{cv.begin() + 1, cv.begin() + 2});
		VERIFY(cv.equal_range(3) == ConstResult{cv.begin() + 2, cv.begin() + 2});
		VERIFY(cv.equal_range(4) == ConstResult{cv.begin() + 2, cv.end()});
		VERIFY(cv.equal_range(5) == ConstResult{cv.end(), cv.end()});
	}
	{
		using Map = Map3;
		using Iterator = typename Map::iterator;
		using ConstIterator = typename Map::const_iterator;

#if defined(HAMON_USE_STD_FLAT_MAP)
		using Result = std::pair<Iterator, Iterator>;
		using ConstResult = std::pair<ConstIterator, ConstIterator>;
#else
		using Result = hamon::pair<Iterator, Iterator>;
		using ConstResult = hamon::pair<ConstIterator, ConstIterator>;
#endif
		static_assert(hamon::is_same<decltype(hamon::declval<Map const&>().equal_range(hamon::declval<int const&>())), ConstResult>::value, "");
		static_assert(hamon::is_same<decltype(hamon::declval<Map&>().equal_range(hamon::declval<int const&>())), Result>::value, "");
		static_assert(!noexcept(hamon::declval<Map const&>().equal_range(hamon::declval<int const&>())), "");
		static_assert(!noexcept(hamon::declval<Map&>().equal_range(hamon::declval<int const&>())), "");

		Map v
		{
			{Key{2}, T{10}},
			{Key{2}, T{20}},
			{Key{1}, T{30}},
			{Key{2}, T{40}},
			{Key{4}, T{50}},
		};

		VERIFY(v.equal_range(0) == Result{v.end(), v.end()});
		VERIFY(v.equal_range(1) == Result{v.begin() + 2, v.end()});
		VERIFY(v.equal_range(2) == Result{v.begin() + 1, v.begin() + 2});
		VERIFY(v.equal_range(3) == Result{v.begin() + 1, v.begin() + 1});
		VERIFY(v.equal_range(4) == Result{v.begin() + 0, v.begin() + 1});
		VERIFY(v.equal_range(5) == Result{v.begin() + 0, v.begin() + 0});

		auto const& cv = v;
		VERIFY(cv.equal_range(0) == ConstResult{cv.end(), cv.end()});
		VERIFY(cv.equal_range(1) == ConstResult{cv.begin() + 2, cv.end()});
		VERIFY(cv.equal_range(2) == ConstResult{cv.begin() + 1, cv.begin() + 2});
		VERIFY(cv.equal_range(3) == ConstResult{cv.begin() + 1, cv.begin() + 1});
		VERIFY(cv.equal_range(4) == ConstResult{cv.begin() + 0, cv.begin() + 1});
		VERIFY(cv.equal_range(5) == ConstResult{cv.begin() + 0, cv.begin() + 0});
	}

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMapTest, EqualRangeHeterogeneousTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<TransparentKey>, hamon::vector<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<TransparentKey>, hamon::deque<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<TransparentKey>, hamon::vector<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<TransparentKey>, hamon::deque<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<TransparentKey>, MinSequenceContainer<long>>()));

	{
		hamon::flat_map<hamon::string, int, hamon::less<>> fm =
		{
			{"A", 3},
			{"B", 1},
			{"C", 4},
			{"D", 5},
		};

		auto ret = fm.equal_range((const char*)"B");
		auto it = ret.first;
		EXPECT_TRUE(it->first == "B");
		EXPECT_TRUE(it->second == 1);
		++it;
		EXPECT_TRUE(it == ret.second);
	}
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace equal_range_heterogeneous_test

}	// namespace hamon_flat_map_test
