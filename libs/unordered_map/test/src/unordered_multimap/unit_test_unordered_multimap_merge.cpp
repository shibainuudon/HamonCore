/**
 *	@file	unit_test_unordered_multimap_merge.cpp
 *
 *	@brief	merge のテスト
 *
 *	template<class H2, class P2>
 *	constexpr void merge(unordered_multimap<Key, T, H2, P2, Allocator>& source);
 *
 *	template<class H2, class P2>
 *	constexpr void merge(unordered_multimap<Key, T, H2, P2, Allocator>&& source);
 *
 *	template<class H2, class P2>
 *	constexpr void merge(unordered_map<Key, T, H2, P2, Allocator>& source);
 *
 *	template<class H2, class P2>
 *	constexpr void merge(unordered_map<Key, T, H2, P2, Allocator>&& source);
 */

#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multimap_test_helper.hpp"

namespace hamon_unordered_multimap_test
{

namespace merge_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test1()
{
	using Map = hamon::unordered_multimap<Key, T>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().merge(hamon::declval<Map&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map&>().merge(hamon::declval<Map&&>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Map&>().merge(hamon::declval<Map&>())), "");
	static_assert(!noexcept(hamon::declval<Map&>().merge(hamon::declval<Map&&>())), "");

	{
		Map v1;
		v1.max_load_factor(0.3f);

		Map v2
		{
			{Key{3}, T{10}},
			{Key{1}, T{20}},
			{Key{4}, T{30}},
		};

		VERIFY(v1.size() == 0);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.count(Key{0}) == 0);
		VERIFY(v1.count(Key{1}) == 0);
		VERIFY(v1.count(Key{2}) == 0);
		VERIFY(v1.count(Key{3}) == 0);
		VERIFY(v1.count(Key{4}) == 0);
		VERIFY(v2.size() == 3);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 0);
		VERIFY(v2.count(Key{1}) == 1);
		VERIFY(v2.count(Key{2}) == 0);
		VERIFY(v2.count(Key{3}) == 1);
		VERIFY(v2.count(Key{4}) == 1);

		v1.merge(v2);

		VERIFY(v1.size() == 3);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.count(Key{0}) == 0);
		VERIFY(v1.count(Key{1}) == 1);
		VERIFY(v1.count(Key{2}) == 0);
		VERIFY(v1.count(Key{3}) == 1);
		VERIFY(v1.count(Key{4}) == 1);
		VERIFY(v2.size() == 0);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 0);
		VERIFY(v2.count(Key{1}) == 0);
		VERIFY(v2.count(Key{2}) == 0);
		VERIFY(v2.count(Key{3}) == 0);
		VERIFY(v2.count(Key{4}) == 0);
	}
	{
		Map v1
		{
			{Key{0}, T{10}},
			{Key{1}, T{20}},
			{Key{3}, T{30}},
		};
		Map v2
		{
			{Key{1}, T{40}},
			{Key{2}, T{50}},
			{Key{4}, T{60}},
		};

		VERIFY(v1.size() == 3);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.count(Key{0}) == 1);
		VERIFY(v1.count(Key{1}) == 1);
		VERIFY(v1.count(Key{2}) == 0);
		VERIFY(v1.count(Key{3}) == 1);
		VERIFY(v1.count(Key{4}) == 0);
		VERIFY(v2.size() == 3);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 0);
		VERIFY(v2.count(Key{1}) == 1);
		VERIFY(v2.count(Key{2}) == 1);
		VERIFY(v2.count(Key{3}) == 0);
		VERIFY(v2.count(Key{4}) == 1);

		v1.merge(hamon::move(v2));

		VERIFY(v1.size() == 6);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.count(Key{0}) == 1);
		VERIFY(v1.count(Key{1}) == 2);
		VERIFY(v1.count(Key{2}) == 1);
		VERIFY(v1.count(Key{3}) == 1);
		VERIFY(v1.count(Key{4}) == 1);
		VERIFY(v2.size() == 0);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 0);
		VERIFY(v2.count(Key{1}) == 0);
		VERIFY(v2.count(Key{2}) == 0);
		VERIFY(v2.count(Key{3}) == 0);
		VERIFY(v2.count(Key{4}) == 0);
	}

	return true;
}

