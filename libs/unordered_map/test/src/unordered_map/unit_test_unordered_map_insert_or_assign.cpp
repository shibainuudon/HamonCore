/**
 *	@file	unit_test_unordered_map_insert_or_assign.cpp
 *
 *	@brief	insert_or_assign のテスト
 *
 *	template<class M>
 *	constexpr pair<iterator, bool> insert_or_assign(const key_type& k, M&& obj);
 *
 *	template<class M>
 *	constexpr pair<iterator, bool> insert_or_assign(key_type&& k, M&& obj);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/pair.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

namespace hamon_unordered_map_test
{

namespace insert_or_assign_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test()
{
	using Map = hamon::unordered_map<Key, T>;
	using Iterator = typename Map::iterator;
	using Result = hamon::pair<Iterator, bool>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert_or_assign(hamon::declval<Key const&>(), hamon::declval<T>())), Result>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().insert_or_assign(hamon::declval<Key&&>(), hamon::declval<T>())), Result>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().insert_or_assign(hamon::declval<Key const&>(), hamon::declval<T>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().insert_or_assign(hamon::declval<Key&&>(), hamon::declval<T>())), "");

	Map v
	{
		{Key{1}, T{10}},
		{Key{3}, T{20}},
	};

	VERIFY(v.size() == 2);
	VERIFY(v.load_factor() <= v.max_load_factor());
	VERIFY(v[Key{1}] == T{10});
	VERIFY(v[Key{3}] == T{20});

	{
		auto r = v.insert_or_assign(Key{1}, T{30});
		VERIFY(r.first->first == Key{1});
		VERIFY(r.first->second == T{30});
		VERIFY(r.second == false);

		VERIFY(v.size() == 2);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[Key{1}] == T{30});
		VERIFY(v[Key{3}] == T{20});
	}
	{
		auto r = v.insert_or_assign(Key{2}, T{40});
		VERIFY(r.first->first == Key{2});
		VERIFY(r.first->second == T{40});
		VERIFY(r.second == true);

		VERIFY(v.size() == 3);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[Key{1}] == T{30});
		VERIFY(v[Key{2}] == T{40});
		VERIFY(v[Key{3}] == T{20});
	}
	{
		Key const k{3};
		auto r = v.insert_or_assign(k, T{50});
		VERIFY(r.first->first == Key{3});
		VERIFY(r.first->second == T{50});
		VERIFY(r.second == false);

		VERIFY(v.size() == 3);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[Key{1}] == T{30});
		VERIFY(v[Key{2}] == T{40});
		VERIFY(v[Key{3}] == T{50});
	}
	{
		Key const k{0};
		auto r = v.insert_or_assign(k, T{60});
		VERIFY(r.first->first == Key{0});
		VERIFY(r.first->second == T{60});
		VERIFY(r.second == true);

		VERIFY(v.size() == 4);
		VERIFY(v.load_factor() <= v.max_load_factor());
		VERIFY(v[Key{0}] == T{60});
		VERIFY(v[Key{1}] == T{30});
		VERIFY(v[Key{2}] == T{40});
		VERIFY(v[Key{3}] == T{50});
	}

	for (int i = 0; i < 100; ++i)
	{
		auto r = v.insert_or_assign(static_cast<Key>(i + 10), T{42});
		VERIFY(r.first->first == static_cast<Key>(i + 10));
		VERIFY(r.first->second == T{42});
		VERIFY(r.second == true);

		VERIFY(v.load_factor() <= v.max_load_factor());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, InsertOrAssignTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<int, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<char, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test<float, float>()));
}

}	// namespace insert_or_assign_test

}	// namespace hamon_unordered_map_test
