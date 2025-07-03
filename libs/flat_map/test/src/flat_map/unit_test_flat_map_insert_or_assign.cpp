/**
 *	@file	unit_test_flat_map_insert_or_assign.cpp
 *
 *	@brief	insert_or_assign のテスト
 *
 *	template<class M>
 *	constexpr pair<iterator, bool> insert_or_assign(const key_type& k, M&& obj);
 *
 *	template<class M>
 *	constexpr pair<iterator, bool> insert_or_assign(key_type&& k, M&& obj);
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

namespace insert_or_assign_test
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
	using Iterator = typename Map::iterator;
#if defined(HAMON_USE_STD_FLAT_MAP)
	using Result = std::pair<Iterator, bool>;
#else
	using Result = hamon::pair<Iterator, bool>;
#endif

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert_or_assign(hamon::declval<Key const&>(), hamon::declval<T const&>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert_or_assign(hamon::declval<Key&&>(), hamon::declval<T const&>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert_or_assign(hamon::declval<Key const&>(), hamon::declval<T const&>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert_or_assign(hamon::declval<Key&&>(), hamon::declval<T const&>())), "");

	Map v
	{
		{Key{1}, T{10}},
		{Key{3}, T{20}},
	};

	VERIFY(v.size() == 2);
	VERIFY(v[Key{1}] == T{10});
	VERIFY(v[Key{3}] == T{20});

	{
		auto r = v.insert_or_assign(Key{1}, T{30});
		VERIFY(r.first->first == Key{1});
		VERIFY(r.first->second == T{30});
		VERIFY(r.second == false);
	}
	VERIFY(v.size() == 2);
	VERIFY(v[Key{1}] == T{30});
	VERIFY(v[Key{3}] == T{20});
	{
		auto r = v.insert_or_assign(Key{2}, T{40});
		VERIFY(r.first->first == Key{2});
		VERIFY(r.first->second == T{40});
		VERIFY(r.second == true);
	}
	VERIFY(v.size() == 3);
	VERIFY(v[Key{1}] == T{30});
	VERIFY(v[Key{2}] == T{40});
	VERIFY(v[Key{3}] == T{20});
	{
		Key const k{3};
		auto r = v.insert_or_assign(k, T{50});
		VERIFY(r.first->first == Key{3});
		VERIFY(r.first->second == T{50});
		VERIFY(r.second == false);
	}
	VERIFY(v.size() == 3);
	VERIFY(v[Key{1}] == T{30});
	VERIFY(v[Key{2}] == T{40});
	VERIFY(v[Key{3}] == T{50});
	{
		Key const k{0};
		auto r = v.insert_or_assign(k, T{60});
		VERIFY(r.first->first == Key{0});
		VERIFY(r.first->second == T{60});
		VERIFY(r.second == true);
	}
	VERIFY(v.size() == 4);
	VERIFY(v[Key{0}] == T{60});
	VERIFY(v[Key{1}] == T{30});
	VERIFY(v[Key{2}] == T{40});
	VERIFY(v[Key{3}] == T{50});

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMapTest, InsertOrAssignTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<int>>()));

	{
		hamon::flat_map<hamon::string, int> fm;

		auto r1 = fm.insert_or_assign("foo", 42);
		EXPECT_TRUE(r1.first->first == "foo");
		EXPECT_TRUE(r1.first->second == 42);
		EXPECT_TRUE(r1.second == true);

		auto r2 = fm.insert_or_assign("foo", 0);
		EXPECT_TRUE(r2.first->first == "foo");
		EXPECT_TRUE(r2.first->second == 0);
		EXPECT_TRUE(r2.second == false);
	}
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace insert_or_assign_test

}	// namespace hamon_flat_map_test
