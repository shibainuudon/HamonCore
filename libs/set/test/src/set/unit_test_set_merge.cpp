﻿/**
 *	@file	unit_test_set_merge.cpp
 *
 *	@brief	merge のテスト
 *
 *	template<class C2>
 *	void merge(set<Key, C2, Allocator>& source);
 *	template<class C2>
 *	void merge(set<Key, C2, Allocator>&& source);
 *	template<class C2>
 *	void merge(multiset<Key, C2, Allocator>& source);
 *	template<class C2>
 *	void merge(multiset<Key, C2, Allocator>&& source);
 */

#include <hamon/set/set.hpp>
#include <hamon/set/multiset.hpp>
#include <hamon/functional.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <gtest/gtest.h>
#include "constexpr_test.hpp"
#include <string>
#include <sstream>

#if 1	// TODO
#if !defined(HAMON_USE_STD_SET) || \
	(defined(__cpp_lib_node_extract) && (__cpp_lib_node_extract >= 201606L))

namespace hamon_set_test
{

namespace merge_test
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

	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().merge(hamon::declval<Set&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set&>().merge(hamon::declval<Set&&>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Set&>().merge(hamon::declval<Set&>())), "");
	static_assert(!noexcept(hamon::declval<Set&>().merge(hamon::declval<Set&&>())), "");

	Set v1{ Key{1}, Key{2}, Key{3} };
	Set v2{ Key{1}, Key{3}, Key{4}, Key{5} };

	v1.merge(v2);
	VERIFY(v1.size() == 5);
	{
		auto it = v1.begin();
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 2);
		VERIFY(*it++ == 3);
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 5);
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 2);
	{
		auto it = v2.begin();
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 3);
		VERIFY(it == v2.end());
	}

	v2.merge(hamon::move(v1));
	VERIFY(v1.size() == 2);
	{
		auto it = v1.begin();
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 3);
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 5);
	{
		auto it = v2.begin();
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 2);
		VERIFY(*it++ == 3);
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 5);
		VERIFY(it == v2.end());
	}

	return true;
}

template <typename Key>
SET_TEST_CONSTEXPR bool test2()
{
	using Set1 = hamon::set<Key, hamon::less<>>;
	using Set2 = hamon::set<Key, hamon::greater<>>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set1&>().merge(hamon::declval<Set2&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set1&>().merge(hamon::declval<Set2&&>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Set1&>().merge(hamon::declval<Set2&>())), "");
	static_assert(!noexcept(hamon::declval<Set1&>().merge(hamon::declval<Set2&&>())), "");

	Set1 v1{ Key{1}, Key{2}, Key{3} };
	Set2 v2{ Key{1}, Key{3}, Key{4}, Key{5} };

	v1.merge(v2);
	VERIFY(v1.size() == 5);
	{
		auto it = v1.begin();
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 2);
		VERIFY(*it++ == 3);
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 5);
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 2);
	{
		auto it = v2.begin();
		VERIFY(*it++ == 3);
		VERIFY(*it++ == 1);
		VERIFY(it == v2.end());
	}

	v2.merge(hamon::move(v1));
	VERIFY(v1.size() == 2);
	{
		auto it = v1.begin();
		VERIFY(*it++ == 1);
		VERIFY(*it++ == 3);
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 5);
	{
		auto it = v2.begin();
		VERIFY(*it++ == 5);
		VERIFY(*it++ == 4);
		VERIFY(*it++ == 3);
		VERIFY(*it++ == 2);
		VERIFY(*it++ == 1);
		VERIFY(it == v2.end());
	}

	return true;
}

