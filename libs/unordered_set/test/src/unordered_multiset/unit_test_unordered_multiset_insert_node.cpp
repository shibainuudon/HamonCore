/**
 *	@file	unit_test_unordered_multiset_insert_node.cpp
 *
 *	@brief	insert のテスト
 *
 *	constexpr iterator insert(node_type&& nh);
 */

#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_multiset_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_MULTISET) || \
	(defined(__cpp_lib_node_extract) && (__cpp_lib_node_extract >= 201606L))

namespace hamon_unordered_multiset_test
{

namespace insert_node_test
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
	using NodeType = typename Set::node_type;
	using Iterator = typename Set::iterator;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().insert(hamon::declval<NodeType>())), Iterator>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().insert(hamon::declval<NodeType>())), "");

	Set v1;
	Set v2
	{
		Key{3}, Key{1}, Key{4}, Key{1}, Key{4}, Key{4},
	};

	VERIFY(v1.size() == 0);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{0}) == 0);
	VERIFY(v1.count(Key{1}) == 0);
	VERIFY(v1.count(Key{2}) == 0);
	VERIFY(v1.count(Key{3}) == 0);
	VERIFY(v1.count(Key{4}) == 0);
	VERIFY(v1.count(Key{5}) == 0);
	VERIFY(v2.size() == 6);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{0}) == 0);
	VERIFY(v2.count(Key{1}) == 2);
	VERIFY(v2.count(Key{2}) == 0);
	VERIFY(v2.count(Key{3}) == 1);
	VERIFY(v2.count(Key{4}) == 3);
	VERIFY(v2.count(Key{5}) == 0);

	{
		auto node = v2.extract(Key{1});
		auto r = v1.insert(hamon::move(node));
		VERIFY(r != v1.end());
	}

	VERIFY(v1.size() == 1);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{0}) == 0);
	VERIFY(v1.count(Key{1}) == 1);
	VERIFY(v1.count(Key{2}) == 0);
	VERIFY(v1.count(Key{3}) == 0);
	VERIFY(v1.count(Key{4}) == 0);
	VERIFY(v1.count(Key{5}) == 0);
	VERIFY(v2.size() == 5);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{0}) == 0);
	VERIFY(v2.count(Key{1}) == 1);
	VERIFY(v2.count(Key{2}) == 0);
	VERIFY(v2.count(Key{3}) == 1);
	VERIFY(v2.count(Key{4}) == 3);
	VERIFY(v2.count(Key{5}) == 0);

	{
		auto node = v2.extract(Key{2});
		auto r = v1.insert(hamon::move(node));
		VERIFY(r == v1.end());
	}

	VERIFY(v1.size() == 1);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{0}) == 0);
	VERIFY(v1.count(Key{1}) == 1);
	VERIFY(v1.count(Key{2}) == 0);
	VERIFY(v1.count(Key{3}) == 0);
	VERIFY(v1.count(Key{4}) == 0);
	VERIFY(v1.count(Key{5}) == 0);
	VERIFY(v2.size() == 5);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{0}) == 0);
	VERIFY(v2.count(Key{1}) == 1);
	VERIFY(v2.count(Key{2}) == 0);
	VERIFY(v2.count(Key{3}) == 1);
	VERIFY(v2.count(Key{4}) == 3);
	VERIFY(v2.count(Key{5}) == 0);

	{
		auto node = v2.extract(Key{3});
		auto r = v1.insert(hamon::move(node));
		VERIFY(r != v1.end());
	}

	VERIFY(v1.size() == 2);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{0}) == 0);
	VERIFY(v1.count(Key{1}) == 1);
	VERIFY(v1.count(Key{2}) == 0);
	VERIFY(v1.count(Key{3}) == 1);
	VERIFY(v1.count(Key{4}) == 0);
	VERIFY(v1.count(Key{5}) == 0);
	VERIFY(v2.size() == 4);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{0}) == 0);
	VERIFY(v2.count(Key{1}) == 1);
	VERIFY(v2.count(Key{2}) == 0);
	VERIFY(v2.count(Key{3}) == 0);
	VERIFY(v2.count(Key{4}) == 3);
	VERIFY(v2.count(Key{5}) == 0);

	{
		auto node = v2.extract(Key{3});
		auto r = v1.insert(hamon::move(node));
		VERIFY(r == v1.end());
	}

	VERIFY(v1.size() == 2);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{0}) == 0);
	VERIFY(v1.count(Key{1}) == 1);
	VERIFY(v1.count(Key{2}) == 0);
	VERIFY(v1.count(Key{3}) == 1);
	VERIFY(v1.count(Key{4}) == 0);
	VERIFY(v1.count(Key{5}) == 0);
	VERIFY(v2.size() == 4);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{0}) == 0);
	VERIFY(v2.count(Key{1}) == 1);
	VERIFY(v2.count(Key{2}) == 0);
	VERIFY(v2.count(Key{3}) == 0);
	VERIFY(v2.count(Key{4}) == 3);
	VERIFY(v2.count(Key{5}) == 0);

	return true;
}

