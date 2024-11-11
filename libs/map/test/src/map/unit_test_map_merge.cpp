/**
 *	@file	unit_test_map_merge.cpp
 *
 *	@brief	merge のテスト
 *
 *	template<class C2>
 *	void merge(map<Key, T, C2, Allocator>& source);
 *
 *	template<class C2>
 *	void merge(map<Key, T, C2, Allocator>&& source);
 *
 *	template<class C2>
 *	void merge(multimap<Key, T, C2, Allocator>& source);
 *
 *	template<class C2>
 *	void merge(multimap<Key, T, C2, Allocator>&& source);
 */

#include <hamon/map/map.hpp>
#include <hamon/map/multimap.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include <string>
#include <sstream>

#if 1	// TODO
#if !defined(HAMON_USE_STD_MAP) || \
	(defined(__cpp_lib_node_extract) && (__cpp_lib_node_extract >= 201606L))

namespace hamon_map_test
{

namespace merge_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test1()
{
	using Map = hamon::map<Key, T>;
	using ValueType = typename Map::value_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().merge(hamon::declval<Map&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().merge(hamon::declval<Map&&>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().merge(hamon::declval<Map&>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().merge(hamon::declval<Map&&>())), "");

	Map v1
	{
		{Key{1}, T{10}},
		{Key{2}, T{20}},
		{Key{3}, T{30}},
	};
	Map v2
	{
		{Key{3}, T{10}},
		{Key{1}, T{20}},
		{Key{4}, T{30}},
		{Key{1}, T{40}},
		{Key{5}, T{50}},
	};

	v1.merge(v2);
	VERIFY(v1.size() == 5);
	{
		auto it = v1.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{10}});
		VERIFY(*it++ == ValueType{Key{2}, T{20}});
		VERIFY(*it++ == ValueType{Key{3}, T{30}});
		VERIFY(*it++ == ValueType{Key{4}, T{30}});
		VERIFY(*it++ == ValueType{Key{5}, T{50}});
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 2);
	{
		auto it = v2.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{20}});
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(it == v2.end());
	}

	v2.merge(hamon::move(v1));
	VERIFY(v1.size() == 2);
	{
		auto it = v1.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{10}});
		VERIFY(*it++ == ValueType{Key{3}, T{30}});
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 5);
	{
		auto it = v2.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{20}});
		VERIFY(*it++ == ValueType{Key{2}, T{20}});
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(*it++ == ValueType{Key{4}, T{30}});
		VERIFY(*it++ == ValueType{Key{5}, T{50}});
		VERIFY(it == v2.end());
	}

	return true;
}

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test2()
{
	using Map1 = hamon::map<Key, T, hamon::less<>>;
	using Map2 = hamon::map<Key, T, hamon::greater<>>;
	using ValueType = typename Map1::value_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map1&>().merge(hamon::declval<Map2&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map1&>().merge(hamon::declval<Map2&&>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Map1&>().merge(hamon::declval<Map2&>())), "");
	static_assert(!noexcept(hamon::declval<Map1&>().merge(hamon::declval<Map2&&>())), "");

	Map1 v1
	{
		{Key{1}, T{10}},
		{Key{2}, T{20}},
		{Key{3}, T{30}},
	};
	Map2 v2
	{
		{Key{3}, T{10}},
		{Key{1}, T{20}},
		{Key{4}, T{30}},
		{Key{1}, T{40}},
		{Key{5}, T{50}},
	};

	v1.merge(v2);
	VERIFY(v1.size() == 5);
	{
		auto it = v1.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{10}});
		VERIFY(*it++ == ValueType{Key{2}, T{20}});
		VERIFY(*it++ == ValueType{Key{3}, T{30}});
		VERIFY(*it++ == ValueType{Key{4}, T{30}});
		VERIFY(*it++ == ValueType{Key{5}, T{50}});
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 2);
	{
		auto it = v2.begin();
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(*it++ == ValueType{Key{1}, T{20}});
		VERIFY(it == v2.end());
	}

	v2.merge(hamon::move(v1));
	VERIFY(v1.size() == 2);
	{
		auto it = v1.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{10}});
		VERIFY(*it++ == ValueType{Key{3}, T{30}});
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 5);
	{
		auto it = v2.begin();
		VERIFY(*it++ == ValueType{Key{5}, T{50}});
		VERIFY(*it++ == ValueType{Key{4}, T{30}});
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(*it++ == ValueType{Key{2}, T{20}});
		VERIFY(*it++ == ValueType{Key{1}, T{20}});
		VERIFY(it == v2.end());
	}

	return true;
}

