/**
 *	@file	unit_test_flat_multimap_insert.cpp
 *
 *	@brief	insert のテスト
 *
 *	constexpr iterator insert(const value_type& x);
 *	constexpr iterator insert(value_type&& x);
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
#include <gtest/gtest.h>
#include <sstream>
#include "constexpr_test.hpp"
#include "flat_multimap_test_helper.hpp"

namespace hamon_flat_multimap_test
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
	using Map = hamon::flat_multimap<Key, T, Compare, KeyContainer, MappedContainer>;
	using ValueType = typename Map::value_type;
	using Iterator = typename Map::iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<ValueType const&>())), Iterator>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<ValueType&&>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<ValueType const&>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<ValueType&&>())), "");

	Map v;
	{
		ValueType const x{Key{1}, T{10}};
		auto r = v.insert(x);
		VERIFY(r->first == Key{1});
		VERIFY(r->second == T{10});
	}
	VERIFY(v.size() == 1);
	VERIFY(v.count(Key{1}) == 1);
	VERIFY(v.count(Key{2}) == 0);
	VERIFY(v.count(Key{3}) == 0);
	{
		ValueType x{Key{2}, T{30}};
		auto r = v.insert(hamon::move(x));
		VERIFY(r->first == Key{2});
		VERIFY(r->second == T{30});
	}
	VERIFY(v.size() == 2);
	VERIFY(v.count(Key{1}) == 1);
	VERIFY(v.count(Key{2}) == 1);
	VERIFY(v.count(Key{3}) == 0);
	{
		ValueType x{Key{1}, T{20}};
		auto r = v.insert(hamon::move(x));
		VERIFY(r->first == Key{1});
		VERIFY(r->second == T{20});
	}
	VERIFY(v.size() == 3);
	VERIFY(v.count(Key{1}) == 2);
	VERIFY(v.count(Key{2}) == 1);
	VERIFY(v.count(Key{3}) == 0);
	{
		ValueType const x{Key{3}, T{40}};
		auto r = v.insert(x);
		VERIFY(r->first == Key{3});
		VERIFY(r->second == T{40});
	}
	VERIFY(v.size() == 4);
	VERIFY(v.count(Key{1}) == 2);
	VERIFY(v.count(Key{2}) == 1);
	VERIFY(v.count(Key{3}) == 1);

	return true;
}

#undef VERIFY

GTEST_TEST(FlatMultimapTest, InsertTest)
{
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<int>, hamon::vector<double>, hamon::less<int>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::vector<float>, hamon::deque<char>, hamon::greater<float>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<char>, hamon::vector<long>, hamon::less<char>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<hamon::deque<double>, hamon::deque<float>, hamon::greater<double>>()));
	FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<MinSequenceContainer<int>, MinSequenceContainer<char>, hamon::less<int>>()));

	{
		hamon::flat_multimap<int, char> fm;

		// 単一要素を挿入する
		fm.insert({3, 'a'});
		fm.insert({3, 'a'});

		hamon::flat_multimap<int, char> fm2 =
		{
			{ 5, 'd'},
			{15, 'e'},
		};

		// シーケンスを挿入する
		fm.insert(fm2.begin(), fm2.end());

		// 挿入するシーケンスがソート済みかつ重複要素がないことがわかっている場合、
		// 以下のように指定した方が高速になる
		fm.insert(hamon::sorted_equivalent, fm2.begin(), fm2.end());

		std::stringstream ss;
		for (const auto& p : fm)
		{
			ss << p.first << ":" << p.second << ", ";
		}
		EXPECT_EQ("3:a, 3:a, 5:d, 5:d, 15:e, 15:e, ", ss.str());
	}
}

#undef FLAT_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef FLAT_MAP_TEST_CONSTEXPR

}	// namespace insert_test

}	// namespace hamon_flat_multimap_test
