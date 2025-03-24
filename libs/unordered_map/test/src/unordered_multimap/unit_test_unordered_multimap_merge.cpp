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

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) || \
	(defined(__cpp_lib_node_extract) && (__cpp_lib_node_extract >= 201606L))

namespace hamon_unordered_multimap_test
{

namespace merge_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTIMAP_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key, typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test1()
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
#if !(defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && defined(HAMON_STDLIB_DINKUMWARE))	// Microsoft-STL だとマージ後のオブジェクトの状態が怪しい
		VERIFY(v2.size() == 0);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 0);
		VERIFY(v2.count(Key{1}) == 0);
		VERIFY(v2.count(Key{2}) == 0);
		VERIFY(v2.count(Key{3}) == 0);
		VERIFY(v2.count(Key{4}) == 0);
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
#if !(defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && defined(HAMON_STDLIB_DINKUMWARE))	// Microsoft-STL だとマージ後のオブジェクトの状態が怪しい
		VERIFY(v2.size() == 0);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 0);
		VERIFY(v2.count(Key{1}) == 0);
		VERIFY(v2.count(Key{2}) == 0);
		VERIFY(v2.count(Key{3}) == 0);
		VERIFY(v2.count(Key{4}) == 0);
#endif
	}

	return true;
}

template <typename Key, typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test2()
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
#if !(defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && defined(HAMON_STDLIB_DINKUMWARE))	// Microsoft-STL だとマージ後のオブジェクトの状態が怪しい
		VERIFY(v2.size() == 0);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 0);
		VERIFY(v2.count(Key{1}) == 0);
		VERIFY(v2.count(Key{2}) == 0);
		VERIFY(v2.count(Key{3}) == 0);
		VERIFY(v2.count(Key{4}) == 0);
#endif
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
#if !(defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && defined(HAMON_STDLIB_DINKUMWARE))	// Microsoft-STL だとマージ後のオブジェクトの状態が怪しい
		VERIFY(v2.size() == 0);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 0);
		VERIFY(v2.count(Key{1}) == 0);
		VERIFY(v2.count(Key{2}) == 0);
		VERIFY(v2.count(Key{3}) == 0);
		VERIFY(v2.count(Key{4}) == 0);
#endif
	}

	return true;
}

template <typename Key, typename T>
UNORDERED_MULTIMAP_TEST_CONSTEXPR bool test3()
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
#if !(defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && defined(HAMON_STDLIB_DINKUMWARE))	// Microsoft-STL だとマージ後のオブジェクトの状態が怪しい
		VERIFY(v2.size() == 0);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 0);
		VERIFY(v2.count(Key{1}) == 0);
		VERIFY(v2.count(Key{2}) == 0);
		VERIFY(v2.count(Key{3}) == 0);
		VERIFY(v2.count(Key{4}) == 0);
#endif
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
#if !(defined(HAMON_USE_STD_UNORDERED_MULTIMAP) && defined(HAMON_STDLIB_DINKUMWARE))	// Microsoft-STL だとマージ後のオブジェクトの状態が怪しい
		VERIFY(v2.size() == 0);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 0);
		VERIFY(v2.count(Key{1}) == 0);
		VERIFY(v2.count(Key{2}) == 0);
		VERIFY(v2.count(Key{3}) == 0);
		VERIFY(v2.count(Key{4}) == 0);
#endif
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultimapTest, MergeTest)
{
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<int, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<char, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test1<float, float>()));

	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<int, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<int, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<int, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<char, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<char, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<char, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<float, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<float, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test2<float, float>()));

	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<int, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<int, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<int, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<char, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<char, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<char, float>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<float, int>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<float, char>()));
	UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE((test3<float, float>()));
}

#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTIMAP_TEST_CONSTEXPR

}	// namespace merge_test

}	// namespace hamon_unordered_multimap_test

#endif
