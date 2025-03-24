/**
 *	@file	unit_test_unordered_map_insert_node.cpp
 *
 *	@brief	insert のテスト
 *
 *	constexpr insert_return_type insert(node_type&& nh);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_map_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MAP) || \
	(defined(__cpp_lib_node_extract) && (__cpp_lib_node_extract >= 201606L))

namespace hamon_unordered_map_test
{

namespace insert_node_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::unordered_map<Key, T>;
	using NodeType = typename Map::node_type;
	using InsertReturnType = typename Map::insert_return_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<NodeType>())), InsertReturnType>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<NodeType>())), "");

	Map v1
	{
		{Key{2}, T{10}},
		{Key{3}, T{20}},
	};
	Map v2
	{
		{Key{3}, T{30}},
		{Key{1}, T{40}},
		{Key{4}, T{50}},
	};

	VERIFY(v1.size() == 2);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.at(Key{2}) == T{10});
	VERIFY(v1.at(Key{3}) == T{20});

	VERIFY(v2.size() == 3);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.at(Key{1}) == T{40});
	VERIFY(v2.at(Key{3}) == T{30});
	VERIFY(v2.at(Key{4}) == T{50});

	{
		auto r = v1.insert(v2.extract(Key{1}));
		VERIFY(r.inserted == true);
		VERIFY(r.position != v1.end());
		VERIFY(r.position->first == Key{1});
		VERIFY(r.position->second == T{40});
		VERIFY(r.node.empty() == true);
	}

	VERIFY(v1.size() == 3);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.at(Key{1}) == T{40});
	VERIFY(v1.at(Key{2}) == T{10});
	VERIFY(v1.at(Key{3}) == T{20});

	VERIFY(v2.size() == 2);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.at(Key{3}) == T{30});
	VERIFY(v2.at(Key{4}) == T{50});

	{
		auto r = v1.insert(v2.extract(Key{2}));
		VERIFY(r.inserted == false);
		VERIFY(r.position == v1.end());
		VERIFY(r.node.empty() == true);
	}

	VERIFY(v1.size() == 3);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.at(Key{1}) == T{40});
	VERIFY(v1.at(Key{2}) == T{10});
	VERIFY(v1.at(Key{3}) == T{20});

	VERIFY(v2.size() == 2);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.at(Key{3}) == T{30});
	VERIFY(v2.at(Key{4}) == T{50});

	{
		auto r = v1.insert(v2.extract(Key{3}));
		VERIFY(r.inserted == false);
		VERIFY(r.position != v1.end());
		VERIFY(r.position->first == Key{3});
		VERIFY(r.position->second == T{20});
		VERIFY(r.node.empty() == false);
		VERIFY(r.node.key() == Key{3});
		VERIFY(r.node.mapped() == T{30});
	}

	VERIFY(v1.size() == 3);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.at(Key{1}) == T{40});
	VERIFY(v1.at(Key{2}) == T{10});
	VERIFY(v1.at(Key{3}) == T{20});

	VERIFY(v2.size() == 1);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.at(Key{4}) == T{50});

	{
		auto r = v1.insert(v2.extract(v2.begin()));
		VERIFY(r.inserted == true);
		VERIFY(r.position != v1.end());
		VERIFY(r.position->first == Key{4});
		VERIFY(r.position->second == T{50});
		VERIFY(r.node.empty() == true);
	}

	VERIFY(v1.size() == 4);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.at(Key{1}) == T{40});
	VERIFY(v1.at(Key{2}) == T{10});
	VERIFY(v1.at(Key{3}) == T{20});
	VERIFY(v1.at(Key{4}) == T{50});

	VERIFY(v2.size() == 0);
	VERIFY(v2.load_factor() <= v2.max_load_factor());

	for (int i = 0; i < 100; ++i)
	{
		v2.emplace(static_cast<Key>(i + 10), T{42});
	}

	VERIFY(v2.size() == 100);
	VERIFY(v2.load_factor() <= v2.max_load_factor());

	while (!v2.empty())
	{
		auto r = v1.insert(v2.extract(v2.begin()));
		VERIFY(r.inserted == true);
		VERIFY(r.position != v1.end());
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v2.load_factor() <= v2.max_load_factor());
	}

	VERIFY(v2.size() == 0);
	VERIFY(v2.load_factor() <= v2.max_load_factor());

	return true;
}

UNORDERED_MAP_TEST_CONSTEXPR bool test2()
{
	// コピー不可、ムーブ不可なオブジェクトを別のMapに移動する

	using Key = int;
	using T = NonCopyableMovable;
	using Map = hamon::unordered_map<Key, T>;

	Map v1;
	v1.emplace(1, 10);
	v1.emplace(2, 11);
	v1.emplace(3, 12);
	v1.emplace(5, 13);

	Map v2;
	v2.emplace(2, 14);
	v2.emplace(4, 15);
	v2.emplace(6, 16);

	VERIFY(v1.size() == 4);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.at(Key{1}) == T{10});
	VERIFY(v1.at(Key{2}) == T{11});
	VERIFY(v1.at(Key{3}) == T{12});
	VERIFY(v1.at(Key{5}) == T{13});

	VERIFY(v2.size() == 3);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.at(Key{2}) == T{14});
	VERIFY(v2.at(Key{4}) == T{15});
	VERIFY(v2.at(Key{6}) == T{16});

	{
		auto r = v1.insert(v2.extract(Key{2}));
		VERIFY(r.inserted == false);
		VERIFY(r.position != v1.end());
		VERIFY(r.position->first == Key{2});
		VERIFY(r.position->second == T{11});
		VERIFY(r.node.empty() == false);
		VERIFY(r.node.key() == Key{2});
		VERIFY(r.node.mapped() == T{14});
	}

	VERIFY(v1.size() == 4);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.at(Key{1}) == T{10});
	VERIFY(v1.at(Key{2}) == T{11});
	VERIFY(v1.at(Key{3}) == T{12});
	VERIFY(v1.at(Key{5}) == T{13});

	VERIFY(v2.size() == 2);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.at(Key{4}) == T{15});
	VERIFY(v2.at(Key{6}) == T{16});

	{
		auto r = v1.insert(v2.extract(Key{3}));
		VERIFY(r.inserted == false);
		VERIFY(r.position == v1.end());
		VERIFY(r.node.empty() == true);
	}

	VERIFY(v1.size() == 4);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.at(Key{1}) == T{10});
	VERIFY(v1.at(Key{2}) == T{11});
	VERIFY(v1.at(Key{3}) == T{12});
	VERIFY(v1.at(Key{5}) == T{13});

	VERIFY(v2.size() == 2);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.at(Key{4}) == T{15});
	VERIFY(v2.at(Key{6}) == T{16});

	{
		auto r = v1.insert(v2.extract(Key{4}));
		VERIFY(r.inserted == true);
		VERIFY(r.position != v1.end());
		VERIFY(r.position->first == Key{4});
		VERIFY(r.position->second == T{15});
		VERIFY(r.node.empty() == true);
	}

	VERIFY(v1.size() == 5);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.at(Key{1}) == T{10});
	VERIFY(v1.at(Key{2}) == T{11});
	VERIFY(v1.at(Key{3}) == T{12});
	VERIFY(v1.at(Key{4}) == T{15});
	VERIFY(v1.at(Key{5}) == T{13});

	VERIFY(v2.size() == 1);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.at(Key{6}) == T{16});

	return true;
}

UNORDERED_MAP_TEST_CONSTEXPR bool test3()
{
	// ハッシュ関数、比較関数が異なるMapに移動する

	using Key = int;
	using T = float;
	using Map1 = hamon::unordered_map<Key, T>;
	using Map2 = hamon::unordered_map<Key, T, WorstHash<Key>, hamon::equal_to<>>;

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
	VERIFY(v1.at(Key{1}) == T{10});
	VERIFY(v1.at(Key{2}) == T{20});

	VERIFY(v2.size() == 3);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.at(Key{2}) == T{30});
	VERIFY(v2.at(Key{3}) == T{40});
	VERIFY(v2.at(Key{4}) == T{50});

	{
		auto r = v2.insert(v1.extract(Key{0}));
		VERIFY(r.inserted == false);
		VERIFY(r.position == v2.end());
		VERIFY(r.node.empty() == true);
	}

	VERIFY(v1.size() == 2);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.at(Key{1}) == T{10});
	VERIFY(v1.at(Key{2}) == T{20});

	VERIFY(v2.size() == 3);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.at(Key{2}) == T{30});
	VERIFY(v2.at(Key{3}) == T{40});
	VERIFY(v2.at(Key{4}) == T{50});

	{
		auto r = v2.insert(v1.extract(Key{1}));
		VERIFY(r.inserted == true);
		VERIFY(r.position != v2.end());
		VERIFY(r.position->first == Key{1});
		VERIFY(r.position->second == T{10});
		VERIFY(r.node.empty() == true);
	}

	VERIFY(v1.size() == 1);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.at(Key{2}) == T{20});

	VERIFY(v2.size() == 4);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.at(Key{1}) == T{10});
	VERIFY(v2.at(Key{2}) == T{30});
	VERIFY(v2.at(Key{3}) == T{40});
	VERIFY(v2.at(Key{4}) == T{50});

	{
		auto r = v2.insert(v1.extract(Key{2}));
		VERIFY(r.inserted == false);
		VERIFY(r.position != v2.end());
		VERIFY(r.position->first == Key{2});
		VERIFY(r.position->second == T{30});
		VERIFY(r.node.empty() == false);
		VERIFY(r.node.key() == Key{2});
		VERIFY(r.node.mapped() == T{20});
	}

	VERIFY(v1.size() == 0);
	VERIFY(v1.load_factor() <= v1.max_load_factor());

	VERIFY(v2.size() == 4);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.at(Key{1}) == T{10});
	VERIFY(v2.at(Key{2}) == T{30});
	VERIFY(v2.at(Key{3}) == T{40});
	VERIFY(v2.at(Key{4}) == T{50});

	return true;
}

UNORDERED_MAP_TEST_CONSTEXPR bool test4()
{
	// multimapからmapに移動する

	using Key = int;
	using T = float;
	using Map      = hamon::unordered_map<Key, T>;
	using Multimap = hamon::unordered_multimap<Key, T, WorstHash<Key>, hamon::equal_to<>>;

	Map v1
	{
		{Key{1}, T{10}},
		{Key{2}, T{20}},
	};
	Multimap v2
	{
		{Key{2}, T{30}},
		{Key{3}, T{40}},
		{Key{3}, T{50}},
		{Key{4}, T{60}},
		{Key{4}, T{70}},
		{Key{4}, T{80}},
	};

	VERIFY(v1.size() == 2);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.at(Key{1}) == T{10});
	VERIFY(v1.at(Key{2}) == T{20});

	VERIFY(v2.size() == 6);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{2}) == 1);
	VERIFY(v2.count(Key{3}) == 2);
	VERIFY(v2.count(Key{4}) == 3);

	{
		auto r = v1.insert(v2.extract(Key{1}));
		VERIFY(r.inserted == false);
		VERIFY(r.position == v1.end());
		VERIFY(r.node.empty() == true);
	}

	VERIFY(v1.size() == 2);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.at(Key{1}) == T{10});
	VERIFY(v1.at(Key{2}) == T{20});

	VERIFY(v2.size() == 6);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{2}) == 1);
	VERIFY(v2.count(Key{3}) == 2);
	VERIFY(v2.count(Key{4}) == 3);

	{
		auto r = v1.insert(v2.extract(Key{2}));
		VERIFY(r.inserted == false);
		VERIFY(r.position != v1.end());
		VERIFY(r.position->first == Key{2});
		VERIFY(r.position->second == T{20});
		VERIFY(r.node.empty() == false);
		VERIFY(r.node.key() == Key{2});
		VERIFY(r.node.mapped() == T{30});
	}

	VERIFY(v1.size() == 2);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.at(Key{1}) == T{10});
	VERIFY(v1.at(Key{2}) == T{20});

	VERIFY(v2.size() == 5);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{2}) == 0);
	VERIFY(v2.count(Key{3}) == 2);
	VERIFY(v2.count(Key{4}) == 3);

	{
		auto r = v1.insert(v2.extract(Key{3}));
		VERIFY(r.inserted == true);
		VERIFY(r.position != v1.end());
		VERIFY(r.position->first == Key{3});
		VERIFY(r.position->second == T{40} ||
		       r.position->second == T{50});
		VERIFY(r.node.empty() == true);
	}

	VERIFY(v1.size() == 3);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.at(Key{1}) == T{10});
	VERIFY(v1.at(Key{2}) == T{20});
	VERIFY(v1.at(Key{3}) == T{40} ||
	       v1.at(Key{3}) == T{50});

	VERIFY(v2.size() == 4);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{2}) == 0);
	VERIFY(v2.count(Key{3}) == 1);
	VERIFY(v2.count(Key{4}) == 3);

	{
		auto r = v1.insert(v2.extract(Key{3}));
		VERIFY(r.inserted == false);
		VERIFY(r.position != v1.end());
		VERIFY(r.position->first == Key{3});
		VERIFY(r.position->second == T{40} ||
		       r.position->second == T{50});
		VERIFY(r.node.empty() == false);
		VERIFY(r.node.key() == Key{3});
		VERIFY(r.node.mapped() == T{40} ||
		       r.node.mapped() == T{50});
	}

	VERIFY(v1.size() == 3);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.at(Key{1}) == T{10});
	VERIFY(v1.at(Key{2}) == T{20});
	VERIFY(v1.at(Key{3}) == T{40} ||
	       v1.at(Key{3}) == T{50});

	VERIFY(v2.size() == 3);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{2}) == 0);
	VERIFY(v2.count(Key{3}) == 0);
	VERIFY(v2.count(Key{4}) == 3);

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, InsertNodeTest)
{
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));

	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test4()));
}

#undef UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MAP_TEST_CONSTEXPR

}	// namespace insert_node_test

}	// namespace hamon_unordered_map_test

#endif
