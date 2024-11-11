/**
 *	@file	unit_test_map_extract_key.cpp
 *
 *	@brief	extract のテスト
 *
 *	node_type extract(const key_type& x);
 */

#include <hamon/map/map.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include <string>
#include <sstream>

#if !defined(HAMON_USE_STD_MAP) || \
	(defined(__cpp_lib_node_extract) && (__cpp_lib_node_extract >= 201606L))

namespace hamon_map_test
{

namespace extract_key_test
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
MAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::map<Key, T>;
	using ValueType = typename Map::value_type;
	using NodeType = typename Map::node_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().extract(hamon::declval<Key const&>())), NodeType>::value, "");
#if !defined(HAMON_USE_STD_MAP)
	static_assert(!noexcept(hamon::declval<Map&>().extract(hamon::declval<Key const&>())), "");
#endif

	Map v
	{
		{Key{3}, T{10}},
		{Key{1}, T{20}},
		{Key{4}, T{30}},
		{Key{1}, T{40}},
		{Key{5}, T{50}},
	};
	VERIFY(v.size() == 4);

	{
		auto r = v.extract(Key{1});
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.key() == Key{1});
		VERIFY(r.mapped() == T{20});
		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(*it++ == ValueType{Key{4}, T{30}});
		VERIFY(*it++ == ValueType{Key{5}, T{50}});
		VERIFY(it == v.end());
	}
	{
		auto r = v.extract(Key{1});
		VERIFY(bool(r) == false);
		VERIFY(r.empty() == true);
		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(*it++ == ValueType{Key{4}, T{30}});
		VERIFY(*it++ == ValueType{Key{5}, T{50}});
		VERIFY(it == v.end());
	}
	{
		auto r = v.extract(Key{2});
		VERIFY(bool(r) == false);
		VERIFY(r.empty() == true);
		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(*it++ == ValueType{Key{4}, T{30}});
		VERIFY(*it++ == ValueType{Key{5}, T{50}});
		VERIFY(it == v.end());
	}
	{
		auto r = v.extract(Key{5});
		VERIFY(bool(r) == true);
		VERIFY(r.empty() == false);
		VERIFY(r.key() == Key{5});
		VERIFY(r.mapped() == T{50});
		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{3}, T{10}});
		VERIFY(*it++ == ValueType{Key{4}, T{30}});
		VERIFY(it == v.end());
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

GTEST_TEST(MapTest, ExtractKeyTest)
{
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float, float>()));

	// https://en.cppreference.com/w/cpp/container/map/extract
	{
		hamon::map<int, char> cont {{1, 'a'}, {2, 'b'}, {3, 'c'}};
		EXPECT_EQ("[1] = a, [2] = b, [3] = c, ", ToString(cont));

		// Extract node handle and change key
		auto nh = cont.extract(1);
		nh.key() = 4;
		EXPECT_EQ("[2] = b, [3] = c, ", ToString(cont));

		// Insert node handle back
		cont.insert(hamon::move(nh));
		EXPECT_EQ("[2] = b, [3] = c, [4] = a, ", ToString(cont));
	}
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace extract_key_test

}	// namespace hamon_map_test

#endif