template <typename Key, typename T>
MAP_TEST_CONSTEXPR bool test3()
{
	using Map1 = hamon::map<Key, T, hamon::less<>>;
	using Map2 = hamon::multimap<Key, T, hamon::greater<>>;
	using ValueType = typename Map1::value_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map1&>().merge(hamon::declval<Map2&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map1&>().merge(hamon::declval<Map2&&>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Map1&>().merge(hamon::declval<Map2&>())), "");
	static_assert(!noexcept(hamon::declval<Map1&>().merge(hamon::declval<Map2&&>())), "");

	Map1 v1
	{
		{Key{1}, T{10}},
		{Key{2}, T{20}},
		{Key{3}, T{30}},
	};
	Map2 v2
	{
		{Key{3}, T{10}},
		{Key{1}, T{20}},
		{Key{4}, T{30}},
		{Key{1}, T{40}},
		{Key{5}, T{50}},
	};

	v1.merge(v2);
	VERIFY(v1.size() == 5);
	{
		auto it = v1.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{10}});
		VERIFY(*it++ == ValueType{Key{2}, T{20}});
		VERIFY(*it++ == ValueType{Key{3}, T{30}});
		VERIFY(*it++ == ValueType{Key{4}, T{30}});
		VERIFY(*it++ == ValueType{Key{5}, T{50}});
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 3);
	{
		auto it = v2.begin();
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(*it++ == ValueType{Key{1}, T{20}});
		VERIFY(*it++ == ValueType{Key{1}, T{40}});
		VERIFY(it == v2.end());
	}

	v2.merge(hamon::move(v1));
	VERIFY(v1.size() == 0);
	VERIFY(v2.size() == 8);
	{
		auto it = v2.begin();
		VERIFY(*it++ == ValueType{Key{5}, T{50}});
		VERIFY(*it++ == ValueType{Key{4}, T{30}});
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(*it++ == ValueType{Key{3}, T{30}});
		VERIFY(*it++ == ValueType{Key{2}, T{20}});
		VERIFY(*it++ == ValueType{Key{1}, T{20}});
		VERIFY(*it++ == ValueType{Key{1}, T{40}});
		VERIFY(*it++ == ValueType{Key{1}, T{10}});
		VERIFY(it == v2.end());
	}

	return true;
}

#undef VERIFY

template <typename Key, typename T, typename C>
std::string ToString(const hamon::map<Key, T, C>& m)
{
	std::stringstream out;
	for (const auto& n : m)
	{
		out << "[" << n.first << "] = " << n.second << ", ";
	}
	return out.str();
}

GTEST_TEST(MapTest, MergeTest)
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

	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<int, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<int, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<int, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<char, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<char, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<char, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<float, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<float, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<float, float>()));

	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<int, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<int, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<int, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<char, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<char, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<char, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<float, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<float, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<float, float>()));

	// https://en.cppreference.com/w/cpp/container/map/merge
	{
		hamon::map<int, std::string> ma {{1, "apple"}, {5, "pear"}, {10, "banana"}};
		hamon::map<int, std::string> mb {{2, "zorro"}, {4, "batman"}, {5, "X"}, {8, "alpaca"}};
		hamon::map<int, std::string> u;
		u.merge(ma);
		EXPECT_EQ("[1] = apple, [5] = pear, [10] = banana, ", ToString(u));
		EXPECT_EQ("", ToString(ma));
		u.merge(mb);
		EXPECT_EQ("[1] = apple, [2] = zorro, [4] = batman, [5] = pear, [8] = alpaca, [10] = banana, ", ToString(u));
		EXPECT_EQ("[5] = X, ", ToString(mb));
	}
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace merge_test

}	// namespace hamon_map_test

#endif
#endif