UNORDERED_MULTISET_TEST_CONSTEXPR bool test2()
{
	// コピー不可、ムーブ不可なオブジェクトを別のSetに移動する

	using Key = NonCopyableMovable;
	using Set = hamon::unordered_multiset<Key, hamon::hash<Key>>;

	Set v1;
	v1.max_load_factor(0.25f);
	v1.emplace(1);
	v1.emplace(2);
	v1.emplace(3);
	v1.emplace(4);

	Set v2;
	v2.max_load_factor(2.0f);
	v2.emplace(2);
	v2.emplace(4);
	v2.emplace(6);

	VERIFY(v1.size() == 4);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{1}) == 1);
	VERIFY(v1.count(Key{2}) == 1);
	VERIFY(v1.count(Key{3}) == 1);
	VERIFY(v1.count(Key{4}) == 1);
	VERIFY(v1.count(Key{5}) == 0);
	VERIFY(v1.count(Key{6}) == 0);
	VERIFY(v2.size() == 3);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{1}) == 0);
	VERIFY(v2.count(Key{2}) == 1);
	VERIFY(v2.count(Key{3}) == 0);
	VERIFY(v2.count(Key{4}) == 1);
	VERIFY(v2.count(Key{5}) == 0);
	VERIFY(v2.count(Key{6}) == 1);

	{
		auto r = v1.insert(v2.extract(Key{2}));
		VERIFY(r != v1.end());
		VERIFY(*r == Key{2});
	}

	VERIFY(v1.size() == 5);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{1}) == 1);
	VERIFY(v1.count(Key{2}) == 2);
	VERIFY(v1.count(Key{3}) == 1);
	VERIFY(v1.count(Key{4}) == 1);
	VERIFY(v1.count(Key{5}) == 0);
	VERIFY(v1.count(Key{6}) == 0);
	VERIFY(v2.size() == 2);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{1}) == 0);
	VERIFY(v2.count(Key{2}) == 0);
	VERIFY(v2.count(Key{3}) == 0);
	VERIFY(v2.count(Key{4}) == 1);
	VERIFY(v2.count(Key{5}) == 0);
	VERIFY(v2.count(Key{6}) == 1);

	{
		auto r = v1.insert(v2.extract(Key{3}));
		VERIFY(r == v1.end());
	}

	VERIFY(v1.size() == 5);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{1}) == 1);
	VERIFY(v1.count(Key{2}) == 2);
	VERIFY(v1.count(Key{3}) == 1);
	VERIFY(v1.count(Key{4}) == 1);
	VERIFY(v1.count(Key{5}) == 0);
	VERIFY(v1.count(Key{6}) == 0);
	VERIFY(v2.size() == 2);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{1}) == 0);
	VERIFY(v2.count(Key{2}) == 0);
	VERIFY(v2.count(Key{3}) == 0);
	VERIFY(v2.count(Key{4}) == 1);
	VERIFY(v2.count(Key{5}) == 0);
	VERIFY(v2.count(Key{6}) == 1);

	{
		auto r = v1.insert(v2.extract(Key{4}));
		VERIFY(r != v1.end());
		VERIFY(*r == Key{4});
	}

	VERIFY(v1.size() == 6);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{1}) == 1);
	VERIFY(v1.count(Key{2}) == 2);
	VERIFY(v1.count(Key{3}) == 1);
	VERIFY(v1.count(Key{4}) == 2);
	VERIFY(v1.count(Key{5}) == 0);
	VERIFY(v1.count(Key{6}) == 0);
	VERIFY(v2.size() == 1);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{1}) == 0);
	VERIFY(v2.count(Key{2}) == 0);
	VERIFY(v2.count(Key{3}) == 0);
	VERIFY(v2.count(Key{4}) == 0);
	VERIFY(v2.count(Key{5}) == 0);
	VERIFY(v2.count(Key{6}) == 1);

	return true;
}

