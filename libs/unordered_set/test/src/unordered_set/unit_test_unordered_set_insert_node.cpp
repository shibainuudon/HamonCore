/**
 *	@file	unit_test_unordered_set_insert_node.cpp
 *
 *	@brief	insert のテスト
 *
 *	constexpr insert_return_type insert(node_type&& nh);
 */

#include <hamon/unordered_set/unordered_set.hpp>
#include <hamon/unordered_set/unordered_multiset.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/utility/declval.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include "unordered_set_test_helper.hpp"

#if !defined(HAMON_USE_STD_UNORDERED_SET) || \
	(defined(__cpp_lib_node_extract) && (__cpp_lib_node_extract >= 201606L))

namespace hamon_unordered_set_test
{

namespace insert_node_test
{

#if !defined(HAMON_USE_STD_UNORDERED_SET) && defined(HAMON_HAS_CONSTEXPR_BIT_CAST)
#define UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE  HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define UNORDERED_SET_TEST_CONSTEXPR              HAMON_CXX20_CONSTEXPR
#else
#define UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE  EXPECT_TRUE
#define UNORDERED_SET_TEST_CONSTEXPR              /**/
#endif

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
UNORDERED_SET_TEST_CONSTEXPR bool test1()
{
	using Set = hamon::unordered_set<Key>;
	using NodeType = typename Set::node_type;
	using InsertReturnType = typename Set::insert_return_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().insert(hamon::declval<NodeType>())), InsertReturnType>::value, "");
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
	VERIFY(v2.size() == 3);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{0}) == 0);
	VERIFY(v2.count(Key{1}) == 1);
	VERIFY(v2.count(Key{2}) == 0);
	VERIFY(v2.count(Key{3}) == 1);
	VERIFY(v2.count(Key{4}) == 1);
	VERIFY(v2.count(Key{5}) == 0);

	{
		auto node = v2.extract(Key{1});
		auto r = v1.insert(hamon::move(node));
		VERIFY(r.inserted == true);
		VERIFY(r.position != v1.end());
		VERIFY(*r.position == Key{1});
		VERIFY(r.node.empty() == true);
	}

	VERIFY(v1.size() == 1);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{0}) == 0);
	VERIFY(v1.count(Key{1}) == 1);
	VERIFY(v1.count(Key{2}) == 0);
	VERIFY(v1.count(Key{3}) == 0);
	VERIFY(v1.count(Key{4}) == 0);
	VERIFY(v1.count(Key{5}) == 0);
	VERIFY(v2.size() == 2);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{0}) == 0);
	VERIFY(v2.count(Key{1}) == 0);
	VERIFY(v2.count(Key{2}) == 0);
	VERIFY(v2.count(Key{3}) == 1);
	VERIFY(v2.count(Key{4}) == 1);
	VERIFY(v2.count(Key{5}) == 0);

	{
		auto node = v2.extract(Key{2});
		auto r = v1.insert(hamon::move(node));
		VERIFY(r.inserted == false);
		VERIFY(r.position == v1.end());
		VERIFY(r.node.empty() == true);
	}

	VERIFY(v1.size() == 1);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{0}) == 0);
	VERIFY(v1.count(Key{1}) == 1);
	VERIFY(v1.count(Key{2}) == 0);
	VERIFY(v1.count(Key{3}) == 0);
	VERIFY(v1.count(Key{4}) == 0);
	VERIFY(v1.count(Key{5}) == 0);
	VERIFY(v2.size() == 2);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{0}) == 0);
	VERIFY(v2.count(Key{1}) == 0);
	VERIFY(v2.count(Key{2}) == 0);
	VERIFY(v2.count(Key{3}) == 1);
	VERIFY(v2.count(Key{4}) == 1);
	VERIFY(v2.count(Key{5}) == 0);

	{
		auto node = v2.extract(Key{4});
		auto r = v1.insert(hamon::move(node));
		VERIFY(r.inserted == true);
		VERIFY(r.position != v1.end());
		VERIFY(*r.position == Key{4});
		VERIFY(r.node.empty() == true);
	}

	VERIFY(v1.size() == 2);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(Key{0}) == 0);
	VERIFY(v1.count(Key{1}) == 1);
	VERIFY(v1.count(Key{2}) == 0);
	VERIFY(v1.count(Key{3}) == 0);
	VERIFY(v1.count(Key{4}) == 1);
	VERIFY(v1.count(Key{5}) == 0);
	VERIFY(v2.size() == 1);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(Key{0}) == 0);
	VERIFY(v2.count(Key{1}) == 0);
	VERIFY(v2.count(Key{2}) == 0);
	VERIFY(v2.count(Key{3}) == 1);
	VERIFY(v2.count(Key{4}) == 0);
	VERIFY(v2.count(Key{5}) == 0);

	return true;
}

