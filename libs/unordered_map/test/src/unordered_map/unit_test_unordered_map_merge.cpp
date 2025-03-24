/**
 *	@file	unit_test_unordered_map_merge.cpp
 *
 *	@brief	merge のテスト
 *
 *	template<class H2, class P2>
 *	constexpr void merge(unordered_map<Key, T, H2, P2, Allocator>& source);
 *
 *	template<class H2, class P2>
 *	constexpr void merge(unordered_map<Key, T, H2, P2, Allocator>&& source);
 *
 *	template<class H2, class P2>
 *	constexpr void merge(unordered_multimap<Key, T, H2, P2, Allocator>& source);
 *
 *	template<class H2, class P2>
 *	constexpr void merge(unordered_multimap<Key, T, H2, P2, Allocator>&& source);
 */

#include <hamon/unordered_map/unordered_map.hpp>
#include <hamon/unordered_map/unordered_multimap.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_map_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MAP) || \
	(defined(__cpp_lib_node_extract) && (__cpp_lib_node_extract >= 201606L))

namespace hamon_unordered_map_test
{

namespace merge_test
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
		VERIFY(v2.size() == 3);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.at(Key{1}) == T{20});
		VERIFY(v2.at(Key{3}) == T{10});
		VERIFY(v2.at(Key{4}) == T{30});

		v1.merge(v2);

		VERIFY(v1.size() == 3);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.at(Key{1}) == T{20});
		VERIFY(v1.at(Key{3}) == T{10});
		VERIFY(v1.at(Key{4}) == T{30});
#if !(defined(HAMON_USE_STD_UNORDERED_MAP) && defined(HAMON_STDLIB_DINKUMWARE))	// Microsoft-STL だとマージ後のオブジェクトの状態が怪しい
		VERIFY(v2.size() == 0);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
#endif
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
		VERIFY(v1.at(Key{0}) == T{10});
		VERIFY(v1.at(Key{1}) == T{20});
		VERIFY(v1.at(Key{3}) == T{30});
		VERIFY(v2.size() == 3);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.at(Key{1}) == T{40});
		VERIFY(v2.at(Key{2}) == T{50});
		VERIFY(v2.at(Key{4}) == T{60});

		v1.merge(hamon::move(v2));

		VERIFY(v1.size() == 5);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.at(Key{0}) == T{10});
		VERIFY(v1.at(Key{1}) == T{20});
		VERIFY(v1.at(Key{2}) == T{50});
		VERIFY(v1.at(Key{3}) == T{30});
		VERIFY(v1.at(Key{4}) == T{60});
#if !(defined(HAMON_USE_STD_UNORDERED_MAP) && defined(HAMON_STDLIB_DINKUMWARE))	// Microsoft-STL だとマージ後のオブジェクトの状態が怪しい
		VERIFY(v2.size() == 1);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.at(Key{1}) == T{40});
#endif
	}
	{
		Map v1
		{
			{Key{10}, T{13}},
			{Key{11}, T{13}},
			{Key{12}, T{13}},
			{Key{13}, T{13}},
			{Key{14}, T{13}},
			{Key{15}, T{13}},
			{Key{16}, T{13}},
			{Key{17}, T{13}},
			{Key{18}, T{13}},
			{Key{19}, T{13}},
		};
		Map v2
		{
			{Key{20}, T{13}},
			{Key{21}, T{13}},
			{Key{22}, T{13}},
			{Key{23}, T{13}},
			{Key{24}, T{13}},
			{Key{25}, T{13}},
			{Key{26}, T{13}},
			{Key{27}, T{13}},
			{Key{28}, T{13}},
			{Key{29}, T{13}},
			{Key{30}, T{13}},
			{Key{31}, T{13}},
			{Key{32}, T{13}},
			{Key{33}, T{13}},
			{Key{34}, T{13}},
			{Key{35}, T{13}},
			{Key{36}, T{13}},
			{Key{37}, T{13}},
			{Key{38}, T{13}},
			{Key{39}, T{13}},
		};

		VERIFY(v1.size() == 10);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v2.size() == 20);
		VERIFY(v2.load_factor() <= v2.max_load_factor());

		v1.merge(v2);

		VERIFY(v1.size() == 30);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