template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test2()
{
	using Map1 = hamon::unordered_multimap<Key, T>;
	using Map2 = hamon::unordered_multimap<Key, T, TransparentHash, hamon::equal_to<>>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map1&>().merge(hamon::declval<Map2&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map1&>().merge(hamon::declval<Map2&&>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Map1&>().merge(hamon::declval<Map2&>())), "");
	static_assert(!noexcept(hamon::declval<Map1&>().merge(hamon::declval<Map2&&>())), "");

	{
		Map1 v1
		{
			{Key{0}, T{10}},
			{Key{1}, T{20}},
			{Key{1}, T{30}},
		};
		Map2 v2
		{
			{Key{1}, T{40}},
			{Key{2}, T{50}},
			{Key{3}, T{60}},
			{Key{3}, T{70}},
		};

		VERIFY(v1.size() == 3);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.count(Key{0}) == 1);
		VERIFY(v1.count(Key{1}) == 2);
		VERIFY(v1.count(Key{2}) == 0);
		VERIFY(v1.count(Key{3}) == 0);
		VERIFY(v1.count(Key{4}) == 0);
		VERIFY(v2.size() == 4);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 0);
		VERIFY(v2.count(Key{1}) == 1);
		VERIFY(v2.count(Key{2}) == 1);
		VERIFY(v2.count(Key{3}) == 2);
		VERIFY(v2.count(Key{4}) == 0);

		v1.merge(v2);

		VERIFY(v1.size() == 7);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.count(Key{0}) == 1);
		VERIFY(v1.count(Key{1}) == 3);
		VERIFY(v1.count(Key{2}) == 1);
		VERIFY(v1.count(Key{3}) == 2);
		VERIFY(v1.count(Key{4}) == 0);
		VERIFY(v2.size() == 0);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 0);
		VERIFY(v2.count(Key{1}) == 0);
		VERIFY(v2.count(Key{2}) == 0);
		VERIFY(v2.count(Key{3}) == 0);
		VERIFY(v2.count(Key{4}) == 0);
	}
	{
		Map1 v1
		{
			{Key{1}, T{10}},
			{Key{2}, T{20}},
			{Key{3}, T{30}},
			{Key{4}, T{40}},
		};
		Map2 v2
		{
			{Key{0}, T{50}},
			{Key{1}, T{60}},
			{Key{3}, T{70}},
		};

		VERIFY(v1.size() == 4);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.count(Key{0}) == 0);
		VERIFY(v1.count(Key{1}) == 1);
		VERIFY(v1.count(Key{2}) == 1);
		VERIFY(v1.count(Key{3}) == 1);
		VERIFY(v1.count(Key{4}) == 1);
		VERIFY(v2.size() == 3);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 1);
		VERIFY(v2.count(Key{1}) == 1);
		VERIFY(v2.count(Key{2}) == 0);
		VERIFY(v2.count(Key{3}) == 1);
		VERIFY(v2.count(Key{4}) == 0);

		v1.merge(hamon::move(v2));

		VERIFY(v1.size() == 7);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.count(Key{0}) == 1);
		VERIFY(v1.count(Key{1}) == 2);
		VERIFY(v1.count(Key{2}) == 1);
		VERIFY(v1.count(Key{3}) == 2);
		VERIFY(v1.count(Key{4}) == 1);
		VERIFY(v2.size() == 0);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 0);
		VERIFY(v2.count(Key{1}) == 0);
		VERIFY(v2.count(Key{2}) == 0);
		VERIFY(v2.count(Key{3}) == 0);
		VERIFY(v2.count(Key{4}) == 0);
	}

	return true;
}