UNORDERED_SET_TEST_CONSTEXPR bool test2()
{
	// コピー不可、ムーブ不可なオブジェクトを別のSetに移動する

	using Key = NonCopyableMovable;
	using Set = hamon::unordered_set<Key, hamon::hash<Key>>;

	Set v1;
	v1.emplace(1);
	v1.emplace(2);
	v1.emplace(3);
	v1.emplace(4);

	Set v2;
	v2.emplace(2);
	v2.emplace(4);
	v2.emplace(6);

	VERIFY(v1.size() == 4);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v2.size() == 3);
	VERIFY(v2.load_factor() <= v2.max_load_factor());

	{
		auto r = v1.insert(v2.extract(Key{2}));
		VERIFY(r.inserted == false);
		VERIFY(r.position != v1.end());
		VERIFY(*r.position == Key{2});
		VERIFY(r.node.empty() == false);
		VERIFY(r.node.value() == Key{2});
	}

	VERIFY(v1.size() == 4);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v2.size() == 2);
	VERIFY(v2.load_factor() <= v2.max_load_factor());

	{
		auto r = v1.insert(v2.extract(Key{3}));
		VERIFY(r.inserted == false);
		VERIFY(r.position == v1.end());
		VERIFY(r.node.empty() == true);
	}

	VERIFY(v1.size() == 4);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v2.size() == 2);
	VERIFY(v2.load_factor() <= v2.max_load_factor());

	{
		auto r = v1.insert(v2.extract(Key{4}));
		VERIFY(r.inserted == false);
		VERIFY(r.position != v1.end());
		VERIFY(*r.position == Key{4});
		VERIFY(r.node.empty() == false);
		VERIFY(r.node.value() == Key{4});
	}

	VERIFY(v1.size() == 4);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v2.size() == 1);
	VERIFY(v2.load_factor() <= v2.max_load_factor());

	{
		auto r = v1.insert(v2.extract(Key{6}));
		VERIFY(r.inserted == true);
		VERIFY(r.position != v1.end());
		VERIFY(*r.position == Key{6});
		VERIFY(r.node.empty() == true);
	}

	VERIFY(v1.size() == 5);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v2.size() == 0);
	VERIFY(v2.load_factor() <= v2.max_load_factor());

	return true;
}

UNORDERED_SET_TEST_CONSTEXPR bool test3()
{
	// ハッシュ関数、比較関数が異なるSetに移動する

	using Set1 = hamon::unordered_set<int>;
	using Set2 = hamon::unordered_set<int, WorstHash<int>, hamon::equal_to<>>;

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
		VERIFY(r.inserted == true);
		VERIFY(r.position != v1.end());
		VERIFY(*r.position == 1);
		VERIFY(r.node.empty() == true);
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
		auto r = v2.insert(v1.extract(4));
		VERIFY(r.inserted == true);
		VERIFY(r.position != v2.end());
		VERIFY(*r.position == 4);
		VERIFY(r.node.empty() == true);
	}

	VERIFY(v1.size() == 3);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(1) == 1);
	VERIFY(v1.count(2) == 1);
	VERIFY(v1.count(3) == 0);
	VERIFY(v1.count(4) == 0);
	VERIFY(v1.count(5) == 0);
	VERIFY(v1.count(6) == 1);
	VERIFY(v2.size() == 3);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(1) == 0);
	VERIFY(v2.count(2) == 1);
	VERIFY(v2.count(3) == 1);
	VERIFY(v2.count(4) == 1);
	VERIFY(v2.count(5) == 0);
	VERIFY(v2.count(6) == 0);

	{
		auto r = v2.insert(v1.extract(2));
		VERIFY(r.inserted == false);
		VERIFY(r.position != v2.end());
		VERIFY(*r.position == 2);
		VERIFY(r.node.empty() == false);
		VERIFY(r.node.value() == 2);
	}

	VERIFY(v1.size() == 2);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(1) == 1);
	VERIFY(v1.count(2) == 0);
	VERIFY(v1.count(3) == 0);
	VERIFY(v1.count(4) == 0);
	VERIFY(v1.count(5) == 0);
	VERIFY(v1.count(6) == 1);
	VERIFY(v2.size() == 3);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(1) == 0);
	VERIFY(v2.count(2) == 1);
	VERIFY(v2.count(3) == 1);
	VERIFY(v2.count(4) == 1);
	VERIFY(v2.count(5) == 0);
	VERIFY(v2.count(6) == 0);

	{
		auto r = v2.insert(v1.extract(2));
		VERIFY(r.inserted == false);
		VERIFY(r.position == v2.end());
		VERIFY(r.node.empty() == true);
	}

	VERIFY(v1.size() == 2);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(1) == 1);
	VERIFY(v1.count(2) == 0);
	VERIFY(v1.count(3) == 0);
	VERIFY(v1.count(4) == 0);
	VERIFY(v1.count(5) == 0);
	VERIFY(v1.count(6) == 1);
	VERIFY(v2.size() == 3);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(1) == 0);
	VERIFY(v2.count(2) == 1);
	VERIFY(v2.count(3) == 1);
	VERIFY(v2.count(4) == 1);
	VERIFY(v2.count(5) == 0);
	VERIFY(v2.count(6) == 0);

	return true;
}

