/**
 *	@file	unit_test_unordered_multiset_merge.cpp
 *
 *	@brief	merge のテスト
 *
 *	template<class H2, class P2>
 *	constexpr void merge(unordered_multiset<Key, H2, P2, Allocator>& source);
 *
 *	template<class H2, class P2>
 *	constexpr void merge(unordered_multiset<Key, H2, P2, Allocator>&& source);
 *
 *	template<class H2, class P2>
 *	constexpr void merge(unordered_set<Key, H2, P2, Allocator>& source);
 *
 *	template<class H2, class P2>
 *	constexpr void merge(unordered_set<Key, H2, P2, Allocator>&& source);
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multiset_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) || \
	(defined(__cpp_lib_node_extract) && (__cpp_lib_node_extract >= 201606L))

namespace hamon_unordered_multiset_test
{

namespace merge_test
{

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_MULTISET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
UNORDERED_MULTISET_TEST_CONSTEXPR bool test1()
{
	using Set = hamon::unordered_multiset<Key>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().merge(hamon::declval<Set&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().merge(hamon::declval<Set&&>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().merge(hamon::declval<Set&>())), "");
	static_assert(!noexcept(hamon::declval<Set&>().merge(hamon::declval<Set&&>())), "");

	{
		Set v1;
		v1.max_load_factor(0.25f);

		Set v2
		{
			Key{3},
			Key{1},
			Key{4},
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
#if !(defined(HAMON_USE_STD_UNORDERED_MULTISET) && defined(HAMON_STDLIB_DINKUMWARE))	// Microsoft-STL だとマージ後のオブジェクトの状態が怪しい
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
		Set v1
		{
			Key{0},
			Key{1},
			Key{3},
		};
		Set v2
		{
			Key{1},
			Key{2},
			Key{4},
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
#if !(defined(HAMON_USE_STD_UNORDERED_MULTISET) && defined(HAMON_STDLIB_DINKUMWARE))	// Microsoft-STL だとマージ後のオブジェクトの状態が怪しい
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

template <typename Key>
UNORDERED_MULTISET_TEST_CONSTEXPR bool test2()
{
	using Set1 = hamon::unordered_multiset<Key>;
	using Set2 = hamon::unordered_multiset<Key, TransparentHash, hamon::equal_to<>>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set1&>().merge(hamon::declval<Set2&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set1&>().merge(hamon::declval<Set2&&>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Set1&>().merge(hamon::declval<Set2&>())), "");
	static_assert(!noexcept(hamon::declval<Set1&>().merge(hamon::declval<Set2&&>())), "");

	{
		Set1 v1
		{
			Key{0},
			Key{1},
			Key{1},
		};
		Set2 v2
		{
			Key{1},
			Key{2},
			Key{3},
			Key{3},
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
#if !(defined(HAMON_USE_STD_UNORDERED_MULTISET) && defined(HAMON_STDLIB_DINKUMWARE))	// Microsoft-STL だとマージ後のオブジェクトの状態が怪しい
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
		Set1 v1
		{
			Key{1},
			Key{2},
			Key{3},
			Key{4},
		};
		Set2 v2
		{
			Key{0},
			Key{1},
			Key{3},
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
#if !(defined(HAMON_USE_STD_UNORDERED_MULTISET) && defined(HAMON_STDLIB_DINKUMWARE))	// Microsoft-STL だとマージ後のオブジェクトの状態が怪しい
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

template <typename Key>
UNORDERED_MULTISET_TEST_CONSTEXPR bool test3()
{
	using Set1 = hamon::unordered_multiset<Key>;
	using Set2 = hamon::unordered_set<Key, TransparentHash, hamon::equal_to<>>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set1&>().merge(hamon::declval<Set2&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set1&>().merge(hamon::declval<Set2&&>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Set1&>().merge(hamon::declval<Set2&>())), "");
	static_assert(!noexcept(hamon::declval<Set1&>().merge(hamon::declval<Set2&&>())), "");

	{
		Set1 v1
		{
			Key{1},
			Key{2},
			Key{3},
			Key{4},
		};
		Set2 v2
		{
			Key{0},
			Key{1},
			Key{3},
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
#if !(defined(HAMON_USE_STD_UNORDERED_MULTISET) && defined(HAMON_STDLIB_DINKUMWARE))	// Microsoft-STL だとマージ後のオブジェクトの状態が怪しい
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
		Set1 v1
		{
			Key{1},
			Key{1},
			Key{1},
			Key{2},
		};
		Set2 v2
		{
			Key{0},
			Key{1},
			Key{2},
			Key{3},
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
#if !(defined(HAMON_USE_STD_UNORDERED_MULTISET) && defined(HAMON_STDLIB_DINKUMWARE))	// Microsoft-STL だとマージ後のオブジェクトの状態が怪しい
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

GTEST_TEST(UnorderedMultisetTest, MergeTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<float>()));

	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test2<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test2<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test2<float>()));

	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test3<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test3<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test3<float>()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace merge_test

}	// namespace hamon_unordered_multiset_test

#endif
