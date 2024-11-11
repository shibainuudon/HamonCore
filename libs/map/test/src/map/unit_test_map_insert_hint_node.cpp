/**
 *	@file	unit_test_map_insert_hint_node.cpp
 *
 *	@brief	insert のテスト
 *
 *	iterator insert(const_iterator hint, node_type&& nh);
 */

#include <hamon/map/map.hpp>
#include <hamon/map/multimap.hpp>
#include <hamon/functional.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if !defined(HAMON_USE_STD_MAP) || \
	(defined(__cpp_lib_node_extract) && (__cpp_lib_node_extract >= 201606L))

namespace hamon_map_test
{

namespace insert_hint_node_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
#endif

struct S
{
	int value;

	constexpr S(int v) : value(v) {}

	S(S&&)                 = delete;
	S(S const&)            = delete;
	S& operator=(S&&)      = delete;
	S& operator=(S const&) = delete;
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::map<Key, T>;
	using ValueType = typename Map::value_type;
	using NodeType = typename Map::node_type;
	using Iterator = typename Map::iterator;
	using ConstIterator = typename Map::const_iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert(hamon::declval<ConstIterator>(), hamon::declval<NodeType>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert(hamon::declval<ConstIterator>(), hamon::declval<NodeType>())), "");

	Map v1;
	Map v2
	{
		{Key{3}, T{10}},
		{Key{1}, T{20}},
		{Key{4}, T{30}},
		{Key{1}, T{40}},
		{Key{5}, T{50}},
	};

	{
		auto node = v2.extract(Key{1});
		auto r = v1.insert(v1.end(), hamon::move(node));
		VERIFY(r == v1.begin());
	}
	VERIFY(v1.size() == 1);
	{
		auto it = v1.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{20}});
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 3);
	{
		auto it = v2.begin();
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(*it++ == ValueType{Key{4}, T{30}});
		VERIFY(*it++ == ValueType{Key{5}, T{50}});
		VERIFY(it == v2.end());
	}

	{
		auto r = v1.insert(v1.begin(), v2.extract(Key{4}));
		VERIFY(r == hamon::next(v1.begin(), 1));
	}
	VERIFY(v1.size() == 2);
	{
		auto it = v1.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{20}});
		VERIFY(*it++ == ValueType{Key{4}, T{30}});
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 2);
	{
		auto it = v2.begin();
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(*it++ == ValueType{Key{5}, T{50}});
		VERIFY(it == v2.end());
	}

	{
		auto r = v1.insert(v1.begin(), v2.extract(Key{2}));
		VERIFY(r == v1.end());
	}
	VERIFY(v1.size() == 2);
	{
		auto it = v1.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{20}});
		VERIFY(*it++ == ValueType{Key{4}, T{30}});
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 2);
	{
		auto it = v2.begin();
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(*it++ == ValueType{Key{5}, T{50}});
		VERIFY(it == v2.end());
	}

	return true;
}

MAP_TEST_CONSTEXPR bool test2()
{
	using Map = hamon::map<int, S>;

	Map v1;
	v1.emplace(1, 10);
	v1.emplace(2, 11);
	v1.emplace(3, 12);
	v1.emplace(4, 13);

	Map v2;
	v2.emplace(2, 14);
	v2.emplace(4, 15);
	v2.emplace(6, 16);

	{
		auto r = v1.insert(v1.begin(), v2.extract(v2.begin()));
		VERIFY(r == hamon::next(v1.begin(), 1));
	}
	VERIFY(v1.size() == 4);
	{
		auto it = v1.begin();
		VERIFY(it->first == 1);
		VERIFY(it->second.value == 10);
		++it;
		VERIFY(it->first == 2);
		VERIFY(it->second.value == 11);
		++it;
		VERIFY(it->first == 3);
		VERIFY(it->second.value == 12);
		++it;
		VERIFY(it->first == 4);
		VERIFY(it->second.value == 13);
		++it;
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 2);
	{
		auto it = v2.begin();
		VERIFY(it->first == 4);
		VERIFY(it->second.value == 15);
		++it;
		VERIFY(it->first == 6);
		VERIFY(it->second.value == 16);
		++it;
		VERIFY(it == v2.end());
	}

	{
		auto r = v1.insert(v1.end(), v2.extract(hamon::next(v2.begin(), 1)));
		VERIFY(r == hamon::next(v1.begin(), 4));
	}
	VERIFY(v1.size() == 5);
	{
		auto it = v1.begin();
		VERIFY(it->first == 1);
		VERIFY(it->second.value == 10);
		++it;
		VERIFY(it->first == 2);
		VERIFY(it->second.value == 11);
		++it;
		VERIFY(it->first == 3);
		VERIFY(it->second.value == 12);
		++it;
		VERIFY(it->first == 4);
		VERIFY(it->second.value == 13);
		++it;
		VERIFY(it->first == 6);
		VERIFY(it->second.value == 16);
		++it;
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 1);
	{
		auto it = v2.begin();
		VERIFY(it->first == 4);
		VERIFY(it->second.value == 15);
		++it;
		VERIFY(it == v2.end());
	}

	return true;
}