#if !(defined(HAMON_USE_STD_UNORDERED_MAP) && defined(HAMON_STDLIB_DINKUMWARE))	// Microsoft-STL だとマージ後のオブジェクトの状態が怪しい
		VERIFY(v2.size() == 0);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
#endif
	}
	{
		Map v1 {};
		Map v2
		{
			{Key{10}, T{13}},
			{Key{11}, T{13}},
			{Key{12}, T{13}},
			{Key{13}, T{13}},
			{Key{14}, T{13}},
			{Key{15}, T{13}},
			{Key{16}, T{13}},
			{Key{17}, T{13}},
			{Key{18}, T{13}},
			{Key{19}, T{13}},
			{Key{20}, T{13}},
			{Key{21}, T{13}},
			{Key{22}, T{13}},
			{Key{23}, T{13}},
			{Key{24}, T{13}},
			{Key{25}, T{13}},
			{Key{26}, T{13}},
			{Key{27}, T{13}},
			{Key{28}, T{13}},
			{Key{29}, T{13}},
			{Key{30}, T{13}},
			{Key{31}, T{13}},
			{Key{32}, T{13}},
			{Key{33}, T{13}},
			{Key{34}, T{13}},
			{Key{35}, T{13}},
			{Key{36}, T{13}},
			{Key{37}, T{13}},
			{Key{38}, T{13}},
			{Key{39}, T{13}},
		};

		VERIFY(v1.size() == 0);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v2.size() == 30);
		VERIFY(v2.load_factor() <= v2.max_load_factor());

		v1.max_load_factor(0.5f);
		v1.merge(v2);

		VERIFY(v1.size() == 30);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
#if !(defined(HAMON_USE_STD_UNORDERED_MAP) && defined(HAMON_STDLIB_DINKUMWARE))	// Microsoft-STL だとマージ後のオブジェクトの状態が怪しい
		VERIFY(v2.size() == 0);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
#endif
	}

	return true;
}

template <typename Key, typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test2()
{
	using Map1 = hamon::unordered_map<Key, T>;
	using Map2 = hamon::unordered_map<Key, T, TransparentHash, hamon::equal_to<>>;

	static_assert(hamon::is_same<decltype(hamon::declval<Map1&>().merge(hamon::declval<Map2&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Map1&>().merge(hamon::declval<Map2&&>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Map1&>().merge(hamon::declval<Map2&>())), "");
	static_assert(!noexcept(hamon::declval<Map1&>().merge(hamon::declval<Map2&&>())), "");

	{
		Map1 v1
		{
			{Key{0}, T{10}},
			{Key{1}, T{20}},
			{Key{4}, T{30}},
		};
		Map2 v2
		{
			{Key{1}, T{40}},
			{Key{2}, T{50}},
		};

		VERIFY(v1.size() == 3);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.at(Key{0}) == T{10});
		VERIFY(v1.at(Key{1}) == T{20});
		VERIFY(v1.at(Key{4}) == T{30});
		VERIFY(v2.size() == 2);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.at(Key{1}) == T{40});
		VERIFY(v2.at(Key{2}) == T{50});

		v1.merge(v2);

		VERIFY(v1.size() == 4);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.at(Key{0}) == T{10});
		VERIFY(v1.at(Key{1}) == T{20});
		VERIFY(v1.at(Key{2}) == T{50});
		VERIFY(v1.at(Key{4}) == T{30});
#if !(defined(HAMON_USE_STD_UNORDERED_MAP) && defined(HAMON_STDLIB_DINKUMWARE))	// Microsoft-STL だとマージ後のオブジェクトの状態が怪しい
		VERIFY(v2.size() == 1);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.at(Key{1}) == T{40});
#endif
	}
	{
		Map1 v1
		{
			{Key{0}, T{10}},
			{Key{1}, T{20}},
			{Key{4}, T{30}},
		};
		Map2 v2
		{
			{Key{2}, T{40}},
			{Key{3}, T{50}},
		};

		VERIFY(v1.size() == 3);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.at(Key{0}) == T{10});
		VERIFY(v1.at(Key{1}) == T{20});
		VERIFY(v1.at(Key{4}) == T{30});
		VERIFY(v2.size() == 2);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.at(Key{2}) == T{40});
		VERIFY(v2.at(Key{3}) == T{50});

		v1.merge(hamon::move(v2));

		VERIFY(v1.size() == 5);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.at(Key{0}) == T{10});
		VERIFY(v1.at(Key{1}) == T{20});
		VERIFY(v1.at(Key{2}) == T{40});
		VERIFY(v1.at(Key{3}) == T{50});
		VERIFY(v1.at(Key{4}) == T{30});
