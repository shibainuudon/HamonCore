/**
 *	@file	unit_test_set_insert_node.cpp
 *
 *	@brief	insert のテスト
 *
 *	insert_return_type insert(node_type&& nh);
 */

#include <hamon/set/set.hpp>
#include <hamon/set/multiset.hpp>
#include <hamon/functional.hpp>
#include <hamon/iterator.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"

#if !defined(HAMON_USE_STD_SET) || \
	(defined(__cpp_lib_node_extract) && (__cpp_lib_node_extract >= 201606L))

namespace hamon_set_test
{

namespace insert_node_test
{

#if !defined(HAMON_USE_STD_SET)
#define SET_TEST_CONSTEXPR_EXPECT_TRUE HAMON_CXX20_CONSTEXPR_EXPECT_TRUE
#define SET_TEST_CONSTEXPR             HAMON_CXX20_CONSTEXPR
#else
#define SET_TEST_CONSTEXPR_EXPECT_TRUE	EXPECT_TRUE
#define SET_TEST_CONSTEXPR              /**/
#endif

struct S
{
	int value;

	constexpr S(int v) : value(v) {}

	S(S&&)                 = delete;
	S(S const&)            = delete;
	S& operator=(S&&)      = delete;
	S& operator=(S const&) = delete;

	friend constexpr bool operator<(S const& lhs, S const& rhs)
	{
		return lhs.value < rhs.value;
	}
};

#define VERIFY(...)	if (!(__VA_ARGS__)) { return false; }

template <typename Key>
SET_TEST_CONSTEXPR bool test1()
{
	using Set = hamon::set<Key>;
	using NodeType = typename Set::node_type;
	using InsertReturnType = typename Set::insert_return_type;

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().insert(hamon::declval<NodeType>())), InsertReturnType>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().insert(hamon::declval<NodeType>())), "");

	Set v1;
	Set v2{ Key{3}, Key{1}, Key{4}, Key{1}, Key{5} };

	{
		auto node = v2.extract(Key{1});
		auto r = v1.insert(hamon::move(node));
		VERIFY(r.inserted == true);
		VERIFY(r.position == v1.begin());
		VERIFY(r.node.empty() == true);
	}
	VERIFY(v1.size() == 1);
	{
		auto it = v1.begin();
		VERIFY(*it++ == 1);
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 3);
	{
		auto it = v2.begin();
		VERIFY(*it++ == 3);
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 5);
		VERIFY(it == v2.end());
	}

	{
		auto r = v1.insert(v2.extract(Key{4}));
		VERIFY(r.inserted == true);
		VERIFY(r.position == hamon::next(v1.begin(), 1));
		VERIFY(r.node.empty() == true);
	}
	VERIFY(v1.size() == 2);
	{
		auto it = v1.begin();
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 4);
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 2);
	{
		auto it = v2.begin();
		VERIFY(*it++ == 3);
		VERIFY(*it++ == 5);
		VERIFY(it == v2.end());
	}

	{
		auto r = v1.insert(v2.extract(Key{2}));
		VERIFY(r.inserted == false);
		VERIFY(r.position == v1.end());
		VERIFY(r.node.empty() == true);
	}
	VERIFY(v1.size() == 2);
	{
		auto it = v1.begin();
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 4);
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 2);
	{
		auto it = v2.begin();
		VERIFY(*it++ == 3);
		VERIFY(*it++ == 5);
		VERIFY(it == v2.end());
	}

	return true;
}

SET_TEST_CONSTEXPR bool test2()
{
	using Set = hamon::set<S>;

	Set v1;
	v1.emplace(1);
	v1.emplace(2);
	v1.emplace(3);
	v1.emplace(4);

	Set v2;
	v2.emplace(2);
	v2.emplace(4);
	v2.emplace(6);

	{
		auto r = v1.insert(v2.extract(v2.begin()));
		VERIFY(r.inserted == false);
		VERIFY(r.position == hamon::next(v1.begin(), 1));
		VERIFY(r.node.empty() == false);
		VERIFY(r.node.value().value == 2);
	}
	VERIFY(v1.size() == 4);
	{
		auto it = v1.begin();
		VERIFY((it++)->value == 1);
		VERIFY((it++)->value == 2);
		VERIFY((it++)->value == 3);
		VERIFY((it++)->value == 4);
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 2);
	{
		auto it = v2.begin();
		VERIFY((it++)->value == 4);
		VERIFY((it++)->value == 6);
		VERIFY(it == v2.end());
	}

	{
		auto r = v1.insert(v2.extract(hamon::next(v2.begin(), 1)));
		VERIFY(r.inserted == true);
		VERIFY(r.position == hamon::next(v1.begin(), 4));
		VERIFY(r.node.empty() == true);
	}
	VERIFY(v1.size() == 5);
	{
		auto it = v1.begin();
		VERIFY((it++)->value == 1);
		VERIFY((it++)->value == 2);
		VERIFY((it++)->value == 3);
		VERIFY((it++)->value == 4);
		VERIFY((it++)->value == 6);
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 1);
	{
		auto it = v2.begin();
		VERIFY((it++)->value == 4);
		VERIFY(it == v2.end());
	}

	return true;
}

