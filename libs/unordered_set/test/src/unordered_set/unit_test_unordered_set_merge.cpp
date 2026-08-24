/**
 *	@file	unit_test_unordered_set_merge.cpp
 *
 *	@brief	merge のテスト
 *
 *	template<class H2, class P2>
 *	constexpr void merge(unordered_set<Key, H2, P2, Allocator>& source);
 *
 *	template<class H2, class P2>
 *	constexpr void merge(unordered_set<Key, H2, P2, Allocator>&& source);
 *
 *	template<class H2, class P2>
 *	constexpr void merge(unordered_multiset<Key, H2, P2, Allocator>& source);
 *
 *	template<class H2, class P2>
 *	constexpr void merge(unordered_multiset<Key, H2, P2, Allocator>&& source);
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_set_test_helper.hpp"

namespace hamon_unordered_set_test
{

namespace merge_test
{

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test1()
{
	using Set = hamon::unordered_set<Key>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().merge(hamon::declval<Set&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().merge(hamon::declval<Set&&>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().merge(hamon::declval<Set&>())), "");
	static_assert(!noexcept(hamon::declval<Set&>().merge(hamon::declval<Set&&>())), "");

	{
		Set v1;
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
		VERIFY(v2.size() == 0);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 0);
		VERIFY(v2.count(Key{1}) == 0);
		VERIFY(v2.count(Key{2}) == 0);
		VERIFY(v2.count(Key{3}) == 0);
		VERIFY(v2.count(Key{4}) == 0);
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

		VERIFY(v1.size() == 5);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.count(Key{0}) == 1);
		VERIFY(v1.count(Key{1}) == 1);
		VERIFY(v1.count(Key{2}) == 1);
		VERIFY(v1.count(Key{3}) == 1);
		VERIFY(v1.count(Key{4}) == 1);
		VERIFY(v2.size() == 1);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 0);
		VERIFY(v2.count(Key{1}) == 1);
		VERIFY(v2.count(Key{2}) == 0);
		VERIFY(v2.count(Key{3}) == 0);
		VERIFY(v2.count(Key{4}) == 0);
	}

	return true;
}

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test2()
{
	using Set1 = hamon::unordered_set<Key>;
	using Set2 = hamon::unordered_set<Key, TransparentHash, hamon::equal_to<>>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set1&>().merge(hamon::declval<Set2&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set1&>().merge(hamon::declval<Set2&&>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Set1&>().merge(hamon::declval<Set2&>())), "");
	static_assert(!noexcept(hamon::declval<Set1&>().merge(hamon::declval<Set2&&>())), "");

	{
		Set1 v1
		{
			Key{0},
			Key{1},
			Key{4},
		};
		Set2 v2
		{
			Key{1},
			Key{2},
		};

		VERIFY(v1.size() == 3);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.count(Key{0}) == 1);
		VERIFY(v1.count(Key{1}) == 1);
		VERIFY(v1.count(Key{2}) == 0);
		VERIFY(v1.count(Key{3}) == 0);
		VERIFY(v1.count(Key{4}) == 1);
		VERIFY(v2.size() == 2);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 0);
		VERIFY(v2.count(Key{1}) == 1);
		VERIFY(v2.count(Key{2}) == 1);
		VERIFY(v2.count(Key{3}) == 0);
		VERIFY(v2.count(Key{4}) == 0);

		v1.merge(v2);

		VERIFY(v1.size() == 4);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.count(Key{0}) == 1);
		VERIFY(v1.count(Key{1}) == 1);
		VERIFY(v1.count(Key{2}) == 1);
		VERIFY(v1.count(Key{3}) == 0);
		VERIFY(v1.count(Key{4}) == 1);
		VERIFY(v2.size() == 1);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 0);
		VERIFY(v2.count(Key{1}) == 1);
		VERIFY(v2.count(Key{2}) == 0);
		VERIFY(v2.count(Key{3}) == 0);
		VERIFY(v2.count(Key{4}) == 0);
	}
	{
		Set1 v1
		{
			Key{0},
			Key{1},
			Key{4},
		};
		Set2 v2
		{
			Key{2},
			Key{3},
		};

		VERIFY(v1.size() == 3);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.count(Key{0}) == 1);
		VERIFY(v1.count(Key{1}) == 1);
		VERIFY(v1.count(Key{2}) == 0);
		VERIFY(v1.count(Key{3}) == 0);
		VERIFY(v1.count(Key{4}) == 1);
		VERIFY(v2.size() == 2);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 0);
		VERIFY(v2.count(Key{1}) == 0);
		VERIFY(v2.count(Key{2}) == 1);
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

template <typename Key>
HAMON_CXX20_CONSTEXPR bool test3()
{
	using Set1 = hamon::unordered_set<Key>;
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
		};
		Set2 v2
		{
			Key{1},
			Key{2},
			Key{2},
		};

		VERIFY(v1.size() == 2);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.count(Key{0}) == 1);
		VERIFY(v1.count(Key{1}) == 1);
		VERIFY(v1.count(Key{2}) == 0);
		VERIFY(v1.count(Key{3}) == 0);
		VERIFY(v1.count(Key{4}) == 0);
		VERIFY(v2.size() == 3);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 0);
		VERIFY(v2.count(Key{1}) == 1);
		VERIFY(v2.count(Key{2}) == 2);
		VERIFY(v2.count(Key{3}) == 0);
		VERIFY(v2.count(Key{4}) == 0);

		v1.merge(v2);

		VERIFY(v1.size() == 3);
		VERIFY(v1.load_factor() <= v1.max_load_factor());
		VERIFY(v1.count(Key{0}) == 1);
		VERIFY(v1.count(Key{1}) == 1);
		VERIFY(v1.count(Key{2}) == 1);
		VERIFY(v1.count(Key{3}) == 0);
		VERIFY(v1.count(Key{4}) == 0);
		VERIFY(v2.size() == 2);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 0);
		VERIFY(v2.count(Key{1}) == 1);
		VERIFY(v2.count(Key{2}) == 1);
		VERIFY(v2.count(Key{3}) == 0);
		VERIFY(v2.count(Key{4}) == 0);
	}
	{
		Set1 v1
		{
			Key{1},
			Key{3},
			Key{4},
		};
		Set2 v2
		{
			Key{0},
			Key{0},
			Key{1},
			Key{2},
			Key{2},
			Key{2},
			Key{3},
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
		VERIFY(v2.size() == 5);
		VERIFY(v2.load_factor() <= v2.max_load_factor());
		VERIFY(v2.count(Key{0}) == 1);
		VERIFY(v2.count(Key{1}) == 1);
		VERIFY(v2.count(Key{2}) == 2);
		VERIFY(v2.count(Key{3}) == 1);
		VERIFY(v2.count(Key{4}) == 0);
	}

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, MergeTest)
{
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test1<float>()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test2<float>()));

	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test3<int>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test3<char>()));
	HAMON_CXX20_CONSTEXPR_EXPECT_TRUE((test3<float>()));
}

}	// namespace merge_test

}	// namespace hamon_unordered_set_test