UNORDERED_SET_TEST_CONSTEXPR bool test4()
{
	// multisetからsetに移動する

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
		auto r = v1.insert(v2.extract(1));
		VERIFY(r.inserted == true);
		VERIFY(r.position != v1.end());
		VERIFY(*r.position == 1);
		VERIFY(r.node.empty() == true);
	}

	VERIFY(v1.size() == 4);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(1) == 1);
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
		auto r = v1.insert(v2.extract(2));
		VERIFY(r.inserted == false);
		VERIFY(r.position != v1.end());
		VERIFY(*r.position == 2);
		VERIFY(r.node.empty() == false);
		VERIFY(r.node.value() == 2);
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
	VERIFY(v2.count(1) == 1);
	VERIFY(v2.count(2) == 0);
	VERIFY(v2.count(3) == 1);
	VERIFY(v2.count(4) == 0);
	VERIFY(v2.count(5) == 0);
	VERIFY(v2.count(6) == 0);

	{
		auto r = v1.insert(v2.extract(4));
		VERIFY(r.inserted == false);
		VERIFY(r.position == v1.end());
		VERIFY(r.node.empty() == true);
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
	VERIFY(v2.count(1) == 1);
	VERIFY(v2.count(2) == 0);
	VERIFY(v2.count(3) == 1);
	VERIFY(v2.count(4) == 0);
	VERIFY(v2.count(5) == 0);
	VERIFY(v2.count(6) == 0);

	{
		auto r = v1.insert(v2.extract(3));
		VERIFY(r.inserted == true);
		VERIFY(r.position != v1.end());
		VERIFY(*r.position == 3);
		VERIFY(r.node.empty() == true);
	}

	VERIFY(v1.size() == 5);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(1) == 1);
	VERIFY(v1.count(2) == 1);
	VERIFY(v1.count(3) == 1);
	VERIFY(v1.count(4) == 1);
	VERIFY(v1.count(5) == 0);
	VERIFY(v1.count(6) == 1);
	VERIFY(v2.size() == 1);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(1) == 1);
	VERIFY(v2.count(2) == 0);
	VERIFY(v2.count(3) == 0);
	VERIFY(v2.count(4) == 0);
	VERIFY(v2.count(5) == 0);
	VERIFY(v2.count(6) == 0);

	{
		auto r = v1.insert(v2.extract(1));
		VERIFY(r.inserted == false);
		VERIFY(r.position != v1.end());
		VERIFY(*r.position == 1);
		VERIFY(r.node.empty() == false);
		VERIFY(r.node.value() == 1);
	}

	VERIFY(v1.size() == 5);
	VERIFY(v1.load_factor() <= v1.max_load_factor());
	VERIFY(v1.count(1) == 1);
	VERIFY(v1.count(2) == 1);
	VERIFY(v1.count(3) == 1);
	VERIFY(v1.count(4) == 1);
	VERIFY(v1.count(5) == 0);
	VERIFY(v1.count(6) == 1);
	VERIFY(v2.size() == 0);
	VERIFY(v2.load_factor() <= v2.max_load_factor());
	VERIFY(v2.count(1) == 0);
	VERIFY(v2.count(2) == 0);
	VERIFY(v2.count(3) == 0);
	VERIFY(v2.count(4) == 0);
	VERIFY(v2.count(5) == 0);
	VERIFY(v2.count(6) == 0);

	return true;
}

#undef VERIFY

GTEST_TEST(UnorderedSetTest, InsertNodeTest)
{
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<char>()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<float>()));

	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test2()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test3()));
	UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE((test4()));
}

#undef UNORDERED_SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef UNORDERED_SET_TEST_CONSTEXPR

}	// namespace insert_node_test

}	// namespace hamon_unordered_set_test

#endif
