/**
 *	@file	unit_test_flat_map_insert.cpp
 *
 *	@brief	insert のテスト
 *
 *	constexpr pair<iterator, bool> insert(const value_type& x);
 *	constexpr pair<iterator, bool> insert(value_type&& x);
 */

#include <hamon/flat_map/flat_map.hpp>
#include <hamon/functional/greater.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/vector.hpp>
#include <hamon/deque.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "flat_map_test_helper.hpp"

namespace hamon_flat_map_test
{

namespace insert_test
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
	using ValueType = typename Map::value_type;
	using Iterator = typename Map::iterator;
#if defined(HAMON_USE_STD_FLAT_MAP)
	using Result = std::pair<Iterator, bool>;
#else
	using Result = hamon::pair<Iterator, bool>;
#endif

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<ValueType const&>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<ValueType&&>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<ValueType const&>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<ValueType&&>())), "");

	Map v;
	{
		ValueType const x{Key{1}, T{10}};
		auto r = v.insert(x);
		VERIFY(r.first->first == Key{1});
		VERIFY(r.first->second == T{10});
		VERIFY(r.second == true);
	}
	VERIFY(v.size() == 1);
	VERIFY(v[Key{1}] == T{10});
	{
		ValueType x{Key{2}, T{30}};
		auto r = v.insert(hamon::move(x));
		VERIFY(r.first->first == Key{2});
		VERIFY(r.first->second == T{30});
		VERIFY(r.second == true);
	}
	VERIFY(v.size() == 2);
	VERIFY(v[Key{1}] == T{10});
	VERIFY(v[Key{2}] == T{30});
	{
		ValueType x{Key{1}, T{20}};
		auto r = v.insert(hamon::move(x));
		VERIFY(r.first->first == Key{1});
		VERIFY(r.first->second == T{10});
		VERIFY(r.second == false);
	}
	VERIFY(v.size() == 2);
	VERIFY(v[Key{1}] == T{10});
	VERIFY(v[Key{2}] == T{30});
	{
		ValueType const x{Key{2}, T{40}};
		auto r = v.insert(x);
		VERIFY(r.first->first == Key{2});
		VERIFY(r.first->second == T{30});
		VERIFY(r.second == false);
	}
	VERIFY(v.size() == 2);
	VERIFY(v[Key{1}] == T{10});
	VERIFY(v[Key{2}] == T{30});

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMapTest, InsertTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::less<>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::greater<>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<int>>()));
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace insert_test

}	// namespace hamon_flat_map_test