template <typename Key, typename T>
HAMON_CXX20_CONSTEXPR bool test3()
{
	using Map1 = hamon::unordered_multimap<Key, T>;
	using Map2 = hamon::unordered_map<Key, T, TransparentHash, hamon::equal_to<>>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map1&>().merge(hamon::declval<Map2&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map1&>().merge(hamon::declval<Map2&&>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Map1&>().merge(hamon::declval<Map2&>())), "");
	static_assert(!noexcept(hamon::declval<Map1&>().merge(hamon::declval<Map2&&>())), "");

	{
		Map1 v1
		{
			{Key{1}, T{10}},
			{Key{2}, T{20}},
			{Key{3}, T{30}},
			{Key{4}, T{40}},
		};
		Map2 v2
		{
			{Key{0}, T{50}},
			{Key{1}, T{60}},
			{Key{3}, T{70}},
		};

		VERIFY(v1.size() == 4);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.count(Key{0}) == 0);
		VERIFY(v1.count(Key{1}) == 1);
		VERIFY(v1.count(Key{2}) == 1);
		VERIFY(v1.count(Key{3}) == 1);
		VERIFY(v1.count(Key{4}) == 1);
		VERIFY(v2.size() == 3);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 1);
		VERIFY(v2.count(Key{1}) == 1);
		VERIFY(v2.count(Key{2}) == 0);
		VERIFY(v2.count(Key{3}) == 1);
		VERIFY(v2.count(Key{4}) == 0);

		v1.merge(v2);

		VERIFY(v1.size() == 7);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.count(Key{0}) == 1);
		VERIFY(v1.count(Key{1}) == 2);
		VERIFY(v1.count(Key{2}) == 1);
		VERIFY(v1.count(Key{3}) == 2);
		VERIFY(v1.count(Key{4}) == 1);
		VERIFY(v2.size() == 0);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 0);
		VERIFY(v2.count(Key{1}) == 0);
		VERIFY(v2.count(Key{2}) == 0);
		VERIFY(v2.count(Key{3}) == 0);
		VERIFY(v2.count(Key{4}) == 0);
	}
	{
		Map1 v1
		{
			{Key{1}, T{10}},
			{Key{1}, T{20}},
			{Key{1}, T{30}},
			{Key{2}, T{40}},
		};
		Map2 v2
		{
			{Key{0}, T{50}},
			{Key{1}, T{60}},
			{Key{2}, T{70}},
			{Key{3}, T{80}},
		};

		VERIFY(v1.size() == 4);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.count(Key{0}) == 0);
		VERIFY(v1.count(Key{1}) == 3);
		VERIFY(v1.count(Key{2}) == 1);
		VERIFY(v1.count(Key{3}) == 0);
		VERIFY(v1.count(Key{4}) == 0);
		VERIFY(v2.size() == 4);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 1);
		VERIFY(v2.count(Key{1}) == 1);
		VERIFY(v2.count(Key{2}) == 1);
		VERIFY(v2.count(Key{3}) == 1);
		VERIFY(v2.count(Key{4}) == 0);

		v1.merge(hamon::move(v2));

		VERIFY(v1.size() == 8);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.count(Key{0}) == 1);
		VERIFY(v1.count(Key{1}) == 4);
		VERIFY(v1.count(Key{2}) == 2);
		VERIFY(v1.count(Key{3}) == 1);
		VERIFY(v1.count(Key{4}) == 0);
		VERIFY(v2.size() == 0);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 0);
		VERIFY(v2.count(Key{1}) == 0);
		VERIFY(v2.count(Key{2}) == 0);
		VERIFY(v2.count(Key{3}) == 0);
		VERIFY(v2.count(Key{4}) == 0);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, MergeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<int, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<char, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<char, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<char, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<float, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<int, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<int, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<int, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<char, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<char, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<char, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<float, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<float, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<float, float>()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test3<int, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test3<int, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test3<int, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test3<char, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test3<char, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test3<char, float>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test3<float, int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test3<float, char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test3<float, float>()));
}

}	// namespace merge_test

}	// namespace hamon_unordered_multimap_test