UNORDERED_MULTISET_TEST_CONSTEXPR bool test3()
{
	// ハッシュ関数、比較関数が異なるSetに移動する

	using Set1 = hamon::unordered_multiset<int>;
	using Set2 = hamon::unordered_multiset<int, WorstHash<int>, hamon::equal_to<>>;

	Set1 v1{2,4,6};
	Set2 v2{1,2,3};

	VERIFY(v1.size() == 3);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(1) == 0);
	VERIFY(v1.count(2) == 1);
	VERIFY(v1.count(3) == 0);
	VERIFY(v1.count(4) == 1);
	VERIFY(v1.count(5) == 0);
	VERIFY(v1.count(6) == 1);
	VERIFY(v2.size() == 3);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(1) == 1);
	VERIFY(v2.count(2) == 1);
	VERIFY(v2.count(3) == 1);
	VERIFY(v2.count(4) == 0);
	VERIFY(v2.count(5) == 0);
	VERIFY(v2.count(6) == 0);

	{
		auto r = v1.insert(v2.extract(1));
		VERIFY(r != v1.end());
		VERIFY(*r == 1);
	}

	VERIFY(v1.size() == 4);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(1) == 1);
	VERIFY(v1.count(2) == 1);
	VERIFY(v1.count(3) == 0);
	VERIFY(v1.count(4) == 1);
	VERIFY(v1.count(5) == 0);
	VERIFY(v1.count(6) == 1);
	VERIFY(v2.size() == 2);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(1) == 0);
	VERIFY(v2.count(2) == 1);
	VERIFY(v2.count(3) == 1);
	VERIFY(v2.count(4) == 0);
	VERIFY(v2.count(5) == 0);
	VERIFY(v2.count(6) == 0);

	{
		auto r = v1.insert(v2.extract(2));
		VERIFY(r != v1.end());
		VERIFY(*r == 2);
	}

	VERIFY(v1.size() == 5);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(1) == 1);
	VERIFY(v1.count(2) == 2);
	VERIFY(v1.count(3) == 0);
	VERIFY(v1.count(4) == 1);
	VERIFY(v1.count(5) == 0);
	VERIFY(v1.count(6) == 1);
	VERIFY(v2.size() == 1);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(1) == 0);
	VERIFY(v2.count(2) == 0);
	VERIFY(v2.count(3) == 1);
	VERIFY(v2.count(4) == 0);
	VERIFY(v2.count(5) == 0);
	VERIFY(v2.count(6) == 0);

	{
		auto r = v1.insert(v2.extract(4));
		VERIFY(r == v1.end());
	}

	VERIFY(v1.size() == 5);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(1) == 1);
	VERIFY(v1.count(2) == 2);
	VERIFY(v1.count(3) == 0);
	VERIFY(v1.count(4) == 1);
	VERIFY(v1.count(5) == 0);
	VERIFY(v1.count(6) == 1);
	VERIFY(v2.size() == 1);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(1) == 0);
	VERIFY(v2.count(2) == 0);
	VERIFY(v2.count(3) == 1);
	VERIFY(v2.count(4) == 0);
	VERIFY(v2.count(5) == 0);
	VERIFY(v2.count(6) == 0);

	return true;
}