SET_TEST_CONSTEXPR bool test3()
{
	using Set1 = hamon::set<int, hamon::less<>>;
	using Set2 = hamon::set<int, hamon::greater<>>;

	Set1 v1{2,4,6};
	Set2 v2{1,2,3};
	VERIFY(v1.size() == 3);
	{
		auto it = v1.begin();
		VERIFY(*it++ == 2);
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 6);
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 3);
	{
		auto it = v2.begin();
		VERIFY(*it++ == 3);
		VERIFY(*it++ == 2);
		VERIFY(*it++ == 1);
		VERIFY(it == v2.end());
	}

	{
		auto r = v1.insert(v2.extract(1));
		VERIFY(r.inserted == true);
		VERIFY(r.position == hamon::next(v1.begin(), 0));
		VERIFY(r.node.empty() == true);
	}
	VERIFY(v1.size() == 4);
	{
		auto it = v1.begin();
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 2);
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 6);
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 2);
	{
		auto it = v2.begin();
		VERIFY(*it++ == 3);
		VERIFY(*it++ == 2);
		VERIFY(it == v2.end());
	}

	{
		auto r = v2.insert(v1.extract(4));
		VERIFY(r.inserted == true);
		VERIFY(r.position == hamon::next(v2.begin(), 0));
		VERIFY(r.node.empty() == true);
	}
	VERIFY(v1.size() == 3);
	{
		auto it = v1.begin();
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 2);
		VERIFY(*it++ == 6);
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 3);
	{
		auto it = v2.begin();
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 3);
		VERIFY(*it++ == 2);
		VERIFY(it == v2.end());
	}

	{
		auto r = v1.insert(v2.extract(2));
		VERIFY(r.inserted == false);
		VERIFY(r.position == hamon::next(v1.begin(), 1));
		VERIFY(r.node.empty() == false);
	}
	VERIFY(v1.size() == 3);
	{
		auto it = v1.begin();
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 2);
		VERIFY(*it++ == 6);
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 2);
	{
		auto it = v2.begin();
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 3);
		VERIFY(it == v2.end());
	}

	return true;
}

SET_TEST_CONSTEXPR bool test4()
{
	using Set1 = hamon::set<int, hamon::less<>>;
	using Set2 = hamon::multiset<int, hamon::greater<>>;

	Set1 v1{2,4,6};
	Set2 v2{1,1,2,3};
	VERIFY(v1.size() == 3);
	{
		auto it = v1.begin();
		VERIFY(*it++ == 2);
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 6);
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 4);
	{
		auto it = v2.begin();
		VERIFY(*it++ == 3);
		VERIFY(*it++ == 2);
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 1);
		VERIFY(it == v2.end());
	}

	{
		auto r = v1.insert(v2.extract(1));
		VERIFY(r.inserted == true);
		VERIFY(r.position == hamon::next(v1.begin(), 0));
		VERIFY(r.node.empty() == true);
	}
	VERIFY(v1.size() == 4);
	{
		auto it = v1.begin();
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 2);
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 6);
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 3);
	{
		auto it = v2.begin();
		VERIFY(*it++ == 3);
		VERIFY(*it++ == 2);
		VERIFY(*it++ == 1);
		VERIFY(it == v2.end());
	}

	{
		auto r = v1.insert(v2.extract(2));
		VERIFY(r.inserted == false);
		VERIFY(r.position == hamon::next(v1.begin(), 1));
		VERIFY(r.node.empty() == false);
	}
	VERIFY(v1.size() == 4);
	{
		auto it = v1.begin();
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 2);
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 6);
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 2);
	{
		auto it = v2.begin();
		VERIFY(*it++ == 3);
		VERIFY(*it++ == 1);
		VERIFY(it == v2.end());
	}

	{
		auto r = v1.insert(v2.extract(4));
		VERIFY(r.inserted == false);
		VERIFY(r.position == v1.end());
		VERIFY(r.node.empty() == true);
	}
	VERIFY(v1.size() == 4);
	{
		auto it = v1.begin();
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 2);
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 6);
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 2);
	{
		auto it = v2.begin();
		VERIFY(*it++ == 3);
		VERIFY(*it++ == 1);
		VERIFY(it == v2.end());
	}

	return true;
}

#undef VERIFY

GTEST_TEST(SetTest, InsertNodeTest)
{
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<char>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<float>()));

	SET_TEST_CONSTEXPR_EXPECT_TRUE((test2()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test3()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test4()));
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace insert_node_test

}	// namespace hamon_set_test

#endif
