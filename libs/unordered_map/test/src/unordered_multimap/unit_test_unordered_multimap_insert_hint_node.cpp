/**
 *	@file	unit_test_unordered_multimap_insert_hint_node.cpp
 *
 *	@brief	insert のテスト
 *
 *	constexpr iterator insert(const_iterator hint, node_type&& nh);
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multimap_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) || \
	(defined(__cpp_lib_node_extract) && (__cpp_lib_node_extract >= 201606L))

namespace hamon_unordered_multimap_test
{

namespace insert_hint_node_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::unordered_multimap<Key, T>;
	using Iterator = typename Map::iterator;
	using ConstIterator = typename Map::const_iterator;
	using NodeType = typename Map::node_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<ConstIterator>(), hamon::declval<NodeType>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<ConstIterator>(), hamon::declval<NodeType>())), "");

	Map v1;
	v1.max_load_factor(0.5f);
	v1.insert({
		{Key{1}, T{10}},
		{Key{2}, T{20}},
		{Key{3}, T{30}},
	});
	Map v2
	{
		{Key{3}, T{40}},
		{Key{1}, T{50}},
		{Key{4}, T{60}},
		{Key{1}, T{70}},
	};

	VERIFY(v1.size() == 3);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{1}) == 1);
	VERIFY(v1.count(Key{2}) == 1);
	VERIFY(v1.count(Key{3}) == 1);

	VERIFY(v2.size() == 4);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{1}) == 2);
	VERIFY(v2.count(Key{2}) == 0);
	VERIFY(v2.count(Key{3}) == 1);
	VERIFY(v2.count(Key{4}) == 1);

	{
		auto r = v1.insert(v1.end(), v2.extract(Key{1}));
		VERIFY(r != v1.end());
		VERIFY(r->first == Key{1});
		VERIFY(r->second == T{50} ||
		       r->second == T{70});
	}

	VERIFY(v1.size() == 4);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{1}) == 2);
	VERIFY(v1.count(Key{2}) == 1);
	VERIFY(v1.count(Key{3}) == 1);

	VERIFY(v2.size() == 3);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{1}) == 1);
	VERIFY(v2.count(Key{2}) == 0);
	VERIFY(v2.count(Key{3}) == 1);
	VERIFY(v2.count(Key{4}) == 1);

	{
		auto r = v1.insert(v1.end(), v2.extract(Key{2}));
		VERIFY(r == v1.end());
	}

	VERIFY(v1.size() == 4);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{1}) == 2);
	VERIFY(v1.count(Key{2}) == 1);
	VERIFY(v1.count(Key{3}) == 1);

	VERIFY(v2.size() == 3);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{1}) == 1);
	VERIFY(v2.count(Key{2}) == 0);
	VERIFY(v2.count(Key{3}) == 1);
	VERIFY(v2.count(Key{4}) == 1);

	{
		auto r = v1.insert(v1.end(), v2.extract(Key{3}));
		VERIFY(r != v1.end());
		VERIFY(r->first == Key{3});
		VERIFY(r->second == T{40});
	}

	VERIFY(v1.size() == 5);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{1}) == 2);
	VERIFY(v1.count(Key{2}) == 1);
	VERIFY(v1.count(Key{3}) == 2);

	VERIFY(v2.size() == 2);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{1}) == 1);
	VERIFY(v2.count(Key{2}) == 0);
	VERIFY(v2.count(Key{3}) == 0);
	VERIFY(v2.count(Key{4}) == 1);

	while (!v2.empty())
	{
		auto r = v1.insert(v1.end(), v2.extract(v2.begin()));
		VERIFY(r != v1.end());
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v2.load_factor() <= v2.max_load_factor());
	}

	VERIFY(v1.size() == 7);

	return true;
}

UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test2()
{
	// コピー不可、ムーブ不可なオブジェクトを別のMapに移動する

	using Key = int;
	using T = NonCopyableMovable;
	using Map = hamon::unordered_multimap<Key, T>;

	Map v1;
	v1.emplace(1, 10);
	v1.emplace(1, 11);
	v1.emplace(1, 12);
	v1.emplace(2, 13);
	v1.emplace(4, 14);

	Map v2;
	v2.emplace(1, 15);
	v2.emplace(1, 16);
	v2.emplace(3, 17);
	v2.emplace(4, 18);

	VERIFY(v1.size() == 5);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{1}) == 3);
	VERIFY(v1.count(Key{2}) == 1);
	VERIFY(v1.count(Key{3}) == 0);
	VERIFY(v1.count(Key{4}) == 1);

	VERIFY(v2.size() == 4);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{1}) == 2);
	VERIFY(v2.count(Key{2}) == 0);
	VERIFY(v2.count(Key{3}) == 1);
	VERIFY(v2.count(Key{4}) == 1);

	{
		auto r = v1.insert(v1.begin(), v2.extract(Key{1}));
		VERIFY(r != v1.end());
		VERIFY(r->first == Key{1});
	}

	VERIFY(v1.size() == 6);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{1}) == 4);
	VERIFY(v1.count(Key{2}) == 1);
	VERIFY(v1.count(Key{3}) == 0);
	VERIFY(v1.count(Key{4}) == 1);

	VERIFY(v2.size() == 3);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{1}) == 1);
	VERIFY(v2.count(Key{2}) == 0);
	VERIFY(v2.count(Key{3}) == 1);
	VERIFY(v2.count(Key{4}) == 1);

	{
		auto r = v1.insert(v1.begin(), v2.extract(Key{2}));
		VERIFY(r == v1.end());
	}

	VERIFY(v1.size() == 6);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{1}) == 4);
	VERIFY(v1.count(Key{2}) == 1);
	VERIFY(v1.count(Key{3}) == 0);
	VERIFY(v1.count(Key{4}) == 1);

	VERIFY(v2.size() == 3);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{1}) == 1);
	VERIFY(v2.count(Key{2}) == 0);
	VERIFY(v2.count(Key{3}) == 1);
	VERIFY(v2.count(Key{4}) == 1);

	{
		auto r = v1.insert(v1.begin(), v2.extract(Key{3}));
		VERIFY(r != v1.end());
		VERIFY(r->first == Key{3});
	}

	VERIFY(v1.size() == 7);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{1}) == 4);
	VERIFY(v1.count(Key{2}) == 1);
	VERIFY(v1.count(Key{3}) == 1);
	VERIFY(v1.count(Key{4}) == 1);

	VERIFY(v2.size() == 2);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{1}) == 1);
	VERIFY(v2.count(Key{2}) == 0);
	VERIFY(v2.count(Key{3}) == 0);
	VERIFY(v2.count(Key{4}) == 1);

	return true;
}

UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test3()
{
	// ハッシュ関数、比較関数が異なるMapに移動する

	using Key = int;
	using T = float;
	using Map1 = hamon::unordered_multimap<Key, T>;
	using Map2 = hamon::unordered_multimap<Key, T, WorstHash<Key>, hamon::equal_to<>>;

	Map1 v1
	{
		{Key{1}, T{10}},
		{Key{2}, T{20}},
	};
	Map2 v2
	{
		{Key{2}, T{30}},
		{Key{3}, T{40}},
		{Key{4}, T{50}},
	};

	VERIFY(v1.size() == 2);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{1}) == 1);
	VERIFY(v1.count(Key{2}) == 1);
	VERIFY(v1.count(Key{3}) == 0);
	VERIFY(v1.count(Key{4}) == 0);

	VERIFY(v2.size() == 3);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{1}) == 0);
	VERIFY(v2.count(Key{2}) == 1);
	VERIFY(v2.count(Key{3}) == 1);
	VERIFY(v2.count(Key{4}) == 1);

	{
		auto r = v2.insert(v2.cend(), v1.extract(Key{1}));
		VERIFY(r != v2.end());
		VERIFY(r->first == Key{1});
		VERIFY(r->second == T{10});
	}

	VERIFY(v1.size() == 1);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{1}) == 0);
	VERIFY(v1.count(Key{2}) == 1);
	VERIFY(v1.count(Key{3}) == 0);
	VERIFY(v1.count(Key{4}) == 0);

	VERIFY(v2.size() == 4);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{1}) == 1);
	VERIFY(v2.count(Key{2}) == 1);
	VERIFY(v2.count(Key{3}) == 1);
	VERIFY(v2.count(Key{4}) == 1);

	{
		auto r = v2.insert(v2.cend(), v1.extract(Key{2}));
		VERIFY(r != v2.end());
		VERIFY(r->first == Key{2});
		VERIFY(r->second == T{20});
	}

	VERIFY(v1.size() == 0);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{1}) == 0);
	VERIFY(v1.count(Key{2}) == 0);
	VERIFY(v1.count(Key{3}) == 0);
	VERIFY(v1.count(Key{4}) == 0);

	VERIFY(v2.size() == 5);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{1}) == 1);
	VERIFY(v2.count(Key{2}) == 2);
	VERIFY(v2.count(Key{3}) == 1);
	VERIFY(v2.count(Key{4}) == 1);

	{
		auto r = v2.insert(v2.cend(), v1.extract(Key{3}));
		VERIFY(r == v2.end());
	}

	VERIFY(v1.size() == 0);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{1}) == 0);
	VERIFY(v1.count(Key{2}) == 0);
	VERIFY(v1.count(Key{3}) == 0);
	VERIFY(v1.count(Key{4}) == 0);

	VERIFY(v2.size() == 5);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{1}) == 1);
	VERIFY(v2.count(Key{2}) == 2);
	VERIFY(v2.count(Key{3}) == 1);
	VERIFY(v2.count(Key{4}) == 1);

	return true;
}

UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test4()
{
	// mapからmultimapに移動する

	using Key = int;
	using T = float;
	using Map      = hamon::unordered_map<Key, T>;
	using Multimap = hamon::unordered_multimap<Key, T, WorstHash<Key>, hamon::equal_to<>>;

	Map v1
	{
		{Key{1}, T{10}},
		{Key{2}, T{20}},
		{Key{3}, T{30}},
	};
	Multimap v2
	{
		{Key{2}, T{30}},
		{Key{3}, T{40}},
		{Key{3}, T{50}},
	};

	VERIFY(v1.size() == 3);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{1}) == 1);
	VERIFY(v1.count(Key{2}) == 1);
	VERIFY(v1.count(Key{3}) == 1);

	VERIFY(v2.size() == 3);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{1}) == 0);
	VERIFY(v2.count(Key{2}) == 1);
	VERIFY(v2.count(Key{3}) == 2);

	{
		auto r = v2.insert(v2.cbegin(), v1.extract(Key{1}));
		VERIFY(r != v2.end());
		VERIFY(r->first == Key{1});
		VERIFY(r->second == T{10});
	}

	VERIFY(v1.size() == 2);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{1}) == 0);
	VERIFY(v1.count(Key{2}) == 1);
	VERIFY(v1.count(Key{3}) == 1);

	VERIFY(v2.size() == 4);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{1}) == 1);
	VERIFY(v2.count(Key{2}) == 1);
	VERIFY(v2.count(Key{3}) == 2);

	{
		auto r = v2.insert(v2.cbegin(), v1.extract(Key{2}));
		VERIFY(r != v2.end());
		VERIFY(r->first == Key{2});
		VERIFY(r->second == T{20});
	}

	VERIFY(v1.size() == 1);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{1}) == 0);
	VERIFY(v1.count(Key{2}) == 0);
	VERIFY(v1.count(Key{3}) == 1);

	VERIFY(v2.size() == 5);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{1}) == 1);
	VERIFY(v2.count(Key{2}) == 2);
	VERIFY(v2.count(Key{3}) == 2);

	{
		auto r = v2.insert(v2.cbegin(), v1.extract(Key{2}));
		VERIFY(r == v2.end());
	}

	VERIFY(v1.size() == 1);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{1}) == 0);
	VERIFY(v1.count(Key{2}) == 0);
	VERIFY(v1.count(Key{3}) == 1);

	VERIFY(v2.size() == 5);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{1}) == 1);
	VERIFY(v2.count(Key{2}) == 2);
	VERIFY(v2.count(Key{3}) == 2);

	{
		auto r = v2.insert(v2.cbegin(), v1.extract(Key{3}));
		VERIFY(r != v2.end());
		VERIFY(r->first == Key{3});
		VERIFY(r->second == T{30});
	}

	VERIFY(v1.size() == 0);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{1}) == 0);
	VERIFY(v1.count(Key{2}) == 0);
	VERIFY(v1.count(Key{3}) == 0);

	VERIFY(v2.size() == 6);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{1}) == 1);
	VERIFY(v2.count(Key{2}) == 2);
	VERIFY(v2.count(Key{3}) == 3);

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, InsertHintNodeTest)
{
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));

	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test4()));
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace insert_hint_node_test

}	// namespace hamon_unordered_multimap_test

#endif
