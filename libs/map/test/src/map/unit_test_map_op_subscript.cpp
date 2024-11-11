/**
 *	@file	unit_test_map_op_subscript.cpp
 *
 *	@brief	operator[] のテスト
 *
 *	mapped_type& operator[](const key_type& x);
 *	mapped_type& operator[](key_type&& x);
 */

#include <hamon/map/map.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include <string>
#include <sstream>

namespace hamon_map_test
{

namespace op_subscript_test
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
	using MappedType = typename Map::mapped_type;
	using ValueType = typename Map::value_type;

	{
		Map v;
		static_assert(hamon::is_same<decltype(v[hamon::declval<Key const&>()]), MappedType&>::value, "");
		static_assert(hamon::is_same<decltype(v[hamon::declval<Key&&>()]), MappedType&>::value, "");
		static_assert(!noexcept(v[hamon::declval<Key const&>()]), "");
		static_assert(!noexcept(v[hamon::declval<Key&&>()]), "");
	}

	Map v
	{
		{Key{1}, T{10}},
		{Key{3}, T{20}},
	};

	{
		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{10}});
		VERIFY(*it++ == ValueType{Key{3}, T{20}});
		VERIFY(it == v.end());
	}

	v[Key{1}] = T{30};
	{
		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{30}});
		VERIFY(*it++ == ValueType{Key{3}, T{20}});
		VERIFY(it == v.end());
	}

	v[Key{2}] = T{40};
	{
		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{30}});
		VERIFY(*it++ == ValueType{Key{2}, T{40}});
		VERIFY(*it++ == ValueType{Key{3}, T{20}});
		VERIFY(it == v.end());
	}

	{
		Key const k{3};
		v[k] = T{50};
	}
	{
		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{30}});
		VERIFY(*it++ == ValueType{Key{2}, T{40}});
		VERIFY(*it++ == ValueType{Key{3}, T{50}});
		VERIFY(it == v.end());
	}

	{
		Key const k{0};
		v[k] = T{60};
	}
	{
		VERIFY(v.size() == 4);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{0}, T{60}});
		VERIFY(*it++ == ValueType{Key{1}, T{30}});
		VERIFY(*it++ == ValueType{Key{2}, T{40}});
		VERIFY(*it++ == ValueType{Key{3}, T{50}});
		VERIFY(it == v.end());
	}

	VERIFY(v[Key{0}] == T{60});
	VERIFY(v[Key{1}] == T{30});
	VERIFY(v[Key{2}] == T{40});
	VERIFY(v[Key{3}] == T{50});
	VERIFY(v[Key{4}] == T{});
	{
		VERIFY(v.size() == 5);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{0}, T{60}});
		VERIFY(*it++ == ValueType{Key{1}, T{30}});
		VERIFY(*it++ == ValueType{Key{2}, T{40}});
		VERIFY(*it++ == ValueType{Key{3}, T{50}});
		VERIFY(*it++ == ValueType{Key{4}, T{}});
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

GTEST_TEST(MapTest, OpSubscriptTest)
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

	// https://en.cppreference.com/w/cpp/container/map/operator_at
	{
		hamon::map<char, int> letter_counts {{'a', 27}, {'b', 3}, {'c', 1}};

		EXPECT_EQ("[a] = 27, [b] = 3, [c] = 1, ", ToString(letter_counts));

		letter_counts['b'] = 42; // updates an existing value
		letter_counts['x'] = 9;  // inserts a new value

		EXPECT_EQ("[a] = 27, [b] = 42, [c] = 1, [x] = 9, ", ToString(letter_counts));

		// count the number of occurrences of each word
		// (the first call to operator[] initialized the counter with zero)
		hamon::map<std::string, int>  word_map;
		for (const auto& w : {"this", "sentence", "is", "not", "a", "sentence",
							  "this", "sentence", "is", "a", "hoax"})
		{
			++word_map[w];
		}
		word_map["that"]; // just inserts the pair {"that", 0}

		EXPECT_EQ("[a] = 2, [hoax] = 1, [is] = 2, [not] = 1, [sentence] = 3, [that] = 0, [this] = 2, ", ToString(word_map));
	}
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace op_subscript_test

}	// namespace hamon_map_test