template <typename Key>
SET_TEST_CONSTEXPR bool test3()
{
	using Set1 = hamon::set<Key, hamon::less<>>;
	using Set2 = hamon::multiset<Key, hamon::greater<>>;

	static_assert(hamon::is_same<decltype(hamon::declval<Set1&>().merge(hamon::declval<Set2&>())), void>::value, "");
	static_assert(hamon::is_same<decltype(hamon::declval<Set1&>().merge(hamon::declval<Set2&&>())), void>::value, "");
	static_assert(!noexcept(hamon::declval<Set1&>().merge(hamon::declval<Set2&>())), "");
	static_assert(!noexcept(hamon::declval<Set1&>().merge(hamon::declval<Set2&&>())), "");

	{
		Set1 v1{ Key{1}, Key{2}, Key{3} };
		Set2 v2{ Key{1}, Key{3}, Key{4}, Key{5} };

		v1.merge(v2);
		VERIFY(v1.size() == 5);
		{
			auto it = v1.begin();
			VERIFY(*it++ == 1);
			VERIFY(*it++ == 2);
			VERIFY(*it++ == 3);
			VERIFY(*it++ == 4);
			VERIFY(*it++ == 5);
			VERIFY(it == v1.end());
		}
		VERIFY(v2.size() == 2);
		{
			auto it = v2.begin();
			VERIFY(*it++ == 3);
			VERIFY(*it++ == 1);
			VERIFY(it == v2.end());
		}
	}
	{
		Set1 v1{ Key{1}, Key{2}, Key{3} };
		Set2 v2{ Key{1}, Key{3}, Key{4}, Key{5} };

		v1.merge(hamon::move(v2));
		VERIFY(v1.size() == 5);
		{
			auto it = v1.begin();
			VERIFY(*it++ == 1);
			VERIFY(*it++ == 2);
			VERIFY(*it++ == 3);
			VERIFY(*it++ == 4);
			VERIFY(*it++ == 5);
			VERIFY(it == v1.end());
		}
		VERIFY(v2.size() == 2);
		{
			auto it = v2.begin();
			VERIFY(*it++ == 3);
			VERIFY(*it++ == 1);
			VERIFY(it == v2.end());
		}
	}

	return true;
}

SET_TEST_CONSTEXPR bool test4()
{
	using Set = hamon::set<S>;

	Set v1;
	v1.emplace(1);
	v1.emplace(2);
	v1.emplace(3);
	v1.emplace(4);

	Set v2;
	v2.emplace(0);
	v2.emplace(2);
	v2.emplace(4);
	v2.emplace(6);

	v1.merge(v2);
	VERIFY(v1.size() == 6);
	{
		auto it = v1.begin();
		VERIFY((it++)->value == 0);
		VERIFY((it++)->value == 1);
		VERIFY((it++)->value == 2);
		VERIFY((it++)->value == 3);
		VERIFY((it++)->value == 4);
		VERIFY((it++)->value == 6);
		VERIFY(it == v1.end());
	}
	VERIFY(v2.size() == 2);
	{
		auto it = v2.begin();
		VERIFY((it++)->value == 2);
		VERIFY((it++)->value == 4);
		VERIFY(it == v2.end());
	}

	return true;
}

#undef VERIFY

template <typename T, typename C>
std::string ToString(const hamon::set<T, C>& set)
{
	std::stringstream out;
	auto n = set.size();
	out << "{";
	for (auto const& elm : set)
	{
		out << elm << (--n ? ", " : "");
	}
	out << "}";
	return out.str();
}

GTEST_TEST(SetTest, MergeTest)
{
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<int>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<char>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test1<float>()));

	SET_TEST_CONSTEXPR_EXPECT_TRUE((test2<int>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test2<char>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test2<float>()));

	SET_TEST_CONSTEXPR_EXPECT_TRUE((test3<int>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test3<char>()));
	SET_TEST_CONSTEXPR_EXPECT_TRUE((test3<float>()));

	SET_TEST_CONSTEXPR_EXPECT_TRUE((test4()));

	// https://en.cppreference.com/w/cpp/container/set/merge
	{
		hamon::set<char>
			p {'C', 'B', 'B', 'A'},
			q {'E', 'D', 'E', 'C'};

		EXPECT_EQ("{A, B, C}", ToString(p));
		EXPECT_EQ("{C, D, E}", ToString(q));

		p.merge(q);

		EXPECT_EQ("{A, B, C, D, E}", ToString(p));
		EXPECT_EQ("{C}", ToString(q));
	}
}

#undef SET_TEST_CONSTEXPR_EXPECT_TRUE
#undef SET_TEST_CONSTEXPR

}	// namespace merge_test

}	// namespace hamon_set_test

#endif
#endif