#if !(defined(HAMON_USE_STD_UNORDERED_MAP) && defined(HAMON_STDLIB_DINKUMWARE))	// Microsoft-STL だとマージ後のオブジェクトの状態が怪しい
		VERIFY(v2.size() == 0);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
#endif
	}

	return true;
}

template <typename Key, typename T>
UNORDERED_MAP_TEST_CONSTEXPR bool test3()
{
	using Map1 = hamon::unordered_map<Key, T>;
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
		};
		Map2 v2
		{
			{Key{1}, T{30}},
			{Key{2}, T{40}},
			{Key{2}, T{50}},
		};

		VERIFY(v1.size() == 2);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.count(Key{0}) == 1);
		VERIFY(v1.count(Key{1}) == 1);
		VERIFY(v1.count(Key{2}) == 0);
		VERIFY(v2.size() == 3);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 0);
		VERIFY(v2.count(Key{1}) == 1);
		VERIFY(v2.count(Key{2}) == 2);

		v1.merge(v2);

		VERIFY(v1.size() == 3);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.count(Key{0}) == 1);
		VERIFY(v1.count(Key{1}) == 1);
		VERIFY(v1.count(Key{2}) == 1);
#if !(defined(HAMON_USE_STD_UNORDERED_MAP) && defined(HAMON_STDLIB_DINKUMWARE))	// Microsoft-STL だとマージ後のオブジェクトの状態が怪しい
		VERIFY(v2.size() == 2);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 0);
		VERIFY(v2.count(Key{1}) == 1);
		VERIFY(v2.count(Key{2}) == 1);
#endif
	}
	{
		Map1 v1
		{
			{Key{1}, T{10}},
			{Key{3}, T{20}},
			{Key{4}, T{30}},
		};
		Map2 v2
		{
			{Key{0}, T{40}},
			{Key{0}, T{50}},
			{Key{1}, T{60}},
			{Key{2}, T{70}},
			{Key{2}, T{80}},
			{Key{2}, T{90}},
			{Key{3}, T{100}},
		};

		VERIFY(v1.size() == 3);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.count(Key{0}) == 0);
		VERIFY(v1.count(Key{1}) == 1);
		VERIFY(v1.count(Key{2}) == 0);
		VERIFY(v1.count(Key{3}) == 1);
		VERIFY(v1.count(Key{4}) == 1);
		VERIFY(v2.size() == 7);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 2);
		VERIFY(v2.count(Key{1}) == 1);
		VERIFY(v2.count(Key{2}) == 3);
		VERIFY(v2.count(Key{3}) == 1);
		VERIFY(v2.count(Key{4}) == 0);

		v1.merge(hamon::move(v2));

		VERIFY(v1.size() == 5);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.count(Key{0}) == 1);
		VERIFY(v1.count(Key{1}) == 1);
		VERIFY(v1.count(Key{2}) == 1);
		VERIFY(v1.count(Key{3}) == 1);
		VERIFY(v1.count(Key{4}) == 1);
#if !(defined(HAMON_USE_STD_UNORDERED_MAP) && defined(HAMON_STDLIB_DINKUMWARE))	// Microsoft-STL だとマージ後のオブジェクトの状態が怪しい
		VERIFY(v2.size() == 5);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 1);
		VERIFY(v2.count(Key{1}) == 1);
		VERIFY(v2.count(Key{2}) == 2);
		VERIFY(v2.count(Key{3}) == 1);
		VERIFY(v2.count(Key{4}) == 0);
#endif
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMapTest, MergeTest)
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

	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<int, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<int, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<int, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<char, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<char, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<char, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<float, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<float, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<float, float>()));

	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<int, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<int, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<int, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<char, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<char, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<char, float>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<float, int>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<float, char>()));
	UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<float, float>()));
}

#undef UNORDERED_MAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MAP_TEST_CONSTEXPR

}	// namespace merge_test

}	// namespace hamon_unordered_map_test

#endif