UNORDERED_MULTISET_TEST_CONSTEXPR bool test4()
{
	// setからmultisetに移動する

	using Set = hamon::unordered_set<int>;
	using MultiSet = hamon::unordered_multiset<int, WorstHash<int>, hamon::equal_to<>>;

	Set v1{2,4,6};
	MultiSet v2{1,1,2,3};

	VERIFY(v1.size() == 3);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(1) == 0);
	VERIFY(v1.count(2) == 1);
	VERIFY(v1.count(3) == 0);
	VERIFY(v1.count(4) == 1);
	VERIFY(v1.count(5) == 0);
	VERIFY(v1.count(6) == 1);
	VERIFY(v2.size() == 4);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(1) == 2);
	VERIFY(v2.count(2) == 1);
	VERIFY(v2.count(3) == 1);
	VERIFY(v2.count(4) == 0);
	VERIFY(v2.count(5) == 0);
	VERIFY(v2.count(6) == 0);

	{
		auto r = v2.insert(v1.extract(1));
		VERIFY(r == v2.end());
	}

	VERIFY(v1.size() == 3);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(1) == 0);
	VERIFY(v1.count(2) == 1);
	VERIFY(v1.count(3) == 0);
	VERIFY(v1.count(4) == 1);
	VERIFY(v1.count(5) == 0);
	VERIFY(v1.count(6) == 1);
	VERIFY(v2.size() == 4);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(1) == 2);
	VERIFY(v2.count(2) == 1);
	VERIFY(v2.count(3) == 1);
	VERIFY(v2.count(4) == 0);
	VERIFY(v2.count(5) == 0);
	VERIFY(v2.count(6) == 0);

	{
		auto r = v2.insert(v1.extract(2));
		VERIFY(r != v2.end());
		VERIFY(*r == 2);
	}

	VERIFY(v1.size() == 2);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(1) == 0);
	VERIFY(v1.count(2) == 0);
	VERIFY(v1.count(3) == 0);
	VERIFY(v1.count(4) == 1);
	VERIFY(v1.count(5) == 0);
	VERIFY(v1.count(6) == 1);
	VERIFY(v2.size() == 5);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(1) == 2);
	VERIFY(v2.count(2) == 2);
	VERIFY(v2.count(3) == 1);
	VERIFY(v2.count(4) == 0);
	VERIFY(v2.count(5) == 0);
	VERIFY(v2.count(6) == 0);

	{
		auto r = v2.insert(v1.extract(4));
		VERIFY(r != v2.end());
		VERIFY(*r == 4);
	}

	VERIFY(v1.size() == 1);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(1) == 0);
	VERIFY(v1.count(2) == 0);
	VERIFY(v1.count(3) == 0);
	VERIFY(v1.count(4) == 0);
	VERIFY(v1.count(5) == 0);
	VERIFY(v1.count(6) == 1);
	VERIFY(v2.size() == 6);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(1) == 2);
	VERIFY(v2.count(2) == 2);
	VERIFY(v2.count(3) == 1);
	VERIFY(v2.count(4) == 1);
	VERIFY(v2.count(5) == 0);
	VERIFY(v2.count(6) == 0);

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedMultisetTest, InsertNodeTest)
{
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<char>()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test1<float>()));

	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test2()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test3()));
	UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE((test4()));
}

#undef UNORDERED_MULTISET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_MULTISET_TEST_CONSTEXPR

}	// namespace insert_node_test

}	// namespace hamon_unordered_multiset_test

#endif
