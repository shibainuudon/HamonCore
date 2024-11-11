/**
 *	@file	unit_test_map_insert_or_assign.cpp
 *
 *	@brief	insert_or_assign のテスト
 *
 *	template<class M>
 *	pair<iterator, bool> insert_or_assign(const key_type& k, M&& obj);
 *	template<class M>
 *	pair<iterator, bool> insert_or_assign(key_type&& k, M&& obj);
 */

#include <hamon/map/map.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include <string>
#include <sstream>

#if !defined(HAMON_USE_STD_MAP) || \
	(defined(__cpp_lib_map_try_emplace) && (__cpp_lib_map_try_emplace >= 201411L))

namespace hamon_map_test
{

namespace insert_or_assign_test
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
	using Iterator = typename Map::iterator;
#if defined(HAMON_USE_STD_MAP)
	using Result = std::pair<Iterator, bool>;
#else
	using Result = hamon::pair<Iterator, bool>;
#endif

	{
		Map v;
		static_assert(hamon::is_same<decltype(v.insert_or_assign(hamon::declval<Key const&>(), hamon::declval<T>())), Result>::value, "");
		static_assert(hamon::is_same<decltype(v.insert_or_assign(hamon::declval<Key&&>(), hamon::declval<T>())), Result>::value, "");
		static_assert(!noexcept(v.insert_or_assign(hamon::declval<Key const&>(), hamon::declval<T>())), "");
		static_assert(!noexcept(v.insert_or_assign(hamon::declval<Key&&>(), hamon::declval<T>())), "");
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

	{
		auto r = v.insert_or_assign(Key{1}, T{30});
		VERIFY(r.first == hamon::next(v.begin(), 0));
		VERIFY(r.second == false);

		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{30}});
		VERIFY(*it++ == ValueType{Key{3}, T{20}});
		VERIFY(it == v.end());
	}

	{
		auto r = v.insert_or_assign(Key{2}, T{40});
		VERIFY(r.first == hamon::next(v.begin(), 1));
		VERIFY(r.second == true);

		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{30}});
		VERIFY(*it++ == ValueType{Key{2}, T{40}});
		VERIFY(*it++ == ValueType{Key{3}, T{20}});
		VERIFY(it == v.end());
	}

	{
		Key const k{3};
		auto r = v.insert_or_assign(k, T{50});
		VERIFY(r.first == hamon::next(v.begin(), 2));
		VERIFY(r.second == false);

		VERIFY(v.size() == 3);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{30}});
		VERIFY(*it++ == ValueType{Key{2}, T{40}});
		VERIFY(*it++ == ValueType{Key{3}, T{50}});
		VERIFY(it == v.end());
	}

	{
		Key const k{0};
		auto r = v.insert_or_assign(k, T{60});
		VERIFY(r.first == hamon::next(v.begin(), 0));
		VERIFY(r.second == true);

		VERIFY(v.size() == 4);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{0}, T{60}});
		VERIFY(*it++ == ValueType{Key{1}, T{30}});
		VERIFY(*it++ == ValueType{Key{2}, T{40}});
		VERIFY(*it++ == ValueType{Key{3}, T{50}});
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

GTEST_TEST(MapTest, InsertOrAssignTest)
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

	// https://en.cppreference.com/w/cpp/container/map/insert_or_assign
	{
		hamon::map<std::string, std::string> myMap;
		{
			auto r = myMap.insert_or_assign("a", "apple");
			EXPECT_EQ("a", r.first->first);
			EXPECT_EQ("apple", r.first->second);
			EXPECT_TRUE(r.second);
		}
		{
			auto r = myMap.insert_or_assign("b", "banana");
			EXPECT_EQ("b", r.first->first);
			EXPECT_EQ("banana", r.first->second);
			EXPECT_TRUE(r.second);
		}
		{
			auto r = myMap.insert_or_assign("c", "cherry");
			EXPECT_EQ("c", r.first->first);
			EXPECT_EQ("cherry", r.first->second);
			EXPECT_TRUE(r.second);
		}
		{
			auto r = myMap.insert_or_assign("c", "clementine");
			EXPECT_EQ("c", r.first->first);
			EXPECT_EQ("clementine", r.first->second);
			EXPECT_FALSE(r.second);
		}
		EXPECT_EQ("[a] = apple, [b] = banana, [c] = clementine, ", ToString(myMap));
	}
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace insert_or_assign_test

}	// namespace hamon_map_test

#endif
