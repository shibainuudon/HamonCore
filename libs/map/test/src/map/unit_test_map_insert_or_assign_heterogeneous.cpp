﻿/**
 *	@file	unit_test_map_insert_or_assign_heterogeneous.cpp
 *
 *	@brief	insert_or_assign のテスト
 *
 *	template<class K, class M>
 *	pair<iterator, bool> insert_or_assign(K&& k, M&& obj);
 */

#include <hamon/map/map.hpp>
#include <hamon/functional.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if !defined(HAMON_USE_STD_MAP) || \
	(defined(__cpp_lib_associative_heterogeneous_insertion) && (__cpp_lib_associative_heterogeneous_insertion >= 202306L))

namespace hamon_map_test
{

namespace insert_or_assign_heterogeneous_test
{

#if !defined(HAMON_USE_STD_MAP)
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define MAP_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define MAP_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define MAP_TEST_CONSTEXPR              /**/
#endif

struct Key
{
	int value;

	explicit constexpr Key(int v) : value(v) {}

	friend constexpr bool operator==(Key const& lhs, Key const& rhs)
	{
		return lhs.value == rhs.value;
	}

	friend constexpr bool operator==(Key const& lhs, int rhs)
	{
		return lhs.value == rhs;
	}

	friend constexpr bool operator<(Key const& lhs, Key const& rhs)
	{
		return lhs.value < rhs.value;
	}

	friend constexpr bool operator<(Key const& lhs, int rhs)
	{
		return lhs.value < rhs;
	}

	friend constexpr bool operator<(int lhs, Key const& rhs)
	{
		return lhs < rhs.value;
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename T>
MAP_TEST_CONSTEXPR bool test()
{
	using Map = hamon::map<Key, T, hamon::less<>>;
	using ValueType = typename Map::value_type;
	using Iterator = typename Map::iterator;
#if defined(HAMON_USE_STD_MAP)
	using Result = std::pair<Iterator, bool>;
#else
	using Result = hamon::pair<Iterator, bool>;
#endif

	{
		Map v;
		static_assert(hamon::is_same<decltype(v.insert_or_assign(hamon::declval<int const&>(), hamon::declval<T>())), Result>::value, "");
		static_assert(hamon::is_same<decltype(v.insert_or_assign(hamon::declval<int&&>(), hamon::declval<T>())), Result>::value, "");
		static_assert(!noexcept(v.insert_or_assign(hamon::declval<int const&>(), hamon::declval<T>())), "");
		static_assert(!noexcept(v.insert_or_assign(hamon::declval<int&&>(), hamon::declval<T>())), "");
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
		auto r = v.insert_or_assign(1, T{30});
		VERIFY(r.first == hamon::next(v.begin(), 0));
		VERIFY(r.second == false);

		VERIFY(v.size() == 2);
		auto it = v.begin();
		VERIFY(*it++ == ValueType{Key{1}, T{30}});
		VERIFY(*it++ == ValueType{Key{3}, T{20}});
		VERIFY(it == v.end());
	}

	{
		auto r = v.insert_or_assign(2, T{40});
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
		int const k{3};
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
		int const k{0};
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

GTEST_TEST(MapTest, InsertOrAssignHeterogeneousTest)
{
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<int>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<char>()));
	MAP_TEST_CONSTEXPR_EXPECT_TRUE((test<float>()));
}

#undef MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef MAP_TEST_CONSTEXPR

}	// namespace insert_or_assign_heterogeneous_test

}	// namespace hamon_map_test

#endif