MAP_TEST_CONSTEXPR bool test3()
{
	using Map1 = hamon::map<int, float, hamon::less<>>;
	using Map2 = hamon::map<int, float, hamon::greater<>>;
	using ValueType = typename Map1::value_type;

	Map1 v1
	{
		{1, 10.0f},
		{3, 20.0f},
		{4, 30.0f},
	};
	Map2 v2
	{
		{3, 10.5f},
		{4, 20.5f},
		{5, 30.5f},
	};
	VERIFY(v1.size() == 3);
	{
		auto it = v1.begin();
		VERIFY(*it++ == ValueType{1, 10.0f});
		VERIFY(*it++ == ValueType{3, 20.0f});
		VERIFY(*it++ == ValueType{4, 30.0f});
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 3);
	{
		auto it = v2.begin();
		VERIFY(*it++ == ValueType{5, 30.5f});
		VERIFY(*it++ == ValueType{4, 20.5f});
		VERIFY(*it++ == ValueType{3, 10.5f});
		VERIFY(it == v2.end());
	}

	{
		auto r = v1.insert(v1.end(), v2.extract(5));
		VERIFY(r == hamon::next(v1.begin(), 3));
	}
	VERIFY(v1.size() == 4);
	{
		auto it = v1.begin();
		VERIFY(*it++ == ValueType{1, 10.0f});
		VERIFY(*it++ == ValueType{3, 20.0f});
		VERIFY(*it++ == ValueType{4, 30.0f});
		VERIFY(*it++ == ValueType{5, 30.5f});
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 2);
	{
		auto it = v2.begin();
		VERIFY(*it++ == ValueType{4, 20.5f});
		VERIFY(*it++ == ValueType{3, 10.5f});
		VERIFY(it == v2.end());
	}

	{
		auto r = v1.insert(v1.end(), v2.extract(4));
		VERIFY(r == hamon::next(v1.begin(), 2));
	}
	VERIFY(v1.size() == 4);
	{
		auto it = v1.begin();
		VERIFY(*it++ == ValueType{1, 10.0f});
		VERIFY(*it++ == ValueType{3, 20.0f});
		VERIFY(*it++ == ValueType{4, 30.0f});
		VERIFY(*it++ == ValueType{5, 30.5f});
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 1);
	{
		auto it = v2.begin();
		VERIFY(*it++ == ValueType{3, 10.5f});
		VERIFY(it == v2.end());
	}

	{
		auto r = v1.insert(v1.end(), v2.extract(2));
		VERIFY(r == v1.end());
	}
	VERIFY(v1.size() == 4);
	{
		auto it = v1.begin();
		VERIFY(*it++ == ValueType{1, 10.0f});
		VERIFY(*it++ == ValueType{3, 20.0f});
		VERIFY(*it++ == ValueType{4, 30.0f});
		VERIFY(*it++ == ValueType{5, 30.5f});
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 1);
	{
		auto it = v2.begin();
		VERIFY(*it++ == ValueType{3, 10.5f});
		VERIFY(it == v2.end());
	}

	return true;
}

MAP_TEST_CONSTEXPR bool test4()
{
	using Map1 = hamon::map<int, float, hamon::less<>>;
	using Map2 = hamon::multimap<int, float, hamon::greater<>>;
	using ValueType = typename Map1::value_type;

	Map1 v1
	{
		{3, 10.0f},
		{4, 20.0f},
	};
	Map2 v2
	{
		{1, 10.5f},
		{1, 20.5f},
		{2, 30.5f},
	};
	VERIFY(v1.size() == 2);
	{
		auto it = v1.begin();
		VERIFY(*it++ == ValueType{3, 10.0f});
		VERIFY(*it++ == ValueType{4, 20.0f});
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 3);
	{
		auto it = v2.begin();
		VERIFY(*it++ == ValueType{2, 30.5f});
		VERIFY(*it++ == ValueType{1, 10.5f});
		VERIFY(*it++ == ValueType{1, 20.5f});
		VERIFY(it == v2.end());
	}

	{
		auto r = v1.insert(v1.begin(), v2.extract(1));
		VERIFY(r == v1.begin());
	}
	VERIFY(v1.size() == 3);
	{
		auto it = v1.begin();
		VERIFY(*it++ == ValueType{1, 10.5f});
		VERIFY(*it++ == ValueType{3, 10.0f});
		VERIFY(*it++ == ValueType{4, 20.0f});
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 2);
	{
		auto it = v2.begin();
		VERIFY(*it++ == ValueType{2, 30.5f});
		VERIFY(*it++ == ValueType{1, 20.5f});
		VERIFY(it == v2.end());
	}

	{
		auto r = v1.insert(v1.begin(), v2.extract(1));
		VERIFY(r == v1.begin());
	}
	VERIFY(v1.size() == 3);
	{
		auto it = v1.begin();
		VERIFY(*it++ == ValueType{1, 10.5f});
		VERIFY(*it++ == ValueType{3, 10.0f});
		VERIFY(*it++ == ValueType{4, 20.0f});
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 1);
	{
		auto it = v2.begin();
		VERIFY(*it++ == ValueType{2, 30.5f});
		VERIFY(it == v2.end());
	}

	{
		auto r = v1.insert(v1.begin(), v2.extract(3));
		VERIFY(r == v1.end());
	}
	VERIFY(v1.size() == 3);
	{
		auto it = v1.begin();
		VERIFY(*it++ == ValueType{1, 10.5f});
		VERIFY(*it++ == ValueType{3, 10.0f});
		VERIFY(*it++ == ValueType{4, 20.0f});
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 1);
	{
		auto it = v2.begin();
		VERIFY(*it++ == ValueType{2, 30.5f});
		VERIFY(it == v2.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(MapTest, InsertHintNodeTest)
{
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));

	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test4()));
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace insert_hint_node_test

}	// namespace hamon_map_test

#endif
